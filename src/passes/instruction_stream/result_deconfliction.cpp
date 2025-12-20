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


#include "passes/instruction_stream/result_deconfliction.hpp"

namespace fcore {

    result_deconfliction::result_deconfliction(uint8_t ac) :
    stream_pass_base("results deconfliction", 2, true, high_level_pass){
        is_vector = true;
        active_channels = ac;
        instruction_counter = 0;
    }

    void result_deconfliction::setup(){
        stream_pass_base::setup();
    }


    std::vector<instruction_variant> result_deconfliction::apply_vector_mutable_pass(
        instruction_variant& element, uint32_t n_pass) {
        std::vector<instruction_variant> result;

        auto var = element.get_content();
        opcode_table_t opcode;
        if(std::holds_alternative<register_instruction>(var)) {
            opcode = std::get<register_instruction>(var).get_opcode();
        } else if(std::holds_alternative<conversion_instruction>(var)){
            opcode = std::get<conversion_instruction>(var).get_opcode();
        } else if(std::holds_alternative<load_constant_instruction>(var)){
            opcode = std::get<load_constant_instruction>(var).get_opcode();
        } else if(std::holds_alternative<ternary_instruction>(var)){
            opcode = std::get<ternary_instruction>(var).get_opcode();
        } else if( std::holds_alternative<independent_instruction>(var)){
            opcode = std::get<independent_instruction>(var).get_opcode();
        } else if(  std::holds_alternative<pseudo_instruction>(var)) {
            throw std::runtime_error("ERROR: pseudo  instructions should not reach result deconfliction");
        } else {
            throw std::runtime_error("ERROR: unknown instruction type");
        }
        if (n_pass == 0){
            if (opcode == opcode_stop || opcode == opcode_nop){
                instruction_counter++;
                return{};
            }
            // TODO: EVALUATE HOW THE MULTICHANNEL MODE AFFECTS WRITEBACK collisions
            auto writeback_index = instruction_counter + fcore_execution_latencies[opcode];
            if (allocated_writeback_slots[writeback_index]){
                delay_slot_addresses.insert(instruction_counter);
            }
            allocated_writeback_slots[writeback_index] = true;
            instruction_counter++;
            if (opcode == opcode_ldc) instruction_counter++;
        } else {
            if (delay_slot_addresses.contains(instruction_counter)){
                result.emplace_back(independent_instruction(opcode_nop));
                result.emplace_back(element);
            } else {
                result.emplace_back(element);
            }
            instruction_counter++;
            if (opcode == opcode_ldc) instruction_counter++;
        }

        return result;
    }

    void result_deconfliction::inter_pass(){
        instruction_counter = 0;
    }
}
