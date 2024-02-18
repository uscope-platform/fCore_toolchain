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
// limitations under the License.30/06/2021.
//

#include "data_structures/high_level_ast/hl_ast_loop_node.h"

fcore::hl_ast_loop_node::hl_ast_loop_node() : hl_ast_node(hl_ast_node_type_loop){

}

std::string fcore::hl_ast_loop_node::pretty_print() {

    std::ostringstream ss;

    ss << "for (" << init_statement->pretty_print()<< "; ";
    ss << condition->pretty_print() << "; ";
    ss << iteration_expr->pretty_print() << ") {"<< std::endl;

    if(!loop_content.empty()){
        for(const auto& item:loop_content){
            ss << item->pretty_print() << ";" << std::endl;
        }
    }
    ss<< "}";
    return ss.str();
}

nlohmann::json fcore::hl_ast_loop_node::dump() {
    nlohmann::json retval = hl_ast_node::dump();
    retval["loop_content"] = hl_ast_node::dump_array(loop_content);
    retval["iteration_expr"] = iteration_expr->dump();
    retval["condition"] = condition->dump();
    retval["init_statement"] = init_statement->dump();

    return retval;
}
