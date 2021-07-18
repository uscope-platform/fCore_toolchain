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


#include "passes/high_level/dead_variable_elimination.hpp"

dead_variable_elimination::dead_variable_elimination() : pass_base<hl_ast_node>("dead variable elimination"){

}

std::shared_ptr<hl_ast_node> dead_variable_elimination::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval =  std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> new_body;

    std::map<std::string, bool> defined_variables;
    for(const auto& item:element->get_content()){

        if(item->node_type == hl_ast_node_type_definition){
            std::shared_ptr<hl_definition_node> node =std::static_pointer_cast<hl_definition_node>(item);
            if(node->is_initialized())
                defined_variables.insert(std::make_pair(node->get_name(), true));
        } else if(item->node_type == hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> node =std::static_pointer_cast<hl_expression_node>(item);
            if(node->get_type() == expr_assign){
                std::shared_ptr<hl_definition_node> lhs = std::static_pointer_cast<hl_definition_node>(node->get_lhs());
                defined_variables.insert(std::make_pair(lhs->get_name(), true));
            }
        }
    }
    for(const auto& item:element->get_content()){

        if(item->node_type == hl_ast_node_type_definition){
            std::shared_ptr<hl_definition_node> node =std::static_pointer_cast<hl_definition_node>(item);
            if(defined_variables.count(node->get_name())>0){
                new_body.push_back(item);
            }
        } else {
            new_body.push_back(item);
        }
    }

    retval->set_content(new_body);
    return retval;
}
