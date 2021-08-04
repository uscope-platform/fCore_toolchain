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


#include "passes/high_level/inline_constant_extraction.hpp"

inline_constant_extraction::inline_constant_extraction() : pass_base<hl_ast_node>("inline constant extraction pass"){
    n_var = 0;
}

std::shared_ptr<hl_ast_node>
inline_constant_extraction::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    for(auto item:element->get_content()){
        if(item->node_type == hl_ast_node_type_definition){
            std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(item);
            if(node->get_initializer()->node_type == hl_ast_node_type_expr){
                std::shared_ptr<hl_expression_node> expr = std::static_pointer_cast<hl_expression_node>(node->get_initializer());
                std::vector<std::shared_ptr<hl_ast_node>> res = process_node(expr);
                node->set_initializer(res[0]);
                if(res.size()>1)
                    new_content.insert(new_content.end(), res.begin()+1, res.end());
                new_content.push_back(node);
            } else{
                new_content.push_back(item);
            }
        } else if(item->node_type == hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(item);
            if(node->get_type()==expr_assign){
                std::shared_ptr<hl_ast_node> rhs = node->get_rhs();
                if(rhs->node_type == hl_ast_node_type_operand){
                    new_content.push_back(item);
                } else{
                    std::shared_ptr<hl_expression_node> n = std::static_pointer_cast<hl_expression_node>(rhs);
                    std::vector<std::shared_ptr<hl_ast_node>> res = process_node(n);
                    if(res.size()>1){
                        new_content.push_back(res[1]);
                        node->set_rhs(res[0]);

                    }
                    new_content.push_back(item);
                }

            } else{
                throw std::runtime_error("INTERNAL ERROR: non assignment top level expressions should not reach inline constant extraction pass");
            }
        } else{
            new_content.push_back(item);
        }
    }
    retval->set_content(new_content);
    return retval;
}




std::vector<std::shared_ptr<hl_ast_node>>
inline_constant_extraction::process_node(std::shared_ptr<hl_expression_node> &element) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;
    if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        std::shared_ptr<hl_ast_operand> rhs = std::static_pointer_cast<hl_ast_operand>(node->get_rhs());
        std::vector<std::shared_ptr<hl_ast_node>> rhs_result = process_expr_side(rhs);
        node->set_rhs(rhs_result[0]);
        if(rhs_result.size()==2)
            retval.push_back(rhs_result[1]);
        if(!node->is_unary()){
            std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(node->get_lhs());
            std::vector<std::shared_ptr<hl_ast_node>> lhs_result = process_expr_side(lhs);
            node->set_lhs(lhs_result[0]);
            if(lhs_result.size()==2)
                retval.push_back(lhs_result[1]);
        }
        retval.insert(retval.begin(), node);
    } else{
        retval.push_back(element);
    }
    return retval;
}


std::vector<std::shared_ptr<hl_ast_node>>
inline_constant_extraction::process_expr_side(std::shared_ptr<hl_ast_operand>& element) {

    std::vector<std::shared_ptr<hl_ast_node>> retval;

    if(element->get_type() == var_type_float_const) {
        std::string var_name = "inlined_variable_"+std::to_string(n_var);
        std::shared_ptr<variable> var = std::make_shared<variable>( var_name);
        std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>(var_name, c_type_float, var);
        n_var++;
        def->set_initializer(element);


        var = std::make_shared<variable>(var_name);
        std::shared_ptr<hl_ast_operand> var_op = std::make_shared<hl_ast_operand>(var);

        retval.insert(retval.end(), {var_op, def});
    } else if(element->get_type() == var_type_int_const){
        std::string var_name = "inlined_variable_"+std::to_string(n_var);
        std::shared_ptr<variable> var = std::make_shared<variable>( var_name);
        std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>(var_name, c_type_int, var);
        n_var++;
        def->set_initializer(element);

        var = std::make_shared<variable>( var_name);
        std::shared_ptr<hl_ast_operand> var_op = std::make_shared<hl_ast_operand>(var);

        retval.insert(retval.end(), {var_op, def});
    } else{
        retval.push_back(element);
    }

    return retval;
}


