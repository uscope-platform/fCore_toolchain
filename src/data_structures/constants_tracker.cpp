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


#include "data_structures/constants_tracker.h"

#include <utility>



void constants_tracker::add_constant(const std::string &s, std::shared_ptr<hl_ast_operand> op, int instr_idx,
                                     int array_idx) {

    if(constants_map.contains(s)){
        constants_map[s][array_idx][constants_map[s].size()-1].validity_range.second = instr_idx;
    }
    constant c;
    c.value = std::move(op);
    c.validity_range = {instr_idx, -1};
    constants_map[s][array_idx].push_back(c);
}

void constants_tracker::add_constant(const std::string &s, std::shared_ptr<hl_ast_operand> op, int instr_idx) {
    add_constant(s, std::move(op), instr_idx, 0);
}

void constants_tracker::add_exclusion(const std::string &s) {
    excluded_constants.insert(s);
}

bool constants_tracker::is_constant(const std::string &s) {
    return is_constant(s,0);
}

bool constants_tracker::is_constant(const std::string &s, int array_idx) {
    if(!constants_map.contains(s)) return false;
    return constants_map[s].contains(array_idx);
}


bool constants_tracker::is_excluded(const std::string &s) {
    return excluded_constants.contains(s);
}

std::shared_ptr<hl_ast_operand> constants_tracker::get_constant(const std::string &s, int instr_idx) {
    return get_constant(s,instr_idx,0);
}

std::shared_ptr<hl_ast_operand> constants_tracker::get_constant(const std::string &s, int instr_idx, int array_idx) {
    for(auto &item:constants_map[s][array_idx]){
        if(instr_idx>=item.validity_range.first && (instr_idx<item.validity_range.second || item.validity_range.second == -1)) return item.value;
    }
    throw std::runtime_error("Error: tracked constant not found");
}

void constants_tracker::clear() {
    constants_map.clear();
    excluded_constants.clear();
}
