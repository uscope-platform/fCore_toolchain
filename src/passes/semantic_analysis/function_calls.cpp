

//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#include "passes/semantic_analysis/function_calls.hpp"


fcore::function_calls_checks::function_calls_checks(): type_check_base("function calls checks")  {
}

void fcore::function_calls_checks::run_check(const std::shared_ptr<hl_code_block> &element) {
    std::unordered_map<std::string, std::vector<c_types_t>> signatures_map;

    // First pass: function definition mapping
    for(const auto &f:element->get_content()) {
        if(f->node_type == hl_ast_node_type_function_def) {
            const auto def = std::static_pointer_cast<hl_function_def_node>(f);
            std::vector<c_types_t> types;
            for(auto &p : def->get_parameters_list()) {
               types.push_back(p->get_type());
            }
            signatures_map[def->get_name()] = types;
        }
    }

    //  Second pass: arguments checking;
    int i = 0;
}
