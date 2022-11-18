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
        bool const_found = map_constants(i, instr_idx);
        if(!const_found) {
            new_content.push_back(i);
            instr_idx++;
       } else {
            if(i->node_type == hl_ast_node_type_definition){
                auto def_class = std::static_pointer_cast<hl_definition_node>(i)->get_variable()->get_variable_class();
                if( def_class == variable_memory_type || def_class == variable_output_type){
                    new_content.push_back(i);
                    instr_idx++;
                }
            }
        }
    }

    content.clear();
    content.reserve(new_content.size());

    for(int i = 0; i<new_content.size(); ++i){
        auto new_item = propagate_constant(new_content[i],i);
        content.push_back(new_item);
    }


    element->set_content(content);

    return element;

}

std::shared_ptr<hl_ast_node> constant_propagation::propagate_constant(std::shared_ptr<hl_ast_node> element, int instr_idx) {

    if(element->node_type == hl_ast_node_type_expr){
        return propagate_constant(std::static_pointer_cast<hl_expression_node>(element), instr_idx);
    } else if(element->node_type == hl_ast_node_type_definition){
        return propagate_constant(std::static_pointer_cast<hl_definition_node>(element), instr_idx);
    } else if(element->node_type == hl_ast_node_type_operand){
        return propagate_constant(std::static_pointer_cast<hl_ast_operand>(element), instr_idx);
    } else{
        return element;
    }
}

std::shared_ptr<hl_ast_node> constant_propagation::propagate_constant(std::shared_ptr<hl_expression_node> element, int instr_idx) {
    if(element->is_immediate()){
        return element;
    }

    std::shared_ptr<hl_ast_node> new_rhs;

    if(element->get_rhs()->node_type == hl_ast_node_type_operand) {
        new_rhs = propagate_constant(std::static_pointer_cast<hl_ast_operand>(element->get_rhs()), instr_idx);
    } else {
        new_rhs = propagate_constant(element->get_rhs(), instr_idx);
    }
    element->set_rhs(new_rhs);

    if(!element->is_unary() && element->get_type() != expr_assign){
        std::shared_ptr<hl_ast_node> new_lhs;
        if(element->get_lhs()->node_type == hl_ast_node_type_operand) {
            std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
            new_lhs = propagate_constant(lhs, instr_idx);
        } else {
            new_lhs = propagate_constant(element->get_lhs(), instr_idx);
        }
        element->set_lhs(new_lhs);

    }
    return element;
}

std::shared_ptr<hl_ast_node> constant_propagation::propagate_constant(std::shared_ptr<hl_definition_node> element, int instr_idx) {
    if(element->is_initialized()){
        std::shared_ptr<hl_ast_node> initializer = element->get_scalar_initializer();
        if(initializer->node_type == hl_ast_node_type_operand){
            std::string constant_name = std::static_pointer_cast<hl_ast_operand>(initializer)->get_name();
            if(tracker.is_excluded(constant_name)){
                element->set_scalar_initializer(tracker.get_constant(constant_name, instr_idx));
            }
        } else {
            std::shared_ptr<hl_ast_node> new_init = propagate_constant(initializer, instr_idx);
            element->set_scalar_initializer(new_init);
        }
    }
    return element;
}



std::shared_ptr<hl_ast_operand> constant_propagation::propagate_constant(std::shared_ptr<hl_ast_operand> element, int instr_idx) {
    if(tracker.is_excluded(element->get_name())){
        return element;
    }
    std::shared_ptr<hl_ast_operand> ret_operand;

    if(element->get_type() != var_type_int_const && element->get_type() != var_type_float_const){
        if(element->get_type()==var_type_array){
            std::vector<std::shared_ptr<hl_ast_node>> new_idx;
            for (auto &item: element->get_array_index()) {
                new_idx.push_back(propagate_constant(item, instr_idx));
            }
            element->set_array_index(new_idx);
            ret_operand = element;
            if(element->get_array_index().size() == 1){
                auto idx = std::static_pointer_cast<hl_ast_operand>(element->get_array_index()[0]);
                if(idx->get_variable()->is_constant()){
                    if(tracker.is_constant(element->get_name(), instr_idx,idx->get_int_value())){
                        std::shared_ptr<hl_ast_operand> new_const = tracker.get_constant(element->get_name(), instr_idx,idx->get_int_value());
                        new_const->set_name(element->get_name());
                        ret_operand =  new_const;
                    }
                }
            }

        } else{
            if(tracker.is_constant(element->get_name(), instr_idx)){
                std::shared_ptr<hl_ast_operand> new_const = tracker.get_constant(element->get_name(), instr_idx);
                new_const->set_name(element->get_name());
                ret_operand =  new_const;
            } else{
                ret_operand =  element;
            }
        }

    } else{
        ret_operand =  element;
    }

    if(element->get_variable()->get_bound_reg() != -1){
        ret_operand->get_variable()->set_bound_reg(element->get_variable()->get_bound_reg());
    }
    return ret_operand;
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
    if (
        element->get_name().rfind("IOM_init_constant_", 0) != 0 &&
        element->get_variable()->get_variable_class() != variable_input_type &&
        element->is_initialized() &&
        element->get_scalar_initializer()->node_type == hl_ast_node_type_operand
    ) {
        if(element->is_scalar()){
            std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(element->get_scalar_initializer());
            if (op->get_type() == var_type_float_const || op->get_type() == var_type_int_const){
                tracker.add_constant(element->get_name(), op, instr_idx);
                return true;
            }
        } else {
            auto array_init = element->get_array_initializer();
            for(int i = 0; i<array_init.size(); i++){
                std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(array_init[i]);
                if (op->get_type() == var_type_float_const || op->get_type() == var_type_int_const){
                    tracker.add_constant(element->get_name(), op, instr_idx, i);
                }
            }
            return true;
        }

    }

    return false;
}

bool constant_propagation::map_constants(const std::shared_ptr<hl_expression_node> &element, int instr_idx) {


    if(element->get_type() == expr_assign){
        std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
        analyze_assignment(element, instr_idx);
        if(
            lhs->get_variable()->get_variable_class() != variable_memory_type &&
            lhs->get_variable()->get_variable_class() != variable_output_type &&
            !lhs->get_contiguity()
        ){
            if(element->get_rhs()->node_type == hl_ast_node_type_operand){
                std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(element->get_rhs());
                if(op->get_type() == var_type_float_const || op->get_type() == var_type_int_const){
                    std::shared_ptr<hl_ast_operand> target = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());
                    tracker.add_constant(target->get_name(), op, instr_idx);
                    return true;
                }
            }
        }
    }
    return false;
}

void constant_propagation::analyze_assignment(const std::shared_ptr<hl_expression_node> &element, int instr_idx) {
    std::shared_ptr<hl_ast_operand> lhs = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());

    if(needs_termination(element, instr_idx)){
        if(!lhs->get_array_index().empty()){
            if(lhs->get_array_index()[0]->node_type != hl_ast_node_type_operand){
                tracker.terminate_all_constant_ranges(lhs->get_name(), instr_idx+1);
            } else{
                auto op = std::static_pointer_cast<hl_ast_operand>(lhs->get_array_index()[0]);
                if(op->get_variable()->is_constant()){
                    // TODO: somehow constant range termination fucks up and terminates early for the first definition
                    tracker.terminate_constant_range(lhs->get_name(), instr_idx+1, op->get_int_value());
                }
            }
        } else {
            tracker.terminate_constant_range(lhs->get_name(), instr_idx+1);
        }
    }
}


bool constant_propagation::needs_termination(const std::shared_ptr<hl_expression_node> &element, int instr_idx) {
    bool needs_termination = false;
    bool analyze_rhs;
    auto dest = std::static_pointer_cast<hl_ast_operand>(element->get_lhs());

    if(dest->get_variable()->get_type() == var_type_array){
        int array_idx = std::static_pointer_cast<hl_ast_operand>(dest->get_array_index()[0])->get_int_value();
        analyze_rhs = tracker.is_constant(dest->get_name(), instr_idx, array_idx);
    } else {
        analyze_rhs = tracker.is_constant(dest->get_name(), instr_idx);
    }

    if(analyze_rhs){
        if(element->get_rhs()->node_type != hl_ast_node_type_operand){
            // ONLY OPERANDS CAN BE CONSTANT, THUS TERMINATE THE RANGE
            needs_termination = true;
        } else {
            if(!std::static_pointer_cast<hl_ast_operand>(element->get_rhs())->get_variable()->is_constant()){
                // TERMINATE THE RANGE AS THE ASSIGNMENT IS NOT CONSTANT
                needs_termination = true;
            }
        }
    }
    return needs_termination;
}

