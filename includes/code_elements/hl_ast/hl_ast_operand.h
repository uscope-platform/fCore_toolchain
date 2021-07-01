//
// Created by fils on 01/07/2021.
//

#ifndef FCORE_HAS_HL_AST_OPERAND_H
#define FCORE_HAS_HL_AST_OPERAND_H

#include "hl_ast_node.h"

#include <string>

typedef enum{
    integer_immediate_operand = 0,
    float_immediate_operand = 1,
    variable_operand = 2,
}operand_type_t;

class hl_ast_operand : public hl_ast_node{
public:
    hl_ast_operand(hl_ast_node_type_t nt, operand_type_t ot);
    void set_name(const std::string &name);
    void set_immediate(const int &v);
    void set_immediate(const float &v);
    [[nodiscard]] int get_int_value() const;
    [[nodiscard]] float get_float_val() const;
private:
    std::string name;
    operand_type_t operand_type;
    int integer_imm;
    float float_imm;
};

#endif //FCORE_HAS_HL_AST_OPERAND_H
