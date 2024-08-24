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

#include "passes/instruction_stream/instruction_counting_pass.hpp"

namespace fcore{

    instruction_counting_pass::instruction_counting_pass(std::shared_ptr<struct instruction_count> &c):
            stream_pass_base("io_constant_tracking", 1) {
        count = c;
    }


    std::shared_ptr<instruction>
    instruction_counting_pass::apply_pass(std::shared_ptr<instruction> element, uint32_t n) {
        std::shared_ptr<instruction> node = std::static_pointer_cast<instruction>(element);
        auto type = node->get_type();
        if(type==isa_load_constant_instruction){
            count->load++;
        } else if(type==isa_register_instruction) {
            auto instr = std::static_pointer_cast<register_instruction>(node);
            if (instr->get_opcode() == "efi") {
                count->efi++;
            } else {
                count->regular++;
            }
        }else if(type  == isa_independent_instruction){
            auto instr = std::static_pointer_cast<independent_instruction>(node);
            if (instr->get_opcode() == "stop") {
                count->stop++;
            } else {
                count->regular++;
            }
        } else if(type != isa_intercalated_constant) {
            count->regular++;
        }
        return element;
    }
}



