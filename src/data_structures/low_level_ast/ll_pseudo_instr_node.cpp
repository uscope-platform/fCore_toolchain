// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#include "data_structures/low_level_ast/ll_pseudo_instr_node.hpp"



ll_pseudo_instr_node::ll_pseudo_instr_node(std::string op, std::vector<std::shared_ptr<variable>> args)
: ll_instruction_node(isa_pseudo_instruction){
 opcode = std::move(op);
 arguments = std::move(args);
}

bool operator==(const ll_pseudo_instr_node &lhs, const ll_pseudo_instr_node &rhs) {
    bool retval = true;

    if(lhs.arguments.empty() && rhs.arguments.empty()){
        retval &= true;
    } else if(lhs.arguments.empty() || rhs.arguments.empty()){
        retval = false;
    } else {
        bool args_equal = true;
        args_equal &= lhs.arguments.size() == rhs.arguments.size();
        for (int i = 0; i < lhs.arguments.size(); i++) {
            args_equal &= *lhs.arguments[i] == *rhs.arguments[i];
        }
        retval &= args_equal;
    }
    return retval;
}

int ll_pseudo_instr_node::instruction_count() {
    return 1;
}
