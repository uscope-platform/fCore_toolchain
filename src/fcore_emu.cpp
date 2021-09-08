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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/


#include "fcore_emu.hpp"

fcore_emu::fcore_emu(std::istream &input, bin_loader_input_type_t in_type) {
    error_code = "";
    try{

        binary_loader dis(input, in_type);
        std::shared_ptr<ll_ast_node> ast = dis.get_ast();

        instruction_stream program_stream = instruction_stream_builder::build_stream(ast);

        stream_pass_manager sman;
        program_stream = sman.process_stream(program_stream);
        emulator backend(program_stream);
        backend.run_program();
        memory = backend.get_memory();

    } catch(std::runtime_error &e){
        error_code = e.what();
        int i = 0;
    }
}

void fcore_emu::write_json(const std::string &output_file) {
    nlohmann::json j;
    j["registers"] = memory;

    std::string str = j.dump();
    std::ofstream ss(output_file);
    ss<<str;
    ss.close();
}
