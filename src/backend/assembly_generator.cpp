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

#include "backend/assembly_generator.hpp"

assembly_generator::assembly_generator(const instruction_stream &stream) {
    std::ostringstream disassembled_program;

    for(const auto& item:stream){
        disassembled_program << item->disassemble() << std::endl;
    }
    program = disassembled_program.str();
}

void assembly_generator::write_program(const std::string &filename) {
    std::ofstream output(filename);
    for(auto &instr:program){
        output << instr;
    }
}
