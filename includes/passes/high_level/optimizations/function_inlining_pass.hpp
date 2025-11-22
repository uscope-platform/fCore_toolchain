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

#ifndef FCORE_TOOLCHAIN_FUNCTION_INLINING_PASS_HPP
#define FCORE_TOOLCHAIN_FUNCTION_INLINING_PASS_HPP

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/pass_base.hpp"


namespace fcore{
    class function_inlining_pass :public pass_base{
    public:
        function_inlining_pass();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;

        std::vector<std::shared_ptr<ast_node>> process_element(std::shared_ptr<ast_node> element);
        std::shared_ptr<ast_loop> process_loop(std::shared_ptr<ast_loop> element);
        std::shared_ptr<ast_conditional> process_conditional(std::shared_ptr<ast_conditional> element);
        std::vector<std::shared_ptr<ast_node>> process_expression(std::shared_ptr<ast_expression> element);
        std::vector<std::shared_ptr<ast_node>> process_definition(std::shared_ptr<ast_definition> element);
        std::shared_ptr<ast_function_def> process_function_def(std::shared_ptr<ast_function_def> element);
        std::shared_ptr<ast_operand> process_operand(std::shared_ptr<ast_operand> element);
        std::vector<std::shared_ptr<ast_node>> process_function_call(std::shared_ptr<ast_call> element);


        std::shared_ptr<ast_node> substitute_arguments(const std::shared_ptr<ast_node> &statement, std::map<std::string, std::shared_ptr<ast_node>> parameters);
        std::shared_ptr<ast_node> substitute_loop_arguments(const std::shared_ptr<ast_loop> &statement, std::map<std::string, std::shared_ptr<ast_node>> parameters);
        std::shared_ptr<ast_node> substitute_conditional_arguments(const std::shared_ptr<ast_conditional> &statement, std::map<std::string, std::shared_ptr<ast_node>> parameters);
        std::shared_ptr<ast_node> substitute_expression_arguments(const std::shared_ptr<ast_expression> &statement, std::map<std::string, std::shared_ptr<ast_node>> parameters);
        std::shared_ptr<ast_node> substitute_definition_arguments(const std::shared_ptr<ast_definition> &statement, std::map<std::string, std::shared_ptr<ast_node>> parameters);
        std::shared_ptr<ast_node> substitute_operand_arguments(const std::shared_ptr<ast_operand> &statement, std::map<std::string, std::shared_ptr<ast_node>> parameters);
        std::shared_ptr<ast_node> substitute_code_block(const std::shared_ptr<ast_code_block> &statement, std::map<std::string, std::shared_ptr<ast_node>> parameters);
        std::shared_ptr<ast_node> substitute_call_arguments(const std::shared_ptr<ast_call> &statement, std::map<std::string, std::shared_ptr<ast_node>> parameters);

    private:
        std::map<std::string, std::shared_ptr<ast_function_def>> functions_map;
    };
}



#endif //FCORE_TOOLCHAIN_FUNCTION_INLINING_PASS_HPP
