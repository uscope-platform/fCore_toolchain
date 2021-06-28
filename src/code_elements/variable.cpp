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
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.


#include "code_elements/variable.hpp"


variable::variable() {
    identifier = 0;
    name = "invalid-variable";
    constant = false;
    used = false;
    type = TYPE_REGULAR;
    float_const = false;
    first_occurrence = 32768;
    last_occurrence = 0;
}

variable::variable(bool const_status, std::string text) {
    identifier = std::hash<std::string>{}(text);
    name = std::move(text);
    constant = const_status;
    used = false;
    type = TYPE_REGULAR;
    float_const = false;
    first_occurrence = 32768;
    last_occurrence = 0;
}

variable::variable(bool const_status, std::string text, bool float_status) {
    identifier = std::hash<std::string>{}(text);
    name = std::move(text);
    constant = const_status;
    used = false;
    type = TYPE_REGULAR;
    float_const = float_status;
    first_occurrence = 32768;
    last_occurrence = 0;
}


void variable::set_used(bool status) {
    used = status;
}

bool variable::is_used() const {
    return used;
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
