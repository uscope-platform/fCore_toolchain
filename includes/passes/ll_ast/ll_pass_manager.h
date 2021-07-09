//
// Created by fils on 06/07/2021.
//

#ifndef FCORE_HAS_LL_PASS_MANAGER_H
#define FCORE_HAS_LL_PASS_MANAGER_H

#include "passes/pass_manager_base.hpp"
#include "code_elements/ll_ast/ll_ast_node.hpp"
#include "passes/pass_base.hpp"

class ll_pass_manager : public pass_manager_base<ll_ast_node> {
public:
    std::shared_ptr<ll_ast_node> run_morphing_pass(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass) override;
    std::vector<std::shared_ptr<ll_ast_node>> process_nodes(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass);
    std::shared_ptr<ll_ast_node> process_leaves(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass);

};


#endif //FCORE_HAS_LL_PASS_MANAGER_H
