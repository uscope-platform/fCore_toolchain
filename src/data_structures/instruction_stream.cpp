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

#include "data_structures/instruction_stream.hpp"

void instruction_stream::push_back(const std::shared_ptr<ll_instruction_node>& item) {
 stream_store.push_back(item);
}

void instruction_stream::push_back(const instruction_stream &stream_in) {
    stream_store.insert(stream_store.end(), stream_in.begin(), stream_in.end());
}

bool instruction_stream::empty(instruction_stream &store) {
    return store.empty();
}

unsigned long instruction_stream::size(instruction_stream &store) {
    return store.size();
}

bool instruction_stream::empty() {
    return stream_store.empty();
}

unsigned long instruction_stream::size() {
    return stream_store.size();
}


