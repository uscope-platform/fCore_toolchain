//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_expression_node.h"

hl_expression_node::hl_expression_node(expression_type_t et) : hl_ast_node(hl_ast_node_type_expr) {
    expr_type = et;
    type_print = {
            {expr_add, "+"},
            {expr_sub, "-"},
            {expr_mult, "*"},
            {expr_div, "/"},
            {expr_incr_pre, "++(pre)"},
            {expr_incr_post, "(post)++"},
            {expr_decr_pre, "--(pre)"},
            {expr_decr_post, "(post)--"},
            {expr_modulo, "%"},
            {expr_and_l, "&&"},
            {expr_and_b, "&"},
            {expr_or_l, "||"},
            {expr_or_b, "|"},
            {expr_not_l, "!"},
            {expr_not_b, "~"},
            {expr_xor_b, "^"},
            {expr_lsh, "<<"},
            {expr_rsh, ">>"},
            {expr_eq, "=="},
            {expr_neq, "!="},
            {expr_neg, "-"},
            {expr_lt, "<"},
            {expr_gt, ">"},
            {expr_lte, "<="},
            {expr_gte, ">="},
            {expr_assign, "="}
    };
}

void hl_expression_node::set_lhs(const std::shared_ptr<hl_ast_node> &node) {
    lhs = node;
}

void hl_expression_node::set_rhs(const std::shared_ptr<hl_ast_node> &node) {
    rhs = node;
}

std::shared_ptr<hl_ast_node> hl_expression_node::get_lhs() {
    return lhs;
}

std::shared_ptr<hl_ast_node> hl_expression_node::get_rhs() {
    return rhs;
}

bool operator==(const hl_expression_node &lhs, const hl_expression_node &rhs) {
    bool ret_val = true;
    if(lhs.lhs != nullptr && rhs.lhs != nullptr){
        if(lhs.lhs->node_type == hl_ast_node_type_expr && rhs.lhs->node_type ==  hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> ex_1 = std::static_pointer_cast<hl_expression_node>(lhs.lhs);
            std::shared_ptr<hl_expression_node> ex_2 = std::static_pointer_cast<hl_expression_node>(rhs.lhs);
            ret_val &= *ex_1 == *ex_2;
        }else if(lhs.lhs->node_type == hl_ast_node_type_operand && rhs.lhs->node_type ==  hl_ast_node_type_operand){
            std::shared_ptr<hl_ast_operand> ex_1 = std::static_pointer_cast<hl_ast_operand>(lhs.lhs);
            std::shared_ptr<hl_ast_operand> ex_2 = std::static_pointer_cast<hl_ast_operand>(rhs.lhs);
            ret_val &= *ex_1 == *ex_2;
        } else {
            return false;
        }
    } else if(lhs.lhs == nullptr && rhs.lhs == nullptr);
    else return false;

    if(lhs.rhs != nullptr && rhs.rhs != nullptr){
        if((lhs.rhs->node_type == hl_ast_node_type_expr) && (rhs.rhs->node_type ==  hl_ast_node_type_expr)){
            std::shared_ptr<hl_expression_node> ex_1 = std::static_pointer_cast<hl_expression_node>(lhs.rhs);
            std::shared_ptr<hl_expression_node> ex_2 = std::static_pointer_cast<hl_expression_node>(rhs.rhs);
            ret_val &= *ex_1 == *ex_2;
        }else if((lhs.rhs->node_type == hl_ast_node_type_operand) && (rhs.rhs->node_type ==  hl_ast_node_type_operand)){
            std::shared_ptr<hl_ast_operand> ex_1 = std::static_pointer_cast<hl_ast_operand>(lhs.rhs);
            std::shared_ptr<hl_ast_operand> ex_2 = std::static_pointer_cast<hl_ast_operand>(rhs.rhs);
            ret_val &= *ex_1 == *ex_2;
        } else {
            return false;
        }
    } else if(lhs.rhs == nullptr && rhs.rhs == nullptr);
    else return false;

    ret_val &= lhs.expr_type == rhs.expr_type;

    return ret_val;
}

std::string hl_expression_node::pretty_print() {
    std::ostringstream ss;
    if(lhs != nullptr){
        if(lhs->node_type == hl_ast_node_type_operand){
            std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(lhs);
            std::string tmp_lhs = *op;
            ss << tmp_lhs;
        } else{
            ss << std::static_pointer_cast<hl_expression_node>(lhs)->pretty_print();
        }

    }
    ss << type_print[expr_type];

    if(rhs->node_type == hl_ast_node_type_operand){

        std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(rhs);
        std::string tmp_rhs = *op;
        ss << tmp_rhs;
    } else{
        ss << std::static_pointer_cast<hl_expression_node>(rhs)->pretty_print();
    }
    std::string ret = ss.str();
    return ret;
}
