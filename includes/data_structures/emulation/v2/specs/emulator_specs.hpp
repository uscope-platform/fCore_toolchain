

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

#ifndef FCORE_TOOLCHAIN_EMULATOR_SPECS_V2_HPP
#define FCORE_TOOLCHAIN_EMULATOR_SPECS_V2_HPP

#include <string>
#include <nlohmann/json.hpp>

#include "emulator_core.hpp"
#include "emulator_interconnect.hpp"
#include "frontend/schema_validators/schema_validator_base.h"



namespace fcore::emulator_v2 {

    class emulator_specs {
    public:
        emulator_specs() = default;
        void set_specs(const nlohmann::json &spec_obj);
        emulator_core get_core_by_id(const std::string &id);


        std::vector<emulator_core> cores;
        std::vector<emulator_interconnect> interconnects;
        double emulation_time;
        bool custom_deploy_mode;
    private:

        emulator_core process_core(const nlohmann::json &o);
        emulator_interconnect process_interconnect(const nlohmann::json &ic);
        emulator_output_specs process_output(const nlohmann::json &o);
        emulator_input_specs process_input(const nlohmann::json &i);
        emulator_memory_specs process_memory(const nlohmann::json &m);


        bool check_float_intness(double d){
            uint64_t rounded_addr = round(d);
            uint64_t c_factor =ceil(d);
            uint64_t f_factor =floor(d);
            if(c_factor == rounded_addr && f_factor == rounded_addr){
                return true;
            } else {
                return false;
            }
        };
    };

} // fcore

#endif //FCORE_TOOLCHAIN_EMULATOR_SPECS_V2_HPP
