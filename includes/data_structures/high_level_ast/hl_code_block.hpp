

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

#ifndef FCORE_TOOLCHAIN_HL_CODE_BLOCK_HPP
#define FCORE_TOOLCHAIN_HL_CODE_BLOCK_HPP


#include "hl_ast_node.hpp"

namespace fcore{
    class hl_code_block : public hl_ast_node {
    public:
        hl_code_block();

        friend bool operator==(const hl_code_block& lhs, const hl_code_block& rhs){
            bool ret_val = true;

            if(lhs.content.empty() && rhs.content.empty()){
                ret_val &= true;
            } else if(lhs.content.empty() || rhs.content.empty()){
                ret_val = false;
            } else{
                bool body_equal = true;
                if(lhs.content.size() != rhs.content.size()) return false;

                for(uint32_t i = 0; i<lhs.content.size(); i++){
                    body_equal &=  hl_ast_node::compare_content_by_type(lhs.content[i], rhs.content[i]);
                }
                ret_val &= body_equal;
            }

            return ret_val;
        };

        static std::shared_ptr<hl_code_block> deep_copy(const std::shared_ptr<hl_code_block> &node);

        std::string pretty_print();

        // CONTENT MANIPULATION
        void add_content(const std::shared_ptr<hl_ast_node>& element) { content.push_back(element);};
        void set_content(const std::vector<std::shared_ptr<hl_ast_node>>& c) {content = c;};

        // CONTENT ACCESS
        virtual std::vector<std::shared_ptr<hl_ast_node>> get_content() {return content;};

    private:
        std::vector<std::shared_ptr<hl_ast_node>> content;

    };
}

#endif //FCORE_TOOLCHAIN_HL_CODE_BLOCK_HPP
