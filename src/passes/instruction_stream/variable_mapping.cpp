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

#include "passes/instruction_stream/variable_mapping.hpp"
namespace fcore{
    variable_mapping::variable_mapping(std::shared_ptr<variable_map> &v) :
            stream_pass_base("Variable mapping", 1,  false){
        vmap = v;
    }

    std::optional<instruction_variant> variable_mapping::apply_pass(const instruction_variant &element, uint32_t n) {

        auto var = element.get_content();
        if(std::holds_alternative<register_instruction>(var)) {
            auto instr = std::get<register_instruction>(var);
            map_register_inst(instr);
        } else if(std::holds_alternative<conversion_instruction>(var)){
            auto instr = std::get<conversion_instruction>(var);
            map_conv_instr(instr);
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            auto instr = std::get<load_constant_instruction>(var);
            map_load_const_instr(instr);
        } else if(std::holds_alternative<ternary_instruction>(var)){
            auto instr = std::get<ternary_instruction>(var);
            map_ternary_instr(instr);
        } else if(std::holds_alternative<independent_instruction>(var) || std::holds_alternative<intercalated_constant>(var) ) {
            // INDEPENDENT INSTRUCTIONS AND INTERCALATED CONSTANTS DO NOT USE VARIABLES
        } else {
            throw std::runtime_error("Invalid instruction type reached variable mapping stage");
        }
        return element;
    }


    void variable_mapping::map_register_inst(const register_instruction& instr) {
        std::string op_a = instr.get_operand_a()->get_linear_identifier();
        std::string op_b = instr.get_operand_b()->get_linear_identifier();
        std::string dst = instr.get_destination()->get_linear_identifier();

        vmap->insert(op_a, instr.get_operand_a());
        vmap->insert(op_b, instr.get_operand_b());
        vmap->insert(dst, instr.get_destination());
    }

    void variable_mapping::map_ternary_instr(const ternary_instruction& instr) {
        std::string op_a = instr.get_operand_a()->get_linear_identifier();
        std::string op_b = instr.get_operand_b()->get_linear_identifier();
        std::string op_c = instr.get_operand_b()->get_linear_identifier();
        std::string dst = instr.get_destination()->get_linear_identifier();

        vmap->insert(op_a, instr.get_operand_a());
        vmap->insert(op_b, instr.get_operand_b());
        vmap->insert(op_c, instr.get_operand_c());
        vmap->insert(dst, instr.get_destination());
    }

    void variable_mapping::map_conv_instr(const conversion_instruction& instr) {
        std::string src = instr.get_source()->get_linear_identifier();
        std::string dst = instr.get_destination()->get_linear_identifier();

        vmap->insert(src, instr.get_source());
        vmap->insert(dst, instr.get_destination());
    }


    void variable_mapping::map_load_const_instr(const load_constant_instruction& instr) {
        std::string dst = instr.get_destination()->get_linear_identifier();
        vmap->insert(dst, instr.get_destination());

    }

}