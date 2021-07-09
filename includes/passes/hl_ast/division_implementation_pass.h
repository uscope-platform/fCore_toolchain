//
// Created by fils on 05/07/2021.
//

#ifndef FCORE_HAS_DIVISION_IMPLEMENTATION_PASS_H
#define FCORE_HAS_DIVISION_IMPLEMENTATION_PASS_H

#include "code_elements/hl_ast/hl_expression_node.h"
#include "code_elements/hl_ast/hl_ast_node.h"
#include "passes/pass_base.hpp"

class division_implementation_pass :public pass_base<hl_ast_node> {
public:
    division_implementation_pass();
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return LEAF_PASS;};
};




#endif //FCORE_HAS_DIVISION_IMPLEMENTATION_PASS_H
