//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_identifier_node.h"

#include <utility>

hl_identifier_node::hl_identifier_node(hl_ast_node_type_t nt, std::string n, c_types_t ct) : hl_ast_node(nt) {
    name = std::move(n);
    type = ct;
}
