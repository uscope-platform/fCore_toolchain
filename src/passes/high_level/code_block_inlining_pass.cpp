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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#include "passes/high_level/code_block_inlining_pass.hpp"

code_block_inlining_pass::code_block_inlining_pass() : pass_base<hl_ast_node>("code block inlining pass"){

}

std::shared_ptr<hl_ast_node> code_block_inlining_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> new_content = process_vector(element->get_content());

    ret_val->set_content(new_content);
    return ret_val;
}



std::vector<std::shared_ptr<hl_ast_node>>
code_block_inlining_pass::process_vector(const std::vector<std::shared_ptr<hl_ast_node>>& elements) {
    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    for(auto &item:elements){
        std::vector<std::shared_ptr<hl_ast_node>> processed_content = process_element_by_type(item);
        new_content.insert(new_content.end(),processed_content.begin(), processed_content.end());
    }
    return new_content;
}



std::vector<std::shared_ptr<hl_ast_node>> code_block_inlining_pass::process_element_by_type(std::shared_ptr<hl_ast_node> element) {
    switch (element->node_type) {
        case hl_ast_node_type_expr:
            return process_expression(std::static_pointer_cast<hl_expression_node>(element));
        case hl_ast_node_type_conditional:
            return {process_conditional(std::static_pointer_cast<hl_ast_conditional_node>(element))};
        case hl_ast_node_type_loop:
            return {process_loop(std::static_pointer_cast<hl_ast_loop_node>(element))};
        case hl_ast_node_type_definition:
            return {process_definition(std::static_pointer_cast<hl_definition_node>(element))};
        case hl_ast_node_type_code_block:
            return element->get_content();
        default:
            return {element};
    }
}

std::shared_ptr<hl_ast_node> code_block_inlining_pass::process_loop(std::shared_ptr<hl_ast_loop_node> element) {
    std::shared_ptr<hl_ast_loop_node> ret_val = std::static_pointer_cast<hl_ast_loop_node>(element);
    ret_val->set_loop_content(process_vector(element->get_loop_content()));
    return ret_val;
}

std::shared_ptr<hl_ast_node>
code_block_inlining_pass::process_conditional(std::shared_ptr<hl_ast_conditional_node> element) {
    std::shared_ptr<hl_ast_conditional_node> ret_val = std::static_pointer_cast<hl_ast_conditional_node>(element);
    ret_val->set_if_block(process_vector(element->get_if_block()));
    ret_val->set_else_block(process_vector(element->get_else_block()));
    return ret_val;
}

std::shared_ptr<hl_ast_node> code_block_inlining_pass::process_definition(std::shared_ptr<hl_definition_node> element) {
    if(element->is_initialized()){
        std::vector<std::shared_ptr<hl_ast_node>> content = process_element_by_type(element->get_scalar_initializer());
        if(content.size()>1){
            throw std::runtime_error("INTERNAL ERROR: A DEFINITION CAN NOT BE INITIALIZED WITH MORE THAN A SINGLE EXPRESSION");
        } else {
            element->set_scalar_initializer(content[0]);
        }
    }
    return element;
}

std::vector<std::shared_ptr<hl_ast_node>> code_block_inlining_pass::process_expression(const std::shared_ptr<hl_expression_node>& expr) {
    std::vector<std::shared_ptr<hl_ast_node>> ret_val;
    std::vector<std::shared_ptr<hl_ast_node>> processed_rhs = process_element_by_type(expr->get_rhs());

    unsigned int proc_size = processed_rhs.size();
    if(proc_size>1){
        for(int i = 0; i<proc_size-1; i++) ret_val.push_back(processed_rhs[i]);
        expr->set_rhs(processed_rhs[proc_size-1]);
    } else{
        expr->set_rhs(processed_rhs[0]);
    }

    if(!expr->is_unary()){
        std::vector<std::shared_ptr<hl_ast_node>> processed_lhs = process_element_by_type(expr->get_lhs());
        proc_size = processed_lhs.size();
        if(proc_size>1){
            for(int i = 0; i<proc_size-1; i++) ret_val.push_back(processed_lhs[i]);
            expr->set_lhs(processed_lhs[proc_size-1]);
        } else{
            expr->set_lhs(processed_lhs[0]);
        }
    }

    ret_val.push_back(expr);
    return ret_val;
}


