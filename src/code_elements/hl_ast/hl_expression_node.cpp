//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_expression_node.h"

hl_expression_node::hl_expression_node(hl_ast_node_type_t nt, expression_type_t et) : hl_ast_node(nt) {
    expr_type = et;
}

void hl_expression_node::set_lhs(const std::shared_ptr<hl_ast_node> &node) {
    lhs = node;
}

void hl_expression_node::set_rhs(const std::shared_ptr<hl_ast_node> &node) {
    rhs = node;
}
