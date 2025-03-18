

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

#include "passes/high_level/semantic_analysis/assignments.hpp"

#include <fmt/format.h>

namespace fcore {

    assignments_checks::assignments_checks() :pass_base("assignments checks") {
    }

    std::shared_ptr<hl_code_block> assignments_checks::process_global(std::shared_ptr<hl_code_block> element, const std::vector<std::shared_ptr<hl_definition_node>> &globals) {
        hl_observing_visitor visitor;

        hl_observing_visitor_operations functions_mapping_ops;

        functions_mapping_ops.visit_definition = [this]<typename T0>(T0 && placeholder) { process_definition(std::forward<T0>(placeholder)); };

        visitor.visit({functions_mapping_ops, {}}, element);

        return element;
    }

    void assignments_checks::process_definition(const std::shared_ptr<hl_definition_node> &def) {
        auto def_type = def->get_type();
        for(auto &val: def->get_array_initializer()) {
            if(val->node_type == hl_ast_node_type_operand) {
                auto op = std::static_pointer_cast<hl_ast_operand>(val);
                if(op->get_variable()->get_type() != var_type_float_const) {
                    if(def_type == c_type_float) {
                        auto var = fmt::format("Assignment of an integer ({0}) to the float variable ({1}) is prohibited",op->get_float_val(), def->get_name());
                        throw std::runtime_error(var);
                    }
                }
                if(op->get_variable()->get_type() != var_type_int_const && op->get_float_val() != 0.0) {
                    if(def_type == c_type_int || def_type == c_type_long || def_type == c_type_short) {
                        auto var = fmt::format("Assignment of a float ({0}) to the integer variable ({1}) is prohibited",op->get_float_val(), def->get_name());
                        throw std::runtime_error(var);
                    }
                }
            }
        }
    }
}
