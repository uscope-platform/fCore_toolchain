

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

#include "passes/high_level/infrastructure/hl_acting_visitor.hpp"

namespace fcore{

    std::shared_ptr<ast_code_block> hl_acting_visitor::visit(const hl_acting_visitor_operations &operations,const std::shared_ptr<ast_code_block> &node) {
        ops = operations;
        auto ret_val = node;
        std::vector<std::shared_ptr<ast_node>> new_content;
        for(const auto &item:ret_val->get_content()){
            auto process_result = process_node_by_type(item);
            new_content.insert(new_content.end(), process_result.begin(), process_result.end());
        }
        ret_val->set_content(new_content);
        return ret_val;
    }

    std::vector<std::shared_ptr<ast_node>> hl_acting_visitor::process_node_by_type(const std::shared_ptr<ast_node> &node) {
        if(!node) return {node};
        switch (node->node_type) {
            case hl_ast_node_type_expr:
                return {process_node(std::static_pointer_cast<ast_expression>(node))};
            case hl_ast_node_type_definition:
                return process_node(std::static_pointer_cast<ast_definition>(node));
            case hl_ast_node_type_conditional:
                return {process_node(std::static_pointer_cast<ast_conditional>(node))};
            case hl_ast_node_type_loop:
                return {process_node(std::static_pointer_cast<ast_loop>(node))};
            case hl_ast_node_type_function_def:
                return {process_node(std::static_pointer_cast<ast_function_def>(node))};
            case hl_ast_node_type_operand:
                return {process_node(std::static_pointer_cast<ast_operand>(node))};
            case hl_ast_node_type_function_call:
                return {process_node(std::static_pointer_cast<ast_call>(node))};
            case hl_ast_node_type_code_block:
                return {process_node(std::static_pointer_cast<ast_code_block>(node))};
            default:
                throw std::runtime_error("unexpected node encounted during AST visit");
        }
    }

    std::shared_ptr<ast_node> hl_acting_visitor::process_node(const std::shared_ptr<ast_conditional> &cond) {
        cond->set_condition(get_expected_scalar_element(process_node_by_type(cond->get_condition())));

        std::vector<std::shared_ptr<ast_node>> new_block;
        if(ops.pre.visit_conditional) ops.pre.visit_conditional(cond);
        for(const auto &item:cond->get_if_block()){
            auto ret_block = process_node_by_type(item);
            new_block.insert(new_block.end(), ret_block.begin(), ret_block.end());
        }
        cond->set_if_block(new_block);

        if(ops.pre.visit_conditional) ops.pre.before_else(cond);
        new_block.clear();

        for(const auto &item:cond->get_else_block()){
            auto ret_block = process_node_by_type(item);
            new_block.insert(new_block.end(), ret_block.begin(), ret_block.end());
        }
        cond->set_else_block(new_block);

        if(ops.post.visit_conditional){
            return ops.post.visit_conditional(cond);
        }
        return cond;
    }

    std::shared_ptr<ast_node> hl_acting_visitor::process_node(const std::shared_ptr<ast_loop> &loop) {

        std::vector<std::shared_ptr<ast_node>> new_block;
        if(ops.pre.visit_loop) ops.pre.visit_loop(loop);
        for(const auto &item:loop->get_loop_content()){
            auto ret_content = process_node_by_type(item);
            new_block.insert(new_block.end(), ret_content.begin(), ret_content.end());
        }
        loop->set_loop_content(new_block);

        loop->set_condition(std::static_pointer_cast<ast_expression>(
            get_expected_scalar_element(process_node_by_type(loop->get_condition()))
        ));

        loop->set_init_statement(std::static_pointer_cast<ast_definition>(
            get_expected_scalar_element(process_node_by_type(loop->get_init_statement()))
        ));

        loop->set_iteration_expr(std::static_pointer_cast<ast_expression>(
            get_expected_scalar_element(process_node_by_type(loop->get_iteration_expr()))
        ));


        if(ops.post.visit_loop){
            return ops.post.visit_loop(loop);
        }
        return loop;
    }

    std::shared_ptr<ast_node> hl_acting_visitor::process_node(const std::shared_ptr<ast_operand> &op) {
        if(ops.pre.visit_operand) ops.pre.visit_operand(op);
        if(ops.post.visit_operand){
            return ops.post.visit_operand(op);
        }
        return op;
    }

    std::vector<std::shared_ptr<ast_node>> hl_acting_visitor::process_node(const std::shared_ptr<ast_definition> &def) {

        std::vector<std::shared_ptr<ast_node>> new_block;
        if(ops.pre.visit_definition) ops.pre.visit_definition(def);
        for(const auto &item:def->get_array_initializer()){
            auto new_array = process_node_by_type(item);
            new_block.insert(new_block.end(), new_array.begin(), new_array.end());
        }
        def->set_array_initializer(new_block);

        new_block.clear();

        for(const auto &item:def->get_array_index()){
            auto new_array = process_node_by_type(item);
            new_block.insert(new_block.end(), new_array.begin(), new_array.end());
        }
        def->set_array_index(new_block);

        if(ops.post.visit_definition){
            return ops.post.visit_definition(def);
        }
        return {def};
    }

    std::vector<std::shared_ptr<ast_node>>  hl_acting_visitor::process_node(const std::shared_ptr<ast_expression> &ex) {
        if(ops.pre.visit_expression) ops.pre.visit_expression(ex);
        if(const auto ths = ex->get_ths())
            ex->set_ths(get_expected_scalar_element(process_node_by_type(*ths)));
        if(const auto lhs = ex->get_lhs())
            ex->set_lhs(get_expected_scalar_element(process_node_by_type(*lhs)));
        ex->set_rhs(get_expected_scalar_element(process_node_by_type(ex->get_rhs())));

        if(ops.post.visit_expression){
            return ops.post.visit_expression(ex);
        }
        return {ex};
    }

    std::vector<std::shared_ptr<ast_node>> hl_acting_visitor::process_node(const std::shared_ptr<ast_call> &call) {

        std::vector<std::shared_ptr<ast_node>> new_block;
        if(ops.pre.visit_function_call) ops.pre.visit_function_call(call);
        for(const auto &item:call->get_arguments()){
            auto ret_args = process_node_by_type(item);
            new_block.insert(new_block.end(), ret_args.begin(), ret_args.end());
        }
        call->set_arguments(new_block);

        if(ops.post.visit_function_call){
            return ops.post.visit_function_call(call);
        }
        return {call};
    }

    std::vector<std::shared_ptr<ast_node>> hl_acting_visitor::process_node(const std::shared_ptr<ast_function_def> &def) {
        std::vector<std::shared_ptr<ast_node>> new_block;
        if(ops.pre.visit_function_def) ops.pre.visit_function_def(def);
        for(const auto &item:def->get_body()){
            auto ret_body = process_node_by_type(item);
            new_block.insert(new_block.end(), ret_body.begin(), ret_body.end());
        }
        def->set_body(new_block);

        def->set_return(get_expected_scalar_element(process_node_by_type(def->get_return())));

        if(ops.post.visit_function_def){
            return ops.post.visit_function_def(def);
        }
        return {def};
    }

    std::shared_ptr<ast_node> hl_acting_visitor::process_node(const std::shared_ptr<ast_code_block> &block) {
        auto ret_val = block;
        std::vector<std::shared_ptr<ast_node>> new_content;
        for(const auto &item:ret_val->get_content()){
            auto process_result = process_node_by_type(item);
            new_content.insert(new_content.end(), process_result.begin(), process_result.end());
        }
        ret_val->set_content(new_content);
        return ret_val;
    }

    std::shared_ptr<ast_node>
    hl_acting_visitor::get_expected_scalar_element(const std::vector<std::shared_ptr<ast_node>> &vect) {
        if(vect.size() ==1) return vect[0];
        throw std::runtime_error("Unexpected vector return in a scalar only position during AST visit");
    }
}
