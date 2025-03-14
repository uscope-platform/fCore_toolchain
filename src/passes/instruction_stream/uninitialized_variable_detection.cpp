//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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


#include "passes/instruction_stream/uninitialized_variable_detection.hpp"

#include <format>


namespace fcore {
    uninitialized_variable_detection::uninitialized_variable_detection():
    stream_pass_base("uninitialized_variable_detection",1, false, high_level_pass) {

    }



    std::optional<instruction_variant> uninitialized_variable_detection::apply_pass(
        const instruction_variant &element,
        uint32_t n
    ) {
        auto var = element.get_content();
        if(std::holds_alternative<conversion_instruction>(var)) {
             process_conversion_instruction(std::get<conversion_instruction>(var));
        } else if(std::holds_alternative<register_instruction>(var)){
             process_register_instruction(std::get<register_instruction>(var));
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            process_load_constant(std::get<load_constant_instruction>(var));
        } else if(std::holds_alternative<ternary_instruction>(var)) {
            process_ternary(std::get<ternary_instruction>(var));
        }  else {
            return element;
        }
        return element;
    }
    void uninitialized_variable_detection::process_ternary(const ternary_instruction &instr) {
        process_variable(instr.get_operand_a());
        process_variable(instr.get_operand_b());
        process_variable(instr.get_operand_c());
        initialized_variables.insert(instr.get_destination()->get_name());
    }

    void uninitialized_variable_detection::process_load_constant(const load_constant_instruction &instr) {
        initialized_variables.insert(instr.get_destination()->get_name());

    }

    void uninitialized_variable_detection::process_register_instruction(const register_instruction &instr) {

        process_variable(instr.get_operand_a());
        process_variable(instr.get_operand_b());
        initialized_variables.insert(instr.get_destination()->get_name());
    }

    void uninitialized_variable_detection::process_conversion_instruction(const conversion_instruction &instr) {
        process_variable(instr.get_source());
        initialized_variables.insert(instr.get_destination()->get_name());
    }


    void uninitialized_variable_detection::process_variable(const std::shared_ptr<variable> &var) {

        bool is_valid = initialized_variables.contains(var->get_name());
        is_valid |= var->get_variable_class().iom_spec == variable_input_type;
        is_valid |= var->get_variable_class().iom_spec == variable_memory_type;
        is_valid |= var->get_type() == var_type_float_const;
        is_valid |= var->get_type() == var_type_int_const;
        if(!is_valid) {
           // throw std::runtime_error(std::format("ERROR: Variable '{}' is used before initialization", var->get_name()));
        }
    }
}

