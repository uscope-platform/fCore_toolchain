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

#include "passes/instruction_stream/ternary_reduction.hpp"

namespace fcore{

    ternary_reduction::ternary_reduction() :
            stream_pass_base("Ternary reduction", 3, true, high_level_pass) {
        last_pass = 999;
    }


    std::optional<instruction_variant> ternary_reduction::apply_mutable_pass(instruction_variant &element, uint32_t n) {
        if(last_pass != n)
            instr_ctr = 0;
        else {
            instr_ctr++;
        }
        last_pass = n;
        if(n == 0){
            map_ternaries(element);
            return {};
        } else if(n == 1){
            map_conditions_source(element);
            return {};
        } else {
            return reduce(element);
        }
    }

    void ternary_reduction::map_ternaries(const instruction_variant &element) {
        if(std::holds_alternative<ternary_instruction>(element.get_content())){
            auto t = std::get<ternary_instruction>(element.get_content());
            auto t_name = t.get_operand_a()->get_name();
            ternaries_map[t_name] = instr_ctr;
            substitution_map[t_name] = t.get_destination();
        }
    }

    std::optional<instruction_variant> ternary_reduction::reduce(instruction_variant &element) {
        auto var = element.get_content();
        if(std::holds_alternative<conversion_instruction>(var)) {
            return reduce_conversion_instr(std::get<conversion_instruction>(var));
        } else if(std::holds_alternative<register_instruction>(var)){
            return reduce_register_instr(std::get<register_instruction>(var));
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            return reduce_load_instr(std::get<load_constant_instruction>(var));
        } else if(std::holds_alternative<ternary_instruction>(var)){
            return reduce_ternary_instr(std::get<ternary_instruction>(var));
        }  else {
            return element;
        }
    }

    void ternary_reduction::map_conditions_source(const instruction_variant &element) {
        auto var = element.get_content();
        if(std::holds_alternative<conversion_instruction>(var)) {
            update_conditions_map(std::get<conversion_instruction>(var).get_destination()->get_name());
        } else if(std::holds_alternative<register_instruction>(var)){
            update_conditions_map(std::get<register_instruction>(var).get_destination()->get_name());
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            update_conditions_map(std::get<load_constant_instruction>(var).get_destination()->get_name());
        } else if(std::holds_alternative<ternary_instruction>(var)){
            update_conditions_map(std::get<ternary_instruction>(var).get_destination()->get_name());
        }
    }


    std::optional<instruction_variant>
    ternary_reduction::reduce_register_instr(register_instruction &element) {
        if(conditions_map.contains(element.get_destination()->get_name())){
            if(conditions_map[element.get_destination()->get_name()] == instr_ctr){
                element.set_destination(substitution_map[element.get_destination()->get_name()]);
            }
        }
        return instruction_variant(element);
    }

    std::optional<instruction_variant>
    ternary_reduction::reduce_conversion_instr(conversion_instruction &element) {
        if(conditions_map.contains(element.get_destination()->get_name())){
            if(conditions_map[element.get_destination()->get_name()] == instr_ctr){
                element.set_destination(substitution_map[element.get_destination()->get_name()]);
            }
        }
        return instruction_variant(element);
    }

    std::optional<instruction_variant>
    ternary_reduction::reduce_load_instr(load_constant_instruction &element) {
        if(conditions_map.contains(element.get_destination()->get_name())){
            if(conditions_map[element.get_destination()->get_name()] == instr_ctr){
                element.set_destination(substitution_map[element.get_destination()->get_name()]);
            }
        }
        return instruction_variant(element);
    }

    std::optional<instruction_variant>
    ternary_reduction::reduce_ternary_instr(ternary_instruction &element) {
        if(conditions_map.contains(element.get_destination()->get_name())){
            if(conditions_map[element.get_destination()->get_name()] == instr_ctr){
                element.set_destination(substitution_map[element.get_destination()->get_name()]);
            }
        }
        element.set_operand_a(element.get_destination());
        return instruction_variant(element);
    }

    void ternary_reduction::update_conditions_map(std::string s){
        if(ternaries_map.contains(s)){
            if(ternaries_map[s]>instr_ctr){
                conditions_map[s] = instr_ctr;
            }
        }
    }


}