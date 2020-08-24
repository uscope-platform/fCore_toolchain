// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#include "fcore_has/passes/variable_lifetime_mapping.hpp"



variable_lifetime_mapping::variable_lifetime_mapping(std::shared_ptr<variable_map> var_map) {
    vmap = std::move(var_map);
    variable_detection_ctr = 0;
}

ast_t variable_lifetime_mapping::process_leaf(ast_t element) {
    for(auto &variable:element->inst.getStringInstr().arguments){
        if(!variable->is_constant() && variable->type ==TYPE_REGULAR){
            if(variable_detection_ctr <= variable->first_occurrence)
                variable->first_occurrence = variable_detection_ctr;
            if(variable_detection_ctr >= variable->last_occurrence)
                variable->last_occurrence = variable_detection_ctr;
        }
    }
    variable_detection_ctr++;
    return element;
}
