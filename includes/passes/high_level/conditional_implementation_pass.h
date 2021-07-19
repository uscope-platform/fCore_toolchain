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
#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_ast_operand.hpp"
#include "ast/high_level/hl_ast_conditional_node.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "ast/high_level/hl_expression_node.hpp"

class conditional_implementation_pass : public pass_base<hl_ast_node> {
public:
    conditional_implementation_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    std::shared_ptr<hl_ast_operand> find_variable_definition(const std::shared_ptr<hl_ast_node>& subexpr, const std::shared_ptr<hl_ast_node>& item,
                                                             const std::vector<std::shared_ptr<hl_ast_node>>& prog_content);
    std::shared_ptr<hl_ast_operand> get_operands(const std::shared_ptr<hl_ast_node>& subexpr, const std::shared_ptr<hl_ast_node>& item,
                                                 const std::vector<std::shared_ptr<hl_ast_node>>& prog_content);
    int get_pass_type() override { return GLOBAL_PASS;};
};


#endif //FCORE_TOOLCHAIN_CONDITIONAL_IMPLEMENTATION_PASS_H
