

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

    undefined_variables::undefined_variables() : pass_base("Undefined Variables checking", 1){

    }

    std::shared_ptr<hl_code_block> undefined_variables::process_global(std::shared_ptr<hl_code_block> element) {
        hl_observing_visitor_operations pre_ops;
        hl_observing_visitor_operations post_ops;
        hl_observing_visitor visitor;

        //stack handling
        pre_ops.visit_function_def = [this]<typename T0>(T0 && placeholder) { process_function_def(std::forward<T0>(placeholder)); };
        pre_ops.visit_loop = [this]<typename T0>(T0 && placeholder) { push_stack(); };
        pre_ops.visit_conditional = [this]<typename T0>(T0 && placeholder) { push_stack(); };

        pre_ops.before_else = [this] { reset_conditional_stack(); };

        post_ops.visit_function_def = [this]<typename T0>(T0 && placeholder) { pop_stack(); };
        post_ops.visit_loop = [this]<typename T0>(T0 && placeholder) { pop_stack(); };
        post_ops.visit_conditional = [this]<typename T0>(T0 && placeholder) { pop_stack(); };

        // analysis
        post_ops.visit_operand = [this]<typename T0>(T0 && placeholder) { process_operand(std::forward<T0>(placeholder)); };
        post_ops.visit_definition = [this]<typename T0>(T0 && placeholder) { process_definition(std::forward<T0>(placeholder)); };


        visitor.visit({pre_ops,post_ops}, element);

        return element;
    }


    void undefined_variables::process_definition(const std::shared_ptr<hl_definition_node> &def) {
        current_stack.insert(def->get_name());
    }

    void undefined_variables::process_function_def(const std::shared_ptr<hl_function_def_node> &def) {
        push_stack();
        for(const auto &arg:def->get_parameters_list()) {
            current_stack.insert(arg->get_name());
        }
    }

    void undefined_variables::process_operand(const std::shared_ptr<hl_ast_operand> &op) const {
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
