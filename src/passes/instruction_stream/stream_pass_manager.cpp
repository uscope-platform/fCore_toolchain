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
// limitations under the License.

#include "passes/instruction_stream/stream_pass_manager.hpp"


stream_pass_manager::stream_pass_manager(std::unordered_map<std::string, std::shared_ptr<variable>> &iom) {
    iom_map = iom;
    std::shared_ptr<variable_map> var_map = std::make_shared<variable_map>();

    passes.push_back(std::make_shared<variable_mapping>(var_map));
    passes.push_back(std::make_shared<variable_lifetime_mapping>(var_map));
    passes.push_back(std::make_shared<register_allocation>(var_map, iom_map));
}

instruction_stream stream_pass_manager::process_stream(instruction_stream stream) {
    instruction_stream ret_val = std::move(stream);
    for(auto &pass:passes){
        ret_val = apply_pass(ret_val, pass);
    }

    return ret_val;
}

instruction_stream
stream_pass_manager::apply_pass(const instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass) {
    instruction_stream retval;
    for(auto &instr:in_stream){
        retval.push_back(pass->apply_pass(instr));
    }
    return retval;
}
