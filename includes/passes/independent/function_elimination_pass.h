//
// Created by fils on 09/07/2021.
//

#ifndef FCORE_HAS_FUNCTION_ELIMINATION_PASS_H
#define FCORE_HAS_FUNCTION_ELIMINATION_PASS_H

#include "code_elements/hl_ast/hl_ast_node.h"
#include "code_elements/hl_ast/hl_function_def_node.h"

class function_elimination_pass {
public:
    function_elimination_pass();
    std::shared_ptr<hl_ast_node> run_pass(std::shared_ptr<hl_ast_node> element);
};


#endif //FCORE_HAS_FUNCTION_ELIMINATION_PASS_H
