//
// Created by fils on 06/07/2021.
//

#ifndef FCORE_HAS_HL_PASS_MANAGER_H
#define FCORE_HAS_HL_PASS_MANAGER_H

#include <gtest/gtest_prod.h>

#include "ast/high_level/hl_ast_node.h"
#include "ast/high_level/hl_expression_node.h"
#include "ast/high_level/hl_ast_operand.h"
#include "ast/high_level/hl_function_call_node.h"
#include "ast/high_level/hl_function_def_node.h"
#include "ast/high_level/hl_definition_node.h"

#include "passes/pass_manager_base.hpp"
#include "passes/pass_base.hpp"


class hl_pass_manager : public pass_manager_base<hl_ast_node> {
public:
    std::shared_ptr<hl_ast_node> run_morphing_pass(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass) override;
    std::shared_ptr<hl_ast_node> run_global_pass(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass) override;

    std::shared_ptr<hl_ast_node> process_leaves(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::vector<std::shared_ptr<hl_ast_node>> process_nodes(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);

private:
    FRIEND_TEST(HlPassesTest, functionMapping);
    std::shared_ptr<hl_ast_node> process_terminal_by_type(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_expression_node> process_expression(const std::shared_ptr<hl_expression_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    static std::shared_ptr<hl_ast_operand> process_operand(const std::shared_ptr<hl_ast_operand> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_function_call_node> process_function_call(const std::shared_ptr<hl_function_call_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);
    std::shared_ptr<hl_definition_node> process_definition(const std::shared_ptr<hl_definition_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);

};


#endif //FCORE_HAS_HL_PASS_MANAGER_H
