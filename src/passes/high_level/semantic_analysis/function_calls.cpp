

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

#include "passes/high_level/semantic_analysis/function_calls.hpp"

#include <fmt/format.h>

namespace fcore {
    function_calls_checks::function_calls_checks(): pass_base("function calls checks")  {

    }

    std::shared_ptr<hl_code_block> function_calls_checks::process_global(std::shared_ptr<hl_code_block> element) {

        hl_observing_visitor visitor;

        hl_observing_visitor_operations functions_mapping_ops;

        functions_mapping_ops.visit_function_def = [this]<typename T0>(T0 && placeholder) { map_definition(std::forward<T0>(placeholder)); };

        visitor.visit({functions_mapping_ops, {}}, element);

        hl_observing_visitor_operations pre_ops;
        hl_observing_visitor_operations post_ops;

        //stack handling
        pre_ops.visit_function_def = [this]<typename T0>(T0 && placeholder) { process_function_def(std::forward<T0>(placeholder)); };
        pre_ops.visit_loop = [this]<typename T0>(T0 && placeholder) { push_stack(); };
        pre_ops.visit_conditional = [this]<typename T0>(T0 && placeholder) { push_stack(); };

        pre_ops.before_else = [this] { reset_conditional_stack(); };

        post_ops.visit_function_def = [this]<typename T0>(T0 && placeholder) { pop_stack(); };
        post_ops.visit_function_call = [this]<typename T0>(T0 && placeholder) { process_function_call(std::forward<T0>(placeholder)); };
        post_ops.visit_loop = [this]<typename T0>(T0 && placeholder) { pop_stack(); };
        post_ops.visit_conditional = [this]<typename T0>(T0 && placeholder) { pop_stack(); };

        // analysis
        post_ops.visit_definition = [this]<typename T0>(T0 && placeholder) { process_definition(std::forward<T0>(placeholder)); };


        visitor.visit({pre_ops,post_ops}, element);

        return element;
    }


    void function_calls_checks::process_definition(const std::shared_ptr<hl_definition_node> &def) {
        current_scope[def->get_name()] = def->get_type();
    }

    void function_calls_checks::process_function_def(const std::shared_ptr<hl_function_def_node> &f_def) {
        push_stack();
        for(const auto &arg:f_def->get_parameters_list()) {
            current_scope[arg->get_name()] = arg->get_type();
        }
    }

    void function_calls_checks::process_function_call(const std::shared_ptr<hl_function_call_node> &call) {
        const auto arguments = call->get_arguments();
        for(int i = 0; i<arguments.size(); i++) {
            if(arguments[i]->node_type == hl_ast_node_type_operand) {
                auto arg_type = current_scope[std::static_pointer_cast<hl_ast_operand>(arguments[i])->get_name()];
                if(arg_type != definitions[call->get_name()][i].second) {
                    const std::string error = fmt::format("Argument #{0} of a call to {1} is of the wrong type", i, call->get_name());
                    throw std::runtime_error(error);
                }
            }
        }
    }

    void function_calls_checks::push_stack() {
        scopes_stack.push(current_scope);
    }

    void function_calls_checks::pop_stack() {
        current_scope = scopes_stack.top();
        scopes_stack.pop();
    }

    void function_calls_checks::reset_conditional_stack() {
        current_scope = scopes_stack.top();
    }

    void function_calls_checks::map_definition(const std::shared_ptr<hl_function_def_node> &def) {
        for(const auto &arg:def->get_parameters_list()) {
            definitions[def->get_name()].emplace_back(arg->get_name(), arg->get_type());
        }
    }
}

