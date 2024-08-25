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
// limitations under the License.02/07/2021.
//

#ifndef FCORE_TOOLCHAIN_BOUND_REGISTER_MAPPING_PASS_HPP
#define FCORE_TOOLCHAIN_BOUND_REGISTER_MAPPING_PASS_HPP

#include "passes/instruction_stream/stream_pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{
    class bound_register_mapping_pass : public stream_pass_base{
    public:
        bound_register_mapping_pass();
        std::optional<instruction_variant> apply_pass(const instruction_variant &element, uint32_t n) override;
    private:
        std::optional<instruction_variant> process_reg_instr(const register_instruction &node);
        std::optional<instruction_variant> process_conv_instr(const conversion_instruction &node);
        std::optional<instruction_variant> process_load_instr(const load_constant_instruction &node);
        std::optional<instruction_variant> process_ternary_instr(const ternary_instruction& node);
    };
}


#endif //FCORE_TOOLCHAIN_BOUND_REGISTER_MAPPING_PASS_HPP
