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

#ifndef FCORE_TOOLCHAIN_EXECUTABLE_HPP
#define FCORE_TOOLCHAIN_EXECUTABLE_HPP

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>

class executable {
public:
    executable();
    void add_code_section(std::vector<uint32_t> code);
    void add_io_mapping(std::vector<std::pair<uint16_t, uint16_t>>);
    std::vector<uint32_t> get_executable();
    std::vector<uint32_t> get_code();
    void generate_metadata();
private:
    std::unordered_map<std::string, std::vector<uint32_t>> sections;

};


#endif //FCORE_TOOLCHAIN_EXECUTABLE_HPP
