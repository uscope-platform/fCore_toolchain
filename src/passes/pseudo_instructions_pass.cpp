//
// Created by fils on 06/05/20.
//


#include "pseudo_instructions_pass.hpp"


std::shared_ptr<code_element> pseudo_instructions_pass::process_leaf(std::shared_ptr<code_element> element) {
    if (element->inst.is_pseudo()){
        std::string opcode = element->inst.pseudo_instr.opcode;
        if(opcode ==  "mov"){
            element->inst.pseudo_instr.arg_3 = 0;
        }
        element->inst.specialize_pseudo();
    }
    return element;
}
