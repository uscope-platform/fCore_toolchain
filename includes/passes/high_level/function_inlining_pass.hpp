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

#ifndef FCORE_TOOLCHAIN_FUNCTION_INLINING_PASS_HPP
#define FCORE_TOOLCHAIN_FUNCTION_INLINING_PASS_HPP

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/pass_base.hpp"

#include <utility>

class function_inlining_pass :public pass_base<hl_ast_node>{
public:
    function_inlining_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;

    std::shared_ptr<hl_ast_node> process_element(std::shared_ptr<hl_ast_node> element);
    std::shared_ptr<hl_ast_loop_node> process_loop(std::shared_ptr<hl_ast_loop_node> element);
    std::shared_ptr<hl_ast_conditional_node> process_conditional(std::shared_ptr<hl_ast_conditional_node> element);
    std::shared_ptr<hl_expression_node> process_expression(std::shared_ptr<hl_expression_node> element);
    std::shared_ptr<hl_definition_node> process_definition(std::shared_ptr<hl_definition_node> element);
    std::shared_ptr<hl_function_def_node> process_function_def(std::shared_ptr<hl_function_def_node> element);
    std::shared_ptr<hl_ast_operand> process_operand(std::shared_ptr<hl_ast_operand> element);
    std::shared_ptr<hl_ast_node> process_function_call(std::shared_ptr<hl_function_call_node> element);


    std::shared_ptr<hl_ast_node> substitute_arguments(const std::shared_ptr<hl_ast_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_loop_arguments(const std::shared_ptr<hl_ast_loop_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_conditional_arguments(const std::shared_ptr<hl_ast_conditional_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_expression_arguments(const std::shared_ptr<hl_expression_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_definition_arguments(const std::shared_ptr<hl_definition_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    std::shared_ptr<hl_ast_node> substitute_operand_arguments(const std::shared_ptr<hl_ast_operand> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>> parameters);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>> functions_map;
};


#endif //FCORE_TOOLCHAIN_FUNCTION_INLINING_PASS_HPP
