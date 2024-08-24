

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
// limitations under the License.

#include "data_structures/emulation/hil_bus_map.hpp"

namespace fcore{

    bool hil_bus_map::check_duplicates() {
        std::map<uint32_t, hil_bus_map_entry> working_set;

        for(auto &entry:data_struct){
            if(working_set.contains(entry.address)){
                if(entry.source != working_set[entry.address].source){
                    duplicates.emplace_back(entry, working_set[entry.address]);
                }
            } else {
                working_set[entry.address] = entry;
            }
        }
        return !duplicates.empty();
    }

    nlohmann::json hil_bus_map::get_duplicates() {
        nlohmann::json ret;
        ret["duplicates"] = duplicates;
        return ret;
    }
}

