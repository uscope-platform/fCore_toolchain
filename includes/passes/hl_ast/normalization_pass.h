//
// Created by fils on 07/07/2021.
//

#ifndef FCORE_HAS_NORMALIZATION_PASS_H
#define FCORE_HAS_NORMALIZATION_PASS_H

#include "code_elements/hl_ast/hl_ast_node.h"
#include "passes/pass_manager_base.hpp"

class normalization_pass : public pass_base<hl_ast_node>{
public:
    normalization_pass();
    std::vector<std::shared_ptr<hl_ast_node>>process_node(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return NODE_PASS;};
};


#endif //FCORE_HAS_NORMALIZATION_PASS_H
