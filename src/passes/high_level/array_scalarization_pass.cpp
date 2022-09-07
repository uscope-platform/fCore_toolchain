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
    if(node->is_immediate()){
        return node;
    }
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
        int idx;
        if(bound_reg_op->get_variable()->is_constant()){
            idx = bound_reg_op->get_int_value();
        } else {
            std::string idx_var_name = bound_reg_op->get_name();
            auto idx_val_def= def_map_s[idx_var_name];
            idx = evaluate_index_definition(idx_val_def);
        }


        if(node->get_variable()->get_bound_reg_array().size()>1)
            var->set_bound_reg(node->get_variable()->get_bound_reg(idx));

    } else{

        std::vector<int> idx;
        idx.reserve(old_array_idx.size());

        for(auto &item:old_array_idx){
            auto bound_reg_op = std::static_pointer_cast<hl_ast_operand>(item);
            if(bound_reg_op->get_variable()->is_constant()){
                idx.push_back(bound_reg_op->get_int_value());
            } else {
                std::string idx_var_name = bound_reg_op->get_name();
                auto idx_val_def= def_map_s[idx_var_name];
                idx.push_back(evaluate_index_definition(idx_val_def));
            }
        }

        unsigned int linearized_idx = linearize_array(def_map_vect[node->get_name()]->get_array_shape(), idx);
        if(node->get_variable()->get_bound_reg_array().size()!=1){
            var->set_bound_reg(node->get_variable()->get_bound_reg(linearized_idx));
        }
    }

    node->set_variable(var);
    node->set_array_index({});

    return node;
}

std::shared_ptr<hl_definition_node>
array_scalarization_pass::process_definition(std::shared_ptr<hl_definition_node> node) {

    if(!node->is_scalar()) {
        def_map_vect[node->get_name()] = node;
    } else{
        def_map_s[node->get_name()] = node;
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
        auto  idx_var = std::static_pointer_cast<hl_ast_operand>(item);
        if(idx_var->get_variable()->is_constant()){
            int idx = idx_var->get_int_value();
            mangled_name += "_" + std::to_string(idx);
        } else {
            std::string idx_var_name = idx_var->get_name();
            auto idx_val_def= def_map_s[idx_var_name];
            auto idx = evaluate_index_definition(idx_val_def);
            mangled_name += "_" + std::to_string(idx);

        }
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

int array_scalarization_pass::evaluate_index_definition(std::shared_ptr<hl_definition_node> node) {
    if(node->is_initialized()){
        if(node->get_scalar_initializer()->node_type == hl_ast_node_type_expr){
            expression_evaluator ev;
            if(ev.is_constant_expression(std::static_pointer_cast<hl_expression_node>(node->get_scalar_initializer()))){
                return ev.evaluate_expression(std::static_pointer_cast<hl_expression_node>(node->get_scalar_initializer()))->get_int_value();
            } else {
                throw std::runtime_error("ERROR: Encountered a non-constant array index expression");
            }
        } else if(node->get_scalar_initializer()->node_type == hl_ast_node_type_operand){
            auto operand = std::static_pointer_cast<hl_ast_operand>(node->get_scalar_initializer());
            if(operand->get_variable()->is_constant()){
                return operand->get_int_value();
            } else{
                throw std::runtime_error("ERROR: Encountered a non-constant array index operand");
            }
        } else {
            throw std::runtime_error("ERROR: Encountered a foreign node type while evaluating an array index");
        }
    } else {
        throw std::runtime_error("ERROR: Encountered a non-initialized array index");
    }

}