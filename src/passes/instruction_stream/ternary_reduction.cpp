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
            stream_pass_base("Ternary reduction", 3) {
        last_pass = 999;
    }

    std::shared_ptr<instruction>
    ternary_reduction::apply_pass(std::shared_ptr<instruction> element, uint32_t n) {
        if(last_pass != n)
            instr_ctr = 0;
        else {
            instr_ctr++;
        }
        last_pass = n;
        if(n == 0){
            map_ternaries(element);
            return nullptr;
        } else if(n == 1){
            map_conditions_source(element);
            return nullptr;
        } else {
            return reduce(element);
        }
    }

    void ternary_reduction::map_ternaries(std::shared_ptr<instruction> element) {
        if(element->get_type() == isa_ternary_instruction){
            auto t = std::static_pointer_cast<ternary_instruction>(element);
            auto t_name = t->get_operand_a()->get_name();
            ternaries_map[t_name] = instr_ctr;
            substitution_map[t_name] = t->get_destination();
        }
    }

    std::shared_ptr<instruction>
    ternary_reduction::reduce(std::shared_ptr<instruction> element) {


        switch (element->get_type()) {
            case isa_conversion_instruction:
                return reduce_conversion_instr(std::static_pointer_cast<conversion_instruction>(element));
            case isa_register_instruction:
                return reduce_register_instr(std::static_pointer_cast<register_instruction>(element));
            case isa_load_constant_instruction:
                return reduce_load_instr(std::static_pointer_cast<load_constant_instruction>(element));
            case isa_ternary_instruction:
                return reduce_ternary_instr(std::static_pointer_cast<ternary_instruction>(element));
            default:
                return  element;
        }

    }


    void ternary_reduction::map_conditions_source(std::shared_ptr<instruction> element) {
        auto type = element->get_type();
        if(type == isa_conversion_instruction){
            auto instr = std::static_pointer_cast<conversion_instruction>(element);
            update_conditions_map(instr->get_destination()->get_name());
        } else if(type == isa_register_instruction) {
            auto instr = std::static_pointer_cast<register_instruction>(element);
            update_conditions_map(instr->get_destination()->get_name());
        } else if(type == isa_load_constant_instruction) {
            auto instr = std::static_pointer_cast<load_constant_instruction>(element);
            update_conditions_map(instr->get_destination()->get_name());
        } else if(type == isa_ternary_instruction) {
            auto instr = std::static_pointer_cast<ternary_instruction>(element);
            update_conditions_map(instr->get_destination()->get_name());
        }
    }


    std::shared_ptr<instruction>
    ternary_reduction::reduce_register_instr(std::shared_ptr<register_instruction> node) {
        if(conditions_map.contains(node->get_destination()->get_name())){
            if(conditions_map[node->get_destination()->get_name()] == instr_ctr){
                node->set_destination(substitution_map[node->get_destination()->get_name()]);
            }
        }
        return node;
    }

    std::shared_ptr<instruction>
    ternary_reduction::reduce_conversion_instr(std::shared_ptr<conversion_instruction> node) {
        if(conditions_map.contains(node->get_destination()->get_name())){
            if(conditions_map[node->get_destination()->get_name()] == instr_ctr){
                node->set_destination(substitution_map[node->get_destination()->get_name()]);
            }
        }
        return node;
    }

    std::shared_ptr<instruction>
    ternary_reduction::reduce_load_instr(std::shared_ptr<load_constant_instruction> node) {
        if(conditions_map.contains(node->get_destination()->get_name())){
            if(conditions_map[node->get_destination()->get_name()] == instr_ctr){
                node->set_destination(substitution_map[node->get_destination()->get_name()]);
            }
        }
        return node;
    }

    std::shared_ptr<instruction>
    ternary_reduction::reduce_ternary_instr(std::shared_ptr<ternary_instruction> node) {
        if(conditions_map.contains(node->get_destination()->get_name())){
            if(conditions_map[node->get_destination()->get_name()] == instr_ctr){
                node->set_destination(substitution_map[node->get_destination()->get_name()]);
            }
        }
        node->set_operand_a(node->get_destination());
        return node;
    }

    void ternary_reduction::update_conditions_map(std::string s){
        if(ternaries_map.contains(s)){
            if(ternaries_map[s]>instr_ctr){
                conditions_map[s] = instr_ctr;
            }
        }
    }

}