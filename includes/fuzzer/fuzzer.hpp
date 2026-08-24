//  Copyright  2026 University of Nottingham
//  Author: Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#ifndef FCORE_TOOLCHAIN_FUZZER_HPP
#define FCORE_TOOLCHAIN_FUZZER_HPP

#include <cstdint>
#include <vector>
#include <map>
#include <set>

#include "fuzzer/fuzzer_rng.hpp"
#include "fCore_isa.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"
#include "backend/binary_generator.hpp"

namespace fcore{
    struct fuzzer_config {
        uint8_t min_inputs = 1;
        uint8_t max_inputs = 5;
        uint8_t active_regs = 5;
        uint8_t min_program_size = 3;
        uint16_t max_program_size = 150;
        uint32_t rng_seed;
        std::pair<float, float> rng_float_params;
    };

    struct fuzzing_package {
        std::vector<uint32_t> binary;
        std::map<uint32_t, float> inputs;
    };

    class fuzzer {
    public:
        explicit fuzzer(const fuzzer_config &config);
        fuzzing_package generate_binary();
    private:
        std::vector<uint32_t> compile_binary(const instruction_stream &s);
        instruction_variant generate_instruction(uint32_t dest, std::vector<uint32_t>& active_registers);
        conversion_instruction generate_conversion_instruction(opcode_table_t op, uint32_t dest, std::vector<unsigned int>& available_inputs);
        register_instruction generate_register_instruction(opcode_table_t op, uint32_t dest, std::vector<unsigned int>& available_inputs);
        load_constant_instruction generate_constant_instruction(opcode_table_t op, uint32_t dest, std::vector<unsigned int>& available_inputs);
        ternary_instruction generate_ternary_instruction(opcode_table_t op, uint32_t dest, std::vector<unsigned int>& available_inputs);
        std::string generate_register(std::vector<unsigned int>& available_inputs);
        std::vector<opcode_table_t> opcodes = {
            // 0 inputs needed
            opcode_ldc,
            // 1 input needed
            opcode_itf, opcode_fti, opcode_not, opcode_rec, opcode_abs, opcode_popcnt, opcode_xor,
            // 2 inputs needed
            opcode_add, opcode_sub, opcode_mul, opcode_bgt, opcode_ble, opcode_beq,
            opcode_bne, opcode_and, opcode_or, opcode_satp, opcode_satn, opcode_bset, opcode_bsel,
            // 3 inputs needed
            opcode_csel
        };
        std::array<size_t, 4> opcode_inputs_bounds = {1, 8, 21, 22};
        fuzzer_rng rng;
        fuzzer_config config;
    };

}
#endif //FCORE_TOOLCHAIN_FUZZER_HPP
