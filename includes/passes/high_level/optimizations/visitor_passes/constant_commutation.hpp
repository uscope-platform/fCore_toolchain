

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

#ifndef CONSTANT_COMMUTATION_HPP
#define CONSTANT_COMMUTATION_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "passes/high_level/infrastructure/hl_acting_visitor.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore {
    class constant_commutation : public pass_base{
    public:
        constant_commutation();
        std::shared_ptr<hl_code_block> process_global(std::shared_ptr<hl_code_block> element,const std::vector<std::shared_ptr<hl_definition_node>> &globals) override;
    private:
        static std::vector<std::shared_ptr<hl_ast_node>> process_expression(const std::shared_ptr<hl_expression_node>& exp);
        static std::vector<std::shared_ptr<hl_ast_node>> process_expression_by_type(
            const std::shared_ptr<hl_expression_node>& exp,
            hl_expression_node::expression_type type,
            hl_expression_node::expression_type additional_type
        );
        static std::pair<std::shared_ptr<hl_ast_operand>, std::shared_ptr<hl_ast_operand>>  process_left_expression(std::shared_ptr<hl_expression_node> exp);
        static std::pair<std::shared_ptr<hl_ast_operand>, std::shared_ptr<hl_ast_operand>> process_right_expression(std::shared_ptr<hl_expression_node> exp);
    };

}

#endif //CONSTANT_COMMUTATION_HPP
