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
// limitations under the License.05/07/2021.


#ifndef FCORE_TOOLCHAIN_EMULATOR_BUILDER_HPP
#define FCORE_TOOLCHAIN_EMULATOR_BUILDER_HPP

#include <vector>
#include <cstdint>
#include <memory>

#include <nlohmann/json.hpp>
#include "frontend/emulator_metadata.hpp"
#include "frontend/binary_loader.hpp"
#include "fcore_dis.hpp"
#include "data_structures/instruction_stream.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "emulator.hpp"
#include "fcore_cc.hpp"


class emulator_builder {
public:
    emulator_builder(bool dbg);
    emulator_metadata load_json_program(const nlohmann::json &core_info, const std::vector<nlohmann::json> &input_connections,
                                   const std::vector<nlohmann::json> &output_connections, std::set<io_map_entry> &am);

    void clear_dma_io() {dma_io.clear();};
    std::map<int, std::string> get_core_ordering(){return cores_ordering;};

    std::vector<uint32_t>  compile_programs(
            const nlohmann::json &core_info,
            const std::vector<nlohmann::json> &input_connections,
            const std::vector<nlohmann::json> &output_connections,
            std::set<io_map_entry> &am
    );

private:

    void process_interconnects(
            const std::vector<nlohmann::json> &input_connections,
            const std::vector<nlohmann::json> &output_connections,
            std::set<std::string> memories
    );

    void process_ioms(
            const nlohmann::json &inputs,
            const nlohmann::json &outputs,
            const nlohmann::json &memory_init_specs,
            const std::set<std::string> memories
    );

    nlohmann::json dma_io;
    std::set<uint32_t> assigned_inputs;
    std::set<uint32_t> assigned_outputs;
    std::set<std::string> memory_names;


    std::map<int, std::string> cores_ordering;
    cores_ordering_t ordering_style = no_ordering;
    int implicit_order_idx = 0;

    bool debug_autogen;
};


#endif //FCORE_TOOLCHAIN_EMULATOR_BUILDER_HPP
