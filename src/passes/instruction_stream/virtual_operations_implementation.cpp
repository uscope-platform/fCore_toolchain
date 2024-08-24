

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

#include "passes/instruction_stream/virtual_operations_implementation.hpp"


namespace fcore{

    virtual_operations_implementation::virtual_operations_implementation() : stream_pass_base("virtual operations implementation pass", 1) {

    }

    std::shared_ptr<instruction>virtual_operations_implementation::apply_pass(std::shared_ptr<instruction> element, uint32_t n) {

        std::shared_ptr<instruction> ret_val = element;
        std::shared_ptr<instruction> node = std::static_pointer_cast<instruction>(element);
        if (node->is_pseudo()){
            std::shared_ptr<pseudo_instruction> pseudo_instr = std::static_pointer_cast<pseudo_instruction>(node);
            std::string opcode = pseudo_instr->get_opcode();
            auto arguments = pseudo_instr->get_arguments();
            if(opcode ==  "mov"){
                arguments.push_back(arguments[1]);
                variable zero("r0");
                arguments[1] = std::make_shared<variable>(zero);
            } else if(opcode == "neg"){
                variable zero("r0");
                arguments.insert(arguments.begin(), std::make_shared<variable>(zero));
                arguments.push_back(arguments[1]);

            }

            std::string new_opcode = fcore_pseudo_op[pseudo_instr->get_opcode()];
            switch (fcore_op_types[new_opcode]) {
                case isa_register_instruction:
                    ret_val = std::make_shared<register_instruction>(new_opcode, arguments[0], arguments[1], arguments[2]);
                    break;
                case isa_independent_instruction:
                    ret_val = std::make_shared<independent_instruction>(new_opcode);
                    break;
                case isa_conversion_instruction:
                    ret_val = std::make_shared<conversion_instruction>(new_opcode, arguments[0], arguments[1]);
                    break;
                case isa_load_constant_instruction:
                    ret_val = std::make_shared<load_constant_instruction>(new_opcode, arguments[0], arguments[1]);
                    break;
                default:
                    break;
            }
        }
        return ret_val;



    }

}
