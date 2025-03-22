// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_CONTIGUOUS_ARRAY_IDENTIFICATION_HPP
#define FCORE_TOOLCHAIN_CONTIGUOUS_ARRAY_IDENTIFICATION_HPP

#include <set>

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{
    class contiguous_array_identification : public pass_base{
    public:
        contiguous_array_identification();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;
    private:
        std::shared_ptr<ast_node> process_element(std::shared_ptr<ast_node> element);
        std::shared_ptr<ast_node> process_element(std::shared_ptr<ast_expression> element);
        std::shared_ptr<ast_node> process_element(std::shared_ptr<ast_definition> element);
        std::shared_ptr<ast_node> process_element(std::shared_ptr<ast_operand> element);
        std::shared_ptr<ast_node> process_element(std::shared_ptr<ast_conditional> element);

        void process_efi_arguments(std::shared_ptr<ast_expression> element);

        std::set<std::string> contiguous_arrays;
    };
}



#endif //FCORE_TOOLCHAIN_CONTIGUOUS_ARRAY_IDENTIFICATION_HPP
