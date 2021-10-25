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
       std::shared_ptr<hl_ast_node> tmp_res = process_node_by_type(i);
       if(!additional_statements.empty()) {
           normalized_body.insert(normalized_body.end(), additional_statements.begin(), additional_statements.end());
           additional_statements.clear();
       }
       normalized_body.push_back(tmp_res);
    }

    retval->set_content(normalized_body);
    return retval;
}


bool normalization_pass::is_normal(const std::shared_ptr<hl_ast_node>& element) {

    if(element->node_type== hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> expr = std::static_pointer_cast<hl_expression_node>(element);
        if(!expr->is_unary()){
            if(expr->get_lhs()->node_type != hl_ast_node_type_operand) return false;
        }
        if(expr->get_rhs()->node_type != hl_ast_node_type_operand) return false;

        return true;
    } else if(element->node_type == hl_ast_node_type_definition){
        std::shared_ptr<hl_definition_node> def = std::static_pointer_cast<hl_definition_node>(element);
        if(def->is_initialized())
            return is_normal(def->get_scalar_initializer());
        else
            return true;
    } else if(element->node_type == hl_ast_node_type_code_block){
        return false;
    } else if(element->node_type == hl_ast_node_type_operand){
        return true;
    } else{
        throw std::runtime_error("ERROR: unexpected block reached the normalization pass");
    }
}

norm_pair_t normalization_pass::process_node_by_type(std::shared_ptr<hl_ast_node> n) {
    if(is_normal(n)){
        return n;
    }
    std::shared_ptr<hl_ast_node> retval;
    if(n->node_type== hl_ast_node_type_expr){
        retval = process_node_exp(std::static_pointer_cast<hl_expression_node>(n));
    } else if(n->node_type == hl_ast_node_type_definition){
        retval = process_node_def(std::static_pointer_cast<hl_definition_node>(n));
    }
    return retval;
}


norm_pair_t normalization_pass::process_node_exp(std::shared_ptr<hl_expression_node> n) {
    std::shared_ptr<hl_expression_node> normalized_expression;
    std::vector<std::shared_ptr<hl_ast_node>> extracted_expressions;
    norm_pair_t ret_val = std::make_pair(normalized_expression, extracted_expressions);



    if(!n->is_unary()){
        if(!is_normal(n->get_lhs())){
            norm_pair_t np_l = process_node_by_type(n->get_lhs());
        }
    }

    if(!is_normal(n->get_rhs())){

    }

    return ret_val;
}


norm_pair_t normalization_pass::process_node_def(const std::shared_ptr<hl_definition_node>& n) {
    std::vector<std::shared_ptr<hl_ast_node>> extracted_expressions;



    if(n->is_initialized()){
        if(!is_normal(n->get_scalar_initializer())) {
            norm_pair_t np = process_node_by_type(n->get_scalar_initializer());
            n->set_scalar_initializer(np.first);
            extracted_expressions = np.second;
        }
    }

    return std::make_pair(n, extracted_expressions);
}
