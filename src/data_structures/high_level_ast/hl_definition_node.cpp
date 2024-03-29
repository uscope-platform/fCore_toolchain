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


fcore::hl_definition_node::hl_definition_node(std::string n, c_types_t ct, std::shared_ptr<variable> v) : hl_ast_node(hl_ast_node_type_definition) {
    name = std::move(n);
    type = ct;
    constant = false;
    inner_variable = std::move(v);
}

bool fcore::hl_definition_node::is_initialized() {
    return !initializer.empty();
}

void fcore::hl_definition_node::set_scalar_initializer(const std::shared_ptr<hl_ast_node>& init) {
    initializer.clear();
    initializer.push_back(init);

}

void fcore::hl_definition_node::set_constant(bool c) {
    constant = c;
}

bool fcore::hl_definition_node::is_constant() const {
    return constant;
}

std::shared_ptr<fcore::hl_ast_node> fcore::hl_definition_node::get_scalar_initializer() {
    return initializer[0];
}

void fcore::hl_definition_node::set_scalar_initializer(const std::shared_ptr<hl_ast_node> &init, uint32_t idx) {
    if(initializer.size()<idx) throw std::runtime_error("Error: Attempt to set undefined initializer");
    initializer[idx] = init;
}

std::string fcore::hl_definition_node::pretty_print() {


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

void fcore::hl_definition_node::set_name(std::string n) {
    name = std::move(n);
}

bool fcore::hl_definition_node::is_scalar() {
    return inner_variable->get_type() != var_type_array;
}


nlohmann::json fcore::hl_definition_node::dump() {
    nlohmann::json retval = hl_ast_node::dump();

    retval["array_index"] = hl_ast_node::dump_array(array_index);
    retval["initializer"] = hl_ast_node::dump_array(initializer);
    retval["inner_variable"] = inner_variable->dump();
    retval["name"] = name;
    retval["constant"] = constant;
    retval["type"] = c_types_to_string(type);

    return retval;
}
