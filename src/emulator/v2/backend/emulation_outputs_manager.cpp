

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

#include "emulator/v2/backend/emulation_outputs_manager.hpp"

namespace fcore::emulator_v2{

    void emulation_outputs_manager::process_specs(const std::shared_ptr<bus_allocator> &engine) {
        bus_engine = engine;

        for(auto &out: bus_engine->get_outputs()) {
            auto data = emulator_output(out.port_name, out.channels, out.vector_size);
            data_section[out.core_name].insert({out.port_name, data});
        }
    }


    void emulation_outputs_manager::process_outputs(
        const std::vector<core_step_metadata> &metadata
    ) {
        for(auto &[core_name, slots]:data_section){
            core_step_metadata m;
            for(auto &m_temp:metadata){
                if(core_name == m_temp.id) m = m_temp;
            }
            if(!m.running){
                // carry over previous outputs
                for(auto &out: slots){
                    out.second.repeat_last_data_point();
                }
            } else {
                for(auto &[slot_name,output]: slots){

                    auto spec = bus_engine->get_slot_source(core_name, slot_name);
                    if(spec.is_vector) {
                        std::vector<uint32_t> addresses;
                        for(int i = 0; i<spec.vector_size; i++)
                            addresses.push_back(bus_engine->get_output_address(core_name, slot_name, i));
                        process_vector_output(core_name, output, addresses, m.n_channels);
                    } else {
                        auto address = bus_engine->get_output_address(core_name, slot_name, 0);
                        process_scalar_output(core_name, output, address, m.n_channels);
                    }


                }

            }
        }


    }

    void emulation_outputs_manager::set_simulation_frequency(uint32_t freq) {
        double period = 1.0/freq;
        for(auto &core:data_section){
            for(auto &output:core.second){
                output.second.set_sampling_period(period);
            }
        }
    }

    nlohmann::json emulation_outputs_manager::get_emulation_output(const std::string& core_id) {
        nlohmann::json res;

        for(auto &[slot_name, data]: data_section[core_id]){
            auto spec = bus_engine->get_slot_source(core_id, slot_name);
            nlohmann::json output_obj;
            if(spec.type == type_uint){
                res[slot_name] = data.get_integer_data();
            } else if(spec.type == type_float){
                res[slot_name] = data.get_float_data();
            } else {
                throw std::runtime_error("unknown output type");
            }
        }

        return res;
    }

    std::vector<double> emulation_outputs_manager::get_timebase() {
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

    void emulation_outputs_manager::process_scalar_output(
            std::string core_id,
            emulator_output &out,
            uint32_t address,
            uint32_t active_channels
    ){

        for(int i = 0; i<active_channels; i++){
            auto val = runners->at(core_id).dma_read(address, i);
            out.add_data_point(val, i);
        }
    }

    void emulation_outputs_manager::process_vector_output(
            std::string core_id,
            emulator_output &out,
            std::vector<uint32_t> addresses,
            uint32_t active_channels
    ){
        for(int  j= 0; j<active_channels; j++){
            std::vector<uint32_t> data_point;

             for(int i = 0; i<addresses.size(); i++){
                auto val = runners->at(core_id).dma_read(addresses[i], j);
                data_point.push_back(val);
            }
            out.add_data_point(data_point, j);
        }
    int i = 0;
    }

    void emulation_outputs_manager::clear() {
        data_section.clear();
    }

}