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
        is_standalone = true;
        active_channels = ac;
    }

    instruction_stream result_deconfliction::standalone(const instruction_stream& in_stream){
        instruction_stream out_stream = in_stream;
        bool deconfliction_done = false;
        std::optional<instruction_stream> pass_result;
        while (!deconfliction_done){
            allocated_writeback_slots = std::vector(fcore_max_binary_size*active_channels, false);
            pass_result = deconflict(out_stream);
            deconfliction_done = pass_result.has_value();
            allocated_writeback_slots.clear();
        }
        return pass_result.value();
    }

    std::optional<instruction_stream> result_deconfliction::deconflict(instruction_stream& in){
        for (int i = 0; i< in.size(); i++){
            auto opcode = in[i].get_opcode();
            if (opcode == opcode_stop){
                return in;
            }
            for (int j = 0 ; j<active_channels; j++){
                auto writeback_index = i*active_channels + fcore_execution_latencies[opcode] +j;
                if (opcode == opcode_nop || opcode == opcode_efi ) {
                } else if (allocated_writeback_slots[writeback_index]){
                    in.insert(instruction_variant(independent_instruction(opcode_nop)), i);
                    return {};
                } else {
                    allocated_writeback_slots[writeback_index] = true;
                }
            }
        }
        return in;
    }
}
