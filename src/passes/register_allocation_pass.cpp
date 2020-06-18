//
// Created by fils on 13/06/20.
//

#include "register_allocation_pass.hpp"

#include <utility>

register_allocation_pass::register_allocation_pass(std::shared_ptr<variable_map> varmap) {
    var_map = std::move(varmap);
    std::string registers[16] = {"r0", "r1", "r2", "r3", "r4", "r5",  "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
    for(int i= 0; i<16; i++){
        used[i] = var_map->at(registers[i])->is_used();
    }
    used[0] = true;
}


ast_t register_allocation_pass::process_leaf(ast_t element) {
    if(element->type == type_instr){
        instruction_t current_instr = element->inst.getStringInstr();
        for(auto &item:current_instr.arguments){
            if(register_mapping.count(item)){
                item = register_mapping[item];
            }else if(!fcore_registers.count(item->to_str()) && !item->is_constant()){
                bool found = false;
                for(int i = 0; i<16;i++){

                    if(!reg_map.is_used(i, item->first_occurrence, item->last_occurrence)){
                        found = true;
                        reg_map.insert(item->to_str(), i, item->first_occurrence, item->last_occurrence);
                        register_mapping[item] = var_map->at("r"+std::to_string(i));
                        item = register_mapping[item];
                        break;
                    }
                }
                if(!found){
                    std::cout<<"ERROR: The register assignment phase run out of registers with variables still to assign."<< std::endl;
                    exit(-1);
                }
            }
        }
        element->inst.setStringInstr(current_instr);
    }
    return element;
}


