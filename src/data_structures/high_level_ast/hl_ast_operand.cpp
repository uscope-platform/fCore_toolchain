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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.01/07/2021.
//

#include "data_structures/high_level_ast/hl_ast_operand.hpp"

#include <utility>

hl_ast_operand::hl_ast_operand(operand_type_t ot) : hl_ast_node(hl_ast_node_type_operand) {
    operand_type = ot;
    integer_imm = 0;
    float_imm = 0.0;
    string_imm = "";
}

void hl_ast_operand::set_name(const std::string &n) {
 name = n;
}

void hl_ast_operand::set_immediate(const int &v) {
    integer_imm = v;
}

void hl_ast_operand::set_immediate(const float &v) {
    float_imm = v;
}

int hl_ast_operand::get_int_value() const {
    return integer_imm;
}

float hl_ast_operand::get_float_val() const {
    return float_imm;
}

void hl_ast_operand::set_string(const std::string &s) {
    string_imm = s;
}

std::string hl_ast_operand::get_string() {
    return string_imm;
}

operand_type_t hl_ast_operand::get_type() {
    return operand_type;
}

bool operator==(const hl_ast_operand &lhs, const hl_ast_operand &rhs) {
    bool ret_val = true;
    ret_val &= lhs.name == rhs.name;
    ret_val &= lhs.string_imm == rhs.string_imm;
    ret_val &= lhs.float_imm == rhs.float_imm;
    ret_val &= lhs.integer_imm == rhs.integer_imm;
    ret_val &= lhs.operand_type == rhs.operand_type;
    ret_val &= lhs.node_type == rhs.node_type;
    if(lhs.array_index != nullptr && rhs.array_index != nullptr)
        ret_val &= hl_ast_node::compare_content_by_type(lhs.array_index, rhs.array_index);
    else if(lhs.array_index == nullptr && rhs.array_index == nullptr)
        ret_val &= true;
    else
        ret_val &= false;

    return ret_val;
}

hl_ast_operand::operator std::string() {
    return pretty_print();
}

std::string hl_ast_operand::pretty_print() {
    std::string ret_val;
    switch (operand_type) {
        case integer_immediate_operand:
            ret_val = std::to_string(integer_imm);
            break;
        case float_immediate_operand:
            ret_val = std::to_string(float_imm);
            break;
        case variable_operand:
            ret_val = name;
            break;
        case string_operand:
            ret_val = string_imm;
            break;
        case array_operand:
            ret_val = name + '[' + array_index->pretty_print() + ']';
    }
    return ret_val;
}

std::shared_ptr<hl_ast_node> hl_ast_operand::get_array_index() {
    return array_index;
}

void hl_ast_operand::set_array_index(std::shared_ptr<hl_ast_node> idx) {
    array_index = std::move(idx);
}

void hl_ast_operand::set_type(operand_type_t type) {
    operand_type = type;
}