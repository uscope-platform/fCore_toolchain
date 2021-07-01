//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_ast_operand.h"

hl_ast_operand::hl_ast_operand(hl_ast_node_type_t  nt, operand_type_t ot) : hl_ast_node(nt) {
    operand_type = ot;
    integer_imm = 0;
    float_imm = 0.0;
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
