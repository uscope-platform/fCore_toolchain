// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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

#include "passes/high_level/contiguous_array_identification.hpp"

contiguous_array_identification::contiguous_array_identification() : pass_base<hl_ast_node>("contiguous_array_identification"){
    process_efi_return = false;
    process_efi_arguments = false;
}

std::shared_ptr<hl_ast_node> contiguous_array_identification::process_global(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_loop_content;
    for(auto &item:element->get_content()){
        new_loop_content.push_back(process_element(item));
    }
    element->set_content(new_loop_content);

    // A second pass is necessary to make shure the array definition nodes are marked correctly
    new_loop_content.clear();
    for(auto &item:element->get_content()){
        new_loop_content.push_back(process_element(item));
    }
    element->set_content(new_loop_content);

    return element;
}


std::shared_ptr<hl_ast_node> contiguous_array_identification::process_element(std::shared_ptr<hl_ast_node> element) {
        switch (element->node_type) {
            case hl_ast_node_type_function_call:
                return process_element(std::static_pointer_cast<hl_function_call_node>(element));
            case hl_ast_node_type_expr:
                return process_element(std::static_pointer_cast<hl_expression_node>(element));
            case hl_ast_node_type_definition:
                return process_element(std::static_pointer_cast<hl_definition_node>(element));
            case hl_ast_node_type_conditional:
                return process_element(std::static_pointer_cast<hl_ast_conditional_node>(element));
            case hl_ast_node_type_loop:
                return process_element(std::static_pointer_cast<hl_ast_loop_node>(element));
            case hl_ast_node_type_function_def:
                return process_element(std::static_pointer_cast<hl_function_def_node>(element));
            case hl_ast_node_type_operand:
                return process_element(std::static_pointer_cast<hl_ast_operand>(element));
            case hl_ast_node_type_code_block:
                throw std::runtime_error("unexpected code block in contiguous array identification pass");
            case hl_ast_node_type_program_root:
                throw std::runtime_error("unexpected nested program root in contiguous array identification pass");
            default:
                throw std::runtime_error("Internal erorr, this condition should never happern");
        }

}


std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_expression_node> element) {
    if(element->is_immediate()) return element;
    element->set_rhs(process_element(element->get_rhs()));
    if(!element->is_unary()){
        auto lhs = element->get_lhs();
        if(element->get_type()!=expr_assign){
            element->set_lhs(process_element(lhs));
        } else{
            auto lhs_op= std::static_pointer_cast<hl_ast_operand>(lhs);

            if(contiguous_arrays.contains(lhs_op->get_name())){
                process_efi_return = false;
            }else if(process_efi_return){
                process_efi_return = false;
                if(lhs_op->get_variable()->get_bound_reg_array()[0] == -1){
                    lhs_op->set_contiguity(true);
                    contiguous_arrays.insert(lhs_op->get_name());
                }
            }
        }
    }
    return element;
}

std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_definition_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_initializer;
    for(auto &item:element->get_array_initializer()){
        new_initializer.push_back(process_element(item));
    }
    element->set_array_initializer(new_initializer);

    std::vector<std::shared_ptr<hl_ast_node>> new_index;
    for(auto &item:element->get_array_index()){
        new_index.push_back(process_element(item));
    }
    element->set_array_index(new_index);

    if(contiguous_arrays.contains(element->get_variable()->get_name())){
        element->get_variable()->set_contiguity(true);
    }
    return element;
}

std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_ast_loop_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_loop_content;
    for(auto &item:element->get_loop_content()){
        new_loop_content.push_back(process_element(item));
    }
    element->set_loop_content(new_loop_content);
    return element;
}

std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_ast_conditional_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_loop_content;
    for(auto &item:element->get_if_block()){
        new_loop_content.push_back(process_element(item));
    }
    element->set_if_block(new_loop_content);

    new_loop_content.clear();
    for(auto &item:element->get_else_block()){
        new_loop_content.push_back(process_element(item));
    }
    element->set_else_block(new_loop_content);
    return element;
}

std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_function_def_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_body;
    for(auto &item:element->get_body()){
        new_body.push_back(process_element(item));
    }
    element->set_body(new_body);

    if(element->has_return()){
        element->set_return(process_element(element->get_return()));
    }
    return element;
}


std::shared_ptr<hl_ast_node> contiguous_array_identification::process_element(std::shared_ptr<hl_function_call_node> element) {
    auto name = element->get_name();
    if(name == "efi"){
        process_efi_return = true;

        process_efi_arguments = true;
        std::vector<std::shared_ptr<hl_ast_node>> new_args;
        for(auto &item:element->get_arguments()){
            if(std::static_pointer_cast<hl_ast_operand>(element->get_arguments()[0])->get_variable()->get_bound_reg_array()[0] == -1){
                new_args.push_back(process_element(item));
            } else{
                new_args.push_back(item);
            }
        }
        element->set_arguments(new_args);

        process_efi_arguments = false;
    }


    return element;
}


std::shared_ptr<hl_ast_node> contiguous_array_identification::process_element(std::shared_ptr<hl_ast_operand> element) {
    if(contiguous_arrays.contains(element->get_name())){
        element->set_contiguity(true);
    }
    if(process_efi_arguments && (element->get_type()!=var_type_int_const && element->get_type()!=var_type_float_const)){
        contiguous_arrays.insert(element->get_name());
        element->set_contiguity(true);
    }
    return element;
}
