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

#ifndef FCORE_TOOLCHAIN_VARIABLE_MAPPING_HPP
#define FCORE_TOOLCHAIN_VARIABLE_MAPPING_HPP

#include "stream_pass_base.hpp"
#include "tools/variable_map.hpp"
#include "data_structures/common/variable.hpp"
#include "data_structures/low_level_ast/low_level_ast.hpp"

class variable_mapping : public stream_pass_base {
public:
    explicit variable_mapping(std::shared_ptr<variable_map> &v);
    std::shared_ptr<ll_instruction_node> apply_pass(std::shared_ptr<ll_instruction_node> element) override;

    void map_register_inst(const std::shared_ptr<ll_register_instr_node>& instr);
    void map_conv_instr(const std::shared_ptr<ll_conversion_instr_node>& instr);
    void map_load_const_instr(const std::shared_ptr<ll_load_constant_instr_node>& instr);

private:
    std::shared_ptr<variable_map> vmap;
};


#endif //FCORE_TOOLCHAIN_VARIABLE_MAPPING_HPP
