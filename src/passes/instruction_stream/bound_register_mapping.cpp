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
// limitations under the License.02/07/2021.
//

#include "passes/instruction_stream/bound_register_mapping.hpp"

namespace fcore{

    bound_register_mapping_pass::bound_register_mapping_pass() : stream_pass_base("Bound register mapping" , 1, false, high_level_pass){

    }

    std::optional<instruction_variant> bound_register_mapping_pass::apply_pass(const instruction_variant &element, uint32_t n) {

        auto var = element.get_content();
        if(std::holds_alternative<register_instruction>(var)) {
            return process_reg_instr(std::get<register_instruction>(var));
        } else if(std::holds_alternative<conversion_instruction>(var)){
            return process_conv_instr(std::get<conversion_instruction>(var));
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            return process_load_instr(std::get<load_constant_instruction>(var));
        } else if(std::holds_alternative<ternary_instruction>(var)){
            return process_ternary_instr(std::get<ternary_instruction>(var));
        } else if(  std::holds_alternative<independent_instruction>(var) || std::holds_alternative<pseudo_instruction>(var)){
            return element;
        } else {
            throw std::runtime_error("ERROR: unknown instruction type");
        }

    }

    std::optional<instruction_variant>
    bound_register_mapping_pass::process_reg_instr(const register_instruction &element) {

        std::string raw_dest = element.get_destination()->get_name();
        int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
        element.get_destination()->set_bound_reg(dest);

        std::string raw_op_a = element.get_operand_a()->get_name();
        int op_a = std::stoi(raw_op_a.substr(1, raw_op_a.size()-1));
        element.get_operand_a()->set_bound_reg(op_a);

        std::string raw_op_b = element.get_operand_b()->get_name();
        int op_b = std::stoi(raw_op_b.substr(1, raw_op_b.size()-1));
        element.get_operand_b()->set_bound_reg(op_b);

        return instruction_variant(element);
    }

    std::optional<instruction_variant>
    bound_register_mapping_pass::process_conv_instr(const conversion_instruction &element) {
        std::string raw_dest = element.get_destination()->get_name();
        int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
        element.get_destination()->set_bound_reg(dest);

        std::string raw_src = element.get_source()->get_name();
        int src = std::stoi(raw_src.substr(1, raw_src.size()-1));
        element.get_source()->set_bound_reg(src);

        return instruction_variant(element);
    }

    std::optional<instruction_variant>
    bound_register_mapping_pass::process_load_instr(const load_constant_instruction &element) {

        std::string raw_dest = element.get_destination()->get_name();
        int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
        element.get_destination()->set_bound_reg(dest);

        return instruction_variant(element);
    }

    std::optional<instruction_variant>
    bound_register_mapping_pass::process_ternary_instr(const ternary_instruction& element) {

        std::string raw_dest = element.get_destination()->get_name();
        int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
        element.get_destination()->set_bound_reg(dest);

        std::string raw_op_a = element.get_operand_a()->get_name();
        int op_a = std::stoi(raw_op_a.substr(1, raw_op_a.size()-1));
        element.get_operand_a()->set_bound_reg(op_a);

        std::string raw_op_b = element.get_operand_b()->get_name();
        int op_b = std::stoi(raw_op_b.substr(1, raw_op_b.size()-1));
        element.get_operand_b()->set_bound_reg(op_b);


        std::string raw_op_c = element.get_operand_c()->get_name();
        int op_c = std::stoi(raw_op_c.substr(1, raw_op_c.size()-1));
        element.get_operand_c()->set_bound_reg(op_c);

        return instruction_variant(element);
    }
}

