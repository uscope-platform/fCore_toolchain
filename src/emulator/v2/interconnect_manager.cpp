

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

    void interconnect_manager::run_interconnect(const emulator_interconnect &ic, std::unordered_map<std::string, bool> enabled_cores) {
        for(auto &ch:ic.channels){
            run_transfer(ch, ic.source_core_id, ic.destination_core_id, enabled_cores[ic.source_core_id]);
        }
    }


    void interconnect_manager::run_scalar_transfer(
        const dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {
        spdlog::trace("SCALAR TRANSFER");
        auto src_addr = c.source.address[0];
        auto dst_addr = c.destination.address[0];
        transfer_register(src_core, dst_core, src_addr, dst_addr, 0, 0, enabled);

    }

    void interconnect_manager::run_scatter_transfer(
        const dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {

        spdlog::trace("SCATTER TRANSFER");
        for(int i = 0; i<c.length; i++){
            auto src_addr = c.source.address[0] + i;
            auto dst_addr = c.destination.address[0];

            transfer_register(src_core, dst_core, src_addr, dst_addr, 0, i, enabled);
        }
    }

    void interconnect_manager::run_gather_transfer(
        const dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {
        spdlog::trace("GATHER TRANSFER");
        for(int i = 0; i<c.length; i++){
            auto src_addr = c.source.address[0];
            auto dst_addr = c.destination.address[0] + i;

            transfer_register(src_core, dst_core, src_addr, dst_addr, i, 0, enabled);
        }
    }

    void interconnect_manager::run_vector_transfer(
        const dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {
        spdlog::trace("VECTOR TRANSFER");
        for(int i = 0; i<c.length; i++){
            auto src_addr = c.source.address[0];
            auto dst_addr = c.destination.address[0];

            transfer_register(src_core, dst_core, src_addr, dst_addr, i, i, enabled);
        }
    }

    void interconnect_manager::run_2d_vector_transfer(
        const dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {

        spdlog::trace("2D VECTOR TRANSFER");
        for(int j = 0; j<c.stride; j++){
            for(int i = 0; i<c.length; i++){
                auto src_addr =c.source.address[0] + j;
                auto dst_addr = c.destination.address[0]+ j;
                transfer_register(src_core, dst_core, src_addr, dst_addr, i, i, enabled);
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

    void interconnect_manager::run_transfer(const dma_channel &c, const std::string &src_core,
                                            const std::string &dst_core, bool enabled) {
        switch (c.type) {
            case dma_link_scalar:
                run_scalar_transfer(c, src_core, dst_core, enabled);
                break;
            case dma_link_scatter:
                run_scatter_transfer(c, src_core, dst_core, enabled);
                break;
            case dma_link_gather:
                run_gather_transfer(c, src_core, dst_core, enabled);
                break;
            case dma_link_vector:
                run_vector_transfer(c, src_core, dst_core, enabled);
                break;
            case dma_link_2d_vector:
                run_2d_vector_transfer(c, src_core, dst_core, enabled);
                break;
        }
    }

    void interconnect_manager::clear_repeater() {
        output_repeater.clear();
    }


}