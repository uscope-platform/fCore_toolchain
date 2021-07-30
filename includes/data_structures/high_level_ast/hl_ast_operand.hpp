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

#ifndef FCORE_TOOLCHAIN_HL_AST_OPERAND_HPP
#define FCORE_TOOLCHAIN_HL_AST_OPERAND_HPP

#include "hl_ast_node.hpp"
#include "tools/variable.hpp"

#include <string>

typedef enum{
    integer_immediate_operand = 0,
    float_immediate_operand = 1,
    variable_operand = 2,
    array_operand = 3
}operand_type_t;

class hl_ast_operand : public hl_ast_node{
public:
    explicit hl_ast_operand(operand_type_t ot);
    void set_name(const std::string &name);
    std::string get_name() { return inner_variable->get_name();};
    void set_immediate(const int &v);
    [[nodiscard]] int get_int_value() const;
    void set_immediate(const float &v);
    [[nodiscard]] float get_float_val() const;
    operand_type_t  get_type();
    void set_type(operand_type_t type);
    std::shared_ptr<hl_ast_node> get_array_index();
    void set_array_index(std::shared_ptr<hl_ast_node> idx);

    void set_variable(std::shared_ptr<variable> v);
    std::shared_ptr<variable> get_variable();


    bool is_terminal() override {return true;}
    std::string pretty_print() override;
    operator std::string();
    friend bool operator==(const hl_ast_operand& lhs, const hl_ast_operand& rhs);
private:

    operand_type_t operand_type;
    std::shared_ptr<hl_ast_node> array_index;

    std::shared_ptr<variable> inner_variable;
};

#endif //FCORE_TOOLCHAIN_HL_AST_OPERAND_HPP
