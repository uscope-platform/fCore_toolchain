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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.01/07/2021.
//

#include "data_structures/high_level_ast/hl_function_call_node.hpp"





hl_function_call_node::hl_function_call_node(std::string n, std::vector<std::shared_ptr<hl_ast_node>> a) : hl_ast_node(hl_ast_node_type_function_call){
    name = std::move(n);
    arguments = std::move(a);
}

std::string hl_function_call_node::pretty_print() {
    std::ostringstream ss;
    ss << name<<"( ";
    if(!arguments.empty()){
        for(const auto& item:arguments){
            if(item->node_type == hl_ast_node_type_expr){
                ss << std::static_pointer_cast<hl_expression_node>(item)->pretty_print();
            } else if(item->node_type == hl_ast_node_type_operand){
                hl_ast_operand op = *std::static_pointer_cast<hl_ast_operand>(item);
                std::string op_s = op;
                ss <<  op_s;
            }
            ss<<", ";
        }
    }
    std::string ret = ss.str();

    ret.pop_back();
    ret.pop_back();
    ret += " )";
    return ret;
}

bool operator==(const hl_function_call_node &lhs, const hl_function_call_node &rhs) {
    bool ret_val = true;

    ret_val &= lhs.name == rhs.name;

    ret_val &= hl_ast_node::compare_vectors(lhs.arguments, rhs.arguments);

    return ret_val;
}