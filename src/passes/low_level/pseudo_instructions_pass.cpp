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

#include "passes/low_level/pseudo_instructions_pass.hpp"


pseudo_instructions_pass::pseudo_instructions_pass() : pass_base<ll_ast_node>("pseudo instruction implementation pass"){

}

std::shared_ptr<ll_ast_node> pseudo_instructions_pass::process_leaf(std::shared_ptr<ll_ast_node> element) {
    std::shared_ptr<ll_ast_node> ret_val = element;
    if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);
        if (node->is_pseudo()){
            std::shared_ptr<ll_pseudo_instr_node> pseudo_instr = std::static_pointer_cast<ll_pseudo_instr_node>(node);
            std::string opcode = node->get_opcode();
            auto arguments = pseudo_instr->get_arguments();
            if(opcode ==  "mov"){
                arguments.push_back(arguments[1]);
                variable zero(false, "r0");
                arguments[1] = std::make_shared<variable>(zero);

            }

            std::string new_opcode = fcore_pseudo_op[node->get_opcode()];
            switch (fcore_op_types[new_opcode]) {
                case isa_register_instruction:
                    ret_val = std::make_shared<ll_register_instr_node>(new_opcode, arguments[0], arguments[1], arguments[2]);
                    break;
                case isa_independent_instruction:
                    ret_val = std::make_shared<ll_independent_inst_node>(new_opcode);
                    break;
                case isa_conversion_instruction:
                    ret_val = std::make_shared<ll_conversion_instr_node>(new_opcode, arguments[0], arguments[1]);
                    break;
                case isa_load_constant_instruction:
                    ret_val = std::make_shared<ll_load_constant_instr_node>(new_opcode, arguments[0], arguments[1]);
                    break;
            }
        }
    }

    return ret_val;
}
