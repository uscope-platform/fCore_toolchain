

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
        const std::vector<core_step_metadata> &metadata,
        const std::string &core
    ) {
        spdlog::trace("Processing outputs for core {}", core);
        for(auto &[core_name, slots]:data_section){
            core_step_metadata m;
            if(core_name != core && core != "") continue;
            bool core_found = false;
            for(auto &m_temp:metadata){
                if(core_name == m_temp.id) {
                    m = m_temp;
                    core_found = true;
                }
            }
            if(!core_found) continue;
            if(!m.running){
                // carry over previous outputs or get initial values
                for(auto &out: slots){
                    if(out.second.is_empty()) {
                        for(int i = 0; i<m.n_channels; i++){
                            auto data_point = initial_values[core_name][out.first][i];
                            out.second.add_data_point(data_point, i);
                        }
                    } else {
                        out.second.repeat_last_data_point();
                    }

                }
            } else {
                for(auto &[slot_name,output]: slots){

                    bool stop = slot_name == "i_in";
                    auto spec = bus_engine->get_slot_source(core_name, slot_name);
                    if(spec.is_vector) {
                        std::vector<uint32_t> addresses;
                        for(int i = 0; i<spec.vector_size; i++)
                            addresses.push_back(bus_engine->get_output_address(core_name, slot_name, i));

                        auto res = process_vector_output(core_name, output, addresses, m.n_channels);
                        if(!res) throw std::runtime_error("Error while reading output: " + core_name + "." + slot_name);
                    } else {
                        auto address = bus_engine->get_output_address(core_name, slot_name, 0);
                        auto res = process_scalar_output(core_name, output, address, m.n_channels);
                        if(!res) throw std::runtime_error("Error while reading output: " + core_name + "." + slot_name);
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
            if(spec.metadata.type == type_uint){
                res[slot_name] = data.get_integer_data();
            } else if(spec.metadata.type == type_float){
                res[slot_name] = data.get_float_data();
            } else {
                throw std::runtime_error("unknown output type");
            }
        }

        return res;
    }


    bool emulation_outputs_manager::process_scalar_output(
            std::string core_id,
            emulator_output &out,
            uint32_t address,
            uint32_t active_channels
    ){

        for(int i = 0; i<active_channels; i++){
            auto read_result = runners->at(core_id).dma_read(address, i);
            if(!read_result.has_value()) return false;
            out.add_data_point(read_result.value(), i);
            spdlog::trace("Read output at io address {} for channel {}", address, i);
        }
        return true;
    }

    bool emulation_outputs_manager::process_vector_output(
            std::string core_id,
            emulator_output &out,
            std::vector<uint32_t> addresses,
            uint32_t active_channels
    ){

        for(int  j= 0; j<active_channels; j++){
            std::vector<uint32_t> data_point;

             for(int i = 0; i<addresses.size(); i++){
                auto read_result = runners->at(core_id).dma_read(addresses[i], j);
                 if(!read_result.has_value()) return false;
                spdlog::trace("Read output at io address {} for channel {}", addresses[i], j);
                data_point.push_back(read_result.value());
            }
            out.add_data_point(data_point, j);
        }
        return true;
    }

    void emulation_outputs_manager::clear() {
        data_section.clear();
    }

}