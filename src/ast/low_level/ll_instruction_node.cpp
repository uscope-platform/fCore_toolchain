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


#include "ast/low_level/ll_instruction_node.hpp"




ll_instruction_node::ll_instruction_node(isa_instruction_type inst_type, float constant) : ll_ast_node(ll_type_instr){
    type = inst_type;
    string_instr.intercalated_constant = constant;
}

ll_instruction_node::ll_instruction_node(isa_instruction_type inst_type, std::string opcode, std::vector<std::shared_ptr<variable>> arguments) : ll_ast_node(ll_type_instr) {
    type = inst_type;
    string_instr.opcode = std::move(opcode);
    string_instr.arguments = std::move(arguments);
}

ll_instruction_node::ll_instruction_node(isa_instruction_type inst_type) {
    type = inst_type;
}

uint32_t ll_instruction_node::emit() const {
    uint32_t raw_instr;
    switch (type) {
        case isa_immediate_instruction:
            raw_instr = emit_immediate();
            break;
        case isa_independent_instruction:
            raw_instr = emit_independent();
            break;
        case isa_register_instruction:
            raw_instr = emit_register();
            break;
        case isa_branch_instruction:
            raw_instr = emit_branch();
            break;
        case isa_conversion_instruction:
            raw_instr = emit_conversion();
            break;
        case isa_load_constant_instruction:
            raw_instr = emit_load_const();
            break;
        case isa_intercalated_constant:
            raw_instr = emit_intercalated_const();
            break;
    }
    return raw_instr;
}

void ll_instruction_node::print() {
    switch(type){
        case isa_immediate_instruction:
            print_immediate();
            break;
        case isa_independent_instruction:
            print_independent();
            break;
        case isa_register_instruction:
            print_register();
            break;
        case isa_branch_instruction:
            print_branch();
            break;
        case isa_conversion_instruction:
            print_conversion();
            break;
        case isa_intercalated_constant:
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
        case isa_immediate_instruction:
        case isa_pseudo_instruction:
        case isa_independent_instruction:
        case isa_register_instruction:
        case isa_conversion_instruction:
            return 1;
        case isa_load_constant_instruction:
            return 2;
        case isa_intercalated_constant:
            return 0;
        case isa_branch_instruction:
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

isa_instruction_type ll_instruction_node::get_type() {
    return type;
}

bool ll_instruction_node::is_terminal() {
    return true;
}

bool operator==(const ll_instruction_node &lhs, const ll_instruction_node &rhs) {
    bool retval = true;
    retval &= lhs.type == rhs.type;
    retval &= lhs.string_instr.opcode == rhs.string_instr.opcode;
    retval &= lhs.string_instr.intercalated_constant == rhs.string_instr.intercalated_constant;

    if(lhs.string_instr.arguments.empty() && rhs.string_instr.arguments.empty()){
        retval &= true;
    } else if(lhs.string_instr.arguments.empty() || rhs.string_instr.arguments.empty()){
        retval = false;
    } else {
        bool args_equal = true;
        args_equal &= lhs.string_instr.arguments.size() == rhs.string_instr.arguments.size();
        for (int i = 0; i < lhs.string_instr.arguments.size(); i++) {
            args_equal &= *lhs.string_instr.arguments[i] == *rhs.string_instr.arguments[i];
        }
        retval &= args_equal;
    }
    return retval;
}
