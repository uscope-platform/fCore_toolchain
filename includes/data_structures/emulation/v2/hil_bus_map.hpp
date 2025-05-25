

//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_HIL_BUS_MAP_V2_HPP
#define FCORE_TOOLCHAIN_HIL_BUS_MAP_V2_HPP

#include <vector>
#include <string>
#include <cstdint>

#include <nlohmann/json.hpp>

namespace fcore::emulator_v2 {

    struct hil_bus_map_entry{
        std::string source;
        std::string type;
        std::string name;
        uint32_t address;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(hil_bus_map_entry, source, type, name, address)
    };

    class hil_bus_map {
    public:
        void add_entry(const std::string &src, const std::string &t, uint32_t a,const std::string &n){data_struct.push_back({src, t, n,a});};
        bool check_duplicates();
        nlohmann::json  get_duplicates();
        void clear(){data_struct.clear();};
    private:
        std::vector<hil_bus_map_entry> data_struct;
        std::vector<std::pair<hil_bus_map_entry, hil_bus_map_entry>> duplicates;
    };
}



#endif //FCORE_TOOLCHAIN_HIL_BUS_MAP_V2_HPP
