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

#include "passes/high_level/array_initialization_propagation_pass.h"

array_initialization_propagation_pass::array_initialization_propagation_pass() : pass_base<hl_ast_node>("array initialization propagation pass"){
}


std::shared_ptr<hl_ast_node>
array_initialization_propagation_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_content;

    for(auto &item:element->get_content()){
        new_content.push_back(process_node_by_type(item));
    }

    element->set_content(new_content);
    return element;
}



std::shared_ptr<hl_ast_node>
array_initialization_propagation_pass::process_node_by_type(const std::shared_ptr<hl_ast_node>& node) {
    switch(node->node_type) {
        case hl_ast_node_type_expr:
            return process_expression(std::static_pointer_cast<hl_expression_node>(node));
        case hl_ast_node_type_operand:
            return process_operand(std::static_pointer_cast<hl_ast_operand>(node));
        case hl_ast_node_type_definition:
            return process_definition(std::static_pointer_cast<hl_definition_node>(node));
        case hl_ast_node_type_conditional:
            return process_conditional(std::static_pointer_cast<hl_ast_conditional_node>(node));
        case hl_ast_node_type_function_def:
            return process_function_definition(std::static_pointer_cast<hl_function_def_node>(node));
        case hl_ast_node_type_function_call:
            return process_function_call(std::static_pointer_cast<hl_function_call_node>(node));
        default:
            throw std::runtime_error("INTERNAL ERROR: Unexpected node found in the AST during array scalarization");
    }
}

std::shared_ptr<hl_expression_node>
array_initialization_propagation_pass::process_expression(std::shared_ptr<hl_expression_node> node) {
    if(node->get_type()==expr_assign){
        std::shared_ptr<hl_ast_operand> target = std::static_pointer_cast<hl_ast_operand>(node->get_lhs());
        if(target->get_type() == var_type_array){
            std::vector<int> idx;
            for(auto &item:target->get_array_index()){
                idx.push_back(std::static_pointer_cast<hl_ast_operand>(item)->get_int_value());
            }
            dirty_elements_idx[target->get_name()].push_back(idx);
        }
        node->set_rhs(process_node_by_type(node->get_rhs()));
    } else{
        node->set_rhs(process_node_by_type(node->get_rhs()));
        if(!node->is_unary()){
            node->set_lhs(process_node_by_type(node->get_lhs()));
        }
    }
    return node;
}

std::shared_ptr<hl_ast_operand>
array_initialization_propagation_pass::process_operand(std::shared_ptr<hl_ast_operand> node) {

    if(node->get_type() == var_type_array){
        std::vector<int> idx;
        for(auto &item:node->get_array_index()){
            idx.push_back(std::static_pointer_cast<hl_ast_operand>(item)->get_int_value());
        }

        auto dirty_idx_vect = dirty_elements_idx[node->get_name()];

        if(std::count(dirty_idx_vect.begin(), dirty_idx_vect.end(),idx)){
            return node;
        } else{

            if(def_map.count(node->get_name())==0){
                return node;
            }

            if(!def_map[node->get_name()]->is_initialized()){
                return node;
            }


            std::vector<int> shape = def_map[node->get_name()]->get_array_shape();
            int linearized_idx = idx.back();

            for(int i = idx.size()-2; i>=0; --i){
                int interm_factor = 1;
                for(int j = shape.size()-1; j>i; --j){
                     interm_factor *= idx[i]*shape[j];
                }
                linearized_idx += interm_factor;
            }
            return  std::static_pointer_cast<hl_ast_operand>(def_map[node->get_name()]->get_array_initializer()[linearized_idx]);
        }
    } else{
        return node;
    }
}

std::shared_ptr<hl_definition_node>
array_initialization_propagation_pass::process_definition(std::shared_ptr<hl_definition_node> node) {

    if(!node->is_scalar()) {
        def_map[node->get_name()] = node;
        dirty_elements_idx[node->get_name()] = std::vector<std::vector<int>>();
    } else {
        if(node->is_initialized()){
            node->set_scalar_initializer(process_node_by_type(node->get_scalar_initializer()));
        }

    }
    return node;
}

std::shared_ptr<hl_function_def_node>
array_initialization_propagation_pass::process_function_definition(std::shared_ptr<hl_function_def_node> node) {
    std::vector<std::shared_ptr<hl_ast_node>> new_body;

    for(auto &item:node->get_body()){
        new_body.push_back(process_node_by_type(item));
    }
    node->set_body(new_body);
    if(node->get_return() != nullptr){
        node->set_return(process_node_by_type(node->get_return()));
    }

    return node;
}

std::shared_ptr<hl_function_call_node>
array_initialization_propagation_pass::process_function_call(std::shared_ptr<hl_function_call_node> node) {

    std::vector<std::shared_ptr<hl_ast_node>> new_args;
    for(auto &item:node->get_arguments()){
        new_args.push_back(process_node_by_type(item));
    }
    node->set_arguments(new_args);

    return node;
}

std::shared_ptr<hl_ast_conditional_node>
array_initialization_propagation_pass::process_conditional(std::shared_ptr<hl_ast_conditional_node> node) {

    std::vector<std::shared_ptr<hl_ast_node>> new_block;
    for(auto &item:node->get_if_block()){
        new_block.push_back(process_node_by_type(item));
    }
    node->set_if_block(new_block);

    new_block.clear();
    for(auto &item:node->get_else_block()){
        new_block.push_back(process_node_by_type(item));
    }
    node->set_else_block(new_block);

    node->set_condition(process_node_by_type(node->get_condition()));
    return node;
}


