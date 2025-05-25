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

#include "emulator/v1/emulation_sequencer.hpp"

#include <cmath>


namespace fcore::emulator{

    void emulation_sequencer::add_core(const std::string& core_id, uint32_t frequency, uint32_t order, uint32_t n_channels) {
        if(order==0){
            throw std::runtime_error("The execution order must an integer greater than 1");
        }
        core_metadata s;
        s.id = core_id;
        s.freq = frequency;
        s.current_step = 0;
        s.exec_order = order;
        s.n_channels = n_channels;
        cores.push_back(s);
    }

    void emulation_sequencer::calculate_sequence() {
        std::vector<uint32_t> frequencies;
        for(auto &i: cores){
            frequencies.push_back(i.freq);
        }


        if ( !std::equal(frequencies.begin() + 1, frequencies.end(), frequencies.begin()) ) {

            simulation_frequency = std::accumulate(frequencies.begin(), frequencies.end(), 1,[](uint32_t a, uint32_t b){
                return std::lcm(a,b);
            });

            for(auto &i: cores){
                i.n_skips = simulation_frequency/i.freq - 1;
            }

        } else {
            simulation_frequency = frequencies[0];
            for(auto &i: cores){
                i.n_skips = 0;
            }
        }

        progress =  (uint64_t) std::round(sim_length*(float)simulation_frequency)-1;

        std::sort(cores.begin(), cores.end(), [](core_metadata const& lhs, core_metadata const &rhs)-> bool {return lhs.exec_order<rhs.exec_order;});

    }

    std::vector<core_step_metadata> emulation_sequencer::get_running_cores() {
        std::vector<core_step_metadata> ret;
        ;
        empty_step = true;
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
            m.step_n = get_current_step() -1;
            m.n_channels = i.n_channels;
            ret.push_back(m);
        }
        return ret;
    }

    void emulation_sequencer::setup_run(double sim_l) {
        sim_length = sim_l;
    }

    void emulation_sequencer::clear() {
        progress = 0;
        sim_length = 0;
        simulation_frequency = 0;
        empty_step = false;
        cores.clear();
        enabled_cores_map.clear();
    }

    core_step_metadata emulation_sequencer::get_core_by_id(const std::string &id) {
        for(auto &c:cores){
            if(c.id == id){
                core_step_metadata m;
                m.id = c.id;
                m.running = true;
                m.order = c.exec_order;
                m.step_n = get_current_step() -1;
                m.n_channels = c.n_channels;
                return m;
            }
        }
        throw std::runtime_error("Core " + id + " not found");
    }

    bool emulation_sequencer::is_last_in_sequence(const std::string &id) {
        for(auto &c:cores) {
            if (c.id == id) {
                if(c.exec_order == cores.size()) return true;
                else return false;
            }
        }
        throw std::runtime_error("Core " + id + " not found");
    }

    std::string emulation_sequencer::get_next_core_by_order(uint32_t n_step) {
        uint32_t next_order = 1;
        if(n_step != cores.size()){
            next_order = n_step + 1;
        }
        return get_core_by_order(next_order);
    }

    std::string emulation_sequencer::get_core_by_order(uint32_t n_step) {
        for(auto &c:cores){
            if(c.exec_order == n_step){
                return c.id;
            }
        }
        throw std::runtime_error("Core with exection order " + std::to_string(n_step) + " not found");
    }

    emulation_progress_stat emulation_sequencer::get_progress() const {
        emulation_progress_stat ret;
        ret.current = get_current_step();
        ret.total_steps = std::round(sim_length*(float)simulation_frequency);
        ret.period = 1/simulation_frequency;
        return ret;
    }
}

