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

#ifndef FCORE_TOOLCHAIN_NORMALIZATION_PASS_HPP
#define FCORE_TOOLCHAIN_NORMALIZATION_PASS_HPP

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/pass_base.hpp"


typedef enum {
    expr_normalized = 0,
    expr_normalize_lhs = 1,
    expr_normalize_rhs = 2,
} side_to_normalize;


class normalization_pass : public pass_base<hl_ast_node> {
public:
    normalization_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    std::shared_ptr<hl_ast_node> process_node_by_type_top(std::shared_ptr<hl_ast_node> n);
    std::vector<std::pair<side_to_normalize, std::shared_ptr<hl_ast_node>>> process_node_expr_inner(std::shared_ptr<hl_expression_node> n);
    std::shared_ptr<hl_expression_node> produce_normalized_expression(std::shared_ptr<hl_expression_node> original_node, const std::vector<std::pair<side_to_normalize, std::shared_ptr<hl_ast_node>>>& extracted_intermediate);
    std::shared_ptr<hl_definition_node> process_node_def(std::shared_ptr<hl_definition_node> n);
    std::shared_ptr<hl_expression_node> process_node_exp(std::shared_ptr<hl_expression_node> n);
    std::shared_ptr<hl_ast_operand> extract_intermediate_expression(std::shared_ptr<hl_expression_node> n);
    std::shared_ptr<hl_ast_node> process_code_block(std::shared_ptr<hl_ast_node> n);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    int intermediate_ordinal = 0;
    std::vector<std::shared_ptr<hl_ast_node>> additional_statements;
};


#endif //FCORE_TOOLCHAIN_NORMALIZATION_PASS_HPP
