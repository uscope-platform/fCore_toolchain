//
// Created by fils on 28/07/2021.
//

#ifndef FCORE_TOOLCHAIN_INSTRUCTION_STREAM_HPP
#define FCORE_TOOLCHAIN_INSTRUCTION_STREAM_HPP

#include <vector>
#include "data_structures/low_level_ast/low_level_ast.hpp"

class instruction_stream {
public:
    void push_back(const std::shared_ptr<ll_instruction_node>& item);
    void push_back(const instruction_stream &vector);
    static bool empty(instruction_stream &stream);
    static unsigned long size(instruction_stream & stream);
    bool empty();
    unsigned long size();



    auto begin() {return stream_store.begin();};
    auto end() {return stream_store.end();};

    auto cbegin() const {return stream_store.cbegin();};
    auto cend() const {return stream_store.cend();};

    auto begin() const {return stream_store.begin();};
    auto end() const {return stream_store.end();};

private:

    std::vector<std::shared_ptr<ll_instruction_node>> stream_store;

};


#endif //FCORE_TOOLCHAIN_INSTRUCTION_STREAM_HPP
