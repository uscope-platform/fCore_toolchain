

//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "passes/high_level/optimizations/visitor_passes/ternary_expression_extraction.hpp"


namespace fcore{
    ternary_expression_extraction::ternary_expression_extraction() : pass_base("Ternary Expression extraction") {
        ternary_progressive = 1;
    }

    std::shared_ptr<hl_code_block>
    ternary_expression_extraction::process_global(std::shared_ptr<hl_code_block> element, const std::vector<std::shared_ptr<hl_definition_node>> &globals) {
        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_expression = process_expression;


        return visitor.visit(ops, element);

    }

    std::vector<std::shared_ptr<hl_ast_node>>
    ternary_expression_extraction::process_expression(std::shared_ptr<hl_expression_node> element) {
        std::vector<std::shared_ptr<hl_ast_node>> ret_val;

        if(element->get_type() == expr_assign){
            if(element->get_rhs()->node_type == hl_ast_node_type_expr){
                auto expr_r = std::static_pointer_cast<hl_expression_node>(element->get_rhs());
                if(expr_r->get_type() == expr_csel){
                    auto lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs().value());
                    auto def_name = "ternary_output_" + lhs->get_identifier();

                    auto var = std::make_shared<variable>(def_name);
                    auto intermediate_def = std::make_shared<hl_definition_node>(def_name, c_type_float, var);
                    intermediate_def->set_scalar_initializer(expr_r);
                    auto op = std::make_shared<hl_ast_operand>(var);
                    element->set_rhs(op);
                    ret_val.push_back(intermediate_def);
                }
            }
        }
        ret_val.push_back(element);
        return ret_val;
    }

}

