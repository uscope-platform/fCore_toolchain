//
// Created by fils on 06/05/20.
//


#include "pseudo_instructions_pass.hpp"


ast_t pseudo_instructions_pass::process_leaf(ast_t element) {
    if (element->inst.is_pseudo()){
        std::string opcode = element->inst.pseudo_instr.opcode;
        if(opcode ==  "mov"){
            element->inst.pseudo_instr.arg_3 = element->inst.pseudo_instr.arg_2;
            element->inst.pseudo_instr.arg_2 = 0;
        }
        element->inst.specialize_pseudo();
    }
    return element;
}
