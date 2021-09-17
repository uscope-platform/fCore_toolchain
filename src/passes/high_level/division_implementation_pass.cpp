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
// limitations under the License.05/07/2021.
//

#include "passes/high_level/division_implementation_pass.hpp"


division_implementation_pass::division_implementation_pass() : pass_base<hl_ast_node>("division implementation pass"){

}

std::shared_ptr<hl_ast_node> division_implementation_pass::process_leaf(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = element;
    if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        if(node->get_type() == expr_div){
            std::shared_ptr<hl_ast_node> lhs = node->get_lhs();
            std::shared_ptr<hl_expression_node> modulo_expr = std::make_shared<hl_expression_node>(expr_reciprocal);
            modulo_expr->set_rhs(node->get_rhs());
            std::shared_ptr<hl_expression_node> mult_expr = std::make_shared<hl_expression_node>(expr_mult);
            mult_expr->set_lhs(node->get_lhs());
            mult_expr->set_rhs(modulo_expr);
            ret_val = mult_expr;
        }
    }
    return ret_val;
}

