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

#include "data_structures/high_level_ast/hl_ast_conditional_node.hpp"

namespace fcore{

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

    void hl_ast_conditional_node::set_condition(std::shared_ptr<hl_ast_node> node) {
        condition = std::move(node);
    }

    std::shared_ptr<hl_ast_node> hl_ast_conditional_node::get_condition() {
        return condition;
    }

    std::shared_ptr<hl_ast_conditional_node>
    hl_ast_conditional_node::deep_copy(const std::shared_ptr<hl_ast_conditional_node> &orig) {
        std::shared_ptr<hl_ast_conditional_node> copied_obj = std::make_shared<hl_ast_conditional_node>();


        std::shared_ptr<hl_ast_node> cond = hl_ast_node::deep_copy(orig->get_condition());
        copied_obj->set_condition(cond);


        std::vector<std::shared_ptr<hl_ast_node>> block;
        for(const auto& i:orig->get_if_block()){
            block.push_back(hl_ast_node::deep_copy(i));
        }
        copied_obj->set_if_block(block);

        block.clear();
        for(const auto& i:orig->get_else_block()){
            block.push_back(hl_ast_node::deep_copy(i));
        }
        copied_obj->set_else_block(block);

        copied_obj->set_ternary(orig->is_ternary());

        return copied_obj;
    }

}