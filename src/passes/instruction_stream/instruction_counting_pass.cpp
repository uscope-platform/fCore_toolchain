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
            stream_pass_base("io_constant_tracking", 1, false, global_pass) {
        count = c;
    }

    std::optional<instruction_variant> instruction_counting_pass::apply_pass(const instruction_variant &element, uint32_t n) {
        auto var = element.get_content();

        if(std::holds_alternative<register_instruction>(var)) {
            auto instr = std::get<register_instruction>(var);
            if (instr.get_opcode() == opcode_efi) {
                count->efi++;
            } else {
                count->regular++;
            }
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            count->load++;
        } else if(std::holds_alternative<independent_instruction>(var)){
            auto instr = std::get<independent_instruction>(var);
            if (instr.get_opcode() == opcode_stop) {
                count->stop++;
            } else {
                count->regular++;
            }
        } else if(!std::holds_alternative<intercalated_constant>(var)){
            count->regular++;
        }

        return element;
    }

}



