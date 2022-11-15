// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.05/07/2021.
//

#include "passes/high_level/constant_propagation.hpp"

constant_propagation::constant_propagation() : pass_base<hl_ast_node>("Constant Propagation Pass"){
}

std::shared_ptr<hl_ast_node> constant_propagation::process_global(std::shared_ptr<hl_ast_node> element) {

    tracker.clear();

    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    std::vector<std::shared_ptr<hl_ast_node>> content = element->get_content();
    int instr_idx = 0;
    for(auto & i : content){
        if(!map_constants(i, instr_idx)) {
            new_content.push_back(i);
            instr_idx++;
       }
    }

    content.clear();
    content.reserve(new_content.size());

    for(int i = 0; i<new_content.size(); ++i){
        auto new_item = substitute_constant(new_content[i],i);
        map_assignments(new_content[i]);
        content.push_back(new_item);
    }


    element->set_content(content);

    return element;

}

std::shared_ptr<hl_ast_node> constant_propagation::substitute_constant(std::shared_ptr<hl_ast_node> element, int instr_idx) {

    if(element->node_type == hl_ast_node_type_expr){
        return substitute_constant(std::static_pointer_cast<hl_expression_node>(element), instr_idx);
    } else if(element->node_type == hl_ast_node_type_definition){
        return substitute_constant(std::static_pointer_cast<hl_definition_node>(element), instr_idx);
    } else if(element->node_type == hl_ast_node_type_operand){
        return substitute_constant(std::static_pointer_cast<hl_ast_operand>(element), instr_idx);
    } else{
        return element;
    }
}

std::shared_ptr<hl_ast_node> constant_propagation::substitute_constant(std::shared_ptr<hl_expression_node> element, int instr_idx) {
    if(element->is_immediate()){
        return element;
    }

    std::shared_ptr<hl_ast_node> new_rhs;

    if(element->get_rhs()->node_type == hl_ast_node_type_operand) {
        new_rhs = substitute_constant(std::static_pointer_cast<hl_ast_operand>(element->get_rhs()), instr_idx);
    } else {
        new_rhs = substitute_constant(element->get_rhs(), instr_idx);
    }
    element->set_rhs(new_rhs);

    if(!element->is_unary() && element->get_type() != expr_assign){
        std::shared_ptr<hl_ast_node> new_lhs;
        if(element->get_lhs()->node_type == hl_ast_node_type_operand) {
            std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
            new_lhs = substitute_constant(lhs, instr_idx);
        } else {
            new_lhs = substitute_constant(element->get_lhs(), instr_idx);
        }
        element->set_lhs(new_lhs);

    }
    return element;
}

std::shared_ptr<hl_ast_node> constant_propagation::substitute_constant(std::shared_ptr<hl_definition_node> element, int instr_idx) {
    if(element->is_initialized()){
        std::shared_ptr<hl_ast_node> initializer = element->get_scalar_initializer();
        if(initializer->node_type == hl_ast_node_type_operand){
            std::string constant_name = std::static_pointer_cast<hl_ast_operand>(initializer)->get_name();
            if(tracker.is_excluded(constant_name)){
                element->set_scalar_initializer(tracker.get_constant(constant_name, instr_idx));
            }
        } else {
            std::shared_ptr<hl_ast_node> new_init = substitute_constant(initializer, instr_idx);
            element->set_scalar_initializer(new_init);
        }
    }
    return element;
}



std::shared_ptr<hl_ast_operand> constant_propagation::substitute_constant(std::shared_ptr<hl_ast_operand> element, int instr_idx) {
    if(tracker.is_excluded(element->get_name())){
        return element;
    }

    if(element->get_type() != var_type_int_const && element->get_type() != var_type_float_const){
        if(element->get_type()==var_type_array){
            std::vector<std::shared_ptr<hl_ast_node>> new_idx;
            for (auto &item: element->get_array_index()) {
                new_idx.push_back(substitute_constant(item, instr_idx));
            }
            element->set_array_index(new_idx);
        }
        if(tracker.is_constant(element->get_name())){
            std::shared_ptr<hl_ast_operand> new_const = tracker.get_constant(element->get_name(), instr_idx);
            new_const->set_name(element->get_name());
            return new_const;
        } else{
            return element;
        }

    } else
        return element;
}

void constant_propagation::map_assignments(const std::shared_ptr<hl_ast_node>& element) {
    if(element->node_type == hl_ast_node_type_definition) {
        std::string var_name = std::static_pointer_cast<hl_definition_node>(element)->get_name();
        if(tracker.is_constant(var_name)){
            tracker.add_exclusion(var_name);
        }
    } else if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        if(node->get_type() == expr_assign){
            std::string var_name = std::static_pointer_cast<hl_ast_operand>(node->get_lhs())->get_name();
            if(tracker.is_constant(var_name)){
                tracker.add_exclusion(var_name);
            }

        }
    }
}

bool constant_propagation::map_constants(const std::shared_ptr<hl_ast_node>& element, int instr_idx) {

    if(element->node_type == hl_ast_node_type_definition) {
        return map_constants(std::static_pointer_cast<hl_definition_node>(element), instr_idx);
    } else if(element->node_type == hl_ast_node_type_expr){
        return map_constants(std::static_pointer_cast<hl_expression_node>(element), instr_idx);
    } else
        return false;

}

bool constant_propagation::map_constants(const std::shared_ptr<hl_definition_node>& element, int instr_idx) {

    if (element->get_name().rfind("IOM_init_constant_", 0) == 0) {
        return false;
    } else if (element->get_variable()->get_variable_class() != variable_regular_type || !element->is_initialized()) {
        return false;
    } else if (element->get_scalar_initializer()->node_type == hl_ast_node_type_operand) {
        std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(
                element->get_scalar_initializer());
        if (op->get_type() == var_type_float_const || op->get_type() == var_type_int_const)
            tracker.add_constant(element->get_name(), op, instr_idx);
        else return false;
    } else return false;

    return true;
}

bool constant_propagation::map_constants(const std::shared_ptr<hl_expression_node> &element, int instr_idx) {

    if(element->get_type() == expr_assign){
        std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
        if(lhs->get_variable()->get_variable_class()==variable_memory_type ||
        lhs->get_variable()->get_variable_class()==variable_output_type|| lhs->get_contiguity()){
            return false;
        } else {
            if(element->get_rhs()->node_type == hl_ast_node_type_operand){
                std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(element->get_rhs());
                if(op->get_type() == var_type_float_const || op->get_type() == var_type_int_const){
                    std::shared_ptr<hl_ast_operand> target = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
                    tracker.add_constant(target->get_name(), op, instr_idx);
                } else return false;
            } else return false;
        }
    } else return false;
    return true;
}
