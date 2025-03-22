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
// limitations under the License.01/07/2021.
//

#include "data_structures/high_level_ast/hl_expression_node.hpp"

#include <unordered_set>

#include "tools/expression_evaluator.hpp"

namespace fcore{

    hl_expression_node::hl_expression_node(expression_type et) : hl_ast_node(hl_ast_node_type_expr) {
        expression_t = et;
        assignment_t = regular_assignment;
        type_print = {
                {ADD, "+"},
                {SUB, "-"},
                {MULT, "*"},
                {DIV, "/"},
                {PRE_INCR, "++(pre)"},
                {POST_INCR, "(post)++"},
                {PRE_DECR, "--(pre)"},
                {POST_DECR, "(post)--"},
                {MODULO, "%"},
                {AND_L, "&&"},
                {AND_B, "&"},
                {OR_L, "||"},
                {OR_B, "|"},
                {NOT_L, "!"},
                {NOT_B, "~"},
                {XOR_B, "^"},
                {LSH, "<<"},
                {RSH, ">>"},
                {EQ, "=="},
                {NEQ, "!="},
                {NEG, "-"},
                {LT, "<"},
                {GT, ">"},
                {LTE, "<="},
                {GTE, ">="},
                {ASSIGN, "="},
                {RECIPROCAL, "1/"}
        };

        assign_prefix_print = {
                {regular_assignment, ""},
                {addition_assignment, "+"},
                {subtraction_assignment, "-"},
                {multiplication_assignment, "*"},
                {division_assignment, "/"},
                {modulo_assignment, "%"},
                {and_assignment, "&"},
                {or_assignment,"|"},
                {xor_assignment,"^"},
                {lsh_assignment,"<<"},
                {rsh_assignment,">>"},
        };
    }

    std::string hl_expression_node::pretty_print() {
        std::ostringstream ss;
        if (lhs.has_value()) {
            if (lhs.value()->node_type == hl_ast_node_type_operand) {
                std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(lhs.value());
                std::string tmp_lhs = *op;
                ss << tmp_lhs;
            } else {
                ss << "(" <<std::static_pointer_cast<hl_expression_node>(lhs.value())->pretty_print() << ")";
            }

        }

        ss << assign_prefix_print[assignment_t] << type_print[expression_t];

        if (rhs->node_type == hl_ast_node_type_operand) {

            std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(rhs);
            std::string tmp_rhs = *op;
            ss << tmp_rhs;
        } else if(rhs->node_type == hl_ast_node_type_function_call){
            ss << std::static_pointer_cast<hl_function_call_node>(rhs)->pretty_print();
        }else{
            ss << "(" <<std::static_pointer_cast<hl_expression_node>(rhs)->pretty_print() << ")";
        }
        std::string ret = ss.str();
        return ret;
    }


    bool hl_expression_node::is_unary() {
        std::unordered_set<expression_type> unaries = {
            RECIPROCAL,
            NOT_B,
            NOT_L,
            NEG,
            PRE_INCR,
            POST_INCR,
            POST_DECR,
            PRE_DECR,
            CALL,
            ITF,
            FTI,
            ABS,
            POPCNT

        };
        return unaries.contains(expression_t);
    }

    bool hl_expression_node::is_immediate() {
        bool res  = false;
        res |= expression_t == NOP;
        return res;
    }

    void hl_expression_node::swap_operands() {
        if(!is_unary() && !is_immediate() && !is_ternary()){
            auto lhs_tmp = lhs.value();
            lhs = rhs;
            rhs = lhs_tmp;
        }
    }

    bool hl_expression_node::is_constant() {
        bool res  = true;
        if(rhs->node_type == hl_ast_node_type_operand) {
            res &= std::static_pointer_cast<hl_ast_operand>(rhs)->is_constant();
        } else {
            res &= std::static_pointer_cast<hl_expression_node>(rhs)->is_constant();
        }

        if(lhs.has_value()) {
            auto lhs_val = lhs.value();
            if(lhs_val->node_type == hl_ast_node_type_operand) {
                res &= std::static_pointer_cast<hl_ast_operand>(lhs_val)->is_constant();
            } else {
                res &= std::static_pointer_cast<hl_expression_node>(lhs_val)->is_constant();
            }
        }

        if(is_ternary()) {
            auto ths_val = ths.value();
            if(ths_val->node_type == hl_ast_node_type_operand) {
                res &= std::static_pointer_cast<hl_ast_operand>(ths_val)->is_constant();
            } else {
                res &= std::static_pointer_cast<hl_expression_node>(ths_val)->is_constant();
            }
        }

        return res;
    }

    std::shared_ptr<hl_ast_operand> hl_expression_node::evaluate(const std::shared_ptr<hl_expression_node> &node) {
        return expression_evaluator::evaluate_expression(node);
    }

    bool hl_expression_node::is_ternary() {
        bool res  = false;
        res |= expression_t == CSEL;
        return res;
    }



    bool operator==(const hl_expression_node &l_ex, const hl_expression_node &r_ex){
        bool ret_val = true;


        if(l_ex.lhs.has_value() && r_ex.lhs.has_value()){
            if(l_ex.lhs.value()->node_type == hl_ast_node_type_expr && r_ex.lhs.value()->node_type ==  hl_ast_node_type_expr){
                std::shared_ptr<hl_expression_node> ex_1 = std::static_pointer_cast<hl_expression_node>(l_ex.lhs.value());
                std::shared_ptr<hl_expression_node> ex_2 = std::static_pointer_cast<hl_expression_node>(r_ex.lhs.value());
                ret_val &= *ex_1 == *ex_2;
            }else if(l_ex.lhs.value()->node_type == hl_ast_node_type_operand && r_ex.lhs.value()->node_type ==  hl_ast_node_type_operand){
                std::shared_ptr<hl_ast_operand> ex_1 = std::static_pointer_cast<hl_ast_operand>(l_ex.lhs.value());
                std::shared_ptr<hl_ast_operand> ex_2 = std::static_pointer_cast<hl_ast_operand>(r_ex.lhs.value());
                ret_val &= *ex_1 == *ex_2;
            } else {
                return false;
            }
        } else if(!l_ex.lhs.has_value() && !r_ex.lhs.has_value());
        else return false;

        if(l_ex.rhs != nullptr && r_ex.rhs != nullptr){
            if((l_ex.rhs->node_type == hl_ast_node_type_expr) && (r_ex.rhs->node_type ==  hl_ast_node_type_expr)){
                auto ex_1 = std::static_pointer_cast<hl_expression_node>(l_ex.rhs);
                auto ex_2 = std::static_pointer_cast<hl_expression_node>(r_ex.rhs);
                ret_val &= *ex_1 == *ex_2;
            }else if((l_ex.rhs->node_type == hl_ast_node_type_operand) && (r_ex.rhs->node_type ==  hl_ast_node_type_operand)){
                auto ex_1 = std::static_pointer_cast<hl_ast_operand>(l_ex.rhs);
                auto ex_2 = std::static_pointer_cast<hl_ast_operand>(r_ex.rhs);
                ret_val &= *ex_1 == *ex_2;
            }else if((l_ex.rhs->node_type == hl_ast_node_type_function_call) && (r_ex.rhs->node_type ==  hl_ast_node_type_function_call)){
                auto ex_1 = std::static_pointer_cast<hl_function_call_node>(l_ex.rhs);
                auto ex_2 = std::static_pointer_cast<hl_function_call_node>(r_ex.rhs);
                ret_val &= *ex_1 == *ex_2;
            }else if((l_ex.rhs->node_type == hl_ast_node_type_conditional) && (r_ex.rhs->node_type ==  hl_ast_node_type_conditional)){
                auto ex_1 = std::static_pointer_cast<hl_ast_conditional_node>(l_ex.rhs);
                auto ex_2 = std::static_pointer_cast<hl_ast_conditional_node>(r_ex.rhs);
                ret_val &= *ex_1 == *ex_2;
            }  else {
                return false;
            }
        } else if(l_ex.rhs == nullptr && r_ex.rhs == nullptr);
        else return false;



        if(l_ex.ths.has_value() && r_ex.ths.has_value()){
            if((l_ex.ths.value()->node_type == hl_ast_node_type_expr) && (r_ex.ths.value()->node_type ==  hl_ast_node_type_expr)){
                std::shared_ptr<hl_expression_node> ex_1 = std::static_pointer_cast<hl_expression_node>(r_ex.ths.value());
                std::shared_ptr<hl_expression_node> ex_2 = std::static_pointer_cast<hl_expression_node>(r_ex.ths.value());
                ret_val &= *ex_1 == *ex_2;
            }else if((l_ex.ths.value()->node_type == hl_ast_node_type_operand) && (r_ex.ths.value()->node_type ==  hl_ast_node_type_operand)){
                std::shared_ptr<hl_ast_operand> ex_1 = std::static_pointer_cast<hl_ast_operand>(r_ex.ths.value());
                std::shared_ptr<hl_ast_operand> ex_2 = std::static_pointer_cast<hl_ast_operand>(r_ex.ths.value());
                ret_val &= *ex_1 == *ex_2;
            }else if((l_ex.ths.value()->node_type == hl_ast_node_type_function_call) && (r_ex.ths.value()->node_type ==  hl_ast_node_type_function_call)){
                std::shared_ptr<hl_function_call_node> ex_1 = std::static_pointer_cast<hl_function_call_node>(r_ex.ths.value());
                std::shared_ptr<hl_function_call_node> ex_2 = std::static_pointer_cast<hl_function_call_node>(r_ex.ths.value());
                ret_val &= *ex_1 == *ex_2;
            } else {
                return false;
            }
        } else if(!l_ex.ths.has_value() && !r_ex.ths.has_value());
        else return false;


        ret_val &= l_ex.expression_t == r_ex.expression_t;
        ret_val &= l_ex.assignment_t == r_ex.assignment_t;

        return ret_val;
    }

    std::shared_ptr<hl_expression_node> hl_expression_node::deep_copy(const std::shared_ptr<hl_expression_node> &orig) {
        std::shared_ptr<hl_expression_node> copied_obj = std::make_shared<hl_expression_node>(orig->get_type());

        if(orig->lhs.has_value()) copied_obj->set_lhs(hl_ast_node::deep_copy(orig->get_lhs().value()));
        copied_obj->set_rhs(hl_ast_node::deep_copy(orig->get_rhs()));
        if(orig->ths.has_value()) copied_obj->set_ths(orig->get_ths().value());

        copied_obj->set_assignment_type(orig->get_assignment_type());

        return copied_obj;
    }
}