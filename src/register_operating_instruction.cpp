//
// Created by fils on 29/04/20.
//

#include "register_operating_instruction.h"

register_operating_instruction::register_operating_instruction(uint8_t opcode, uint8_t op_a, uint8_t op_b,
                                                               uint8_t dest) {
    instr = 0;
    instr += opcode & 0xfu;
    instr_content.opcode = opcode;

    instr += (op_a & 0xfu) << 4u;
    instr_content.op_a = op_a;

    instr += (op_b & 0xfu) << 8u;
    instr_content.op_b = op_b;

    instr += (dest & 0xfu) << 12u;
    instr_content.dest = dest;
}


uint32_t register_operating_instruction::emit() {
    return instr;
}

void register_operating_instruction::print() {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << instr << " -> OPCODE: " << instr_content.opcode << " OPERAND A: " << instr_content.op_a << " OPERAND B: " << instr_content.op_b <<" DESTINATION: " << instr_content.dest <<std::endl;
}

