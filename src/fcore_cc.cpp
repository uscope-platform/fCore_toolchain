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



namespace fcore{

    fcore_cc::fcore_cc(std::vector<std::string> &contents, std::vector<std::string> &inc) :
            input_string_stream(contents[0]){
        type = "string";
        includes = inc;
        include_is_paths = false;
        logging = false;
    }

    fcore_cc::fcore_cc(std::string &path, std::vector<std::string> &inc, bool print_debug) :
            input_file_stream(path){
        type = "file";
        include_is_paths = true;
        includes = inc;
        logging = print_debug;
    }

    bool fcore_cc::compile() {
        auto def_map = std::make_shared<define_map>();

        if (profiling_core != nullptr) profiling_core->set_phase("parsing");

        std::vector<std::shared_ptr<ast_code_block>> includes_ASTs;
        if (profiling_core != nullptr) profiling_core->start_event("parse headers", false);
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
        if (profiling_core != nullptr) profiling_core->end_event("parse headers");
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


    std::string fcore_cc::get_errors() {
        return error_code;
    }

    std::vector<uint32_t> fcore_cc::get_raw_code() {
        return writer.get_code();
    }


    void fcore_cc::write_hexfile(const std::string &ouput_file) {
        writer.write_hex_file(ouput_file);
    }

    void fcore_cc::write_verilog_memfile(const std::string &ouput_file) {
        writer.write_mem_file(ouput_file);
    }

    void fcore_cc::write_json(const std::string &output_file) {
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

    std::pair<std::shared_ptr<ast_code_block>, std::vector<std::shared_ptr<ast_definition>>> fcore_cc::get_hl_ast() {
        parse(dma_io_spec, std::make_shared<define_map>());
        return {hl_ast, globals};
    }

    void fcore_cc::parse(std::map<std::string, variable_class_t> dma_specs, std::shared_ptr<define_map> def_map) {
        error_code = "";
        C_language_parser target_parser;
        if(type == "string"){
            target_parser = C_language_parser(input_string_stream, def_map);
        } else{
            target_parser = C_language_parser(input_file_stream, def_map);
        }

        if (profiling_core != nullptr) profiling_core->start_event("program_parsing", false);
        target_parser.pre_process({});
        target_parser.parse(std::move(dma_specs));
        hl_ast = target_parser.AST;
        globals = target_parser.get_globals();

        if (profiling_core != nullptr) profiling_core->end_event("program_parsing");
    }

    void fcore_cc::optimize(std::map<std::string, std::vector<uint32_t>> &dma_map) {

        std::string ep = "main";
        hl_manager = create_hl_pass_manager(ep);
        hl_manager.set_profiler(profiling_core);
        if (profiling_core != nullptr) profiling_core->set_phase("AST processing");
        hl_ast = hl_manager.run_optimizations(hl_ast, globals);

        high_level_ast_lowering translator;
        translator.set_input_ast(hl_ast);
        instruction_stream program_stream  = translator.translate();


        allocation_map = std::make_shared<io_map>();

        auto bindings_map = std::make_shared<std::map<std::string, memory_range_t>>();
        stream_pass_manager sman( bindings_map, allocation_map, profiling_core, stream_pass_manager::high_level_language);
        program_stream = sman.process_stream(program_stream);

        analyze_program_length(sman.get_instruction_count());


        if(program_stream.empty()){
            program_stream.push_back(instruction_variant(independent_instruction(opcode_stop)));
        }
        insert_stop(program_stream);
        flush_pipeline(program_stream);
        writer.process_stream(program_stream,dma_map,allocation_map, logging);
    }

    void fcore_cc::parse_dma_spec() {
        for(auto &item:dma_spec){
            std::shared_ptr<variable> v = std::make_shared<variable>(item.first);
            variable_class_t c{};
            switch (item.second.type) {
                case core_iom_input:
                    c = {variable_input_type, item.second.common_io};
                    v->set_variable_class(c);
                    dma_io_spec[item.first] = c;
                    break;
                case core_iom_output:
                    c = {variable_output_type, item.second.common_io};
                    v->set_variable_class(c);
                    dma_io_spec[item.first] = c;
                    break;
                case core_iom_memory:
                    c = {variable_memory_type, item.second.common_io};
                    v->set_variable_class(c);
                    dma_io_spec[item.first] = c;
                    break;
            }
            dma_io_map[item.first] = item.second.address;

        }

    }

    std::vector<uint32_t> fcore_cc::get_executable() {
        return writer.get_executable();
    }

    std::set<io_map_entry> fcore_cc::get_io_map() {
        return writer.get_io_mapping();
    }

    std::shared_ptr<ast_code_block>  fcore_cc::parse_include(std::istream &input, std::shared_ptr<define_map> def_map) {
        std::map<std::string, variable_class_t> dma_specs;
        C_language_parser target_parser(input, def_map);
        target_parser.pre_process({});
        target_parser.parse(std::move(dma_specs));
        return target_parser.AST;
    }

    void fcore_cc::merge_includes(const std::vector<std::shared_ptr<ast_code_block>>& i) {

        std::set<std::string> target_functions;
        for(auto & node: hl_ast->get_content()){
            if(node->node_type == hl_ast_node_type_function_def){
                target_functions.insert(std::static_pointer_cast<ast_function_def>(node)->get_name());
            }
        }

        for(auto &include:i){
            for(auto &node:include->get_content()){
                if(node->node_type == hl_ast_node_type_function_def){
                    if(!target_functions.contains(std::static_pointer_cast<ast_function_def>(node)->get_name())){
                        hl_ast->add_content(node);
                    }
                }
            }
        }

    }

    void fcore_cc::analyze_program_length(std::shared_ptr<struct instruction_count> c) {

        length_info.per_channel_portion = c->regular + c->efi * info.efi_lenght + c->load;

        length_info.fixed_portion = c->stop * info.stop_duration +
                                    info.fixed_core_overhead + c->load*info.load_overhead;
    }

    void fcore_cc::insert_stop(instruction_stream &program_stream) {
        if(std::holds_alternative<independent_instruction>(program_stream.last().get_content())){
            auto opcode = program_stream.last().get_opcode();
            if(opcode != opcode_stop){
                program_stream.push_back(instruction_variant(independent_instruction(opcode_stop)));
            }
        } else {
            program_stream.push_back(instruction_variant(independent_instruction(opcode_stop)));
        }

    }

    void fcore_cc::flush_pipeline(instruction_stream &program_stream) {

        auto last_instruction_idx = program_stream.size()-2;
        for(int i =program_stream.size()-2;i>0; i--){
            if (std::holds_alternative<independent_instruction>(program_stream[i].get_content())) {
                auto instr = program_stream.last().get_opcode();
                if(instr != opcode_nop){
                    last_instruction_idx = i;
                    break;
                }
            }  else {
                last_instruction_idx = i;
                break;
            }
        }
        auto last_instruction_latency = fcore_execution_latencies[program_stream[last_instruction_idx].get_opcode()];
        auto present_nops = program_stream.size()-2-last_instruction_idx;
        for(int i = 0; i< last_instruction_latency; i++) {
            program_stream.insert(instruction_variant(independent_instruction(opcode_nop)), -1);
        }
    }

    nlohmann::json fcore_cc::dump_iom_map(std::map<std::string, core_iom> &map) {
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

    std::map<std::string, core_iom> fcore_cc::load_iom_map(const nlohmann::json &raw_map) {
        std::map<std::string, core_iom> ret;

        for(auto &obj:raw_map.items()){
            core_iom iom;
            auto item = obj.value();

            std::vector<uint32_t> addr;

            if(item["address"].is_array()){
                addr = (std::vector<uint32_t>)item["address"];
            } else {
                addr = {item["address"]};
            }

            iom.address = addr;
            iom.type = core_iom_type_translator[item["type"]];
            iom.common_io = item["common_io"];
            ret[obj.key()] = iom;
        }

        return ret;
    }

}