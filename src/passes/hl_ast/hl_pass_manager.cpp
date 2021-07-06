//
// Created by fils on 06/07/2021.
//

#include "passes/hl_ast/hl_pass_manager.h"

std::shared_ptr<hl_ast_node> ll_pass_manager::run_pass(const std::shared_ptr<hl_ast_node> &subtree,
                                                       const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    return pass_manager_base::run_pass(subtree, pass);
}

std::shared_ptr<hl_ast_node> ll_pass_manager::process_leaves(const std::shared_ptr<hl_ast_node> &subtree,
                                                             const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    return std::shared_ptr<hl_ast_node>();
}
