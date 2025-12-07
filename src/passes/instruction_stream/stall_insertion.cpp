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


#include "passes/instruction_stream/stall_insertion.hpp"

namespace fcore {
    stall_insertion::stall_insertion()
    : stream_pass_base("stall insertion", 1, true, high_level_pass),
    operations_tracker({}) {
        is_vector = true;
    }

    std::vector<instruction_variant> stall_insertion::apply_vector_mutable_pass(instruction_variant &element,
        uint32_t n_pass, uint32_t n_instuction){

        auto var = element.get_content();
        if(std::holds_alternative<register_instruction>(var)) {
            return process(std::get<register_instruction>(var));
        } else if(std::holds_alternative<conversion_instruction>(var)){
            return process(std::get<conversion_instruction>(var));
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            return process(std::get<load_constant_instruction>(var));
        } else if(std::holds_alternative<ternary_instruction>(var)){
            return process(std::get<ternary_instruction>(var));
        } else if( std::holds_alternative<intercalated_constant>(var) || std::holds_alternative<independent_instruction>(var) || std::holds_alternative<pseudo_instruction>(var)){
            return {element};
        } else {
            throw std::runtime_error("ERROR: unknown instruction type");
        }

    }

    void stall_insertion::get_stalls(uint8_t reg, std::vector<instruction_variant> &instructions) {
        std::vector<instruction_variant> res;
        while(operations_tracker[reg] > 0){
            // INSERT NOP
            res.emplace_back(independent_instruction("nop"));
            advance_tracker(-1);
        }
        instructions.insert(instructions.end(), res.begin(), res.end());
    }

    void stall_insertion::advance_tracker(int exclusion){
        for (int i =0; i<operations_tracker.size(); i++){
            if (operations_tracker[i]> 0 && i != exclusion) operations_tracker[i]--;
        }
    }

    std::vector<instruction_variant> stall_insertion::process(const register_instruction &node){
        std::vector<instruction_variant>  result;
        auto dest  = node.get_destination()->get_bound_reg();
        auto op_a  = node.get_operand_a()->get_bound_reg();
        auto op_b  = node.get_operand_b()->get_bound_reg();

        if( (dest == -1 && node.get_opcode() != "bset" )|| op_a == -1 || (op_b == -1 && node.get_opcode() != "efi")) {
            throw std::runtime_error("Encountered unbound register while inserting pipeline delay slots");
        }
        get_stalls(op_a, result);
        get_stalls(op_b, result);
        result.emplace_back(node);
        operations_tracker[dest] = fcore_execution_latencies[node.get_opcode()];
        advance_tracker(dest);
        return result;
    }

    std::vector<instruction_variant> stall_insertion::process(const load_constant_instruction &node) {
        auto dest = node.get_destination()->get_bound_reg();
        operations_tracker[dest] = fcore_execution_latencies["ldc"];
        advance_tracker(dest);
        return {instruction_variant(node)};
    }

    std::vector<instruction_variant> stall_insertion::process(const ternary_instruction &node) {
        std::vector<instruction_variant>  result;
        auto dest  = node.get_destination()->get_bound_reg();
        auto op_a  = node.get_operand_a()->get_bound_reg();
        auto op_b  = node.get_operand_b()->get_bound_reg();
        auto op_c = node.get_operand_c()->get_bound_reg();
        if(dest == -1 || op_a == -1 || op_b == -1|| op_c == -1) {
            throw std::runtime_error("Encountered unbound register while inserting pipeline delay slots");
        }
        get_stalls(op_a, result);
        get_stalls(op_b, result);
        get_stalls(op_c, result);
        result.emplace_back(node);
        operations_tracker[dest] =  fcore_execution_latencies[node.get_opcode()];
        advance_tracker(dest);
        return result;
    }

    std::vector<instruction_variant>  stall_insertion::process(const conversion_instruction &node) {
        std::vector<instruction_variant>  result;
        auto dest  = node.get_destination()->get_bound_reg();
        auto src  = node.get_source()->get_bound_reg();
        if(dest == -1 || src == -1) {
            throw std::runtime_error("Encountered unbound register while inserting pipeline delay slots");
        }
        get_stalls(src, result);
        result.emplace_back(node);
        operations_tracker[dest] =  fcore_execution_latencies[node.get_opcode()];
        advance_tracker(dest);
        return result;
    }


}

