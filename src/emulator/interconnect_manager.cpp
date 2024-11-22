

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

#include "emulator/interconnect_manager.hpp"

namespace fcore {



    void interconnect_manager::run_scalar_transfer(
        const emulator::dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {
        spdlog::trace("SCALAR TRANSFER");
        auto src_addr = translate_address(src_core, c.source.address[0], 0);
        auto dst_addr = translate_address(dst_core, c.destination.address[0], 0);

        transfer_register(src_core, dst_core, src_addr, dst_addr, 0, 0, enabled);

    }

    void interconnect_manager::run_scatter_transfer(
        const emulator::dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {

        spdlog::trace("SCATTER TRANSFER");
        for(int i = 0; i<c.length; i++){
            auto src_addr = translate_address(src_core, c.source.address[0], i);
            auto dst_addr = translate_address(dst_core, c.destination.address[0], 0);

            transfer_register(src_core, dst_core, src_addr, dst_addr, 0, i, enabled);
        }
    }

    void interconnect_manager::run_gather_transfer(
        const emulator::dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {
        spdlog::trace("GATHER TRANSFER");
        for(int i = 0; i<c.length; i++){
            auto src_addr = translate_address(src_core, c.source.address[0], 0);
            auto dst_addr = translate_address(dst_core, c.destination.address[0], i);

            transfer_register(src_core, dst_core, src_addr, dst_addr, i, 0, enabled);
        }
    }

    void interconnect_manager::run_vector_transfer(
        const emulator::dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {
        spdlog::trace("VECTOR TRANSFER");
        for(int i = 0; i<c.length; i++){
            auto src_addr = translate_address(src_core, c.source.address[0], 0);
            auto dst_addr = translate_address(dst_core, c.destination.address[0], 0);

            transfer_register(src_core, dst_core, src_addr, dst_addr, i, i, enabled);
        }
    }

    void interconnect_manager::run_2d_vector_transfer(
        const emulator::dma_channel &c,
        const std::string &src_core,
        const std::string &dst_core,
        bool enabled
    ) {

        spdlog::trace("2D VECTOR TRANSFER");
        for(int j = 0; j<c.stride; j++){
            for(int i = 0; i<c.length; i++){
                auto src_addr = translate_address(src_core, c.source.address[0] + j, 0);
                auto dst_addr = translate_address(dst_core, c.destination.address[0]+ j, 0);

                transfer_register(src_core, dst_core, src_addr, dst_addr, i, i, enabled);
            }
        }
    }


    void interconnect_manager::transfer_register(const std::string& src_core, const std::string& dst_core,
                                             uint32_t src_addr, uint32_t dst_addr,
                                             uint32_t src_channel, uint32_t dst_channel,
                                             bool src_enabled) {

        spdlog::trace("REGISTER TO REGISTER TRANSFER: source {0} | target {1} | source pair ({2}, {3}) | target pair ({4}, {5})", src_core,dst_core, src_channel,src_addr, dst_channel,dst_addr);

        if(dst_channel>=emulators_memory->at(dst_core).size()){
            throw std::runtime_error("Attempted write to unavailable channel: " + std::to_string(dst_channel) + " of core: " + dst_core);
        }
        if(src_enabled){
            if(src_channel>=emulators_memory->at(src_core).size()){
                throw std::runtime_error("Attempted read from unavailable channel: " + std::to_string(src_channel) + " of core: " + src_core);
            }
            auto val = emulators_memory->at(src_core)[src_channel]->at(src_addr);
            output_repeater.add_output(src_core, src_addr,src_channel, val);
             emulators_memory->at(dst_core)[dst_channel]->at(dst_addr) = val;
        } else {
            auto val = output_repeater.get_output(src_core, src_addr, src_channel);
            emulators_memory->at(dst_core)[dst_channel]->at(dst_addr) = val;
        }
    }

    uint32_t interconnect_manager::translate_address(const std::string& core_id, uint32_t io_addr, uint32_t offset) {

        auto bundle =get_bundle_by_name(core_id);

        if(auto a = io_map_entry::get_io_map_entry_by_io_addr(bundle.io, io_addr + offset)){
            auto core_addr = a->core_addr;
            spdlog::trace("ADDRESS TRANSLATION: core {0} | io address {1} | core address {2}", core_id, io_addr + offset, core_addr);
            return core_addr;
        } else{
            throw std::runtime_error("Unable to find io address " + std::to_string(io_addr + offset) + " in the source address map for core: " + core_id);
        }
    }

    void interconnect_manager::run_transfer(const emulator::dma_channel &c, const std::string &src_core,
                                            const std::string &dst_core, bool enabled) {
        switch (c.type) {
            case emulator::dma_link_scalar:
                run_scalar_transfer(c, src_core, dst_core, enabled);
                break;
            case emulator::dma_link_scatter:
                run_scatter_transfer(c, src_core, dst_core, enabled);
                break;
            case emulator::dma_link_gather:
                run_gather_transfer(c, src_core, dst_core, enabled);
                break;
            case emulator::dma_link_vector:
                run_vector_transfer(c, src_core, dst_core, enabled);
                break;
            case emulator::dma_link_2d_vector:
                run_2d_vector_transfer(c, src_core, dst_core, enabled);
                break;
        }
    }

    void interconnect_manager::clear_repeater() {
        output_repeater.clear();
    }

}