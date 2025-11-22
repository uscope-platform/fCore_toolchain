//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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


#ifndef FCORE_TOOLCHAIN_TERNARY_REDUCTION_HPP
#define FCORE_TOOLCHAIN_TERNARY_REDUCTION_HPP

#include "passes/instruction_stream/stream_pass_base.hpp"

namespace fcore{
    class ternary_reduction : public stream_pass_base{
    public:
        ternary_reduction();
        std::optional<instruction_variant> apply_mutable_pass(instruction_variant &element, uint32_t n) override;
    private:
        void map_ternaries(const instruction_variant &element);
        void map_conditions_source(const instruction_variant &element);
        void update_conditions_map(std::string s);
        std::optional<instruction_variant> reduce(instruction_variant &element);
        std::optional<instruction_variant> reduce_register_instr(register_instruction &element);
        std::optional<instruction_variant> reduce_conversion_instr(conversion_instruction &node);
        std::optional<instruction_variant> reduce_load_instr(load_constant_instruction &node);
        std::optional<instruction_variant> reduce_ternary_instr(ternary_instruction &node);


        uint32_t instr_ctr;
        uint32_t last_pass;
        std::map<std::string, uint32_t> ternaries_map;
        std::map<std::string, std::shared_ptr<variable>> substitution_map;
        std::map<std::string, uint32_t> conditions_map;
    };
}



#endif //FCORE_TOOLCHAIN_TERNARY_REDUCTION_HPP
