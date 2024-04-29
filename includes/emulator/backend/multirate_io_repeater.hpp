

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

#ifndef FCORE_TOOLCHAIN_MULTIRATE_IO_REPEATER_HPP
#define FCORE_TOOLCHAIN_MULTIRATE_IO_REPEATER_HPP

#include <unordered_map>
#include <cstdint>
#include <string>

namespace fcore {
    class multirate_io_repeater {
    public:
        void add_output(std::string &core, uint32_t addr, uint32_t value) { working_map[core][addr] = value; };

        uint32_t get_output(std::string &core, uint32_t addr) { return working_map[core][addr]; };

        void clear() { working_map.clear(); };
    private:
        std::unordered_map<std::string, std::unordered_map<uint32_t, uint32_t>> working_map;

    };
}

#endif //FCORE_TOOLCHAIN_MULTIRATE_IO_REPEATER_HPP
