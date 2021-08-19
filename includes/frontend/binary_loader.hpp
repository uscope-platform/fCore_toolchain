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

#ifndef FCORE_TOOLCHAIN_BINARY_LOADER_HPP
#define FCORE_TOOLCHAIN_BINARY_LOADER_HPP

#include <istream>

#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "fCore_isa.hpp"

typedef enum {
    bin_loader_mem_input = 0,
    bin_loader_hex_input = 1
} bin_loader_input_type_t;

class binary_loader {
public:
    binary_loader(std::istream &stream, bin_loader_input_type_t in_type);
    std::shared_ptr<ll_ast_node> get_ast() {return ast_root;};
    void construct_ast(std::vector<uint32_t> &program);
    static std::shared_ptr<ll_ast_node> process_register_instr(uint32_t instruction);
    static std::shared_ptr<ll_ast_node> process_independent_instruction(uint32_t instruction);
    static std::shared_ptr<ll_ast_node> process_load_constant(uint32_t instruction, uint32_t raw_constant);
    static std::shared_ptr<ll_ast_node> process_conversion_instr(uint32_t instruction);
    static uint32_t to_littleEndiann(uint32_t in_num);
private:
    std::shared_ptr<ll_ast_node> ast_root;
};


#endif //FCORE_TOOLCHAIN_BINARY_LOADER_HPP
