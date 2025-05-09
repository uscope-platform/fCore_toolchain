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

#include "data_structures/instruction_stream/load_constant_instruction.hpp"


namespace fcore {

    load_constant_instruction::load_constant_instruction(std::string op, std::shared_ptr<variable> dest, std::shared_ptr<variable> c){
        destination = std::move(dest);
        constant = std::move(c);
        opcode = std::move(op);
    }

    uint32_t load_constant_instruction::emit() const{
        uint32_t raw_instr = 0;
        uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
        uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
        raw_instr += fcore_opcodes[opcode] & opcode_mask;
        raw_instr += (destination->get_value().first & register_mask) << fcore_opcode_width;
        return raw_instr;
    }

    void load_constant_instruction::print() const {
        std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> " <<  to_string() <<std::endl;
    }

    std::string load_constant_instruction::to_string() const {
        return "OPCODE: " + opcode + " DESTINATION: " + destination->to_str() + " CONSTANT(NEXT INSTRUCTION): " + constant->to_str();
    }

    int load_constant_instruction::instruction_count() const {
        return 1;
    }


    float load_constant_instruction::get_constant_f() {
        return constant->get_float_val();
    }

    void load_constant_instruction::set_arguments(const std::vector<std::shared_ptr<variable>> &a) {
        destination = a[0];
        constant = a[1];
    }

    int load_constant_instruction::get_constant_i() {
        return constant->get_int_value();
    }

    std::string load_constant_instruction::disassemble() const{
        return opcode + " " + destination->get_name() + ", ";
    }

    bool load_constant_instruction::is_float() {
        return constant->is_float();
    }

}