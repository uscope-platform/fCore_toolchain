//
// Created by fils on 29/04/20.
//

#include "instruction.h"
#include "../../include/fCore_isa.hpp"
#include <utility>

instruction::instruction() {

}

instruction::instruction(int inst_type, uint32_t complete_instr) {
    type = inst_type;
    if(inst_type!=GENERATED_INSTRUCTION){
        throw std::runtime_error("This constructor is meant only for generated instructions");
    }
    instr = complete_instr;

}
instruction::instruction(int inst_type, std::vector<uint16_t> arguments) {
    type = inst_type;
    switch (type) {
        case IMMEDIATE_INSTRUCTION:
            form_imm_inst(arguments[0], arguments[1], arguments[2]);
            break;
        case REGISTER_INSTRUCTION:
            form_reg_inst(arguments[0], arguments[1], arguments[2], arguments[3]);
            break;
        case INDEPENDENT_INSTRUCTION:
            form_indep_inst(arguments[0]);
            break;
        case  BRANCH_INSTRUCTION:
            form_branch_inst(arguments[0], arguments[1], arguments[2], arguments[3]);
            break;
    }
}
instruction::instruction(int inst_type,std::string opcode, std::vector<uint16_t> operands) {
    type = inst_type;

    pseudo_instr.opcode = std::move(opcode);
    pseudo_instr.arg_1 = operands[0];
    pseudo_instr.arg_2 = operands[1];
    pseudo_instr.arg_3 = operands[2];
}


void instruction::form_indep_inst(uint8_t opcode){
    instr = 0;
    instr += opcode & 0xfu;
}

void instruction::form_reg_inst(uint8_t opcode, uint8_t op_a, uint8_t op_b, uint8_t dest){
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

void instruction::form_imm_inst(uint8_t opcode, uint8_t dest, uint16_t immediate) {
    instr = 0;
    instr += opcode & 0xfu;
    immediate_instr.opcode = opcode;
    instr += (dest & 0xfu) << 4u;
    immediate_instr.destination = dest;
    instr += (immediate & 0xfffu) << 8u;
    immediate_instr.immediate = immediate;
}

void instruction::form_branch_inst(uint8_t opcode, uint8_t op_a, uint8_t op_b, uint16_t offset) {
    instr = 0;
    instr += opcode & 0xfu;
    branch_instr.opcode = opcode;

    instr += (op_a & 0xfu) << 4u;
    branch_instr.op_a = op_a;

    instr += (op_b & 0xfu) << 8u;
    branch_instr.op_b = op_b;

    instr += (offset & 0xfffu) << 12u;
    branch_instr.offset = offset;
}

uint32_t instruction::emit() const {
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
        case BRANCH_INSTRUCTION:
            print_branch();
    }
}

void instruction::print_immediate() const {
    std::cout << std::setfill('0') << std::setw(4) << std::hex << instr << " -> OPCODE: " << immediate_instr.opcode <<
    " DESTINATION: " << immediate_instr.destination << " IMMEDIATE: " << immediate_instr.immediate << std::endl;
}

void instruction::print_independent() const {
    std::cout << std::setfill('0') << std::setw(4) << std::hex << instr << " -> OPCODE: " << instr << std::endl;
}

void instruction::print_register() const {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << instr << " -> OPCODE: " << register_instr.opcode <<
    " OPERAND A: " << register_instr.op_a << " OPERAND B: " << register_instr.op_b <<
    " DESTINATION: " << register_instr.dest <<std::endl;
}
void instruction::print_branch() const {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << instr << " -> OPCODE: " << branch_instr.opcode <<
        " OPERAND A: " << branch_instr.op_a << " OPERAND B: " << branch_instr.op_b <<
        " OFFSET: " << branch_instr.offset <<std::endl;
}

void instruction::specialize_pseudo() {
    std::string target_instruction = fcore_pseudo_op[pseudo_instr.opcode];
    uint16_t opcode = fcore_opcodes[target_instruction];
    switch (fcore_op_types[target_instruction]) {
        case REGISTER_INSTRUCTION:
            form_reg_inst(opcode, pseudo_instr.arg_1, pseudo_instr.arg_2, pseudo_instr.arg_3);
            type = REGISTER_INSTRUCTION;
            break;
        case IMMEDIATE_INSTRUCTION:
            form_imm_inst(opcode, pseudo_instr.arg_1, pseudo_instr.arg_3);
            type = IMMEDIATE_INSTRUCTION;
            break;
        case INDEPENDENT_INSTRUCTION:
            form_indep_inst(opcode);
            type = INDEPENDENT_INSTRUCTION;
            break;
        case BRANCH_INSTRUCTION:
            form_branch_inst(opcode, pseudo_instr.arg_1, pseudo_instr.arg_2, pseudo_instr.arg_3);
            type = BRANCH_INSTRUCTION;
            break;
        default:
            break;
    }
}



