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
// limitations under the License.02/07/2021.
//

#include "passes/instruction_stream/zero_assignment_removal_pass.hpp"

namespace fcore{

    zero_assignment_removal_pass::zero_assignment_removal_pass() :
            stream_pass_base("Zero assignment removal", 1, false){
        delete_intercalated_const = false;
    }

    std::optional<instruction_variant> zero_assignment_removal_pass::apply_pass(const instruction_variant &element, uint32_t n) {
        auto var = element.get_content();
        if(std::holds_alternative<load_constant_instruction>(var)) {
            auto instr = std::get<load_constant_instruction>(var);
            if(instr.get_destination()->get_name() == "r0"){
                delete_intercalated_const = true;
                return {};
            } else {
                return element;
            }
        } else if(std::holds_alternative<intercalated_constant>(var)){
            if(delete_intercalated_const){
                delete_intercalated_const = false;
                return {};
            } else {
                return element;
            }
        }  else {
            return element;
        }

    }
}
