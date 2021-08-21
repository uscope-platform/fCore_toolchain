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

#ifndef FCORE_TOOLCHAIN_CODE_BLOCK_INLINING_PASS_HPP
#define FCORE_TOOLCHAIN_CODE_BLOCK_INLINING_PASS_HPP

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

class code_block_inlining_pass : public pass_base<hl_ast_node>{
public:
    code_block_inlining_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    std::vector<std::shared_ptr<hl_ast_node>> process_element_by_type(std::shared_ptr<hl_ast_node> element);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::vector<std::shared_ptr<hl_ast_node>> process_vector(const std::vector<std::shared_ptr<hl_ast_node>>& elements);
    std::vector<std::shared_ptr<hl_ast_node>> process_expression(const std::shared_ptr<hl_expression_node>& expr);
    std::shared_ptr<hl_ast_node> process_loop(std::shared_ptr<hl_ast_loop_node> element);
    std::shared_ptr<hl_ast_node> process_definition(std::shared_ptr<hl_definition_node> element);
    std::shared_ptr<hl_ast_node> process_conditional(std::shared_ptr<hl_ast_conditional_node> element);
};


#endif //FCORE_TOOLCHAIN_CODE_BLOCK_INLINING_PASS_HPP
