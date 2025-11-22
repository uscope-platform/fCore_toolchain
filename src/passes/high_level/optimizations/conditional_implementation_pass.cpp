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

#include "passes/high_level/optimizations/conditional_implementation_pass.h"
#include <spdlog/spdlog.h>

namespace fcore{

    conditional_implementation_pass::conditional_implementation_pass() : pass_base("Conditional Implementation pass"){

    }

    std::shared_ptr<ast_code_block> conditional_implementation_pass::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {
        std::shared_ptr<ast_code_block> ret_val = std::make_shared<ast_code_block>();

        std::vector<std::shared_ptr<ast_node>> body;

        for(const auto& item:element->get_content()){
            std::vector<std::shared_ptr<ast_node>> selected_branch = process_block_by_type(item, element);
            body.insert(body.end(),selected_branch.begin(), selected_branch.end());
        }

        ret_val->set_content(body);
        return ret_val;
    }


    std::vector<std::shared_ptr<ast_node>>
    conditional_implementation_pass::process_block_by_type(const std::shared_ptr<ast_node> &node,
                                                                  const std::shared_ptr<ast_code_block> &subtree) {

        switch (node->node_type) {
            case hl_ast_node_type_loop:
                return process_loop(std::static_pointer_cast<ast_loop>(node), subtree);
            case hl_ast_node_type_conditional:
                return process_conditional(std::static_pointer_cast<ast_conditional>(node), subtree);
            case hl_ast_node_type_definition:
                return process_definition(std::static_pointer_cast<ast_definition>(node), subtree);
            case hl_ast_node_type_expr:
                return process_expression(std::static_pointer_cast<ast_expression>(node), subtree);
            default:
                return {node};
        }

    }

    std::vector<std::shared_ptr<ast_node>>
    conditional_implementation_pass::process_loop(const std::shared_ptr<ast_loop> &node,
                                                         const std::shared_ptr<ast_code_block> &subtree) {



        std::vector<std::shared_ptr<ast_node>> new_block_content;
        for(auto &loop_instr:node->get_loop_content()){
            if(loop_instr->node_type == hl_ast_node_type_conditional){
                std::shared_ptr<ast_conditional> instr_node = std::static_pointer_cast<ast_conditional>(loop_instr);
                std::vector<std::shared_ptr<ast_node>> selected_branch = process_conditional(instr_node, subtree);
                new_block_content.insert(new_block_content.end(),selected_branch.begin(), selected_branch.end());
            } else{
                new_block_content.push_back(loop_instr);
            }
        }
        node->set_loop_content(new_block_content);
        return {node};
    }

    std::vector<std::shared_ptr<ast_node>>
    conditional_implementation_pass::process_definition(const std::shared_ptr<ast_definition> &node,
                                                               const std::shared_ptr<ast_code_block> &subtree) {
        if(node->is_initialized()){
            if(node->is_scalar()){
                auto initializer = node->get_scalar_initializer();
                if(initializer->node_type == hl_ast_node_type_conditional){
                    auto cond = std::static_pointer_cast<ast_conditional>(initializer);
                    if(cond->is_ternary()){
                        node->set_scalar_initializer(process_ternary(cond));
                    } else {
                        throw std::runtime_error("Unexpected non ternary conditional found in variable initialization");
                    }
                }
            } else {
                auto init_v = node->get_array_initializer();
                std::vector<std::shared_ptr<ast_node>> new_initializer;
                for(auto & item:init_v){
                    if(item->node_type == hl_ast_node_type_conditional){
                        auto cond = std::static_pointer_cast<ast_conditional>(item);
                        if(cond->is_ternary()){
                            new_initializer.push_back(process_ternary(cond));
                        } else {
                            throw std::runtime_error("Unexpected non ternary conditional found in variable initialization");
                        }
                    } else{
                        new_initializer.push_back(item);
                    }
                }
                node->set_array_initializer(new_initializer);
            }
        }
        return {node};
    }

    std::vector<std::shared_ptr<ast_node>>
    conditional_implementation_pass::process_expression(const std::shared_ptr<ast_expression> &node,
                                                               const std::shared_ptr<ast_code_block> &subtree) {
        if(node->get_type()== ast_expression::ASSIGN){
            auto rhs = node->get_rhs();
            if(rhs->node_type==hl_ast_node_type_conditional){
                auto cond = std::static_pointer_cast<ast_conditional>(rhs);
                node->set_rhs(process_ternary(cond));
            }
        }
        return {node};
    }


    std::vector<std::shared_ptr<ast_node>>
    conditional_implementation_pass::process_conditional(const std::shared_ptr<ast_conditional>& node, const std::shared_ptr<ast_code_block>& subtree) {
        std::vector<std::shared_ptr<ast_node>> result_body;

        std::shared_ptr<ast_expression> condition = std::static_pointer_cast<ast_expression>(node->get_condition());
        std::shared_ptr<ast_operand> lhs_op, rhs_op;
        auto raw_lhs = get_operands(condition->get_lhs().value(), node, subtree->get_content());
        auto raw_rhs = get_operands(condition->get_rhs(), node, subtree->get_content());

        bool ternarize_loop = false;
        if(raw_lhs.has_value()) {
            lhs_op = raw_lhs.value();
        } else {
            ternarize_loop = true;
        }

        if(raw_rhs.has_value()) {
            rhs_op = raw_rhs.value();
        } else {
            ternarize_loop = true;
        }

        if(node->is_ternary()) {
            return {process_ternary(node)};
        }

        if(ternarize_loop) {
            return conditional_to_ternary(node, subtree);
        }


        std::shared_ptr<ast_expression> const_cond_expr = std::make_shared<ast_expression>(condition->get_type());
        const_cond_expr->set_lhs(lhs_op);
        const_cond_expr->set_rhs(rhs_op);

        std::shared_ptr<ast_operand> result_op =  ast_expression::evaluate(const_cond_expr);
        bool result;
        if(result_op->get_type() == var_type_int_const) result = result_op->get_int_value();
        if(result_op->get_type() == var_type_float_const) result = result_op->get_float_val() == 1;

        if(result){
            std::vector<std::shared_ptr<ast_node>> selected_block = node->get_if_block();
            result_body.insert(result_body.end(), selected_block.begin(), selected_block.end());
        } else if(node->has_else()){
            std::vector<std::shared_ptr<ast_node>> selected_block = node->get_else_block();
            result_body.insert(result_body.end(), selected_block.begin(), selected_block.end());
        }
        return result_body;
    }


    std::optional<std::shared_ptr<ast_operand>> conditional_implementation_pass::find_variable_definition(const std::shared_ptr<ast_node>& subexpr,
                                                                     const std::shared_ptr<ast_node>& item,
                                                                     const std::vector<std::shared_ptr<ast_node>>& prog_content) {
        std::shared_ptr<ast_operand> retval;
        if(subexpr->node_type == hl_ast_node_type_expr){
            throw std::runtime_error("OH SNAP! Nested subexpression handling is not implemented yet");
        } else {
            std::shared_ptr<ast_operand> variable = std::static_pointer_cast<ast_operand>(subexpr);
            for(const auto& i: prog_content){
                if(i == item){
                    return {};
                } else if (i->node_type == hl_ast_node_type_definition){
                    std::shared_ptr<ast_definition> def = std::static_pointer_cast<ast_definition>(i);
                    if(def->get_name() == variable->get_name()){
                        if(def->is_initialized()){
                            if(def->get_scalar_initializer()->node_type == hl_ast_node_type_operand){
                                return std::static_pointer_cast<ast_operand>(def->get_scalar_initializer());
                            } else{
                                return find_variable_definition(def->get_scalar_initializer(), def, prog_content);
                            }
                        }
                    }
                }
            }
        }

        return retval;
    }


    std::optional<std::shared_ptr<ast_operand>>
    conditional_implementation_pass::get_operands(const std::shared_ptr<ast_node> &subexpr,
                                                         const std::shared_ptr<ast_node> &item,
                                                         const std::vector<std::shared_ptr<ast_node>> &prog_content) {
        std::shared_ptr<ast_operand> retval;
        if(subexpr->node_type != hl_ast_node_type_operand){
            auto def = find_variable_definition(subexpr, item, prog_content);
            if(def.has_value()) {
                retval = def.value();
            } else {
                throw std::runtime_error("Variable not found in conditional processing");
            }
        } else{
            variable_type_t vt = std::static_pointer_cast<ast_operand>(subexpr)->get_type();
            if(vt == var_type_scalar || vt == var_type_array){
                auto def = find_variable_definition(subexpr, item, prog_content);
                if(def.has_value()) {
                    retval = def.value();
                } else {
                    return {};
                }

            } else {
                retval = std::static_pointer_cast<ast_operand>(subexpr);
            }
        }
        return retval;
    }

    std::shared_ptr<ast_node>
    conditional_implementation_pass::process_ternary(const std::shared_ptr<ast_conditional> &node) {

        std::shared_ptr<ast_expression> ret = std::make_shared<ast_expression>(ast_expression::CSEL);
        ret->set_lhs(node->get_condition());
        ret->set_rhs(node->get_if_block()[0]);
        ret->set_ths(node->get_else_block()[0]);
        return ret;
    }

    std::vector<std::shared_ptr<ast_node>> conditional_implementation_pass::conditional_to_ternary(
        const std::shared_ptr<ast_conditional> &node, const std::shared_ptr<ast_code_block> &subtree) {
        std::vector<std::shared_ptr<ast_node>> ret_val;

        auto cond_name = "ternarized_selector_" +  std::to_string(ternarization_index);
        auto var = std::make_shared<variable>(cond_name);
        std::shared_ptr<ast_definition> condition_def = std::make_shared<ast_definition>(cond_name,c_type_int, var);
        condition_def->set_scalar_initializer(node->get_condition());
        ret_val.push_back(condition_def);

        struct ternary_map_t{
            std::shared_ptr<ast_node> target;
            std::shared_ptr<ast_node> if_block;
            std::shared_ptr<ast_node> else_block;
        };
        std::map<std::string, ternary_map_t> ternary_map;
        for(auto &raw_expr: node->get_if_block()) {
            if(raw_expr->node_type != hl_ast_node_type_expr) {
                throw("Encountered conditional block which can't be implemented with ternary");
            }
            auto expr = std::static_pointer_cast<ast_expression>(raw_expr);
            if(expr->get_type() != ast_expression::ASSIGN) {
                throw("Encountered conditional block which can't be implemented with ternary");
            }
            auto if_block = process_block_by_type(expr->get_rhs() ,subtree);
            if(if_block.size() != 1) {
                throw("nested if/else ternarization is not supported");
            }
            auto var = std::static_pointer_cast<ast_operand>(expr->get_lhs().value())->get_name();
            ternary_map[var] = {
                expr->get_lhs().value(), if_block[0], nullptr};
        }

        for(auto &raw_expr: node->get_else_block()) {
            if(raw_expr->node_type != hl_ast_node_type_expr) {
                throw("Encountered conditional block which can't be implemented with ternary");
            }
            auto expr = std::static_pointer_cast<ast_expression>(raw_expr);
            if(expr->get_type() != ast_expression::ASSIGN) {
                throw("Encountered conditional block which can't be implemented with ternary");
            }
            auto name = std::static_pointer_cast<ast_operand>(expr->get_lhs().value())->get_name();

            auto else_block = process_block_by_type(expr->get_rhs() ,subtree);
            if(else_block.size() != 1) {
                throw("nested if/else ternarization is not supported");
            }

            if(else_block[0]->node_type == hl_ast_node_type_expr) {
                if(std::static_pointer_cast<ast_expression>(else_block[0])->get_type() == ast_expression::CSEL) {

                    auto var_name = "extracted_ternary_" +  std::to_string(ternary_extraction);
                    std::shared_ptr<ast_definition> extracted_def = std::make_shared<ast_definition>(var_name,c_type_int, std::make_shared<variable>(var_name));
                    extracted_def->set_scalar_initializer(else_block[0]);
                    ret_val.insert(ret_val.begin(), extracted_def);

                    else_block[0] = std::make_shared<ast_operand>(std::make_shared<variable>(var_name));
                    ternary_extraction++;
                }
            }
            if(ternary_map.contains(name)) {
                ternary_map[name].else_block = else_block[0];
            } else {
                ternary_map[name] = {expr->get_lhs().value(), nullptr, else_block[0]};
            }
        }


        for(auto &conditional: ternary_map | std::views::values) {

            auto assignment = std::make_shared<ast_expression>(ast_expression::ASSIGN);
            assignment->set_lhs(conditional.target);


            auto  ternary = std::make_shared<ast_expression>(ast_expression::CSEL);
            ternary->set_lhs(std::make_shared<ast_operand>(var));

            if(conditional.if_block != nullptr) ternary->set_rhs(conditional.if_block);
            else ternary->set_rhs(conditional.target);

            if(conditional.else_block != nullptr) ternary->set_ths(conditional.else_block);
            else ternary->set_ths(conditional.target);

            assignment->set_rhs(ternary);

            ret_val.push_back(assignment);
        }

        ternarization_index++;
        return ret_val;
    }
}

