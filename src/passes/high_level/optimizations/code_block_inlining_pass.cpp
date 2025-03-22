//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "passes/high_level/optimizations/code_block_inlining_pass.hpp"

namespace fcore{

    code_block_inlining_pass::code_block_inlining_pass() : pass_base("code block inlining pass"){

    }

    std::shared_ptr<ast_code_block> code_block_inlining_pass::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {
        auto ret_val = std::make_shared<ast_code_block>();
        std::vector<std::shared_ptr<ast_node>> new_content = process_vector(element->get_content());

        ret_val->set_content(new_content);
        return ret_val;
    }



    std::vector<std::shared_ptr<ast_node>>
    code_block_inlining_pass::process_vector(const std::vector<std::shared_ptr<ast_node>>& elements) {
        std::vector<std::shared_ptr<ast_node>> new_content;
        for(auto &item:elements){
            std::vector<std::shared_ptr<ast_node>> processed_content = process_element_by_type(item);
            new_content.insert(new_content.end(),processed_content.begin(), processed_content.end());
        }
        return new_content;
    }



    std::vector<std::shared_ptr<ast_node>> code_block_inlining_pass::process_element_by_type(std::shared_ptr<ast_node> element) {
        switch (element->node_type) {
            case hl_ast_node_type_expr:
                return process_expression(std::static_pointer_cast<ast_expression>(element));
            case hl_ast_node_type_conditional:
                return {process_conditional(std::static_pointer_cast<ast_conditional>(element))};
            case hl_ast_node_type_loop:
                return {process_loop(std::static_pointer_cast<ast_loop>(element))};
            case hl_ast_node_type_definition:
                return {process_definition(std::static_pointer_cast<ast_definition>(element))};
            case hl_ast_node_type_code_block:
                return process_code_block(std::static_pointer_cast<ast_code_block>(element));
            case hl_ast_node_type_function_def:
                return process_function_definition(std::static_pointer_cast<ast_function_def>(element));
            default:
                return {element};
        }
    }

    std::shared_ptr<ast_node> code_block_inlining_pass::process_loop(std::shared_ptr<ast_loop> element) {
        std::shared_ptr<ast_loop> ret_val = std::static_pointer_cast<ast_loop>(element);
        ret_val->set_loop_content(process_vector(element->get_loop_content()));
        return ret_val;
    }

    std::shared_ptr<ast_node>
    code_block_inlining_pass::process_conditional(std::shared_ptr<ast_conditional> element) {
        std::shared_ptr<ast_conditional> ret_val = std::static_pointer_cast<ast_conditional>(element);
        ret_val->set_if_block(process_vector(element->get_if_block()));
        ret_val->set_else_block(process_vector(element->get_else_block()));
        return ret_val;
    }

    std::shared_ptr<ast_node> code_block_inlining_pass::process_definition(std::shared_ptr<ast_definition> element) {
        if(element->is_initialized()){
            if(element->is_scalar()){
                std::vector<std::shared_ptr<ast_node>> content = process_element_by_type(element->get_scalar_initializer());
                if(content.size()>1){
                    throw std::runtime_error("A DEFINITION CAN NOT BE INITIALIZED WITH MORE THAN A SINGLE EXPRESSION");
                } else {
                    element->set_scalar_initializer(content[0]);
                }
            } else{
                std::vector<std::shared_ptr<ast_node>> init;

                for(auto &item:element->get_array_initializer()){
                    std::vector<std::shared_ptr<ast_node>> content = process_element_by_type(item);
                    if(content.size()>1){
                        throw std::runtime_error("A DEFINITION CAN NOT BE INITIALIZED WITH MORE THAN A SINGLE EXPRESSION");
                    } else {
                        init.push_back(content[0]);
                    }
                }
                element->set_array_initializer(init);
            }

        }
        return element;
    }

    std::vector<std::shared_ptr<ast_node>> code_block_inlining_pass::process_expression(const std::shared_ptr<ast_expression>& expr) {
        std::vector<std::shared_ptr<ast_node>> ret_val;
        if(!expr->is_immediate()){
            std::vector<std::shared_ptr<ast_node>> processed_rhs = process_element_by_type(expr->get_rhs());

            unsigned int proc_size = processed_rhs.size();
            if(proc_size>1){
                for(uint32_t i = 0; i<proc_size-1; i++) ret_val.push_back(processed_rhs[i]);
                expr->set_rhs(processed_rhs[proc_size-1]);
            } else{
                expr->set_rhs(processed_rhs[0]);
            }


            if(auto lhs = expr->get_lhs()){
                std::vector<std::shared_ptr<ast_node>> processed_lhs = process_element_by_type(lhs.value());
                proc_size = processed_lhs.size();
                if(proc_size>1){
                    for(uint32_t i = 0; i<proc_size-1; i++) ret_val.push_back(processed_lhs[i]);
                    expr->set_lhs(processed_lhs[proc_size-1]);
                } else{
                    expr->set_lhs(processed_lhs[0]);
                }
            }
        }

        ret_val.push_back(expr);
        return ret_val;
    }

    std::vector<std::shared_ptr<ast_node>>
    code_block_inlining_pass::process_code_block(const std::shared_ptr<ast_code_block>& element) {

        std::vector<std::shared_ptr<ast_node>> new_content;

        for(const auto &item:element->get_content()){
            std::vector<std::shared_ptr<ast_node>> processed_element = process_element_by_type(item);
            new_content.insert(new_content.end(),processed_element.begin(), processed_element.end());
        }

        return new_content;
    }

    std::vector<std::shared_ptr<ast_node>>
    code_block_inlining_pass::process_function_definition(const std::shared_ptr<ast_function_def> &fdef) {

        auto new_body = process_vector(fdef->get_body());
        fdef->set_body(new_body);

        return {fdef};
    }

}

