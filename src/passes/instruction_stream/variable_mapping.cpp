// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#include "passes/instruction_stream/variable_mapping.hpp"

variable_mapping::variable_mapping(std::shared_ptr<variable_map> &v) : stream_pass_base("Variable mapping"){
    vmap = v;
}

std::shared_ptr<ll_instruction_node> variable_mapping::apply_pass(std::shared_ptr<ll_instruction_node> element) {

    switch (element->get_type()) {
        case isa_register_instruction:
            map_register_inst(std::static_pointer_cast<ll_register_instr_node>(element));
            break;
        case isa_conversion_instruction:
            map_conv_instr(std::static_pointer_cast<ll_conversion_instr_node>(element));
            break;
        case isa_independent_instruction:
        case isa_intercalated_constant:
            // INDEPENDENT INSTRUCTIONS AND INTERCALATED CONSTANTS DO NOT USE VARIABLES
            break;
        case isa_load_constant_instruction:
            map_load_const_instr(std::static_pointer_cast<ll_load_constant_instr_node>(element));
            break;
        default:
            throw std::runtime_error("ERROR: Invalid instruction type reached variable mapping stage");
    }


    return element;
}

void variable_mapping::map_register_inst(const std::shared_ptr<ll_register_instr_node>& instr) {
    std::string op_a = instr->get_operand_a()->to_str();
    std::string op_b = instr->get_operand_b()->to_str();
    std::string dst = instr->get_destination()->to_str();

    vmap->insert(op_a, instr->get_operand_a());
    vmap->insert(op_b, instr->get_operand_b());
    vmap->insert(dst, instr->get_destination());
}

void variable_mapping::map_conv_instr(const std::shared_ptr<ll_conversion_instr_node>& instr) {
    std::string src = instr->get_source()->to_str();
    std::string dst = instr->get_destination()->to_str();

    vmap->insert(src, instr->get_source());
    vmap->insert(dst, instr->get_destination());
}


void variable_mapping::map_load_const_instr(const std::shared_ptr<ll_load_constant_instr_node>& instr) {
    std::string dst = instr->get_destination()->to_str();
    vmap->insert(dst, instr->get_destination());

}