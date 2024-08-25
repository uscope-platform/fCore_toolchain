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

#include "data_structures/instruction_stream/independent_instruction.hpp"


namespace fcore{

    independent_instruction::independent_instruction(std::string op) {
        opcode = std::move(op);
    }


    uint32_t independent_instruction::emit()const {
        uint32_t raw_instr = 0;
        uint32_t opcode_mask = std::pow(2, fcore_opcode_width)-1;
        raw_instr += fcore_opcodes[opcode] & opcode_mask;
        return raw_instr;
    }

    void independent_instruction::print() const {
        std::cout << std::setfill('0') << std::setw(4) << std::hex << emit() << " -> OPCODE: " << opcode << std::endl;
    }

    int  independent_instruction::instruction_count() const{
        return 1;
    }

    std::string independent_instruction::disassemble() const {
        return opcode;
    }

    nlohmann::json  independent_instruction::dump() const{
        nlohmann::json retval;
        retval["instruction_type"] = "isa_independent_instruction";
        return retval;
    }
}