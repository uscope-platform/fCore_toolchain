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

#include "data_structures/instruction_stream/instruction_stream.hpp"
#include "data_structures/executable.hpp"
#include "fCore_isa.hpp"
namespace fcore{

    typedef enum {
        bin_loader_mem_input = 0,
        bin_loader_hex_input = 1
    } bin_loader_input_type_t;

    class binary_loader {
    public:
        binary_loader(std::istream &stream, bin_loader_input_type_t in_type);
        explicit binary_loader(const std::vector<uint32_t> &file_content);
        void load_program(const std::vector<uint32_t> &file_content);
        instruction_stream get_program_stream() {return program_stream;};
        void construct_ast(const std::vector<uint32_t> &program);
        static instruction_variant process_register_instr(uint32_t instruction);
        static instruction_variant process_ternary_instr(uint32_t instruction);
        static instruction_variant process_independent_instruction(uint32_t instruction);
        std::pair<instruction_variant, instruction_variant> process_load_constant(uint32_t instruction, uint32_t raw_constant);
        static instruction_variant process_conversion_instr(uint32_t instruction);
        static uint32_t to_littleEndian(uint32_t in_num);
        std::unordered_map<uint16_t, uint16_t> get_io_mapping();
        std::set<io_map_entry> get_io_mapping_set();
    private:
        instruction_stream program_stream;
        std::set<std::pair<uint16_t , uint16_t>> io_mapping;
    };
}



#endif //FCORE_TOOLCHAIN_BINARY_LOADER_HPP
