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

#include "data_structures/low_level_ast/ll_ast_pragma.hpp"



fcore::ll_ast_pragma::ll_ast_pragma() : ll_ast_node(ll_type_pragma){

}

fcore::ll_ast_pragma::ll_ast_pragma(std::string str): ll_ast_node(ll_type_pragma) {
    directive = std::move(str);
}

void fcore::ll_ast_pragma::print() {
    std::cout<<"PRAGMA -> " + directive;
}

std::string fcore::ll_ast_pragma::get_directive() {
    return directive;
}

bool fcore::ll_ast_pragma::is_terminal() {
    return true;
}


nlohmann::json fcore::ll_ast_pragma::dump() {
    nlohmann::json retval = ll_ast_node::dump();
    retval["directive"] = directive;
    return retval;
}
