//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "data_structures/low_level_ast/ll_ternary_instr_node.hpp"

fcore::ll_ternary_instr_node::ll_ternary_instr_node(std::string op, std::shared_ptr<variable> op_a,
                                                    std::shared_ptr<variable> op_b, std::shared_ptr<variable> op_c,
                                                    std::shared_ptr<variable> dest) : ll_instruction_node(isa_ternary_instruction) {
    operand_a = std::move(op_a);
    operand_b = std::move(op_b);
    operand_c = std::move(op_c);
    destination = std::move(dest);
    opcode = std::move(op);
}

uint32_t fcore::ll_ternary_instr_node::emit() {
    throw std::runtime_error("ERROR: Requested emission of ternary emission not supported by the hardware");
}

std::string fcore::ll_ternary_instr_node::disassemble() {
    return opcode + " " + operand_a->get_name() + ", " + operand_b->get_name() +
    ", " + operand_c->get_name()  + ", " + destination->get_name();
}

int fcore::ll_ternary_instr_node::instruction_count() {
    return 1;
}

void fcore::ll_ternary_instr_node::print() {
    std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << opcode <<
              " OPERAND A: " << operand_a->to_str() << " OPERAND B: " << operand_b->to_str() <<
              " OPERAND C: " << operand_c->to_str() << " DESTINATION: " << destination->to_str() <<std::endl;
}

nlohmann::json fcore::ll_ternary_instr_node::dump() {
    nlohmann::json retval = ll_instruction_node::dump();
    retval["operand_a"] = operand_a->dump();
    retval["operand_b"] = operand_b->dump();
    retval["operand_c"] = operand_c->dump();
    retval["destination"] = destination->dump();
    return retval;
}

void fcore::ll_ternary_instr_node::set_arguments(const std::vector<std::shared_ptr<variable>> &a) {
    operand_a = a[0];
    operand_b = a[1];
    operand_c = a[2];
    destination = a[3];
}
