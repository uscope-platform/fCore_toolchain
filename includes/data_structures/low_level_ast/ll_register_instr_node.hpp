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

#ifndef FCORE_TOOLCHAIN_LL_REGISTER_INSTR_NODE_H
#define FCORE_TOOLCHAIN_LL_REGISTER_INSTR_NODE_H

#include "data_structures/low_level_ast/ll_instruction_node.hpp"
#include "tools/variable.hpp"

class ll_register_instr_node: public ll_instruction_node {
public:
    ll_register_instr_node(std::string op, std::shared_ptr<variable> op_a, std::shared_ptr<variable> op_b, std::shared_ptr<variable> dest);
    uint32_t emit() override;
    std::string disassemble() override;
    void print() override;
    int instruction_count() override;

    friend bool operator==(const ll_register_instr_node& lhs, const ll_register_instr_node& rhs);

    std::shared_ptr<variable> get_operand_a() {return operand_a;};
    std::shared_ptr<variable> get_operand_b() {return operand_b;};
    std::shared_ptr<variable> get_destination() {return destination;};
    std::vector<std::shared_ptr<variable>> get_arguments() override {return {operand_a, operand_b, destination};};
    void set_arguments(const std::vector<std::shared_ptr<variable>> &a) override;
private:
    std::shared_ptr<variable> operand_a;
    std::shared_ptr<variable> operand_b;
    std::shared_ptr<variable> destination;
};


#endif //FCORE_TOOLCHAIN_LL_REGISTER_INSTR_NODE_H
