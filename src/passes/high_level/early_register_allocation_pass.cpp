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


#include "passes/high_level/early_register_allocation_pass.hpp"

#include <utility>


early_register_allocation_pass::early_register_allocation_pass(
        const std::unordered_map<std::string, std::shared_ptr<variable>>& iom,
        std::shared_ptr<std::unordered_map<std::string, memory_range_t>> bm
) : pass_base<hl_ast_node>("Early register allocation"),
                                                                                                                                 mem_tracker({1,pow(2, fcore_register_address_width)-1}){
    bindings_map = std::move(bm);
    for( auto&item:iom){
        if(item.second->get_variable_class() == variable_memory_type || item.second->get_variable_class() == variable_output_type || item.second->get_variable_class() == variable_input_type){
            for(auto &idx:item.second->get_bound_reg_array()){
                mem_tracker.reserve_register(idx);
            }
        }
    }

}

std::shared_ptr<hl_ast_node> early_register_allocation_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    for(auto &item:element->get_content()){
        new_content.push_back(process_element(item));
    }
    element->set_content(new_content);
    return element;
}

std::shared_ptr<hl_ast_node> early_register_allocation_pass::process_element(std::shared_ptr<hl_ast_node> element) {

    switch(element->node_type) {
        case hl_ast_node_type_expr:
            return process_element(std::static_pointer_cast<hl_expression_node>(element));
        case hl_ast_node_type_definition:
            return process_element(std::static_pointer_cast<hl_definition_node>(element));
        case hl_ast_node_type_conditional:
            return process_element(std::static_pointer_cast<hl_ast_conditional_node>(element));
        case hl_ast_node_type_operand:
            return process_element(std::static_pointer_cast<hl_ast_operand>(element));
        case hl_ast_node_type_loop:
        case hl_ast_node_type_function_def:
        case hl_ast_node_type_function_call:
        case hl_ast_node_type_program_root:
        case hl_ast_node_type_code_block:
        default:
            throw std::runtime_error("Unexpected node type encountered during early register allocation");
    }

}

std::shared_ptr<hl_ast_node>
early_register_allocation_pass::process_element(std::shared_ptr<hl_definition_node> element) {
    if(element->is_initialized()){
        std::vector<std::shared_ptr<hl_ast_node>> content;
        for(auto &item:element->get_array_initializer()){
            content.push_back(process_element(item));
        }
        element->set_array_initializer(content);
    }

    std::vector<std::shared_ptr<hl_ast_node>> content;
    for(auto &item:element->get_array_index()){
        content.push_back(process_element(item));
    }
    element->set_array_index(content);

    if(element->get_variable()->is_contiguous()){
        uint32_t size  = 0;
        for(auto &item:element->get_array_index()){
            size += std::static_pointer_cast<hl_ast_operand>(item)->get_int_value();
        }
        element->set_variable(allocate_contiguous_array(element->get_variable(), size));
    }

    return element;
}

std::shared_ptr<hl_ast_node>
early_register_allocation_pass::process_element(std::shared_ptr<hl_ast_conditional_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> content;
    for(auto &item:element->get_if_block()){
        content.push_back(process_element(item));
    }
    element->set_if_block(content);

    content.clear();
    for(auto &item:element->get_else_block()){
        content.push_back(process_element(item));
    }
    element->set_else_block(content);

    return element;
}

std::shared_ptr<hl_ast_node> early_register_allocation_pass::process_element(std::shared_ptr<hl_ast_operand> element) {
    if(bindings_map->contains(element->get_name())){
        auto bound_reg = std::vector<int>();
        for(int i=bindings_map->at(element->get_name()).first; i<bindings_map->at(element->get_name()).second; i++){
            bound_reg.push_back(i);
        }
        element->get_variable()->set_bound_reg_array(bound_reg);
    }
    return element;
}

std::shared_ptr<hl_ast_node>
early_register_allocation_pass::process_element(std::shared_ptr<hl_expression_node> element) {
    if(element->is_immediate()) return element;
    if(!element->is_unary()) element->set_lhs(process_element(element->get_lhs()));
    element->set_rhs(process_element(element->get_rhs()));
    return element;

}



std::shared_ptr<variable> early_register_allocation_pass::allocate_contiguous_array(std::shared_ptr<variable> v, uint32_t size) {
    memory_range_t allocation = mem_tracker.get_free_memory_range(size);
    std::vector<int> bound_reg;
    for(int i=allocation.first; i<allocation.second; i++){
        bound_reg.push_back(i);
    }
    v->set_bound_reg_array(bound_reg);
    bindings_map->insert({v->get_name(), allocation});
    return v;
}

