//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_EMULATION_SEQUENCER_HPP
#define FCORE_TOOLCHAIN_EMULATION_SEQUENCER_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>
#include <numeric>
#include <algorithm>

namespace fcore {
    struct core_metadata {
        std::string id;
        uint32_t n_skips;
        uint64_t freq;
        uint32_t current_step;
        uint32_t exec_order;
    };

    struct core_step_metadata {
        bool running;
        std::string id;
        uint32_t order;
        uint64_t step_n;
    };

    class emulation_sequencer {
    public:
        void add_core(const std::string &core_id, uint32_t frequency, uint32_t order);
        void setup_run(uint64_t l);
        void calculate_sequence();

        uint32_t get_simulation_frequency(){ return simulation_frequency;};
        uint64_t get_current_step() const { return sim_length - progress; };
        bool sim_complete() const { return progress == 0; };

        std::vector<core_step_metadata> get_running_cores();

        std::unordered_map<std::string, bool> get_enabled_cores() { return enabled_cores_map; };
    private:
        std::vector<core_metadata> cores;
        uint64_t progress;
        uint64_t sim_length;
        uint32_t simulation_frequency;
        std::unordered_map<std::string, bool> enabled_cores_map;
    };
}

#endif //FCORE_TOOLCHAIN_EMULATION_SEQUENCER_HPP
