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

#ifndef FCORE_TOOLCHAIN_LL_INSTRUCTION_NODE_HPP
#define FCORE_TOOLCHAIN_LL_INSTRUCTION_NODE_HPP

#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>

#include "ast/low_level/ll_ast_node.hpp"
#include "tools/variable.hpp"
#include "fCore_isa.hpp"

typedef struct {
    std::string opcode;
    std::vector<std::shared_ptr<variable>> arguments;
    float intercalated_constant;
} instruction_t;


class ll_instruction_node : public ll_ast_node{

public:
    ll_instruction_node() = default;
    explicit ll_instruction_node(isa_instruction_type inst_type);
    ll_instruction_node(isa_instruction_type inst_type, std::string opcode, std::vector<std::shared_ptr<variable>> arguments);
    ll_instruction_node(isa_instruction_type inst_type, float constant);
    isa_instruction_type get_type();
    [[nodiscard]] uint32_t emit() const;
    [[nodiscard]] int instruction_count() const;
    bool is_terminal() override;
    void print();
    [[nodiscard]] bool is_pseudo() const { return type == isa_pseudo_instruction;};
    [[nodiscard]] const instruction_t &getStringInstr() const;
    void setStringInstr(const instruction_t &stringInstr);

    friend bool operator==(const ll_instruction_node& lhs, const ll_instruction_node& rhs);

private:
    [[nodiscard]] uint32_t emit_branch() const;
    [[nodiscard]] uint32_t emit_immediate() const;
    [[nodiscard]] uint32_t emit_independent() const;
    [[nodiscard]] uint32_t emit_register() const;
    [[nodiscard]] uint32_t emit_conversion() const;
    [[nodiscard]] uint32_t emit_load_const() const;
    [[nodiscard]] uint32_t emit_intercalated_const() const;
    void print_immediate() const;
    void print_independent() const;
    void print_register() const;
    void print_branch() const;
    void print_conversion() const;
    void print_load_const() const;
    void print_intercalated_const() const;

    isa_instruction_type type;
    instruction_t string_instr;


};



#endif //FCORE_TOOLCHAIN_LL_INSTRUCTION_NODE_HPP
