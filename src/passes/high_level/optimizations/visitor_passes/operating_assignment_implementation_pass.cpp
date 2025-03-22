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

    std::shared_ptr<ast_code_block>
    operating_assignment_implementation_pass::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_expression = process_expression;


        return visitor.visit(ops, element);

    }


    std::shared_ptr<ast_expression>
    operating_assignment_implementation_pass::create_top_expression(ast_expression::assignment_type a) {
        std::shared_ptr<ast_expression> retval;
        switch (a) {
            case ast_expression::addition_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::ADD);
                break;
            case ast_expression::subtraction_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::SUB);
                break;
            case ast_expression::multiplication_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::MULT);
                break;
            case ast_expression::division_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::DIV);
                break;
            case ast_expression::modulo_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::MODULO);
                break;
            case ast_expression::and_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::AND_B);
                break;
            case ast_expression::or_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::OR_B);
                break;
            case ast_expression::xor_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::XOR_B);
                break;
            case ast_expression::lsh_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::LSH);
                break;
            case ast_expression::rsh_assignment:
                retval = std::make_shared<ast_expression>(ast_expression::RSH);
                break;
        }
        return retval;
    }

    std::vector<std::shared_ptr<ast_node>>
    operating_assignment_implementation_pass::process_expression(std::shared_ptr<ast_expression> element) {
        if(element->get_type() == ast_expression::ASSIGN && element->get_assignment_type() != ast_expression::regular_assignment ){
            std::shared_ptr<ast_expression> outer_exp = std::make_shared<ast_expression>(ast_expression::ASSIGN);
            outer_exp->set_lhs(element->get_lhs().value());
            std::shared_ptr<ast_expression> inner_exp = create_top_expression(element->get_assignment_type());
            inner_exp->set_lhs(element->get_lhs().value());
            inner_exp->set_rhs(element->get_rhs());
            outer_exp->set_rhs(inner_exp);
            return {outer_exp};
        } else {
            return {element};
        }
    }
}

