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


#ifndef DESTRUCTURING_PASS_HPP
#define DESTRUCTURING_PASS_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/hl_acting_visitor.hpp"

namespace fcore {

    class destructuring_pass : public pass_base{
    public:
        destructuring_pass();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;

        std::vector<std::shared_ptr<ast_node>> process_definition(const std::shared_ptr<ast_definition> &def);
        std::vector<std::shared_ptr<ast_node>> process_expression(std::shared_ptr<ast_expression> exp);
        std::shared_ptr<ast_node> process_operand(std::shared_ptr<ast_operand> op);
    private:

        std::map<std::string, std::shared_ptr<ast_struct>> struct_definitions;
        std::map<std::string, std::shared_ptr<ast_struct>> struct_instances;

    };
}



#endif //DESTRUCTURING_PASS_HPP
