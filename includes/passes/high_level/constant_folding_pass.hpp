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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.05/07/2021.
//


#ifndef FCORE_TOOLCHAIN_CONSTANT_FOLDING_PASS_HPP
#define FCORE_TOOLCHAIN_CONSTANT_FOLDING_PASS_HPP

#include "passes/pass_base.hpp"
#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_expression_node.hpp"
#include "tools/expression_evaluator.hpp"


class constant_folding_pass : public  pass_base<hl_ast_node> {
public:
    constant_folding_pass();
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return LEAF_PASS;};
};


#endif //FCORE_TOOLCHAIN_CONSTANT_FOLDING_PASS_HPP
