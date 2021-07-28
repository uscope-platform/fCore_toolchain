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


#include "data_structures/low_level_ast/ll_instruction_node.hpp"

ll_instruction_node::ll_instruction_node(isa_instruction_type t) : ll_ast_node(ll_type_instr) {
    instruction_type = t;
}

ll_instruction_node::ll_instruction_node(const ll_instruction_node &old_obj) {

    instruction_type = old_obj.instruction_type;
    opcode = old_obj.opcode;
}

isa_instruction_type ll_instruction_node::get_type() {
    return instruction_type;
}

bool ll_instruction_node::is_terminal() {
    return true;
}

bool operator==(const ll_instruction_node &lhs, const ll_instruction_node &rhs) {
    bool retval = true;
    retval &= lhs.instruction_type == rhs.instruction_type;
    retval &= lhs.opcode == rhs.opcode;

    return retval;
}