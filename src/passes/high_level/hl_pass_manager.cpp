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
// limitations under the License.06/07/2021.
//

#include "passes/high_level/hl_pass_manager.hpp"

#include "passes/pass_base.hpp"

namespace fcore{



    void hl_pass_manager::run_repeating_pass_group(std::shared_ptr<hl_ast_node> &subtree,
                                                                                 const std::vector<std::shared_ptr<pass_base<hl_ast_node>>> &group) {


        int run_number = 1;

        std::shared_ptr<hl_ast_node> old_tree;
        do{
            old_tree = hl_ast_node::deep_copy(subtree);
            for(auto &pass:group){

                if(ic != nullptr) ic->start_event(pass->get_name(), false);
                run_single_pass(subtree, pass);
                if(ic != nullptr) ic->end_event(pass->get_name());

            }
            ++run_number;
        } while (!(*old_tree == *subtree));

    }

    void hl_pass_manager::run_unique_pass_group(std::shared_ptr<hl_ast_node> &subtree,
                                                                              const std::vector<std::shared_ptr<pass_base<hl_ast_node>>> &group) {


        for(auto &pass:group){

            if(ic != nullptr) ic->start_event(pass->get_name(), false);
            run_single_pass(subtree, pass);
            if(ic != nullptr) ic->end_event(pass->get_name());
        }
    }




    void hl_pass_manager::run_single_pass( std::shared_ptr<hl_ast_node> &subtree,
                                                  const std::shared_ptr<pass_base<hl_ast_node>> &pass) {

        switch (pass->get_pass_type()) {
            case LEAF_PASS:{
                process_leaves(subtree, pass);
                break;
            }
            case GLOBAL_PASS:{
                std::shared_ptr<hl_ast_node> tmp =  run_global_pass(subtree, pass);
                *subtree = *tmp;
                break;
            }
            default:
                throw std::runtime_error("The pass  " + pass->get_name() + "  does not have a correct type");
        }
    }


    std::shared_ptr<hl_ast_node> hl_pass_manager::run_global_pass(const std::shared_ptr<hl_ast_node> &subtree,
                                                                                const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
        return pass->process_global(subtree);
    }


    std::shared_ptr<hl_ast_node> hl_pass_manager::process_leaves(const std::shared_ptr<hl_ast_node> &subtree,
                                                                               const std::shared_ptr<pass_base<hl_ast_node>> &pass) {

        std::shared_ptr<hl_ast_node> result;
        if(!subtree->is_terminal()){
            if(subtree->node_type == hl_ast_node_type_function_def){
                std::shared_ptr<hl_function_def_node> node = std::static_pointer_cast<hl_function_def_node>(subtree);

                std::vector<std::shared_ptr<hl_ast_node>> body =  node->get_body();
                for(auto &i :body){
                    i = process_leaves(i, pass);
                }
                node->set_body(body);
                if(node->get_return() != nullptr){
                    node->set_return(process_leaves(node->get_return(), pass));
                }

                result = node;
            }else if (subtree->node_type == hl_ast_node_type_conditional){
                std::shared_ptr<hl_ast_conditional_node> node = std::static_pointer_cast<hl_ast_conditional_node>(subtree);

                std::vector<std::shared_ptr<hl_ast_node>> new_block_content;
                for(auto &item:node->get_if_block()){
                    new_block_content.push_back(process_leaves(item, pass));
                }
                node->set_if_block(new_block_content);

                new_block_content.clear();

                for(auto &item:node->get_else_block()){
                    new_block_content.push_back(process_leaves(item, pass));
                }
                node->set_else_block(new_block_content);
                node->set_condition(process_leaves(node->get_condition(), pass));
                result = node;
            }else if (subtree->node_type == hl_ast_node_type_loop){
                std::shared_ptr<hl_ast_loop_node> node = std::static_pointer_cast<hl_ast_loop_node>(subtree);

                std::vector<std::shared_ptr<hl_ast_node>> new_block_content;
                for(auto &item:node->get_loop_content()){
                    new_block_content.push_back(process_leaves(item, pass));
                }
                node->set_loop_content(new_block_content);

                node->set_condition(std::static_pointer_cast<hl_expression_node>(process_leaves(node->get_condition(), pass)));
                node->set_init_statement(std::static_pointer_cast<hl_definition_node>(process_leaves(node->get_init_statement(), pass)));
                node->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(process_leaves(node->get_iteration_expr(), pass)));
                result = node;
            } else{
                std::vector<std::shared_ptr<hl_ast_node>> content =  subtree->get_content();
                for(auto &i :content){
                    i = process_leaves(i, pass);
                }
                subtree->set_content(content);
                result = subtree;
            }

        } else{
            result = process_terminal_by_type(subtree, pass);
        }
        return result;
    }

    std::shared_ptr<hl_ast_node>
    hl_pass_manager::process_expression(const std::shared_ptr<hl_expression_node> &subtree,
                                               const std::shared_ptr<pass_base<hl_ast_node>> &pass) {

        std::shared_ptr<hl_expression_node> result = std::static_pointer_cast<hl_expression_node>(hl_ast_node::deep_copy(subtree));


        if(!subtree->is_immediate()){
            std::shared_ptr<hl_ast_node> rhs = process_terminal_by_type(subtree->get_rhs(), pass);
            result->set_rhs(rhs);
            if(!subtree->is_unary()){
                std::shared_ptr<hl_ast_node> lhs = process_terminal_by_type(subtree->get_lhs(), pass);
                result->set_lhs(lhs);
            }
        }

        return pass->process_leaf(result);

    }

    std::shared_ptr<hl_ast_operand> hl_pass_manager::process_operand(const std::shared_ptr<hl_ast_operand> &subtree,
                                                                                   const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
        return std::static_pointer_cast<hl_ast_operand>(pass->process_leaf(subtree));
    }

    std::shared_ptr<hl_ast_node>
    hl_pass_manager::process_function_call(const std::shared_ptr<hl_function_call_node> &subtree,
                                                  const std::shared_ptr<pass_base<hl_ast_node>> &pass) {

        return pass->process_leaf(subtree);
    }

    std::shared_ptr<hl_definition_node>
    hl_pass_manager::process_definition(const std::shared_ptr<hl_definition_node> &subtree,
                                               const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
        if(subtree->is_initialized()){
            if(subtree->is_scalar()){
                std::shared_ptr<hl_ast_node> new_initializer = process_terminal_by_type(subtree->get_scalar_initializer(), pass);
                subtree->set_scalar_initializer(new_initializer);
            } else{
                std::vector<std::shared_ptr<hl_ast_node>> new_initializer;
                for(auto &item: subtree->get_array_initializer()){
                    new_initializer.push_back(process_terminal_by_type(item, pass));
                }
                subtree->set_array_initializer(new_initializer);
            }
        }
        return std::static_pointer_cast<hl_definition_node>(pass->process_leaf(subtree));
    }

    std::shared_ptr<hl_ast_loop_node> hl_pass_manager::process_loop(const std::shared_ptr<hl_ast_loop_node> &subtree,
                                                                                  const std::shared_ptr<pass_base<hl_ast_node>> &pass) {

        subtree->set_condition(std::static_pointer_cast<hl_expression_node>(process_terminal_by_type(subtree->get_condition(), pass)));
        subtree->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(process_terminal_by_type(subtree->get_iteration_expr(), pass)));
        subtree->set_init_statement(std::static_pointer_cast<hl_definition_node>(process_terminal_by_type(subtree->get_init_statement(), pass)));

        std::vector<std::shared_ptr<hl_ast_node>> new_block_content;
        for(auto &item:subtree->get_loop_content()){
            new_block_content.push_back(process_terminal_by_type(item, pass));
        }
        subtree->set_loop_content(new_block_content);
        return subtree;
    }

    std::shared_ptr<hl_ast_conditional_node>
    hl_pass_manager::process_conditional(const std::shared_ptr<hl_ast_conditional_node> &subtree,
                                                const std::shared_ptr<pass_base<hl_ast_node>> &pass) {

        subtree->set_condition(pass->process_leaf(subtree->get_condition()));
        std::vector<std::shared_ptr<hl_ast_node>> new_block_content;
        for(auto &item:subtree->get_if_block()){
            new_block_content.push_back(process_terminal_by_type(item, pass));
        }
        subtree->set_if_block(new_block_content);

        new_block_content.clear();
        for(auto &item:subtree->get_else_block()){
            new_block_content.push_back(process_terminal_by_type(item, pass));
        }
        subtree->set_else_block(new_block_content);

        return subtree;
    }



    std::shared_ptr<hl_ast_node>
    hl_pass_manager::process_terminal_by_type(const std::shared_ptr<hl_ast_node> &subtree,
                                                     const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
        std::shared_ptr<hl_ast_node> res;
        switch (subtree->node_type) {
            case hl_ast_node_type_expr:
                res = process_expression(std::static_pointer_cast<hl_expression_node>(subtree), pass);
                break;
            case hl_ast_node_type_function_call:
                res = process_function_call(std::static_pointer_cast<hl_function_call_node>(subtree), pass);
                break;
            case hl_ast_node_type_operand:
                res = process_operand(std::static_pointer_cast<hl_ast_operand>(subtree), pass);
                break;
            case hl_ast_node_type_definition:
                res = process_definition(std::static_pointer_cast<hl_definition_node>(subtree),pass);
                break;
            case hl_ast_node_type_conditional:
                res = process_conditional(std::static_pointer_cast<hl_ast_conditional_node>(subtree), pass);
                break;
            default:
                break;
        };
        return res;
    }

    void hl_pass_manager::add_morphing_pass(const std::string& name, const std::shared_ptr<pass_base<hl_ast_node>>& pass){
        opt_pass p;
        p.pass = {pass};
        p.type = single_pass;
        p.name = name;
        p.enabled = true;
        passes.push_back(p);
    }

    void hl_pass_manager::add_morphing_pass_group(const std::string& name, const std::vector<std::shared_ptr<pass_base<hl_ast_node>>>& group){
        opt_pass p;
        p.pass = group;
        p.type = repeating_pass_group;
        p.name = name;
        p.enabled = true;
        passes.push_back(p);
    }

    void hl_pass_manager::run_morphing_passes(std::shared_ptr<hl_ast_node> AST) {
        for(auto& p:passes){
            if(p.type == single_pass){
                if(p.enabled){
                    std::shared_ptr<pass_base<hl_ast_node>> pass = p.pass[0];

                    if (ic != nullptr) ic->start_event(pass->get_name(), false);
                    run_single_pass(AST, pass);
                    if (ic != nullptr) ic->end_event(pass->get_name());
                }
            } else if(p.type == repeating_pass_group) {
                if (p.enabled) {
                    run_repeating_pass_group(AST, p.pass);
                }
            } else if(p.type == unique_pass_group) {
                if(p.enabled){
                    run_unique_pass_group(AST, p.pass);
                }
            } else {
                throw std::runtime_error("ERROR: unexpected pass type");
            }


        }
    }

    void hl_pass_manager::enable_pass(const std::string &name) {
        for(auto& p:passes) {
            if(p.name == name) {
                p.enabled = true;
                return;
            }
        }
        throw std::runtime_error("Required pass not found");
    }

    void hl_pass_manager::disable_all() {
        for(auto& p:passes) {
            p.enabled = false;
        }
    }

}