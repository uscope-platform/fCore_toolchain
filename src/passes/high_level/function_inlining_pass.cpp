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

#include "passes/high_level/function_inlining_pass.hpp"


function_inlining_pass::function_inlining_pass() : pass_base<hl_ast_node>("function inlining pass"){

}


void function_inlining_pass::set_functions_map(
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> map) {
    functions_map = std::move(map);
}

std::shared_ptr<hl_ast_node> function_inlining_pass::process_leaf(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = element;
    if(element->node_type == hl_ast_node_type_function_call){
        std::shared_ptr<hl_function_call_node> f_call = std::static_pointer_cast<hl_function_call_node>(element);
        std::shared_ptr<hl_function_def_node> f_def = functions_map->at(f_call->get_name());

        // MAP ARGUMENTS OF  THE CALL WITH its name
        int idx = 0;
        std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> arguments_map;
        for(const auto& arg: f_call->get_arguments()){
            std::string arg_name = f_def->get_parameters_list()[idx]->get_name();
            arguments_map[arg_name] = hl_ast_node::deep_copy(arg);
            ++idx;

        }

        std::shared_ptr<hl_ast_node> inlined_code = std::make_shared<hl_ast_node>(hl_ast_node_type_code_block);

        // SUBSTITUTE THE ARGUMENTS OF THE CALL WITHIN THE FUNCTION BODY
        std::vector<std::shared_ptr<hl_ast_node>> body;


        for(auto &i: f_def->get_body()){
            body.push_back(substitute_arguments(hl_ast_node::deep_copy(i),arguments_map));
        }
        inlined_code->set_content(body);
        inlined_code->add_content(substitute_arguments(hl_ast_node::deep_copy(f_def->get_return()), arguments_map));

        ret_val = inlined_code;
    }
    return ret_val;
}


 std::shared_ptr<hl_ast_node> function_inlining_pass::substitute_arguments(const std::shared_ptr<hl_ast_node> &statement,
                                                                           std::unordered_map<std::string, std::shared_ptr<hl_ast_node>>& parameters) {
    std::shared_ptr<hl_ast_node> retval = statement;
    if (statement->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> item = std::static_pointer_cast<hl_expression_node>(statement);

        std::shared_ptr<hl_ast_node> tmp = item->get_lhs();
        item->set_lhs(substitute_arguments(tmp, parameters));
        tmp = item->get_rhs();
        item->set_rhs(substitute_arguments(tmp, parameters));

    } else if (statement->node_type == hl_ast_node_type_definition){
        std::shared_ptr<hl_definition_node> item = std::static_pointer_cast<hl_definition_node>(statement);

        std::shared_ptr<hl_ast_node> tmp = item->get_initializer();
        item->set_initializer(std::static_pointer_cast<hl_expression_node>(substitute_arguments(tmp, parameters)));

    } else if(statement->node_type == hl_ast_node_type_operand){
        std::shared_ptr<hl_ast_operand> s = std::static_pointer_cast<hl_ast_operand>(statement);
        std::string param_name = s->get_name();
        if(parameters.count(param_name)){

            return parameters[param_name];
        }
    }
     return retval;
}

