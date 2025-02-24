

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
    void hl_observing_visitor::visit(const std::pair<hl_observing_visitor_operations,hl_observing_visitor_operations>&operations,
        const std::shared_ptr<hl_code_block> &node) {
        preorder_ops = operations.first;
        postorder_ops = operations.second;


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
                break;
            case hl_ast_node_type_definition:
                process_node(std::static_pointer_cast<hl_definition_node>(node));
                break;
            case hl_ast_node_type_conditional:
                process_node(std::static_pointer_cast<hl_ast_conditional_node>(node));
                break;
            case hl_ast_node_type_loop:
                process_node(std::static_pointer_cast<hl_ast_loop_node>(node));
                break;
            case hl_ast_node_type_function_def:
                process_node(std::static_pointer_cast<hl_function_def_node>(node));
                break;
            case hl_ast_node_type_operand:
                process_node(std::static_pointer_cast<hl_ast_operand>(node));
                break;
            case hl_ast_node_type_function_call:
                process_node(std::static_pointer_cast<hl_function_call_node>(node));
                break;
            case hl_ast_node_type_code_block:
                process_node(std::static_pointer_cast<hl_code_block>(node));
                break;
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
        if(preorder_ops.visit_conditional) {
            preorder_ops.visit_conditional(cond);
        }
        process_node_by_type(cond->get_condition());
        process_nodes_vector(cond->get_if_block());
        preorder_ops.before_else();
        process_nodes_vector(cond->get_else_block());

        if(postorder_ops.visit_conditional) {
            postorder_ops.visit_conditional(cond);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_ast_loop_node> &loop) {
        if(preorder_ops.visit_loop) {
            preorder_ops.visit_loop(loop);
        }
        process_node_by_type(loop->get_init_statement());
        process_node_by_type(loop->get_condition());
        process_node_by_type(loop->get_iteration_expr());
        process_nodes_vector(loop->get_loop_content());
        if(postorder_ops.visit_loop) {
            postorder_ops.visit_loop(loop);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_ast_operand> &op) {
        if(preorder_ops.visit_operand) {
            preorder_ops.visit_operand(op);
        }
        process_nodes_vector(op->get_array_index());
        if(postorder_ops.visit_operand) {
            postorder_ops.visit_operand(op);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_definition_node> &def) {
        if(preorder_ops.visit_definition) {
            preorder_ops.visit_definition(def);
        }
        process_nodes_vector(def->get_array_initializer());
        process_nodes_vector(def->get_array_index());
        if(postorder_ops.visit_definition) {
            postorder_ops.visit_definition(def);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_expression_node> &exp) {
        if(preorder_ops.visit_expression) {
            preorder_ops.visit_expression(exp);
        }
        if(const auto lhs = exp->get_lhs()) {
            process_node_by_type(*lhs);
        }
        if(const auto ths = exp->get_ths()) {
            process_node_by_type(*ths);
        }
        process_node_by_type(exp->get_rhs());
        if(postorder_ops.visit_expression) {
            postorder_ops.visit_expression(exp);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_function_call_node> &call) {
        if(preorder_ops.visit_function_call) {
            preorder_ops.visit_function_call(call);
        }
        process_nodes_vector(call->get_arguments());
        if(postorder_ops.visit_function_call) {
            postorder_ops.visit_function_call(call);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_function_def_node> &f_def) {
        if(preorder_ops.visit_function_def) {
            preorder_ops.visit_function_def(f_def);
        }
        process_nodes_vector(f_def->get_body());
        process_node_by_type(f_def->get_return());

        if(postorder_ops.visit_function_def) {
            postorder_ops.visit_function_def(f_def);
        }
    }

    void hl_observing_visitor::process_node(const std::shared_ptr<hl_code_block> &block) {
        process_nodes_vector(block->get_content());
    }

}
