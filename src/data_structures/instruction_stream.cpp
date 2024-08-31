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

#include "data_structures/instruction_stream/instruction_stream.hpp"

namespace fcore{

    void instruction_stream::push_back(const instruction_variant& item) {
        stream_store.push_back(item);
    }

    void instruction_stream::push_back(const instruction_stream &stream_in) {
        for(auto &v:stream_in){
            stream_store.push_back(v);
        }
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



}

