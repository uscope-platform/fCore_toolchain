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


#ifndef FCORE_TOOLCHAIN_LOOP_UNROLLING_PASS_H
#define FCORE_TOOLCHAIN_LOOP_UNROLLING_PASS_H


#include <utility>

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "tools/expression_evaluator.hpp"
#include "tools/variable.hpp"

class loop_unrolling_pass : public pass_base<hl_ast_node> {
public:
    loop_unrolling_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::vector<std::shared_ptr<hl_ast_node>> process_loop(const std::shared_ptr<hl_ast_loop_node>& element);
    unsigned int process_loop_initializer(const std::shared_ptr<hl_ast_node>& raw_initializer);
    bool evaluate_loop(const std::shared_ptr<hl_expression_node>& condition, const std::shared_ptr<hl_expression_node>& iteration_exp, std::shared_ptr<hl_ast_operand> &loop_var);
    std::shared_ptr<hl_expression_node> update_loop_condition(std::shared_ptr<hl_expression_node> expression, std::shared_ptr<hl_ast_operand> loop_var);
    void update_expression(std::shared_ptr<hl_expression_node> expression, std::shared_ptr<hl_ast_operand> loop_var);

    std::shared_ptr<hl_ast_node> substitute_index(std::shared_ptr<hl_ast_node> element, std::string idx_name, int value);
    std::shared_ptr<hl_ast_loop_node> substitute_index_in_loop(std::shared_ptr<hl_ast_loop_node> node, std::string idx_name, int value);
    std::shared_ptr<hl_expression_node> substitute_index_in_expression(std::shared_ptr<hl_expression_node> node, std::string idx_name, int value);
    std::shared_ptr<hl_definition_node> substitute_index_in_definition(std::shared_ptr<hl_definition_node> node, std::string idx_name, int value);
    static std::shared_ptr<hl_ast_operand> substitute_index_in_operand(std::shared_ptr<hl_ast_operand> node, std::string idx_name, int value);
    const unsigned int max_loop_iterations = 32767;
    unsigned int current_loop_iteration;

};


#endif //FCORE_TOOLCHAIN_LOOP_UNROLLING_PASS_H
