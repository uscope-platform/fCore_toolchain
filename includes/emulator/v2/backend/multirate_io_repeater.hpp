

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

#ifndef FCORE_TOOLCHAIN_MULTIRATE_IO_REPEATER_V2_HPP
#define FCORE_TOOLCHAIN_MULTIRATE_IO_REPEATER_V2_HPP

#include <unordered_map>
#include <cstdint>
#include <string>

#include "emulator/v2/bus_allocator.hpp"

namespace fcore::emulator_v2 {
    class multirate_io_repeater {
    public:
        void add_output(const endpoint_descriptor &source, uint32_t addr,uint32_t channel, uint32_t value);
        uint32_t get_output(const endpoint_descriptor &source, uint32_t addr, uint32_t channel);

        void set_initial_input_values(const std::unordered_map<std::string, std::unordered_map<std::string, std::vector<uint32_t>>> &values) {initial_input_values = values;}
        void clear() { working_map.clear(); };
    private:
        std::unordered_map<std::string,
            std::unordered_map<uint32_t, std::unordered_map<uint32_t, uint32_t>>
        > working_map;

        std::unordered_map<std::string, std::unordered_map<std::string, std::vector<uint32_t>>> initial_input_values;

        std::unordered_map<std::string, std::unordered_map<std::string, bool>> initialized_endpoints;
    };
}

#endif //FCORE_TOOLCHAIN_MULTIRATE_IO_REPEATER_V2_HPP
