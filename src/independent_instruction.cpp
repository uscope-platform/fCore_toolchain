//
// Created by fils on 29/04/20.
//

#include "independent_instruction.hpp"

independent_instruction::independent_instruction(uint8_t opcode) {
    instr = 0;
    instr += opcode & 0xfu;
}
void independent_instruction::print() {

    std::cout << std::setfill('0') << std::setw(4) << std::hex << instr << " -> OPCODE: " << instr << std::endl;
}

uint32_t independent_instruction::emit() {
    return instr;
}


