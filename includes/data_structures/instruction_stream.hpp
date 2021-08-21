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
