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

#ifndef UNINITIALIZED_VARIABLE_DETECTION_HPP
#define UNINITIALIZED_VARIABLE_DETECTION_HPP

#include "passes/instruction_stream/stream_pass_base.hpp"

#include <unordered_set>

namespace fcore{

    class uninitialized_variable_detection : public stream_pass_base{
    public:
        explicit uninitialized_variable_detection();
        std::optional<instruction_variant> apply_pass(const instruction_variant &element, uint32_t n) override;

    private:
        void process_ternary(const ternary_instruction &instr);
        void process_load_constant(const load_constant_instruction &instr);
        void process_register_instruction(const register_instruction &instr);
        void process_conversion_instruction(const conversion_instruction &instr);
        void process_variable(const std::shared_ptr<variable> &var);
        std::unordered_set<std::string> initialized_variables;
    };


}


#endif //UNINITIALIZED_VARIABLE_DETECTION_HPP
