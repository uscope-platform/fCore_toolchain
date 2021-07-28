// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_VARIABLE_MAPPING_HPP
#define FCORE_TOOLCHAIN_VARIABLE_MAPPING_HPP

#include "stream_pass_base.hpp"
#include "tools/variable_map.hpp"
#include "tools/variable.hpp"
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
