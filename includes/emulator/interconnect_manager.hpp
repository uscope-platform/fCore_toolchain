

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

#ifndef INTERCONNECT_MANAGER_HPP
#define INTERCONNECT_MANAGER_HPP

#include "data_structures/emulation/program_bundle.hpp"
#include "emulator/backend/multirate_io_repeater.hpp"
#include <spdlog/spdlog.h>

namespace fcore {

    class interconnect_manager {
    public:

        void set_program_bundle(const std::vector<program_bundle> &pb) {programs = pb;};
        void set_emulator_memory(const std::shared_ptr<std::unordered_map<std::string, core_memory_pool_t>>  &em) {emulators_memory = em;};

        void clear_repeater();

        void run_interconnect(const emulator::emulator_interconnect &ic, std::unordered_map<std::string, bool> enabled_cores);

    private:

        void run_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_scalar_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_scatter_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_gather_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_vector_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_2d_vector_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);

        uint32_t translate_address(const std::string& core_id, uint32_t io_addr, uint32_t offset);

        void transfer_register(const std::string& src_core, const std::string& dst_core,
                               uint32_t src_addr, uint32_t dst_addr,
                               uint32_t src_channel, uint32_t dst_channel,
                               bool src_enabled
        );

        program_bundle get_bundle_by_name(const std::string& name){
            for(const auto & p : programs){
                if(p.name==name){
                    return p;
                }
            }
            throw std::runtime_error("Program bundle with name: " + name + " not found");
        }


        std::vector<program_bundle> programs;
        multirate_io_repeater output_repeater;
        std::shared_ptr<std::unordered_map<std::string, core_memory_pool_t>> emulators_memory;
    };
}



#endif //INTERCONNECT_MANAGER_HPP
