

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

namespace fcore{

    void emulation_outputs_manager::add_specs(const std::string& id, const std::vector<emulator::emulator_output_specs>& specs, uint32_t active_channels) {
        for(const auto &spec:specs){
            output_specs[id][spec.name]= spec;
            auto data = emulator_output(spec, active_channels);
            data_section[id].insert({spec.name, data});
        }
        output_specs[id];
    }

    void emulation_outputs_manager::add_interconnect_outputs(const emulator::emulator_interconnect &spec,const std::vector<emulator::emulator_core> &cores) {
        for(auto &c:spec.channels){
            auto stride = c.stride != 0 ? c.stride : 1;
            auto length = c.length != 0 ? c.length : 1;

            emulator::emulator_output_specs out_spec;
            out_spec.name = c.source.io_name;

            if(c.type == emulator::dma_link_scalar || c.type == emulator::dma_link_gather || c.type == emulator::dma_link_vector){

                out_spec.address.push_back(c.source.address[0]);

            } else {
                for(int i = 0; i< stride; i++){
                    out_spec.address.push_back(c.source.address[0] + i);
                }
            }

            for(auto &ch:cores){
                if(ch.id == spec.source_core_id){
                    for(auto &o:ch.outputs){
                        if(c.source.io_name == o.name){
                            out_spec.output_type = o.output_type;
                        }
                    }
                }
            }
            // TODO: ALLOW USER TO CHOSE THIS
            out_spec.output_type = emulator::type_float;
            out_spec.metadata.type = emulator::type_float;
            out_spec.metadata.width = 32;
            out_spec.metadata.is_signed = true;

            output_specs[spec.source_core_id][c.source.io_name] =  out_spec;
            auto data = emulator_output(out_spec, length);
            data_section[spec.source_core_id].insert({c.source.io_name, data});
        }
    }


    void emulation_outputs_manager::process_outputs(
        const std::vector<core_step_metadata> &metadata
    ) {
        for(const auto &s:output_specs){
            core_step_metadata m;
            for(auto &m_temp:metadata){
                if(s.first == m_temp.id) m = m_temp;
            }
            if(!m.running){
                // carry over previous outputs
                for(auto &out: data_section[s.first]){

                    out.second.repeat_last_data_point();
                }
            } else {
                for(auto &out: data_section[s.first]){
                    auto spec = output_specs[s.first][out.first];
                    if(spec.address.size()>1){
                        process_vector_output(s.first, out.second, spec ,m.n_channels);
                    } else {
                        process_scalar_output(s.first, out.second, spec ,m.n_channels);
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

        for(auto &s: output_specs[core_id]){
            auto out_data = data_section[core_id].at(s.second.name);
            nlohmann::json output_obj;
            if(s.second.output_type == emulator::type_uint){
                res[s.second.name] = out_data.get_integer_data();
            } else if(s.second.output_type == emulator::type_float){
                res[s.second.name] = out_data.get_float_data();
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
            const emulator::emulator_output_specs &spec,
            uint32_t active_channels
    ){
        uint16_t io_address = spec.address[0];


        for(int i = 0; i<active_channels; i++){
            auto val = runners->at(core_id).dma_read(io_address, i);
            out.add_data_point(val, i);
        }
    }

    void emulation_outputs_manager::process_vector_output(
            std::string core_id,
            emulator_output &out,
            const emulator::emulator_output_specs &spec,
            uint32_t active_channels
    ){
        for(int  j= 0; j<active_channels; j++){
            std::vector<uint32_t> data_point;
            for(int i = 0; i<spec.address.size(); i++){
                uint16_t io_address = spec.address[i];

                auto val = runners->at(core_id).dma_read(io_address, j);
                data_point.push_back(val);
            }
            out.add_data_point(data_point, j);
        }


    }

}