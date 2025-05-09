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

#include "data_structures/instruction_stream/conversion_instruction.hpp"

namespace fcore{
    conversion_instruction::conversion_instruction(std::string op, std::shared_ptr<variable> s, std::shared_ptr<variable> d) {
        source = std::move(s);
        destination = std::move(d);
        opcode = std::move(op);
    }

    uint32_t conversion_instruction::emit() const {
        uint32_t raw_instr = 0;
        uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
        uint32_t register_mask = std::pow(2, fcore_register_address_width)-1;
        raw_instr += fcore_opcodes[opcode] & opcode_mask;
        auto src = source->get_value();
        raw_instr += (src.first & register_mask) << fcore_opcode_width;
        raw_instr += (destination->get_value().first & register_mask) << (fcore_opcode_width+fcore_register_address_width);

        if(src.second){
            raw_instr += 1 <<  (fcore_opcode_width+2*fcore_register_address_width);
        }

        return raw_instr;
    }

    void conversion_instruction::print() const {
        std::cout << std::setfill('0') << std::setw(4) <<  std::hex << emit() << " -> " << to_string() <<std::endl;
    }

    std::string conversion_instruction::to_string() const {
        return "OPCODE: " + opcode + " SOURCE: " + source->to_str() + " DESTINATION: " + destination->to_str();
    }

    int conversion_instruction::instruction_count() const{
        return 1;
    }

    void conversion_instruction::set_arguments(const std::vector<std::shared_ptr<variable>> &a) {
        source = a[0];
        destination = a[1];
    }

    std::string conversion_instruction::disassemble() const {
        return opcode + " " + source->get_name() + ", " + destination->get_name();
    }

}


