// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.


#include "tools/variable.hpp"


variable::variable() {

    name = "invalid-variable";
    used = {false};
    variable_class = variable_regular_type;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register = 0;
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
    bound_register = 0;
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
    bound_register = 0;
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
    bound_register = 0;
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
