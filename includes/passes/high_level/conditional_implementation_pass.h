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

#ifndef FCORE_TOOLCHAIN_CONDITIONAL_IMPLEMENTATION_PASS_H
#define FCORE_TOOLCHAIN_CONDITIONAL_IMPLEMENTATION_PASS_H

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

#include "tools/expression_evaluator.hpp"

class conditional_implementation_pass : public pass_base<hl_ast_node> {
public:
    conditional_implementation_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};

private:
    std::shared_ptr<hl_ast_operand> find_variable_definition(const std::shared_ptr<hl_ast_node>& subexpr, const std::shared_ptr<hl_ast_node>& item,
                                                             const std::vector<std::shared_ptr<hl_ast_node>>& prog_content);
    std::shared_ptr<hl_ast_operand> get_operands(const std::shared_ptr<hl_ast_node>& subexpr, const std::shared_ptr<hl_ast_node>& item,
                                                 const std::vector<std::shared_ptr<hl_ast_node>>& prog_content);

    std::vector<std::shared_ptr<hl_ast_node>> process_block_by_type(const std::shared_ptr<hl_ast_node>& node, const std::shared_ptr<hl_ast_node>& subtree);
    std::vector<std::shared_ptr<hl_ast_node>> process_conditional(const std::shared_ptr<hl_ast_conditional_node>& node, const std::shared_ptr<hl_ast_node>& subtree);
    std::vector<std::shared_ptr<hl_ast_node>> process_loop(const std::shared_ptr<hl_ast_loop_node>& node, const std::shared_ptr<hl_ast_node>& subtree);
};


#endif //FCORE_TOOLCHAIN_CONDITIONAL_IMPLEMENTATION_PASS_H
