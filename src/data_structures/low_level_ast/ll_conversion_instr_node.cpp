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

#include "data_structures/low_level_ast/ll_conversion_instr_node.hpp"


ll_conversion_instr_node::ll_conversion_instr_node(std::string op, std::shared_ptr<variable> s, std::shared_ptr<variable> d) : ll_instruction_node(isa_conversion_instruction){
    source = std::move(s);
    destination = std::move(d);
    opcode = std::move(op);
}

uint32_t ll_conversion_instr_node::emit() {
    uint32_t raw_instr = 0;
    uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
    uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
    raw_instr += fcore_opcodes[opcode] & opcode_mask;
    raw_instr += (source->get_value() & register_mask) << fcore_opcode_width;
    raw_instr += (destination->get_value() & register_mask) << (fcore_opcode_width+fcore_register_address_width);
    return raw_instr;
}

void ll_conversion_instr_node::print() {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << opcode <<
              " SOURCE: " << source->to_str() << " DESTINATION: " << destination->to_str()<<std::endl;
}

int ll_conversion_instr_node::instruction_count() {
    return 1;
}

bool operator==(const ll_conversion_instr_node &lhs, const ll_conversion_instr_node &rhs) {
    bool retval = true;

    retval &= *lhs.source == *rhs.source;
    retval &= *lhs.destination == *rhs.destination;
    retval &= rhs.opcode == lhs.opcode;
    return retval;
}

void ll_conversion_instr_node::set_arguments(const std::vector<std::shared_ptr<variable>> &a) {
    source = a[0];
    destination = a[1];
}
