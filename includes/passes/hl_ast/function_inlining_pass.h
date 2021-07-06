//
// Created by fils on 05/07/2021.
//

#ifndef FCORE_HAS_FUNCTION_INLINING_PASS_H
#define FCORE_HAS_FUNCTION_INLINING_PASS_H

#include "passes/pass_manager_base.hpp"
#include "code_elements/hl_ast/hl_ast_node.h"

class function_inlining_pass :public pass_base<hl_ast_node>{

};


#endif //FCORE_HAS_FUNCTION_INLINING_PASS_H
