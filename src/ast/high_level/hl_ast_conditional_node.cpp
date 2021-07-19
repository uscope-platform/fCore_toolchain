//
// Created by fils on 17/07/2021.
//

#include "ast/high_level/hl_ast_conditional_node.hpp"

#include <utility>

hl_ast_conditional_node::hl_ast_conditional_node() : hl_ast_node(hl_ast_node_type_conditional) {
    has_else = false;
}

void hl_ast_conditional_node::set_if_block(std::vector<std::shared_ptr<hl_ast_node>> node) {
    if_block = std::move(node);
}

std::vector<std::shared_ptr<hl_ast_node>> hl_ast_conditional_node::get_if_block() {
    return if_block;
}

void hl_ast_conditional_node::set_else_block(std::vector<std::shared_ptr<hl_ast_node>> node) {
    else_block = std::move(node);
}

std::vector<std::shared_ptr<hl_ast_node>> hl_ast_conditional_node::get_else_block() {
    return else_block;
}

std::string hl_ast_conditional_node::pretty_print() {

    std::ostringstream ss;

    ss << "if (cond) {" << std::endl;
    if(!if_block.empty()){
        for(const auto& item:if_block){
            ss << item->pretty_print() << ";" << std::endl;
        }
    }
    if(!else_block.empty()){
        ss << "} else {" << std::endl;
        for(const auto& item:else_block){
            ss << item->pretty_print() << ";" << std::endl;
        }
    }
    ss<< "}";
    return ss.str();
}

bool operator==(const hl_ast_conditional_node &lhs, const hl_ast_conditional_node &rhs) {
    bool ret_val = true;

    if(lhs.if_block.empty() && rhs.if_block.empty()){
        ret_val &= true;
    } else if(lhs.if_block.empty() || rhs.if_block.empty()){
        ret_val = false;
    } else{
        bool body_equal = true;
        if(lhs.if_block.size() != rhs.if_block.size()) return false;

        for(int i = 0; i<lhs.if_block.size(); i++){
            body_equal &=  hl_ast_node::compare_content_by_type( lhs.if_block[i], rhs.if_block[i]);
        }
        ret_val &= body_equal;
    }

    if(lhs.else_block.empty() && rhs.else_block.empty()){
        ret_val &= true;
    } else if(lhs.else_block.empty() || rhs.else_block.empty()){
        ret_val = false;
    } else{
        bool body_equal = true;
        if(lhs.else_block.size() != rhs.else_block.size()) return false;

        for(int i = 0; i<lhs.else_block.size(); i++){
            body_equal &= hl_ast_node::compare_content_by_type( lhs.else_block[i], rhs.else_block[i]);
        }
        ret_val &= body_equal;
    }

    ret_val &= hl_ast_node::compare_content_by_type( lhs.condition, rhs.condition);

    return ret_val;
}

void hl_ast_conditional_node::set_condition(std::shared_ptr<hl_ast_node> node) {
    condition = std::move(node);
}

std::shared_ptr<hl_ast_node> hl_ast_conditional_node::get_condition() {
    return condition;
}
