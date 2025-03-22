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
// limitations under the License.08/07/2021.
//

#include "passes/high_level/optimizations/visitor_passes/operating_assignment_implementation_pass.hpp"

namespace fcore{

    operating_assignment_implementation_pass::operating_assignment_implementation_pass() : pass_base("operating assignments implementation pass"){

    }

    std::shared_ptr<hl_code_block>
    operating_assignment_implementation_pass::process_global(std::shared_ptr<hl_code_block> element, const std::vector<std::shared_ptr<hl_definition_node>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_expression = process_expression;


        return visitor.visit(ops, element);

    }


    std::shared_ptr<hl_expression_node>
    operating_assignment_implementation_pass::create_top_expression(hl_expression_node::assignment_type_t a) {
        std::shared_ptr<hl_expression_node> retval;
        switch (a) {
            case hl_expression_node::addition_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_add);
                break;
            case hl_expression_node::subtraction_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_sub);
                break;
            case hl_expression_node::multiplication_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_mult);
                break;
            case hl_expression_node::division_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_div);
                break;
            case hl_expression_node::modulo_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_modulo);
                break;
            case hl_expression_node::and_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_and_b);
                break;
            case hl_expression_node::or_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_or_b);
                break;
            case hl_expression_node::xor_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_xor_b);
                break;
            case hl_expression_node::lsh_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_lsh);
                break;
            case hl_expression_node::rsh_assignment:
                retval = std::make_shared<hl_expression_node>(hl_expression_node::expr_rsh);
                break;
        }
        return retval;
    }

    std::vector<std::shared_ptr<hl_ast_node>>
    operating_assignment_implementation_pass::process_expression(std::shared_ptr<hl_expression_node> element) {
        if(element->get_type() == hl_expression_node::expr_assign && element->get_assignment_type() != hl_expression_node::regular_assignment ){
            std::shared_ptr<hl_expression_node> outer_exp = std::make_shared<hl_expression_node>(hl_expression_node::expr_assign);
            outer_exp->set_lhs(element->get_lhs().value());
            std::shared_ptr<hl_expression_node> inner_exp = create_top_expression(element->get_assignment_type());
            inner_exp->set_lhs(element->get_lhs().value());
            inner_exp->set_rhs(element->get_rhs());
            outer_exp->set_rhs(inner_exp);
            return {outer_exp};
        } else {
            return {element};
        }
    }
}

