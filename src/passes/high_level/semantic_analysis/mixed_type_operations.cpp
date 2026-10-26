

//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#include "passes/high_level/semantic_analysis/mixed_type_operations.hpp"

fcore::mixed_type_operations::mixed_type_operations() : pass_base("mixed_type_operations") {

}

fcore::pass_result fcore::mixed_type_operations::process_global(
    std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {

        hl_observing_visitor visitor;

        hl_observing_visitor_operations ops;

        ops.pre.visit_expression = [this](const std::shared_ptr<ast_expression> &exp) { process_expression(exp); };
        ops.should_stop = stop_condition();

        auto visited = visitor.visit(ops, element);
        return finish(visited, element);


}

void fcore::mixed_type_operations::process_expression(const std::shared_ptr<ast_expression> &exp) {
    if(!exp->is_unary() && !exp->is_ternary() && !exp->is_immediate()) {
        if(exp->get_lhs().value()->node_type == hl_ast_node_type_operand && exp->get_rhs()->node_type == hl_ast_node_type_operand) {
            auto lhs = std::static_pointer_cast<ast_operand>(exp->get_lhs().value());
            auto rhs = std::static_pointer_cast<ast_operand>(exp->get_rhs());
            if(!are_types_compatible(lhs->get_c_type(), rhs->get_c_type())) {
                report(error(error_code::type_error, fmt::format(
                    "Encountered expression with mixed types: {0} is {1} and {2} is {3}",
                    lhs->get_name(), variable::type_to_string(lhs->get_c_type()),
                    rhs->get_name(), variable::type_to_string(rhs->get_c_type())
                )));
            }
        }
    }
}

bool fcore::mixed_type_operations::are_types_compatible(c_types_t lhs, c_types_t rhs){
    if(rhs == lhs) return true;
    if(rhs == c_type_int && lhs == c_type_long) return true;
    if(rhs == c_type_long && lhs == c_type_int) return true;

    if(rhs == c_type_int && lhs == c_type_short) return true;
    if(rhs == c_type_short && lhs == c_type_int) return true;

    if(rhs == c_type_short && lhs == c_type_long) return true;
    if(rhs == c_type_long && lhs == c_type_short) return true;

    return false;
}
