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
// limitations under the License.07/07/2021.
//

#include "passes/high_level/normalization_pass.hpp"

normalization_pass::normalization_pass() : pass_base<hl_ast_node>("normalization pass"){

}


std::shared_ptr<hl_ast_node> normalization_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);


    std::vector<std::shared_ptr<hl_ast_node>> normalized_body;

    for(auto &i: element->get_content()){
        std::shared_ptr<hl_ast_node> tmp_res = process_node_by_type_top(i);
        if(tmp_res != nullptr){
            normalized_body.insert(normalized_body.end(), additional_statements.begin(), additional_statements.end());
            additional_statements.clear();
            normalized_body.push_back(tmp_res);
        } else {
            normalized_body.push_back(i);
        }

    }

    retval->set_content(normalized_body);
    return retval;
}

std::shared_ptr<hl_ast_node> normalization_pass::process_node_by_type_top(std::shared_ptr<hl_ast_node> n) {
    std::shared_ptr<hl_ast_node> retval;
    if(n->node_type== hl_ast_node_type_expr){
        retval = process_node_exp(std::static_pointer_cast<hl_expression_node>(n));
    } else if(n->node_type == hl_ast_node_type_definition){
        retval = process_node_def(std::static_pointer_cast<hl_definition_node>(n));
    } else if(n->node_type == hl_ast_node_type_code_block){
        retval = process_code_block(n);
    }
    return retval;
}



std::vector<std::pair<side_to_normalize, std::shared_ptr<hl_ast_node>>> normalization_pass::process_node_expr_inner(std::shared_ptr<hl_expression_node> n) {
    std::vector<std::pair<side_to_normalize, std::shared_ptr<hl_ast_node>>> retval;
    if(n->is_unary()){
        if(n->get_rhs()->node_type==hl_ast_node_type_operand){
            retval.emplace_back(expr_normalized, n);
        } else{
            std::vector<std::pair<side_to_normalize , std::shared_ptr<hl_ast_node>>> extracted_exp = process_node_expr_inner(std::static_pointer_cast<hl_expression_node>(n->get_rhs()));
            std::shared_ptr<hl_expression_node> lower_level_expr  = produce_normalized_expression(n, extracted_exp);

            std::shared_ptr<hl_ast_operand> intermediate_def = extract_intermediate_expression(lower_level_expr);
            retval.emplace_back(expr_normalize_rhs, intermediate_def);
        }
    } else{
        if(n->get_rhs()->node_type==hl_ast_node_type_operand && n->get_lhs()->node_type==hl_ast_node_type_operand){
            retval.emplace_back(expr_normalized, n);
        } else {
            if(n->get_lhs()->node_type!=hl_ast_node_type_operand){
                std::vector<std::pair<side_to_normalize , std::shared_ptr<hl_ast_node>>> extracted_exp = process_node_expr_inner(std::static_pointer_cast<hl_expression_node>(n->get_lhs()));
                std::shared_ptr<hl_expression_node> lower_level_expr  = produce_normalized_expression(n, extracted_exp);

                std::shared_ptr<hl_ast_operand> intermediate_def = extract_intermediate_expression(lower_level_expr);
                retval.emplace_back(expr_normalize_lhs, intermediate_def);
            }
            if(n->get_rhs()->node_type!=hl_ast_node_type_operand) {
                std::vector<std::pair<side_to_normalize , std::shared_ptr<hl_ast_node>>> extracted_exp = process_node_expr_inner(std::static_pointer_cast<hl_expression_node>(n->get_rhs()));
                std::shared_ptr<hl_expression_node> lower_level_expr  = produce_normalized_expression(n, extracted_exp);

                std::shared_ptr<hl_ast_operand> intermediate_def = extract_intermediate_expression(lower_level_expr);
                retval.emplace_back(expr_normalize_rhs, intermediate_def);
            }
        }
    }

    return retval;
}

std::shared_ptr<hl_definition_node> normalization_pass::process_node_def(std::shared_ptr<hl_definition_node> n) {
    std::shared_ptr<hl_definition_node> retval = std::static_pointer_cast<hl_definition_node>(hl_ast_node::deep_copy(n));

    if(n->is_initialized()){
        if(n->get_scalar_initializer()->node_type == hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(
                    n->get_scalar_initializer());
            std::vector<std::pair<side_to_normalize , std::shared_ptr<hl_ast_node>>> intermediate = process_node_expr_inner(node);
            std::shared_ptr<hl_expression_node> tmp_ret =produce_normalized_expression(node, intermediate);
            retval->set_scalar_initializer(tmp_ret);
        }

    }

    return retval;
}

std::shared_ptr<hl_ast_operand>
normalization_pass::extract_intermediate_expression(std::shared_ptr<hl_expression_node> n) {

    variable_type_t type_rhs = std::static_pointer_cast<hl_ast_operand>(n->get_rhs())->get_type();
    c_types_t expr_type;

    if(!n->is_unary()){
        variable_type_t type_lhs = std::static_pointer_cast<hl_ast_operand>(n->get_lhs())->get_type();

        if(type_lhs == var_type_float_const && type_rhs == var_type_float_const){
            expr_type = c_type_float;
        } else if(type_lhs == var_type_int_const && type_rhs == var_type_int_const){
            expr_type = c_type_int;
        } else if(type_rhs == var_type_float_const){
            expr_type = c_type_float;
        } else if(type_lhs == var_type_float_const){
            expr_type = c_type_float;
        } else if(type_rhs == var_type_int_const){
            expr_type = c_type_int;
        } else {
            expr_type = c_type_float;
        }
    } else{
        if(type_rhs == var_type_float_const){
            expr_type = c_type_float;
        } else if(type_rhs == var_type_int_const){
            expr_type = c_type_int;
        } else {
            expr_type = c_type_float;
        }
    }

    std::string name = "intermediate_expr_" + std::to_string(intermediate_ordinal);
    intermediate_ordinal++;
    std::shared_ptr<variable> var = std::make_shared<variable>( name);
    std::shared_ptr<hl_definition_node> intermediate_def = std::make_shared<hl_definition_node>(name, expr_type, var);

    intermediate_def->set_scalar_initializer(std::static_pointer_cast<hl_expression_node>(n));

    additional_statements.push_back(intermediate_def);


    var = std::make_shared<variable>( name);
    std::shared_ptr<hl_ast_operand> ret = std::make_shared<hl_ast_operand>(var);

    return ret;
}

std::shared_ptr<hl_expression_node> normalization_pass::process_node_exp(std::shared_ptr<hl_expression_node> n) {
    if(n->get_type()==expr_assign){
        if(n->get_rhs()->node_type == hl_ast_node_type_operand){
            return n;
        } else{
            std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(hl_ast_node::deep_copy(n->get_rhs()));
            if(node->get_rhs()->node_type != hl_ast_node_type_operand || node->get_lhs()->node_type !=hl_ast_node_type_operand ){
                std::vector<std::pair<side_to_normalize , std::shared_ptr<hl_ast_node>>> intermediate = process_node_expr_inner(node);
                std::shared_ptr<hl_expression_node> tmp_ret =produce_normalized_expression(node, intermediate);
                n->set_rhs(tmp_ret);
                return n;
            } else{
                return n;
            }
        }
    } else{
        return n;
    }

}

std::shared_ptr<hl_expression_node>
normalization_pass::produce_normalized_expression(std::shared_ptr<hl_expression_node> original_node,
                                                  const std::vector<std::pair<side_to_normalize , std::shared_ptr<hl_ast_node>>>& extracted_intermediate) {

    std::shared_ptr<hl_expression_node> tmp_ret = std::static_pointer_cast<hl_expression_node>(hl_ast_node::deep_copy(original_node));
    for(auto &i: extracted_intermediate){
        switch (i.first) {
            case expr_normalized:
                return std::static_pointer_cast<hl_expression_node>(i.second);
                break;
            case expr_normalize_lhs:
                tmp_ret->set_lhs(i.second);
                break;
            case expr_normalize_rhs:
                tmp_ret->set_rhs(i.second);
                break;
        }
    }
    return tmp_ret;
}

std::shared_ptr<hl_ast_node> normalization_pass::process_code_block(std::shared_ptr<hl_ast_node> n) {
    std::vector<std::shared_ptr<hl_ast_node>> content = n->get_content();
    std::shared_ptr<hl_ast_node> return_statement = content.back();
    content.pop_back();
    for(auto &item:content){
        additional_statements.push_back(item);
    }
    return return_statement;
}

