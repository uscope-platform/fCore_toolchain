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

//
// Created by filippo savi on 03/12/25.
//

#include "passes/instruction_stream/stall_insertion.hpp"

namespace fcore {
    stall_insertion::stall_insertion()
    : stream_pass_base("stall insertion", 1, true, high_level_pass) {

    }

    std::optional<instruction_variant> stall_insertion::apply_pass(const instruction_variant &element, uint32_t current_scan) {

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
            return element;
        } else {
            throw std::runtime_error("ERROR: unknown instruction type");
        }

    }

    std::optional<instruction_variant> stall_insertion::process(const register_instruction &node) {
        operations_tracker[node.get_destination()->get_bound_reg()] = fcore_execution_latencies[node.get_opcode()];
        return instruction_variant(node);
    }

    std::optional<instruction_variant> stall_insertion::process(const load_constant_instruction &node) {
        operations_tracker[node.get_destination()->get_bound_reg()] = fcore_execution_latencies["ldc"];
        return instruction_variant(node);
    }

    std::optional<instruction_variant> stall_insertion::process(const ternary_instruction &node) {
        operations_tracker[node.get_destination()->get_bound_reg()] = fcore_execution_latencies[node.get_opcode()];
        return instruction_variant(node);
    }

    std::optional<instruction_variant> stall_insertion::process(const conversion_instruction &node) {
        operations_tracker[node.get_destination()->get_bound_reg()] = fcore_execution_latencies[node.get_opcode()];
        return instruction_variant(node);
    }
}

