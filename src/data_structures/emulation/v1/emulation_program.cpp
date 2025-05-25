

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

#include "data_structures/emulation/v1/emulation_program.hpp"



namespace fcore::emulator{

    void emulation_program::process_raw_program(std::vector<uint32_t> &raw_program) {

        for(int i = 0; i<raw_program.size(); i++){
            emulation_instruction inst;
            auto opcode = get_opcode(raw_program[i]);

            inst.instruction = raw_program[i];
            if(opcode == fcore_opcodes["ldc"]){
                inst.load_constant = raw_program[i+1];
                i++;
            }
            program.push_back(inst);
        }
    }

    emulation_instruction &emulation_program::operator[](int idx) {
        if (idx >= program.size()) {
            throw std::range_error("out of bound access");
        }
        return program[idx];
    }
}