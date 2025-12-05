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


#ifndef FCORE_TOOLCHAIN_IO_MAP_HPP
#define FCORE_TOOLCHAIN_IO_MAP_HPP

#include <map>
#include <string>
#include <vector>
#include "io_map_entry.hpp"
namespace fcore {
    typedef std::map<std::string, std::vector<io_map_entry>> io_map;
}


#endif //FCORE_TOOLCHAIN_IO_MAP_HPP