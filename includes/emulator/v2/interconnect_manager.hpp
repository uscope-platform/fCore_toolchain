

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

#ifndef INTERCONNECT_MANAGER_V2_HPP
#define INTERCONNECT_MANAGER_V2_HPP

#include "emulator/v2/emulator_runner.hpp"
#include "emulator/v2/bus_allocator.hpp"
#include "emulator/v2/backend/multirate_io_repeater.hpp"
#include <spdlog/spdlog.h>



namespace fcore::emulator_v2 {

    class interconnect_manager {
    public:
        interconnect_manager();
        void set_emulation_specs(const emulator_specs &specs);
        void set_runners(const std::shared_ptr<std::unordered_map<std::string, emulator_runner>> &r){runners = r;};
        std::shared_ptr<bus_allocator> get_bus_engine(){ return bus_engine;}
        void clear_repeater();

        void run_interconnect(const std::string &core_name, std::unordered_map<std::string, bool> enabled_cores);

    private:

        void run_transfer(const dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_vector_transfer(const dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_2d_vector_transfer(const dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);

        void transfer_register(const std::string& src_core, const std::string& dst_core,
                               uint32_t src_addr, uint32_t dst_addr,
                               uint32_t src_channel, uint32_t dst_channel,
                               bool src_enabled
        );


        std::shared_ptr<bus_allocator> bus_engine;

        std::shared_ptr<std::unordered_map<std::string, emulator_runner>> runners;
        multirate_io_repeater output_repeater;
    };
}



#endif //INTERCONNECT_MANAGER_V2_HPP
