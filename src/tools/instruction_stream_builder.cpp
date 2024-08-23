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

#include "tools/instruction_stream_builder.hpp"

fcore::instruction_stream fcore::instruction_stream_builder::build_stream(const std::shared_ptr<ll_ast_node>& tree) {
    instruction_stream stream;
    std::vector<std::shared_ptr<ll_ast_node>> content = tree->get_content();
    for(auto &item:content){

        if(item->type == ll_type_instr){
            auto node = std::static_pointer_cast<ll_instruction_node>(item);

            stream.push_back(node);
            if(node->get_opcode() == "ldc"){
                std::shared_ptr<ll_load_constant_instr_node> load_instr = std::static_pointer_cast<ll_load_constant_instr_node>(node);
                std::shared_ptr<ll_intercalated_const_instr_node> constant;
                if(load_instr->is_float()){
                    float desired_constant = load_instr->get_constant_f();
                    constant = std::make_shared<ll_intercalated_const_instr_node>(desired_constant);
                } else {
                    uint32_t desired_constant = load_instr->get_constant_i();
                    constant = std::make_shared<ll_intercalated_const_instr_node>(desired_constant);
                }
                stream.push_back(constant);
            }

        } else if(item->type == ll_type_code_block){
            instruction_stream substeam = build_stream(item);
            stream.push_back(substeam);
        } else{
            throw std::runtime_error("Forbidden ast node type reached the instruction stream builder");
        }
    }
    return stream;
}
