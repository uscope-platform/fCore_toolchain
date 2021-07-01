//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_function_node.h"

#include <utility>

hl_function_node::hl_function_node(hl_ast_node_type_t t, c_types_t ret_val, std::string &n) : hl_ast_node(t) {
    return_type = ret_val;
    name = n;
}

void hl_function_node::set_parameters_list(std::vector<std::shared_ptr<hl_identifier_node>> list) {
    parameters_list = std::move(list);
}
