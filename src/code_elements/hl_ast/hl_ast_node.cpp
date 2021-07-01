//
// Created by fils on 30/06/2021.
//

#include "code_elements/hl_ast/hl_ast_node.h"


bool hl_ast_node::is_terminal() {
    return false;
}

hl_ast_node::hl_ast_node(hl_ast_node_type_t t) {
    node_type = t;
}

c_types_t hl_ast_node::string_to_type(const std::string &t) {
    std::map <std::string, c_types_t>  translator {
            {"void", c_type_void},
            {"char", c_type_char},
            {"short", c_type_short},
            {"int", c_type_int},
            {"long", c_type_long},
            {"float", c_type_float}
    };


    return translator[t];
}

bool operator==(const hl_ast_node &lhs, const hl_ast_node &rhs) {
    bool ret_val = true;
    ret_val &= lhs.node_type == rhs.node_type;
    ret_val &= lhs.content == rhs.content;
    return ret_val;
}
