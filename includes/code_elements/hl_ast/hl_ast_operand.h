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
    string_operand = 2,
    variable_operand = 3,
}operand_type_t;

class hl_ast_operand : public hl_ast_node{
public:
    hl_ast_operand(operand_type_t ot);
    void set_name(const std::string &name);
    void set_immediate(const int &v);
    void set_immediate(const float &v);
    void set_string(const std::string &s);
    std::string get_string();
    operand_type_t  get_type();
    [[nodiscard]] int get_int_value() const;
    [[nodiscard]] float get_float_val() const;
    friend bool operator==(const hl_ast_operand& lhs, const hl_ast_operand& rhs);
private:
    std::string name;
    operand_type_t operand_type;
    int integer_imm;
    float float_imm;
    std::string string_imm;
};

#endif //FCORE_HAS_HL_AST_OPERAND_H
