//
// Created by fils on 09/07/2021.
//

#ifndef FCORE_HAS_FUNCTION_ELIMINATION_PASS_H
#define FCORE_HAS_FUNCTION_ELIMINATION_PASS_H

#include "ast/high_level/hl_ast_node.h"
#include "ast/high_level/hl_function_def_node.h"
#include "passes/pass_base.hpp"


class function_elimination_pass : public pass_base<hl_ast_node> {
public:
    function_elimination_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};
};


#endif //FCORE_HAS_FUNCTION_ELIMINATION_PASS_H
