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
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP
#define FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP


#include "hl_ast_operand.hpp"
#include "hl_ast_node.hpp"
#include "hl_function_call_node.hpp"
#include "hl_ast_conditional_node.hpp"

namespace fcore{

    // FORWARD DECLARATIONS
    class expression_evaluator;

    class hl_expression_node : public hl_ast_node{
    public:

         enum assignment_type_t{
            regular_assignment,
            addition_assignment,
            subtraction_assignment,
            multiplication_assignment,
            division_assignment,
            modulo_assignment,
            and_assignment,
            or_assignment,
            xor_assignment,
            lsh_assignment,
            rsh_assignment,
        } ;

        enum expression_type_t{
            expr_add,
            expr_sub,
            expr_mult,
            expr_div,
            expr_incr_pre,
            expr_incr_post,
            expr_decr_pre,
            expr_decr_post,
            expr_modulo,
            expr_and_l,
            expr_and_b,
            expr_or_l,
            expr_or_b,
            expr_not_l,
            expr_not_b,
            expr_xor_b,
            expr_lsh,
            expr_rsh,
            expr_eq,
            expr_neq,
            expr_neg,
            expr_lt,
            expr_gt,
            expr_lte,
            expr_gte,
            expr_assign,
            expr_call,
            expr_reciprocal,
            expr_itf,
            expr_fti,
            expr_satp,
            expr_satn,
            expr_abs,
            expr_popcnt,
            expr_efi,
            expr_bset,
            expr_bsel,
            expr_nop,
            expr_csel
        } ;



        hl_expression_node( expression_type_t et);
        void set_lhs(const std::shared_ptr<hl_ast_node> &node) {lhs = node;};
        void set_rhs(const std::shared_ptr<hl_ast_node> &node) {rhs = node;};
        void set_ths(const std::shared_ptr<hl_ast_node> &node) {ths = node;};

        std::optional<std::shared_ptr<hl_ast_node>> get_lhs(){return lhs;};
        std::shared_ptr<hl_ast_node> get_rhs(){return rhs;};
        std::optional<std::shared_ptr<hl_ast_node>> get_ths(){return ths;};

        void set_assignment_type(assignment_type_t a) { assignment_type = a;};
        assignment_type_t get_assignment_type() {return assignment_type;};

        expression_type_t get_type(){return expr_type;};
        void set_type(expression_type_t t){expr_type = t;};
        std::string pretty_print();
        bool is_unary();
        bool is_ternary();
        bool is_immediate();

        void swap_operands();

        bool is_constant();
        static std::shared_ptr<hl_ast_operand> evaluate(const std::shared_ptr<hl_expression_node> &node);

        friend bool operator==(const hl_expression_node& lhs, const hl_expression_node& rhs);

        static std::shared_ptr<hl_expression_node> deep_copy (const std::shared_ptr<hl_expression_node> &node);

    private:
        expression_type_t expr_type;
        assignment_type_t assignment_type;

        std::optional<std::shared_ptr<hl_ast_node>> lhs;
        std::shared_ptr<hl_ast_node> rhs;
        std::optional<std::shared_ptr<hl_ast_node>> ths;

        std::map<expression_type_t, std::string> type_print;
        std::map<assignment_type_t, std::string> assign_prefix_print;
    };
}


#endif //FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP
