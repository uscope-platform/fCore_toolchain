//
// Created by fils on 06/07/2021.
//

#ifndef FCORE_HAS_HL_PASS_MANAGER_H
#define FCORE_HAS_HL_PASS_MANAGER_H

#include "code_elements/hl_ast/hl_ast_node.h"
#include "passes/pass_manager_base.hpp"

class ll_pass_manager : public pass_manager_base<hl_ast_node> {
public:
    std::shared_ptr<hl_ast_node> run_pass(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass) override;
    std::shared_ptr<hl_ast_node> process_leaves(const std::shared_ptr<hl_ast_node> &subtree, const std::shared_ptr<pass_base<hl_ast_node>>& pass);

};


#endif //FCORE_HAS_HL_PASS_MANAGER_H
