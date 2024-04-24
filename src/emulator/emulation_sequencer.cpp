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

#include "emulator/emulation_sequencer.hpp"


void emulation_sequencer::add_core(const std::string& core_id, uint32_t frequency, uint32_t order) {
    core_metadata s;
    s.id = core_id;
    s.freq = frequency;
    s.current_step = 0;
    s.exec_order = order;
    cores.push_back(s);
}

void emulation_sequencer::calculate_sequence() {
    std::vector<uint32_t> frequencies;
    for(auto &i: cores){
        frequencies.push_back(i.freq);
    }


    if ( !std::equal(frequencies.begin() + 1, frequencies.end(), frequencies.begin()) ) {

        uint32_t f_tb = std::accumulate(frequencies.begin(), frequencies.end(), 1,[](uint32_t a, uint32_t b){
            return std::lcm(a,b);
        });

        for(auto &i: cores){
            i.n_skips = f_tb/i.freq - 1;
        }

    } else {

        for(auto &i: cores){
            i.n_skips = 0;
        }
    }

    std::sort(cores.begin(), cores.end(), [](core_metadata const& lhs, core_metadata const &rhs)-> bool {return lhs.exec_order<rhs.exec_order;});

}

std::vector<core_step_metadata> emulation_sequencer::get_running_cores() {
    std::vector<core_step_metadata> ret;
    progress--;
    bool empty_step = true;
    for(auto &i: cores){
        bool executing = false;
        if(i.current_step == 0 || i.n_skips == 0){
            empty_step = false;
            ++i.current_step;
            executing = true;
        } else if(i.current_step == i.n_skips){
            i.current_step = 0;
        } else {
            ++i.current_step;
        }

        core_step_metadata m;
        m.id = i.id;
        m.running = executing;
        enabled_cores_map[i.id] = executing;
        m.order = i.exec_order;
        m.step_n = get_current_step()-1;

        ret.push_back(m);
    }
    if(empty_step){
        return {};
    } else {
        return ret;
    }
}

void emulation_sequencer::setup_run(uint64_t l) {
    sim_length = l;
    progress = sim_length;
}
