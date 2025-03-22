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

#ifndef FCORE_TOOLCHAIN_CODE_BLOCK_INLINING_PASS_HPP
#define FCORE_TOOLCHAIN_CODE_BLOCK_INLINING_PASS_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{
    class code_block_inlining_pass : public pass_base{
    public:
        code_block_inlining_pass();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;
        std::vector<std::shared_ptr<ast_node>> process_element_by_type(std::shared_ptr<ast_node> element);
    private:
        std::vector<std::shared_ptr<ast_node>> process_vector(const std::vector<std::shared_ptr<ast_node>>& elements);
        std::vector<std::shared_ptr<ast_node>> process_expression(const std::shared_ptr<ast_expression>& expr);
        std::vector<std::shared_ptr<ast_node>> process_function_definition(const std::shared_ptr<ast_function_def>& expr);
        std::shared_ptr<ast_node> process_loop(std::shared_ptr<ast_loop> element);
        std::shared_ptr<ast_node> process_definition(std::shared_ptr<ast_definition> element);
        std::shared_ptr<ast_node> process_conditional(std::shared_ptr<ast_conditional> element);
        std::vector<std::shared_ptr<ast_node>> process_code_block(const std::shared_ptr<ast_code_block>& element);
    };
}



#endif //FCORE_TOOLCHAIN_CODE_BLOCK_INLINING_PASS_HPP
