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

#include "data_structures/instruction_stream/ll_pseudo_instr_node.hpp"



fcore::ll_pseudo_instr_node::ll_pseudo_instr_node(std::string op, std::vector<std::shared_ptr<variable>> args)
: ll_instruction_node(isa_pseudo_instruction){
 opcode = std::move(op);
 arguments = std::move(args);
}

int fcore::ll_pseudo_instr_node::instruction_count() {
    return 1;
}

nlohmann::json fcore::ll_pseudo_instr_node::dump() {
    nlohmann::json retval = ll_instruction_node::dump();

    std::vector<nlohmann::json> args_dump;
    for(auto &i:arguments){
        args_dump.push_back(i->dump());
    }
    retval["arguments"] = args_dump;
    return retval;
}
