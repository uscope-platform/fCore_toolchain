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
