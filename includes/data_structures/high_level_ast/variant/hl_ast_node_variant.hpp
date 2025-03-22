

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

#ifndef FCORE_TOOLCHAIN_HL_AST_NODE_VARIANT_HPP
#define FCORE_TOOLCHAIN_HL_AST_NODE_VARIANT_HPP

#include <variant>
#include <vector>

#include "high_level_ast.hpp"

namespace fcore{

    class hl_ast_node_variant {
    public:

        virtual bool is_terminal();

        virtual std::string pretty_print();

        // CONTENT MANIPULATION
        void add_child(const hl_ast_node_variant& element);
        void set_children(const std::vector<hl_ast_node_variant>& c);

        // CONTENT ACCESS
        std::vector<hl_ast_node_variant> get_children();

    private:
        std::vector<hl_ast_node_variant> children;
        std::variant<
                ast_conditional,
                ast_loop,
                ast_operand,
                ast_definition,
                ast_expression,
                ast_call,
                ast_function_def
        > content;
    };
}



#endif //FCORE_TOOLCHAIN_HL_AST_NODE_VARIANT_HPP
