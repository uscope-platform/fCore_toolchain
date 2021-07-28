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

#include "data_structures/low_level_ast/ll_load_constant_instr_node.hpp"



ll_load_constant_instr_node::ll_load_constant_instr_node(std::string op, std::shared_ptr<variable> dest, std::shared_ptr<variable> c)
: ll_instruction_node(isa_load_constant_instruction){
    destination = std::move(dest);
    constant = std::move(c);
    opcode = std::move(op);
}

uint32_t ll_load_constant_instr_node::emit() {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[opcode] & opcode_mask;
    raw_instr += (destination->get_value() & register_mask) << fcore_opcode_width;
    return raw_instr;
}

void ll_load_constant_instr_node::print() {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << opcode <<
              " DESTINATION: " << destination->to_str() << " CONSTANT(NEXT INSTRUCTION): " << constant->to_str()<<std::endl;
}

int ll_load_constant_instr_node::instruction_count() {
    return 1;
}

bool operator==(const ll_load_constant_instr_node &lhs, const ll_load_constant_instr_node &rhs) {
    bool retval = true;

    retval &= *lhs.constant == *rhs.constant;
    retval &= *lhs.destination == *rhs.destination;
    retval &= rhs.opcode == lhs.opcode;
    return retval;
}

float ll_load_constant_instr_node::get_constant() {
    return std::stof(constant->to_str());
}

void ll_load_constant_instr_node::set_arguments(const std::vector<std::shared_ptr<variable>> &a) {
    destination = a[0];
    constant = a[1];
}
