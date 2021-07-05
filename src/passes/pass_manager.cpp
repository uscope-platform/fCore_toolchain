// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#include "passes/pass_manager.hpp"

#include <utility>

void pass_manager::add_pass(const std::shared_ptr<pass_base>& pass) {
    passes.push_back(pass);
}

std::shared_ptr<ll_ast_node> pass_manager::run_morphing_passes(std::shared_ptr<ll_ast_node> AST) {
    std::shared_ptr<ll_ast_node> working_tree = std::move(AST);
    for( auto& pass:passes){
        int pass_type = pass->get_pass_type();
        switch (pass_type) {
            case NODE_PASS:{
                std::vector<std::shared_ptr<ll_ast_node>> tmp = process_nodes(working_tree, pass);
                working_tree = tmp[0];
                break;
            }
            case LEAF_PASS:{
                working_tree = process_leaves(working_tree, pass);
                break;
            }
            default:
                break;
        }
    }
    return working_tree;
}

std::vector<std::vector<int>> pass_manager::run_analysis_passes(const std::shared_ptr<ll_ast_node>& AST) {
    std::vector<std::vector<int>> results;
    for( auto& pass:passes){
        if(pass->get_pass_type() == ANALYSIS_PASS){
            analyze_tree(AST, pass);
            results.push_back(pass->get_analysis_result());
        }
    }
    return results;
}

std::vector<std::shared_ptr<ll_ast_node>>
pass_manager::process_nodes(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base>& pass) {
    std::shared_ptr<ll_ast_node> result;
    std::vector<std::shared_ptr<ll_ast_node>> content = subtree->get_content();
    std::vector<std::shared_ptr<ll_ast_node>> result_vector = content;
    for (int i = 0; i< content.size(); i++) {
        if(content[i]->is_terminal()) continue;
        std::vector<std::shared_ptr<ll_ast_node>> tmp_result;
        tmp_result = process_nodes(content[i], pass);
        result_vector.insert(result_vector.begin()+i, tmp_result.begin(), tmp_result.end());

        result_vector.erase(result_vector.begin()+i+tmp_result.size());
    }
    subtree->set_content(result_vector);
    return pass->process_node(subtree);
}

std::shared_ptr<ll_ast_node> pass_manager::process_leaves(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base> &pass) {

    std::shared_ptr<ll_ast_node> result;
    std::vector<std::shared_ptr<ll_ast_node>> content = subtree->get_content();
    std::vector<std::shared_ptr<ll_ast_node>> result_vector = content;
    for (auto & i : content) {
        if(i->is_terminal()) {
            i = pass->process_leaf(i);
        } else{
            process_leaves(i, pass);
        }

    }
    subtree->set_content(content);
    return subtree;
}

void
pass_manager::analyze_tree(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base> &pass) {
    for(auto &i : subtree->get_content()){
        analyze_tree(i,pass);
    }
    pass->analyze_element(subtree);
}

