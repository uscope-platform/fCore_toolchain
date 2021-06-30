//
// Created by fils on 30/06/2021.
//

#include "code_elements/hl_ast/hl_ast_node.h"

bool hl_ast_node::is_terminal() {
    return false;
}

hl_ast_node::hl_ast_node(int t) {
    type = t;
}
