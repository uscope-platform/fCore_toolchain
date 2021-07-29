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

typedef enum {
    variable_input_type = 0,
    variable_output_type = 1,
    variable_memory_type = 2,
    variable_regular_type = 3
} variable_class_t;

typedef enum {
    float_variable = 0,
    integer_variable = 1,
    true_variable = 2
} variable_type_t;


class variable {
public:
    variable();
    explicit variable(std::string n);
    variable(std::string n, float value);
    variable(std::string n, int value);


    float get_const_f();
    int get_const_i();

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

    variable_class_t variable_class;
    unsigned int first_occurrence;
    unsigned int last_occurrence;

private:

    variable_type_t variable_type;

    bool is_array;
    unsigned int array_length;

    unsigned int bound_register;
    std::string name;
    bool float_const;
    bool constant;
    std::vector<bool> used;

    int const_i;
    float const_f;

};


#endif //FCORE_TOOLCHAIN_VARIABLE_HPP
