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


#include "passes/instruction_stream/bound_register_assignment.hpp"

namespace fcore {
    bound_register_assignment::bound_register_assignment() :
    stream_pass_base("bound regiser assignment", 1, true, global_pass){
    }

    std::optional<instruction_variant>
    bound_register_assignment::apply_mutable_pass(instruction_variant& element, uint32_t n) {

        auto var = element.get_content();
        if(std::holds_alternative<register_instruction>(var)) {
            return process(std::get<register_instruction>(var));
        } else if(std::holds_alternative<conversion_instruction>(var)){
            return process(std::get<conversion_instruction>(var));
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            return process(std::get<load_constant_instruction>(var));
        } else if(std::holds_alternative<ternary_instruction>(var)){
            return process(std::get<ternary_instruction>(var));
        } else if( std::holds_alternative<intercalated_constant>(var) || std::holds_alternative<independent_instruction>(var) || std::holds_alternative<pseudo_instruction>(var)){
            return {element};
        } else {
            throw std::runtime_error("ERROR: unknown instruction type");
        }
    }

    std::optional<instruction_variant> bound_register_assignment::process(const pseudo_instruction& node){

        for (auto &a: node.get_arguments()){
            a->set_bound_reg(get_register_number(a->get_name()));
        }
        return {instruction_variant(node)};
    }

    std::optional<instruction_variant> bound_register_assignment::process(const register_instruction& node){
        for (auto &a: node.get_arguments()){
            a->set_bound_reg(get_register_number(a->get_name()));
        }
        auto dest = node.get_destination();
        dest->set_bound_reg(get_register_number(dest->get_name()));
        return {instruction_variant(node)};
    }

    std::optional<instruction_variant> bound_register_assignment::process(const conversion_instruction& node){
        for (auto &a: node.get_arguments()){
            a->set_bound_reg(get_register_number(a->get_name()));
        }
        auto dest = node.get_destination();
        dest->set_bound_reg(get_register_number(dest->get_name()));
        return {instruction_variant(node)};
    }

    std::optional<instruction_variant> bound_register_assignment::process(const load_constant_instruction& node){
        auto dest = node.get_destination();
        dest->set_bound_reg(get_register_number(dest->get_name()));
        return {instruction_variant(node)};
    }

    std::optional<instruction_variant> bound_register_assignment::process(const ternary_instruction& node){
        for (auto &a: node.get_arguments()){
            a->set_bound_reg(get_register_number(a->get_name()));
        }
        auto dest = node.get_destination();
        dest->set_bound_reg(get_register_number(dest->get_name()));
        return {instruction_variant(node)};
    }

    int bound_register_assignment::get_register_number(std::string n) {
        if (n == "constant") return -1;
        return std::stoi(n.erase(0,1));
    }
}
