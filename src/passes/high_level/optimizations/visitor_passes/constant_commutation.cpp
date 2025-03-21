

//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "passes/high_level/optimizations/visitor_passes/constant_commutation.hpp"

#include <gmp.h>

namespace fcore {
    constant_commutation::constant_commutation() : pass_base("constant commutation"){
    }

    std::shared_ptr<hl_code_block> constant_commutation::process_global(std::shared_ptr<hl_code_block> element,
        const std::vector<std::shared_ptr<hl_definition_node>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_expression = process_expression;
        auto processed_tree = visitor.visit(ops, element);
        return processed_tree;

    }

    std::vector<std::shared_ptr<hl_ast_node>> constant_commutation::process_expression(
        const std::shared_ptr<hl_expression_node>& exp) {
        switch(exp->get_type()) {
            case expr_add:
                return process_expression_by_type(exp, expr_add, expr_sub);
            case expr_sub:
                return process_expression_by_type(exp, expr_sub, expr_add);
            case expr_mult:
                return process_expression_by_type(exp, expr_mult, expr_mult);
            default:
                return {exp};
        }
    }

    std::vector<std::shared_ptr<hl_ast_node>> constant_commutation::process_expression_by_type(
        const std::shared_ptr<hl_expression_node>& exp,
        expression_type_t main_type,
        expression_type_t additional_type
    ) {
        if(exp->get_type() != main_type) return {exp};
        if(exp->get_rhs()->node_type  == exp->get_lhs().value()->node_type) return {exp};

        std::shared_ptr<hl_ast_operand> lhs_op, rhs_op, parent_op;

        expression_type_t child_type;

        if(exp->get_rhs()->node_type == hl_ast_node_type_operand) {
            auto child_exp = std::static_pointer_cast<hl_expression_node>(exp->get_lhs().value());
            child_type = child_exp->get_type();
            if(child_exp->is_immediate() || child_exp->is_constant() || child_exp->is_unary()) {
                return {exp};
            }
            if(child_type != main_type && child_type !=  additional_type) return {exp};
            if(child_exp->get_rhs()->node_type != hl_ast_node_type_operand || child_exp->get_lhs().value()->node_type != hl_ast_node_type_operand)
                return {exp};
            parent_op = std::static_pointer_cast<hl_ast_operand>(exp->get_rhs());
            if(!parent_op->is_constant() || child_exp->is_constant())
                return {exp};

            auto [lhs, rhs] = process_right_expression(exp);

            rhs_op = rhs;
            lhs_op = lhs;
        } else {
            auto child_exp = std::static_pointer_cast<hl_expression_node>(exp->get_rhs());
            if(child_exp->is_immediate() || child_exp->is_constant() || child_exp->is_unary()) {
                return {exp};
            }
            child_type = child_exp->get_type();

            if(child_type != main_type && child_type !=  additional_type) return {exp};
            if(child_exp->get_rhs()->node_type != hl_ast_node_type_operand || child_exp->get_lhs().value()->node_type != hl_ast_node_type_operand)
                return {exp};
            parent_op = std::static_pointer_cast<hl_ast_operand>(exp->get_lhs().value());
            if(!parent_op->is_constant() || child_exp->is_constant())
                return {exp};

            auto [lhs, rhs] =  process_left_expression(exp);
            rhs_op = rhs;
            lhs_op = lhs;
        }

        std::shared_ptr<hl_expression_node> return_expr = std::make_shared<hl_expression_node>(child_type);

        std::shared_ptr<hl_expression_node> inner_exp = std::make_shared<hl_expression_node>(main_type);
        inner_exp->set_lhs(parent_op);
        inner_exp->set_rhs(rhs_op);
        return_expr->set_rhs(inner_exp);
        return_expr->set_lhs(lhs_op);
        return {return_expr};
    }


    std::pair<std::shared_ptr<hl_ast_operand>, std::shared_ptr<hl_ast_operand>> constant_commutation::process_right_expression(
        std::shared_ptr<hl_expression_node> exp) {

        std::shared_ptr<hl_expression_node> child_exp_side = std::static_pointer_cast<hl_expression_node>(exp->get_lhs().value());
        std::shared_ptr<hl_ast_operand> parent_operand_side =  std::static_pointer_cast<hl_ast_operand>(exp->get_rhs());;


        auto child_rhs = std::static_pointer_cast<hl_ast_operand>(child_exp_side->get_rhs());
        auto child_lhs = std::static_pointer_cast<hl_ast_operand>(child_exp_side->get_lhs().value());

        if(child_lhs->is_constant() && !child_rhs->is_constant()) {
            return {child_rhs, child_lhs};
        }

        return {child_lhs, child_rhs};
    }

    std::pair<std::shared_ptr<hl_ast_operand>, std::shared_ptr<hl_ast_operand>> constant_commutation::process_left_expression(
        std::shared_ptr<hl_expression_node> exp) {

            std::shared_ptr<hl_expression_node> child_exp_side = std::static_pointer_cast<hl_expression_node>(exp->get_rhs());
            std::shared_ptr<hl_ast_operand> parent_operand_side =  std::static_pointer_cast<hl_ast_operand>(exp->get_lhs().value());

            auto child_rhs = std::static_pointer_cast<hl_ast_operand>(child_exp_side->get_rhs());
            auto child_lhs = std::static_pointer_cast<hl_ast_operand>(child_exp_side->get_lhs().value());

            if(child_lhs->is_constant() && !child_rhs->is_constant()) {
                return {child_rhs, child_lhs};
            }
            return {child_lhs, child_rhs};

    }

}

