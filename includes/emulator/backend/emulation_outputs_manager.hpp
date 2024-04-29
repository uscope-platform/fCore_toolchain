

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

#ifndef FCORE_TOOLCHAIN_EMULATION_OUTPUTS_MANAGER_HPP
#define FCORE_TOOLCHAIN_EMULATION_OUTPUTS_MANAGER_HPP

#include <unordered_map>
#include <utility>
#include <string>
#include <nlohmann/json.hpp>

#include "data_structures/emulation/emulator_output.hpp"
#include "data_structures/emulation/emulator_metadata.hpp"
#include "emulator/backend/emulator.hpp"

namespace fcore{

    class emulation_outputs_manager {
    public:
        void add_specs(const std::string& id, const std::vector<emulator_output_t>& specs, uint32_t active_channels);
        void process_outputs(const std::string& core_id, const emulator_metadata &emu, bool running);
        void set_simulation_frequency(uint32_t freq);
        nlohmann::json get_emulation_output(const std::string& core_id);
        std::vector<double> get_timebase();
    private:
        std::unordered_map<std::string,std::unordered_map<std::string, emulator_output>> data_section;
        std::unordered_map<std::string, std::unordered_map<std::string, emulator_output_t>> output_specs;
    };
}





#endif //FCORE_TOOLCHAIN_EMULATION_OUTPUTS_MANAGER_HPP
