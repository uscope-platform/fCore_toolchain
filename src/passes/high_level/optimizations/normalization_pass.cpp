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

#include "passes/high_level/optimizations/normalization_pass.hpp"

namespace fcore{

    normalization_pass::normalization_pass() : pass_base("normalization pass"){
    }


    std::shared_ptr<ast_code_block> normalization_pass::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {
        auto retval = std::make_shared<ast_code_block>();

        std::vector<std::shared_ptr<ast_node>> normalized_body;

        for(auto &i: element->get_content()){
            norm_pair_t norm_pair = process_node_by_type(i);
            normalized_body.insert(normalized_body.end(), norm_pair.second.begin(), norm_pair.second.end());
            normalized_body.push_back(norm_pair.first);
        }

        retval->set_content(normalized_body);
        return retval;
    }


    bool normalization_pass::is_normal(const std::shared_ptr<ast_node>& element) {

        if(element->node_type== hl_ast_node_type_expr){
            std::shared_ptr<ast_expression> expr = std::static_pointer_cast<ast_expression>(element);
            if(!expr->is_immediate()){
                if(auto lhs = expr->get_lhs())
                    if(lhs.value()->node_type != hl_ast_node_type_operand) return false;

                if(expr->get_rhs()->node_type != hl_ast_node_type_operand) return false;
            }

            return true;
        } else if(element->node_type == hl_ast_node_type_definition){
            std::shared_ptr<ast_definition> def = std::static_pointer_cast<ast_definition>(element);
            if(def->is_initialized())
                return is_normal(def->get_scalar_initializer());
            else
                return true;
        } else if(element->node_type == hl_ast_node_type_code_block){
            return false;
        } else if(element->node_type == hl_ast_node_type_operand){
            return true;
        } else{
            throw std::runtime_error("unexpected block reached the normalization pass");
        }
    }

    norm_pair_t normalization_pass::process_node_by_type(std::shared_ptr<ast_node> n) {
        if(n->node_type== hl_ast_node_type_expr){
            return process_node_exp(std::static_pointer_cast<ast_expression>(n));
        } else if(n->node_type == hl_ast_node_type_definition){
            return process_node_def(std::static_pointer_cast<ast_definition>(n));
        }
        std::vector<std::shared_ptr<ast_node>> vect = {};
        return std::make_pair(n,vect);
    }


    norm_pair_t normalization_pass::process_node_exp(const std::shared_ptr<ast_expression>& n) {
        std::shared_ptr<ast_expression> normalized_expression = n;
        std::vector<std::shared_ptr<ast_node>> extracted_expressions = {};
        norm_pair_t ret_val = std::make_pair(normalized_expression, extracted_expressions);

        if(is_normal(n)){
            return ret_val;
        }

        std::shared_ptr<ast_node> rhs = n->get_rhs();

        norm_pair_t np_l;
        norm_pair_t np_r = process_node_by_type(rhs);



        if(auto lhs = n->get_lhs()) {
            np_l = process_node_by_type(lhs.value());
        };


        if(!np_l.second.empty()) {
            ret_val.second.insert(ret_val.second.end(), np_l.second.begin(), np_l.second.end());
        }

        if(!np_r.second.empty()) {
            ret_val.second.insert(ret_val.second.end(), np_r.second.begin(), np_r.second.end());
        }

        if(n->get_type() == ast_expression::ASSIGN){
            std::static_pointer_cast<ast_expression>(ret_val.first)->set_lhs(np_l.first);
            std::static_pointer_cast<ast_expression>(ret_val.first)->set_rhs(np_r.first);
            n->set_rhs(np_r.first);
            return ret_val;
        }

        if(rhs->node_type == hl_ast_node_type_expr){
            std::string int_exp = "intermediate_expression_"+std::to_string(intermediate_ordinal);
            std::shared_ptr<variable> var = std::make_shared<variable>(int_exp);
            std::shared_ptr<ast_definition> def = std::make_shared<ast_definition>(
                    int_exp,
                    get_expression_type(std::static_pointer_cast<ast_expression>(np_r.first)),
                    var
            );
            def->set_scalar_initializer(np_r.first);
            ++intermediate_ordinal;
            ret_val.second.push_back(def);
            std::shared_ptr<ast_operand> op = std::make_shared<ast_operand>(var);
            std::static_pointer_cast<ast_expression>(ret_val.first)->set_rhs(op);
        }

        if(auto lhs = n->get_lhs()) {
            if(lhs.value()->node_type == hl_ast_node_type_expr){
                std::string int_exp = "intermediate_expression_"+std::to_string(intermediate_ordinal);
                std::shared_ptr<variable> var = std::make_shared<variable>(int_exp);
                std::shared_ptr<ast_definition> def = std::make_shared<ast_definition>(
                        int_exp,
                        get_expression_type(std::static_pointer_cast<ast_expression>(np_l.first)),
                        var
                );
                ++intermediate_ordinal;
                def->set_scalar_initializer(np_l.first);
                ret_val.second.push_back(def);
                std::shared_ptr<ast_operand> op = std::make_shared<ast_operand>(var);
                std::static_pointer_cast<ast_expression>(ret_val.first)->set_lhs(op);
            }
        }
        return ret_val;
    }



    norm_pair_t normalization_pass::process_node_def(const std::shared_ptr<ast_definition>& n) {
        std::vector<std::shared_ptr<ast_node>> extracted_expressions;

        if(n->is_initialized()){
            if(!is_normal(n->get_scalar_initializer())) {
                norm_pair_t np = process_node_by_type(n->get_scalar_initializer());
                n->set_scalar_initializer(np.first);
                extracted_expressions = np.second;
            }
        }

        return std::make_pair(n, extracted_expressions);
    }

    c_types_t normalization_pass::get_expression_type(std::shared_ptr<ast_expression> expr) {

        variable_type_t type_rhs = std::static_pointer_cast<ast_operand>(expr->get_rhs())->get_type();
        c_types_t expr_type;


        if(auto lhs = expr->get_lhs()){

            variable_type_t type_lhs = std::static_pointer_cast<ast_operand>(lhs.value())->get_type();

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
        return expr_type;
    }

}