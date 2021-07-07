//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_definition_node.h"

#include <utility>

hl_definition_node::hl_definition_node(std::string n, c_types_t ct) : hl_ast_node(hl_ast_node_type_definition) {
    name = std::move(n);
    type = ct;
    constant = false;
}

bool hl_definition_node::is_initialized() {
    return initializer== nullptr;
}

void hl_definition_node::set_initializer(std::shared_ptr<hl_expression_node> init) {
    initializer = std::move(init);
}

void hl_definition_node::set_constant(bool c) {
    constant = c;
}

bool hl_definition_node::is_constant() {
    return constant;
}

std::shared_ptr<hl_expression_node> hl_definition_node::get_initializer() {
    return initializer;
}

std::string hl_definition_node::pretty_print() {


    std::ostringstream ss;
    if(constant) ss << "const ";
    ss << hl_ast_node::type_to_string(type) << " " << name;

    if(initializer != nullptr){
        ss << " = " << initializer->pretty_print();
    }


    std::string ret = ss.str();
    return ret;

}

bool operator==(const hl_definition_node &lhs, const hl_definition_node &rhs) {
    bool ret_val = true;

    ret_val &= lhs.constant == rhs.constant;
    ret_val &= lhs.type == rhs.type;
    ret_val &= lhs.name == rhs.name;
    ret_val &= *std::static_pointer_cast<hl_expression_node>(lhs.initializer) == *std::static_pointer_cast<hl_expression_node>(rhs.initializer);

    return ret_val;
}

void hl_definition_node::set_name(std::string n) {
name = std::move(n);
}
