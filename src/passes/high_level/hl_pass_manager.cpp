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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.06/07/2021.
//

#include "passes/high_level/hl_pass_manager.hpp"
#include "passes/pass_base.hpp"

void hl_pass_manager::run_morphing_pass( std::shared_ptr<hl_ast_node> &subtree,
                                                       const std::shared_ptr<pass_base<hl_ast_node>> &pass) {

    switch (pass->get_pass_type()) {
        case NODE_PASS:{
            process_nodes(subtree, pass);
            break;
        }
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
            break;
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

std::vector<std::shared_ptr<hl_ast_node>> hl_pass_manager::process_nodes(const std::shared_ptr<hl_ast_node> &subtree,
                                                                         const std::shared_ptr<pass_base<hl_ast_node>> &pass) {

    std::shared_ptr<hl_ast_node> result;
    std::vector<std::shared_ptr<hl_ast_node>> content = subtree->get_content();
    std::vector<std::shared_ptr<hl_ast_node>> result_vector = content;
    for (int i = 0; i< content.size(); i++) {
        if(content[i]->is_terminal()) continue;
        std::vector<std::shared_ptr<hl_ast_node>> tmp_result;
        tmp_result = process_nodes(content[i], pass);
        result_vector.insert(result_vector.begin()+i, tmp_result.begin(), tmp_result.end());

        result_vector.erase(result_vector.begin()+i+tmp_result.size());
    }
    subtree->set_content(result_vector);
    return pass->process_node(subtree);


}

std::shared_ptr<hl_expression_node>
hl_pass_manager::process_expression(const std::shared_ptr<hl_expression_node> &subtree,
                                    const std::shared_ptr<pass_base<hl_ast_node>> &pass) {

    std::shared_ptr<hl_expression_node> result = std::make_shared<hl_expression_node>(subtree->get_type());

    std::shared_ptr<hl_ast_node> rhs = process_terminal_by_type(subtree->get_rhs(), pass);
    result->set_rhs(rhs);

    if(!subtree->is_unary()){
        std::shared_ptr<hl_ast_node> lhs = process_terminal_by_type(subtree->get_lhs(), pass);
        result->set_lhs(lhs);
    }

    return std::static_pointer_cast<hl_expression_node>(pass->process_leaf(result));

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
        std::shared_ptr<hl_ast_node> new_initializer = process_terminal_by_type(subtree->get_initializer(), pass);
        subtree->set_initializer(new_initializer);
    }
    return std::static_pointer_cast<hl_definition_node>(pass->process_leaf(subtree));
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
        default:
            break;
    };
    return res;
}

