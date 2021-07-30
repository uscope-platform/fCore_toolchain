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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.09/07/2021.
//

#include "passes/high_level/hl_variable_mapping.hpp"

hl_variable_mapping::hl_variable_mapping(std::shared_ptr<variable_map> &v) : pass_base<hl_ast_node>("high level variable mapping"){
    var_map = v;
}

std::shared_ptr<hl_ast_node> hl_variable_mapping::process_global(std::shared_ptr<hl_ast_node> element) {
    for(auto &i:element->get_content()){
        process_var(i);
    }
    return element;
}

void hl_variable_mapping::process_var(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type == hl_ast_node_type_definition) {
        std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(element);
        if (node->is_initialized()) process_var(node->get_initializer());
        std::shared_ptr<variable> var = std::make_shared<variable>(node->get_name());
        var_map->insert(node->get_name(), var);
    } else if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        if (node->get_lhs() != nullptr) process_var(node->get_lhs());
        if (node->get_rhs() != nullptr) process_var(node->get_rhs());

    } else if(element->node_type == hl_ast_node_type_operand){
        std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(element);
        std::shared_ptr<variable> var;
        std::string var_name;
        if(op->get_type() == var_type_int_const){
            var = std::make_shared<variable>("constant", op->get_int_value());
        } else if(op->get_type()==var_type_float_const){
            var = std::make_shared<variable>("constant", op->get_float_val());
        } else if(op->get_type()==var_type_scalar || op->get_type() == var_type_array){
            var_name = op->get_name();
            var = std::make_shared<variable>(var_name);
        }
        var_map->insert(var_name, var);
    }
}
