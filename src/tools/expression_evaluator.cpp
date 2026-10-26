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


    expression_evaluator::evaluated_t
    expression_evaluator::evaluate_expression(std::shared_ptr<ast_expression> expression) {
        if(expression->is_unary()) {
            return evaluate_unary_expression(expression);
        }else if(expression->is_ternary()){
            return evaluate_ternary_expression(expression);
        } else {
            return evaluate_regular_expression(expression);
        }
    }



    expression_evaluator::evaluated_t
    expression_evaluator::evaluate_unary_expression(std::shared_ptr<ast_expression> expression) {
        std::shared_ptr<ast_operand> retval;

        auto rhs_side = evaluate_expression_side(expression->get_rhs());
        if(!rhs_side) return fail(std::move(rhs_side).error());
        std::shared_ptr<ast_operand> rhs = rhs_side.value();

        c_types_t expr_type = c_type_int;
        //In order for the result type to be flating point either the operand is a float or the expression is reciprocal, which
        //always results in a float
        if(rhs->get_type() == var_type_float_const || expression->get_type() == ast_expression::RECIPROCAL){
            expr_type = c_type_float;
        }

        if(expression->get_type() != ast_expression::FTI && expression->get_type() != ast_expression::ITF  ){
            if(expr_type == c_type_float){
                float operand = rhs->get_float_val();

                std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
                retval = std::make_shared<ast_operand>(var);

                auto evaluation = evaluate_unary_expr_f(operand, expression->get_type());
                if(!evaluation) return fail(std::move(evaluation).error().with_context("evaluating " + expression->pretty_print()));
                retval->set_immediate(evaluation.value());
            } else {
                int operand = rhs->get_int_value();

                std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
                retval = std::make_shared<ast_operand>(var);

                auto evaluation = evaluate_unary_expr_i(operand, expression->get_type());
                if(!evaluation) return fail(std::move(evaluation).error().with_context("evaluating " + expression->pretty_print()));
                retval->set_immediate(evaluation.value());
            }
        } else {
            if(expr_type == c_type_float){
                float operand = rhs->get_float_val();
                int result_val = std::round(operand);
                std::shared_ptr<variable> var = std::make_shared<variable>("constant", result_val);
                retval = std::make_shared<ast_operand>(var);

                retval->set_immediate(result_val);
            } else {
                int operand = rhs->get_int_value();
                auto result_val = (float)operand;
                std::shared_ptr<variable> var = std::make_shared<variable>("constant", result_val);
                retval = std::make_shared<ast_operand>(var);

                retval->set_immediate(result_val);
            }
        }

        return retval;
    }

    expression_evaluator::evaluated_t
    expression_evaluator::evaluate_regular_expression(std::shared_ptr<ast_expression> expression) {

        std::shared_ptr<ast_operand> retval;

        auto lhs_side = evaluate_expression_side(expression->get_lhs().value());
        if(!lhs_side) return fail(std::move(lhs_side).error());
        std::shared_ptr<ast_operand> lhs = lhs_side.value();

        auto rhs_side = evaluate_expression_side(expression->get_rhs());
        if(!rhs_side) return fail(std::move(rhs_side).error());
        std::shared_ptr<ast_operand> rhs = rhs_side.value();

        c_types_t expr_type = c_type_int;

        if(rhs->get_type() == var_type_float_const || lhs->get_type() == var_type_float_const){
            expr_type = c_type_float;
        }


        if(expr_type == c_type_int) {
            int op_a = lhs->get_int_value();
            int op_b = rhs->get_int_value();


            auto evaluation = evaluate_regular_expr_i(op_a, op_b, expression->get_type());
            if(!evaluation) return fail(std::move(evaluation).error().with_context("evaluating " + expression->pretty_print()));
            int operand = evaluation.value();

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
            retval = std::make_shared<ast_operand>(var);

        } else {
            float op_a = lhs->get_float_val();
            float op_b = rhs->get_float_val();

            auto evaluation = evaluate_regular_expr_f(op_a, op_b, expression->get_type());
            if(!evaluation) return fail(std::move(evaluation).error().with_context("evaluating " + expression->pretty_print()));
            float operand = evaluation.value();

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
            retval = std::make_shared<ast_operand>(var);

        }

        return retval;
    }



    expression_evaluator::evaluated_t
    expression_evaluator::evaluate_expression_side(const std::shared_ptr<ast_node> &side) {
        if(side->node_type == hl_ast_node_type_operand){
            return std::static_pointer_cast<ast_operand>(side);
        }
        if(side->node_type == hl_ast_node_type_expr){
            return evaluate_expression(std::static_pointer_cast<ast_expression>(side));
        }
        return fail(error_code::internal_error, "node type not expected during expression evaluation");
    }


    result<float> expression_evaluator::evaluate_unary_expr_f(float operand, ast_expression::expression_type operation) {
        switch (operation) {
            case ast_expression::RECIPROCAL:
                return 1/operand;
            case ast_expression::NOT_B:
                return (float)~(unsigned int)operand;
            case ast_expression::NEG:
                return -operand;
            case ast_expression::PRE_INCR:
            case ast_expression::POST_INCR:
                return operand+1;
            case ast_expression::POST_DECR:
            case ast_expression::PRE_DECR:
                return operand-1;
            case ast_expression::FTI:
                return operand;
            default:
                return fail(error_code::not_supported, "the operation can not be evaluated at compile time");

        }
    }

    result<int> expression_evaluator::evaluate_unary_expr_i(int operand, ast_expression::expression_type operation) {
        switch (operation) {
            case ast_expression::RECIPROCAL:
                return 1/operand;
            case ast_expression::NOT_B:
                return ~operand;
            case ast_expression::NEG:
                return -operand;
            case ast_expression::PRE_INCR:
            case ast_expression::POST_INCR:
                return operand+1;
            case ast_expression::POST_DECR:
            case ast_expression::PRE_DECR:
                return operand-1;
            case ast_expression::ITF:
                return operand;
            default:
                return fail(error_code::not_supported, "the operation can not be evaluated at compile time");

        }
    }


    result<float> expression_evaluator::evaluate_regular_expr_f(float operand_a, float operand_b, ast_expression::expression_type operation) {
        switch (operation) {
            case ast_expression::ADD:
                return operand_a+operand_b;
            case ast_expression::SUB:
                return operand_a-operand_b;
            case ast_expression::MULT:
                return operand_a*operand_b;
            case ast_expression::DIV:
                return operand_a/operand_b;
            case ast_expression::EQ:
                return operand_a==operand_b?1:0;
            case ast_expression::NEQ:
                return operand_a!=operand_b?1:0;
            case ast_expression::LT:
                return operand_a<operand_b?1:0;
            case ast_expression::GT:
                return operand_a>operand_b?1:0;
            case ast_expression::LTE:
                return operand_a<=operand_b?1:0;
            case ast_expression::GTE:
                return operand_a>=operand_b?1:0;
            case ast_expression::SATP:
                return operand_a>operand_b?operand_b:operand_a;
            case ast_expression::SATN:
                return operand_a<operand_b?operand_b:operand_a;
            default:
                return fail(error_code::not_supported, "the operation can not be evaluated at compile time");
        }
    }

    result<int> expression_evaluator::evaluate_regular_expr_i(int operand_a, int operand_b, ast_expression::expression_type operation) {
        switch (operation) {
            case ast_expression::ADD:
                return operand_a+operand_b;
            case ast_expression::SUB:
                return operand_a-operand_b;
            case ast_expression::MULT:
                return operand_a*operand_b;
            case ast_expression::DIV:
                return operand_a/operand_b;
            case ast_expression::MODULO:
                return operand_a%operand_b;
            case ast_expression::AND_L:
                return operand_a&&operand_b;
            case ast_expression::AND_B:
                return operand_a&operand_b;
            case ast_expression::OR_L:
                return operand_a||operand_b;
            case ast_expression::OR_B:
                return operand_a|operand_b;
            case ast_expression::XOR_B:
                return operand_a^operand_b;
            case ast_expression::LSH:
                return operand_a<<operand_b;
            case ast_expression::RSH:
                return operand_a>>operand_b;
            case ast_expression::EQ:
                return operand_a==operand_b?1:0;
            case ast_expression::NEQ:
                return operand_a!=operand_b?1:0;
            case ast_expression::LT:
                return operand_a<operand_b?1:0;
            case ast_expression::GT:
                return operand_a>operand_b?1:0;
            case ast_expression::LTE:
                return operand_a<=operand_b?1:0;
            case ast_expression::GTE:
                return operand_a>=operand_b?1:0;
            case ast_expression::SATP:
                return operand_a>operand_b?operand_b:operand_a;
            case ast_expression::SATN:
                return operand_a<operand_b?operand_b:operand_a;
            default:
                return fail(error_code::not_supported, "the operation can not be evaluated at compile time");
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

    expression_evaluator::evaluated_t
    expression_evaluator::evaluate_ternary_expression(std::shared_ptr<ast_expression> expression) {

        std::shared_ptr<ast_operand> retval;

        auto lhs_side = evaluate_expression_side(expression->get_lhs().value());
        if(!lhs_side) return fail(std::move(lhs_side).error());
        std::shared_ptr<ast_operand> lhs = lhs_side.value();

        auto rhs_side = evaluate_expression_side(expression->get_rhs());
        if(!rhs_side) return fail(std::move(rhs_side).error());
        std::shared_ptr<ast_operand> rhs = rhs_side.value();

        auto ths_side = evaluate_expression_side(expression->get_ths().value());
        if(!ths_side) return fail(std::move(ths_side).error());
        std::shared_ptr<ast_operand> ths = ths_side.value();

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
            retval = std::make_shared<ast_operand>(var);

        } else {
            float op_a = lhs->get_float_val();
            float op_b = rhs->get_float_val();
            float op_c = ths->get_float_val();

            float operand = evaluate_ternary_expr_f(op_a, op_b, op_c);

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", operand);
            retval = std::make_shared<ast_operand>(var);

        }

        return retval;
    }
}
