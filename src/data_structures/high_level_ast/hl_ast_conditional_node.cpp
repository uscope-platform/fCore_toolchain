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
