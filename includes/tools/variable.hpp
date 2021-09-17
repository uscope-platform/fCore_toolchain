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

    [[nodiscard]]  unsigned int get_bound_reg() const { return bound_register[0];};
    [[nodiscard]]  void set_bound_reg(unsigned int reg) { bound_register[0] = reg;};

    [[nodiscard]]  unsigned int get_bound_reg(unsigned int idx) const { return bound_register[idx];};
    [[nodiscard]]  void set_bound_reg(unsigned int idx, unsigned int val) { bound_register[idx] = val;};

    [[nodiscard]]  std::vector<unsigned int> get_bound_reg_array() const { return bound_register;};
    [[nodiscard]]  void set_bound_reg_array(std::vector<unsigned int> reg) { bound_register = std::move(reg);};

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
    std::vector<unsigned int> bound_register;

    std::string name;
    std::vector<bool> used;

    int const_i;
    float const_f;

};


#endif //FCORE_TOOLCHAIN_VARIABLE_HPP
