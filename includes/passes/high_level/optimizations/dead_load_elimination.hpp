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

#ifndef FCORE_TOOLCHAIN_DEAD_LOAD_ELIMINATION_HPP
#define FCORE_TOOLCHAIN_DEAD_LOAD_ELIMINATION_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{

    struct load_t {
        int last_assignment;
        int first_usage;
    };

    class dead_load_elimination : public pass_base{
    public:
        explicit dead_load_elimination();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;
    private:
        int idx;
        void search_usages(std::shared_ptr<ast_node> element);
        void search_usages(std::shared_ptr<ast_expression> element);
        void search_usages(std::shared_ptr<ast_definition> element);
        void search_usages(std::shared_ptr<ast_operand> element);
        void search_constants(std::shared_ptr<ast_node> element);
        std::shared_ptr<ast_node> purge_dead_loads(std::shared_ptr<ast_node> element);
        std::unordered_map<std::string, load_t> last_loads_map;
        bool efi_mode;
    };
}


#endif //FCORE_TOOLCHAIN_DEAD_LOAD_ELIMINATION_HPP
