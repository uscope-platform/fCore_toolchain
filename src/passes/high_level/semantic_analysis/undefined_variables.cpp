

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

#include "passes/high_level/semantic_analysis/undefined_variables.hpp"

namespace fcore {

    undefined_variables::undefined_variables() : pass_base("Undefined Variables checking"){

    }

    std::shared_ptr<ast_code_block> undefined_variables::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {
        hl_observing_visitor_operations ops;
        hl_observing_visitor visitor;

        //stack handling
        ops.pre.visit_function_def = [this]<typename T0>(T0 && placeholder) { process_function_def(std::forward<T0>(placeholder)); };
        ops.pre.visit_loop = [this]<typename T0>(T0 && placeholder) { push_stack(); };
        ops.pre.visit_conditional = [this]<typename T0>(T0 && placeholder) { push_stack(); };

        ops.pre.before_else = [this] { reset_conditional_stack(); };

        ops.post.visit_function_def = [this]<typename T0>(T0 && placeholder) { pop_stack(); };
        ops.post.visit_loop = [this]<typename T0>(T0 && placeholder) { pop_stack(); };
        ops.post.visit_conditional = [this]<typename T0>(T0 && placeholder) { pop_stack(); };

        // analysis
        ops.post.visit_operand = [this]<typename T0>(T0 && placeholder) { process_operand(std::forward<T0>(placeholder)); };
        ops.post.visit_definition = [this]<typename T0>(T0 && placeholder) { process_definition(std::forward<T0>(placeholder)); };


        visitor.visit(ops, element);

        return element;
    }


    void undefined_variables::process_definition(const std::shared_ptr<ast_definition> &def) {
        current_stack.insert(def->get_name());
    }

    void undefined_variables::process_function_def(const std::shared_ptr<ast_function_def> &def) {
        push_stack();
        for(const auto &arg:def->get_parameters_list()) {
            current_stack.insert(arg->get_name());
        }
    }

    void undefined_variables::process_operand(const std::shared_ptr<ast_operand> &op) const {
        if(!current_stack.contains(op->get_name())) {
            auto type = op->get_type();
            if(type != var_type_float_const && type != var_type_int_const) {
                // report error and exit;
                throw std::runtime_error("Undefined variable: " + op->get_name());
            }
        }
    }

    void undefined_variables::reset_conditional_stack() {
        current_stack = definitions_stack.top();
    }

    void undefined_variables::push_stack() {
        definitions_stack.push(current_stack);
    }

    void undefined_variables::pop_stack() {
        current_stack = definitions_stack.top();
        definitions_stack.pop();
    }

}
