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

#include "passes/low_level/ll_pass_manager.hpp"


std::vector<std::shared_ptr<ll_ast_node>>
ll_pass_manager::process_nodes(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>> &pass) {
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

std::shared_ptr<ll_ast_node> ll_pass_manager::process_leaves(const std::shared_ptr<ll_ast_node> &subtree,
                                                             const std::shared_ptr<pass_base<ll_ast_node>> &pass) {

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

void ll_pass_manager::run_morphing_pass(std::shared_ptr<ll_ast_node> subtree,
                                                       const std::shared_ptr<pass_base<ll_ast_node>> &pass) {
    switch (pass->get_pass_type()) {
        case NODE_PASS:{
            process_nodes(subtree, pass)[0];
            break;
        }
        case LEAF_PASS:{
            process_leaves(subtree, pass);
            break;
        }
        default:
            break;
    }
}

