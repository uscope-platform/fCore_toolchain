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


#include "passes/high_level/optimizations/visitor_passes/constant_folding_pass.hpp"

namespace fcore{

    constant_folding_pass::constant_folding_pass() : pass_base("Constant folding pass"){

    }

    std::shared_ptr<hl_code_block> constant_folding_pass::process_global(std::shared_ptr<hl_code_block> element) {

        hl_ast_visitor_operations ops;
        hl_ast_visitor visitor;

        ops.visit_expression = process_expression;

        return visitor.visit(ops, element);

    }


    std::vector<std::shared_ptr<hl_ast_node>>  constant_folding_pass::process_expression(std::shared_ptr<hl_expression_node> exp) {
        if(expression_evaluator::is_constant_expression(exp)){
            return {expression_evaluator::evaluate_expression(exp)};
        } else return {exp};
    }


}