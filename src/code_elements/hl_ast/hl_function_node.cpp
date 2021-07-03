//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_function_node.h"

#include <utility>

hl_function_node::hl_function_node() : hl_ast_node(hl_ast_node_type_function) {
    return_type = c_type_void;
}

void hl_function_node::set_parameters_list(std::vector<std::shared_ptr<hl_identifier_node>> list) {
    parameters_list = std::move(list);
}

void hl_function_node::set_body(std::vector<std::shared_ptr<hl_ast_node>> b) {
    function_body = std::move(b);
}

void hl_function_node::set_return(std::shared_ptr<hl_expression_node> r) {
    return_expression = std::move(r);
}

void hl_function_node::set_name(std::string &n) {
    name = n;
}

void hl_function_node::set_type(c_types_t ret_val) {
    return_type = ret_val;

}
