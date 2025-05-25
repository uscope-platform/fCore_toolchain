

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

#include "emulator/v1/emulator_runner.hpp"
#include "emulator/v1/backend/multirate_io_repeater.hpp"
#include <spdlog/spdlog.h>



namespace fcore {

    class interconnect_manager {
    public:
        void set_runners(const std::shared_ptr<std::unordered_map<std::string, emulator_runner>> &r){runners = r;};

        void clear_repeater();

        void run_interconnect(const emulator::emulator_interconnect &ic, std::unordered_map<std::string, bool> enabled_cores);

    private:

        void run_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_scalar_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_scatter_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_gather_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_vector_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);
        void run_2d_vector_transfer(const emulator::dma_channel &c, const std::string &src_core, const std::string &dst_core,bool enabled);

        void transfer_register(const std::string& src_core, const std::string& dst_core,
                               uint32_t src_addr, uint32_t dst_addr,
                               uint32_t src_channel, uint32_t dst_channel,
                               bool src_enabled
        );


        std::shared_ptr<std::unordered_map<std::string, emulator_runner>> runners;
        multirate_io_repeater output_repeater;
    };
}



#endif //INTERCONNECT_MANAGER_HPP
