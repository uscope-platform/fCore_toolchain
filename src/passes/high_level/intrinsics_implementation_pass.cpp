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
// limitations under the License.

#include "passes/high_level/intrinsics_implementation_pass.hpp"

namespace fcore {

    intrinsics_implementation_pass::intrinsics_implementation_pass() : pass_base(
            "intrinsics implementation pass") {
        substitutions = {
                std::make_pair("itf", expr_itf),
                std::make_pair("fti", expr_fti),
                std::make_pair("satp", expr_satp),
                std::make_pair("satn", expr_satn),
                std::make_pair("abs", expr_abs),
                std::make_pair("popcnt", expr_popcnt),
                std::make_pair("efi", expr_efi),
                std::make_pair("bset", expr_bset),
                std::make_pair("bsel", expr_bsel),
                std::make_pair("nop", expr_nop)
        };
        n_arguments = {
                std::make_pair("itf", 1),
                std::make_pair("fti", 1),
                std::make_pair("satp", 2),
                std::make_pair("satn", 2),
                std::make_pair("abs", 1),
                std::make_pair("popcnt", 1),
                std::make_pair("efi", 2),
                std::make_pair("binv", 2),
                std::make_pair("bset", 3),
                std::make_pair("bsel", 2),
                std::make_pair("bclr", 2),
                std::make_pair("nop", 0)
        };
    }

    std::shared_ptr<hl_ast_node> intrinsics_implementation_pass::process_global(std::shared_ptr<hl_ast_node> element) {
        std::shared_ptr<hl_ast_root> ret_val = std::make_shared<hl_ast_root>();
        std::vector<std::shared_ptr<hl_ast_node>> new_content;
        for (auto &item: element->get_content()) {
            new_content.push_back(process_node_by_type(item));
        }
        ret_val->set_content(new_content);
        return ret_val;
    }


    std::shared_ptr<hl_ast_node>
    intrinsics_implementation_pass::process_node_by_type(const std::shared_ptr<hl_ast_node> &element) {


        if (!element->is_terminal()) {
            if (element->node_type == hl_ast_node_type_function_def) {
                std::shared_ptr<hl_function_def_node> node = std::static_pointer_cast<hl_function_def_node>(element);

                std::vector<std::shared_ptr<hl_ast_node>> body = node->get_body();
                for (auto &i: body) {
                    i = process_node_by_type(i);
                }
                node->set_body(body);
                if (node->get_return() != nullptr) {
                    node->set_return(process_node_by_type(node->get_return()));
                }

                return node;
            } else if (element->node_type == hl_ast_node_type_conditional) {
                std::shared_ptr<hl_ast_conditional_node> node = std::static_pointer_cast<hl_ast_conditional_node>(
                        element);

                std::vector<std::shared_ptr<hl_ast_node>> new_block_content;
                for (auto &i: node->get_if_block()) {
                    new_block_content.push_back(process_node_by_type(i));
                }
                node->set_if_block(new_block_content);

                new_block_content.clear();

                for (auto &i: node->get_else_block()) {
                    new_block_content.push_back(process_node_by_type(i));
                }
                node->set_else_block(new_block_content);
                node->set_condition(process_node_by_type(node->get_condition()));
                return node;
            } else if (element->node_type == hl_ast_node_type_loop) {
                std::shared_ptr<hl_ast_loop_node> node = std::static_pointer_cast<hl_ast_loop_node>(element);

                std::vector<std::shared_ptr<hl_ast_node>> new_block_content;
                for (auto &i: node->get_loop_content()) {
                    new_block_content.push_back(process_node_by_type(i));
                }
                node->set_loop_content(new_block_content);

                node->set_condition(
                        std::static_pointer_cast<hl_expression_node>(process_node_by_type(node->get_condition())));
                node->set_init_statement(
                        std::static_pointer_cast<hl_definition_node>(process_node_by_type(node->get_init_statement())));
                node->set_iteration_expr(
                        std::static_pointer_cast<hl_expression_node>(process_node_by_type(node->get_iteration_expr())));
                return node;
            } else {
                std::vector<std::shared_ptr<hl_ast_node>> content = element->get_content();
                for (auto &i: content) {
                    i = process_node_by_type(i);
                }
                element->set_content(content);
                return element;
            }

        } else {

            switch (element->node_type) {
                case hl_ast_node_type_expr:
                    return process_expression(std::static_pointer_cast<hl_expression_node>(element));
                case hl_ast_node_type_function_call:
                    return process_function_call(std::static_pointer_cast<hl_function_call_node>(element));
                case hl_ast_node_type_definition:
                    return process_definition(std::static_pointer_cast<hl_definition_node>(element));
                default:
                    return element;
            }

        }

    }


    std::shared_ptr<hl_ast_node>
    intrinsics_implementation_pass::process_definition(const std::shared_ptr<hl_definition_node> &element) {


        std::vector<std::shared_ptr<hl_ast_node>> next_init;

        for(auto &item: element->get_array_initializer()){
            next_init.push_back(process_node_by_type(item));
        }
        element->set_array_initializer(next_init);

        std::vector<std::shared_ptr<hl_ast_node>> next_idx;

        for(auto &item: element->get_array_index()){
            next_idx.push_back(process_node_by_type(item));
        }
        element->set_array_index(next_idx);


        return element;

    }


    std::shared_ptr<hl_ast_node>
    intrinsics_implementation_pass::process_expression(const std::shared_ptr<hl_expression_node> &element) {
        element->set_rhs(process_node_by_type(element->get_rhs()));
        if(!element->is_unary()){
            element->set_lhs(process_node_by_type(element->get_lhs()));
        }
        if(element->is_ternary()){
            element->set_ths(process_node_by_type(element->get_ths()));
        }

        return element;
    }


    std::shared_ptr<hl_ast_node>
    intrinsics_implementation_pass::process_function_call(const std::shared_ptr<hl_function_call_node> &element) {

        for(auto &item:element->get_arguments()){
            item = process_node_by_type(item);
        }

        unsigned int matches = substitutions.count(element->get_name());
        if(matches == 0) {
            return element;
        }

        std::shared_ptr<hl_expression_node> retval = std::make_shared<hl_expression_node>(substitutions[element->get_name()]);

        if(n_arguments[element->get_name()]== 3){
            retval = std::make_shared<hl_expression_node>(expr_assign);
            retval->set_lhs(element->get_arguments()[2]);
            std::shared_ptr<hl_expression_node> rhs = std::make_shared<hl_expression_node>(substitutions[element->get_name()]);
            rhs->set_lhs(element->get_arguments()[0]);
            rhs->set_rhs(element->get_arguments()[1]);
            retval->set_rhs(rhs);
        } else if(n_arguments[element->get_name()]==2){
            retval->set_lhs(element->get_arguments()[0]);
            retval->set_rhs(element->get_arguments()[1]);
        }else if(n_arguments[element->get_name()]==1){
            retval->set_rhs(element->get_arguments()[0]);
        }

        return retval;
    }
}