//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_INSTRUCTION_STREAM_HPP
#define FCORE_TOOLCHAIN_INSTRUCTION_STREAM_HPP

#include <vector>

#include "instruction_variant.hpp"

namespace fcore{
    class instruction_stream {
    public:
        void push_back(const instruction_variant& item);
        void push_back(const instruction_stream &vector);
        bool empty(instruction_stream &stream);
        unsigned long size(instruction_stream & stream);
        bool empty();
        unsigned long size();

        instruction_variant last() {return stream_store.back();};
        instruction_variant get(ssize_t i) {return stream_store[i];};


        auto begin() {return stream_store.begin();};
        auto end() {return stream_store.end();};

        auto cbegin() const {return stream_store.cbegin();};
        auto cend() const {return stream_store.cend();};

        auto begin() const {return stream_store.begin();};
        auto end() const {return stream_store.end();};



        friend bool operator==(const instruction_stream& lhs, const instruction_stream& rhs){
            bool retval = true;

            if(lhs.stream_store.size() != rhs.stream_store.size()){
                retval = false;
            } else{
                for(unsigned long i = 0; i<lhs.stream_store.size();++i){
                    retval &= lhs.stream_store[i] == rhs.stream_store[i];
                }
            }
            return retval;
        };

    private:

        std::vector<instruction_variant> stream_store;

    };
}


#endif //FCORE_TOOLCHAIN_INSTRUCTION_STREAM_HPP
