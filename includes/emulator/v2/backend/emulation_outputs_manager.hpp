

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

#ifndef FCORE_TOOLCHAIN_EMULATION_OUTPUTS_MANAGER_V2_HPP
#define FCORE_TOOLCHAIN_EMULATION_OUTPUTS_MANAGER_V2_HPP

#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>

#include "data_structures/emulation/v2/specs/emulator_specs.hpp"
#include "data_structures/emulation/v2/emulator_output.hpp"
#include "data_structures/emulation/v2/emulator_metadata.hpp"
#include "data_structures/common/io_map_entry.hpp"

#include "emulator/v2/emulator_runner.hpp"
#include "emulator/v2/bus_allocator.hpp"

namespace fcore::emulator_v2{

    class emulation_outputs_manager {
    public:
        void set_runners(const std::shared_ptr<std::unordered_map<std::string, emulator_runner>> &r){runners = r;}
        void process_specs(const std::shared_ptr<bus_allocator> &bus_engine);
        void process_outputs(
            const std::vector<core_step_metadata> &metadata,
            const std::string &core
        );

        bool process_scalar_output(
                std::string core_id,
                emulator_output &out,
                uint32_t address,
                uint32_t active_channels
        );

        bool process_vector_output(
                std::string core_id,
                emulator_output &out,
            std::vector<uint32_t> addresses,
                uint32_t active_channels
        );
        void set_initial_values(const std::map<std::string,std::map<std::string, std::vector<uint32_t>>> &ivs){initial_values = ivs;}
        void set_simulation_frequency(uint32_t freq);
        nlohmann::json get_emulation_output(const std::string& core_id);
        void clear();
    private:
        std::shared_ptr<bus_allocator> bus_engine;
        std::shared_ptr<std::unordered_map<std::string, emulator_runner>> runners;

        std::map<std::string,std::map<std::string, emulator_output>> data_section;

        std::map<std::string,std::map<std::string, std::vector<uint32_t>>> initial_values;
    };
}





#endif //FCORE_TOOLCHAIN_EMULATION_OUTPUTS_MANAGER_V2_HPP
