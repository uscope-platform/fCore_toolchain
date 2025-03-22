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

         enum assignment_type{
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

        enum expression_type{
            ADD,
            SUB,
            MULT,
            DIV,
            PRE_INCR,
            POST_INCR,
            PRE_DECR,
            POST_DECR,
            MODULO,
            AND_L,
            AND_B,
            OR_L,
            OR_B,
            NOT_L,
            NOT_B,
            XOR_B,
            LSH,
            RSH,
            EQ,
            NEQ,
            NEG,
            LT,
            GT,
            LTE,
            GTE,
            ASSIGN,
            CALL,
            RECIPROCAL,
            ITF,
            FTI,
            SATP,
            SATN,
            ABS,
            POPCNT,
            EFI,
            BSET,
            BSEL,
            NOP,
            CSEL
        } ;



        hl_expression_node( expression_type et);
        void set_lhs(const std::shared_ptr<hl_ast_node> &node) {lhs = node;};
        void set_rhs(const std::shared_ptr<hl_ast_node> &node) {rhs = node;};
        void set_ths(const std::shared_ptr<hl_ast_node> &node) {ths = node;};

        std::optional<std::shared_ptr<hl_ast_node>> get_lhs(){return lhs;};
        std::shared_ptr<hl_ast_node> get_rhs(){return rhs;};
        std::optional<std::shared_ptr<hl_ast_node>> get_ths(){return ths;};

        void set_assignment_type(assignment_type a) { assignment_t = a;};
        assignment_type get_assignment_type() {return assignment_t;};

        expression_type get_type(){return expression_t;};
        void set_type(expression_type t){expression_t = t;};
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
        expression_type expression_t;
        assignment_type assignment_t;

        std::optional<std::shared_ptr<hl_ast_node>> lhs;
        std::shared_ptr<hl_ast_node> rhs;
        std::optional<std::shared_ptr<hl_ast_node>> ths;

        std::map<expression_type, std::string> type_print;
        std::map<assignment_type, std::string> assign_prefix_print;
    };
}


#endif //FCORE_TOOLCHAIN_HL_EXPRESSION_NODE_HPP
