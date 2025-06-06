//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "data_structures/common/variable.hpp"

namespace fcore{


    variable::variable() {

        name = "invalid-variable";
        used = {false};
        variable_class = {variable_regular_type, false};
        first_occurrence = 32768;
        last_occurrence = 0;
        bound_register.push_back(-1);
        contiguity = false;
        c_type = c_type_void;
    }

    variable::variable(const std::string &n, float value) {
        name = n;
        const_f = value;
        variable_type = var_type_float_const;
        used = {false};
        variable_class =  {variable_regular_type, false};
        first_occurrence = 32768;
        last_occurrence = 0;
        bound_register.push_back(-1);
        const_i = 0;
        contiguity = false;
        c_type = c_type_float;
    }

    variable::variable(const std::string &n, int value) {
        name = n;
        const_i = value;
        variable_type = var_type_int_const;
        used = {false};
        variable_class =  {variable_regular_type, false};
        first_occurrence = 32768;
        last_occurrence = 0;
        bound_register.push_back(-1);
        const_f = 0;
        contiguity = false;
        c_type = c_type_int;
    }


    variable::variable(std::string n) {
        name = std::move(n);
        const_i = 0;
        variable_type = var_type_scalar;
        used = {false};
        variable_class = {variable_regular_type, false};
        first_occurrence = 32768;
        last_occurrence = 0;
        bound_register.push_back(-1);
        const_f = 0;
        contiguity = false;
        c_type = c_type_char;
    }


    void variable::set_used(bool status) {
        used[0] = status;
    }

    bool variable::is_used() const {
        return used[0];
    }

    std::pair<uint32_t, bool> variable::get_value() const {

        if(name.starts_with('r')){
            if(name.ends_with('c')){
                auto reg_text = name.substr(1, name.size()-2);
                return std::make_pair(std::stoi(reg_text), true);
            }
            auto rest = name;
            rest.erase(0,1);
            if(!rest.empty() && std::find_if(rest.begin(), rest.end(), [](unsigned char c) { return !std::isdigit(c); }) == rest.end()){
                return std::make_pair(std::stoi(rest), false);
            };
        }

        if(is_constant()){
            return std::make_pair(const_i, false);
        }
        throw std::runtime_error("Invalid operation: the compiler tried to get the numeric value of a variable");
    }

    float variable::get_float_val() const {
        if(variable_type == var_type_float_const){
            return const_f;
        } else {
            return static_cast<float>(const_i);
        }
    }

    int variable::get_int_value() const {
        if(variable_type == var_type_int_const){
            return const_i;
        } else {
            return static_cast<int>(const_f);
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


    std::shared_ptr<variable> variable::deep_copy(const std::shared_ptr <variable>& original) {
        std::shared_ptr<variable> copied_var = std::make_shared<variable>();

        copied_var->name = original->name;
        copied_var->variable_type = original->variable_type;
        copied_var->variable_class = original->variable_class;
        copied_var->first_occurrence = original->first_occurrence;
        copied_var->last_occurrence = original->last_occurrence;
        copied_var->bound_register = original->bound_register;
        copied_var->used = original->used;
        copied_var->const_i = original->const_i;
        copied_var->const_f = original->const_f;
        copied_var->contiguity = original->contiguity;
        copied_var->array_shape = original->array_shape;
        copied_var->array_index = original->array_index;
        copied_var->struct_accessors = original->struct_accessors;
        copied_var->c_type = original->c_type;
        return copied_var;
    }

    std::string variable::get_identifier() {
        return get_identifier(array_index);
    }

    std::string variable::get_identifier(const std::vector<int>& idx) {
        std::string ret = name;
        for(auto &elem:idx){
            ret += "_" + std::to_string(elem);
        }
        return ret;
    }

    std::string variable::get_linear_identifier() {
        if(array_shape.empty()){
            return name;
        }
        std::string ret = name + "_" + std::to_string(get_linear_index());
        return ret;
    }

    std::string variable::get_linear_identifier(const std::vector<int> &idx) {
        if(array_shape.empty()){
            return name;
        }
        std::string ret = name + "_" + std::to_string(get_linear_index(idx));
        return ret;
    }

    std::string variable::get_linear_identifier(const int &idx) {
        if(array_shape.empty()){
            return name;
        }
        std::string ret = name + "_" + std::to_string(idx);
        return ret;
    }

    int variable::get_linear_index() {
        return get_linear_index(array_index);
    }

    int variable::get_linear_index(const std::vector<int> &idx) {
        if(variable_type == var_type_scalar || variable_type == var_type_float_const || variable_type == var_type_int_const){
            return -1;
        }
        return linearize_array(array_shape, idx);
    }

    int variable::get_bound_reg() {
        if(!array_index.empty() && bound_register.size()!=1){
            return bound_register[get_linear_index()];
        }
        return bound_register[0];
    }

    unsigned int variable::get_size() {

        unsigned int shape = 1;
        for(auto &dim:array_shape){
            shape *= dim;
        }
        return shape;
    }

    bool variable::is_explicit_register(std::string s) {
        bool is_register_handle = false;
        if(s.starts_with("r")){
            s.erase(0,1);
            is_register_handle =  !s.empty() && std::find_if(s.begin(),
                                                                s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
        }
        return is_register_handle;
    }

    std::string variable::type_to_string(const c_types_t &t) {
        std::map <c_types_t,std::string>  translator {
                    {c_type_void, "void"},
                    {c_type_char, "char"},
                    {c_type_short, "short"},
                    {c_type_int, "int"},
                    {c_type_long, "long"},
                    {c_type_float, "float"},
                    {c_type_struct, "struct"}
        };

        return translator[t];
    }

}
