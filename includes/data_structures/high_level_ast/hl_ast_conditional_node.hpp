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

#ifndef FCORE_TOOLCHAIN_HL_AST_CONDITIONAL_NODE_HPP
#define FCORE_TOOLCHAIN_HL_AST_CONDITIONAL_NODE_HPP

#include "data_structures/high_level_ast/hl_ast_node.hpp"


namespace fcore{
    class hl_ast_conditional_node : public hl_ast_node{
    public:
        hl_ast_conditional_node();
        void set_if_block(std::vector<std::shared_ptr<hl_ast_node>> node);
        std::vector<std::shared_ptr<hl_ast_node>> get_if_block();
        void set_else_block(std::vector<std::shared_ptr<hl_ast_node>> node);
        std::vector<std::shared_ptr<hl_ast_node>> get_else_block();
        void set_condition(std::shared_ptr<hl_ast_node> node);
        std::shared_ptr<hl_ast_node> get_condition();
        std::string pretty_print();
        void set_ternary(bool t){ternary_flag = t;};
        bool is_ternary() const{return ternary_flag;};
        friend bool operator==(const hl_ast_conditional_node& lhs, const hl_ast_conditional_node& rhs){
            bool ret_val = true;

            ret_val &= hl_ast_node::compare_vectors(lhs.if_block, rhs.if_block);
            ret_val &= hl_ast_node::compare_vectors(lhs.else_block, rhs.else_block);
            ret_val &= hl_ast_node::compare_content_by_type( lhs.condition, rhs.condition);
            ret_val &= lhs.ternary_flag == rhs.ternary_flag;

            return ret_val;
        };
        bool is_terminal() override {
            return false;
        }


        bool has_else() {return !else_block.empty();};

        static std::shared_ptr<hl_ast_conditional_node> deep_copy(const std::shared_ptr<hl_ast_conditional_node> &node);

    private:

        std::vector<std::shared_ptr<hl_ast_node>> if_block;
        std::vector<std::shared_ptr<hl_ast_node>> else_block;
        std::shared_ptr<hl_ast_node> condition;
        bool ternary_flag = false;
    };
}



#endif //FCORE_TOOLCHAIN_HL_AST_CONDITIONAL_NODE_HPP
