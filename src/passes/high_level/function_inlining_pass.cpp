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
            std::shared_ptr<hl_ast_node> copied_node = hl_ast_node::deep_copy(i);
            body.push_back(substitute_arguments(copied_node,arguments_map));
        }
        inlined_code->set_content(body);

        if(f_def->get_return() != nullptr){
            inlined_code->add_content(substitute_arguments(hl_ast_node::deep_copy(f_def->get_return()), arguments_map));
        }


        ret_val = inlined_code;
    }
    return ret_val;
}


 std::shared_ptr<hl_ast_node> function_inlining_pass::substitute_arguments(const std::shared_ptr<hl_ast_node> &statement,
                                                                           std::unordered_map<std::string, std::shared_ptr<hl_ast_node>>& parameters) {
    std::shared_ptr<hl_ast_node> retval = statement;
    if (statement->node_type == hl_ast_node_type_expr){
        return substitute_expression_arguments(std::static_pointer_cast<hl_expression_node>(statement), parameters);
    } else if (statement->node_type == hl_ast_node_type_definition){
        return substitute_definition_arguments(std::static_pointer_cast<hl_definition_node>(statement), parameters);
    } else if(statement->node_type == hl_ast_node_type_operand){
        return substitute_operand_arguments(std::static_pointer_cast<hl_ast_operand>(statement), parameters);
    } else if(statement->node_type == hl_ast_node_type_conditional){
        return substitute_conditional_arguments(std::static_pointer_cast<hl_ast_conditional_node>(statement), parameters);
    } else if(statement->node_type == hl_ast_node_type_loop){
        return substitute_loop_arguments(std::static_pointer_cast<hl_ast_loop_node>(statement), parameters);
    }
     return retval;
}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_loop_arguments(const std::shared_ptr<hl_ast_loop_node> &statement,
                                                  std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> &parameters) {

    std::vector<std::shared_ptr<hl_ast_node>> tmp_vect;
    for(auto &item: statement->get_loop_content()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_loop_content(tmp_vect);

    statement->set_init_statement(std::static_pointer_cast<hl_definition_node>(substitute_arguments(statement->get_init_statement(), parameters)));
    statement->set_condition(std::static_pointer_cast<hl_expression_node>(substitute_arguments(statement->get_condition(), parameters)));
    statement->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(substitute_arguments(statement->get_init_statement(), parameters)));

    return statement;
}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_conditional_arguments(const std::shared_ptr<hl_ast_conditional_node> &statement,
                                                         std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> &parameters) {

    std::vector<std::shared_ptr<hl_ast_node>> tmp_vect;
    for(auto &item: statement->get_if_block()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_if_block(tmp_vect);

    tmp_vect.clear();
    for(auto &item: statement->get_else_block()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_else_block(tmp_vect);

    statement->set_condition(substitute_arguments(statement->get_condition(), parameters));
    return statement;
}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_expression_arguments(const std::shared_ptr<hl_expression_node> &statement,
                                                        std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> &parameters) {

    std::shared_ptr<hl_ast_node> tmp = statement->get_lhs();
    statement->set_lhs(substitute_arguments(tmp, parameters));
    tmp = statement->get_rhs();
    statement->set_rhs(substitute_arguments(tmp, parameters));
    return statement;
}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_definition_arguments(const std::shared_ptr<hl_definition_node> &statement,
                                                        std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> &parameters) {
    std::shared_ptr<hl_ast_node> tmp = statement->get_scalar_initializer();
    statement->set_scalar_initializer(
            std::static_pointer_cast<hl_expression_node>(substitute_arguments(tmp, parameters)));

    std::vector<std::shared_ptr<hl_ast_node>> tmp_vect;
    for(auto &item: statement->get_array_index()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_array_index(tmp_vect);

    tmp_vect.clear();
    for(auto &item: statement->get_array_initializer()){
        tmp_vect.push_back(substitute_arguments(item, parameters));
    }
    statement->set_array_initializer(tmp_vect);

    return statement;
}

std::shared_ptr<hl_ast_node>
function_inlining_pass::substitute_operand_arguments(const std::shared_ptr<hl_ast_operand> &statement,
                                                     std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> &parameters) {

    std::shared_ptr<hl_ast_operand> p = std::static_pointer_cast<hl_ast_operand>(parameters[statement->get_name()]);
    std::vector<std::shared_ptr<hl_ast_node>> tmp_vect;

    if(p != nullptr){
        for(auto &item: p->get_array_index()){
            tmp_vect.push_back(substitute_arguments(item, parameters));
        }
        statement->set_array_index(tmp_vect);

       statement->set_variable(p->get_variable());
    }

    return statement;
}

