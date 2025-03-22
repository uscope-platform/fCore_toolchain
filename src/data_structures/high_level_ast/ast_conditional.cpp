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

#include "data_structures/high_level_ast/ast_conditional.hpp"

namespace fcore{

    ast_conditional::ast_conditional() : ast_node(hl_ast_node_type_conditional) {
    }

    void ast_conditional::set_if_block(std::vector<std::shared_ptr<ast_node>> node) {
        if_block = std::move(node);
    }

    std::vector<std::shared_ptr<ast_node>> ast_conditional::get_if_block() {
        return if_block;
    }

    void ast_conditional::set_else_block(std::vector<std::shared_ptr<ast_node>> node) {
        else_block = std::move(node);
    }

    std::vector<std::shared_ptr<ast_node>> ast_conditional::get_else_block() {
        return else_block;
    }

    std::string ast_conditional::pretty_print() {

        std::ostringstream ss;

        ss << "if (" << ast_node::pretty_print(condition)<< ") {" << std::endl;
        if(!if_block.empty()){
            for(const auto& item:if_block){
                ss << ast_node::pretty_print(item) << ";" << std::endl;
            }
        }
        if(!else_block.empty()){
            ss << "} else {" << std::endl;
            for(const auto& item:else_block){
                ss << ast_node::pretty_print(item) << ";" << std::endl;
            }
        }
        ss<< "}";
        return ss.str();
    }

    void ast_conditional::set_condition(std::shared_ptr<ast_node> node) {
        condition = std::move(node);
    }

    std::shared_ptr<ast_node> ast_conditional::get_condition() {
        return condition;
    }

    std::shared_ptr<ast_conditional>
    ast_conditional::deep_copy(const std::shared_ptr<ast_conditional> &orig) {
        std::shared_ptr<ast_conditional> copied_obj = std::make_shared<ast_conditional>();


        std::shared_ptr<ast_node> cond = ast_node::deep_copy(orig->get_condition());
        copied_obj->set_condition(cond);


        std::vector<std::shared_ptr<ast_node>> block;
        for(const auto& i:orig->get_if_block()){
            block.push_back(ast_node::deep_copy(i));
        }
        copied_obj->set_if_block(block);

        block.clear();
        for(const auto& i:orig->get_else_block()){
            block.push_back(ast_node::deep_copy(i));
        }
        copied_obj->set_else_block(block);

        copied_obj->set_ternary(orig->is_ternary());

        return copied_obj;
    }

}