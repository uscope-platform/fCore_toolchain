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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.05/07/2021.
//

#include "ast/low_level/ll_ast_pragma.hpp"



ll_ast_pragma::ll_ast_pragma() : ll_ast_node(ll_type_pragma){

}

ll_ast_pragma::ll_ast_pragma(std::string str): ll_ast_node(ll_type_pragma) {
    directive = std::move(str);
}

void ll_ast_pragma::print() {
    std::cout<<"PRAGMA -> " + directive;
}

std::string ll_ast_pragma::get_directive() {
    return directive;
}

bool ll_ast_pragma::is_terminal() {
    return true;
}

bool operator==(const ll_ast_pragma &lhs, const ll_ast_pragma &rhs) {
    bool retval = true;
    retval &= lhs.directive == rhs.directive;
    return retval;
}
