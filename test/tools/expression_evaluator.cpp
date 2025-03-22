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


#include <gtest/gtest.h>

#include "tools/expression_evaluator.hpp"

using namespace fcore;


std::shared_ptr<ast_expression> construct_unary_f(float a, ast_expression::expression_type t) {
    auto var = std::make_shared<variable>("var", a);
    auto op = std::make_shared<ast_operand>(var);
    auto expr = std::make_shared<ast_expression>(t);
    expr->set_rhs(op);

    return expr;
}


std::shared_ptr<ast_expression> construct_unary_i(int a, ast_expression::expression_type t) {
    auto var = std::make_shared<variable>("var", a);
    auto op = std::make_shared<ast_operand>(var);
    auto expr = std::make_shared<ast_expression>(t);
    expr->set_rhs(op);

    return expr;
}


std::shared_ptr<ast_expression> construct_expression_f(float a, float b, ast_expression::expression_type t) {
    auto var = std::make_shared<variable>("var", a);
    auto op = std::make_shared<ast_operand>(var);
    auto expr = std::make_shared<ast_expression>(t);

    expr->set_lhs(op);
    var = std::make_shared<variable>("var", b);
    op = std::make_shared<ast_operand>(var);
    expr->set_rhs(op);

    return expr;
}


std::shared_ptr<ast_expression> construct_expression_i(int a, int b, ast_expression::expression_type t) {
    auto var = std::make_shared<variable>("var", a);
    auto op = std::make_shared<ast_operand>(var);
    auto expr = std::make_shared<ast_expression>(t);

    expr->set_lhs(op);
    var = std::make_shared<variable>("var", b);
    op = std::make_shared<ast_operand>(var);
    expr->set_rhs(op);

    return expr;
}

TEST(expression_evaluator, expression_add_f) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, ast_expression::ADD));
    EXPECT_EQ(result->get_float_val(), 6.0f);
}

TEST(expression_evaluator, expression_sub_f) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, ast_expression::SUB));
    EXPECT_EQ(result->get_float_val(), -2.0f);
}

TEST(expression_evaluator, expression_mult_f) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, ast_expression::MULT));
    EXPECT_EQ(result->get_float_val(), 8.0f);
}

TEST(expression_evaluator, expression_div_f) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, ast_expression::DIV));
    EXPECT_EQ(result->get_float_val(), 0.5f);
}

TEST(expression_evaluator, expression_eq_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 2, ast_expression::EQ));
    EXPECT_EQ(result->get_float_val(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_f(3, 2, ast_expression::EQ));
    EXPECT_EQ(result->get_float_val(), 0);
}


TEST(expression_evaluator, expression_neq_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(4, 2, ast_expression::NEQ));
    EXPECT_EQ(result->get_float_val(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_f(4, 4, ast_expression::NEQ));
    EXPECT_EQ(result->get_float_val(), 0);
}


TEST(expression_evaluator, expression_gt_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(4, 2, ast_expression::GT));
    EXPECT_EQ(result->get_float_val(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, ast_expression::GT));
    EXPECT_EQ(result->get_float_val(), 0);
}

TEST(expression_evaluator, expression_gte_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 2, ast_expression::GTE));
    EXPECT_EQ(result->get_float_val(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_f(2, 7, ast_expression::GTE));
    EXPECT_EQ(result->get_float_val(), 0);
}

TEST(expression_evaluator, expression_lt_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(1, 2, ast_expression::LT));
    EXPECT_EQ(result->get_float_val(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_f(3, 2, ast_expression::LT));
    EXPECT_EQ(result->get_float_val(), 0);
}


TEST(expression_evaluator, expression_lte_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 2, ast_expression::LTE));
    EXPECT_EQ(result->get_float_val(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_f(6, 2, ast_expression::LTE));
    EXPECT_EQ(result->get_float_val(), 0);
}

TEST(expression_evaluator, expression_satp_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(250, 200, ast_expression::SATP));
    EXPECT_EQ(result->get_float_val(), 200.0f);
    result = expression_evaluator::evaluate_expression(construct_expression_f(102, 200, ast_expression::SATP));
    EXPECT_EQ(result->get_float_val(), 102.0f);
}

TEST(expression_evaluator, expression_satn_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(-200, 2, ast_expression::SATN));
    EXPECT_EQ(result->get_float_val(), 2);
    result = expression_evaluator::evaluate_expression(construct_expression_f(20, 2, ast_expression::SATN));
    EXPECT_EQ(result->get_float_val(), 20);
}


TEST(expression_evaluator, expression_rec_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(200, ast_expression::RECIPROCAL));
    EXPECT_EQ(result->get_float_val(), 0.005f);
}

TEST(expression_evaluator, expr_neg_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(0.5, ast_expression::NEG));
    EXPECT_EQ(result->get_float_val(), -0.5f);
}


TEST(expression_evaluator, expr_fti_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(23, ast_expression::FTI));
    EXPECT_EQ(result->get_float_val(), 23.f);
}

TEST(expression_evaluator, expr_not_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(124532143.3, ast_expression::NOT_B));
    EXPECT_FLOAT_EQ(result->get_float_val(),4.17043507e+09);
}


TEST(expression_evaluator, expr_incr_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(5, ast_expression::POST_INCR));
    EXPECT_FLOAT_EQ(result->get_float_val(),6.f);

    result = expression_evaluator::evaluate_expression(construct_unary_f(5, ast_expression::PRE_INCR));
    EXPECT_FLOAT_EQ(result->get_float_val(),6.f);
}



TEST(expression_evaluator, expr_decr_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(5, ast_expression::PRE_DECR));
    EXPECT_FLOAT_EQ(result->get_float_val(),4.f);

    result = expression_evaluator::evaluate_expression(construct_unary_f(5, ast_expression::POST_DECR));
    EXPECT_FLOAT_EQ(result->get_float_val(),4.f);
}

TEST(expression_evaluator, expression_add_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 4, ast_expression::ADD));
    EXPECT_EQ(result->get_int_value(), 6);
}

TEST(expression_evaluator, expression_sub_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 4, ast_expression::SUB));
    EXPECT_EQ(result->get_int_value(), -2);
}

TEST(expression_evaluator, expression_mult_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 4, ast_expression::MULT));
    EXPECT_EQ(result->get_int_value(), 8);
}

TEST(expression_evaluator, expression_div_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(5, 2, ast_expression::DIV));
    EXPECT_EQ(result->get_int_value(), 2);
}

TEST(expression_evaluator, expression_mod_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(8, 3, ast_expression::MODULO));
    EXPECT_EQ(result->get_int_value(), 2);
}

TEST(expression_evaluator, expression_eq_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 2, ast_expression::EQ));
    EXPECT_EQ(result->get_int_value(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_i(2, 3, ast_expression::EQ));
    EXPECT_EQ(result->get_int_value(), 0);
}


TEST(expression_evaluator, expression_neq_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(4, 2, ast_expression::NEQ));
    EXPECT_EQ(result->get_int_value(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_i(4, 4, ast_expression::NEQ));
    EXPECT_EQ(result->get_int_value(), 0);
}


TEST(expression_evaluator, expression_gt_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(4, 2, ast_expression::GT));
    EXPECT_EQ(result->get_int_value(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_i(1, 2, ast_expression::GT));
    EXPECT_EQ(result->get_int_value(), 0);
}

TEST(expression_evaluator, expression_gte_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 2, ast_expression::GTE));
    EXPECT_EQ(result->get_int_value(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_i(2, 7, ast_expression::GTE));
    EXPECT_EQ(result->get_int_value(), 0);
}

TEST(expression_evaluator, expression_lt_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(1, 2, ast_expression::LT));
    EXPECT_EQ(result->get_int_value(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_i(2, 2, ast_expression::LT));
    EXPECT_EQ(result->get_int_value(), 0);
}

TEST(expression_evaluator, expression_lte_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 2, ast_expression::LTE));
    EXPECT_EQ(result->get_int_value(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_i(5, 2, ast_expression::LTE));
    EXPECT_EQ(result->get_int_value(), 0);
}

TEST(expression_evaluator, expression_satp_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(250, 200, ast_expression::SATP));
    EXPECT_EQ(result->get_int_value(), 200);

    result = expression_evaluator::evaluate_expression(construct_expression_i(120, 200, ast_expression::SATP));
    EXPECT_EQ(result->get_int_value(), 120);
}

TEST(expression_evaluator, expression_satn_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(-200, 2, ast_expression::SATN));
    EXPECT_EQ(result->get_int_value(), 2);
    result = expression_evaluator::evaluate_expression(construct_expression_i(20, 2, ast_expression::SATN));
    EXPECT_EQ(result->get_int_value(), 20);
}


TEST(expression_evaluator, expression_and_l_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(112, 100, ast_expression::AND_L));
    EXPECT_EQ(result->get_int_value(), 1);
}


TEST(expression_evaluator, expression_and_b_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(112, 100, ast_expression::AND_B));
    EXPECT_EQ(result->get_int_value(), 96);
}


TEST(expression_evaluator, expression_or_b_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(-200, 2, ast_expression::OR_B));
    EXPECT_EQ(result->get_int_value(), -198);
}


TEST(expression_evaluator, expression_or_l_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(-200, 2, ast_expression::OR_L));
    EXPECT_EQ(result->get_int_value(), 1);
}



TEST(expression_evaluator, expression_xor_b_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(533, 254, ast_expression::XOR_B));
    EXPECT_EQ(result->get_int_value(), 747);
}


TEST(expression_evaluator, expression_lsh_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(533, 2, ast_expression::LSH));
    EXPECT_EQ(result->get_int_value(), 2132);
}

TEST(expression_evaluator, expression_rsh_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(533, 2, ast_expression::RSH));
    EXPECT_EQ(result->get_int_value(), 133);
}


TEST(expression_evaluator, expr_neg) {
    const auto result = expression_evaluator::evaluate_expression(construct_unary_i(-23, ast_expression::NEG));
    EXPECT_EQ(result->get_int_value(), 23);
}


TEST(expression_evaluator, expr_not_b) {
    const auto result = expression_evaluator::evaluate_expression(construct_unary_i(-23, ast_expression::NOT_B));
    EXPECT_EQ(result->get_int_value(), 22);
}


TEST(expression_evaluator, expr_incr_i) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_i(-23, ast_expression::PRE_INCR));
    EXPECT_EQ(result->get_int_value(), -22);
    result = expression_evaluator::evaluate_expression(construct_unary_i(-23, ast_expression::POST_INCR));
    EXPECT_EQ(result->get_int_value(), -22);
}

TEST(expression_evaluator, expr_decr_i) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_i(-23, ast_expression::POST_DECR));
    EXPECT_EQ(result->get_int_value(), -24);
    result = expression_evaluator::evaluate_expression(construct_unary_i(-23, ast_expression::PRE_DECR));
    EXPECT_EQ(result->get_int_value(), -24);
}

TEST(expression_evaluator, ternary_float) {
    auto var = std::make_shared<variable>("var", 1.43f);
    auto op = std::make_shared<ast_operand>(var);
    auto expr = std::make_shared<ast_expression>(ast_expression::CSEL);
    expr->set_lhs(op);

    var = std::make_shared<variable>("var", 3.2f);
    op = std::make_shared<ast_operand>(var);
    expr->set_rhs(op);

    var = std::make_shared<variable>("var", 1.2f);
    op = std::make_shared<ast_operand>(var);
    expr->set_ths(op);

    auto result = expression_evaluator::evaluate_expression(expr);
    EXPECT_EQ(result->get_float_val(), 3.2f);

    var = std::make_shared<variable>("var", 0.0f);
    op = std::make_shared<ast_operand>(var);
    expr->set_lhs(op);

    result = expression_evaluator::evaluate_expression(expr);
    EXPECT_EQ(result->get_float_val(), 1.2f);

}


TEST(expression_evaluator, ternary_int) {
    auto var = std::make_shared<variable>("var", 12);
    auto op = std::make_shared<ast_operand>(var);
    auto expr = std::make_shared<ast_expression>(ast_expression::CSEL);
    expr->set_lhs(op);

    var = std::make_shared<variable>("var", 32);
    op = std::make_shared<ast_operand>(var);
    expr->set_rhs(op);

    var = std::make_shared<variable>("var", 42);
    op = std::make_shared<ast_operand>(var);
    expr->set_ths(op);

    auto result = expression_evaluator::evaluate_expression(expr);
    EXPECT_EQ(result->get_int_value(), 32);

    var = std::make_shared<variable>("var", 0);
    op = std::make_shared<ast_operand>(var);
    expr->set_lhs(op);

    result = expression_evaluator::evaluate_expression(expr);
    EXPECT_EQ(result->get_int_value(), 42);

}

