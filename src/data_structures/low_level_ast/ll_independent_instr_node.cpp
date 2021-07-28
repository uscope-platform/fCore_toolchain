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

#include "data_structures/low_level_ast/ll_independent_instr_node.hpp"




ll_independent_inst_node::ll_independent_inst_node(std::string op) : ll_instruction_node(isa_independent_instruction) {
    opcode = std::move(op);
}


uint32_t ll_independent_inst_node::emit() {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    raw_instr += fcore_opcodes[opcode] & opcode_mask;
    return raw_instr;
}

void ll_independent_inst_node::print() {
    std::cout << std::setfill('0') << std::setw(4) << std::hex << emit() << " -> OPCODE: " << opcode << std::endl;
}

int ll_independent_inst_node::instruction_count() {
    return 1;
}

bool operator==(const ll_independent_inst_node &lhs, const ll_independent_inst_node &rhs) {
    return rhs.opcode == lhs.opcode;
}