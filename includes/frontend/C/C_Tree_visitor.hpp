// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_HAS_ASMTREE_VISITOR_HPP
#define FCORE_HAS_TREE_VISITOR_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <stack>
#include <exception>

#include "C_parser/C_grammarBaseListener.h"
#include "C_parser/C_grammarParser.h"
#include "code_elements/variable.hpp"
#include "frontend/variable_map.hpp"

#include "code_elements/hl_ast/hl_function_node.h"
#include "code_elements/hl_ast/hl_identifier_node.h"
#include "code_elements/hl_ast/hl_ast_node.h"
#include "code_elements/hl_ast/hl_expression_node.h"
#include "code_elements/hl_ast/hl_identifier_node.h"

#include <gtest/gtest_prod.h>

typedef std::unordered_map<std::string, std::shared_ptr<variable>>  varmap_t;

class C_Tree_visitor : public  C_parser::C_grammarBaseListener{
public:
    explicit C_Tree_visitor();

    void enterFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) override;
    void exitFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) override;


    void enterCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) override;
    void exitCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) override;

    void exitParameterDeclaration(C_parser::C_grammarParser::ParameterDeclarationContext *ctx) override;
    void exitDeclarationSpecifiers(C_parser::C_grammarParser::DeclarationSpecifiersContext *ctx) override;

    void exitDeclaration(C_parser::C_grammarParser::DeclarationContext *ctx) override;
    void exitInitDeclarator(C_parser::C_grammarParser::InitDeclaratorContext *ctx) override;

    void exitPrimaryExpression(C_parser::C_grammarParser::PrimaryExpressionContext *ctx) override;
    void exitUnaryExpression(C_parser::C_grammarParser::UnaryExpressionContext *ctx) override;

    void exitMultiplicativeExpression(C_parser::C_grammarParser::MultiplicativeExpressionContext *ctx) override;
    void exitAdditiveExpression(C_parser::C_grammarParser::AdditiveExpressionContext *ctx) override;
    void exitShiftExpression(C_parser::C_grammarParser::ShiftExpressionContext *ctx) override;
    void exitEqualityExpression(C_parser::C_grammarParser::EqualityExpressionContext *ctx) override;
    void exitRelationalExpression(C_parser::C_grammarParser::RelationalExpressionContext *ctx) override;
    void exitInclusiveOrExpression(C_parser::C_grammarParser::InclusiveOrExpressionContext *ctx) override;
    void exitExclusiveOrExpression(C_parser::C_grammarParser::ExclusiveOrExpressionContext *ctx) override;
    void exitAndExpression(C_parser::C_grammarParser::AndExpressionContext *ctx) override;
    void exitLogicalOrExpression(C_parser::C_grammarParser::LogicalOrExpressionContext *ctx) override;
    void exitLogicalAndExpression(C_parser::C_grammarParser::LogicalAndExpressionContext *ctx) override;
private:
    FRIEND_TEST( cTreeVisitor, unaryExpressions);
    FRIEND_TEST( cTreeVisitor, multiplicativeExpressions);
    FRIEND_TEST( cTreeVisitor, additiveExpressions);
    FRIEND_TEST(cTreeVisitor, shiftExpressions);
    FRIEND_TEST(cTreeVisitor, relationalExpressions);
    FRIEND_TEST(cTreeVisitor, equalityExpressions);
    FRIEND_TEST(cTreeVisitor, exOrBinExpressions);
    FRIEND_TEST(cTreeVisitor, andBinExpressions);
    FRIEND_TEST(cTreeVisitor, orBinExpressions);
    FRIEND_TEST(cTreeVisitor, andLogExpressions);
    FRIEND_TEST(cTreeVisitor, orLogExpressions);

    template<typename T>
    void processExpression(unsigned int expression_size, const T& operands_array, std::map<std::string, expression_type_t> &expr_map);

    std::stack<std::string> declaration_type;
    std::vector<std::shared_ptr<hl_identifier_node>> parameters_list;
    std::vector<std::shared_ptr<hl_function_node>> functions;
    std::vector<std::shared_ptr<hl_ast_node>> function_body;

    std::stack<std::shared_ptr<hl_ast_operand>> operands_stack;
    std::stack<std::shared_ptr<hl_expression_node>> expressions_stack;
    bool in_function_declaration;
    bool in_function_body;
    int expression_nesting_level;
};

#endif //FCORE_HAS_ASMTREE_VISITOR_HPP
