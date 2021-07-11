// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_HAS_HL_AST_OPERAND_HPP
#define FCORE_HAS_HL_AST_OPERAND_HPP

#include "hl_ast_node.hpp"

#include <string>

typedef enum{
    integer_immediate_operand = 0,
    float_immediate_operand = 1,
    string_operand = 2,
    variable_operand = 3,
}operand_type_t;

class hl_ast_operand : public hl_ast_node{
public:
    explicit hl_ast_operand(operand_type_t ot);
    void set_name(const std::string &name);
    std::string get_name() { return name;};
    void set_immediate(const int &v);
    [[nodiscard]] int get_int_value() const;
    void set_immediate(const float &v);
    [[nodiscard]] float get_float_val() const;
    void set_string(const std::string &s);
    std::string get_string();
    operand_type_t  get_type();

    bool is_terminal() override {
        return true;
    }
    operator std::string();
    friend bool operator==(const hl_ast_operand& lhs, const hl_ast_operand& rhs);
private:
    std::string name;
    operand_type_t operand_type;
    int integer_imm;
    float float_imm;
    std::string string_imm;
};

#endif //FCORE_HAS_HL_AST_OPERAND_HPP
