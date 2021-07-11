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
#include "passes/low_level/register_allocation_pass.hpp"
#include "passes/pass_manager_base.hpp"
#include "passes/pass_base.hpp"


register_allocation_pass::register_allocation_pass(std::shared_ptr<variable_map> varmap) : pass_base<ll_ast_node>("register allocation pass"){
    var_map = std::move(varmap);
    std::string registers[16] = {"r0", "r1", "r2", "r3", "r4", "r5",  "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
    for(int i= 0; i<16; i++){
        used[i] = var_map->at(registers[i])->is_used();
    }
    used[0] = true;
}


std::shared_ptr<ll_ast_node> register_allocation_pass::process_leaf(std::shared_ptr<ll_ast_node> element) {
    std::shared_ptr<ll_ast_node> ret_val = element;
    if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);
        instruction_t current_instr = node->getStringInstr();
        for(auto &item:current_instr.arguments){
            std::regex re("r(\\d\\d?)");
            std::smatch m;
            std::string s = item->to_str();
            std::regex_match(s, m, re);
            if(item->get_bound_reg() != 0){
                register_mapping[item] = var_map->at("r"+std::to_string(item->get_bound_reg()));
                item = register_mapping[item];
            } else{
                if(register_mapping.count(item)){
                    item = register_mapping[item];
                }else if(m.empty() && !item->is_constant()){
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

        }
        node->setStringInstr(current_instr);
        ret_val = node;
    }
    return ret_val;
}


