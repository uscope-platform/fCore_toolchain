

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

#include "passes/instruction_stream/ternary_deconfliction.hpp"

namespace fcore {
    ternary_deconfliction::ternary_deconfliction() : stream_pass_base("Ternary deconfliction", 2, true, high_level_pass){
        is_vector = true;

    }

    std::vector<instruction_variant> ternary_deconfliction::apply_vector_mutable_pass(instruction_variant &element,
        uint32_t n_pass) {
            if(n_pass==0) {
                map_ternaries(element);
                return {};
            } else if(n_pass==1) {
                return deconflict(element);
            } else {
                throw std::runtime_error("Invalid pass number");
            }
    }


    void ternary_deconfliction::map_ternaries(const instruction_variant &element) {
        if(std::holds_alternative<ternary_instruction>(element.get_content())){
            auto t = std::get<ternary_instruction>(element.get_content());
            auto t_name = t.get_operand_a()->get_name();
            if(condition_usage_map.contains(t_name)) {
                condition_usage_map[t_name]++;
            } else {
                condition_usage_map.insert({t_name, 1});
            }
        }
    }

    std::vector<instruction_variant> ternary_deconfliction::deconflict(instruction_variant &element) {
        if(std::holds_alternative<ternary_instruction>(element.get_content())){
            auto t = std::get<ternary_instruction>(element.get_content());
            auto t_name = t.get_operand_a()->get_name();
            if(condition_usage_map[t_name] > 1) {
                condition_usage_map[t_name]--;
                auto condition_name = t_name  + "_" + std::to_string(condition_progressives[t_name]);
                condition_progressives[t_name]++;
                auto new_cond = std::make_shared<variable>(condition_name);
                register_instruction move(
                    opcode_or,
                    t.get_operand_a(),
                    std::make_shared<variable>("r0"),
                    new_cond
                );
                t.set_operand_a(new_cond);
                instruction_variant v(t);
                auto ret = {instruction_variant(move), v};
                return ret;
            }
        }

        return {element};
    }
}
