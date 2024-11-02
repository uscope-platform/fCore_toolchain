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


#ifndef FCORE_TOOLCHAIN_CONSTANT_FOLDING_PASS_HPP
#define FCORE_TOOLCHAIN_CONSTANT_FOLDING_PASS_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/hl_ast_visitor.hpp"

namespace fcore{
    class comparison_flipping : public  pass_base {
    public:
        comparison_flipping();
        std::shared_ptr<hl_code_block> process_global(std::shared_ptr<hl_code_block> element) override;
    private:
        static std::vector<std::shared_ptr<hl_ast_node>> process_expression(std::shared_ptr<hl_expression_node> exp);
    };
}



#endif //FCORE_TOOLCHAIN_CONSTANT_FOLDING_PASS_HPP
