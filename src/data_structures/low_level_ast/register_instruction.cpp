// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "data_structures/instruction_stream/register_instruction.hpp"


namespace fcore{

    register_instruction::register_instruction(std::string op, std::shared_ptr<variable> op_a, std::shared_ptr<variable> op_b,
                                                          std::shared_ptr<variable> dest) {
        operand_a = std::move(op_a);
        operand_b = std::move(op_b);
        destination = std::move(dest);
        opcode = std::move(op);
    }

    uint32_t register_instruction::emit()const {
        uint32_t raw_instr = 0;
        uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
        uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
        raw_instr += fcore_opcodes[opcode] & opcode_mask;
        raw_instr += (operand_a->get_value() & register_mask) << fcore_opcode_width;
        raw_instr += (operand_b->get_value() & register_mask) << (fcore_opcode_width+fcore_register_address_width);
        raw_instr += (destination->get_value() & register_mask) << (fcore_opcode_width+2*fcore_register_address_width);

        return raw_instr;
    }

    void register_instruction::print() const{
        std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> OPCODE: " << opcode <<
                  " OPERAND A: " << operand_a->to_str() << " OPERAND B: " << operand_b->to_str() <<
                  " DESTINATION: " << destination->to_str() <<std::endl;
    }

    int register_instruction::instruction_count()const {
        return 1;
    }

    void register_instruction::set_arguments(const std::vector<std::shared_ptr<variable>> &a) {
        operand_a = a[0];
        operand_b = a[1];
        destination = a[2];
    }

    std::string register_instruction::disassemble()const {
        return opcode + " " + operand_a->get_name() + ", " + operand_b->get_name() + ", " + destination->get_name();
    }

    nlohmann::json register_instruction::dump() const{
        nlohmann::json retval;
        retval["instruction_type"] = "isa_register_instruction";
        retval["operand_a"] = operand_a->dump();
        retval["operand_b"] = operand_b->dump();
        retval["destination"] = destination->dump();
        return retval;
    }


}