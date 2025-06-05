

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

    void interconnect_manager::run_interconnect(const std::string &core_name, std::unordered_map<std::string, bool> enabled_cores) {


        auto interconnects = bus_engine->get_interconnects(core_name);
        for(const auto &ic: interconnects) {
            if(ic.source.core_name == core_name) {
                if(!ic.source_is_vector() && !ic.destination_is_vector()) {
                    if(!ic.source_is_multichannel()&& !ic.destination_is_multichannel()) {
                        spdlog::trace("SCALAR TRANSFER");
                        transfer_register(
                            ic.source.core_name,
                            ic.destination.core_name,
                            ic.source_addresses[0],
                            ic.destination_addresses[0],
                            0,
                            0,
                            enabled_cores[ic.source.core_name]
                        );
                    } else {
                        spdlog::trace("VECTOR TRANSFER");
                        for(int i = 0; i<ic.source_channels; i++) {
                            transfer_register(
                                ic.source.core_name,
                                ic.destination.core_name,
                                ic.source_addresses[0],
                                ic.destination_addresses[0],
                                i,
                                i,
                                enabled_cores[ic.source.core_name]
                            );
                        }

                    }
                } else if(!ic.source_is_vector() && ic.destination_is_vector()) {
                    spdlog::trace("GATHER TRANSFER");
                    for(int i = 0; i<ic.source_channels; i++){
                        auto src_addr = ic.source_addresses[0];
                        auto dst_addr = ic.destination_addresses[i] ;
                        transfer_register(
                        ic.source.core_name,
                        ic.destination.core_name,
                        src_addr,
                        dst_addr,
                        i,
                        0,
                        enabled_cores[ic.source.core_name]);
                    }
                } else if(ic.source_is_vector() && !ic.destination_is_vector()) {
                    spdlog::trace("SCATTER TRANSFER");
                    for(int i = 0; i<ic.dest_channels; i++){
                        transfer_register(
                        ic.source.core_name,
                        ic.destination.core_name,
                        ic.source_addresses[i],
                        ic.destination_addresses[0],
                        0,
                        i,
                        enabled_cores[ic.source.core_name]);
                    }
                } else {// 1 or 2d vector transfer
                    spdlog::trace("2D VECTOR TRANSFER");
                    for(int j = 0; j<ic.source_addresses.size(); j++){
                        for(int i = 0; i<ic.source_channels; i++){
                            transfer_register(
                            ic.source.core_name,
                            ic.destination.core_name,
                            ic.source_addresses[j],
                            ic.destination_addresses[j],
                            i,
                            i,
                            enabled_cores[ic.source.core_name]);
                        }
                    }
                }
            }

        }
    }



    void interconnect_manager::transfer_register(const std::string& src_core, const std::string& dst_core,
                                             uint32_t src_addr, uint32_t dst_addr,
                                             uint32_t src_channel, uint32_t dst_channel,
                                             bool src_enabled) {

        spdlog::trace("REGISTER TO REGISTER TRANSFER: source {0} | target {1} | source pair ({2}, {3}) | target pair ({4}, {5})", src_core,dst_core, src_channel,src_addr, dst_channel,dst_addr);


        if(src_enabled){
            auto val = runners->at(src_core).dma_read(src_addr, src_channel);
            output_repeater.add_output(src_core, src_addr,src_channel, val);
            runners->at(dst_core).dma_write(dst_addr, dst_channel, val);
        } else {
            auto val = output_repeater.get_output(src_core, src_addr, src_channel);
            runners->at(dst_core).dma_write(dst_addr, dst_channel, val);
        }
    }


    void interconnect_manager::set_emulation_specs(const emulator_specs &specs) {
        bus_engine->set_emulation_specs(specs);
    }

    void interconnect_manager::clear_repeater() {
        output_repeater.clear();
    }


}