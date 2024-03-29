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
        std::shared_ptr<ll_instruction_node> apply_pass(std::shared_ptr<ll_instruction_node> element, uint32_t n) override;
    private:
        std::shared_ptr<ll_instruction_node> process_reg_instr(std::shared_ptr<ll_register_instr_node> node);
        std::shared_ptr<ll_instruction_node> process_conv_instr(std::shared_ptr<ll_conversion_instr_node> node);
        std::shared_ptr<ll_instruction_node> process_load_instr(std::shared_ptr<ll_load_constant_instr_node> node);
        std::shared_ptr<ll_instruction_node> process_ternary_instr(const std::shared_ptr<ll_ternary_instr_node>& node);
    };
}


#endif //FCORE_TOOLCHAIN_BOUND_REGISTER_MAPPING_PASS_HPP
