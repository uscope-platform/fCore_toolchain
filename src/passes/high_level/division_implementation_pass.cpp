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
//

#include "passes/high_level/division_implementation_pass.hpp"

namespace fcore{

    division_implementation_pass::division_implementation_pass() : pass_base("division implementation pass"){

    }

    std::shared_ptr<hl_code_block> division_implementation_pass::process_global(std::shared_ptr<hl_code_block> element) {
        auto ret_val = std::make_shared<hl_code_block>();
        std::vector<std::shared_ptr<hl_ast_node>> new_content;
        for(auto &item:element->get_content()){
            new_content.push_back(process_node_by_type(item));
        }
        ret_val->set_content(new_content);
        return ret_val;
    }

    std::shared_ptr<hl_ast_node> division_implementation_pass::process_expression(std::shared_ptr<hl_expression_node> exp) {
        if(exp->get_type() == expr_div){
            std::shared_ptr<hl_ast_node> lhs = exp->get_lhs().value();
            std::shared_ptr<hl_expression_node> modulo_expr = std::make_shared<hl_expression_node>(expr_reciprocal);
            modulo_expr->set_rhs(exp->get_rhs());
            std::shared_ptr<hl_expression_node> mult_expr = std::make_shared<hl_expression_node>(expr_mult);
            mult_expr->set_lhs(exp->get_lhs().value());
            mult_expr->set_rhs(modulo_expr);
            return mult_expr;
        } else {
            return exp;
        }
    }

    std::shared_ptr<hl_ast_node> division_implementation_pass::process_f_call(std::shared_ptr<hl_function_call_node> f_call) {
        auto args = f_call->get_arguments();
        for(auto &i: args) {
            if(i->node_type == hl_ast_node_type_expr){
                i = process_expression(std::static_pointer_cast<hl_expression_node>(i));
            }
        }
        f_call->set_arguments(args);
        return f_call;
    }

    std::shared_ptr<hl_ast_node>
    division_implementation_pass::process_node_by_type(std::shared_ptr<hl_ast_node> item) {
        if(!item->is_terminal()){
            if(item->node_type == hl_ast_node_type_function_def){
                std::shared_ptr<hl_function_def_node> node = std::static_pointer_cast<hl_function_def_node>(item);

                std::vector<std::shared_ptr<hl_ast_node>> body =  node->get_body();
                for(auto &i :body){
                    i = process_node_by_type(i);
                }
                node->set_body(body);
                if(node->get_return() != nullptr){
                    node->set_return(process_node_by_type(node->get_return()));
                }

                return node;
            }else if (item->node_type == hl_ast_node_type_conditional){
                std::shared_ptr<hl_ast_conditional_node> node = std::static_pointer_cast<hl_ast_conditional_node>(item);

                std::vector<std::shared_ptr<hl_ast_node>> new_block_content;
                for(auto &i:node->get_if_block()){
                    new_block_content.push_back(process_node_by_type(i));
                }
                node->set_if_block(new_block_content);

                new_block_content.clear();

                for(auto &i:node->get_else_block()){
                    new_block_content.push_back(process_node_by_type(i));
                }
                node->set_else_block(new_block_content);
                node->set_condition(process_node_by_type(node->get_condition()));
                return node;
            }else if (item->node_type == hl_ast_node_type_loop){
                std::shared_ptr<hl_ast_loop_node> node = std::static_pointer_cast<hl_ast_loop_node>(item);

                std::vector<std::shared_ptr<hl_ast_node>> new_block_content;
                for(auto &i:node->get_loop_content()){
                    new_block_content.push_back(process_node_by_type(i));
                }
                node->set_loop_content(new_block_content);

                node->set_condition(std::static_pointer_cast<hl_expression_node>(process_node_by_type(node->get_condition())));
                node->set_init_statement(std::static_pointer_cast<hl_definition_node>(process_node_by_type(node->get_init_statement())));
                node->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(process_node_by_type(node->get_iteration_expr())));
                return node;
            } else {

                return item;
            }
        } else{
            return process_terminal(item);
        }
    }

    std::shared_ptr<hl_ast_node> division_implementation_pass::process_terminal(std::shared_ptr<hl_ast_node> element) {
        std::shared_ptr<hl_ast_node> ret_val = element;
        if(element->node_type == hl_ast_node_type_definition){
            ret_val = process_definition(std::static_pointer_cast<hl_definition_node>(element));
        }else if(element->node_type == hl_ast_node_type_expr){
            ret_val = process_expression(std::static_pointer_cast<hl_expression_node>(element));
        } else if(element->node_type == hl_ast_node_type_function_call){
            ret_val = process_f_call(std::static_pointer_cast<hl_function_call_node>(element));
        }
        return ret_val;
    }

    std::shared_ptr<hl_ast_node>
    division_implementation_pass::process_definition(std::shared_ptr<hl_definition_node> exp) {

        std::vector<std::shared_ptr<hl_ast_node>> new_init;

        for(auto &item: exp->get_array_initializer()){
            new_init.push_back(process_node_by_type(item));
        }
        exp->set_array_initializer(new_init);

        std::vector<std::shared_ptr<hl_ast_node>> new_index;
        for(auto &item:exp->get_array_index()){
            new_index.push_back(process_node_by_type(item));
        }
        exp->set_array_index(new_index);

        return exp;
    }

}
