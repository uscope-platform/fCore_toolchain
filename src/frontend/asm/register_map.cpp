// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#include "fcore_has/frontend/asm/register_map.hpp"


register_map::register_map() {
    for(int i = 0; i<N_REGISTERS; i++){
        std::vector<range_t> reg_range;
        reg_map.push_back(reg_range);
    }
}



bool register_map::is_used(int reg, int from_inst, int to_inst) {
    if(reg==0)
        return true;
    std::vector<range_t> current_ranges = reg_map[reg];
    range_t req_range = {from_inst, to_inst};
    for(auto item:current_ranges){
        bool ranges_overlap = (item.start <= req_range.end) && (req_range.start <= item.end);
        if(ranges_overlap)
            return true;
    }
    return false;
}

void register_map::insert(const std::string &identifier,int reg, int from_inst, int to_inst) {
    range_t req_range = {from_inst, to_inst};
    reg_map[reg].push_back(req_range);
}
