// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_REGISTER_MAP_HPP
#define FCORE_TOOLCHAIN_REGISTER_MAP_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define N_REGISTERS 16

typedef struct{
    int start;
    int end;
} range_t;

class register_map {
public:
    register_map();
    bool is_used(int reg, int from_inst, int to_inst);
    void insert(const std::string& identifier,int reg, int from_inst, int to_inst);
private:

    std::vector<std::vector<range_t>> reg_map;
};


#endif //FCORE_TOOLCHAIN_REGISTER_MAP_HPP
