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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.08/07/2021.
//

#include "passes/high_level/operating_assignment_implementation_pass.hpp"


operating_assignment_implementation_pass::operating_assignment_implementation_pass() : pass_base<hl_ast_node>("operating assignments implementation pass"){

}

std::shared_ptr<hl_ast_node>
operating_assignment_implementation_pass::process_leaf(std::shared_ptr<hl_ast_node> element) {

    std::shared_ptr<hl_ast_node> ret_val = element;
    if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        if(node->get_type() == expr_assign && node->get_assignment_type() != regular_assignment ){
            std::shared_ptr<hl_expression_node> outer_exp = std::make_shared<hl_expression_node>(expr_assign);
            outer_exp->set_lhs(node->get_lhs());
            std::shared_ptr<hl_expression_node> inner_exp = create_top_expression(node->get_assignment_type());
            inner_exp->set_lhs(node->get_lhs());
            inner_exp->set_rhs(node->get_rhs());
            outer_exp->set_rhs(inner_exp);
            ret_val = outer_exp;
        }
    }
    return ret_val;

}

std::shared_ptr<hl_expression_node>
operating_assignment_implementation_pass::create_top_expression(assignment_type_t a) {
    std::shared_ptr<hl_expression_node> retval;
    switch (a) {
        case addition_assignment:
            retval = std::make_shared<hl_expression_node>(expr_add);
            break;
        case subtraction_assignment:
            retval = std::make_shared<hl_expression_node>(expr_sub);
            break;
        case multiplication_assignment:
            retval = std::make_shared<hl_expression_node>(expr_mult);
            break;
        case division_assignment:
            retval = std::make_shared<hl_expression_node>(expr_div);
            break;
        case modulo_assignment:
            retval = std::make_shared<hl_expression_node>(expr_modulo);
            break;
        case and_assignment:
            retval = std::make_shared<hl_expression_node>(expr_and_b);
            break;
        case or_assignment:
            retval = std::make_shared<hl_expression_node>(expr_or_b);
            break;
        case xor_assignment:
            retval = std::make_shared<hl_expression_node>(expr_xor_b);
            break;
        case lsh_assignment:
            retval = std::make_shared<hl_expression_node>(expr_lsh);
            break;
        case rsh_assignment:
            retval = std::make_shared<hl_expression_node>(expr_rsh);
            break;
    }
    return retval;
}


