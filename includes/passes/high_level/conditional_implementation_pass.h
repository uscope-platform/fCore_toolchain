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
//

#ifndef FCORE_TOOLCHAIN_CONDITIONAL_IMPLEMENTATION_PASS_H
#define FCORE_TOOLCHAIN_CONDITIONAL_IMPLEMENTATION_PASS_H

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

#include "tools/expression_evaluator.hpp"

namespace fcore{
    class conditional_implementation_pass : public pass_base {
    public:
        conditional_implementation_pass();
        std::shared_ptr<hl_ast_root> process_global(std::shared_ptr<hl_ast_root> element) override;

    private:
        std::shared_ptr<hl_ast_operand> find_variable_definition(const std::shared_ptr<hl_ast_node>& subexpr, const std::shared_ptr<hl_ast_node>& item,
                                                                 const std::vector<std::shared_ptr<hl_ast_node>>& prog_content);
        std::shared_ptr<hl_ast_operand> get_operands(const std::shared_ptr<hl_ast_node>& subexpr, const std::shared_ptr<hl_ast_node>& item,
                                                     const std::vector<std::shared_ptr<hl_ast_node>>& prog_content);

        std::vector<std::shared_ptr<hl_ast_node>> process_block_by_type(const std::shared_ptr<hl_ast_node>& node, const std::shared_ptr<hl_ast_node>& subtree);
        std::vector<std::shared_ptr<hl_ast_node>> process_conditional(const std::shared_ptr<hl_ast_conditional_node>& node, const std::shared_ptr<hl_ast_node>& subtree);
        std::vector<std::shared_ptr<hl_ast_node>> process_loop(const std::shared_ptr<hl_ast_loop_node>& node, const std::shared_ptr<hl_ast_node>& subtree);
        std::vector<std::shared_ptr<hl_ast_node>> process_definition(const std::shared_ptr<hl_definition_node> &node, const std::shared_ptr<hl_ast_node>& subtree);
        std::vector<std::shared_ptr<hl_ast_node>> process_expression(const std::shared_ptr<hl_expression_node> &node, const std::shared_ptr<hl_ast_node>& subtree);
        std::shared_ptr<hl_ast_node> process_ternary(const std::shared_ptr<hl_ast_conditional_node>& node);
    };
}



#endif //FCORE_TOOLCHAIN_CONDITIONAL_IMPLEMENTATION_PASS_H
