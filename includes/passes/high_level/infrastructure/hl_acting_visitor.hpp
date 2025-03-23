

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

#ifndef FCORE_TOOLCHAIN_HL_AST_VISITOR_HPP
#define FCORE_TOOLCHAIN_HL_AST_VISITOR_HPP

#include <memory>
#include <vector>

#include "data_structures/high_level_ast/ast_node.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{


    struct hl_acting_visitor_operations{
        struct post_operations{
            std::function<std::shared_ptr<ast_node> (const std::shared_ptr<ast_conditional> &cond)> visit_conditional;
            std::function<std::shared_ptr<ast_node> (const std::shared_ptr<ast_conditional> &cond)> before_else;
            std::function<std::shared_ptr<ast_node> (const std::shared_ptr<ast_loop> &cond)> visit_loop;
            std::function<std::shared_ptr<ast_node> (const std::shared_ptr<ast_operand> &cond)> visit_operand;
            std::function<std::vector<std::shared_ptr<ast_node>> (const std::shared_ptr<ast_definition> & def)> visit_definition;
            std::function<std::vector<std::shared_ptr<ast_node>> (const std::shared_ptr<ast_expression> &cond)> visit_expression;
            std::function<std::vector<std::shared_ptr<ast_node>> (const std::shared_ptr<ast_function_def> &cond)> visit_function_def;
            std::function<std::vector<std::shared_ptr<ast_node>>  (const std::shared_ptr<ast_call> &cond)> visit_function_call;
        };
        struct pre_operations{
            std::function<void (const std::shared_ptr<ast_conditional> &cond)> visit_conditional;
            std::function<void (const std::shared_ptr<ast_conditional> &cond)> before_else;
            std::function<void (const std::shared_ptr<ast_loop> &cond)> visit_loop;
            std::function<void (const std::shared_ptr<ast_operand> &cond)> visit_operand;
            std::function<void (const std::shared_ptr<ast_definition> & def)> visit_definition;
            std::function<void (const std::shared_ptr<ast_expression> &cond)> visit_expression;
            std::function<void (const std::shared_ptr<ast_function_def> &cond)> visit_function_def;
            std::function<void (const std::shared_ptr<ast_call> &cond)> visit_function_call;
        };
        pre_operations pre;
        post_operations post;
    };

    class hl_acting_visitor {
    public:
        std::shared_ptr<ast_code_block> visit(const hl_acting_visitor_operations &operations,const std::shared_ptr<ast_code_block> &node);
    private:
        std::vector<std::shared_ptr<ast_node>> process_node_by_type(const std::shared_ptr<ast_node> &node);
        std::shared_ptr<ast_node> process_node(const std::shared_ptr<ast_conditional> &cond);
        std::shared_ptr<ast_node> process_node(const std::shared_ptr<ast_loop> &loop);
        std::shared_ptr<ast_node> process_node(const std::shared_ptr<ast_operand> &op);
        std::vector<std::shared_ptr<ast_node>> process_node(const std::shared_ptr<ast_definition> &def);
        std::vector<std::shared_ptr<ast_node>> process_node(const std::shared_ptr<ast_expression> &cond);
        std::vector<std::shared_ptr<ast_node>>  process_node(const std::shared_ptr<ast_call> &cond);
        std::vector<std::shared_ptr<ast_node>> process_node(const std::shared_ptr<ast_function_def> &def);
        std::shared_ptr<ast_node> process_node(const std::shared_ptr<ast_code_block> &block);
        hl_acting_visitor_operations ops;

        std::shared_ptr<ast_node> get_expected_scalar_element(const std::vector<std::shared_ptr<ast_node>> &vect);

    };

}


#endif //FCORE_TOOLCHAIN_HL_AST_VISITOR_HPP
