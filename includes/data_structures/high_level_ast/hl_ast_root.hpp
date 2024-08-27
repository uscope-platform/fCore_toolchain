

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

#ifndef FCORE_TOOLCHAIN_HL_AST_ROOT_HPP
#define FCORE_TOOLCHAIN_HL_AST_ROOT_HPP

#include "hl_ast_node.hpp"
#include <cstdint>
#include <memory>
#include <vector>

namespace fcore{

    class hl_ast_root : public hl_ast_node{
    public:
        hl_ast_root();
        friend bool operator==(const hl_ast_root& lhs, const hl_ast_root& rhs){
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

    private:
        std::vector<std::shared_ptr<hl_ast_node>> content;

    };
}


#endif //FCORE_TOOLCHAIN_HL_AST_ROOT_HPP
