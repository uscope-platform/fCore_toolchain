//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_ast_operand.h"

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
    return ret_val;
}

hl_ast_operand::operator std::string() {
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
    }
    return ret_val;
}
