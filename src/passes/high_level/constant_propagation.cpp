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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.05/07/2021.
//

#include "passes/high_level/constant_propagation.hpp"

constant_propagation::constant_propagation() : pass_base<hl_ast_node>("Constant Propagation Pass"){
}

std::shared_ptr<hl_ast_node> constant_propagation::process_global(std::shared_ptr<hl_ast_node> element) {


    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    std::vector<std::shared_ptr<hl_ast_node>> content = element->get_content();
    for(auto & i : content){
        if(i->node_type == hl_ast_node_type_definition){
            std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(i);
            if(node->get_variable()->variable_class != variable_regular_type) {
                new_content.push_back(i);
            } else if(node->get_initializer()->node_type == hl_ast_node_type_operand){
                std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(node->get_initializer());
                if(op->get_type() == float_immediate_operand || op->get_type() == integer_immediate_operand)
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
        if(node->is_unary()){
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
        std::shared_ptr<hl_ast_node> new_init = substitute_constant(node->get_initializer());
        node->set_initializer(new_init);
        return node;
    } else{
        return element;
    }
}

std::shared_ptr<hl_ast_operand> constant_propagation::process_operand(std::shared_ptr<hl_ast_operand> element) {
    if(element->get_type() == variable_operand){
        if(constants_map.count(element->get_name())>0){
            return constants_map[element->get_name()];
        } else{
            return element;
        }

    } else
        return element;
}
