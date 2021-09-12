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

#include "fcore_dis.hpp"

fcore_dis::fcore_dis(std::istream &input, bin_loader_input_type_t in_type) {
    error_code = "";
    try{

        binary_loader dis(input, in_type);
        std::shared_ptr<ll_ast_node> ast = dis.get_ast();

        instruction_stream program_stream = instruction_stream_builder::build_stream(ast);
        std::unordered_map<std::string, std::shared_ptr<variable>> iom;

        stream_pass_manager sman(iom);
        program_stream = sman.process_stream(program_stream);
        gen = std::make_unique<assembly_generator>(program_stream);

    } catch(std::runtime_error &e){
        error_code = e.what();
    }
}

std::string fcore_dis::get_errors() {
    return error_code;
}

void fcore_dis::write_json(const std::string &output_file) {
    nlohmann::json j;
    j["error_code"] = error_code;
    if(error_code.empty()){
        j["disassembled_program"] = gen->get_program();
    } else{
        j["disassembled_program"] = "";
    }
    std::string str = j.dump();
    std::ofstream ss(output_file);
    ss<<str;
    ss.close();
}

std::string fcore_dis::get_disassenbled_program() {
    return gen->get_program();
}

void fcore_dis::write_disassembled_program(const std::string &output_file) {
    gen->write_program(output_file);
}


