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

namespace fcore{


    template<class... Ts>
    struct overloads : Ts... { using Ts::operator()...; };

    register_allocation::register_allocation(
            std::shared_ptr<variable_map> vmap,
            std::shared_ptr<std::map<std::string, memory_range_t>> &ebm,
            const std::shared_ptr<std::map<std::string, std::vector<io_map_entry>>>& all_map
    ) : stream_pass_base("register allocation", 1, true, global_pass) {

        allocation_map = all_map;
        var_map = std::move(vmap);

        int n_regs = 2<<(fcore_register_address_width-1);
        //pre_initialize the registers statuses, excluding form allocation pool the registers explicitly by the user
        excluded.reserve(n_regs);
        for(int i = 0; i< n_regs; ++i) {
            excluded.push_back(var_map->at("r"+std::to_string(i))->is_used());
        }


        excluded[0] = true;
    }

    void register_allocation::setup() {
        int memory_idx = 0;
        int inputs_idx = 1;

        int n_regs = 2 << (fcore_register_address_width - 1);

        for(auto &item: *var_map) {
            auto vc = item.second->get_variable_class();
            if (vc.iom_spec == variable_memory_type) {
                if (!excluded[n_regs - 1 - memory_idx]) {
                    memory_vars[item.first] = n_regs - memory_idx - 1;
                    excluded[n_regs - memory_idx - 1] = true;
                }
                memory_idx++;
            } else if (vc.iom_spec == variable_input_type) {
                if(!vc.common_io){
                    if(!allocation_map->contains(item.first)){
                        if((item.second->get_type() == var_type_array) && item.second->is_contiguous()){
                            allocate_array(item.second, inputs_idx);
                            inputs_idx += item.second->get_size();
                        } else {
                            allocate_register(item.second, inputs_idx);
                            inputs_idx++;
                        }
                    }
                }
            }
        }
    }


    std::optional<instruction_variant> register_allocation::apply_mutable_pass(instruction_variant &element, uint32_t n) {

        auto arguments = element.get_arguments();

        for(auto &item:arguments){

            std::string var_name = item->to_str();

            auto bound_reg = item->get_bound_reg();


            if(bound_reg != -1){
                reg_map.add_bound_identifier(item, bound_reg);
                item = reg_map.get_identifier(item);
            } else if (memory_vars.contains(item->get_linear_identifier())) {
                allocate_register(item, memory_vars[item->get_linear_identifier()]);
                item = reg_map.get_identifier(item);
            } else{
                if(reg_map.is_allocated(item)){
                    item = reg_map.get_identifier(item);
                }else if(!variable::is_explicit_register(var_name) && !item->is_constant()){
                    bool found = false;
                    for(int i = 0; i<pow(2, fcore_register_address_width);i++){
                        if(!item->get_array_shape().empty() && item->is_contiguous()){
                            if(!reg_map.is_used({i,item->get_size()}, item) & !excluded[i]){
                                found = true;
                                allocate_array(item, i);
                                item = reg_map.get_identifier(item);
                                break;
                            }
                        } else{
                            if(!reg_map.is_used(i, item) & !excluded[i]){
                                found = true;
                                allocate_register(item, i);
                                item = reg_map.get_identifier(item);
                                break;
                            }
                        }
                    }
                    if(!found){
                        std::cout<<"ERROR: The register assignment phase run out of registers with variables still to assign."<< std::endl;
                        exit(-1);
                    }
                }
            }
        }

        auto instr = element.get_content();

        return std::visit(overloads{
            overloads{[&arguments](register_instruction &i){ i.set_arguments(arguments); return instruction_variant(i);}},
            overloads{[&arguments](conversion_instruction &i){ i.set_arguments(arguments); return instruction_variant(i);}},
            overloads{[&arguments](independent_instruction &i){ i.set_arguments(arguments); return instruction_variant(i);}},
            overloads{[&arguments](pseudo_instruction &i){ i.set_arguments(arguments); return instruction_variant(i);}},
            overloads{[&arguments](ternary_instruction &i){ i.set_arguments(arguments); return instruction_variant(i);}},
            overloads{[&arguments](load_constant_instruction &i){ i.set_arguments(arguments); return instruction_variant(i);}}
        }, instr);

    }



    void register_allocation::allocate_register(std::shared_ptr<variable> &var, int reg_addr) {
        if(var->get_variable_class().common_io){
            reg_map.insert_common_io(var, reg_addr);
            auto item = std::vector<io_map_entry>();
            item.emplace_back( var->get_linear_index(), reg_addr, get_variable_type(var));
            item[0].common_io = true;
            item[0].io_name = var->get_linear_identifier();
            allocation_map->emplace(var->get_linear_identifier(), item);

        } else {
            reg_map.insert(var, reg_addr);
            auto lin_identifier = var->get_linear_identifier();
            std::string var_type =get_variable_type(var);
            if(allocation_map->contains(lin_identifier)){
                allocation_map->at(lin_identifier).emplace_back(var->get_linear_index(),reg_addr, var_type);
                allocation_map->at(lin_identifier).back().io_name = lin_identifier;
            } else {
                auto item = std::vector<io_map_entry>();
                item.emplace_back( var->get_linear_index(), reg_addr, var_type);
                item.back().io_name = lin_identifier;
                allocation_map->emplace(lin_identifier, item);
            }
            if(var->get_variable_class().iom_spec == variable_output_type){
                excluded[reg_addr] = true;
            }
        }
    }

    void register_allocation::allocate_array(std::shared_ptr<variable> &var, int reg_addr) {
        if(var->get_variable_class().common_io){
            // TODO: ALLOCATE REGISTER IN SCALAR IO SPACE
            throw std::runtime_error("Feature not yet implemented");

        } else {
            std::pair<int, int> reg_pair = {reg_addr, var->get_size()};
            reg_map.insert(var, reg_pair);
            allocated_contiguous_arrays[var->get_name()] = {reg_addr, reg_addr+var->get_size()-1};
            std::string var_type =get_variable_type(var);

            for(int i=0; i<var->get_size(); i++){

                auto lin_identifier = var->get_linear_identifier(i);

                if(allocation_map->contains(lin_identifier)){
                    allocation_map->at(lin_identifier).emplace_back( i,reg_addr+i, var_type);
                    allocation_map->at(lin_identifier).back().io_name = lin_identifier;
                } else {
                    auto item = std::vector<io_map_entry>();
                    item.emplace_back(i,reg_addr+i,  var_type);
                    item.back().io_name = lin_identifier;
                    allocation_map->emplace(lin_identifier, item);

                }

            }
            for(int i=0; i<var->get_size(); i++){
                if(var->get_variable_class().iom_spec == variable_output_type){
                    excluded[reg_addr+i] = true;
                }
            }
        }
    }

    std::string register_allocation::get_variable_type(std::shared_ptr<variable> &var) {
        std::string var_type;
        if(var->get_variable_class().iom_spec == variable_input_type){
            var_type = "i";
        } else if(var->get_variable_class().iom_spec == variable_output_type){
            var_type = "o";
        }else if(var->get_variable_class().iom_spec == variable_memory_type ){
            var_type = "m";
        } else{
            var_type = "g";
        }
        return var_type;
    }

}

