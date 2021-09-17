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

#ifndef FCORE_TOOLCHAIN_HL_AST_NODE_HPP
#define FCORE_TOOLCHAIN_HL_AST_NODE_HPP

#include <map>
#include <string>
#include <stdexcept>

#include "data_structures/ast_node_base.hpp"



typedef enum {
    hl_ast_node_type_expr = 1,
    hl_ast_node_type_definition = 2,
    hl_ast_node_type_conditional = 3,
    hl_ast_node_type_loop = 4,
    hl_ast_node_type_function_def = 5,
    hl_ast_node_type_operand = 6,
    hl_ast_node_type_function_call = 7,
    hl_ast_node_type_program_root = 8,
    hl_ast_node_type_code_block = 9
} hl_ast_node_type_t;

typedef enum {
    c_type_void = 1,
    c_type_char = 2,
    c_type_short = 3,
    c_type_int = 4,
    c_type_long = 5,
    c_type_float = 6
} c_types_t;

class hl_ast_node : public ast_node_base<hl_ast_node>{

public:
    explicit hl_ast_node(hl_ast_node_type_t t);
    static c_types_t string_to_type(const std::string& t);
    static std::string  type_to_string(const c_types_t &t);

    virtual bool is_terminal();

    virtual std::string pretty_print();

    friend bool operator==(const hl_ast_node& lhs, const hl_ast_node& rhs);

    static  bool compare_content_by_type(const std::shared_ptr<hl_ast_node>& lhs, const std::shared_ptr<hl_ast_node>& rhs);

    static std::shared_ptr<hl_ast_node> deep_copy(const std::shared_ptr<hl_ast_node> &node);
    hl_ast_node_type_t node_type;
    static bool compare_vectors(const std::vector<std::shared_ptr<hl_ast_node>>& lhs, const std::vector<std::shared_ptr<hl_ast_node>>& rhs);

private:
    static std::shared_ptr<hl_ast_node> deep_copy_expr(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_def(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_conditional(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_loop(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_function_def(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_operands(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_function_call(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_program_root(const std::shared_ptr<hl_ast_node> &node);
};


#endif //FCORE_TOOLCHAIN_HL_AST_NODE_HPP
