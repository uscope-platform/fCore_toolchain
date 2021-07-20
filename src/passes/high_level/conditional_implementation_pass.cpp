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

#include "passes/high_level/conditional_implementation_pass.h"

conditional_implementation_pass::conditional_implementation_pass() : pass_base<hl_ast_node>("Conditional Implementation pass"){

}

std::shared_ptr<hl_ast_node> conditional_implementation_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::vector<std::shared_ptr<hl_ast_node>> body;

    for(auto item:element->get_content()){
        if(item->node_type == hl_ast_node_type_conditional){
            std::shared_ptr<hl_ast_conditional_node> node = std::static_pointer_cast<hl_ast_conditional_node>(item);
            std::shared_ptr<hl_expression_node> condition = std::static_pointer_cast<hl_expression_node>(node->get_condition());
            std::shared_ptr<hl_ast_operand> lhs_op = get_operands(condition->get_lhs(), node, element->get_content());
            std::shared_ptr<hl_ast_operand> rhs_op = get_operands(condition->get_rhs(), node, element->get_content());

            std::shared_ptr<hl_expression_node> const_cond_expr = std::make_shared<hl_expression_node>(condition->get_type());
            const_cond_expr->set_lhs(lhs_op);
            const_cond_expr->set_rhs(rhs_op);

            std::shared_ptr<hl_ast_operand> result_op = expression_evaluator::evaluate_expression(const_cond_expr);
            bool result;
            if(result_op->get_type() == integer_immediate_operand) result = result_op->get_int_value();
            if(result_op->get_type() == float_immediate_operand) result = result_op->get_float_val() == 1;

            if(result){
                std::vector<std::shared_ptr<hl_ast_node>> selected_block = node->get_if_block();
                body.insert(body.end(), selected_block.begin(), selected_block.end());
            } else if(node->has_else()){
                std::vector<std::shared_ptr<hl_ast_node>> selected_block = node->get_else_block();
                body.insert(body.end(), selected_block.begin(), selected_block.end());
            }
        } else {
            body.push_back(item);
        }
    }

    ret_val->set_content(body);
    return ret_val;
}

std::shared_ptr<hl_ast_operand>
conditional_implementation_pass::find_variable_definition(const std::shared_ptr<hl_ast_node>& subexpr,
                                                          const std::shared_ptr<hl_ast_node>& item,
                                                          const std::vector<std::shared_ptr<hl_ast_node>>& prog_content) {
    std::shared_ptr<hl_ast_operand> retval;
    if(subexpr->node_type == hl_ast_node_type_expr){
        throw std::runtime_error("OH SNAP! Nested subexpression handling is not implemented yet");
    } else {
        std::shared_ptr<hl_ast_operand> variable = std::static_pointer_cast<hl_ast_operand>(subexpr);
        for(const auto& i: prog_content){
            if(i == item){
                throw std::runtime_error("ERROR: The value of all variables in a conditional condition must be defined before the expression itself");
            } else if (i->node_type == hl_ast_node_type_definition){
                std::shared_ptr<hl_definition_node> def = std::static_pointer_cast<hl_definition_node>(i);
                if(def->get_name() == variable->get_name()){
                    if(def->is_initialized()){
                        if(def->get_initializer()->node_type == hl_ast_node_type_operand){
                            return std::static_pointer_cast<hl_ast_operand>(def->get_initializer());
                        } else{
                            return find_variable_definition(def->get_initializer(), def, prog_content);
                        }
                    }
                }
            }
        }
    }

    return retval;
}

std::shared_ptr<hl_ast_operand>
conditional_implementation_pass::get_operands(const std::shared_ptr<hl_ast_node> &subexpr,
                                              const std::shared_ptr<hl_ast_node> &item,
                                              const std::vector<std::shared_ptr<hl_ast_node>> &prog_content) {
    std::shared_ptr<hl_ast_operand> retval;
    if(subexpr->node_type != hl_ast_node_type_operand){
        retval = find_variable_definition(subexpr, item, prog_content);
    } else{
        if(std::static_pointer_cast<hl_ast_operand>(subexpr)->get_type() == variable_operand){
            retval = find_variable_definition(subexpr, item, prog_content);
        } else {
            retval = std::static_pointer_cast<hl_ast_operand>(subexpr);
        }
    }
    return retval;
}


