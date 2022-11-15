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


#ifndef FCORE_TOOLCHAIN_CONSTANTS_TRACKER_H
#define FCORE_TOOLCHAIN_CONSTANTS_TRACKER_H

#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>

#include "data_structures/high_level_ast/high_level_ast.hpp"

class constant{
public:
    int array_index;
    std::pair<int, int> validity_range;
    std::shared_ptr<hl_ast_operand> value;
};


class constants_tracker {
public:
    void add_constant(const std::string& s, std::shared_ptr<hl_ast_operand> op, int instr_idx);
    void add_exclusion(const std::string& s);
    bool is_constant(const std::string& s);
    bool is_excluded(const std::string& s);
    std::shared_ptr<hl_ast_operand> get_constant(const std::string& s, int instr_idx);
    void clear();

private:
    std::unordered_map<std::string, std::vector<constant>> constants_map;
    std::unordered_set<std::string> excluded_constants;
};


#endif //FCORE_TOOLCHAIN_CONSTANTS_TRACKER_H
