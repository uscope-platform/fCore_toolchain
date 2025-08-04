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

#include "tools/register_map.hpp"

namespace fcore{
    register_map::register_map() {
        for(int i = 0; i<N_REGISTERS; i++){
            std::vector<range_t> reg_range;
            reg_map.push_back(reg_range);
        }
    }



    bool register_map::is_used(int reg, std::shared_ptr<variable> var) {
        if(reg==0)
            return true;
        if(var->get_variable_class().common_io) {
            return used_common_io.contains(reg);
        }else {
            std::vector<range_t> current_ranges = reg_map[reg];
            range_t req_range;
            req_range.start = var->get_first_occurrence();
            req_range.end = var->get_last_occurrence();
            for(auto item:current_ranges){
                bool ranges_overlap = (item.start <= req_range.end) && (req_range.start <= item.end);
                if(ranges_overlap)
                    return true;
            }
        }

        return false;
    }

    bool register_map::is_used(std::pair<int,int> array, std::shared_ptr<variable> var) {
        bool retval = false;
        if(array.first==0)
            retval = true;
        for(int i =array.first; i<array.first+array.second; i++){
            retval |= is_used(i, var);
        }
        return retval;
    }

    void register_map::insert(const std::shared_ptr<variable>& var,int reg) {
        range_t req_range;
        req_range.start = var->get_first_occurrence();
        req_range.end = var->get_last_occurrence();
        reg_map[reg].push_back(req_range);
        identifiers_map[var->get_identifier()] = std::make_shared<variable>("r"+std::to_string(reg));
    }



    void register_map::insert(const std::shared_ptr<variable>& var, std::pair<int, int> reg) {

        range_t req_range;
        req_range.start = var->get_first_occurrence();
        req_range.end = var->get_last_occurrence();

        for(int i=0; i<reg.second; i++){
            reg_map[reg.first+i].push_back(req_range);
            auto idx = array_delinearize(var->get_array_shape(), i);
            identifiers_map[var->get_identifier(idx)] = std::make_shared<variable>("r"+std::to_string(reg.first+i));
        }

    }

    void register_map::add_bound_identifier(const std::shared_ptr<variable> & var, int reg) {
        identifiers_map[var->get_identifier()] = std::make_shared<variable>("r"+std::to_string(reg));
    }

    std::shared_ptr<variable> register_map::get_identifier(const std::shared_ptr<variable> &var) {
        auto id = var->get_identifier();
        if(identifiers_map.contains(id))
            return identifiers_map[id];
        else
            return common_io_map[id];
    }

    void register_map::insert_common_io(const std::shared_ptr<variable>& var, int reg) {
        common_io_map[var->get_identifier()] = std::make_shared<variable>("r"+std::to_string(reg) + "c");
        common_io_map[var->get_identifier()]->set_variable_class({variable_input_type, true});
        used_common_io.insert(reg);
    }

}

