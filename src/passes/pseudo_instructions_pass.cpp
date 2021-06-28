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

#include "passes/pseudo_instructions_pass.hpp"


ast_t pseudo_instructions_pass::process_leaf(ast_t element) {
    if (element->inst.is_pseudo()){
        instruction_t instr = element->inst.getStringInstr();
        std::string opcode = instr.opcode;
        if(opcode ==  "mov"){
            instr.arguments.push_back(instr.arguments[1]);
            variable zero(false, "r0");
            instr.arguments[1] = std::make_shared<variable>(zero);

        }

        std::string new_opcode = fcore_pseudo_op[instr.opcode];
        instruction new_inst(fcore_op_types[new_opcode], new_opcode, instr.arguments);
        element->inst = new_inst;
    }
    return element;
}
