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

#include "passes/instruction_stream/variable_lifetime_mapping.hpp"

variable_lifetime_mapping::variable_lifetime_mapping(std::shared_ptr<variable_map> &v) : stream_pass_base("Variable lifetime mapping") {
    vmap = v;
    instr_cntr = 0;
}

std::shared_ptr<ll_instruction_node>
variable_lifetime_mapping::apply_pass(std::shared_ptr<ll_instruction_node> element) {
    int i = 0;
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

    ++instr_cntr;
    return element;
}

void variable_lifetime_mapping::map_register_inst(const std::shared_ptr<ll_register_instr_node> &instr) {
    std::shared_ptr<variable> op_a = vmap->at(instr->get_operand_a()->to_str());
    vmap->insert(op_a->to_str(), update_variable_lifetime(op_a));

    std::shared_ptr<variable> op_b = vmap->at(instr->get_operand_b()->to_str());
    vmap->insert(op_b->to_str(), update_variable_lifetime(op_b));

    std::shared_ptr<variable> dest = vmap->at(instr->get_destination()->to_str());
    vmap->insert(dest->to_str(), update_variable_lifetime(dest));

}

void variable_lifetime_mapping::map_conv_instr(const std::shared_ptr<ll_conversion_instr_node> &instr) {
    std::shared_ptr<variable> src = vmap->at(instr->get_source()->to_str());
    vmap->insert(src->to_str(), update_variable_lifetime(src));

    std::shared_ptr<variable> dest = vmap->at(instr->get_destination()->to_str());
    vmap->insert(dest->to_str(), update_variable_lifetime(dest));

}

void variable_lifetime_mapping::map_load_const_instr(const std::shared_ptr<ll_load_constant_instr_node> &instr) {
    std::shared_ptr<variable> dest = vmap->at(instr->get_destination()->to_str());
    vmap->insert(dest->to_str(), update_variable_lifetime(dest));
}

std::shared_ptr<variable> variable_lifetime_mapping::update_variable_lifetime(const std::shared_ptr<variable>& var) const {
   std::shared_ptr<variable> retval = var;
    if(!var->is_constant() && var->get_variable_class() == variable_regular_type){
        if(instr_cntr <= retval->get_first_occurrence())
            retval->set_first_occurrence(instr_cntr);
        if(instr_cntr >= retval->get_last_occurrence())
            retval->set_last_occurrence(instr_cntr);
    }
    return retval;
}
