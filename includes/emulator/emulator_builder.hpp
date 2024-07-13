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

#include "data_structures/emulation/specs/emulator_core.hpp"
#include <nlohmann/json.hpp>
#include "data_structures/emulation/emulator_metadata.hpp"
#include "frontend/binary_loader.hpp"
#include "fcore_dis.hpp"
#include "emulator/backend/emulator_backend.hpp"
#include "fcore_cc.hpp"

namespace fcore {
    class emulator_builder {
    public:
        emulator_builder(bool dbg);

        std::vector<uint32_t>  compile_program(
                const nlohmann::json &core_info,
                const emulator::emulator_core& core_spec,
                const std::vector<nlohmann::json> &input_connections,
                const std::vector<nlohmann::json> &output_connections,
                std::set<io_map_entry> &am
        );
        struct program_info get_program_info() const {return length_info;};


        static std::set<io_map_entry> read_io_map(const std::vector<uint32_t>&  raw_prog);
        static std::vector<uint32_t> sanitize_program(const std::vector<uint32_t>&  raw_prog);


        efi_implementation_t get_efi_implementation(const std::string &s);
        comparator_type_t get_comparator_type(const std::string &s);
    private:

        nlohmann::json process_interconnects(
                const std::vector<nlohmann::json> &input_connections,
                const std::vector<nlohmann::json> &output_connections,
                std::set<std::string> memories
        );

        nlohmann::json process_ioms(
                const nlohmann::json &interconnect_io,
                const nlohmann::json &inputs,
                const nlohmann::json &outputs,
                const nlohmann::json &memory_init_specs,
                const std::set<std::string> memories
        );

        std::set<uint32_t> assigned_inputs;
        std::set<uint32_t> assigned_outputs;
        std::set<std::string> memory_names;

        struct program_info length_info;

        bool debug_autogen;
    };
}



#endif //FCORE_TOOLCHAIN_EMULATOR_BUILDER_HPP
