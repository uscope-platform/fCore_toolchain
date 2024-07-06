

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


void fcore::emulation_outputs_manager::add_specs(const std::string& id, const std::vector<emulator_output_t>& specs, uint32_t active_channels) {
    for(const auto &spec:specs){
       output_specs[id][spec.name]= spec;
       auto data = emulator_output(spec.name,active_channels);
       data_section[id].insert({spec.name, data});
    }
    output_specs[id];
}

void fcore::emulation_outputs_manager::process_outputs(const std::string& core_id, const fcore::emulator_metadata &emu, bool running) {

    if(!running){
        // carry over previous outputs
        for(auto &out: data_section[core_id]){
            out.second.repeat_last_data_point();
        }
    } else {
        for(auto &out: data_section[core_id]){
            uint16_t io_address = output_specs[core_id][out.first].reg_n;
            if(!emu.io_map.contains(io_address)){
                throw std::runtime_error("Address of output \"" + output_specs[core_id][out.first].name + "\" not found.");
            }
            uint32_t core_address = emu.io_map.at(io_address);

            if(emu.active_channels==1){
                auto data_point = emu.emu->get_output(core_address, 0);
                out.second.add_data_point(data_point);
            } else {
                std::vector<uint32_t> data_point;
                for(int i = 0; i<emu.active_channels; i++){
                    data_point.push_back(emu.emu->get_output(core_address, 0));
                }
                out.second.add_data_point(data_point);
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
        if(s.second.type == type_uint32){
            res[s.second.name] = out_data.get_integer_data();
        } else if(s.second.type == type_float){

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
