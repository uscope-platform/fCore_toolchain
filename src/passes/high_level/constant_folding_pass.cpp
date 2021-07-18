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


#include "passes/high_level/constant_folding_pass.hpp"

constant_folding_pass::constant_folding_pass() : pass_base<hl_ast_node>("Constant folding pass"){

}

std::shared_ptr<hl_ast_node> constant_folding_pass::process_leaf(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type==hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> expression = std::static_pointer_cast<hl_expression_node>(element);
        if(!expression->is_unary()){
            return process_regular_expr(expression);
        } else{
            return process_unary_expr(expression);
        }
    }

    return element;
}

std::shared_ptr<hl_ast_node> constant_folding_pass::process_unary_expr(const std::shared_ptr<hl_expression_node>& element) {
    if(element->get_rhs()->node_type != hl_ast_node_type_operand) return element;
    std::shared_ptr<hl_ast_operand> rhs = std::static_pointer_cast<hl_ast_operand>(element->get_rhs());

    std::shared_ptr<hl_ast_operand> operand_res;

    if(element->get_type() != expr_fti || element->get_type() != expr_itf  ){
        if(rhs->get_type() == float_immediate_operand){
            float operand = rhs->get_float_val();
            operand_res = std::make_shared<hl_ast_operand>(float_immediate_operand);
            operand_res->set_immediate(evaluate_unary_expr_f(operand, element->get_type()));
        } else if(rhs->get_type()==integer_immediate_operand){
            int operand = rhs->get_int_value();
            operand_res = std::make_shared<hl_ast_operand>(integer_immediate_operand);
            operand_res->set_immediate(evaluate_unary_expr_i(operand, element->get_type()));
        } else{
            return element;
        }
    }

    return operand_res;
}

std::shared_ptr<hl_ast_node> constant_folding_pass::process_regular_expr(const std::shared_ptr<hl_expression_node>& element) {
    if(element->get_rhs()->node_type != hl_ast_node_type_operand || element->get_lhs()->node_type != hl_ast_node_type_operand) return element;

    std::shared_ptr<hl_ast_operand> rhs = std::static_pointer_cast<hl_ast_operand>(element->get_rhs());
    std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());

    std::shared_ptr<hl_ast_operand> operand_res;
    c_types_t  expr_type = c_type_int;


    if(rhs->get_type() == float_immediate_operand){
       expr_type = c_type_float;
    } else if(rhs->get_type()!=integer_immediate_operand){
        return element;
    }

    if(lhs->get_type() == float_immediate_operand){
        expr_type = c_type_float;
    } else if(lhs->get_type()!=integer_immediate_operand){
        return element;
    }


    if(expr_type == c_type_int) {
        int op_a = lhs->get_int_value();
        int op_b = rhs->get_int_value();
        operand_res = std::make_shared<hl_ast_operand>(integer_immediate_operand);
        operand_res->set_immediate(evaluate_regular_expr_i(op_a, op_b, element->get_type()));
    } else {
        float op_a = lhs->get_float_val();
        float op_b = rhs->get_float_val();
        operand_res = std::make_shared<hl_ast_operand>(float_immediate_operand);
        operand_res->set_immediate(evaluate_regular_expr_f(op_a, op_b, element->get_type()));
    }

    return operand_res;



}

float constant_folding_pass::evaluate_unary_expr_f(float operand, expression_type_t operation) {
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

int constant_folding_pass::evaluate_unary_expr_i(int operand, expression_type_t operation) {
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


float constant_folding_pass::evaluate_regular_expr_f(float operand_a, float operand_b, expression_type_t operation) {
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

int constant_folding_pass::evaluate_regular_expr_i(int operand_a, int operand_b, expression_type_t operation) {
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
