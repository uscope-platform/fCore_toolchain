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
    constant = false;
    used = {false};
    type = variable_regular_type;
    float_const = false;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register = 0;
    is_array = false;
    array_length = 0;
}

variable::variable(bool const_status, std::string text) {
    name = std::move(text);
    constant = const_status;
    used = {false};
    type = variable_regular_type;
    float_const = false;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register = 0;
    is_array = false;
    array_length = 0;
}

variable::variable(bool const_status, std::string text, bool float_status) {

    name = std::move(text);
    constant = const_status;
    used = {false};
    type = variable_regular_type;
    float_const = float_status;
    first_occurrence = 32768;
    last_occurrence = 0;
    bound_register = 0;
    is_array = false;
    array_length = 0;
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

    if(constant){
        return std::stoi(name, nullptr, 0);
    }
    throw std::runtime_error("Invalid operation: the compiler tried to get the numeric value of a variable");
}

bool operator==(const variable &lhs, const variable &rhs) {
    bool cond = lhs.type == rhs.type;
    cond &= lhs.first_occurrence == rhs.first_occurrence;
    cond &= lhs.last_occurrence == rhs.last_occurrence;
    cond &= lhs.name == rhs.name;
    cond &= lhs.bound_register == rhs.bound_register;
    cond &= lhs.float_const == rhs.float_const;
    cond &= lhs.constant == rhs.constant;
    cond &= lhs.used == rhs.used;

    return cond;
}
