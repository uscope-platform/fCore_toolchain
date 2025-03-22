// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.29/06/2021.
//

#include "tools/expression_evaluator.hpp"

namespace fcore{


    std::shared_ptr<hl_ast_operand>
    expression_evaluator::evaluate_expression(std::shared_ptr<hl_expression_node> expression) {
        if(expression->is_unary()) {
            return evaluate_unary_expression(expression);
        }else if(expression->is_ternary()){
            return evaluate_ternary_expression(expression);
        } else {
            return evaluate_regular_expression(expression);
        }
    }



    std::shared_ptr<hl_ast_operand>
    expression_evaluator::evaluate_unary_expression(std::shared_ptr<hl_expression_node> expression) {
        std::shared_ptr<hl_ast_operand> retval;

        std::shared_ptr<hl_ast_operand> rhs;
        if(expression->get_rhs()->node_type ==hl_ast_node_type_expr){
            rhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_rhs()));
        } else if(expression->get_rhs()->node_type ==hl_ast_node_type_operand) {
            rhs = std::static_pointer_cast<hl_ast_operand>(expression->get_rhs());
        } else {
            throw std::runtime_error("node type not expected during expression evaluation");
        }

        c_types_t expr_type = c_type_int;
        //In order for the result type to be flating point either the operand is a float or the expression is reciprocal, which
        //always results in a float
        if(rhs->get_type() == var_type_float_const || expression->get_type() == hl_expression_node::RECIPROCAL){
            expr_type = c_type_float;
        }

        if(expression->get_type() != hl_expression_node::FTI && expression->get_type() != hl_expression_node::ITF  ){
            if(expr_type == c_type_float){
                float operand = rhs->get_float_val();

                std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
                retval = std::make_shared<hl_ast_operand>(var);

                retval->set_immediate(evaluate_unary_expr_f(operand, expression->get_type()));
            } else {
                int operand = rhs->get_int_value();

                std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
                retval = std::make_shared<hl_ast_operand>(var);

                retval->set_immediate(evaluate_unary_expr_i(operand, expression->get_type()));
            }
        } else {
            if(expr_type == c_type_float){
                float operand = rhs->get_float_val();
                int result_val = std::round(operand);
                std::shared_ptr<variable> var = std::make_shared<variable>("constant", result_val);
                retval = std::make_shared<hl_ast_operand>(var);

                retval->set_immediate(result_val);
            } else {
                int operand = rhs->get_int_value();
                auto result_val = (float)operand;
                std::shared_ptr<variable> var = std::make_shared<variable>("constant", result_val);
                retval = std::make_shared<hl_ast_operand>(var);

                retval->set_immediate(result_val);
            }
        }

        return retval;
    }

    std::shared_ptr<hl_ast_operand>
    expression_evaluator::evaluate_regular_expression(std::shared_ptr<hl_expression_node> expression) {

        std::shared_ptr<hl_ast_operand> retval;

        std::shared_ptr<hl_ast_operand> lhs;
        if(expression->get_lhs().value()->node_type ==hl_ast_node_type_expr){
            lhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_lhs().value()));
        } else if(expression->get_lhs().value()->node_type ==hl_ast_node_type_operand) {
            lhs = std::static_pointer_cast<hl_ast_operand>(expression->get_lhs().value());
        } else {
            throw std::runtime_error("node type not expected during expression evaluation");
        }

        std::shared_ptr<hl_ast_operand> rhs;
        if(expression->get_rhs()->node_type ==hl_ast_node_type_expr){
            rhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_rhs()));
        } else if(expression->get_rhs()->node_type ==hl_ast_node_type_operand) {
            rhs = std::static_pointer_cast<hl_ast_operand>(expression->get_rhs());
        } else {
            throw std::runtime_error("node type not expected during expression evaluation");
        }

        c_types_t expr_type = c_type_int;

        if(rhs->get_type() == var_type_float_const || lhs->get_type() == var_type_float_const){
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


    float expression_evaluator::evaluate_unary_expr_f(float operand, hl_expression_node::expression_type operation) {
        switch (operation) {
            case hl_expression_node::RECIPROCAL:
                return 1/operand;
            case hl_expression_node::NOT_B:
                return (float)~(unsigned int)operand;
            case hl_expression_node::NEG:
                return -operand;
            case hl_expression_node::PRE_INCR:
            case hl_expression_node::POST_INCR:
                return operand+1;
            case hl_expression_node::POST_DECR:
            case hl_expression_node::PRE_DECR:
                return operand-1;
            case hl_expression_node::FTI:
                return operand;
            default:
                throw std::runtime_error("Internal error: this condition should not have been possible");

        }
    }

    int expression_evaluator::evaluate_unary_expr_i(int operand, hl_expression_node::expression_type operation) {
        switch (operation) {
            case hl_expression_node::RECIPROCAL:
                return 1/operand;
            case hl_expression_node::NOT_B:
                return ~operand;
            case hl_expression_node::NEG:
                return -operand;
            case hl_expression_node::PRE_INCR:
            case hl_expression_node::POST_INCR:
                return operand+1;
            case hl_expression_node::POST_DECR:
            case hl_expression_node::PRE_DECR:
                return operand-1;
            case hl_expression_node::ITF:
                return operand;
            default:
                throw std::runtime_error("Internal error: this condition should not have been possible");

        }
    }


    float expression_evaluator::evaluate_regular_expr_f(float operand_a, float operand_b, hl_expression_node::expression_type operation) {
        switch (operation) {
            case hl_expression_node::ADD:
                return operand_a+operand_b;
            case hl_expression_node::SUB:
                return operand_a-operand_b;
            case hl_expression_node::MULT:
                return operand_a*operand_b;
            case hl_expression_node::DIV:
                return operand_a/operand_b;
            case hl_expression_node::EQ:
                return operand_a==operand_b?1:0;
            case hl_expression_node::NEQ:
                return operand_a!=operand_b?1:0;
            case hl_expression_node::LT:
                return operand_a<operand_b?1:0;
            case hl_expression_node::GT:
                return operand_a>operand_b?1:0;
            case hl_expression_node::LTE:
                return operand_a<=operand_b?1:0;
            case hl_expression_node::GTE:
                return operand_a>=operand_b?1:0;
            case hl_expression_node::SATP:
                return operand_a>operand_b?operand_b:operand_a;
            case hl_expression_node::SATN:
                return operand_a<operand_b?operand_b:operand_a;
            default:
                throw std::runtime_error("Internal Unexpected constant expression");
        }
    }

    int expression_evaluator::evaluate_regular_expr_i(int operand_a, int operand_b, hl_expression_node::expression_type operation) {
        switch (operation) {
            case hl_expression_node::ADD:
                return operand_a+operand_b;
            case hl_expression_node::SUB:
                return operand_a-operand_b;
            case hl_expression_node::MULT:
                return operand_a*operand_b;
            case hl_expression_node::DIV:
                return operand_a/operand_b;
            case hl_expression_node::MODULO:
                return operand_a%operand_b;
            case hl_expression_node::AND_L:
                return operand_a&&operand_b;
            case hl_expression_node::AND_B:
                return operand_a&operand_b;
            case hl_expression_node::OR_L:
                return operand_a||operand_b;
            case hl_expression_node::OR_B:
                return operand_a|operand_b;
            case hl_expression_node::XOR_B:
                return operand_a^operand_b;
            case hl_expression_node::LSH:
                return operand_a<<operand_b;
            case hl_expression_node::RSH:
                return operand_a>>operand_b;
            case hl_expression_node::EQ:
                return operand_a==operand_b?1:0;
            case hl_expression_node::NEQ:
                return operand_a!=operand_b?1:0;
            case hl_expression_node::LT:
                return operand_a<operand_b?1:0;
            case hl_expression_node::GT:
                return operand_a>operand_b?1:0;
            case hl_expression_node::LTE:
                return operand_a<=operand_b?1:0;
            case hl_expression_node::GTE:
                return operand_a>=operand_b?1:0;
            case hl_expression_node::SATP:
                return operand_a>operand_b?operand_b:operand_a;
            case hl_expression_node::SATN:
                return operand_a<operand_b?operand_b:operand_a;
            default:
                throw std::runtime_error("Internal Unexpected constant expression");
        }
    }

    int
    expression_evaluator::evaluate_ternary_expr_i(int operand_a, int operand_b, int operand_c) {
        if(operand_a == 0){
            return operand_c;
        } else {
            return operand_b;
        }
    }

    float expression_evaluator::evaluate_ternary_expr_f(float operand_a, float operand_b, float operand_c) {
        if(operand_a == 0){
            return operand_c;
        } else {
            return operand_b;
        }
    }

    std::shared_ptr<hl_ast_operand>
    expression_evaluator::evaluate_ternary_expression(std::shared_ptr<hl_expression_node> expression) {

        std::shared_ptr<hl_ast_operand> retval;

        std::shared_ptr<hl_ast_operand> lhs;
        if(expression->get_lhs().value()->node_type ==hl_ast_node_type_expr){
            lhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_lhs().value()));
        } else if(expression->get_lhs().value()->node_type ==hl_ast_node_type_operand) {
            lhs = std::static_pointer_cast<hl_ast_operand>(expression->get_lhs().value());
        } else {
            throw std::runtime_error("node type not expected during expression evaluation");
        }

        std::shared_ptr<hl_ast_operand> rhs;
        if(expression->get_rhs()->node_type ==hl_ast_node_type_expr){
            rhs = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_rhs()));
        } else if(expression->get_rhs()->node_type ==hl_ast_node_type_operand) {
            rhs = std::static_pointer_cast<hl_ast_operand>(expression->get_rhs());
        } else {
            throw std::runtime_error("node type not expected during expression evaluation");
        }

        std::shared_ptr<hl_ast_operand> ths;
        if(expression->get_ths().value()->node_type ==hl_ast_node_type_expr){
            ths = evaluate_expression_side(std::static_pointer_cast<hl_expression_node>(expression->get_ths().value()));
        } else if(expression->get_rhs()->node_type ==hl_ast_node_type_operand) {
            ths = std::static_pointer_cast<hl_ast_operand>(expression->get_ths().value());
        } else {
            throw std::runtime_error("node type not expected during expression evaluation");
        }

        c_types_t expr_type = c_type_int;

        if(rhs->get_type() == var_type_float_const || lhs->get_type() == var_type_float_const|| ths->get_type() == var_type_float_const){
            expr_type = c_type_float;
        }


        if(expr_type == c_type_int) {
            int op_a = lhs->get_int_value();
            int op_b = rhs->get_int_value();
            int op_c = ths->get_int_value();


            int operand = evaluate_ternary_expr_i(op_a, op_b, op_c);

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
            retval = std::make_shared<hl_ast_operand>(var);

        } else {
            float op_a = lhs->get_float_val();
            float op_b = rhs->get_float_val();
            float op_c = ths->get_float_val();

            float operand = evaluate_ternary_expr_f(op_a, op_b, op_c);

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
            retval = std::make_shared<hl_ast_operand>(var);

        }

        return retval;
    }
}
