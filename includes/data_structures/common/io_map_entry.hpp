

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

#ifndef FCORE_TOOLCHAIN_IO_MAP_ENTRY_HPP
#define FCORE_TOOLCHAIN_IO_MAP_ENTRY_HPP

#include <string>
#include <cstdint>
#include <optional>
#include <set>

namespace fcore{
    class io_map_entry{
    public:
        io_map_entry(int32_t i, int32_t c, const std::string &t) {io_addr =i; core_addr = c; type = t;};
        int32_t io_addr;
        int32_t core_addr;
        std::string io_name;
        bool common_io = false;

        std::string type;
        bool operator<(io_map_entry& rhs) const
        {
            return io_addr < rhs.io_addr;
        }
        bool operator<(const io_map_entry& rhs) const
        {
            return io_addr < rhs.io_addr;
        }
        static std::optional<io_map_entry> get_io_map_entry_by_io_addr(const std::set<io_map_entry>& set, uint32_t addr){
            for(auto &item:set){
                if(item.io_addr == addr){
                    return item;
                }
            }
            return {};
        }

        static std::optional<io_map_entry>  get_io_map_entry_by_core_addr(const std::set<io_map_entry>& set, uint32_t addr){
            for(auto &item:set){
                if(item.core_addr == addr){
                    return item;
                }
            }
            return {};
        }
    };


}




#endif //FCORE_TOOLCHAIN_IO_MAP_ENTRY_HPP
