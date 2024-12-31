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
#include <stdexcept>

#include "data_structures/common/program_metadata.hpp"

namespace fcore {
    struct core_metadata {
        std::string id;
        uint32_t n_skips;
        uint64_t freq;
        uint32_t current_step;
        uint32_t exec_order;
        uint32_t n_channels;
    };

    struct core_step_metadata {
        bool running;
        std::string id;
        uint32_t order;
        uint64_t step_n ;
        uint32_t n_channels;
    };

    class emulation_sequencer {
    public:
        void add_core(const std::string &core_id, uint32_t frequency, uint32_t order, uint32_t n_channels);
        void setup_run(double sim_l);
        void calculate_sequence();

        emulation_progress_stat get_progress();

        uint32_t get_simulation_frequency(){ return simulation_frequency;};
        bool sim_complete() const { return progress < 0; };
        bool is_empty_step() {return empty_step;};
        std::vector<core_step_metadata> get_running_cores();
        void advance_emulation() { progress--;};

        core_step_metadata get_core_by_id(const std::string &id);
        std::string get_next_core_by_order(uint32_t n_step);
        std::string get_core_by_order(uint32_t n_step);
        bool is_last_in_sequence(const std::string &id);

        void clear();
        std::unordered_map<std::string, bool> get_enabled_cores() { return enabled_cores_map; };
    private:

        uint64_t get_current_step() const { return sim_length*simulation_frequency - progress; };
        std::vector<core_metadata> cores;
        int64_t progress;
        float sim_length;
        uint32_t simulation_frequency;
        bool empty_step;
        std::unordered_map<std::string, bool> enabled_cores_map;
    };
}

#endif //FCORE_TOOLCHAIN_EMULATION_SEQUENCER_HPP
