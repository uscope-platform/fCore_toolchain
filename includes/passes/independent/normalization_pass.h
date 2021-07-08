//
// Created by fils on 07/07/2021.
//

#ifndef FCORE_HAS_NORMALIZATION_PASS_H
#define FCORE_HAS_NORMALIZATION_PASS_H

#include "code_elements/hl_ast/hl_ast_node.h"
#include "code_elements/hl_ast/hl_function_def_node.h"
#include "code_elements/hl_ast/hl_function_call_node.h"
#include "passes/pass_manager_base.hpp"

class normalization_pass{
public:
    normalization_pass();
    std::shared_ptr<hl_ast_node> run_pass(std::shared_ptr<hl_ast_node> element);
    std::vector<std::shared_ptr<hl_ast_node>> process_node_by_type(std::shared_ptr<hl_ast_node> n);
    std::vector<std::shared_ptr<hl_ast_node>> process_node(std::shared_ptr<hl_expression_node> n);
    std::vector<std::shared_ptr<hl_ast_node>> process_node(std::shared_ptr<hl_definition_node> n);
};


#endif //FCORE_HAS_NORMALIZATION_PASS_H
