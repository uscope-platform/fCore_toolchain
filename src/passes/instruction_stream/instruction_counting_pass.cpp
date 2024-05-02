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

fcore::instruction_counting_pass::instruction_counting_pass(std::shared_ptr<struct instruction_count> &c):
stream_pass_base("io_constant_tracking", 1) {
    count = c;
}


std::shared_ptr<fcore::ll_instruction_node>
fcore::instruction_counting_pass::apply_pass(std::shared_ptr<ll_instruction_node> element, uint32_t n) {
    if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);
        auto type = node->get_type();
        if(type==isa_load_constant_instruction){
            count->load++;
        } else if(type==isa_register_instruction) {
            if (node->get_opcode() == "efi") {
                count->efi++;
            } else {
                count->regular++;
            }
        }else if(type  == isa_independent_instruction){
            if (node->get_opcode() == "stop") {
                count->stop++;
            } else {
                count->regular++;
            }
        } else if(type != isa_intercalated_constant) {
            count->regular++;
        }
    }
    return element;
}



