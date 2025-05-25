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

#ifndef FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP
#define FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "emulator/v1/emulator_builder.hpp"
#include "emulator/v1/backend/emulator_backend.hpp"
#include "emulator/v1/emulation_sequencer.hpp"
#include "data_structures/emulation/v1/hil_bus_map.hpp"
#include "data_structures/emulation/v1/specs/emulator_specs.hpp"
#include "emulator/v1/backend/emulation_outputs_manager.hpp"
#include "data_structures/emulation/v1/emulator_metadata.hpp"
#include "emulator/v1/interconnect_manager.hpp"
#include "emulator/v1/emulator_runner.hpp"

namespace fcore{


    class emulator_manager {
    public:
        emulator_manager();
        void enable_debug_mode() {debug_autogen = true;};
        void set_profiler(const std::shared_ptr<instrumentation_core> &prof){ this->profiler = prof;};
        void set_specs(const nlohmann::json &spec_file);
        std::set<uint32_t> get_breakpoints(const std::string &id);
        void process();

        std::optional<debug_checkpoint> emulate();
        debug_checkpoint step_over();
        std::optional<debug_checkpoint> continue_emulation();

        void add_breakpoint(const std::string &s, uint32_t addr);
        void remove_breakpoint(const std::string &s, uint32_t addr);

        void set_multichannel_debug(bool mc);

        std::unordered_map<std::string, disassembled_program>  disassemble();

        nlohmann::json get_results();
        std::vector<program_bundle> get_programs();
    private:
        void check_bus_duplicates();

        void run_cores(bool in_progress);

        debug_checkpoint augment_checkpoint_info(debug_checkpoint &in);

        void interconnects_phase(const std::vector<emulator::emulator_interconnect> &specs, const core_step_metadata& info);

        std::unordered_map<std::string, std::string> errors;
        bool debug_autogen;
        bool multichannel_debug;


        int interactive_restart_point;
        std::string currently_active_core;
        uint32_t current_channel;

        hil_bus_map bus_map;

        emulation_sequencer sequencer;
        emulation_outputs_manager outputs_manager;

        interconnect_manager ic_manager;

        std::vector<program_bundle> programs;

        std::shared_ptr<instrumentation_core> profiler;

        std::shared_ptr<std::unordered_map<std::string, emulator_runner>> runners;

        emulator::emulator_specs emu_spec;

    };
}


#endif //FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP
