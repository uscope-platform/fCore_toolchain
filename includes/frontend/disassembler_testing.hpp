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

#ifndef FCORE_TOOLCHAIN_DISASSEMBLER_TESTING_HPP
#define FCORE_TOOLCHAIN_DISASSEMBLER_TESTING_HPP

#include <istream>

#include "data_structures/low_level_ast/ll_ast_node.hpp"

typedef enum {
    disassembler_mem_input = 0,
    disassembler_hex_input = 1
} disassembler_input_type_t;

class disassembler_testing {
public:
    disassembler_testing(std::istream &stream, disassembler_input_type_t in_type);
    std::shared_ptr<ll_ast_node> get_ast() {return ast_root;};
private:
    std::shared_ptr<ll_ast_node> ast_root;
};


#endif //FCORE_TOOLCHAIN_DISASSEMBLER_TESTING_HPP
