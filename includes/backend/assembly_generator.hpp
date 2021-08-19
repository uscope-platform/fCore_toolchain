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

#ifndef FCORE_TOOLCHAIN_ASSEMBLY_GENERATOR_H
#define FCORE_TOOLCHAIN_ASSEMBLY_GENERATOR_H

#include <fstream>

#include "data_structures/instruction_stream.hpp"

class assembly_generator {
public:
    explicit assembly_generator(const instruction_stream& stream);
    void write_program(const std::string& filename);
    std::string get_program() {return  program;};
private:
    std::string program;
};


#endif //FCORE_TOOLCHAIN_ASSEMBLY_GENERATOR_H
