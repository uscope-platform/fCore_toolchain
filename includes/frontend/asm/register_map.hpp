// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

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
