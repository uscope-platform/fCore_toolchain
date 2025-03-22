//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_ARRAY_INITIALIZATION_SUBSTITUTION_H
#define FCORE_TOOLCHAIN_ARRAY_INITIALIZATION_SUBSTITUTION_H

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "tools/array_linearizer.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/hl_acting_visitor.hpp"

namespace fcore{
    class array_initialization_substitution : public pass_base{
    public:
        array_initialization_substitution();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;

    private:
        static std::vector<std::shared_ptr<ast_node>> process_definition(const std::shared_ptr<ast_definition> &node);
        static std::shared_ptr<ast_expression> build_initialization_expr(const std::shared_ptr<ast_definition>& var_name, int index);
    };
}


#endif //FCORE_TOOLCHAIN_ARRAY_INITIALIZATION_SUBSTITUTION_H
