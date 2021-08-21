// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#include "tools/instruction_stream_builder.hpp"

instruction_stream instruction_stream_builder::build_stream(const std::shared_ptr<ll_ast_node>& tree) {
    instruction_stream stream;
    std::vector<std::shared_ptr<ll_ast_node>> content = tree->get_content();
    for(auto &item:content){
        if(item->type == ll_type_instr){
            stream.push_back(std::static_pointer_cast<ll_instruction_node>(item));
        } else if(item->type == ll_type_code_block){
            instruction_stream substeam = build_stream(item);
            stream.push_back(substeam);
        } else{
            throw std::runtime_error("ERROR: Forbidden ast node type reached the instruction stream builder");
        }
    }
    return stream;
}
