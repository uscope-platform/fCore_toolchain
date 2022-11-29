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

#include "passes/instruction_stream/register_allocation.hpp"


register_allocation::register_allocation(
        std::shared_ptr<variable_map> vmap,
        std::unordered_map<std::string, std::shared_ptr<variable>> &iom,
        std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &ebm
        ) : stream_pass_base("register allocation") {

    early_bindings_map = ebm;
    var_map = std::move(vmap);
    iom_map = iom;
    //pre_initialize the registers statuses;
    excluded.reserve(pow(2, fcore_register_address_width));
    for(int i = 0; i< pow(2, fcore_register_address_width); ++i) {
        excluded.push_back(false);
    }

    //exclude form allocation pool the register that are used explicitly by the user
    for(int i= 0; i<pow(2, fcore_register_address_width); i++){
        excluded[i] = var_map->at("r"+std::to_string(i))->is_used();
    }

    for( auto&item:iom_map){
        if(item.second->get_variable_class() == variable_memory_type || item.second->get_variable_class() == variable_output_type || item.second->get_variable_class() == variable_input_type){
            for(auto &idx:item.second->get_bound_reg_array()){
                excluded[idx] = true;
            }
        }
    }

    //exclude form allocation pool the inputs and outputs
    for(auto &item: *var_map){
        int bound_reg = item.second->get_bound_reg();
        if(bound_reg>0){
            excluded[bound_reg] = true;
        }
    }

    for(auto &item :*early_bindings_map){
        auto mem_range = item.second;
        for(int i = 0; i<mem_range.second-mem_range.first; i++){
            excluded[mem_range.first+i] = true;
        }
    }

    excluded[0] = true;
}




std::shared_ptr<ll_instruction_node> register_allocation::apply_pass(std::shared_ptr<ll_instruction_node> element) {
    std::shared_ptr<ll_instruction_node> ret_val = element;


    auto arguments = element->get_arguments();
    for(auto &item:arguments){
        std::regex re("r(\\d\\d?)");
        std::smatch m;
        std::string s = item->to_str();
        std::regex_match(s, m, re);
        s = item->get_identifier();
        if(item->get_bound_reg() != -1){
            if(item->get_type() == var_type_array){
                auto arr_idx = item->get_bound_reg_array()[item->get_linear_index()];
                register_mapping[s] = var_map->at("r"+std::to_string(arr_idx));
            } else {
                register_mapping[s] = var_map->at("r"+std::to_string(item->get_bound_reg()));
            }

            item = register_mapping[s];
        } else{
            if(register_mapping.count(s)){
                item = register_mapping[s];
            }else if(m.empty() && !item->is_constant()){
                bool found = false;
                for(int i = 0; i<pow(2, fcore_register_address_width);i++){

                    if(!reg_map.is_used(i, item->get_first_occurrence(), item->get_last_occurrence()) & !excluded[i]){
                        found = true;
                        reg_map.insert(s, i, item->get_first_occurrence(), item->get_last_occurrence());
                        register_mapping[s] = var_map->at("r"+std::to_string(i));
                        item = register_mapping[s];
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

