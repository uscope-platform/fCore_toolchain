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

#include "passes/instruction_stream/variable_lifetime_mapping.hpp"

namespace fcore{

    variable_lifetime_mapping::variable_lifetime_mapping(std::shared_ptr<variable_map> &v) :
            stream_pass_base("Variable lifetime mapping", 1, false) {
        vmap = v;
        instr_cntr = 0;
    }

    std::optional<instruction_variant> variable_lifetime_mapping::apply_pass(const instruction_variant &element, uint32_t n) {
        auto var = element.get_content();
        if(std::holds_alternative<register_instruction>(var)) {
            map_register_inst(std::get<register_instruction>(var));
        } else if(std::holds_alternative<conversion_instruction>(var)){
            map_conv_instr(std::get<conversion_instruction>(var));
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            map_load_const_instr(std::get<load_constant_instruction>(var));
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            map_ternary_instr(std::get<ternary_instruction>(var));
        }

        ++instr_cntr;
        return element;
    }

    void variable_lifetime_mapping::map_register_inst( register_instruction &instr) {
        std::shared_ptr<variable> op_a = vmap->at(instr.get_operand_a()->get_linear_identifier());
        vmap->insert(op_a->get_linear_identifier(), update_variable_lifetime(op_a));

        std::shared_ptr<variable> op_b = vmap->at(instr.get_operand_b()->get_linear_identifier());
        vmap->insert(op_b->get_linear_identifier(), update_variable_lifetime(op_b));

        std::shared_ptr<variable> dest = vmap->at(instr.get_destination()->get_linear_identifier());
        vmap->insert(dest->get_linear_identifier(), update_variable_lifetime(dest));

    }

    void variable_lifetime_mapping::map_conv_instr( conversion_instruction &instr) {
        std::shared_ptr<variable> src = vmap->at(instr.get_source()->get_linear_identifier());
        vmap->insert(src->get_linear_identifier(), update_variable_lifetime(src));

        std::shared_ptr<variable> dest = vmap->at(instr.get_destination()->get_linear_identifier());
        vmap->insert(dest->get_linear_identifier(), update_variable_lifetime(dest));

    }

    void variable_lifetime_mapping::map_load_const_instr( load_constant_instruction &instr) {
        std::shared_ptr<variable> dest = vmap->at(instr.get_destination()->get_linear_identifier());
        vmap->insert(dest->get_linear_identifier(), update_variable_lifetime(dest));
    }

    std::shared_ptr<variable> variable_lifetime_mapping::update_variable_lifetime(const std::shared_ptr<variable>& var) const {
        std::shared_ptr<variable> retval = var;
        if(!var->is_constant()){
            if(var->get_variable_class()==variable_input_type){
                retval->set_first_occurrence(0);
            } else{
                if(instr_cntr <= retval->get_first_occurrence())
                    retval->set_first_occurrence(instr_cntr);
            }

            if(instr_cntr >= retval->get_last_occurrence())
                retval->set_last_occurrence(instr_cntr);
        }
        return retval;
    }

    void variable_lifetime_mapping::map_ternary_instr( ternary_instruction &instr) {
        std::shared_ptr<variable> op_a = vmap->at(instr.get_operand_a()->get_linear_identifier());
        vmap->insert(op_a->get_linear_identifier(), update_variable_lifetime(op_a));

        std::shared_ptr<variable> op_b = vmap->at(instr.get_operand_b()->get_linear_identifier());
        vmap->insert(op_b->get_linear_identifier(), update_variable_lifetime(op_b));

        std::shared_ptr<variable> op_c = vmap->at(instr.get_operand_c()->get_linear_identifier());
        vmap->insert(op_c->get_linear_identifier(), update_variable_lifetime(op_b));

        std::shared_ptr<variable> dest = vmap->at(instr.get_destination()->get_linear_identifier());
        vmap->insert(dest->get_linear_identifier(), update_variable_lifetime(dest));
    }


}
