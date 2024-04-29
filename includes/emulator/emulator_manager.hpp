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
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "data_structures/emulation/emulator_input.hpp"
#include "data_structures/emulation/emulator_input_factory.hpp"
#include "data_structures/emulation/hil_bus_map.hpp"
#include "emulation_sequencer.hpp"
#include "frontend/schema_validators/schema_validator_base.h"
#include "frontend/binary_loader.hpp"
#include "../../third_party/csv.hpp"
#include "emulator/backend/emulator.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "data_structures/emulation/emulator_metadata.hpp"
#include "emulator_builder.hpp"
#include "emulator/backend/multirate_io_repeater.hpp"
#include "emulator/backend/emulation_outputs_manager.hpp"

namespace fcore{
    class program_bundle{
    public:
        std::string name;
        std::vector<uint32_t> program;
        std::set<io_map_entry> io;
        std::unordered_map<uint32_t, uint32_t> mem_init;
        uint32_t multirate_divisor;
    };

    class emulator_manager {
    public:
        emulator_manager(nlohmann::json &spec_file, bool dbg, const std::string& s_f);
        void process();
        void emulate();

        std::shared_ptr<std::vector<uint32_t>> get_memory_snapshot(const std::string &core_id, int channel);
        std::string get_results();
        std::unordered_map<std::string, emulator_metadata> get_emulators(){return emulators;};
        std::vector<program_bundle> get_programs();
        std::vector<interconnect_t> load_interconnects(nlohmann::json &interconnects);
    private:
        void check_bus_duplicates();
        std::unordered_map<std::string, emulator_input> load_input(nlohmann::json &core);
        std::vector<emulator_output_t> load_output_specs(nlohmann::json &core);
        std::unordered_map<unsigned int, uint32_t> load_memory_init(nlohmann::json &mem_init);
        std::unordered_map<unsigned int, uint32_t> io_remap_memory_init(std::unordered_map<unsigned int, uint32_t> &map,
                                                                        std::unordered_map<uint16_t, uint16_t> &io_map);

        void run_cores();

        void inputs_phase(const core_step_metadata& info);
        void execution_phase(const core_step_metadata& info);
        void interconnects_phase(const core_step_metadata& info, std::unordered_map<std::string, bool> enabled_cores);
        void outputs_phase(core_step_metadata info);

        nlohmann::json get_channel_outputs(std::vector<emulator_output_t> specs, int ch, std::unordered_map<int, std::unordered_map<int, std::vector<uint32_t>>> outs);

        std::unordered_map<std::string, emulator_metadata> emulators;
        std::vector<interconnect_t> interconnects;
        int emu_length;
        std::unordered_map<std::string, std::string> errors;
        bool debug_autogen;

        nlohmann::json spec_file;
        std::string schema_file;

        hil_bus_map bus_map;

        multirate_io_repeater output_repeater;
        emulation_sequencer sequencer;
        emulation_outputs_manager outputs_manager;
        bool async_multirate;
    };
}


#endif //FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP
