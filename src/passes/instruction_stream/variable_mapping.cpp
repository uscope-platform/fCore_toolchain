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
            stream_pass_base("Variable mapping", 1){
        vmap = v;
    }

    std::shared_ptr<instruction>
    variable_mapping::apply_pass(std::shared_ptr<instruction> element, uint32_t n) {

        switch (element->get_type()) {
            case isa_register_instruction:
                map_register_inst(std::static_pointer_cast<register_instruction>(element));
                break;
            case isa_conversion_instruction:
                map_conv_instr(std::static_pointer_cast<conversion_instruction>(element));
                break;
            case isa_independent_instruction:
            case isa_intercalated_constant:
                // INDEPENDENT INSTRUCTIONS AND INTERCALATED CONSTANTS DO NOT USE VARIABLES
                break;
            case isa_load_constant_instruction:
                map_load_const_instr(std::static_pointer_cast<load_constant_instruction>(element));
                break;
            case isa_ternary_instruction:
                map_ternary_instr(std::static_pointer_cast<ternary_instruction>(element));
                break;
            default:
                throw std::runtime_error("Invalid instruction type reached variable mapping stage");
        }


        return element;
    }

    void variable_mapping::map_register_inst(const std::shared_ptr<register_instruction>& instr) {
        std::string op_a = instr->get_operand_a()->get_linear_identifier();
        std::string op_b = instr->get_operand_b()->get_linear_identifier();
        std::string dst = instr->get_destination()->get_linear_identifier();

        vmap->insert(op_a, instr->get_operand_a());
        vmap->insert(op_b, instr->get_operand_b());
        vmap->insert(dst, instr->get_destination());
    }

    void variable_mapping::map_ternary_instr(const std::shared_ptr<ternary_instruction>& instr) {
        std::string op_a = instr->get_operand_a()->get_linear_identifier();
        std::string op_b = instr->get_operand_b()->get_linear_identifier();
        std::string op_c = instr->get_operand_b()->get_linear_identifier();
        std::string dst = instr->get_destination()->get_linear_identifier();

        vmap->insert(op_a, instr->get_operand_a());
        vmap->insert(op_b, instr->get_operand_b());
        vmap->insert(op_c, instr->get_operand_c());
        vmap->insert(dst, instr->get_destination());
    }

    void variable_mapping::map_conv_instr(const std::shared_ptr<conversion_instruction>& instr) {
        std::string src = instr->get_source()->get_linear_identifier();
        std::string dst = instr->get_destination()->get_linear_identifier();

        vmap->insert(src, instr->get_source());
        vmap->insert(dst, instr->get_destination());
    }


    void variable_mapping::map_load_const_instr(const std::shared_ptr<load_constant_instruction>& instr) {
        std::string dst = instr->get_destination()->get_linear_identifier();
        vmap->insert(dst, instr->get_destination());

    }

}