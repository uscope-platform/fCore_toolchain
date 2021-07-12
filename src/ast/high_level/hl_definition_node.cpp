// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.01/07/2021.
//

#include "ast/high_level/hl_definition_node.hpp"


hl_definition_node::hl_definition_node(std::string n, c_types_t ct) : hl_ast_node(hl_ast_node_type_definition) {
    name = std::move(n);
    type = ct;
    constant = false;
}

bool hl_definition_node::is_initialized() {
    return initializer != nullptr;
}

void hl_definition_node::set_initializer(std::shared_ptr<hl_ast_node> init) {
    initializer = std::move(init);
}

void hl_definition_node::set_constant(bool c) {
    constant = c;
}

bool hl_definition_node::is_constant() {
    return constant;
}

std::shared_ptr<hl_ast_node> hl_definition_node::get_initializer() {
    return initializer;
}

std::string hl_definition_node::pretty_print() {


    std::ostringstream ss;
    if(constant) ss << "const ";
    ss << hl_ast_node::type_to_string(type) << " " << name;

    if(initializer != nullptr){
        ss << " = ";
        if(initializer->node_type == hl_ast_node_type_function_call){
            ss << std::static_pointer_cast<hl_function_call_node>(initializer)->pretty_print();
        } else{
            ss << std::static_pointer_cast<hl_expression_node>(initializer)->pretty_print();
        }

    }


    std::string ret = ss.str();
    return ret;

}

bool operator==(const hl_definition_node &lhs, const hl_definition_node &rhs) {
    bool ret_val = true;

    ret_val &= lhs.constant == rhs.constant;
    ret_val &= lhs.type == rhs.type;
    ret_val &= lhs.name == rhs.name;
    if(lhs.initializer == nullptr && rhs.initializer == nullptr) ret_val &= true;
    else if(lhs.initializer != nullptr && rhs.initializer != nullptr) {
        ret_val &= *std::static_pointer_cast<hl_expression_node>(lhs.initializer) == *std::static_pointer_cast<hl_expression_node>(rhs.initializer);
    } else {
        ret_val &= false;
    }


    return ret_val;
}

void hl_definition_node::set_name(std::string n) {
    name = std::move(n);
}
