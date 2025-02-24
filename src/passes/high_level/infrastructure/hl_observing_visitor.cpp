

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

#include "passes/high_level/infrastructure/hl_observing_visitor.hpp"


namespace fcore {
    void hl_observing_visitor::visit(const hl_observing_visitor_operations &operations,
        const std::shared_ptr<hl_code_block> &node) {
        ops = operations;


        auto ret_val = node;
        for(const auto &item:node->get_content()){
            process_node_by_type(item);
        }
    }

    void hl_observing_visitor::process_node_by_type(const std::shared_ptr<hl_ast_node> &node) {

        if(!node) return;
        switch (node->node_type) {
            case hl_ast_node_type_expr:
                process_node(std::static_pointer_cast<hl_expression_node>(node));
            case hl_ast_node_type_definition:
                process_node(std::static_pointer_cast<hl_definition_node>(node));
            case hl_ast_node_type_conditional:
                process_node(std::static_pointer_cast<hl_ast_conditional_node>(node));
            case hl_ast_node_type_loop:
                process_node(std::static_pointer_cast<hl_ast_loop_node>(node));
            case hl_ast_node_type_function_def:
                process_node(std::static_pointer_cast<hl_function_def_node>(node));
            case hl_ast_node_type_operand:
                process_node(std::static_pointer_cast<hl_ast_operand>(node));
            case hl_ast_node_type_function_call:
                process_node(std::static_pointer_cast<hl_function_call_node>(node));
            case hl_ast_node_type_code_block:
                process_node(std::static_pointer_cast<hl_code_block>(node));
            default:
                throw std::runtime_error("unexpected node encounted during AST visit");
        }

    }

    void hl_observing_visitor::process_nodes_vector(const std::vector<std::shared_ptr<hl_ast_node>> &node) {
        for(const auto &item:node){
            process_node_by_type(item);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_ast_conditional_node> &cond) {

        process_node_by_type(cond->get_condition());
        process_nodes_vector(cond->get_if_block());
        process_nodes_vector(cond->get_else_block());

        if(ops.visit_conditional){
            ops.visit_conditional(cond);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_ast_loop_node> &loop) {
        process_node_by_type(loop->get_init_statement());
        process_node_by_type(loop->get_condition());
        process_node_by_type(loop->get_iteration_expr());
        process_nodes_vector(loop->get_loop_content());
        if(ops.visit_loop) {
            ops.visit_loop(loop);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_ast_operand> &op) {
        if(ops.visit_operand) {
            ops.visit_operand(op);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_definition_node> &def) {
        process_nodes_vector(def->get_array_initializer());
        process_nodes_vector(def->get_array_index());
        if(ops.visit_definition) {
            ops.visit_definition(def);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_expression_node> &exp) {
        if(const auto lhs = exp->get_lhs()) {
            process_node_by_type(*lhs);
        }
        if(const auto ths = exp->get_ths()) {
            process_node_by_type(*ths);
        }
        process_node_by_type(exp->get_rhs());
        if(ops.visit_expression) {
            ops.visit_expression(exp);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_function_call_node> &call) {
        process_nodes_vector(call->get_arguments());
        if(ops.visit_function_call) {
            ops.visit_function_call(call);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_function_def_node> &f_def) {
        process_nodes_vector(f_def->get_body());
        process_node_by_type(f_def->get_return());

        if(ops.visit_function_def) {
            ops.visit_function_def(f_def);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_code_block> &block) {
        process_nodes_vector(block->get_content());
    }
}
