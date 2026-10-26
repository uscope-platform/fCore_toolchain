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

#ifndef FCORE_TOOLCHAIN_HIGH_LEVEL_AST_LOWERING_HPP
#define FCORE_TOOLCHAIN_HIGH_LEVEL_AST_LOWERING_HPP

#include <vector>
#include <utility>

#include "errors/result.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"
#include "tools/variable_map.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore {
    class high_level_ast_lowering {
    public:
        explicit high_level_ast_lowering();
        void set_input_ast(std::shared_ptr<ast_code_block> i) {input_ast = std::move(i);};
        [[nodiscard]] result<instruction_stream> translate();
    private:
        /// no instruction (nullopt) is a valid outcome, for example a definition without initializer
        typedef result<std::optional<instruction_variant>> lowered_t;

        lowered_t translate_node(const std::shared_ptr<ast_node>& input);
        lowered_t translate_node(const std::shared_ptr<ast_expression>& input, const std::shared_ptr<variable>& dest);
        lowered_t translate_node(const std::shared_ptr<ast_operand>& input, std::shared_ptr<variable> dest);
        lowered_t translate_node(const std::shared_ptr<ast_definition>& input, const std::shared_ptr<variable>& dest);
        lowered_t process_unary_expression(std::shared_ptr<ast_expression> input, std::shared_ptr<variable> dest);
        lowered_t process_ternary_expression(std::shared_ptr<ast_expression> input, std::shared_ptr<variable> dest);
        lowered_t process_immediate_expression(std::shared_ptr<ast_expression> input);
        lowered_t process_regular_expression(std::shared_ptr<ast_expression> input, std::shared_ptr<variable> dest);
        std::shared_ptr<ast_code_block> input_ast;

        std::optional<instruction_variant> create_ast_node(isa_instruction_type t, std::vector<std::shared_ptr<variable>> args, const opcode_table_t& op);
        std::map<ast_expression::expression_type, opcode_table_t> expr_instruction_mapping;

    };
}


#endif //FCORE_TOOLCHAIN_HIGH_LEVEL_AST_LOWERING_HPP
