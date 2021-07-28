//
// Created by fils on 28/07/2021.
//

#ifndef FCORE_TOOLCHAIN_INSTRUCTION_STREAM_BUILDER_HPP
#define FCORE_TOOLCHAIN_INSTRUCTION_STREAM_BUILDER_HPP

#include "data_structures/instruction_stream.hpp"

class instruction_stream_builder {
public:
    static instruction_stream build_stream(const std::shared_ptr<ll_ast_node>& tree);

};


#endif //FCORE_TOOLCHAIN_INSTRUCTION_STREAM_BUILDER_HPP
