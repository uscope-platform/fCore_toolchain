//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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


#include "passes/instruction_stream/io_constant_tracking.hpp"

#include <utility>

namespace fcore{

    io_constant_tracking::io_constant_tracking(std::shared_ptr<std::unordered_map<std::string, std::pair<int,int>>> lam) :
            stream_pass_base("io_constant_tracking", 1, false){
        index = 0;
        last_assignment_map = std::move(lam);
    }

    std::optional<instruction_variant> io_constant_tracking::apply_pass(const instruction_variant &element, uint32_t n) {
        auto var = element.get_content();
        std::shared_ptr<variable> dest;
        if(std::holds_alternative<register_instruction>(var)) {
            dest = std::get<register_instruction>(var).get_destination();
        } else if(std::holds_alternative<conversion_instruction>(var)) {
            dest = std::get<conversion_instruction>(var).get_destination();
        } else if(std::holds_alternative<load_constant_instruction>(var)) {
            dest = std::get<load_constant_instruction>(var).get_destination();
        } else {
            return element;
        }

        if(dest->get_variable_class() ==variable_output_type ||dest->get_variable_class() ==variable_input_type){
            add_assignment(dest->get_identifier());
        }

        index++;
        return element;
    }

    void io_constant_tracking::add_assignment(const std::string& s) {
        if(last_assignment_map->contains(s)){
            last_assignment_map->at(s) = {last_assignment_map->at(s).first, index};
        } else {
            last_assignment_map->insert({s, {index, -1}});
        }
    }
}