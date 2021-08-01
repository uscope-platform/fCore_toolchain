// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.


#include "fcore_cc.hpp"


fcore_cc::fcore_cc(std::istream &input, std::vector<std::string> &includes, bool print_debug) {
    std::shared_ptr<define_map> defines_map = std::make_shared<define_map>();
    error_code = "";
    try{
        C_language_parser target_parser(input, defines_map);
        target_parser.pre_process({}, {});
        target_parser.parse();
        hl_ast = target_parser.AST;
        std::string ep = "main";
        hl_manager = create_hl_pass_manager(ep,{});
        hl_manager.run_morphing_passes(hl_ast);

        high_level_ast_lowering tranlator;

        tranlator.set_input_ast(hl_ast);
        tranlator.translate();
        ll_ast = tranlator.get_output_ast();

        ll_manager = create_ll_pass_manager();
        ll_manager.run_morphing_passes(ll_ast);

        instruction_stream program_stream = instruction_stream_builder::build_stream(ll_ast);

        stream_pass_manager sman;
        program_stream = sman.process_stream(program_stream);

        writer.process_stream(program_stream, false);

    } catch(std::runtime_error &e){
        error_code = e.what();
        int i = 0;
    } catch (...) {
        throw std::runtime_error("OH SNAP!");
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

