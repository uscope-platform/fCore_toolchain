//
// Created by fils on 29/04/20.
//

#include "immediate_instruction.h"

immediate_instruction::immediate_instruction(uint8_t opcode,uint8_t dest, uint16_t immediate) {

    instr = 0;
    instr += opcode & 0xfu;
    instr_content.opcode = opcode;
    instr += (dest & 0xfu) << 4u;
    instr_content.destination = dest;
    instr += (immediate & 0xfffu) << 8u;
    instr_content.immediate = immediate;
}

uint32_t immediate_instruction::emit() {
    return instr;
}

void immediate_instruction::print() {
    std::cout << std::setfill('0') << std::setw(4) << std::hex << instr << " -> OPCODE: " << instr_content.opcode << " DESTINATION: " << instr_content.destination << " IMMEDIATE: " << instr_content.immediate << std::endl;
}
