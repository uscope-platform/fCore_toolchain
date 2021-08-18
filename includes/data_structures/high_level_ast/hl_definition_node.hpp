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

#ifndef FCORE_TOOLCHAIN_HL_DEFINITION_NODE_HPP
#define FCORE_TOOLCHAIN_HL_DEFINITION_NODE_HPP

#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "tools/variable.hpp"

#include <utility>
#include <string>

class hl_definition_node : public hl_ast_node{
public:
    hl_definition_node(std::string n, c_types_t ct, std::shared_ptr<variable> v);
    void set_name(std::string name);
    std::string get_name(){ return name;};
    c_types_t get_type(){ return type;};
    bool is_initialized();
    bool is_scalar();
    void set_constant(bool c);
    bool is_constant();

    std::vector<std::shared_ptr<hl_ast_node>> get_array_index() {return array_index;};
    void set_array_index(std::vector<std::shared_ptr<hl_ast_node>> i) {array_index = std::move(i);};

    std::shared_ptr<hl_ast_node> get_scalar_initializer();
    void set_scalar_initializer(const std::shared_ptr<hl_ast_node>& init);

    std::vector<std::shared_ptr<hl_ast_node>> get_array_initializer() {return initializer;};
    void set_array_initializer(const std::vector<std::shared_ptr<hl_ast_node>> &init) {initializer = init;};

    std::shared_ptr<variable> get_variable() {return inner_variable;};
    void set_variable(std::shared_ptr<variable> var) {inner_variable = std::move(var);};

    void set_array_shape(std::vector<int> &shape){array_shape = shape;};
    std::vector<int> get_array_shape(){return array_shape;};

    unsigned int get_array_size();
    unsigned int get_flattened_idx(std::vector<int> md_idx);
    std::string pretty_print() override;
    bool is_terminal() override {
        return true;
    }

    friend bool operator==(const hl_definition_node& lhs, const hl_definition_node& rhs);

protected:
    bool constant;
    std::string name;
    c_types_t type;
    std::vector<std::shared_ptr<hl_ast_node>> initializer;
    std::vector<std::shared_ptr<hl_ast_node>> array_index;
    std::shared_ptr<variable> inner_variable;

    std::vector<int> array_shape;
};


#endif //FCORE_TOOLCHAIN_HL_DEFINITION_NODE_HPP
