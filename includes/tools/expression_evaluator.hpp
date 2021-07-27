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

#ifndef FCORE_TOOLCHAIN_EXPRESSION_EVALUATOR_H
#define FCORE_TOOLCHAIN_EXPRESSION_EVALUATOR_H


#include "data_structures/high_level_ast/hl_expression_node.hpp"

class expression_evaluator {
public:
    expression_evaluator() = default;
    static std::shared_ptr<hl_ast_operand> evaluate_expression(std::shared_ptr<hl_expression_node> expression);
    static bool is_constant_expression(const std::shared_ptr<hl_expression_node>& expression);
private:
    static bool is_constant_subexpr(const std::shared_ptr<hl_ast_node>& subex);
    static std::shared_ptr<hl_ast_operand> evaluate_regular_expression(std::shared_ptr<hl_expression_node> expression);
    static std::shared_ptr<hl_ast_operand> evaluate_unary_expression(std::shared_ptr<hl_expression_node> expression);
    static std::shared_ptr<hl_ast_operand> evaluate_expression_side(const std::shared_ptr<hl_ast_node>& side);
    static int evaluate_regular_expr_i(int operand_a, int operand_b, expression_type_t operation);
    static float evaluate_regular_expr_f(float operand_a, float operand_b, expression_type_t operation);
    static int evaluate_unary_expr_i(int operand, expression_type_t operation);
    static float evaluate_unary_expr_f(float operand, expression_type_t operation);
};


#endif //FCORE_TOOLCHAIN_EXPRESSION_EVALUATOR_H
