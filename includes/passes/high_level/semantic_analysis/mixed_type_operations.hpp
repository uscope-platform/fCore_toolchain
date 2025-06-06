

//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#ifndef MIXED_TYPE_OPERATIONS_HPP
#define MIXED_TYPE_OPERATIONS_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/hl_observing_visitor.hpp"

#include <fmt/format.h>

namespace fcore{
    class mixed_type_operations : public pass_base {
    public:
        mixed_type_operations();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;
    private:
        static void process_expression(const std::shared_ptr<ast_expression> &exp);
        static bool are_types_compatible(c_types_t lhs, c_types_t rhs);
    };

}


#endif //MIXED_TYPE_OPERATIONS_HPP
