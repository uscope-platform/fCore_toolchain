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


fcore_cc::fcore_cc(std::string &path, std::vector<std::string> &inc, bool print_debug, int dump_lvl) : hl_manager(dump_lvl),
                                                                                                                  ll_manager(dump_lvl) {
    input_file =  path;
    includes = inc;
    logging = print_debug;
    dump_ast_level = dump_lvl;
}

void fcore_cc::compile() {
    try{
        std::unordered_map<std::string, std::shared_ptr<variable>> iom = construct_io_map();
        parse(iom);
        optimize(iom);

    } catch(std::runtime_error &e){
        error_code = e.what();
    }
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

void fcore_cc::parse(std::unordered_map<std::string, std::shared_ptr<variable>> &iom) {
    std::shared_ptr<define_map> defines_map = std::make_shared<define_map>();
    error_code = "";
    C_language_parser target_parser(input_file, defines_map);
    target_parser.pre_process({});
    target_parser.parse(iom);
    hl_ast = target_parser.AST;
}

void fcore_cc::optimize(std::unordered_map<std::string, std::shared_ptr<variable>> &iom) {
    std::string ep = "main";
    auto bindings_map = std::make_shared<std::unordered_map<std::string, memory_range_t>>();
    hl_manager = create_hl_pass_manager(ep,{}, dump_ast_level, iom, bindings_map);
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

    stream_pass_manager sman(iom, dump_ast_level, bindings_map);
    program_stream = sman.process_stream(program_stream);

    if(dump_ast_level>0) dump["stream"] = sman.get_dump();

    if(program_stream.empty()){
        program_stream.push_back(std::make_shared<ll_independent_inst_node>("stop"));
    }
    if(!program_stream.last()->is_stop()){
        program_stream.push_back(std::make_shared<ll_independent_inst_node>("stop"));
    }

    writer.process_stream(program_stream, iom, logging);
}

std::unordered_map<std::string, std::shared_ptr<variable>> fcore_cc::construct_io_map() {
    std::unordered_map<std::string, std::shared_ptr<variable>> io_map;
    for(auto &item:dma_io_map.items()){
        std::shared_ptr<variable> v = std::make_shared<variable>(item.key());
        if(item.value()["type"] =="input"){
            v->set_variable_class(variable_input_type);
        } else if(item.value()["type"]=="output"){
            v->set_variable_class(variable_output_type);
        } else if(item.value()["type"]=="memory"){
            v->set_variable_class(variable_memory_type);
        } else{
            const std::string& var_name = item.key();
            throw std::runtime_error("Unrecognized DMA IO variable: "+ var_name);
        }
        if(item.value()["address"].is_array()){
            std::vector<int> bound_reg = item.value()["address"];
            v->set_bound_reg_array(bound_reg);
        } else {
            int bound_reg = item.value()["address"];
            v->set_bound_reg(bound_reg);
        }
        io_map[item.key()] = v;
    }

    return io_map;
}
