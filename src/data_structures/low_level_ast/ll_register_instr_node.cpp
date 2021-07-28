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


#include "data_structures/low_level_ast/ll_register_instr_node.hpp"

#include <utility>

ll_register_instr_node::ll_register_instr_node(std::string op, std::shared_ptr<variable> op_a, std::shared_ptr<variable> op_b,
                                               std::shared_ptr<variable> dest) : ll_instruction_node(isa_register_instruction) {
    operand_a = std::move(op_a);
    operand_b = std::move(op_b);
    destination = std::move(dest);
    opcode = std::move(op);
}

uint32_t ll_register_instr_node::emit() {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[opcode] & opcode_mask;
    raw_instr += (operand_a->get_value() & register_mask) << fcore_opcode_width;
    raw_instr += (operand_b->get_value() & register_mask) << (fcore_opcode_width+fcore_register_address_width);
    raw_instr += (destination->get_value() & register_mask) << (fcore_opcode_width+2*fcore_register_address_width);

    return raw_instr;
}

void ll_register_instr_node::print() {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << opcode <<
              " OPERAND A: " << operand_a->to_str() << " OPERAND B: " << operand_b->to_str() <<
              " DESTINATION: " << destination->to_str() <<std::endl;
}

int ll_register_instr_node::instruction_count() {
    return 1;
}

bool operator==(const ll_register_instr_node &lhs, const ll_register_instr_node &rhs) {
    bool retval = true;

    retval &= *lhs.operand_a == *rhs.operand_a;
    retval &= *lhs.operand_b == *rhs.operand_b;
    retval &= *lhs.destination == *rhs.destination;
    retval &= rhs.opcode == lhs.opcode;
    return retval;
}

