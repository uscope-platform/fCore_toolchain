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


#ifndef FCORE_TOOLCHAIN_BOUND_REGISTER_ASSIGNMENT_HPP
#define FCORE_TOOLCHAIN_BOUND_REGISTER_ASSIGNMENT_HPP

#include "stream_pass_base.hpp"

namespace fcore {
    class bound_register_assignment : public stream_pass_base {
    public:
        bound_register_assignment();
        std::optional<instruction_variant> apply_mutable_pass(instruction_variant &element, uint32_t n)  override;
    private:

        std::optional<instruction_variant> process(const pseudo_instruction &node);
        std::optional<instruction_variant> process(const register_instruction &node);
        std::optional<instruction_variant> process(const conversion_instruction &node);
        std::optional<instruction_variant> process(const load_constant_instruction &node);
        std::optional<instruction_variant> process(const ternary_instruction &node);
        int get_register_number(std::string n);
    };
}



#endif //FCORE_TOOLCHAIN_BOUND_REGISTER_ASSIGNMENT_HPP