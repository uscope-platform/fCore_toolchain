// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fcore_cc.hpp"

#include <utility>




fcore::fcore_cc::fcore_cc(std::vector<std::string> &contents, std::vector<std::string> &inc) :
        input_string_stream(contents[0]), hl_manager(0), ll_manager(0){
    type = "string";
    includes = inc;
    include_is_paths = false;
    logging = false;
    dump_ast_level = 0;
}

fcore::fcore_cc::fcore_cc(std::string &path, std::vector<std::string> &inc, bool print_debug, int dump_lvl) :
input_file_stream(path), hl_manager(dump_lvl), ll_manager(dump_lvl){
    type = "file";
    include_is_paths = true;
    includes = inc;
    logging = print_debug;
    dump_ast_level = dump_lvl;
}

bool fcore::fcore_cc::compile() {
    auto def_map = std::make_shared<define_map>();
    std::vector<std::shared_ptr<hl_ast_node>> includes_ASTs;
    if(!includes.empty()){
        for(auto &i:includes){
            if(include_is_paths){
                std::ifstream ifs(i);
                includes_ASTs.push_back(parse_include(ifs, def_map));
            } else {
                std::istringstream ifs(i);
                includes_ASTs.push_back(parse_include(ifs, def_map));
            }
        }
    }

    try{
        parse_dma_spec();
        parse(dma_io_spec, def_map);
        merge_includes(includes_ASTs);
        optimize(dma_io_map);
    } catch(std::runtime_error &e){
        std::string error = e.what();
        error_code = e.what();
        return false;
    }
    return true;
}


std::string fcore::fcore_cc::get_errors() {
    return error_code;
}

std::vector<uint32_t> fcore::fcore_cc::get_raw_code() {
    return writer.get_code();
}


void fcore::fcore_cc::write_hexfile(const std::string &ouput_file) {
    writer.write_hex_file(ouput_file);
}

void fcore::fcore_cc::write_verilog_memfile(const std::string &ouput_file) {
    writer.write_mem_file(ouput_file);
}

void fcore::fcore_cc::write_json(const std::string &output_file) {
    nlohmann::json j;
    j["error_code"] = error_code;
    if(error_code.empty()){
        j["compiled_program"] = writer.generate_hex(false);
    } else{
        j["compiled_program"] = {};
    }
    std::string str = j.dump();
    std::ofstream ss(output_file);
    ss<<str;
    ss.close();
}

void fcore::fcore_cc::parse(std::unordered_map<std::string, variable_class_t> dma_specs, std::shared_ptr<define_map> def_map) {
    error_code = "";
    C_language_parser target_parser;
    if(type == "string"){
        target_parser = C_language_parser(input_string_stream, def_map);
    } else{
        target_parser = C_language_parser(input_file_stream, def_map);
    }
    target_parser.pre_process({});
    target_parser.parse(std::move(dma_specs));
    hl_ast = target_parser.AST;
}

void fcore::fcore_cc::optimize(std::unordered_map<std::string, std::vector<uint32_t>> &dma_map) {
    std::string ep = "main";
    hl_manager = create_hl_pass_manager(ep, dump_ast_level);
    hl_manager.run_morphing_passes(hl_ast);
    if(dump_ast_level>0) dump["high_level"] = hl_manager.get_dump();

    high_level_ast_lowering translator;
    translator.set_input_ast(hl_ast);
    translator.translate();
    ll_ast = translator.get_output_ast();


    ll_manager = create_ll_pass_manager(dump_ast_level);
    ll_manager.run_morphing_passes(ll_ast);

    if(dump_ast_level>0) dump["low_level"] = ll_manager.get_dump();

    instruction_stream program_stream = instruction_stream_builder::build_stream(ll_ast);

    allocation_map = std::make_shared<io_map>();

    auto bindings_map = std::make_shared<std::unordered_map<std::string, memory_range_t>>();
    stream_pass_manager sman(dump_ast_level, bindings_map, allocation_map);
    program_stream = sman.process_stream(program_stream);

    analyze_program_length(sman.get_instruction_count());

    if(dump_ast_level>0) dump["stream"] = sman.get_dump();

    if(program_stream.empty()){
        program_stream.push_back(std::make_shared<ll_independent_inst_node>("stop"));
    }
    if(!program_stream.last()->is_stop()){
        program_stream.push_back(std::make_shared<ll_independent_inst_node>("stop"));
    }
    writer.process_stream(program_stream,dma_map,allocation_map, logging);
}

void fcore::fcore_cc::parse_dma_spec() {
    for(auto &item:dma_spec){
        std::shared_ptr<variable> v = std::make_shared<variable>(item.first);
        switch (item.second.type) {
            case core_iom_input:
                v->set_variable_class(variable_input_type);
                dma_io_spec[item.first] = variable_input_type;
                break;
            case core_iom_output:
                v->set_variable_class(variable_output_type);
                dma_io_spec[item.first] = variable_output_type;
                break;
            case core_iom_memory:
                v->set_variable_class(variable_memory_type);
                dma_io_spec[item.first] = variable_memory_type;
                break;
        }
        dma_io_map[item.first] = item.second.address;

    }

}

std::vector<uint32_t> fcore::fcore_cc::get_executable() {
    return writer.get_executable();
}

std::set<fcore::io_map_entry> fcore::fcore_cc::get_io_map() {
    return writer.get_io_mapping();
}

std::shared_ptr<fcore::hl_ast_node>  fcore::fcore_cc::parse_include(std::istream &input, std::shared_ptr<define_map> def_map) {
    std::unordered_map<std::string, variable_class_t> dma_specs;
    C_language_parser target_parser(input, def_map);
    target_parser.pre_process({});
    target_parser.parse(std::move(dma_specs));
    auto target = target_parser.AST;
    return target;
}

void fcore::fcore_cc::merge_includes(const std::vector<std::shared_ptr<hl_ast_node>>& i) {

    std::set<std::string> target_functions;
    for(auto & node: hl_ast->get_content()){
        if(node->node_type == hl_ast_node_type_function_def){
            target_functions.insert(std::static_pointer_cast<hl_function_def_node>(node)->get_name());
        }
    }

    for(auto &include:i){
        for(auto &node:include->get_content()){
            if(node->node_type == hl_ast_node_type_function_def){
                if(!target_functions.contains(std::static_pointer_cast<hl_function_def_node>(node)->get_name())){
                    hl_ast->add_content(node);
                }
            }
        }
    }

}

void fcore::fcore_cc::analyze_program_length(std::shared_ptr<struct instruction_count> c) {

    length_info.per_channel_portion = c->regular + c->efi * info.efi_lenght + c->load;

    length_info.fixed_portion = c->stop * info.stop_duration +
            info.fixed_core_overhead + c->load*info.load_overhead;
}

nlohmann::json fcore::fcore_cc::dump_iom_map(std::unordered_map<std::string, core_iom> &map) {
    nlohmann::json ret;
    for(auto &item:map){
        ret[item.first] = nlohmann::json();
        switch (item.second.type) {
            case core_iom_output:
                ret[item.first]["type"] = "output";
                break;
            case core_iom_input:
                ret[item.first]["type"] = "input";
                break;
            case core_iom_memory:
                ret[item.first]["type"]= "memory";
                break;
        }
        ret[item.first]["address"] = item.second.address;
    }
    return ret;
}

std::unordered_map<std::string, fcore::core_iom> fcore::fcore_cc::load_iom_map(const nlohmann::json &raw_map) {
    std::unordered_map<std::string, fcore::core_iom> ret;

    for(auto &item:raw_map.items()){
        fcore::core_iom iom;
        std::vector<uint32_t> addr =  raw_map["address"];
        iom.address = addr;
        iom.type = core_iom_type_translator[raw_map["type"]];
    }

    return ret;
}
