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
// limitations under the License.05/07/2021.
//

#include "passes/high_level/constant_propagation.hpp"

constant_propagation::constant_propagation() : pass_base<hl_ast_node>("Constant Propagation Pass"){
}

std::shared_ptr<hl_ast_node> constant_propagation::process_global(std::shared_ptr<hl_ast_node> element) {

    constants_map.clear();
    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    std::vector<std::shared_ptr<hl_ast_node>> content = element->get_content();
    for(auto & i : content){
        if(i->node_type == hl_ast_node_type_definition){
            std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(i);
            if(node->get_name().rfind("IOM_init_constant_", 0) == 0){
                new_content.push_back(i);
            } else if(node->get_variable()->get_variable_class() != variable_regular_type || !node->is_initialized()) {
                new_content.push_back(i);
            } else if(node->get_scalar_initializer()->node_type == hl_ast_node_type_operand){
                std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(
                        node->get_scalar_initializer());
                if(op->get_type() == var_type_float_const || op->get_type() == var_type_int_const)
                    constants_map.insert(std::make_pair(node->get_name(), op));
                else{
                    new_content.push_back(i);
                }
            } else {
                new_content.push_back(i);
            }
        } else {
            new_content.push_back(i);
        }
    }

    content.clear();
    content.reserve(new_content.size());

    for(auto & i : new_content){
        auto new_item = substitute_constant(i);
        content.push_back(new_item);
    }
    element->set_content(content);
    return element;

}

std::shared_ptr<hl_ast_node> constant_propagation::substitute_constant(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        if(node->is_unary() || node->get_type() == expr_assign){
            std::shared_ptr<hl_ast_node> new_rhs;
            if(node->get_rhs()->node_type == hl_ast_node_type_operand) {
                new_rhs = process_operand(std::static_pointer_cast<hl_ast_operand>(node->get_rhs()));
            } else {
                new_rhs = substitute_constant(node->get_rhs());
            }
            node->set_rhs(new_rhs);
            return node;
        } else{
            std::shared_ptr<hl_ast_node> new_lhs;
            std::shared_ptr<hl_ast_node> new_rhs;


            if(node->get_rhs()->node_type == hl_ast_node_type_operand) {
                std::shared_ptr<hl_ast_operand> rhs = std::static_pointer_cast<hl_ast_operand>(node->get_rhs());
                new_rhs = process_operand(rhs);
            } else {
                new_rhs = substitute_constant(node->get_rhs());
            }

            if(node->get_lhs()->node_type == hl_ast_node_type_operand) {
                std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(node->get_lhs());
                new_lhs = process_operand(lhs);
            } else {
                new_rhs = substitute_constant(node->get_rhs());
            }

            node->set_rhs(new_rhs);
            node->set_lhs(new_lhs);

            return node;
        }
    } else if(element->node_type == hl_ast_node_type_definition){
        std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(element);
        if(node->is_initialized()){
            std::shared_ptr<hl_ast_node> new_init = substitute_constant(node->get_scalar_initializer());
            node->set_scalar_initializer(new_init);

        }
        return node;
    } else{
        return element;
    }
}

std::shared_ptr<hl_ast_operand> constant_propagation::process_operand(std::shared_ptr<hl_ast_operand> element) {
    if(element->get_type() == var_type_scalar || element->get_type() == var_type_array){
        if(constants_map.count(element->get_name())>0){
            return constants_map[element->get_name()];
        } else{
            return element;
        }

    } else
        return element;
}
