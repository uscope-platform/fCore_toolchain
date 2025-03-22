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

#include "data_structures/high_level_ast/high_level_ast.hpp"


using namespace fcore;

TEST(hl_expression, successful_const_testing) {

    auto e_add = std::make_shared<ast_expression>(ast_expression::ADD);
    auto var = std::make_shared<variable>("constant", 2.9f);
    auto op = std::make_shared<ast_operand>(var);
    e_add->set_lhs(op);
    var = std::make_shared<variable>("constant", 5.1f);
    op = std::make_shared<ast_operand>(var);
    e_add->set_rhs(op);

    auto e_mul = std::make_shared<ast_expression>(ast_expression::MULT);
    e_mul->set_rhs(e_add);
    var = std::make_shared<variable>("constant", 3.3f);
    op = std::make_shared<ast_operand>(var);
    e_mul->set_lhs(op);

    auto e_div = std::make_shared<ast_expression>(ast_expression::DIV);
    e_div->set_lhs(e_mul);
    var = std::make_shared<variable>("constant", 7.0f);
    op = std::make_shared<ast_operand>(var);
    e_div->set_rhs(op);

    EXPECT_TRUE(e_div->is_constant());
}


TEST(hl_expression, failed_const_testing) {

    auto e_add = std::make_shared<ast_expression>(ast_expression::ADD);
    auto var = std::make_shared<variable>("constant", 2.9f);
    auto op = std::make_shared<ast_operand>(var);
    e_add->set_lhs(op);
    var = std::make_shared<variable>("variable");
    op = std::make_shared<ast_operand>(var);
    e_add->set_rhs(op);

    auto e_mul = std::make_shared<ast_expression>(ast_expression::MULT);
    e_mul->set_rhs(e_add);
    var = std::make_shared<variable>("constant", 3.3f);
    op = std::make_shared<ast_operand>(var);
    e_mul->set_lhs(op);

    auto e_div = std::make_shared<ast_expression>(ast_expression::DIV);
    e_div->set_lhs(e_mul);
    var = std::make_shared<variable>("constant", 7.0f);
    op = std::make_shared<ast_operand>(var);
    e_div->set_rhs(op);

    EXPECT_FALSE(e_div->is_constant());
}


TEST(hl_expression, expression_evaluation) {

    auto e_add = std::make_shared<ast_expression>(ast_expression::ADD);
    auto var = std::make_shared<variable>("constant", 2.9f);
    auto op = std::make_shared<ast_operand>(var);
    e_add->set_lhs(op);
    var = std::make_shared<variable>("constant", 5.1f);
    op = std::make_shared<ast_operand>(var);
    e_add->set_rhs(op);

    auto e_mul = std::make_shared<ast_expression>(ast_expression::MULT);
    e_mul->set_rhs(e_add);
    var = std::make_shared<variable>("constant", 3.3f);
    op = std::make_shared<ast_operand>(var);
    e_mul->set_lhs(op);

    auto e_div = std::make_shared<ast_expression>(ast_expression::DIV);
    e_div->set_lhs(e_mul);
    var = std::make_shared<variable>("constant", 7.0f);
    op = std::make_shared<ast_operand>(var);
    e_div->set_rhs(op);

    auto result = ast_expression::evaluate(e_div);

    var = std::make_shared<variable>("constant", 3.7714285f);
    auto reference = std::make_shared<ast_operand>(var);
    EXPECT_EQ(*result, *reference);
}