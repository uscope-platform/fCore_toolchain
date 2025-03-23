

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

#include "passes/high_level/semantic_analysis/type_propagation.hpp"



namespace fcore {
    type_propagation::type_propagation() : pass_base("type_propagation"){

    }

    std::shared_ptr<ast_code_block> type_propagation::process_global(std::shared_ptr<ast_code_block> element,
        const std::vector<std::shared_ptr<ast_definition>> &globals) {

        hl_acting_visitor visitor;
        hl_acting_visitor_operations ops;

        ops.pre.visit_definition = [this](auto && arg) { return process_definition(std::forward<decltype(arg)>(arg));};

        ops.pre.visit_function_def = [this](auto && arg) { return enter_function_def(std::forward<decltype(arg)>(arg));};
        ops.post.visit_function_def = [this](auto && arg) { return exit_function_def(std::forward<decltype(arg)>(arg));};

        ops.pre.visit_loop = [this](auto && arg) { return enter_loop(std::forward<decltype(arg)>(arg));};
        ops.post.visit_loop = [this](auto && arg) { return exit_loop(std::forward<decltype(arg)>(arg));};

        ops.pre.visit_conditional = [this](auto && arg) { return enter_conditional(std::forward<decltype(arg)>(arg));};
        ops.pre.before_else = [this](auto && arg) { return after_else_conditional(std::forward<decltype(arg)>(arg));};
        ops.post.visit_conditional = [this](auto && arg) { return exit_conditional(std::forward<decltype(arg)>(arg));};

        ops.post.visit_operand = [this](auto && arg) { return process_operand(std::forward<decltype(arg)>(arg));};
        auto result =  visitor.visit(ops, element);
        return result;
    }

    void type_propagation::enter_loop(const std::shared_ptr<ast_loop> &node) {
        setup_frame();
    }

    std::shared_ptr<ast_node> type_propagation::exit_loop(const std::shared_ptr<ast_loop> &node) {
        teardown_frame();
        return node;
    }


     void type_propagation::enter_function_def(const std::shared_ptr<ast_function_def> &node) {
        setup_frame();
        for(auto &a:node->get_parameters_list()) {
            current_scope[a->get_name()] = a->get_type();
        }

    }

    std::vector<std::shared_ptr<ast_node>> type_propagation::exit_function_def(const std::shared_ptr<ast_function_def> &node) {
        teardown_frame();
        return{node};
    }

    void type_propagation::enter_conditional(const std::shared_ptr<ast_conditional> &node) {
        setup_frame();
    }

    void type_propagation::after_else_conditional(const std::shared_ptr<ast_conditional> &node) {
        teardown_frame();
        setup_frame();
    }

    std::shared_ptr<ast_node> type_propagation::exit_conditional(const std::shared_ptr<ast_conditional> &node) {
        teardown_frame();
        return {node};
    }

    std::vector<std::shared_ptr<ast_node>> type_propagation::process_definition(const std::shared_ptr<ast_definition> &node) {
        current_scope[node->get_name()] = node->get_type();
        return {node};
    }

    std::shared_ptr<ast_node> type_propagation::process_operand(const std::shared_ptr<ast_operand> &node) {
        if(node->is_constant()) return node;
        if(current_scope.contains(node->get_name())) {
            node->set_c_type(current_scope[node->get_name()]);
        }
        return node;
    }

    void type_propagation::setup_frame() {
        scopes_stack.push(current_scope);
    }

    void type_propagation::teardown_frame() {
        current_scope = scopes_stack.top();
        scopes_stack.pop();
    }

}
