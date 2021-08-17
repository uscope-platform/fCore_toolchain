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

#include "passes/high_level/array_scalarization_pass.hpp"

array_scalarization_pass::array_scalarization_pass() : pass_base<hl_ast_node>("array scalarization pass"){
    loop_variable_counter = 0;
}

std::shared_ptr<hl_ast_node> array_scalarization_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> new_content;

    for(auto &item:element->get_content()){
        new_content.push_back(process_element(item));
    }
    ret_val->set_content(new_content);
    return ret_val;
}

std::shared_ptr<hl_ast_node> array_scalarization_pass::process_element(std::shared_ptr<hl_ast_node> node) {
    switch(node->node_type) {
        case hl_ast_node_type_expr:
            return process_expression(std::static_pointer_cast<hl_expression_node>(node));
        case hl_ast_node_type_operand:
            return process_operand(std::static_pointer_cast<hl_ast_operand>(node));
        case hl_ast_node_type_definition:
            return process_definition(std::static_pointer_cast<hl_definition_node>(node));
        case hl_ast_node_type_conditional:
        case hl_ast_node_type_loop:
        case hl_ast_node_type_function_def:
        case hl_ast_node_type_function_call:
        case hl_ast_node_type_program_root:
        case hl_ast_node_type_code_block:
            throw std::runtime_error("INTERNAL ERROR: Unexpected node found in the AST during array scalarization");
    }
}

std::shared_ptr<hl_expression_node>
array_scalarization_pass::process_expression(std::shared_ptr<hl_expression_node> node) {
    if(!node->is_unary()){
        node->set_lhs(process_element(node->get_lhs()));
    }
    node->set_rhs(process_element(node->get_rhs()));
    return node;
}

std::shared_ptr<hl_ast_operand> array_scalarization_pass::process_operand(std::shared_ptr<hl_ast_operand> node) {
    if(node->get_variable()->get_type() != var_type_array)
        return node;

    std::vector<std::shared_ptr<hl_ast_node>> old_array_idx = node->get_array_index();
    std::string var_name = node->get_variable()->get_name();

    std::shared_ptr<variable> var = std::make_shared<variable>(mangle_name(old_array_idx, var_name));
    node->set_variable(var);
    node->set_array_index({});

    return node;
}

std::shared_ptr<hl_definition_node>
array_scalarization_pass::process_definition(std::shared_ptr<hl_definition_node> node) {

    if(node->is_initialized()){
        node->set_scalar_initializer(process_element(node->get_scalar_initializer()));
    }
    if(node->get_variable()->get_type() != var_type_array || !node->is_initialized())
        return node;

    std::vector<std::shared_ptr<hl_ast_node>> old_array_idx = node->get_array_index();
    std::string var_name = node->get_variable()->get_name();

    std::shared_ptr<variable> var = std::make_shared<variable>(mangle_name(old_array_idx, var_name));

    node->set_variable(var);
    node->set_array_index({});

    return node;
}

std::string array_scalarization_pass::mangle_name(std::vector<std::shared_ptr<hl_ast_node>> old_array_idx, std::string var_name) {


    std::vector<std::shared_ptr<hl_ast_node>> new_array_idx;
    std::string mangled_name = "_fcmglr_flattened_array_"+  var_name;
    for(auto &item:old_array_idx){
        int idx = std::static_pointer_cast<hl_ast_operand>(item)->get_int_value();
        mangled_name += "_" + std::to_string(idx);
    }
    return mangled_name;
}



