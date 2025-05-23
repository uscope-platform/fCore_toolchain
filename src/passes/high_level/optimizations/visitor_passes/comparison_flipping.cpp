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
// limitations under the License.
//


#include "passes/high_level/optimizations/visitor_passes/comparison_flipping.hpp"

namespace fcore{

    comparison_flipping::comparison_flipping() : pass_base("Comparison flipping pass"){

    }

    std::shared_ptr<ast_code_block> comparison_flipping::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.post.visit_expression = process_expression;

        return visitor.visit(ops, element);

    }


    std::vector<std::shared_ptr<ast_node>>  comparison_flipping::process_expression(std::shared_ptr<ast_expression> exp) {
        if(exp->get_type() == ast_expression::GTE){
            exp->set_type(ast_expression::LTE);
            auto lhs = exp->get_lhs();
            exp->set_lhs(exp->get_rhs());
            exp->set_rhs(lhs.value());
        } else if (exp->get_type() == ast_expression::LT) {
            exp->set_type(ast_expression::GT);
            auto lhs = exp->get_lhs();
            exp->set_lhs(exp->get_rhs());
            exp->set_rhs(lhs.value());
        }

        return {exp};
    }


}