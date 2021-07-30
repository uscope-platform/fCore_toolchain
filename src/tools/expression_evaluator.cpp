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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.29/06/2021.
//

#include "tools/expression_evaluator.hpp"


bool expression_evaluator::is_constant_expression(const std::shared_ptr<hl_expression_node>& expression) {
    bool retval = true;
    retval &= is_constant_subexpr(expression->get_rhs());
    if(!expression->is_unary()) retval &= is_constant_subexpr(expression->get_lhs());
    return retval;
}

bool expression_evaluator::is_constant_subexpr(const std::shared_ptr<hl_ast_node>& subex) {
    if(subex->node_type == hl_ast_node_type_operand){
        std::shared_ptr<hl_ast_operand> node = std::static_pointer_cast<hl_ast_operand>(subex);
        if(node->get_type() == var_type_scalar ||  node->get_type() == var_type_array){
            return false;
        } else{
            return true;
        }
    } else{
        return is_constant_expression(std::static_pointer_cast<hl_expression_node>(subex));
    }
}

std::shared_ptr<hl_ast_operand>
expression_evaluator::evaluate_expression(std::shared_ptr<hl_expression_node> expression) {
    if(expression->is_unary()){
        return evaluate_unary_expression(expression);
    } else {
        return evaluate_regular_expression(expression);
    }
}



std::shared_ptr<hl_ast_operand>
expression_evaluator::evaluate_unary_expression(std::shared_ptr<hl_expression_node> expression) {
    std::shared_ptr<hl_ast_operand> retval;
    std::shared_ptr<hl_ast_operand> rhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_rhs()));

    c_types_t expr_type = c_type_int;

    if(rhs->get_type() == var_type_float_const){
        expr_type = c_type_float;
    }

    if(expression->get_type() != expr_fti || expression->get_type() != expr_itf  ){
        if(rhs->get_type() == var_type_float_const){
            float operand = rhs->get_float_val();

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
            retval = std::make_shared<hl_ast_operand>(var);

            retval->set_immediate(evaluate_unary_expr_f(operand, expression->get_type()));
        } else if(rhs->get_type()==var_type_int_const){
            int operand = rhs->get_int_value();

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
            retval = std::make_shared<hl_ast_operand>(var);

            retval->set_immediate(evaluate_unary_expr_i(operand, expression->get_type()));
        }
    }

    return retval;
}

std::shared_ptr<hl_ast_operand>
expression_evaluator::evaluate_regular_expression(std::shared_ptr<hl_expression_node> expression) {

    std::shared_ptr<hl_ast_operand> retval;

    std::shared_ptr<hl_ast_operand> lhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_lhs()));
    std::shared_ptr<hl_ast_operand> rhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_rhs()));

    c_types_t expr_type = c_type_int;

    if(rhs->get_type() == var_type_float_const){
        expr_type = c_type_float;
    }

    if(lhs->get_type() == var_type_int_const){
        expr_type = c_type_float;
    }


    if(expr_type == c_type_int) {
        int op_a = lhs->get_int_value();
        int op_b = rhs->get_int_value();


        int operand = evaluate_regular_expr_i(op_a, op_b, expression->get_type());

        std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
        retval = std::make_shared<hl_ast_operand>(var);

    } else {
        float op_a = lhs->get_float_val();
        float op_b = rhs->get_float_val();

        float operand = evaluate_regular_expr_f(op_a, op_b, expression->get_type());

        std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
        retval = std::make_shared<hl_ast_operand>(var);

    }

    return retval;
}



std::shared_ptr<hl_ast_operand>
expression_evaluator::evaluate_expression_side(const std::shared_ptr<hl_ast_node> &side) {
    std::shared_ptr<hl_ast_operand> retval;

    if(side->node_type == hl_ast_node_type_operand){
        retval = std::static_pointer_cast<hl_ast_operand>(side);
    } else{
        retval = evaluate_expression(std::static_pointer_cast<hl_expression_node>(side));
    }
    return retval;
}


float expression_evaluator::evaluate_unary_expr_f(float operand, expression_type_t operation) {
    switch (operation) {
        case expr_reciprocal:
            return 1/operand;
        case expr_not_b:
            return (float)~(unsigned int)operand;
        case expr_neg:
            return -operand;
        case expr_incr_pre:
        case expr_incr_post:
            return operand+1;
        case expr_decr_post:
        case expr_decr_pre:
            return operand-1;
        default:
            throw std::runtime_error("Internal error: this condition should not have been possible");

    }
}

int expression_evaluator::evaluate_unary_expr_i(int operand, expression_type_t operation) {
    switch (operation) {
        case expr_reciprocal:
            return 1/operand;
        case expr_not_b:
            return ~operand;
        case expr_neg:
            return -operand;
        case expr_incr_pre:
        case expr_incr_post:
            return operand+1;
        case expr_decr_post:
        case expr_decr_pre:
            return operand-1;
        default:
            throw std::runtime_error("Internal error: this condition should not have been possible");

    }
}


float expression_evaluator::evaluate_regular_expr_f(float operand_a, float operand_b, expression_type_t operation) {
    switch (operation) {
        case expr_add:
            return operand_a+operand_b;
        case expr_sub:
            return operand_a-operand_b;
        case expr_mult:
            return operand_a*operand_b;
        case expr_div:
            return operand_a/operand_b;
        case expr_eq:
            return operand_a==operand_b?1:0;
        case expr_neq:
            return operand_a!=operand_b?1:0;
        case expr_lt:
            return operand_a<operand_b?1:0;
        case expr_gt:
            return operand_a>operand_b?1:0;
        case expr_lte:
            return operand_a<=operand_b?1:0;
        case expr_gte:
            return operand_a>=operand_b?1:0;
        case expr_satp:
            return operand_a>operand_b?operand_b:operand_a;
        case expr_satn:
            return operand_a<operand_b?operand_b:operand_a;
        default:
            throw std::runtime_error("Internal error: Unexpected constant expression");
    }
}

int expression_evaluator::evaluate_regular_expr_i(int operand_a, int operand_b, expression_type_t operation) {
    switch (operation) {
        case expr_add:
            return operand_a+operand_b;
        case expr_sub:
            return operand_a-operand_b;
        case expr_mult:
            return operand_a*operand_b;
        case expr_div:
            return operand_a/operand_b;
        case expr_modulo:
            return operand_a%operand_b;
        case expr_and_l:
            return operand_a&&operand_b;
        case expr_and_b:
            return operand_a&operand_b;
        case expr_or_l:
            return operand_a||operand_b;
        case expr_or_b:
            return operand_a|operand_b;
        case expr_xor_b:
            return operand_a^operand_b;
        case expr_lsh:
            return operand_a<<operand_b;
        case expr_rsh:
            return operand_a>>operand_b;
        case expr_eq:
            return operand_a==operand_b?1:0;
        case expr_neq:
            return operand_a!=operand_b?1:0;
        case expr_lt:
            return operand_a<operand_b?1:0;
        case expr_gt:
            return operand_a>operand_b?1:0;
        case expr_lte:
            return operand_a<=operand_b?1:0;
        case expr_gte:
            return operand_a>=operand_b?1:0;
        case expr_satp:
            return operand_a>operand_b?operand_b:operand_a;
        case expr_satn:
            return operand_a<operand_b?operand_b:operand_a;
        default:
            throw std::runtime_error("Internal error: Unexpected constant expression");
    }
}