

//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#include "emulator/v2/interconnect_manager.hpp"

namespace fcore::emulator_v2 {

    interconnect_manager::interconnect_manager() {
        bus_engine = std::make_shared<bus_allocator>();
    }

    void interconnect_manager::run_interconnect(const std::string &core_name, std::map<std::string, bool> enabled_cores) {
        spdlog::trace("Processing interconnects for core {0}", core_name);
        auto interconnects = bus_engine->get_interconnects();
        for(const auto &ic: interconnects) {
            if(ic.source.core_name == core_name) {
                switch(ic.get_type()) {
                    case dma_link_scalar:
                        spdlog::trace("SCALAR TRANSFER");
                        transfer_register(
                            ic.source,
                            ic.destination,
                            ic.source_addresses[0],
                            ic.destination_addresses[0],
                            0,
                            0,
                            enabled_cores[ic.source.core_name]
                        );
                        break;
                    case dma_link_scatter:
                        spdlog::trace("SCATTER TRANSFER");
                        for(int i = 0; i<ic.destination_shape.channels; i++){
                            transfer_register(
                            ic.source,
                            ic.destination,
                            ic.source_addresses[i],
                            ic.destination_addresses[0],
                            0,
                            i,
                            enabled_cores[ic.source.core_name]);
                        }
                        break;
                    case dma_link_gather:
                        spdlog::trace("GATHER TRANSFER");
                        for(int i = 0; i<ic.source_shape.channels; i++){
                            auto src_addr = ic.source_addresses[0];
                            auto dst_addr = ic.destination_addresses[i] ;
                            transfer_register(
                            ic.source,
                            ic.destination,
                            src_addr,
                            dst_addr,
                            i,
                            0,
                            enabled_cores[ic.source.core_name]);
                        }
                        break;
                    case dma_link_vector:
                        spdlog::trace("VECTOR TRANSFER");
                        for(int i = 0; i<ic.source_shape.channels; i++) {
                            transfer_register(
                                ic.source,
                                ic.destination,
                                ic.source_addresses[0],
                                ic.destination_addresses[0],
                                i,
                                i,
                                enabled_cores[ic.source.core_name]
                            );
                        }
                        break;
                    case dma_link_2d_vector:
                        spdlog::trace("2D VECTOR TRANSFER");
                        for(int j = 0; j<ic.source_shape.size; j++){
                            for(int i = 0; i<ic.source_shape.channels; i++){
                                transfer_register(
                                ic.source,
                                ic.destination,
                                ic.source_addresses[j],
                                ic.destination_addresses[j],
                                i,
                                i,
                                enabled_cores[ic.source.core_name]);
                            }
                        }
                        break;
                    case dma_link_partial:
                        spdlog::trace("PARTIAL SCALAR TRANSFER");
                        transfer_register(
                            ic.source,
                            ic.destination,
                            ic.source_addresses[0],
                            ic.destination_addresses[0],
                            ic.partial_channels.first,
                            ic.partial_channels.second,
                            enabled_cores[ic.source.core_name]
                        );
                        break;
                }
            }

        }
    }

    void interconnect_manager::transfer_register(const endpoint_descriptor& src_core, const endpoint_descriptor& dst_core,
                                                 uint32_t src_addr, uint32_t dst_addr,
                                                 uint32_t src_channel, uint32_t dst_channel,
                                                 bool src_enabled) {

        spdlog::trace("REGISTER TO REGISTER TRANSFER: source {0} | target {1} | source pair ({2}, {3}) | target pair ({4}, {5})", src_core.core_name,dst_core.core_name, src_channel,src_addr, dst_channel,dst_addr);


        if(src_enabled){
            auto read_result = runners->at(src_core.core_name).dma_read(src_addr, src_channel);
            if(!read_result.has_value()) throw std::runtime_error("Error during read phase of register to register transfer " +src_core.core_name + "->" + dst_core.core_name);
            output_repeater.add_output(src_core, src_addr,src_channel, read_result.value());
            auto res = runners->at(dst_core.core_name).dma_write(dst_addr, dst_channel, read_result.value());
            if(!res) throw std::runtime_error("Error during write phase of register to register transfer " +src_core.core_name + "->" + dst_core.core_name);
        } else {
            auto val = output_repeater.get_output(src_core, src_addr, src_channel);
            auto val_f = emulator_backend::uint32_to_float(val);
            auto res = runners->at(dst_core.core_name).dma_write(dst_addr, dst_channel, val);
            if(!res) throw std::runtime_error("Error during register to register transfer " +src_core.core_name+ "->" + dst_core.core_name);
        }
    }


    void interconnect_manager::set_emulation_specs(const emulator_specs &specs) {
        bus_engine->set_emulation_specs(specs);
        output_repeater.set_initial_input_values(specs.get_outputs_initial_values());
    }

    void interconnect_manager::clear_repeater() {
        output_repeater.clear();
    }


}