// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#include "fcore_cc.hpp"


fcore_cc::fcore_cc(std::istream &input, std::vector<std::string> &includes) {
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    std::shared_ptr<define_map> defines_map = std::make_shared<define_map>();

    C_language_parser target_parser(input, variables_map, defines_map);
    target_parser.pre_process({}, {});
    target_parser.parse();
    AST = target_parser.AST;
    std::string ep = "main";
    manager = create_hl_pass_manager(ep, variables_map);
    manager.run_morphing_passes(AST);
    
}


std::vector<uint32_t> fcore_cc::get_hexfile(bool endian_swap) {
    return writer->generate_hex(endian_swap);
}

std::string fcore_cc::get_errors() {
    return error_code;
}

std::vector<std::string> fcore_cc::get_verilog_memfile() {
    return writer->generate_mem();
}

void fcore_cc::write_hexfile(const std::string &ouput_file) {
    writer->write_hex_file(ouput_file);
}

void fcore_cc::write_verilog_memfile(const std::string &ouput_file) {
    writer->write_mem_file(ouput_file);
}

uint32_t fcore_cc::get_program_size() {
    return writer->get_program_size();
}

uint32_t fcore_cc::get_inst_count() {
    int program_lenght = manager.analysis_passes["instruction_counting"]->get_analysis_result()[0];
    float program_runtime = (float) program_lenght*0.01f;
    std::cout << "The compiled program is " << program_lenght << "instructions long"<< std::endl;
    std::cout << "Runtime at the standard frequency of 100 MHz will be of " << program_runtime << " µS"<< std::endl;
    return 0;
}
