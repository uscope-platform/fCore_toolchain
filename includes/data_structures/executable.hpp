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

#ifndef FCORE_TOOLCHAIN_EXECUTABLE_HPP
#define FCORE_TOOLCHAIN_EXECUTABLE_HPP

#include <cstdint>
#include <utility>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>

#include "data_structures/common/io_map_entry.hpp"

class executable {
public:
    executable();
    static void split_word(uint32_t w, uint16_t fields[2]){
        fields[0] = w&0xFFFF;
        fields[1] = (w&0xFFFF0000)>>16;
    }
    explicit executable(std::vector<uint32_t> executable);
    void add_code_section(std::vector<uint32_t> code);
    void add_io_mapping(const std::set<io_map_entry>& iom);
    std::vector<uint32_t> get_executable();
    std::vector<uint32_t> get_code();
    std::set<std::pair<uint16_t, uint16_t>> get_io_mapping();
    void generate_metadata();
    bool is_io_mapped() {return io_mapping_present;};
private:

    std::unordered_map<std::string, std::vector<uint32_t>> sections;
    bool io_mapping_present = false;
};


#endif //FCORE_TOOLCHAIN_EXECUTABLE_HPP
