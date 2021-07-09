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

#include "passes/low_level/pseudo_instructions_pass.hpp"


pseudo_instructions_pass::pseudo_instructions_pass() : pass_base<ll_ast_node>("pseudo instruction implementation pass"){

}

std::shared_ptr<ll_ast_node> pseudo_instructions_pass::process_leaf(std::shared_ptr<ll_ast_node> element) {
    std::shared_ptr<ll_ast_node> ret_val = element;
    if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);
        if (node->is_pseudo()){
            instruction_t instr = node->getStringInstr();
            std::string opcode = instr.opcode;
            if(opcode ==  "mov"){
                instr.arguments.push_back(instr.arguments[1]);
                variable zero(false, "r0");
                instr.arguments[1] = std::make_shared<variable>(zero);

            }

            std::string new_opcode = fcore_pseudo_op[instr.opcode];
            ret_val = std::make_shared<ll_instruction_node>(fcore_op_types[new_opcode], new_opcode, instr.arguments);
        }
    }

    return ret_val;
}
