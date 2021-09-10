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

std::shared_ptr<hl_ast_node> array_scalarization_pass::process_element(const std::shared_ptr<hl_ast_node>& node) {
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
            return process_function_def(std::static_pointer_cast<hl_function_def_node>(node));
        case hl_ast_node_type_function_call:
            return process_function_call(std::static_pointer_cast<hl_function_call_node>(node));
        case hl_ast_node_type_loop:
        case hl_ast_node_type_program_root:
        case hl_ast_node_type_code_block:
            throw std::runtime_error("INTERNAL ERROR: Unexpected node found in the AST during array scalarization");
    }
    return nullptr;
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
    if(old_array_idx.empty()){
        throw std::runtime_error("ERROR: All array operations must be performed element wise and thus have a compile time known index");
    }

    std::shared_ptr<variable> var = std::make_shared<variable>(mangle_name(old_array_idx, var_name));

    if(old_array_idx.size() == 1){
        std::shared_ptr<hl_ast_operand> bound_reg_op = std::static_pointer_cast<hl_ast_operand>(old_array_idx[0]);
        if(node->get_variable()->get_bound_reg_array().size()>1)
            var->set_bound_reg(node->get_variable()->get_bound_reg(bound_reg_op->get_int_value()));
    } else{
        std::vector<int> idx;
        idx.reserve(old_array_idx.size());
        for(auto &item:old_array_idx){
            idx.push_back(std::static_pointer_cast<hl_ast_operand>(item)->get_int_value());
        }
        if(def_map[node->get_name()] != nullptr){
            unsigned int linearized_idx = linearize_array(def_map[node->get_name()]->get_array_shape(),idx);
            if(node->get_variable()->get_bound_reg_array().size()!=1){
                var->set_bound_reg(node->get_variable()->get_bound_reg(linearized_idx));
            }
        }
    }



    node->set_variable(var);
    node->set_array_index({});

    return node;
}

std::shared_ptr<hl_definition_node>
array_scalarization_pass::process_definition(std::shared_ptr<hl_definition_node> node) {

    if(!node->is_scalar()) {
        def_map[node->get_name()] = node;
    }

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

std::shared_ptr<hl_function_call_node>
array_scalarization_pass::process_function_call(std::shared_ptr<hl_function_call_node> node) {


    std::vector<std::shared_ptr<hl_ast_node>> new_args;
    for(auto &item:node->get_arguments()){
        new_args.push_back(process_element(item));
    }
    node->set_arguments(new_args);

    return node;
}

std::shared_ptr<hl_function_def_node>
array_scalarization_pass::process_function_def(std::shared_ptr<hl_function_def_node> node) {

    std::vector<std::shared_ptr<hl_ast_node>> new_body;

    for(auto &item:node->get_body()){
        new_body.push_back(process_element(item));
    }
    node->set_body(new_body);
    if(node->get_return() != nullptr){
        node->set_return(process_element(node->get_return()));
    }

    return node;
}

std::shared_ptr<hl_ast_conditional_node>
array_scalarization_pass::process_conditional(std::shared_ptr<hl_ast_conditional_node> node) {
    std::vector<std::shared_ptr<hl_ast_node>> new_block;
    for(auto &item:node->get_if_block()){
        new_block.push_back(process_element(item));
    }
    node->set_if_block(new_block);

    new_block.clear();
    for(auto &item:node->get_else_block()){
        new_block.push_back(process_element(item));
    }
    node->set_else_block(new_block);

    node->set_condition(process_element(node->get_condition()));
    return node;
}




