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

#include "emulator_builder.hpp"
#include "emulator/backend/emulator_backend.hpp"
#include "../../third_party/csv.hpp"
#include "emulation_sequencer.hpp"
#include "data_structures/emulation/hil_bus_map.hpp"
#include "data_structures/emulation/specs/emulator_specs.hpp"
#include "emulator/backend/emulation_outputs_manager.hpp"
#include "data_structures/emulation/emulator_metadata.hpp"
#include "emulator/interconnect_manager.hpp"
#include "emulator_runner.hpp"

namespace fcore{


    class emulator_manager {
    public:
        emulator_manager(bool dbg);
        void set_profiler(const std::shared_ptr<instrumentation_core> &prof){ this->profiler = prof;};
        void set_specs(nlohmann::json &spec_file);
        void process();
        std::optional<debug_checkpoint> emulate(bool interactive);

        void add_breakpoint(const std::string &s, uint32_t addr);
        void remove_breakpoint(const std::string &s, uint32_t addr);

        std::unordered_map<std::string, std::string>  disassemble();

        nlohmann::json get_results();
        std::vector<program_bundle> get_programs();
    private:
        void check_bus_duplicates();

        void run_cores();

        void interconnects_phase(const std::vector<emulator::emulator_interconnect> &specs, const core_step_metadata& info);

        std::unordered_map<std::string, std::string> errors;
        bool debug_autogen;

        bool in_interactive_session;

        uint32_t interactive_restart_point;

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
