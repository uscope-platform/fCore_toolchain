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

#include "passes/low_level/variable_lifetime_mapping.hpp"
#include "passes/pass_base.hpp"


variable_lifetime_mapping::variable_lifetime_mapping(std::shared_ptr<variable_map> var_map) : pass_base<ll_ast_node>("variable lifetime mapping pass"){
    vmap = std::move(var_map);
    variable_detection_ctr = 0;
}

std::shared_ptr<ll_ast_node> variable_lifetime_mapping::process_leaf(std::shared_ptr<ll_ast_node> element) {

   /* if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);
        for(auto &variable:node->get_arguments()){
            if(!variable->is_constant() && variable->type ==TYPE_REGULAR){
                if(variable_detection_ctr <= variable->first_occurrence)
                    variable->first_occurrence = variable_detection_ctr;
                if(variable_detection_ctr >= variable->last_occurrence)
                    variable->last_occurrence = variable_detection_ctr;
            }
        }
        variable_detection_ctr++;
    }*/

    return element;
}
