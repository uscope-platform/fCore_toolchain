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

#ifndef FCORE_TOOLCHAIN_HL_PASS_MANAGER_HPP
#define FCORE_TOOLCHAIN_HL_PASS_MANAGER_HPP

#include <gtest/gtest_prod.h>

#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_expression_node.hpp"
#include "ast/high_level/hl_ast_operand.hpp"
#include "ast/high_level/hl_function_call_node.hpp"
#include "ast/high_level/hl_function_def_node.hpp"
#include "ast/high_level/hl_definition_node.hpp"

#include "passes/pass_manager_base.hpp"
#include "passes/pass_base.hpp"


class hl_pass_manager : public pass_manager_base<hl_ast_node> {
public:
    void run_morphing_pass( std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass) override;
    void run_morphing_pass_group(std::shared_ptr<hl_ast_node> &subtree, const std::vector<std::shared_ptr<pass_base<hl_ast_node>>>& group) override;

    std::shared_ptr<hl_ast_node> run_global_pass(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);

    std::shared_ptr<hl_ast_node> process_leaves(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::vector<std::shared_ptr<hl_ast_node>> process_nodes(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);

private:
    FRIEND_TEST(HlPassesTest, functionMapping);
    std::shared_ptr<hl_ast_node> process_terminal_by_type(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_expression_node> process_expression(const std::shared_ptr<hl_expression_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    static std::shared_ptr<hl_ast_operand> process_operand(const std::shared_ptr<hl_ast_operand> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_ast_node> process_function_call(const std::shared_ptr<hl_function_call_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_definition_node> process_definition(const std::shared_ptr<hl_definition_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);

};


#endif //FCORE_TOOLCHAIN_HL_PASS_MANAGER_HPP
