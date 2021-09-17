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


#include "data_structures/low_level_ast/ll_instruction_node.hpp"

ll_instruction_node::ll_instruction_node(isa_instruction_type t) : ll_ast_node(ll_type_instr) {
    instruction_type = t;
}

ll_instruction_node::ll_instruction_node(const ll_instruction_node &old_obj) {

    instruction_type = old_obj.instruction_type;
    opcode = old_obj.opcode;
}

isa_instruction_type ll_instruction_node::get_type() {
    return instruction_type;
}

bool ll_instruction_node::is_terminal() {
    return true;
}

bool operator==(const ll_instruction_node &lhs, const ll_instruction_node &rhs) {
    bool retval = true;
    retval &= lhs.instruction_type == rhs.instruction_type;
    retval &= lhs.opcode == rhs.opcode;

    return retval;
}
