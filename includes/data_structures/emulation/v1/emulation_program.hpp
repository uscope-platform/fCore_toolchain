

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

#ifndef FCORE_TOOLCHAIN_EMULATION_PROGRAM_HPP
#define FCORE_TOOLCHAIN_EMULATION_PROGRAM_HPP

#include <cstdint>
#include <vector>
#include "fCore_isa.hpp"

namespace fcore{

    struct emulation_instruction{

        uint32_t instruction;
        uint32_t load_constant;
    };

    class emulation_program {
    public:
        void process_raw_program(std::vector<uint32_t> &raw_program);
        uint32_t size() {return program.size();};


        emulation_instruction & operator[](int idx);
    private:
        std::vector<emulation_instruction> program;
    };

}


#endif //FCORE_TOOLCHAIN_EMULATION_PROGRAM_HPP
