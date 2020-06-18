//
// Created by fils on 18/06/20.
//

#include "register_map.hpp"


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
