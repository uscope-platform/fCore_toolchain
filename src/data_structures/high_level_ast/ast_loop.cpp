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
// limitations under the License.30/06/2021.
//

#include "data_structures/high_level_ast/ast_loop.hpp"

namespace fcore{

    ast_loop::ast_loop() : ast_node(hl_ast_node_type_loop){

    }

    std::string ast_loop::pretty_print() {

        std::ostringstream ss;

        ss << "for (" << init_statement->pretty_print()<< "; ";
        ss << condition->pretty_print() << "; ";
        ss << iteration_expr->pretty_print() << ") {"<< std::endl;

        if(!loop_content.empty()){
            for(const auto& item:loop_content){
                ss << ast_node::pretty_print(item) << ";" << std::endl;
            }
        }
        ss<< "}";
        return ss.str();
    }

    std::shared_ptr<ast_loop> ast_loop::deep_copy(const std::shared_ptr<ast_loop> &orig) {
        std::shared_ptr<ast_loop> copied_obj = std::make_shared<ast_loop>();

        copied_obj->set_condition(std::static_pointer_cast<ast_expression>(ast_node::deep_copy(orig->get_condition())));
        copied_obj->set_iteration_expr(std::static_pointer_cast<ast_expression>(ast_node::deep_copy(orig->get_iteration_expr())));
        copied_obj->set_init_statement(std::static_pointer_cast<ast_definition>(ast_node::deep_copy(orig->get_init_statement())));

        std::vector<std::shared_ptr<ast_node>> block;
        for(const auto& i:orig->get_loop_content()){
            block.push_back(ast_node::deep_copy(i));
        }
        copied_obj->set_loop_content(block);

        return copied_obj;
    }

}