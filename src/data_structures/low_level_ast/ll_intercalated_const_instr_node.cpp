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

#include "data_structures/low_level_ast/ll_intercalated_const_instr_node.hpp"

ll_intercalated_const_instr_node::ll_intercalated_const_instr_node(float constant) : ll_instruction_node(isa_intercalated_constant){
    intercalated_constant = constant;
}

uint32_t ll_intercalated_const_instr_node::emit() {
    uint32_t  raw_instr = 0;
    float constant = intercalated_constant;
    memcpy(&raw_instr, &constant, sizeof(raw_instr));
    return raw_instr;
}

void ll_intercalated_const_instr_node::print() {
}

int ll_intercalated_const_instr_node::instruction_count() {
    return 1;
}

bool operator==(const ll_intercalated_const_instr_node &lhs, const ll_intercalated_const_instr_node &rhs) {
    bool retval = true;

    retval &= lhs.intercalated_constant == rhs.intercalated_constant;
    retval &= rhs.opcode == lhs.opcode;
    return retval;
}
