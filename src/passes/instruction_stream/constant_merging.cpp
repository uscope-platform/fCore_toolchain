// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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

#include "passes/instruction_stream/constant_merging.hpp"

constant_merging::constant_merging() : stream_pass_base("constant merging pass"){
    delete_intercalated_const = false;
    idx = 0;
}

std::shared_ptr<ll_instruction_node> constant_merging::apply_pass(std::shared_ptr<ll_instruction_node> element) {
    idx++;
    switch (element->get_type()) {
        case isa_register_instruction:
            return merge_register_inst(std::static_pointer_cast<ll_register_instr_node>(element));
        case isa_conversion_instruction:
            return merge_conv_instr(std::static_pointer_cast<ll_conversion_instr_node>(element));
        case isa_independent_instruction:
            return element;
        case isa_intercalated_constant:
            return merge_interc_const(std::static_pointer_cast<ll_intercalated_const_instr_node>(element));
        case isa_load_constant_instruction:
            return merge_load_const_instr(std::static_pointer_cast<ll_load_constant_instr_node>(element));
        default:
            throw std::runtime_error("ERROR: Invalid instruction type reached variable mapping stage");
    }


}

std::shared_ptr<ll_instruction_node> constant_merging::merge_register_inst(const std::shared_ptr<ll_register_instr_node> &instr) {
    std::vector<std::shared_ptr<variable>> new_args;
    auto op = instr->get_operand_a();
    if(op->is_constant() || processed_constants.contains(op->get_name())){
        new_args.push_back(get_merged_constant(op));
    } else{
        new_args.push_back(op);
    }

    op = instr->get_operand_b();
    if(instr->get_operand_b()->is_constant() || processed_constants.contains(op->get_name())){
       new_args.push_back(get_merged_constant(op));
    } else{
       new_args.push_back(op);
    }
    new_args.push_back(instr->get_destination());
    instr->set_arguments(new_args);
    return instr;
}

std::shared_ptr<ll_instruction_node> constant_merging::merge_conv_instr(const std::shared_ptr<ll_conversion_instr_node> &instr) {
    std::vector<std::shared_ptr<variable>> new_args;
    auto op = instr->get_source();
    if(op->is_constant() || processed_constants.contains(op->get_name())){
        new_args.push_back(get_merged_constant(op));
    } else{
        new_args.push_back(op);
    }
    new_args.push_back(instr->get_destination());
    instr->set_arguments(new_args);
    return instr;
}

std::shared_ptr<ll_instruction_node> constant_merging::merge_load_const_instr(const std::shared_ptr<ll_load_constant_instr_node> &instr) {
    std::shared_ptr<ll_instruction_node> ret;
    auto vc = instr->get_destination()->get_variable_class();
    if(vc != variable_regular_type){
        iom_constants.insert(instr->get_destination()->get_name());
        return instr;
    }

    if(instr->is_float()){
        if(float_const_map.contains(instr->get_constant_f())){
            ret = nullptr;
            reassignments_map[instr->get_destination()->get_name()] = float_const_map[instr->get_constant_f()];
            delete_intercalated_const = true;
        } else {
            float_const_map[instr->get_constant_f()] = instr->get_destination();
            reassignments_map[instr->get_destination()->get_name()] = instr->get_destination();
            ret = instr;
        }
    } else{
        if(int_const_map.contains(instr->get_constant_i())){
            ret = nullptr;
            reassignments_map[instr->get_destination()->get_name()] = int_const_map[instr->get_constant_i()];
            delete_intercalated_const = true;
        } else {
            int_const_map[instr->get_constant_i()] = instr->get_destination();
            reassignments_map[instr->get_destination()->get_name()] = instr->get_destination();
            ret = instr;
        }
    }
    processed_constants.insert(instr->get_destination()->get_name());
    return ret;
}

std::shared_ptr<ll_instruction_node>
constant_merging::merge_interc_const(const std::shared_ptr<ll_intercalated_const_instr_node> &instr) {
    if(!delete_intercalated_const){
        return instr;
    } else {
        delete_intercalated_const = false;
        return nullptr;
    }

}

std::shared_ptr<variable> constant_merging::get_merged_constant(std::shared_ptr<variable> v) {
    auto var_name = v->get_name();
    if(!(iom_constants.contains(var_name) || processed_constants.contains(var_name))){
        return v;
    }
    if(reassignments_map.contains(var_name)){
        auto reass = reassignments_map[var_name];
        return reassignments_map[var_name];
    }
    if(v->is_float()) {
        return float_const_map[v->get_const_f()];
    } else{
        return int_const_map[v->get_const_i()];
    }

}
