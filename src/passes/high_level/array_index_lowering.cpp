//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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


#include "passes/high_level/array_index_lowering.hpp"

namespace fcore{

    array_index_lowering::array_index_lowering() : pass_base("array index lowering"){

    }


    std::shared_ptr<hl_ast_root> array_index_lowering::process_global(std::shared_ptr<hl_ast_root> element) {
        std::shared_ptr<hl_ast_root> ret_val = std::make_shared<hl_ast_root>();
        std::vector<std::shared_ptr<hl_ast_node>> new_content;
        for(auto &item:element->get_content()){
            new_content.push_back(process_node_by_type(item));
        }
        ret_val->set_content(new_content);
        return ret_val;
    }

    std::shared_ptr<hl_ast_node> array_index_lowering::process_node_by_type(std::shared_ptr<hl_ast_node> item) {
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

    std::shared_ptr<hl_ast_node> array_index_lowering::process_terminal(std::shared_ptr<hl_ast_node> element) {
        if(element->node_type == hl_ast_node_type_definition){
            return process_definition(std::static_pointer_cast<hl_definition_node>(element));
        }else if(element->node_type == hl_ast_node_type_expr){
            return process_expression(std::static_pointer_cast<hl_expression_node>(element));
        } else if(element->node_type == hl_ast_node_type_function_call){
            return process_f_call(std::static_pointer_cast<hl_function_call_node>(element));
        } else if(element->node_type== hl_ast_node_type_operand){
            return process_operand(std::static_pointer_cast<hl_ast_operand>(element));
        }else{
            return element;
        }
    }

    std::shared_ptr<hl_ast_node> array_index_lowering::process_expression(std::shared_ptr<hl_expression_node> element) {
        element->set_rhs(process_node_by_type(element->get_rhs()));
        if(!element->is_unary()){
            element->set_lhs(process_node_by_type(element->get_lhs()));
        }
        if(element->is_ternary()){
            element->set_ths(process_node_by_type(element->get_ths()));
        }

        return element;
    }

    std::shared_ptr<hl_ast_node> array_index_lowering::process_definition(std::shared_ptr<hl_definition_node> exp) {

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

    std::shared_ptr<hl_ast_node> array_index_lowering::process_f_call(std::shared_ptr<hl_function_call_node> f_call) {
        auto args = f_call->get_arguments();
        for(auto &i: args) {
            if(i->node_type == hl_ast_node_type_expr){
                i = process_expression(std::static_pointer_cast<hl_expression_node>(i));
            }
        }
        f_call->set_arguments(args);
        return f_call;
    }

    std::shared_ptr<hl_ast_node> array_index_lowering::process_operand(const std::shared_ptr<hl_ast_operand> &op) {
        if(op->get_type()==var_type_array){
            std::vector<int> array_idx;
            for(auto&item:op->get_array_index()){
                auto idx_op = std::static_pointer_cast<hl_ast_operand>(item);
                array_idx.push_back(idx_op->get_int_value());
            }
            op->get_variable()->set_array_index(array_idx);
            op->set_array_index({});
        }
        return op;
    }
}
