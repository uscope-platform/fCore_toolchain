// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_HIGH_LEVEL_AST_LOWERING_HPP
#define FCORE_TOOLCHAIN_HIGH_LEVEL_AST_LOWERING_HPP


#include <utility>
#include <stdexcept>

#include "tools/variable_map.hpp"
#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "data_structures/high_level_ast/hl_definition_node.hpp"
#include "data_structures/low_level_ast/low_level_ast.hpp"

class high_level_ast_lowering {
public:
    explicit high_level_ast_lowering(std::shared_ptr<variable_map> &m);
    void set_input_ast(std::shared_ptr<hl_ast_node> i) {input_ast = std::move(i);};
    void translate();
    std::shared_ptr<ll_ast_node> get_output_ast() {return output_ast;};
private:
    std::shared_ptr<ll_ast_node> translate_node(const std::shared_ptr<hl_ast_node>& input);
    std::shared_ptr<ll_ast_node> translate_node(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest);
    std::shared_ptr<ll_ast_node> translate_node(const std::shared_ptr<hl_ast_operand>& input, std::shared_ptr<variable> dest);
    std::shared_ptr<ll_ast_node> translate_node(const std::shared_ptr<hl_definition_node>& input, const std::shared_ptr<variable>& dest);
    std::shared_ptr<ll_ast_node> process_unary_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest);
    std::shared_ptr<ll_ast_node> process_regular_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest);
    std::shared_ptr<hl_ast_node> input_ast;
    std::shared_ptr<ll_ast_node> output_ast;

    std::shared_ptr<ll_ast_node> create_ast_node(isa_instruction_type t, std::vector<std::shared_ptr<variable>> args, const std::string& op);
    std::map<expression_type_t, std::string> expr_instruction_mapping;
    std::shared_ptr<variable_map> var_map;
};


#endif //FCORE_TOOLCHAIN_HIGH_LEVEL_AST_LOWERING_HPP
