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
        std::shared_ptr<instruction> apply_pass(std::shared_ptr<instruction> element, uint32_t n) override;

    private:
        void map_ternaries(std::shared_ptr<instruction> element);
        void map_conditions_source(std::shared_ptr<instruction> element);
        void update_conditions_map(std::string s);
        std::shared_ptr<instruction> reduce(std::shared_ptr<instruction> element);
        std::shared_ptr<instruction> reduce_register_instr(std::shared_ptr<register_instruction> element);
        std::shared_ptr<instruction> reduce_conversion_instr(std::shared_ptr<conversion_instruction>);
        std::shared_ptr<instruction> reduce_load_instr(std::shared_ptr<load_constant_instruction> node);
        std::shared_ptr<instruction> reduce_ternary_instr(std::shared_ptr<ternary_instruction> node);


        uint32_t instr_ctr;
        uint32_t last_pass;
        std::unordered_map<std::string, uint32_t> ternaries_map;
        std::unordered_map<std::string, std::shared_ptr<variable>> substitution_map;
        std::unordered_map<std::string, uint32_t> conditions_map;
    };
}



#endif //FCORE_TOOLCHAIN_TERNARY_REDUCTION_HPP
