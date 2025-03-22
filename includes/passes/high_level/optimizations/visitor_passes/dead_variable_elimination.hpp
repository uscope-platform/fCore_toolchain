//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef FCORE_TOOLCHAIN_DEAD_VARIABLE_ELIMINATION_HPP
#define FCORE_TOOLCHAIN_DEAD_VARIABLE_ELIMINATION_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/hl_acting_visitor.hpp"

namespace fcore{
    class dead_variable_elimination : public pass_base{
    public:
        explicit dead_variable_elimination();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;

        std::vector<std::shared_ptr<ast_node>> detect_definition(const std::shared_ptr<ast_definition> &def);
        std::vector<std::shared_ptr<ast_node>> process_definition(const std::shared_ptr<ast_definition> &def);

        std::vector<std::shared_ptr<ast_node>> detect_expression(const std::shared_ptr<ast_expression> &expr);
    private:
        std::map<std::string, bool> defined_variables;
    };
}


#endif //FCORE_TOOLCHAIN_DEAD_VARIABLE_ELIMINATION_HPP
