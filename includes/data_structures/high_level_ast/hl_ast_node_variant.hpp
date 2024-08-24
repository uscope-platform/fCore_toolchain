

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

    private:
        std::vector<std::variant<
                hl_ast_conditional_node,
                hl_ast_loop_node,
                hl_ast_operand,
                hl_definition_node,
                hl_expression_node,
                hl_function_call_node,
                hl_function_def_node
        >> content;
    };
}



#endif //FCORE_TOOLCHAIN_HL_AST_NODE_VARIANT_HPP
