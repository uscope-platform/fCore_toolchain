//
// Created by fils on 28/07/2021.
//

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
