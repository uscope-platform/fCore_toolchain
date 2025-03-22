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

#include "passes/high_level/optimizations/visitor_passes/division_implementation_pass.hpp"

namespace fcore {

    division_implementation_pass::division_implementation_pass() : pass_base("division implementation pass") {

    }

    std::shared_ptr<ast_code_block>
    division_implementation_pass::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        // ops.visit_expression = [this](auto && arg) { return process_expression(std::forward<decltype(arg)>(arg)); };
        ops.visit_expression = process_expression;

        return visitor.visit(ops, element);
    }

    std::vector<std::shared_ptr<ast_node>>
    division_implementation_pass::process_expression(std::shared_ptr<ast_expression> exp) {
        if (exp->get_type() == ast_expression::DIV) {
            std::shared_ptr<ast_node> lhs = exp->get_lhs().value();
            std::shared_ptr<ast_expression> modulo_expr = std::make_shared<ast_expression>(ast_expression::RECIPROCAL);
            modulo_expr->set_rhs(exp->get_rhs());
            std::shared_ptr<ast_expression> mult_expr = std::make_shared<ast_expression>(ast_expression::MULT);
            mult_expr->set_lhs(exp->get_lhs().value());
            mult_expr->set_rhs(modulo_expr);
            return {mult_expr};
        } else {
            return {exp};
        }
    }
}