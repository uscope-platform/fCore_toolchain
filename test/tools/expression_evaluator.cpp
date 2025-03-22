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


std::shared_ptr<hl_expression_node> construct_unary_f(float a, hl_expression_node::expression_type_t t) {
    auto var = std::make_shared<variable>("var", a);
    auto op = std::make_shared<hl_ast_operand>(var);
    auto expr = std::make_shared<hl_expression_node>(t);
    expr->set_rhs(op);

    return expr;
}


std::shared_ptr<hl_expression_node> construct_unary_i(int a, hl_expression_node::expression_type_t t) {
    auto var = std::make_shared<variable>("var", a);
    auto op = std::make_shared<hl_ast_operand>(var);
    auto expr = std::make_shared<hl_expression_node>(t);
    expr->set_rhs(op);

    return expr;
}


std::shared_ptr<hl_expression_node> construct_expression_f(float a, float b, hl_expression_node::expression_type_t t) {
    auto var = std::make_shared<variable>("var", a);
    auto op = std::make_shared<hl_ast_operand>(var);
    auto expr = std::make_shared<hl_expression_node>(t);

    expr->set_lhs(op);
    var = std::make_shared<variable>("var", b);
    op = std::make_shared<hl_ast_operand>(var);
    expr->set_rhs(op);

    return expr;
}


std::shared_ptr<hl_expression_node> construct_expression_i(int a, int b, hl_expression_node::expression_type_t t) {
    auto var = std::make_shared<variable>("var", a);
    auto op = std::make_shared<hl_ast_operand>(var);
    auto expr = std::make_shared<hl_expression_node>(t);

    expr->set_lhs(op);
    var = std::make_shared<variable>("var", b);
    op = std::make_shared<hl_ast_operand>(var);
    expr->set_rhs(op);

    return expr;
}

TEST(expression_evaluator, expression_add_f) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, hl_expression_node::expr_add));
    EXPECT_EQ(result->get_float_val(), 6.0f);
}

TEST(expression_evaluator, expression_sub_f) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, hl_expression_node::expr_sub));
    EXPECT_EQ(result->get_float_val(), -2.0f);
}

TEST(expression_evaluator, expression_mult_f) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, hl_expression_node::expr_mult));
    EXPECT_EQ(result->get_float_val(), 8.0f);
}

TEST(expression_evaluator, expression_div_f) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, hl_expression_node::expr_div));
    EXPECT_EQ(result->get_float_val(), 0.5f);
}

TEST(expression_evaluator, expression_eq_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 2, hl_expression_node::expr_eq));
    EXPECT_EQ(result->get_float_val(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_f(3, 2, hl_expression_node::expr_eq));
    EXPECT_EQ(result->get_float_val(), 0);
}


TEST(expression_evaluator, expression_neq_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(4, 2, hl_expression_node::expr_neq));
    EXPECT_EQ(result->get_float_val(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_f(4, 4, hl_expression_node::expr_neq));
    EXPECT_EQ(result->get_float_val(), 0);
}


TEST(expression_evaluator, expression_gt_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(4, 2, hl_expression_node::expr_gt));
    EXPECT_EQ(result->get_float_val(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_f(2, 4, hl_expression_node::expr_gt));
    EXPECT_EQ(result->get_float_val(), 0);
}

TEST(expression_evaluator, expression_gte_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 2, hl_expression_node::expr_gte));
    EXPECT_EQ(result->get_float_val(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_f(2, 7, hl_expression_node::expr_gte));
    EXPECT_EQ(result->get_float_val(), 0);
}

TEST(expression_evaluator, expression_lt_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(1, 2, hl_expression_node::expr_lt));
    EXPECT_EQ(result->get_float_val(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_f(3, 2, hl_expression_node::expr_lt));
    EXPECT_EQ(result->get_float_val(), 0);
}


TEST(expression_evaluator, expression_lte_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(2, 2, hl_expression_node::expr_lte));
    EXPECT_EQ(result->get_float_val(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_f(6, 2, hl_expression_node::expr_lte));
    EXPECT_EQ(result->get_float_val(), 0);
}

TEST(expression_evaluator, expression_satp_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(250, 200, hl_expression_node::expr_satp));
    EXPECT_EQ(result->get_float_val(), 200.0f);
    result = expression_evaluator::evaluate_expression(construct_expression_f(102, 200, hl_expression_node::expr_satp));
    EXPECT_EQ(result->get_float_val(), 102.0f);
}

TEST(expression_evaluator, expression_satn_f) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_f(-200, 2, hl_expression_node::expr_satn));
    EXPECT_EQ(result->get_float_val(), 2);
    result = expression_evaluator::evaluate_expression(construct_expression_f(20, 2, hl_expression_node::expr_satn));
    EXPECT_EQ(result->get_float_val(), 20);
}


TEST(expression_evaluator, expression_rec_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(200, hl_expression_node::expr_reciprocal));
    EXPECT_EQ(result->get_float_val(), 0.005f);
}

TEST(expression_evaluator, expr_neg_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(0.5, hl_expression_node::expr_neg));
    EXPECT_EQ(result->get_float_val(), -0.5f);
}


TEST(expression_evaluator, expr_fti_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(23, hl_expression_node::expr_fti));
    EXPECT_EQ(result->get_float_val(), 23.f);
}

TEST(expression_evaluator, expr_not_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(124532143.3, hl_expression_node::expr_not_b));
    EXPECT_FLOAT_EQ(result->get_float_val(),4.17043507e+09);
}


TEST(expression_evaluator, expr_incr_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(5, hl_expression_node::expr_incr_post));
    EXPECT_FLOAT_EQ(result->get_float_val(),6.f);

    result = expression_evaluator::evaluate_expression(construct_unary_f(5, hl_expression_node::expr_incr_pre));
    EXPECT_FLOAT_EQ(result->get_float_val(),6.f);
}



TEST(expression_evaluator, expr_decr_f) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_f(5, hl_expression_node::expr_decr_pre));
    EXPECT_FLOAT_EQ(result->get_float_val(),4.f);

    result = expression_evaluator::evaluate_expression(construct_unary_f(5, hl_expression_node::expr_decr_post));
    EXPECT_FLOAT_EQ(result->get_float_val(),4.f);
}

TEST(expression_evaluator, expression_add_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 4, hl_expression_node::expr_add));
    EXPECT_EQ(result->get_int_value(), 6);
}

TEST(expression_evaluator, expression_sub_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 4, hl_expression_node::expr_sub));
    EXPECT_EQ(result->get_int_value(), -2);
}

TEST(expression_evaluator, expression_mult_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 4, hl_expression_node::expr_mult));
    EXPECT_EQ(result->get_int_value(), 8);
}

TEST(expression_evaluator, expression_div_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(5, 2, hl_expression_node::expr_div));
    EXPECT_EQ(result->get_int_value(), 2);
}

TEST(expression_evaluator, expression_mod_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(8, 3, hl_expression_node::expr_modulo));
    EXPECT_EQ(result->get_int_value(), 2);
}

TEST(expression_evaluator, expression_eq_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 2, hl_expression_node::expr_eq));
    EXPECT_EQ(result->get_int_value(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_i(2, 3, hl_expression_node::expr_eq));
    EXPECT_EQ(result->get_int_value(), 0);
}


TEST(expression_evaluator, expression_neq_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(4, 2, hl_expression_node::expr_neq));
    EXPECT_EQ(result->get_int_value(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_i(4, 4, hl_expression_node::expr_neq));
    EXPECT_EQ(result->get_int_value(), 0);
}


TEST(expression_evaluator, expression_gt_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(4, 2, hl_expression_node::expr_gt));
    EXPECT_EQ(result->get_int_value(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_i(1, 2, hl_expression_node::expr_gt));
    EXPECT_EQ(result->get_int_value(), 0);
}

TEST(expression_evaluator, expression_gte_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 2, hl_expression_node::expr_gte));
    EXPECT_EQ(result->get_int_value(), 1);
    result = expression_evaluator::evaluate_expression(construct_expression_i(2, 7, hl_expression_node::expr_gte));
    EXPECT_EQ(result->get_int_value(), 0);
}

TEST(expression_evaluator, expression_lt_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(1, 2, hl_expression_node::expr_lt));
    EXPECT_EQ(result->get_int_value(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_i(2, 2, hl_expression_node::expr_lt));
    EXPECT_EQ(result->get_int_value(), 0);
}

TEST(expression_evaluator, expression_lte_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(2, 2, hl_expression_node::expr_lte));
    EXPECT_EQ(result->get_int_value(), 1);

    result = expression_evaluator::evaluate_expression(construct_expression_i(5, 2, hl_expression_node::expr_lte));
    EXPECT_EQ(result->get_int_value(), 0);
}

TEST(expression_evaluator, expression_satp_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(250, 200, hl_expression_node::expr_satp));
    EXPECT_EQ(result->get_int_value(), 200);

    result = expression_evaluator::evaluate_expression(construct_expression_i(120, 200, hl_expression_node::expr_satp));
    EXPECT_EQ(result->get_int_value(), 120);
}

TEST(expression_evaluator, expression_satn_i) {
    auto result = expression_evaluator::evaluate_expression(construct_expression_i(-200, 2, hl_expression_node::expr_satn));
    EXPECT_EQ(result->get_int_value(), 2);
    result = expression_evaluator::evaluate_expression(construct_expression_i(20, 2, hl_expression_node::expr_satn));
    EXPECT_EQ(result->get_int_value(), 20);
}


TEST(expression_evaluator, expression_and_l_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(112, 100, hl_expression_node::expr_and_l));
    EXPECT_EQ(result->get_int_value(), 1);
}


TEST(expression_evaluator, expression_and_b_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(112, 100, hl_expression_node::expr_and_b));
    EXPECT_EQ(result->get_int_value(), 96);
}


TEST(expression_evaluator, expression_or_b_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(-200, 2, hl_expression_node::expr_or_b));
    EXPECT_EQ(result->get_int_value(), -198);
}


TEST(expression_evaluator, expression_or_l_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(-200, 2, hl_expression_node::expr_or_l));
    EXPECT_EQ(result->get_int_value(), 1);
}



TEST(expression_evaluator, expression_xor_b_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(533, 254, hl_expression_node::expr_xor_b));
    EXPECT_EQ(result->get_int_value(), 747);
}


TEST(expression_evaluator, expression_lsh_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(533, 2, hl_expression_node::expr_lsh));
    EXPECT_EQ(result->get_int_value(), 2132);
}

TEST(expression_evaluator, expression_rsh_i) {
    const auto result = expression_evaluator::evaluate_expression(construct_expression_i(533, 2, hl_expression_node::expr_rsh));
    EXPECT_EQ(result->get_int_value(), 133);
}


TEST(expression_evaluator, expr_neg) {
    const auto result = expression_evaluator::evaluate_expression(construct_unary_i(-23, hl_expression_node::expr_neg));
    EXPECT_EQ(result->get_int_value(), 23);
}


TEST(expression_evaluator, expr_not_b) {
    const auto result = expression_evaluator::evaluate_expression(construct_unary_i(-23, hl_expression_node::expr_not_b));
    EXPECT_EQ(result->get_int_value(), 22);
}


TEST(expression_evaluator, expr_incr_i) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_i(-23, hl_expression_node::expr_incr_pre));
    EXPECT_EQ(result->get_int_value(), -22);
    result = expression_evaluator::evaluate_expression(construct_unary_i(-23, hl_expression_node::expr_incr_post));
    EXPECT_EQ(result->get_int_value(), -22);
}

TEST(expression_evaluator, expr_decr_i) {
    auto result = expression_evaluator::evaluate_expression(construct_unary_i(-23, hl_expression_node::expr_decr_post));
    EXPECT_EQ(result->get_int_value(), -24);
    result = expression_evaluator::evaluate_expression(construct_unary_i(-23, hl_expression_node::expr_decr_pre));
    EXPECT_EQ(result->get_int_value(), -24);
}

TEST(expression_evaluator, ternary_float) {
    auto var = std::make_shared<variable>("var", 1.43f);
    auto op = std::make_shared<hl_ast_operand>(var);
    auto expr = std::make_shared<hl_expression_node>(hl_expression_node::expr_csel);
    expr->set_lhs(op);

    var = std::make_shared<variable>("var", 3.2f);
    op = std::make_shared<hl_ast_operand>(var);
    expr->set_rhs(op);

    var = std::make_shared<variable>("var", 1.2f);
    op = std::make_shared<hl_ast_operand>(var);
    expr->set_ths(op);

    auto result = expression_evaluator::evaluate_expression(expr);
    EXPECT_EQ(result->get_float_val(), 3.2f);

    var = std::make_shared<variable>("var", 0.0f);
    op = std::make_shared<hl_ast_operand>(var);
    expr->set_lhs(op);

    result = expression_evaluator::evaluate_expression(expr);
    EXPECT_EQ(result->get_float_val(), 1.2f);

}


TEST(expression_evaluator, ternary_int) {
    auto var = std::make_shared<variable>("var", 12);
    auto op = std::make_shared<hl_ast_operand>(var);
    auto expr = std::make_shared<hl_expression_node>(hl_expression_node::expr_csel);
    expr->set_lhs(op);

    var = std::make_shared<variable>("var", 32);
    op = std::make_shared<hl_ast_operand>(var);
    expr->set_rhs(op);

    var = std::make_shared<variable>("var", 42);
    op = std::make_shared<hl_ast_operand>(var);
    expr->set_ths(op);

    auto result = expression_evaluator::evaluate_expression(expr);
    EXPECT_EQ(result->get_int_value(), 32);

    var = std::make_shared<variable>("var", 0);
    op = std::make_shared<hl_ast_operand>(var);
    expr->set_lhs(op);

    result = expression_evaluator::evaluate_expression(expr);
    EXPECT_EQ(result->get_int_value(), 42);

}

