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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.30/06/2021.
//

#include "ast/high_level/hl_ast_loop_node.h"

hl_ast_loop_node::hl_ast_loop_node() : hl_ast_node(hl_ast_node_type_loop){

}

std::string hl_ast_loop_node::pretty_print() {

    std::ostringstream ss;

    ss << "for (" << init_statement->pretty_print()<< "; ";
    ss << condition->pretty_print() << "; ";
    ss << iteration_expr->pretty_print() << ") {"<< std::endl;

    if(!content.empty()){
        for(const auto& item:content){
            ss << item->pretty_print() << ";" << std::endl;
        }
    }
    ss<< "}";
    return ss.str();
}

bool operator==(const hl_ast_loop_node &lhs, const hl_ast_loop_node &rhs) {
    bool ret_val = true;

    ret_val &= hl_ast_node::compare_content_by_type( lhs.init_statement, rhs.init_statement);
    ret_val &= hl_ast_node::compare_content_by_type( lhs.condition, rhs.condition);
    ret_val &= hl_ast_node::compare_content_by_type( lhs.iteration_expr, rhs.iteration_expr);

    ret_val &= hl_ast_node::compare_vectors(lhs.content, rhs.content);

    return ret_val;
}
