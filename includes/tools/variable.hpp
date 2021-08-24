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
    var_type_float_const = 0,
    var_type_int_const = 1,
    var_type_scalar = 2,
    var_type_array = 3
} variable_type_t;


class variable {
public:
    variable();
    explicit variable(std::string n);
    variable(std::string n, float value);
    variable(std::string n, int value);

    float get_const_f();
    int get_const_i();

    void set_const_f(float f);
    void set_const_i(int i);

    variable_type_t get_type() {return variable_type;};
    void set_type(variable_type_t t) {variable_type = t;};

    void set_name(std::string n){name = std::move(n);};
    std::string get_name() {return name;};

    [[nodiscard]] std::string to_str();

    static bool is_terminal() { return true;};

    void set_used(bool status);
    [[nodiscard]] bool is_used() const;

    [[nodiscard]] bool is_constant() const { return (variable_type ==var_type_float_const || variable_type == var_type_int_const);};
    [[nodiscard]] bool is_float() const {return variable_type == var_type_float_const;};

    [[nodiscard]]  unsigned int get_bound_reg() const { return bound_register;};
    [[nodiscard]]  void set_bound_reg(unsigned int reg) { bound_register = reg;};

    [[nodiscard]] uint32_t get_value() const;
    friend bool operator==(const variable& lhs, const variable& rhs);

    variable_class_t get_variable_class() {return variable_class;};
    void set_variable_class(variable_class_t vc) {variable_class = vc;};

    unsigned int get_last_occurrence() const {return last_occurrence;};
    void set_last_occurrence(unsigned int lo) {last_occurrence = lo;};

    unsigned int get_first_occurrence() const {return first_occurrence;};
    void set_first_occurrence(unsigned int fo) {first_occurrence = fo;};

    unsigned int get_array_length() const {return array_length;};
    void set_array_length(unsigned int al) {array_length = al;};

    static std::shared_ptr<variable> deep_copy(const std::shared_ptr<variable>& original);

private:

    variable_class_t variable_class;
    variable_type_t variable_type;

    unsigned int first_occurrence;
    unsigned int last_occurrence;

    unsigned int array_length;

    unsigned int bound_register;
    std::string name;
    std::vector<bool> used;

    int const_i;
    float const_f;

};


#endif //FCORE_TOOLCHAIN_VARIABLE_HPP
