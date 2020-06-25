//
// Created by fils on 17/06/20.
//

#include "variable_lifetime_mapping.hpp"



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
