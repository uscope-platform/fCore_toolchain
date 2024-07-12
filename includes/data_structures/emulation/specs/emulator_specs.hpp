

//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_EMULATOR_SPECS_HPP
#define FCORE_TOOLCHAIN_EMULATOR_SPECS_HPP

#include <string>
#include <nlohmann/json.hpp>

#include "data_structures/emulation/specs/emulator_core.hpp"
#include "data_structures/emulation/specs/emulator_interconnect.hpp"
#include "frontend/schema_validators/schema_validator_base.h"



namespace fcore::emulator{

    class emulator_specs {
    public:
        explicit emulator_specs(const nlohmann::json &spec_obj, const std::string& schema_path);
        emulator_core get_core_by_id(const std::string &id);


        std::vector<emulator_core> cores;
        std::vector<emulator_interconnect> interconnects;
        double emulation_time;
    private:

        emulator_core process_core(const nlohmann::json &o);
        emulator_interconnect process_interconnect(const nlohmann::json &ic);
        emulator_output_specs process_output(const nlohmann::json &o);
        emulator_input_specs process_input(const nlohmann::json &i, const nlohmann::json &in_data);
        emulator_memory_specs process_memory(const nlohmann::json &m);

    };

} // fcore

#endif //FCORE_TOOLCHAIN_EMULATOR_SPECS_HPP
