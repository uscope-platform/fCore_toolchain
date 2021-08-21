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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP
#define FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP


#include "hl_ast_operand.hpp"
#include "hl_ast_node.hpp"
#include "hl_function_call_node.hpp"

#include <iostream>
#include <sstream>

typedef enum {
    expr_add = 0,
    expr_sub = 1,
    expr_mult = 2,
    expr_div = 3,
    expr_incr_pre= 4,
    expr_incr_post= 5,
    expr_decr_pre= 6,
    expr_decr_post= 7,
    expr_modulo =8,
    expr_and_l = 9,
    expr_and_b = 10,
    expr_or_l = 11,
    expr_or_b = 12,
    expr_not_l = 13,
    expr_not_b = 14,
    expr_xor_b = 15,
    expr_lsh = 16,
    expr_rsh = 17,
    expr_eq = 18,
    expr_neq = 19,
    expr_neg = 20,
    expr_lt = 21,
    expr_gt = 22,
    expr_lte = 23,
    expr_gte = 24,
    expr_assign = 25,
    expr_call = 26,
    expr_reciprocal = 27,
    expr_itf = 28,
    expr_fti = 29,
    expr_satp = 30,
    expr_satn = 31
} expression_type_t;

typedef enum {
   regular_assignment = 0,
   addition_assignment = 1,
   subtraction_assignment = 2,
   multiplication_assignment = 3,
   division_assignment = 4,
   modulo_assignment = 5,
   and_assignment = 6,
   or_assignment = 7,
   xor_assignment = 8,
   lsh_assignment = 9,
   rsh_assignment = 10,
} assignment_type_t;

class hl_expression_node : public hl_ast_node{
public:
    hl_expression_node( expression_type_t et);
    void set_lhs(const std::shared_ptr<hl_ast_node> &node);
    void set_rhs(const std::shared_ptr<hl_ast_node> &node);
    std::shared_ptr<hl_ast_node> get_lhs();
    std::shared_ptr<hl_ast_node> get_rhs();

    void set_assignment_type(assignment_type_t a) { assignment_type = a;};
    assignment_type_t get_assignment_type() {return assignment_type;};

    expression_type_t get_type();
    std::string pretty_print() override;
    bool is_unary();
    static bool is_hardware_compatible(expression_type_t et);
    bool is_terminal() override {
        return true;
    }
    friend bool operator==(const hl_expression_node& lhs, const hl_expression_node& rhs);

private:
    expression_type_t expr_type;
    assignment_type_t assignment_type;
    std::shared_ptr<hl_ast_node> lhs;
    std::shared_ptr<hl_ast_node> rhs;
    std::map<expression_type_t, std::string> type_print;
    std::map<assignment_type_t, std::string> assign_prefix_print;
};

#endif //FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP
