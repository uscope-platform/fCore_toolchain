// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.01/07/2021.
//

#include "data_structures/high_level_ast/hl_definition_node.hpp"


hl_definition_node::hl_definition_node(std::string n, c_types_t ct, std::shared_ptr<variable> v) : hl_ast_node(hl_ast_node_type_definition) {
    name = std::move(n);
    type = ct;
    constant = false;
    inner_variable = std::move(v);
}

bool hl_definition_node::is_initialized() {
    return !initializer.empty();
}

void hl_definition_node::set_scalar_initializer(const std::shared_ptr<hl_ast_node>& init) {
    initializer.clear();
    initializer.push_back(init);

}

void hl_definition_node::set_constant(bool c) {
    constant = c;
}

bool hl_definition_node::is_constant() {
    return constant;
}

std::shared_ptr<hl_ast_node> hl_definition_node::get_scalar_initializer() {
    return initializer[0];
}

std::string hl_definition_node::pretty_print() {


    std::ostringstream ss;
    if(constant) ss << "const ";
    ss << hl_ast_node::type_to_string(type) << " " << name;

    if(!initializer.empty()){
        ss << " = ";
        if(initializer[0]->node_type == hl_ast_node_type_function_call){
            ss << std::static_pointer_cast<hl_function_call_node>(initializer[0])->pretty_print();
        } else{
            ss << std::static_pointer_cast<hl_expression_node>(initializer[0])->pretty_print();
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

    ret_val &= lhs.array_shape == rhs.array_shape;

    ret_val &= hl_ast_node::compare_vectors(lhs.array_index, rhs.array_index);
    ret_val &= hl_ast_node::compare_vectors(lhs.initializer, rhs.initializer);

    if(lhs.inner_variable == nullptr && rhs.inner_variable == nullptr) ret_val &= true;
    else if (lhs.inner_variable == nullptr || rhs.inner_variable == nullptr) ret_val &= false;
    else ret_val &= *lhs.inner_variable == *rhs.inner_variable;

    return ret_val;
}

void hl_definition_node::set_name(std::string n) {
    name = std::move(n);
}

bool hl_definition_node::is_scalar() {
    return inner_variable->get_type() != var_type_array;
}

unsigned int hl_definition_node::get_array_size() {
    unsigned  int retval = array_shape[0];
    for(int i = 1; i<array_shape.size(); i++) {
        retval *= array_shape[i];
    }
    return retval;
}