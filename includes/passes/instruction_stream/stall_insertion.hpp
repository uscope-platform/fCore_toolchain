//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_STALL_INSERTION_H
#define FCORE_TOOLCHAIN_STALL_INSERTION_H


#include "fCore_isa.hpp"
#include "stream_pass_base.hpp"

namespace fcore{

    class stall_insertion : public stream_pass_base{
    public:
        stall_insertion(int n_channels);

        std::vector<instruction_variant> apply_vector_mutable_pass(instruction_variant &element, uint32_t n_pass, uint32_t n_instuction) override;

    private:
        uint8_t get_latency(opcode_table_t opcode){
            auto del = fcore_execution_latencies[opcode];
            if ((active_channels-1)>del) return  0;
            return del - (active_channels-1);
        }
        void get_stalls(uint8_t reg, std::vector<instruction_variant> &instructions);
        void advance_tracker(int exclusion);
        std::vector<instruction_variant> process(const register_instruction &node);
        std::vector<instruction_variant> process(const conversion_instruction &node);
        std::vector<instruction_variant> process(const load_constant_instruction &node);
        std::vector<instruction_variant> process(const ternary_instruction &node);

        std::array<uint8_t, 1<<fcore_register_address_width> operations_tracker;
        uint8_t active_channels;
    };



}

#endif //FCORE_TOOLCHAIN_STALL_INSERTION_H