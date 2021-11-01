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
// limitations under the License.

#include "tools/variable.hpp"


variable::variable() {

    name = "invalid-variable";
    used = {false};
    variable_class = variable_regular_type;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register.push_back(0);
    array_length = 0;
}

variable::variable(std::string n, float value) {
    name = std::move(n);
    const_f = value;
    variable_type = var_type_float_const;

    used = {false};
    variable_class = variable_regular_type;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register.push_back(0);
    array_length = 0;
    const_i = 0;
}

variable::variable(std::string n, int value) {
    name = std::move(n);
    const_i = value;
    variable_type = var_type_int_const;
    used = {false};
    variable_class = variable_regular_type;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register.push_back(0);
    array_length = 0;
    const_f = 0;
}


variable::variable(std::string n) {
    name = std::move(n);
    const_i = 0;
    variable_type = var_type_scalar;
    used = {false};
    variable_class = variable_regular_type;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register.push_back(0);
    array_length = 0;
    const_f = 0;
}


void variable::set_used(bool status) {
    used[0] = status;
}

bool variable::is_used() const {
    return used[0];
}

uint32_t variable::get_value() const {

    std::regex re("r(\\d\\d?)");
    std::smatch m;

    if(std::regex_match(name, m, re)) {
        return std::stoi(m[1]);
    }

    if(is_constant()){
        return const_i;
    }
    throw std::runtime_error("Invalid operation: the compiler tried to get the numeric value of a variable");
}

bool operator==(const variable &lhs, const variable &rhs) {
    bool cond = lhs.variable_class == rhs.variable_class;
    cond &= lhs.first_occurrence == rhs.first_occurrence;
    cond &= lhs.last_occurrence == rhs.last_occurrence;
    cond &= lhs.name == rhs.name;
    cond &= lhs.bound_register == rhs.bound_register;
    cond &= lhs.used == rhs.used;

    return cond;
}

float variable::get_const_f() {
    if(variable_type == var_type_float_const){
        return const_f;
    } else {
        return (float) const_i;
    }
}

int variable::get_const_i() {
    if(variable_type == var_type_int_const){
        return const_i;
    } else {
        return (int)const_f;
    }
}

std::string variable::to_str() {
    switch (variable_type) {
        case var_type_int_const:
            return std::to_string(const_i);
        case var_type_float_const:
            return std::to_string(const_f);
        case var_type_scalar:
        case var_type_array:
            return name;
    }
    return "";
}

void variable::set_const_f(float f) {
    if(variable_type == var_type_float_const){
        const_f = f;
    } else {
        throw std::runtime_error("INTERNAL ERROR: Setting the floating point value of a non floating point variable is not allowed");
    }
}

void variable::set_const_i(int i) {
    if(variable_type == var_type_int_const){
        const_i = i;
    } else {
        throw std::runtime_error("INTERNAL ERROR: Setting the integer  value of a non integer point variable is not allowed");
    }
}

std::shared_ptr<variable> variable::deep_copy(const std::shared_ptr <variable>& original) {
    std::shared_ptr<variable> copied_var = std::make_shared<variable>();

    copied_var->name = original->name;
    copied_var->variable_type = original->variable_type;
    copied_var->variable_class = original->variable_class;
    copied_var->first_occurrence = original->first_occurrence;
    copied_var->last_occurrence = original->last_occurrence;
    copied_var->array_length = original->array_length;
    copied_var->bound_register = original->bound_register;
    copied_var->used = original->used;
    copied_var->const_i = original->const_i;
    copied_var->const_f = original->const_f;

    return copied_var;
}

nlohmann::json variable::dump() {
    nlohmann::json ret_val;

    ret_val["name"] = name;
    ret_val["type"] = variable_type;
    ret_val["class"] = variable_class;
    ret_val["first_occurrence"] = first_occurrence;
    ret_val["last_occurrence"] = last_occurrence;
    ret_val["array_length"] = array_length;
    ret_val["bound_register"] = bound_register;
    ret_val["used"] = used;
    ret_val["const_i"] = const_i;
    ret_val["const_f"] = const_f;

    return ret_val;
}
