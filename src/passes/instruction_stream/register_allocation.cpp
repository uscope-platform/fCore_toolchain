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

#include "passes/instruction_stream/register_allocation.hpp"


register_allocation::register_allocation(std::shared_ptr<variable_map> vmap) : stream_pass_base("register allocation") {
var_map = std::move(vmap);
//pre_initialize the registers statuses;
used.reserve(pow(2, fcore_opcode_width));
for(int i = 0; i< pow(2, fcore_opcode_width); ++i) {
    used[i] = false;
}

//exclude form allocation pool the register that are used explicitly by the user
for(int i= 0; i<pow(2, fcore_opcode_width); i++){
    used[i] = var_map->at("r"+std::to_string(i))->is_used();
}

//exclude form allocation pool the inputs and outputs
for(auto &item: *var_map){
    unsigned int bound_reg = item.second->get_bound_reg();
    if(bound_reg>0){
        used[bound_reg] = true;
    }
}

used[0] = true;
}

std::shared_ptr<ll_instruction_node> register_allocation::apply_pass(std::shared_ptr<ll_instruction_node> element) {
    std::shared_ptr<ll_instruction_node> ret_val = element;

    auto arguments = element->get_arguments();
    for(auto &item:arguments){
        std::regex re("r(\\d\\d?)");
        std::smatch m;
        std::string s = item->to_str();
        std::regex_match(s, m, re);
        if(item->get_bound_reg() != 0){
            register_mapping[item->to_str()] = var_map->at("r"+std::to_string(item->get_bound_reg()));
            item = register_mapping[item->to_str()];
        } else{
            if(register_mapping.count(item->to_str())){
                item = register_mapping[item->to_str()];
            }else if(m.empty() && !item->is_constant()){
                bool found = false;
                for(int i = 0; i<16;i++){

                    if(!reg_map.is_used(i, item->get_first_occurrence(), item->get_last_occurrence())){
                        found = true;
                        reg_map.insert(item->to_str(), i, item->get_first_occurrence(), item->get_last_occurrence());
                        register_mapping[item->to_str()] = var_map->at("r"+std::to_string(i));
                        item = register_mapping[item->to_str()];
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
    ret_val->set_arguments(arguments);
    ret_val = element;

    return ret_val;
}

