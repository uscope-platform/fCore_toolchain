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
// limitations under the License.05/07/2021.
//

#ifndef FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP
#define FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <fstream>

#include "frontend/binary_loader.hpp"
#include "../third_party/json.hpp"
#include "backend/emulator.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"

typedef struct {
    std::vector<std::pair<unsigned int, std::vector<uint32_t>>> input;
    std::vector<emulator_output_t> output_specs;
    std::unordered_map<unsigned int, std::pair<std::string, std::string>> output_types;
    std::unordered_map<unsigned int, uint32_t> memory_init;
    std::shared_ptr<emulator> emu;
    int active_channels;
    std::string efi_implementation;
    std::vector<uint32_t> memory;
    std::unordered_map<int, std::vector<uint32_t>> outputs;
}emulator_metadata;

class emulator_manager {
public:
    emulator_manager(nlohmann::json &spec_file);
    void run_emulation();
    std::string get_results();

private:
    emulator_metadata load_program(nlohmann::json &core);
    std::vector<std::pair<unsigned int, std::vector<uint32_t>>> load_input(nlohmann::json &core);
    std::vector<emulator_output_t> load_output_specs(nlohmann::json &core);
    std::unordered_map<unsigned int, uint32_t> load_memory_init(nlohmann::json &mem_init);
    static std::vector<float> uint32_to_float(std::vector<uint32_t> &vect);
    std::unordered_map<std::string, emulator_metadata> emulators;
    std::unordered_map<std::string, std::string> errors;
};


#endif //FCORE_TOOLCHAIN_EMULATOR_MANAGER_HPP
