

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

#include "passes/high_level/infrastructure/hl_ast_visitor.hpp"

namespace fcore{

    std::shared_ptr<hl_code_block> fcore::hl_ast_visitor::visit(const fcore::hl_ast_visitor_operations &operations,const std::shared_ptr<hl_code_block> &node) {
        ops = operations;
        auto ret_val = node;
        std::vector<std::shared_ptr<hl_ast_node>> new_content;
        for(const auto &item:ret_val->get_content()){
            new_content.push_back(process_node_by_type(item));
        }
        ret_val->set_content(new_content);
        return ret_val;
    }

    std::shared_ptr<hl_ast_node> fcore::hl_ast_visitor::process_node_by_type(const std::shared_ptr<hl_ast_node> &node) {
        if(!node) return node;
        switch (node->node_type) {
            case hl_ast_node_type_expr:
                return process_node(std::static_pointer_cast<hl_expression_node>(node));
            case hl_ast_node_type_definition:
                return process_node(std::static_pointer_cast<hl_definition_node>(node));
            case hl_ast_node_type_conditional:
                return process_node(std::static_pointer_cast<hl_ast_conditional_node>(node));
            case hl_ast_node_type_loop:
                return process_node(std::static_pointer_cast<hl_ast_loop_node>(node));
            case hl_ast_node_type_function_def:
                return process_node(std::static_pointer_cast<hl_function_def_node>(node));
            case hl_ast_node_type_operand:
                return process_node(std::static_pointer_cast<hl_ast_operand>(node));
            case hl_ast_node_type_function_call:
                return process_node(std::static_pointer_cast<hl_function_call_node>(node));
            case hl_ast_node_type_code_block:
                return visit(ops, std::static_pointer_cast<hl_code_block>(node));
            default:
                throw std::runtime_error("unexpected node encounted during AST visit");
        }
    }

    std::shared_ptr<hl_ast_node> hl_ast_visitor::process_node(const std::shared_ptr<hl_ast_conditional_node> &cond) {
        cond->set_condition(process_node_by_type(cond->get_condition()));

        std::vector<std::shared_ptr<hl_ast_node>> new_block;

        for(const auto &item:cond->get_if_block()){
            new_block.push_back(process_node_by_type(item));
        }
        cond->set_if_block(new_block);

        new_block.clear();

        for(const auto &item:cond->get_else_block()){
            new_block.push_back(process_node_by_type(item));
        }
        cond->set_else_block(new_block);

        if(ops.visit_conditional){
            return ops.visit_conditional(cond);
        } else {
            return cond;
        }
    }

    std::shared_ptr<hl_ast_node> hl_ast_visitor::process_node(const std::shared_ptr<hl_ast_loop_node> &loop) {

        std::vector<std::shared_ptr<hl_ast_node>> new_block;

        for(const auto &item:loop->get_loop_content()){
            new_block.push_back(process_node_by_type(item));
        }
        loop->set_loop_content(new_block);

        loop->set_condition(std::static_pointer_cast<hl_expression_node>(
                process_node_by_type(loop->get_condition())
                ));

        loop->set_init_statement(std::static_pointer_cast<hl_definition_node>(
                process_node_by_type(loop->get_init_statement())
        ));

        loop->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(
                process_node_by_type(loop->get_iteration_expr())
        ));


        if(ops.visit_loop){
            return ops.visit_loop(loop);
        } else {
            return loop;
        }
    }

    std::shared_ptr<hl_ast_node> hl_ast_visitor::process_node(const std::shared_ptr<hl_ast_operand> &op) {
        if(ops.visit_operand){
            return ops.visit_operand(op);
        } else {
            return op;
        }
    }

    std::shared_ptr<hl_ast_node> hl_ast_visitor::process_node(const std::shared_ptr<hl_definition_node> &def) {

        std::vector<std::shared_ptr<hl_ast_node>> new_block;

        for(const auto &item:def->get_array_initializer()){
            new_block.push_back(process_node_by_type(item));
        }
        def->set_array_initializer(new_block);

        new_block.clear();

        for(const auto &item:def->get_array_index()){
            new_block.push_back(process_node_by_type(item));
        }
        def->set_array_index(new_block);

        if(ops.visit_definition){
            return ops.visit_definition(def);
        } else {
            return def;
        }
    }

    std::shared_ptr<hl_ast_node> hl_ast_visitor::process_node(const std::shared_ptr<hl_expression_node> &ex) {
        if(auto ths = ex->get_ths()) ex->set_ths(process_node_by_type(ths.value()));
        if(auto lhs = ex->get_lhs()) ex->set_lhs(process_node_by_type(lhs.value()));
        ex->set_rhs(process_node_by_type(ex->get_rhs()));

        if(ops.visit_expression){
            return ops.visit_expression(ex);
        } else {
            return ex;
        }
    }

    std::shared_ptr<hl_ast_node> hl_ast_visitor::process_node(const std::shared_ptr<hl_function_call_node> &call) {

        std::vector<std::shared_ptr<hl_ast_node>> new_block;

        for(const auto &item:call->get_arguments()){
            new_block.push_back(process_node_by_type(item));
        }
        call->set_arguments(new_block);

        if(ops.visit_function_call){
            return ops.visit_function_call(call);
        } else {
            return call;
        }
    }

    std::shared_ptr<hl_ast_node> hl_ast_visitor::process_node(const std::shared_ptr<hl_function_def_node> &def) {
        std::vector<std::shared_ptr<hl_ast_node>> new_block;

        for(const auto &item:def->get_body()){
            new_block.push_back(process_node_by_type(item));
        }
        def->set_body(new_block);

        def->set_return(process_node_by_type(def->get_return()));

        if(ops.visit_function_def){
            return ops.visit_function_def(def);
        } else {
            return def;
        }

    }
}
