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
#include <nlohmann/json.hpp>
#include "frontend/emulator_metadata.hpp"
#include "frontend/binary_loader.hpp"
#include "data_structures/instruction_stream.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "backend/emulator.hpp"
#include "fcore_cc.hpp"

class emulator_builder {
public:
    emulator_metadata load_program(const nlohmann::json &core_info, const nlohmann::json &input_connections, const nlohmann::json &output_connections);
private:

};


#endif //FCORE_TOOLCHAIN_EMULATOR_BUILDER_HPP
