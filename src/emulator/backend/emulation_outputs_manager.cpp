

//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "emulator/backend/emulation_outputs_manager.hpp"


void fcore::emulation_outputs_manager::add_specs(const std::string& id, const std::vector<emulator::emulator_output_specs>& specs, uint32_t active_channels) {
    for(const auto &spec:specs){
       output_specs[id][spec.name]= spec;
       auto data = emulator_output(spec.name, spec.address.size(), active_channels);
       data_section[id].insert({spec.name, data});
    }
    output_specs[id];
}

void fcore::emulation_outputs_manager::add_interconnect_outputs(const fcore::emulator::emulator_interconnect &spec) {
    for(auto &c:spec.channels){
        auto stride = c.stride != 0 ? c.stride : 1;
        auto length = c.length != 0 ? c.length : 1;

        for(int i = 0; i< stride; i++){
            for(int j = 0; j< length; j++){
                emulator::emulator_output_specs out_spec;
                out_spec.name = c.source.io_name;
                for(auto val:c.source.address){
                    out_spec.address.push_back(val);
                }
                out_spec.data_type = emulator::type_float; // TODO: HANDLE INTEGER Types
                out_spec.type = emulator::scalar_endpoint;
                output_specs[spec.source_core_id][c.source.io_name] =  out_spec;
                auto data = emulator_output(c.source.io_name, stride, length);
                data_section[spec.source_core_id].insert({c.source.io_name, data});
            }
        }
    }
}


void fcore::emulation_outputs_manager::process_outputs(
        const std::string& core_id,
        fcore::core_memory_pool_t &pool,
        bool running,
        uint32_t active_channels,
        std::set<io_map_entry>& io_map
) {

    if(!running){
        // carry over previous outputs
        for(auto &out: data_section[core_id]){

            out.second.repeat_last_data_point();
        }
    } else {
        for(auto &out: data_section[core_id]){
            auto spec = output_specs[core_id][out.first];
            if(spec.address.size()>1){
                process_vector_output(out.second, spec, pool ,active_channels, io_map);
            } else {
                process_scalar_output(out.second, spec, pool ,active_channels, io_map);
            }
        }

    }

}

void fcore::emulation_outputs_manager::set_simulation_frequency(uint32_t freq) {
    double period = 1.0/freq;
    for(auto &core:data_section){
        for(auto &output:core.second){
            output.second.set_sampling_period(period);
        }
    }
}

nlohmann::json fcore::emulation_outputs_manager::get_emulation_output(const std::string& core_id) {
    nlohmann::json res;

    for(auto &s: output_specs[core_id]){
        auto out_data = data_section[core_id].at(s.second.name);
        nlohmann::json output_obj;
        if(s.second.data_type == emulator::type_uint){
            res[s.second.name] = out_data.get_integer_data();
        } else if(s.second.data_type == emulator::type_float){

            res[s.second.name] = out_data.get_float_data();
        }
    }

    return res;
}

std::vector<double> fcore::emulation_outputs_manager::get_timebase() {
    std::vector<double> result;
    emulator_output output;
    // TODO: this check should be done before the simulation is run, not after, and the output timebase existing or not
    // Should not depend on whether an output is present or not...
    bool found_output = false;
    for(const auto &o:data_section){
        if(!o.second.empty()){
            output = o.second.begin()->second;
            found_output = true;
            break;
        }
    }
    if(!found_output){
        throw std::runtime_error("At least one emulator has to have an output defined");
    }
    auto ts = output.get_sampling_period();
    auto size = output.get_data_length();

    for(int i = 0; i<size; i++){
        result.push_back(ts*i);
    }
    return result;
}

void fcore::emulation_outputs_manager::process_scalar_output(
        emulator_output &out,
        const fcore::emulator::emulator_output_specs &spec,
        fcore::core_memory_pool_t &pool, uint32_t active_channels,
        const std::set<io_map_entry> &io_map
){
    uint16_t io_address = spec.address[0];

    uint32_t core_address;
    if(auto a = io_map_entry::get_io_map_entry_by_io_addr(io_map, io_address)){
        core_address = a->core_addr;
    } else {
        throw std::runtime_error("unable to find input address in the core io map during output phase");
    }

    for(int i = 0; i<active_channels; i++){
        out.add_data_point(pool.at(i)->at(core_address), i);
    }
}

void fcore::emulation_outputs_manager::process_vector_output(
        emulator_output &out,
        const fcore::emulator::emulator_output_specs &spec,
        fcore::core_memory_pool_t &pool, uint32_t active_channels,
        const std::set<io_map_entry> &io_map
){
    for(int  j= 0; j<active_channels; j++){
        std::vector<uint32_t> data_point;
        for(int i = 0; i<spec.address.size(); i++){
            uint16_t io_address = spec.address[i];

            uint32_t core_address;
            if(auto a = io_map_entry::get_io_map_entry_by_io_addr(io_map, io_address)){
                core_address = a->core_addr;
            } else {
                throw std::runtime_error("unable to find input address in the core io map during output phase");
            }

            data_point.push_back(pool.at(j)->at(core_address));
        }
        out.add_data_point(data_point, j);
    }


}
