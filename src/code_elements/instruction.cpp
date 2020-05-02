//
// Created by fils on 29/04/20.
//

#include "instruction.h"

instruction::instruction() {

}


instruction::instruction(uint8_t opcode, uint8_t dest, uint16_t immediate) {
    type = IMMEDIATE_INSTRUCTION;
    instr = 0;
    instr += opcode & 0xfu;
    immediate_instr.opcode = opcode;
    instr += (dest & 0xfu) << 4u;
    immediate_instr.destination = dest;
    instr += (immediate & 0xfffu) << 8u;
    immediate_instr.immediate = immediate;
}

instruction::instruction(uint8_t opcode) {
    type = INDEPENDENT_INSTRUCTION;
    instr = 0;
    instr += opcode & 0xfu;
}

instruction::instruction(uint8_t opcode, uint8_t op_a, uint8_t op_b, uint8_t dest) {
    type = REGISTER_INSTRUCTION;
    instr = 0;
    instr += opcode & 0xfu;
    register_instr.opcode = opcode;

    instr += (op_a & 0xfu) << 4u;
    register_instr.op_a = op_a;

    instr += (op_b & 0xfu) << 8u;
    register_instr.op_b = op_b;

    instr += (dest & 0xfu) << 12u;
    register_instr.dest = dest;
}

uint32_t instruction::emit() {
    return instr;
}

void instruction::print() {
    switch(type){
        case IMMEDIATE_INSTRUCTION:
            print_immediate();
            break;
        case INDEPENDENT_INSTRUCTION:
            print_independent();
            break;
        case REGISTER_INSTRUCTION:
            print_register();
            break;
    }
}

void instruction::print_immediate() {
    std::cout << std::setfill('0') << std::setw(4) << std::hex << instr << " -> OPCODE: " << immediate_instr.opcode <<
    " DESTINATION: " << immediate_instr.destination << " IMMEDIATE: " << immediate_instr.immediate << std::endl;
}

void instruction::print_independent() {
    std::cout << std::setfill('0') << std::setw(4) << std::hex << instr << " -> OPCODE: " << instr << std::endl;
}

void instruction::print_register() {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << instr << " -> OPCODE: " << register_instr.opcode <<
    " OPERAND A: " << register_instr.op_a << " OPERAND B: " << register_instr.op_b <<
    " DESTINATION: " << register_instr.dest <<std::endl;
}

