//
// Created by fils on 06/05/20.
//


#include "pseudo_instructions_pass.hpp"


ast_t pseudo_instructions_pass::process_leaf(ast_t element) {
    if (element->inst.is_pseudo()){
        instruction_t instr = element->inst.getStringInstr();
        std::string opcode = instr.opcode;
        if(opcode ==  "mov"){
            instr.arguments.push_back(instr.arguments[1]);
            variable zero(false, "r0");
            instr.arguments[1] = zero;

        }

        std::string new_opcode = fcore_pseudo_op[instr.opcode];
        instruction new_inst(fcore_op_types[new_opcode], new_opcode, instr.arguments);
        element->inst = new_inst;
    }
    return element;
}
