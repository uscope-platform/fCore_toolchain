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
// limitations under the License.08/07/2021.
//

#include "passes/high_level/operating_assignment_implementation_pass.hpp"

namespace fcore{

    operating_assignment_implementation_pass::operating_assignment_implementation_pass() : pass_base<hl_ast_node>("operating assignments implementation pass"){

    }

    std::shared_ptr<hl_ast_node>
    operating_assignment_implementation_pass::process_global(std::shared_ptr<hl_ast_node> element) {


        std::shared_ptr<hl_ast_root> ret_val = std::make_shared<hl_ast_root>();
        std::vector<std::shared_ptr<hl_ast_node>> new_content;
        for(auto &item:element->get_content()){
            new_content.push_back(process_node_by_type(item));
        }
        ret_val->set_content(new_content);
        return ret_val;
    }





    std::shared_ptr<hl_expression_node>
    operating_assignment_implementation_pass::create_top_expression(assignment_type_t a) {
        std::shared_ptr<hl_expression_node> retval;
        switch (a) {
            case addition_assignment:
                retval = std::make_shared<hl_expression_node>(expr_add);
                break;
            case subtraction_assignment:
                retval = std::make_shared<hl_expression_node>(expr_sub);
                break;
            case multiplication_assignment:
                retval = std::make_shared<hl_expression_node>(expr_mult);
                break;
            case division_assignment:
                retval = std::make_shared<hl_expression_node>(expr_div);
                break;
            case modulo_assignment:
                retval = std::make_shared<hl_expression_node>(expr_modulo);
                break;
            case and_assignment:
                retval = std::make_shared<hl_expression_node>(expr_and_b);
                break;
            case or_assignment:
                retval = std::make_shared<hl_expression_node>(expr_or_b);
                break;
            case xor_assignment:
                retval = std::make_shared<hl_expression_node>(expr_xor_b);
                break;
            case lsh_assignment:
                retval = std::make_shared<hl_expression_node>(expr_lsh);
                break;
            case rsh_assignment:
                retval = std::make_shared<hl_expression_node>(expr_rsh);
                break;
        }
        return retval;
    }

    std::shared_ptr<hl_ast_node>
    operating_assignment_implementation_pass::process_terminal(std::shared_ptr<hl_ast_node> element) {

        std::shared_ptr<hl_ast_node> ret_val = element;
        if(element->node_type == hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
            if(node->get_type() == expr_assign && node->get_assignment_type() != regular_assignment ){
                std::shared_ptr<hl_expression_node> outer_exp = std::make_shared<hl_expression_node>(expr_assign);
                outer_exp->set_lhs(node->get_lhs());
                std::shared_ptr<hl_expression_node> inner_exp = create_top_expression(node->get_assignment_type());
                inner_exp->set_lhs(node->get_lhs());
                inner_exp->set_rhs(node->get_rhs());
                outer_exp->set_rhs(inner_exp);
                ret_val = outer_exp;
            }
        }
        return ret_val;
    }

    std::shared_ptr<hl_ast_node>
    operating_assignment_implementation_pass::process_node_by_type(std::shared_ptr<hl_ast_node> item) {
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
            } else{
                std::vector<std::shared_ptr<hl_ast_node>> content =  item->get_content();
                for(auto &i :content){
                    i = process_node_by_type(i);
                }
                item->set_content(content);
                return item;
            }

        } else{
            return process_terminal(item);
        }
    }
}

