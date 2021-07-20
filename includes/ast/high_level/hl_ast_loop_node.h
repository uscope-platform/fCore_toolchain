// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.30/06/2021.
//

#ifndef FCORE_TOOLCHAIN_HL_AST_LOOP_NODE_H
#define FCORE_TOOLCHAIN_HL_AST_LOOP_NODE_H

#include <utility>

#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "ast/high_level/hl_expression_node.hpp"

class hl_ast_loop_node : public hl_ast_node {
public:
    hl_ast_loop_node();
    void set_loop_content(std::vector<std::shared_ptr<hl_ast_node>> content) {loop_content = std::move(content);};
    std::vector<std::shared_ptr<hl_ast_node>> get_loop_content() {return loop_content;};
    std::shared_ptr<hl_expression_node> get_condition() {return condition;};
    void set_condition(std::shared_ptr<hl_expression_node> c) {condition = std::move(c);};
    std::shared_ptr<hl_definition_node> get_init_statement() { return  init_statement;};
    void set_init_statement(std::shared_ptr<hl_definition_node> init_s) {init_statement = std::move(init_s);}
    std::shared_ptr<hl_expression_node> get_iteration_expr() {return iteration_expr;};
    void set_iteration_expr(std::shared_ptr<hl_expression_node> i) {iteration_expr = std::move(i);};
    std::string pretty_print() override;
    friend bool operator==(const hl_ast_loop_node& lhs, const hl_ast_loop_node& rhs);
private:
    std::vector<std::shared_ptr<hl_ast_node>> loop_content;
    std::shared_ptr<hl_expression_node> condition;
    std::shared_ptr<hl_expression_node> iteration_expr;
    std::shared_ptr<hl_definition_node> init_statement;
};


#endif //FCORE_TOOLCHAIN_HL_AST_LOOP_NODE_H
