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

#include "passes/high_level/array_initialization_propagation_pass.h"

array_initialization_propagation_pass::array_initialization_propagation_pass() : pass_base<hl_ast_node>("array initialization propagation pass"){
}


std::shared_ptr<hl_ast_node>
array_initialization_propagation_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_content;

    for(auto &item:element->get_content()){
        std::vector<std::shared_ptr<hl_ast_node>> content = process_node_by_type(item);
        new_content.insert( new_content.end(), content.begin(), content.end());
    }

    element->set_content(new_content);
    return element;
}



std::vector<std::shared_ptr<hl_ast_node>>
array_initialization_propagation_pass::process_node_by_type(const std::shared_ptr<hl_ast_node>& node) {
    switch(node->node_type) {
        case hl_ast_node_type_expr:
            return {process_expression(std::static_pointer_cast<hl_expression_node>(node))};
        case hl_ast_node_type_operand:
            return {process_operand(std::static_pointer_cast<hl_ast_operand>(node))};
        case hl_ast_node_type_definition:
            return process_definition(std::static_pointer_cast<hl_definition_node>(node));
        case hl_ast_node_type_conditional:
            return {process_conditional(std::static_pointer_cast<hl_ast_conditional_node>(node))};
        case hl_ast_node_type_function_def:
            return {process_function_definition(std::static_pointer_cast<hl_function_def_node>(node))};
        case hl_ast_node_type_loop:
            return {process_loop(std::static_pointer_cast<hl_ast_loop_node>(node))};
        case hl_ast_node_type_function_call:
            return {process_function_call(std::static_pointer_cast<hl_function_call_node>(node))};
        default:
            throw std::runtime_error("INTERNAL ERROR: Unexpected node found in the AST during array initialization propagation");
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
        node->set_rhs(process_node_by_type(node->get_rhs())[0]);
    } else{
        node->set_rhs(process_node_by_type(node->get_rhs())[0]);
        if(!node->is_unary()){
            node->set_lhs(process_node_by_type(node->get_lhs())[0]);
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

            unsigned int linearized_idx = linearize_array(shape, idx);
            std::shared_ptr<hl_ast_operand> ret_operand = std::static_pointer_cast<hl_ast_operand>(hl_ast_node::deep_copy(def_map[node->get_name()]->get_array_initializer()[linearized_idx]));
            ret_operand->set_name(node->get_name());
            ret_operand->get_variable()->set_bound_reg(node->get_variable()->get_bound_reg());
            ret_operand->get_variable()->set_variable_class(node->get_variable()->get_variable_class());
            return  ret_operand;
        }
    } else{
        return node;
    }
}

std::vector<std::shared_ptr<hl_ast_node>>
array_initialization_propagation_pass::process_definition(std::shared_ptr<hl_definition_node> node) {

    if(!node->is_scalar()) {
        def_map[node->get_name()] = node;
        dirty_elements_idx[node->get_name()] = std::vector<std::vector<int>>();
        //ADD DEFINITIONS FOR THE IOMs IN THE INSTRUCTION STREAM TO AVOID THEM BEING INLINED
        if(node->is_initialized()){
            std::vector<std::shared_ptr<hl_ast_node>> ret_val;
            if( node->get_variable()->get_variable_class() == variable_memory_type ||  node->get_variable()->get_variable_class() == variable_output_type) {
                for(int i = 0; i<node->get_variable()->get_bound_reg_array().size(); ++i){
                    if(node->get_array_initializer()[i]->node_type != hl_ast_node_type_operand)
                        throw std::runtime_error("ERROR: Non constant initialization of arrays is not allowed.");

                    std::string produced_var = "IOM_init_constant_"+std::to_string(n_init_iom);
                    std::shared_ptr<variable> definition_var = std::make_shared<variable>(produced_var);
                    definition_var->set_bound_reg(node->get_variable()->get_bound_reg_array()[i]);
                    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>(produced_var, c_type_float, definition_var);
                    std::shared_ptr<hl_ast_operand> initializer = std::static_pointer_cast<hl_ast_operand>(hl_ast_node::deep_copy(node->get_array_initializer()[i]));
                    def->set_scalar_initializer(initializer);
                    ret_val.push_back(def);
                    n_init_iom++;
                }
            };
            ret_val.push_back(node);
            return ret_val;
        }

    } else {
        if(node->is_initialized()){
            node->set_scalar_initializer(process_node_by_type(node->get_scalar_initializer())[0]);
        }

    }
    return {node};
}

std::shared_ptr<hl_function_def_node>
array_initialization_propagation_pass::process_function_definition(std::shared_ptr<hl_function_def_node> node) {
    std::vector<std::shared_ptr<hl_ast_node>> new_body;

    for(auto &item:node->get_body()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_items = process_node_by_type(item);
        if(processed_items.size()>1){
            new_body.insert(new_body.end(), processed_items.begin(), processed_items.end());
        } else{
            new_body.push_back(process_node_by_type(item)[0]);
        }
    }
    node->set_body(new_body);
    if(node->get_return() != nullptr){
        node->set_return(process_node_by_type(node->get_return())[0]);
    }

    return node;
}

std::shared_ptr<hl_function_call_node>
array_initialization_propagation_pass::process_function_call(std::shared_ptr<hl_function_call_node> node) {

    std::vector<std::shared_ptr<hl_ast_node>> new_args;
    for(auto &item:node->get_arguments()){
        new_args.push_back(process_node_by_type(item)[0]);
    }
    node->set_arguments(new_args);

    return node;
}

std::shared_ptr<hl_ast_conditional_node>
array_initialization_propagation_pass::process_conditional(std::shared_ptr<hl_ast_conditional_node> node) {

    std::vector<std::shared_ptr<hl_ast_node>> new_block;
    for(auto &item:node->get_if_block()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_items = process_node_by_type(item);
        if(processed_items.size()>1){
            new_block.insert(new_block.end(), processed_items.begin(), processed_items.end());
        } else{
            new_block.push_back(process_node_by_type(item)[0]);
        }
    }
    node->set_if_block(new_block);

    new_block.clear();
    for(auto &item:node->get_else_block()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_items = process_node_by_type(item);
        if(processed_items.size()>1){
            new_block.insert(new_block.end(), processed_items.begin(), processed_items.end());
        } else{
            new_block.push_back(process_node_by_type(item)[0]);
        }
    }
    node->set_else_block(new_block);

    node->set_condition(process_node_by_type(node->get_condition())[0]);
    return node;
}

std::shared_ptr<hl_ast_loop_node>
array_initialization_propagation_pass::process_loop(std::shared_ptr<hl_ast_loop_node> node) {

    node->set_init_statement(std::static_pointer_cast<hl_definition_node>(process_node_by_type(node->get_init_statement())[0]));
    node->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(process_node_by_type(node->get_iteration_expr())[0]));
    node->set_condition(std::static_pointer_cast<hl_expression_node>(process_node_by_type(node->get_condition())[0]));

    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    for(auto &item:node->get_loop_content()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_items = process_node_by_type(item);
        if(processed_items.size()>1){
            new_content.insert(new_content.end(), processed_items.begin(), processed_items.end());
        } else{
            new_content.push_back(process_node_by_type(item)[0]);
        }

    }
    node->set_loop_content(new_content);

    return node;
}


