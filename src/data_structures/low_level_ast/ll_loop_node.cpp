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
//

#include "data_structures/low_level_ast/ll_loop_node.hpp"



fcore::ll_loop_node::ll_loop_node() : ll_ast_node(ll_type_for_block) {
    loop_start = {"", 0};
    loop_advance = {true, 1};
    end_condition = {0, ">"};
}

void fcore::ll_loop_node::set_loop_start(loop_start_t start) {
    loop_start = std::move(start);
}

void fcore::ll_loop_node::set_loop_end(loop_end_t end) {
    end_condition = std::move(end);
}

void fcore::ll_loop_node::set_advance(loop_advance_t adv) {
    loop_advance = adv;
}

fcore::loop_start_t fcore::ll_loop_node::get_loop_start() {
    return loop_start;
}

fcore::loop_end_t fcore::ll_loop_node::get_loop_end() {
    return end_condition;
}

fcore::loop_advance_t fcore::ll_loop_node::get_advance() {
    return loop_advance;
}


nlohmann::json fcore::ll_loop_node::dump() {
    nlohmann::json retval = ll_ast_node::dump();
    nlohmann::json start;
    nlohmann::json end;
    nlohmann::json advance;

    start["variable"] = loop_start.variable;
    start["starting_value"] = loop_start.starting_value;
    end["end_count"] = end_condition.end_count;
    end["condition"] = end_condition.condition;
    advance["direction"] = loop_advance.direction;
    advance["loop_increment"] = loop_advance.loop_increment;

    retval["start"] = start;
    retval["end"] = end;
    retval["advance"] = advance;
    return retval;
}

