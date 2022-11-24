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
        if(constants_map[s].contains(array_idx)){
            constants_map[s][array_idx].back().validity_range.second = instr_idx;
        }
    }
    constant c;
    c.value = std::move(op);
    c.array_index = array_idx;
    c.validity_range = {instr_idx, -1};
    constants_map[s][array_idx].push_back(c);
    purge_map[s][array_idx] = false;
}

void constants_tracker::add_constant(const std::string &s, std::shared_ptr<hl_ast_operand> op, int instr_idx) {
    add_constant(s, std::move(op), instr_idx, 0);
}


bool constants_tracker::is_constant(const std::string &s, int instr_idx) {
    return is_constant(s,instr_idx,0);
}

bool constants_tracker::is_constant(const std::string &s, int instr_idx, int array_idx) {
    if(!constants_map.contains(s)) return false;
    if(!constants_map[s].contains(array_idx)) return false;
    for(auto &item:constants_map[s][array_idx]){
        if(instr_idx>=item.validity_range.first && (instr_idx<item.validity_range.second || item.validity_range.second == -1)) return true;
    }
    return false;
}


bool constants_tracker::is_excluded(const std::string &s) {
    return excluded_constants.contains(s);
}

std::shared_ptr<hl_ast_operand> constants_tracker::get_constant(const std::string &s, int instr_idx) {
    return get_constant(s,instr_idx,0);
}

std::shared_ptr<hl_ast_operand> constants_tracker::get_constant(const std::string &s, int instr_idx, int array_idx) {
    for(auto &item:constants_map[s][array_idx]){
        if(instr_idx>=item.validity_range.first && (instr_idx<item.validity_range.second || item.validity_range.second == -1)) {
            purge_map[s][array_idx] = true;
            return item.value;
        }
    }
    throw std::runtime_error("Error: tracked constant not found");
}

void constants_tracker::clear() {
    constants_map.clear();
    excluded_constants.clear();
}

void constants_tracker::terminate_constant_range(const std::string &s, int instr_idx) {
    terminate_constant_range(s, instr_idx, 0);
}

void constants_tracker::terminate_constant_range(const std::string &s, int instr_idx, int array_idx) {

    if(constants_map.contains(s)){
        if(constants_map[s].contains(array_idx)){
            constants_map[s][array_idx].back().validity_range.second = instr_idx;
            return;
        } else{
            throw std::runtime_error("Error: attempted termination of a range belonging to a non constant array member");
        }
    } else{
        throw std::runtime_error("Error: constant whose range need termination not found");
    }

}

void constants_tracker::terminate_all_constant_ranges(const std::string &s, int instr_idx) {

    if(constants_map.contains(s)){
        for(auto&range:constants_map[s]){
            if(range.second.back().validity_range.second == -1){
                range.second.back().validity_range.second = instr_idx;
            }
        }
    }
    throw std::runtime_error("Error: constant whose range need termination not found");
}

bool constants_tracker::needs_purging(const std::string &s) {
    return needs_purging(s, 0);
}

bool constants_tracker::needs_purging(const std::string &s, int array_idx) {
    return purge_map[s][array_idx];
}





std::string multidimentional_constants_map::stringify_index(const int& v) {
    std::string ret;
    for(auto &item:{v}){
        ret += std::to_string(item);
    }

    return ret;
}


bool multidimentional_constants_map::contains(const int &i) {
    return inner_map.contains(stringify_index(i));
}

void multidimentional_constants_map::add(const int &i, std::vector<constant> c) {
    inner_map[stringify_index(i)] = std::move(c);
}

void multidimentional_constants_map::push_back(const int &i, const constant &c) {
    inner_map[stringify_index(i)].push_back(c);
}

std::vector<constant> multidimentional_constants_map::get(const int &i) {
    return inner_map[stringify_index(i)];
}

