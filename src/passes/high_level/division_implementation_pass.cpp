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

#include "passes/high_level/division_implementation_pass.hpp"

namespace fcore {

    division_implementation_pass::division_implementation_pass() : pass_base("division implementation pass") {

    }

    std::shared_ptr<hl_code_block>
    division_implementation_pass::process_global(std::shared_ptr<hl_code_block> element) {

        hl_ast_visitor_operations ops;
        hl_ast_visitor visitor;

        ops.visit_expression = std::bind(&division_implementation_pass::process_expression, this,
                                         std::placeholders::_1);


        return visitor.visit(ops, element);
    }

    std::shared_ptr<hl_ast_node>
    division_implementation_pass::process_expression(std::shared_ptr<hl_expression_node> exp) {
        if (exp->get_type() == expr_div) {
            std::shared_ptr<hl_ast_node> lhs = exp->get_lhs().value();
            std::shared_ptr<hl_expression_node> modulo_expr = std::make_shared<hl_expression_node>(expr_reciprocal);
            modulo_expr->set_rhs(exp->get_rhs());
            std::shared_ptr<hl_expression_node> mult_expr = std::make_shared<hl_expression_node>(expr_mult);
            mult_expr->set_lhs(exp->get_lhs().value());
            mult_expr->set_rhs(modulo_expr);
            return mult_expr;
        } else {
            return exp;
        }
    }
}