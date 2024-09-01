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
// limitations under the License.
//

#include "passes/instruction_stream/constant_merging.hpp"

namespace fcore{

    constant_merging::constant_merging(std::shared_ptr<std::unordered_map<std::string, std::pair<int,int>>> lam) :
            stream_pass_base("constant merging pass", 1, false){
        delete_intercalated_const = false;
        assignments_map = std::move(lam);
        idx = 0;
    }

    std::optional<instruction_variant> constant_merging::apply_pass(const instruction_variant &element, uint32_t n) {
        map_exclusions(element);

        std::shared_ptr<variable> dest;
        idx++;

        auto var = element.get_content();
        if(std::holds_alternative<register_instruction>(var)) {
            return merge_register_inst(std::get<register_instruction>(var));
        } else if(std::holds_alternative<conversion_instruction>(var)){
            return merge_conv_instr(std::get<conversion_instruction>(var));
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            return merge_load_const_instr(std::get<load_constant_instruction>(var));
        } else if(std::holds_alternative<ternary_instruction>(var)){
            return merge_ternary_inst(std::get<ternary_instruction>(var));
        } else if(std::holds_alternative<intercalated_constant>(var)){
            return merge_interc_const(std::get<intercalated_constant>(var));
        } else if(std::holds_alternative<independent_instruction>(var)){
            return element;
        } else if(std::holds_alternative<pseudo_instruction>(var)){
            return element;
        } else {
            throw std::runtime_error("Invalid instruction type reached variable mapping stage");
        }
    }


    void constant_merging::map_exclusions(const instruction_variant &element) {

        std::shared_ptr<variable> dest;
        auto var = element.get_content();
        if(std::holds_alternative<register_instruction>(var)) {
            dest = std::get<register_instruction>(var).get_destination();
        } else if(std::holds_alternative<conversion_instruction>(var)){
            dest = std::get<conversion_instruction>(var).get_destination();
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            dest = std::get<load_constant_instruction>(var).get_destination();
        } else if(std::holds_alternative<ternary_instruction>(var)){
            dest = std::get<ternary_instruction>(var).get_destination();
        } else if(std::holds_alternative<independent_instruction>(var) || std::holds_alternative<intercalated_constant>(var) || std::holds_alternative<pseudo_instruction>(var) ) {
            return;
        } else {
            throw std::runtime_error("Invalid instruction type reached variable mapping stage");
        }

        if(processed_constants.contains(dest->get_identifier())){
            processed_constants.erase(dest->get_identifier());
        }

    }

    instruction_variant constant_merging::merge_register_inst(register_instruction&instr) {
        std::vector<std::shared_ptr<variable>> new_args;


        auto op = instr.get_operand_a();
        if(op->is_constant() || processed_constants.contains(op->get_identifier())){
            new_args.push_back(get_merged_constant(op));
        } else{
            new_args.push_back(op);
        }

        op = instr.get_operand_b();
        if(instr.get_operand_b()->is_constant() || processed_constants.contains(op->get_identifier())){
            new_args.push_back(get_merged_constant(op));
        } else{
            new_args.push_back(op);
        }
        new_args.push_back(instr.get_destination());
        instr.set_arguments(new_args);
        return instruction_variant(instr);
    }

    instruction_variant constant_merging::merge_ternary_inst(ternary_instruction &instr) {
        std::vector<std::shared_ptr<variable>> new_args;

        auto op = instr.get_operand_a();
        if(op->is_constant() || processed_constants.contains(op->get_identifier())){
            new_args.push_back(get_merged_constant(op));
        } else{
            new_args.push_back(op);
        }

        op = instr.get_operand_b();
        if(instr.get_operand_b()->is_constant() || processed_constants.contains(op->get_identifier())){
            new_args.push_back(get_merged_constant(op));
        } else{
            new_args.push_back(op);
        }

        op = instr.get_operand_c();
        if(instr.get_operand_c()->is_constant() || processed_constants.contains(op->get_identifier())){
            new_args.push_back(get_merged_constant(op));
        } else{
            new_args.push_back(op);
        }


        new_args.push_back(instr.get_destination());
        instr.set_arguments(new_args);
        return instruction_variant(instr);
    }

    instruction_variant constant_merging::merge_conv_instr(conversion_instruction &instr) {
        std::vector<std::shared_ptr<variable>> new_args;
        if(is_last_io_assignment(instr.get_destination())){
            return instruction_variant(instr);
        }

        auto op = instr.get_source();
        if(op->is_constant() || processed_constants.contains(op->get_identifier())){
            new_args.push_back(get_merged_constant(op));
        } else{
            new_args.push_back(op);
        }
        new_args.push_back(instr.get_destination());
        instr.set_arguments(new_args);
        return instruction_variant(instr);
    }

    std::optional<instruction_variant>  constant_merging::merge_load_const_instr(load_constant_instruction &instr) {
        if(is_last_io_assignment(instr.get_destination())){
            return instruction_variant(instr);
        }

        processed_constants.insert(instr.get_destination()->get_identifier());

        if(instr.is_float()){
            if(float_const_map.contains(instr.get_constant_f())){

                reassignments_map[instr.get_destination()->get_identifier()] = float_const_map[instr.get_constant_f()];
                delete_intercalated_const = true;
                return {};
            } else {
                float_const_map[instr.get_constant_f()] = instr.get_destination();
                reassignments_map[instr.get_destination()->get_identifier()] = instr.get_destination();
                return instruction_variant(instr);
            }
        } else{
            if(int_const_map.contains(instr.get_constant_i())){
                reassignments_map[instr.get_destination()->get_identifier()] = int_const_map[instr.get_constant_i()];
                delete_intercalated_const = true;
                return {};
            } else {
                int_const_map[instr.get_constant_i()] = instr.get_destination();
                reassignments_map[instr.get_destination()->get_identifier()] = instr.get_destination();
                return instruction_variant(instr);
            }
        }
    }

    std::optional<instruction_variant> constant_merging::merge_interc_const(intercalated_constant &instr) {
        if(!delete_intercalated_const){
            return instruction_variant(instr);
        } else {
            delete_intercalated_const = false;
            return {};
        }

    }

    std::shared_ptr<variable> constant_merging::get_merged_constant(std::shared_ptr<variable> v) {
        auto var_name = v->get_identifier();
        if(!processed_constants.contains(var_name)){
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

    bool constant_merging::is_last_io_assignment(const std::shared_ptr<variable> &dest) {
        if(dest->get_variable_class().iom_spec == variable_output_type || dest->get_variable_class().iom_spec == variable_memory_type){
            if(assignments_map->contains(dest->get_identifier())){
                auto last_assignment_idx = assignments_map->at(dest->get_identifier()).second;
                if( last_assignment_idx== idx || last_assignment_idx == -1){
                    return true;
                }
            }
        }
        return false;
    }

}
