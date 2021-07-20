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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.05/07/2021.
//


#include "passes/high_level/constant_folding_pass.hpp"

constant_folding_pass::constant_folding_pass() : pass_base<hl_ast_node>("Constant folding pass"){

}

std::shared_ptr<hl_ast_node> constant_folding_pass::process_leaf(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type==hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> expression = std::static_pointer_cast<hl_expression_node>(element);
        if(expression_evaluator::is_constant_expression(expression)){
            return expression_evaluator::evaluate_expression(expression);
        } else {
            return element;
        }
    }
    return element;
}