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

#ifndef FCORE_TOOLCHAIN_VARIABLE_HPP
#define FCORE_TOOLCHAIN_VARIABLE_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <regex>
#include <iostream>
#include "fCore_isa.hpp"

#define TYPE_INPUT 0
#define TYPE_OUTPUT 1
#define TYPE_REGULAR 2

class variable {
public:
    variable();
    variable(bool const_status, std::string text);
    variable(bool const_status, std::string text, bool is_float);


    static bool is_terminal() { return true;};
    [[nodiscard]] bool is_constant() const { return constant;};
    void set_used(bool status);
    [[nodiscard]] bool is_used() const;
    [[nodiscard]] bool is_float() const {return float_const;};
    [[nodiscard]]  unsigned int get_bound_reg() const { return bound_register;};
    [[nodiscard]]  void set_bound_reg(unsigned int reg) { bound_register = reg;};
    [[nodiscard]] std::string to_str() const { return name;};
    [[nodiscard]] uint32_t get_value() const;
    friend bool operator==(const variable& lhs, const variable& rhs);

    int type;
    unsigned int first_occurrence;
    unsigned int last_occurrence;

private:
    unsigned int bound_register;
    std::string name;
    bool float_const;
    bool constant;
    bool used;

};


#endif //FCORE_TOOLCHAIN_VARIABLE_HPP
