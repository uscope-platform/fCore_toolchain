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
// limitations under the License.30/06/2021.
//

#ifndef FCORE_TOOLCHAIN_AST_LOOP_HPP
#define FCORE_TOOLCHAIN_AST_LOOP_HPP

#include <utility>

#include "data_structures/high_level_ast/ast_node.hpp"
#include "data_structures/high_level_ast/ast_definition.hpp"
#include "data_structures/high_level_ast/ast_expression.hpp"

namespace fcore{
    class ast_loop : public ast_node {
    public:
        ast_loop();
        void set_loop_content(std::vector<std::shared_ptr<ast_node>> content) {loop_content = std::move(content);};
        std::vector<std::shared_ptr<ast_node>> get_loop_content() {return loop_content;};
        std::shared_ptr<ast_expression> get_condition() {return condition;};
        void set_condition(std::shared_ptr<ast_expression> c) {condition = std::move(c);};
        std::shared_ptr<ast_definition> get_init_statement() { return  init_statement;};
        void set_init_statement(std::shared_ptr<ast_definition> init_s) {init_statement = std::move(init_s);}
        std::shared_ptr<ast_expression> get_iteration_expr() {return iteration_expr;};
        void set_iteration_expr(std::shared_ptr<ast_expression> i) {iteration_expr = std::move(i);};
        std::string pretty_print();

        friend bool operator==(const ast_loop& lhs, const ast_loop& rhs){
            bool ret_val = true;

            ret_val &= compare_content_by_type( lhs.init_statement, rhs.init_statement);
            ret_val &= compare_content_by_type( lhs.condition, rhs.condition);
            ret_val &= compare_content_by_type( lhs.iteration_expr, rhs.iteration_expr);

            ret_val &= compare_vectors(lhs.loop_content, rhs.loop_content);

            return ret_val;
        };
        static std::shared_ptr<ast_loop> deep_copy(const std::shared_ptr<ast_loop> &node);


    private:
        std::vector<std::shared_ptr<ast_node>> loop_content;
        std::shared_ptr<ast_expression> condition;
        std::shared_ptr<ast_expression> iteration_expr;
        std::shared_ptr<ast_definition> init_statement;
    };
}


#endif //FCORE_TOOLCHAIN_AST_LOOP_HPP
