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

#include "data_structures/instruction_stream/ternary_instruction.hpp"


namespace fcore{

    ternary_instruction::ternary_instruction(opcode_table_t op, std::shared_ptr<variable> op_a,
                                                    std::shared_ptr<variable> op_b, std::shared_ptr<variable> op_c,
                                                    std::shared_ptr<variable> dest){
        operand_a = std::move(op_a);
        operand_b = std::move(op_b);
        operand_c = std::move(op_c);
        destination = std::move(dest);
        opcode = std::move(op);
    }

    std::vector<uint32_t> ternary_instruction::emit() const{
        if(*operand_a != *destination){
            throw std::runtime_error("ERROR: for ternary instructions operand a and destinations need to be equal");
        }

        uint32_t raw_instr = 0;
        uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
        uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
        raw_instr += fcore_opcodes[opcode] & opcode_mask;

        auto op_a = operand_a->get_value();
        raw_instr += (op_a.first & register_mask) << fcore_opcode_width;
        auto op_b = operand_b->get_value();
        raw_instr += (op_b.first & register_mask) << (fcore_opcode_width+fcore_register_address_width);
        auto op_c = operand_c->get_value();
        raw_instr += (op_c.first & register_mask) << (fcore_opcode_width+2*fcore_register_address_width);



        if(op_a.second){
            raw_instr += 1 <<  (fcore_opcode_width+3*fcore_register_address_width);
        }

        if(op_b.second){
            raw_instr += 1 <<  (fcore_opcode_width+3*fcore_register_address_width +1);
        }

        if(op_c.second){
            raw_instr += 1 <<  (fcore_opcode_width+3*fcore_register_address_width +2);
        }

        return {raw_instr};

    }

    std::string ternary_instruction::disassemble() const{
        return fcore_string_map[opcode] + " " + operand_a->get_name() + ", " + operand_b->get_name() +
               ", " + operand_c->get_name()  + ", " + destination->get_name();
    }

    int ternary_instruction::instruction_count() const{
        return 1;
    }

    void ternary_instruction::print() const{
        std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit()[0] << " -> " << to_string() <<std::endl;
    }

    std::string ternary_instruction::to_string() const {
        return "OPCODE: " + fcore_string_map[opcode] +  " OPERAND A: " + operand_a->to_str() + " OPERAND B: " + operand_b->to_str() +
        " OPERAND C: " + operand_c->to_str() + " DESTINATION: " + destination->to_str();
    }

    void ternary_instruction::set_arguments(const std::vector<std::shared_ptr<variable>> &a) {
        operand_a = a[0];
        operand_b = a[1];
        operand_c = a[2];
        destination = a[3];
    }
}
