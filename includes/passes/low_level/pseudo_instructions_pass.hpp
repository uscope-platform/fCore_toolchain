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
#ifndef FCORE_TOOLCHAIN_PSEUDO_INSTRUCTIONS_PASS_HPP
#define FCORE_TOOLCHAIN_PSEUDO_INSTRUCTIONS_PASS_HPP

#include <memory>
#include "data_structures/low_level_ast/ll_instruction_node.hpp"
#include "data_structures/low_level_ast/ll_ast_node.hpp"
#include "passes/pass_base.hpp"
#include "fCore_isa.hpp"


class pseudo_instructions_pass: public pass_base<ll_ast_node> {
public:
    pseudo_instructions_pass();
    std::shared_ptr<ll_ast_node> process_leaf(std::shared_ptr<ll_ast_node> element) override ;
    int get_pass_type() override { return LEAF_PASS;};
};


#endif //FCORE_TOOLCHAIN_PSEUDO_INSTRUCTIONS_PASS_HPP
