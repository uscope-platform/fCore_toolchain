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


fcore_cc::fcore_cc(std::string &path, std::vector<std::string> &includes, bool print_debug, int dump_ast_level) : hl_manager(dump_ast_level),
                                                                                                                  ll_manager(dump_ast_level) {
    std::shared_ptr<define_map> defines_map = std::make_shared<define_map>();
    error_code = "";
    try{
        C_language_parser target_parser(path, defines_map);
        target_parser.pre_process({});
        target_parser.parse();
        hl_ast = target_parser.AST;
        std::unordered_map<std::string, std::shared_ptr<variable>> iom = target_parser.get_iom_map();

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

        writer.process_stream(program_stream, print_debug);

    } catch(std::runtime_error &e){
        error_code = e.what();
    }
}


std::vector<uint32_t> fcore_cc::get_hexfile(bool endian_swap) {
    return writer.generate_hex(endian_swap);
}

std::string fcore_cc::get_errors() {
    return error_code;
}

std::vector<std::string> fcore_cc::get_verilog_memfile() {
    return writer.generate_mem();
}

void fcore_cc::write_hexfile(const std::string &ouput_file) {
    writer.write_hex_file(ouput_file);
}

void fcore_cc::write_verilog_memfile(const std::string &ouput_file) {
    writer.write_mem_file(ouput_file);
}

uint32_t fcore_cc::get_program_size() {
    return writer.get_program_size();
}

uint32_t fcore_cc::get_inst_count() {
    int program_lenght = ll_manager.analysis_passes["instruction_counting"]->get_analysis_result()[0];
    float program_runtime = (float) program_lenght*0.01f;
    std::cout << "The compiled program is " << program_lenght << "instructions long"<< std::endl;
    std::cout << "Runtime at the standard frequency of 100 MHz will be of " << program_runtime << " µS"<< std::endl;
    return 0;
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

