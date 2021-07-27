//
// Created by fils on 17/07/2021.
//

#include "data_structures/high_level_ast/hl_ast_conditional_node.hpp"


hl_ast_conditional_node::hl_ast_conditional_node() : hl_ast_node(hl_ast_node_type_conditional) {
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

    ss << "if (" << condition->pretty_print() << ") {" << std::endl;
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

    ret_val &= hl_ast_node::compare_vectors(lhs.if_block, rhs.if_block);
    ret_val &= hl_ast_node::compare_vectors(lhs.else_block, rhs.else_block);
    ret_val &= hl_ast_node::compare_content_by_type( lhs.condition, rhs.condition);

    return ret_val;
}

void hl_ast_conditional_node::set_condition(std::shared_ptr<hl_ast_node> node) {
    condition = std::move(node);
}

std::shared_ptr<hl_ast_node> hl_ast_conditional_node::get_condition() {
    return condition;
}
