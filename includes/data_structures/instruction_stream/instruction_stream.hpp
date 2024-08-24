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

#include "ll_register_instr_node.hpp"
#include "ll_load_constant_instr_node.hpp"
#include "ll_intercalated_const_instr_node.hpp"
#include "ll_instruction_node.hpp"
#include "ll_independent_instr_node.hpp"
#include "ll_conversion_instr_node.hpp"
#include "ll_pseudo_instr_node.hpp"
#include "ll_ternary_instr_node.hpp"

namespace fcore{
    class instruction_stream {
    public:
        void push_back(const std::shared_ptr<ll_instruction_node>& item);
        void push_back(const instruction_stream &vector);
        bool empty(instruction_stream &stream);
        unsigned long size(instruction_stream & stream);
        bool empty();
        unsigned long size();

        std::shared_ptr<ll_instruction_node> last() {return stream_store.back();};
        std::shared_ptr<ll_instruction_node> get(ssize_t i) {return stream_store[i];};

        nlohmann::json dump();

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
                    retval &= ll_instruction_node::compare_content_by_type(lhs.stream_store[i],rhs.stream_store[i]);
                }
            }
            return retval;
        };

    private:

        std::vector<std::shared_ptr<ll_instruction_node>> stream_store;

    };
}


#endif //FCORE_TOOLCHAIN_INSTRUCTION_STREAM_HPP
