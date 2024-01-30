// Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP
#define FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "data_structures/emulation/emulator_input.hpp"
#include "data_structures/emulation/emulator_input_factory.hpp"
#include "frontend/schema_validators/schema_validator_base.h"
#include "frontend/binary_loader.hpp"
#include "../third_party/csv.hpp"
#include "backend/emulator/emulator.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "frontend/emulator_metadata.hpp"
#include "backend/emulator/emulator_builder.hpp"


class program_bundle{
public:
    std::string name;
    std::vector<uint32_t> program;
    std::shared_ptr<io_map> io;
};

class emulator_manager {
public:
    emulator_manager(nlohmann::json &spec_file, bool dbg, std::string s_f);
    void emulate();

    std::shared_ptr<std::vector<uint32_t>> get_memory_snapshot(const std::string &core_id, int channel);
    std::string get_results();
    std::unordered_map<std::string, emulator_metadata> get_emulators(){return emulators;};
    std::vector<program_bundle> get_programs();
    std::vector<interconnect_t> load_interconnects(nlohmann::json &interconnects);
private:

    std::unordered_map<std::string, emulator_input> load_input(nlohmann::json &core);
    std::vector<emulator_output_t> load_output_specs(nlohmann::json &core);
    std::unordered_map<unsigned int, uint32_t> load_memory_init(nlohmann::json &mem_init);
    std::unordered_map<unsigned int, uint32_t> io_remap_memory_init(std::unordered_map<unsigned int, uint32_t> &map,
                                                                    std::unordered_map<uint16_t, uint16_t> &io_map);

    nlohmann::json dump_core(const emulator_metadata &md);
    nlohmann::json dump_interconnects(const std::vector<interconnect_t> &md);

    void run_cores();

    nlohmann::json get_channel_outputs(std::vector<emulator_output_t> specs, int ch, std::unordered_map<int, std::unordered_map<int, std::vector<uint32_t>>> outs);

    static std::vector<float> uint32_to_float(std::vector<uint32_t> &vect);
    std::map<int, std::string> cores_ordering;

    std::unordered_map<std::string, emulator_metadata> emulators;
    std::vector<interconnect_t> interconnects;
    int emu_length;
    std::unordered_map<std::string, std::string> errors;
    bool debug_autogen;

    nlohmann::json spec_file;
    std::string schema_file;
};


#endif //FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP
