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
        std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &ebm,
        const std::shared_ptr<std::unordered_map<std::string, std::vector<std::pair<int,int>>>>& all_map
        ) : stream_pass_base("register allocation") {

    early_bindings_map = ebm;
    allocation_map = all_map;
    var_map = std::move(vmap);

    int n_regs = 2<<(fcore_register_address_width-1);
    //pre_initialize the registers statuses, excluding form allocation pool the registers explicitly by the user
    excluded.reserve(n_regs);
    for(int i = 0; i< n_regs; ++i) {
        excluded.push_back(var_map->at("r"+std::to_string(i))->is_used());
    }

    for(auto &item :*early_bindings_map){
        auto mem_range = item.second;
        for(int i = 0; i<mem_range.second-mem_range.first; i++){
            excluded[mem_range.first+i] = true;
        }
    }

    excluded[0] = true;
}

void register_allocation::setup() {
    int memory_idx = 0;
    int n_regs = 2<<(fcore_register_address_width-1);

    for(auto &item:*var_map){
        if(item.second->get_variable_class() == variable_memory_type){
            if(!excluded[n_regs-1-memory_idx])
                memory_vars[item.first] = n_regs-memory_idx-1;
            memory_idx++;
        }
    }
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
            register_mapping[s] = var_map->at("r"+std::to_string(item->get_bound_reg()));
            item = register_mapping[s];
        } else if (memory_vars.contains(item->get_name())) {
            allocate_register(item, memory_vars[item->get_name()]);
            item = register_mapping[s];
        } else{
            if(register_mapping.count(s)){
                item = register_mapping[s];
            }else if(m.empty() && !item->is_constant()){
                bool found = false;
                for(int i = 0; i<pow(2, fcore_register_address_width);i++){

                    if(!reg_map.is_used(i, item->get_first_occurrence(), item->get_last_occurrence()) & !excluded[i]){
                        found = true;
                        allocate_register(item, i);
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

void register_allocation::allocate_register(std::shared_ptr<variable> &var, int reg_addr) {
    reg_map.insert(var->get_identifier(), reg_addr, var->get_first_occurrence(), var->get_last_occurrence());
    register_mapping[var->get_identifier()] = var_map->at("r"+std::to_string(reg_addr));
    int array_index = -1;
    auto var_name = demangle_array(var->get_identifier(), array_index);
    if(allocation_map->contains(var_name)){
        allocation_map->at(var_name).push_back({reg_addr, array_index});
    } else {
        auto item = std::vector<std::pair<int, int>>();
        item.emplace_back(reg_addr, array_index);
        allocation_map->emplace(var_name, item);
    }
    if(var->get_variable_class() == variable_output_type){
        excluded[reg_addr] = true;
    }
}

std::string register_allocation::demangle_array(const std::string &s, int &index) {
    std::string array_prefix = "_fcmglr_flattened_array_";
    std::string arr_name;
    if(s.starts_with(array_prefix)){
        arr_name = s.substr(array_prefix.size());
        auto suffix_start = arr_name.find_last_of('_');
        index = std::stoi(arr_name.substr(suffix_start+1));
        return arr_name.substr(0, suffix_start);
    }else{
        return s;
    }

}

