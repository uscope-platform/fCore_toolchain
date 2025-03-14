

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

    virtual_operations_implementation::virtual_operations_implementation() :
    stream_pass_base("virtual operations implementation pass", 1,  false, global_pass) {

    }

    std::optional<instruction_variant> virtual_operations_implementation::apply_pass(const instruction_variant &element, uint32_t n) {
        auto var = element.get_content();
        if(std::holds_alternative<pseudo_instruction>(var)) {
            auto instr = std::get<pseudo_instruction>(var);
            std::string opcode = instr.get_opcode();
            auto arguments = instr.get_arguments();
            if(opcode ==  "mov"){
                arguments.push_back(arguments[1]);
                variable zero("r0");
                arguments[1] = std::make_shared<variable>(zero);
            } else if(opcode == "neg"){
                variable zero("r0");
                arguments.insert(arguments.begin(), std::make_shared<variable>(zero));
                arguments.push_back(arguments[1]);

            }

            std::string new_opcode = fcore_pseudo_op[instr.get_opcode()];
            switch (fcore_op_types[new_opcode]) {
                case isa_register_instruction:
                    return instruction_variant(register_instruction(new_opcode, arguments[0], arguments[1], arguments[2]));
                case isa_independent_instruction:
                    return instruction_variant(independent_instruction(new_opcode));
                case isa_conversion_instruction:
                    return instruction_variant(conversion_instruction(new_opcode, arguments[0], arguments[1]));
                case isa_load_constant_instruction:
                    return instruction_variant(load_constant_instruction(new_opcode, arguments[0], arguments[1]));
                default:
                    return {};
            }
        } else {
            return element;
        }

    }

}
