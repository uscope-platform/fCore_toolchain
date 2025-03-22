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

#ifndef FCORE_TOOLCHAIN_AST_NODE_HPP
#define FCORE_TOOLCHAIN_AST_NODE_HPP

#include <string>

#include <nlohmann/json.hpp>

namespace fcore{

    typedef enum {
        hl_ast_node_type_expr = 1,
        hl_ast_node_type_definition = 2,
        hl_ast_node_type_conditional = 3,
        hl_ast_node_type_loop = 4,
        hl_ast_node_type_function_def = 5,
        hl_ast_node_type_operand = 6,
        hl_ast_node_type_function_call = 7,
        hl_ast_node_type_code_block = 8,
        hl_ast_node_type_struct = 9
    } hl_ast_node_type_t;

    constexpr std::string_view hl_ast_node_to_string(hl_ast_node_type_t i){
        switch (i) {
            case hl_ast_node_type_expr:return "hl_ast_node_type_expr";
            case hl_ast_node_type_definition: return "hl_ast_node_type_definition";
            case hl_ast_node_type_conditional: return "hl_ast_node_type_conditional";
            case hl_ast_node_type_loop: return "hl_ast_node_type_loop";
            case hl_ast_node_type_function_def: return "hl_ast_node_type_function_def";
            case hl_ast_node_type_operand: return "hl_ast_node_type_operand";
            case hl_ast_node_type_function_call: return "hl_ast_node_type_function_call";
            case hl_ast_node_type_code_block: return "hl_ast_node_type_code_block";
            case hl_ast_node_type_struct: return "hl_ast_struct";
            default: return "unknown hl ast type";
        }
    }

    typedef enum {
        c_type_void = 1,
        c_type_char = 2,
        c_type_short = 3,
        c_type_int = 4,
        c_type_long = 5,
        c_type_float = 6,
        c_type_struct = 7
    } c_types_t;

    class ast_node {

    public:
        virtual ~ast_node() = default;

        explicit ast_node(hl_ast_node_type_t t);
        static c_types_t string_to_type(const std::string& t);
        static std::string  type_to_string(const c_types_t &t);

        virtual std::string pretty_print(const std::shared_ptr<ast_node> &node);

        friend bool operator==(const ast_node& lhs, const ast_node& rhs){
            bool ret_val = true;
            ret_val &= lhs.node_type == rhs.node_type;


            return ret_val;
        };

        static  bool compare_content_by_type(const std::shared_ptr<ast_node>& lhs, const std::shared_ptr<ast_node>& rhs);

        static std::shared_ptr<ast_node> deep_copy(const std::shared_ptr<ast_node> &node);
        static bool compare_vectors(const std::vector<std::shared_ptr<ast_node>>& lhs, const std::vector<std::shared_ptr<ast_node>>& rhs);

        hl_ast_node_type_t node_type;


    };
}



#endif //FCORE_TOOLCHAIN_AST_NODE_HPP
