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

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{
    class conditional_implementation_pass : public pass_base {
    public:
        conditional_implementation_pass();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;

    private:
        std::shared_ptr<ast_operand> find_variable_definition(const std::shared_ptr<ast_node>& subexpr, const std::shared_ptr<ast_node>& item,
                                                                 const std::vector<std::shared_ptr<ast_node>>& prog_content);
        std::shared_ptr<ast_operand> get_operands(const std::shared_ptr<ast_node>& subexpr, const std::shared_ptr<ast_node>& item,
                                                     const std::vector<std::shared_ptr<ast_node>>& prog_content);

        std::vector<std::shared_ptr<ast_node>> process_block_by_type(const std::shared_ptr<ast_node>& node, const std::shared_ptr<ast_code_block>& subtree);
        std::vector<std::shared_ptr<ast_node>> process_conditional(const std::shared_ptr<ast_conditional>& node, const std::shared_ptr<ast_code_block>& subtree);
        std::vector<std::shared_ptr<ast_node>> process_loop(const std::shared_ptr<ast_loop>& node, const std::shared_ptr<ast_code_block>& subtree);
        std::vector<std::shared_ptr<ast_node>> process_definition(const std::shared_ptr<ast_definition> &node, const std::shared_ptr<ast_code_block>& subtree);
        std::vector<std::shared_ptr<ast_node>> process_expression(const std::shared_ptr<ast_expression> &node, const std::shared_ptr<ast_code_block>& subtree);
        std::shared_ptr<ast_node> process_ternary(const std::shared_ptr<ast_conditional>& node);
    };
}



#endif //FCORE_TOOLCHAIN_CONDITIONAL_IMPLEMENTATION_PASS_H
