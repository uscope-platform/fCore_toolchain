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

#ifndef FCORE_TOOLCHAIN_EXPRESSION_EVALUATOR_H
#define FCORE_TOOLCHAIN_EXPRESSION_EVALUATOR_H


#include "data_structures/high_level_ast/ast_expression.hpp"

namespace fcore {
    class expression_evaluator {
    public:
        expression_evaluator() = default;
        static std::shared_ptr<ast_operand> evaluate_expression(std::shared_ptr<ast_expression> expression);
    private:
        static bool is_constant_subexpr(const std::shared_ptr<ast_node>& subex);
        static std::shared_ptr<ast_operand> evaluate_regular_expression(std::shared_ptr<ast_expression> expression);
        static std::shared_ptr<ast_operand> evaluate_ternary_expression(std::shared_ptr<ast_expression> expression);
        static std::shared_ptr<ast_operand> evaluate_unary_expression(std::shared_ptr<ast_expression> expression);
        static std::shared_ptr<ast_operand> evaluate_expression_side(const std::shared_ptr<ast_node>& side);
        static int evaluate_regular_expr_i(int operand_a, int operand_b, ast_expression::expression_type operation);
        static float evaluate_regular_expr_f(float operand_a, float operand_b, ast_expression::expression_type operation);
        static int evaluate_ternary_expr_i(int operand_a, int operand_b,  int operand_c);
        static float evaluate_ternary_expr_f(float operand_a, float operand_b, float operand_c);
        static int evaluate_unary_expr_i(int operand, ast_expression::expression_type operation);
        static float evaluate_unary_expr_f(float operand, ast_expression::expression_type operation);
    };
}



#endif //FCORE_TOOLCHAIN_EXPRESSION_EVALUATOR_H
