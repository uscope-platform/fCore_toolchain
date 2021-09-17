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

#include "data_structures/low_level_ast/ll_intercalated_const_instr_node.hpp"

ll_intercalated_const_instr_node::ll_intercalated_const_instr_node(float constant) : ll_instruction_node(isa_intercalated_constant){
    intercalated_constant = constant;
}

uint32_t ll_intercalated_const_instr_node::emit() {
    uint32_t  raw_instr = 0;
    float constant = intercalated_constant;
    memcpy(&raw_instr, &constant, sizeof(raw_instr));
    return raw_instr;
}

void ll_intercalated_const_instr_node::print() {
}

int ll_intercalated_const_instr_node::instruction_count() {
    return 1;
}

bool operator==(const ll_intercalated_const_instr_node &lhs, const ll_intercalated_const_instr_node &rhs) {
    bool retval = true;

    retval &= lhs.intercalated_constant == rhs.intercalated_constant;
    retval &= rhs.opcode == lhs.opcode;
    return retval;
}
