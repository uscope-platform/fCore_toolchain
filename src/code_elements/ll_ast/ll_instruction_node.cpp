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


#include "code_elements/ll_ast/ll_instruction_node.h"




ll_instruction_node::ll_instruction_node(int inst_type, float constant) : ll_ast_node(ll_type_instr){
    type = inst_type;
    string_instr.intercalated_constant = constant;
}

ll_instruction_node::ll_instruction_node(int inst_type, std::string opcode, std::vector<std::shared_ptr<variable>> arguments) : ll_ast_node(ll_type_instr) {
    type = inst_type;
    string_instr.opcode = std::move(opcode);
    string_instr.arguments = std::move(arguments);
}

ll_instruction_node::ll_instruction_node(int inst_type) {
    type = inst_type;
}

uint32_t ll_instruction_node::emit() const {
    uint32_t raw_instr;
    switch (type) {
        case IMMEDIATE_INSTRUCTION:
            raw_instr = emit_immediate();
            break;
        case INDEPENDENT_INSTRUCTION:
            raw_instr = emit_independent();
            break;
        case REGISTER_INSTRUCTION:
            raw_instr = emit_register();
            break;
        case BRANCH_INSTRUCTION:
            raw_instr = emit_branch();
            break;
        case CONVERSION_INSTRUCTION:
            raw_instr = emit_conversion();
            break;
        case LOAD_CONSTANT_INSTRUCTION:
            raw_instr = emit_load_const();
            break;
        case INTERCALATED_CONSTANT:
            raw_instr = emit_intercalated_const();
            break;
    }
    return raw_instr;
}

void ll_instruction_node::print() {
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
            break;
        case CONVERSION_INSTRUCTION:
            print_conversion();
            break;
        case LOAD_CONSTANT_INSTRUCTION:
            print_load_const();
            break;
    }
}

uint32_t ll_instruction_node::emit_immediate() const {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[string_instr.opcode] & opcode_mask;
    raw_instr += (string_instr.arguments[0]->get_value() & register_mask) << fcore_opcode_width;
    raw_instr += (string_instr.arguments[1]->get_value() & 0xfffu) << (fcore_opcode_width+fcore_register_address_width);
    return raw_instr;
}

uint32_t ll_instruction_node::emit_independent() const {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    raw_instr += fcore_opcodes[string_instr.opcode] & opcode_mask;
    return raw_instr;
}

uint32_t ll_instruction_node::emit_register() const {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[string_instr.opcode] & opcode_mask;
    raw_instr += (string_instr.arguments[0]->get_value() & register_mask) << fcore_opcode_width;
    raw_instr += (string_instr.arguments[1]->get_value() & register_mask) << (fcore_opcode_width+fcore_register_address_width);
    raw_instr += (string_instr.arguments[2]->get_value() & register_mask) << (fcore_opcode_width+2*fcore_register_address_width);

    return raw_instr;
}


uint32_t ll_instruction_node::emit_branch() const {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[string_instr.opcode] & opcode_mask;
    raw_instr += (string_instr.arguments[0]->get_value() & register_mask) << fcore_opcode_width;
    raw_instr += (string_instr.arguments[1]->get_value() & register_mask) << (fcore_opcode_width+fcore_register_address_width);
    raw_instr += (string_instr.arguments[2]->get_value() & register_mask) << (fcore_opcode_width+2*fcore_register_address_width);
    return raw_instr;
}

uint32_t ll_instruction_node::emit_conversion() const {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[string_instr.opcode] & opcode_mask;
    raw_instr += (string_instr.arguments[0]->get_value() & register_mask) << fcore_opcode_width;
    raw_instr += (string_instr.arguments[1]->get_value() & register_mask) << (fcore_opcode_width+fcore_register_address_width);
    return raw_instr;
}

uint32_t ll_instruction_node::emit_intercalated_const() const {
    uint32_t  raw_instr = 0;
    float constant = string_instr.intercalated_constant;
    memcpy(&raw_instr, &constant, sizeof(raw_instr));
    return raw_instr;
}

uint32_t ll_instruction_node::emit_load_const() const {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[string_instr.opcode] & opcode_mask;
    raw_instr += (string_instr.arguments[0]->get_value() & register_mask) << fcore_opcode_width;
    return raw_instr;
}

void ll_instruction_node::print_immediate() const {
    std::cout << std::setfill('0') << std::setw(4) << std::hex << emit() << " -> OPCODE: " << string_instr.opcode <<
              " DESTINATION: " << string_instr.arguments[0]->to_str() << " IMMEDIATE: " << string_instr.arguments[1]->to_str() << std::endl;
}

void ll_instruction_node::print_independent() const {
    std::cout << std::setfill('0') << std::setw(4) << std::hex << emit() << " -> OPCODE: " << string_instr.opcode << std::endl;
}

void ll_instruction_node::print_register() const {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << string_instr.opcode <<
              " OPERAND A: " << string_instr.arguments[0]->to_str() << " OPERAND B: " << string_instr.arguments[1]->to_str() <<
              " DESTINATION: " << string_instr.arguments[2]->to_str() <<std::endl;
}


void ll_instruction_node::print_branch() const {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << string_instr.opcode <<
              " OPERAND A: " << string_instr.arguments[0]->to_str() << " OPERAND B: " << string_instr.arguments[1]->to_str() <<
              " OFFSET: " << string_instr.arguments[2]->to_str() <<std::endl;
}

void ll_instruction_node::print_conversion() const {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << string_instr.opcode <<
              " SOURCE: " << string_instr.arguments[0]->to_str() << " DESTINATION: " << string_instr.arguments[1]->to_str()<<std::endl;
}

void ll_instruction_node::print_load_const() const {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << string_instr.opcode <<
              " DESTINATION: " << string_instr.arguments[0]->to_str() << " CONSTANT(NEXT INSTRUCTION): " << string_instr.arguments[1]->to_str()<<std::endl;
}

int ll_instruction_node::instruction_count() const {
    switch(type){
        case IMMEDIATE_INSTRUCTION:
        case PSEUDO_INSTRUCTION:
        case INDEPENDENT_INSTRUCTION:
        case REGISTER_INSTRUCTION:
        case CONVERSION_INSTRUCTION:
            return 1;
        case LOAD_CONSTANT_INSTRUCTION:
            return 2;
        case INTERCALATED_CONSTANT:
            return 0;
        case BRANCH_INSTRUCTION:
            return -1;
        default:
            throw std::runtime_error("instruction type not recognised");
    }
}

const instruction_t &ll_instruction_node::getStringInstr() const {
    return string_instr;
}

void ll_instruction_node::setStringInstr(const instruction_t &stringInstr) {
    string_instr = stringInstr;
}

int ll_instruction_node::get_type() {
    return type;
}

bool ll_instruction_node::is_terminal() {
    return true;
}
