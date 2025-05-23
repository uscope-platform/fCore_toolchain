

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
        const std::shared_ptr<ast_code_block> &node) {
        ops = operations;


        auto ret_val = node;
        for(const auto &item:node->get_content()){
            process_node_by_type(item);
        }
    }

    void hl_observing_visitor::process_node_by_type(const std::shared_ptr<ast_node> &node) {

        if(!node) return;
        switch (node->node_type) {
            case hl_ast_node_type_expr:
                process_node(std::static_pointer_cast<ast_expression>(node));
                break;
            case hl_ast_node_type_definition:
                process_node(std::static_pointer_cast<ast_definition>(node));
                break;
            case hl_ast_node_type_conditional:
                process_node(std::static_pointer_cast<ast_conditional>(node));
                break;
            case hl_ast_node_type_loop:
                process_node(std::static_pointer_cast<ast_loop>(node));
                break;
            case hl_ast_node_type_function_def:
                process_node(std::static_pointer_cast<ast_function_def>(node));
                break;
            case hl_ast_node_type_operand:
                process_node(std::static_pointer_cast<ast_operand>(node));
                break;
            case hl_ast_node_type_function_call:
                process_node(std::static_pointer_cast<ast_call>(node));
                break;
            case hl_ast_node_type_code_block:
                process_node(std::static_pointer_cast<ast_code_block>(node));
                break;
            default:
                throw std::runtime_error("unexpected node encounted during AST visit");
        }

    }

    void hl_observing_visitor::process_nodes_vector(const std::vector<std::shared_ptr<ast_node>> &node) {
        for(const auto &item:node){
            process_node_by_type(item);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<ast_conditional> &cond) {
        if(ops.pre.visit_conditional) ops.pre.visit_conditional(cond);
        process_node_by_type(cond->get_condition());
        process_nodes_vector(cond->get_if_block());
        if (ops.pre.before_else) ops.pre.before_else();
        process_nodes_vector(cond->get_else_block());

        if(ops.post.visit_conditional) ops.post.visit_conditional(cond);
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<ast_loop> &loop) {
        if(ops.pre.visit_loop) ops.pre.visit_loop(loop);
        process_node_by_type(loop->get_init_statement());
        process_node_by_type(loop->get_condition());
        process_node_by_type(loop->get_iteration_expr());
        process_nodes_vector(loop->get_loop_content());
        if(ops.post.visit_loop) ops.post.visit_loop(loop);
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<ast_operand> &op) {
        if(ops.pre.visit_operand) ops.pre.visit_operand(op);
        process_nodes_vector(op->get_array_index());
        if(ops.post.visit_operand) ops.post.visit_operand(op);
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<ast_definition> &def) {
        if(ops.pre.visit_definition) ops.pre.visit_definition(def);
        process_nodes_vector(def->get_array_initializer());
        process_nodes_vector(def->get_array_index());
        if(ops.post.visit_definition) ops.post.visit_definition(def);
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<ast_expression> &exp) {
        if(ops.pre.visit_expression) ops.pre.visit_expression(exp);
        if(const auto lhs = exp->get_lhs()) {
            process_node_by_type(*lhs);
        }
        if(const auto ths = exp->get_ths()) {
            process_node_by_type(*ths);
        }
        process_node_by_type(exp->get_rhs());
        if(ops.post.visit_expression) ops.post.visit_expression(exp);
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<ast_call> &call) {
        if(ops.pre.visit_function_call) ops.pre.visit_function_call(call);
        process_nodes_vector(call->get_arguments());
        if(ops.post.visit_function_call) ops.post.visit_function_call(call);
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<ast_function_def> &f_def) {
        if(ops.pre.visit_function_def) ops.pre.visit_function_def(f_def);
        process_nodes_vector(f_def->get_body());
        process_node_by_type(f_def->get_return());
        if(ops.post.visit_function_def) ops.post.visit_function_def(f_def);
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<ast_code_block> &block) {
        process_nodes_vector(block->get_content());
    }

}
