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


#include "passes/high_level/optimizations/loop_unrolling_pass.hpp"

namespace fcore{

    loop_unrolling_pass::loop_unrolling_pass() : pass_base("C loop unrolling pass"){
        current_loop_iteration = 0;
    }

    std::shared_ptr<ast_code_block> loop_unrolling_pass::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {
        auto retval = std::make_shared<ast_code_block>();
        std::vector<std::shared_ptr<ast_node>> new_content;

        for(const auto& item:element->get_content()){
            if(item->node_type == hl_ast_node_type_function_def){
                new_content.push_back(process_function_def(std::static_pointer_cast<ast_function_def>(item)));
            } else {
                if(item->node_type == hl_ast_node_type_loop){
                    std::vector<std::shared_ptr<ast_node>> unrolled_loop = process_loop(std::static_pointer_cast<ast_loop>(item));
                    new_content.insert(new_content.end(), unrolled_loop.begin(), unrolled_loop.end());
                } else {
                    new_content.push_back(item);
                }
            }
        }
        retval->set_content(new_content);
        return retval;
    }

    std::shared_ptr<ast_node>
    loop_unrolling_pass::process_function_def(const std::shared_ptr<ast_function_def> &node) {

        std::shared_ptr<ast_function_def> retval = node;
        std::vector<std::shared_ptr<ast_node>> new_body;

        for(const auto& item:node->get_body()){
            if(item->node_type == hl_ast_node_type_loop){
                std::vector<std::shared_ptr<ast_node>> unrolled_loop = process_loop(std::static_pointer_cast<ast_loop>(item));
                new_body.insert(new_body.end(), unrolled_loop.begin(), unrolled_loop.end());
            } else {
                new_body.push_back(item);
            }
        }
        retval->set_body(new_body);

        return retval;

    }

    std::vector<std::shared_ptr<ast_node>> loop_unrolling_pass::process_loop(const std::shared_ptr<ast_loop>& element) {
        std::vector<std::shared_ptr<ast_node>> retval;
        if(!element->get_init_statement()->is_initialized()){
            throw std::runtime_error("Incomplete loop initialization statement");
        }
        std::vector<std::shared_ptr<ast_node>> new_body;

        for(auto &item:element->get_loop_content()){
            if(item->node_type ==hl_ast_node_type_loop){
                std::vector<std::shared_ptr<ast_node>> unrolled_loop = process_loop(std::static_pointer_cast<ast_loop>(item));
                new_body.insert(new_body.end(), unrolled_loop.begin(), unrolled_loop.end());
            } else{
                new_body.push_back(item);
            }
        }
        element->set_loop_content(new_body);

        std::shared_ptr<ast_node> raw_initializer = element->get_init_statement()->get_scalar_initializer();
        std::string loop_var_name = element->get_init_statement()->get_name();
        current_loop_iteration = process_loop_initializer(raw_initializer);

        std::shared_ptr<ast_expression> condition = element->get_condition();
        std::shared_ptr<ast_expression> iter_exp = element->get_iteration_expr();



        std::shared_ptr<variable> var = std::make_shared<variable>(loop_var_name, (int)current_loop_iteration);
        std::shared_ptr<ast_operand> loop_var = std::make_shared<ast_operand>(var);

        while(evaluate_loop(condition, iter_exp, loop_var)){
            std::vector<std::shared_ptr<ast_node>> content = element->get_loop_content();

            std::vector<std::shared_ptr<ast_node>> new_content;
            for(auto &item:content){
                int loop_variable_val = loop_var->get_variable()->get_int_value();
                new_content.push_back(substitute_index(item, loop_var_name, loop_variable_val));
            }
            var = std::make_shared<variable>(loop_var_name, (int)current_loop_iteration);
            loop_var = std::make_shared<ast_operand>(var);
            retval.insert(retval.end(), new_content.begin(), new_content.end());
        }
        return retval;
    }

    unsigned int loop_unrolling_pass::process_loop_initializer(const std::shared_ptr<ast_node>& raw_initializer) {

        unsigned int ret_val;

        std::shared_ptr<ast_operand> initializer;

        if(raw_initializer->node_type == hl_ast_node_type_expr){

            if(!std::static_pointer_cast<ast_expression>(raw_initializer)->is_constant()){
                throw std::runtime_error("Loop initialization statement is not a compile time constant");
            }
            initializer = ast_expression::evaluate(std::static_pointer_cast<ast_expression>(raw_initializer));
        } else if(raw_initializer->node_type == hl_ast_node_type_operand){
            initializer = std::static_pointer_cast<ast_operand>(raw_initializer);
            if(initializer->get_type() == var_type_float_const){
                throw std::runtime_error("Floating point loop initializers are not supported");
            }
            if(initializer->get_type() != var_type_int_const){
                throw std::runtime_error("Loop initialization statement is not a compile time constant");
            }
        } else{
            throw std::runtime_error("Unsupported loop initialization statement type");
        }

        ret_val = initializer->get_int_value();

        return ret_val;
    }

    bool loop_unrolling_pass::evaluate_loop(const std::shared_ptr<ast_expression>& condition,
                                                   const std::shared_ptr<ast_expression>& ,
                                                   std::shared_ptr<ast_operand> &loop_var) {

        if(current_loop_iteration ==  max_loop_iterations){
            throw std::runtime_error("Loops with more than 65536 iterations are not supported");
        }

        std::shared_ptr<ast_expression> loop_cond = update_loop_condition(condition, loop_var);
        auto expr = ast_expression::evaluate(loop_cond);
        bool res = expr->get_int_value();
        ++current_loop_iteration;
        return res;
    }

    std::shared_ptr<ast_expression>
    loop_unrolling_pass::update_loop_condition(std::shared_ptr<ast_expression> expression,
                                                      std::shared_ptr<ast_operand> loop_var) {
        std::shared_ptr<ast_expression> ret_val = expression;
        loop_var->set_immediate((int)current_loop_iteration);
        update_expression(ret_val, loop_var);
        return ret_val;
    }

    void loop_unrolling_pass::update_expression(std::shared_ptr<ast_expression> expression, std::shared_ptr<ast_operand> loop_var) {
        if(expression->get_lhs().value()->node_type == hl_ast_node_type_operand){
            std::shared_ptr<ast_operand> node = std::static_pointer_cast<ast_operand>(expression->get_lhs().value());
            std::string var_name = node->get_name();
            std::string loop_var_name = loop_var->get_name();
            if(var_name == loop_var_name)
                expression->set_lhs(loop_var);
        } else if(expression->get_lhs().value()->node_type == hl_ast_node_type_expr){
            update_expression(std::static_pointer_cast<ast_expression>(expression->get_lhs().value()), std::move(loop_var));
        }
        if(expression->get_rhs()->node_type == hl_ast_node_type_operand){
            std::shared_ptr<ast_operand> node = std::static_pointer_cast<ast_operand>(expression->get_rhs());
            if(node->get_name() == loop_var->get_name())
                expression->set_rhs(loop_var);
        } else if(expression->get_rhs()->node_type == hl_ast_node_type_expr) {
            update_expression(std::static_pointer_cast<ast_expression>(expression->get_rhs()), std::move(loop_var));
        }
    }



    std::shared_ptr<ast_node>
    loop_unrolling_pass::substitute_index(std::shared_ptr<ast_node> element, std::string idx_name, int value) {
        switch (element->node_type) {
            case hl_ast_node_type_function_call:
                return substitute_index_in_function_call(std::static_pointer_cast<ast_call>(element), idx_name, value);
            case hl_ast_node_type_conditional:
                return substitute_index_in_conditional(std::static_pointer_cast<ast_conditional>(element), idx_name, value);
            case hl_ast_node_type_expr:
                return substitute_index_in_expression(std::static_pointer_cast<ast_expression>(element), idx_name, value);
            case hl_ast_node_type_operand:
                return substitute_index_in_operand(std::static_pointer_cast<ast_operand>(element), idx_name, value);;
            case hl_ast_node_type_definition:
                return substitute_index_in_definition(std::static_pointer_cast<ast_definition>(element), idx_name, value);
            default:
                throw std::runtime_error("An unexpected node type was present in the AST during loop unrolling.");
        }
    }

    std::shared_ptr<ast_expression>
    loop_unrolling_pass::substitute_index_in_expression(const std::shared_ptr<ast_expression>& node, const std::string& idx_name,
                                                               int value) {
        std::shared_ptr<ast_expression> retval = std::static_pointer_cast<ast_expression>(ast_node::deep_copy(node));
        if(node->is_immediate()){
            return retval;
        }

        if(auto lhs = node->get_lhs()) retval->set_lhs(substitute_index(lhs.value(), idx_name, value));
        if(auto ths = node->get_ths()) retval->set_ths(substitute_index(ths.value(), idx_name, value));

        retval->set_rhs(substitute_index(node->get_rhs(), idx_name, value));
        return retval;
    }

    std::shared_ptr<ast_operand>
    loop_unrolling_pass::substitute_index_in_operand(const std::shared_ptr<ast_operand>& node, const std::string& idx_name,
                                                            int value) {
        std::shared_ptr<ast_operand> retval = std::static_pointer_cast<ast_operand>(ast_operand::deep_copy(node));
        if(node->get_type() == var_type_scalar) {
            if(node->get_name() == idx_name) {
                std::shared_ptr<variable> const_var = std::make_shared<variable>(idx_name + "_" + std::to_string(current_loop_iteration-1),  (int) current_loop_iteration-1);
                return std::make_shared<ast_operand>(const_var);
            }
            return retval;
        }

        std::vector<std::shared_ptr<ast_node>> old_idx_array = retval->get_array_index();
        std::vector<std::shared_ptr<ast_node>> new_idx_array = proces_array_of_indices(old_idx_array,idx_name, value);

        retval->set_array_index(new_idx_array);
        return retval;
    }

    std::shared_ptr<ast_definition>
    loop_unrolling_pass::substitute_index_in_definition(const std::shared_ptr<ast_definition>& node, const std::string& idx_name,
                                                               int value) {
        std::shared_ptr<ast_definition> ret_val = std::static_pointer_cast<ast_definition>(ast_node::deep_copy(node));

        if(node->is_initialized()){
            if(node->is_scalar()){
                std::shared_ptr<ast_node> init = substitute_index(node->get_scalar_initializer(), idx_name, value);
                ret_val->set_scalar_initializer(init);
            } else {
                std::vector<std::shared_ptr<ast_node>> init;
                for(auto &item: node->get_array_initializer()){
                    init.push_back(substitute_index(item, idx_name, value));
                }
                ret_val->set_array_initializer(init);
            }

        }

        if(node->get_variable()->get_type() == var_type_array){
            ret_val->set_array_index(proces_array_of_indices(node->get_array_index(),idx_name, value));
        }
        return ret_val;
    }



    std::shared_ptr<ast_conditional>
    loop_unrolling_pass::substitute_index_in_conditional(const std::shared_ptr<ast_conditional> &node,
                                                                const std::string &idx_name, int value) {
        std::shared_ptr<ast_conditional> new_node = std::static_pointer_cast<ast_conditional>(ast_node::deep_copy(node));

        new_node->set_condition(substitute_index(new_node->get_condition(), idx_name, value));
        std::vector<std::shared_ptr<ast_node>> new_if_content;
        for(auto &item:new_node->get_if_block()){
            new_if_content.push_back(substitute_index(item, idx_name, value));
        }
        new_node->set_if_block(new_if_content);

        std::vector<std::shared_ptr<ast_node>> new_else_content;
        for(auto &item:new_node->get_else_block()){
            new_else_content.push_back(substitute_index(item, idx_name, value));
        }
        new_node->set_else_block(new_else_content);

        return new_node;
    }

    std::shared_ptr<ast_call>
    loop_unrolling_pass::substitute_index_in_function_call(const std::shared_ptr<ast_call> &node,
                                                                  const std::string &idx_name, int value) {
        std::vector<std::shared_ptr<ast_node>> new_args;
        for(auto &item:node->get_arguments()){
            new_args.push_back(substitute_index(item, idx_name, value));
        }
        node->set_arguments(new_args);
        return node;
    }

    std::vector<std::shared_ptr<ast_node>>
    loop_unrolling_pass::proces_array_of_indices(const std::vector<std::shared_ptr<ast_node>>& old_idx_array, const std::string& idx_name,
                                                        int value ) {
        std::vector<std::shared_ptr<ast_node>> new_idx_array;
        for(auto &item:old_idx_array){
            std::shared_ptr<ast_operand> old_idx = std::static_pointer_cast<ast_operand>(item);
            if(old_idx->get_name() == idx_name){
                std::shared_ptr<variable> var = std::make_shared<variable>(old_idx->get_name(), value);
                std::shared_ptr<ast_operand> idx = std::make_shared<ast_operand>(var);
                new_idx_array.push_back(idx);
            } else {
                new_idx_array.push_back(old_idx);
            }
        }
        return new_idx_array;
    }
}


