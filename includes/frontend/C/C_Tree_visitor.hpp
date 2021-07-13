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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_C_TREE_VISITOR_HPP
#define FCORE_TOOLCHAIN_C_TREE_VISITOR_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <stack>
#include <exception>
#include <stdexcept>

#include "C_parser/C_grammarBaseListener.h"
#include "C_parser/C_grammarParser.h"
#include "ast/variable.hpp"
#include "frontend/variable_map.hpp"


#include "ast/high_level/hl_function_def_node.hpp"
#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_expression_node.hpp"
#include "ast/high_level/hl_ast_operand.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "ast/high_level/hl_function_call_node.hpp"

#include <gtest/gtest_prod.h>

typedef std::unordered_map<std::string, std::shared_ptr<variable>>  varmap_t;

class C_Tree_visitor : public  C_parser::C_grammarBaseListener{
public:
    explicit C_Tree_visitor();

    void enterFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) override;
    void exitFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) override;
    void exitBlockItem(C_parser::C_grammarParser::BlockItemContext *ctx) override;

    void enterCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) override;
    void exitCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) override;

    void exitParameterDeclaration(C_parser::C_grammarParser::ParameterDeclarationContext *ctx) override;
    void exitDeclaration(C_parser::C_grammarParser::DeclarationContext *ctx) override;
    void exitInitializer(C_parser::C_grammarParser::InitializerContext *ctx) override;

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
    void exitAssignmentExpression(C_parser::C_grammarParser::AssignmentExpressionContext *ctx) override;
    void exitArgumentExpression(C_parser::C_grammarParser::ArgumentExpressionContext *ctx) override;

    void exitStatement(C_parser::C_grammarParser::StatementContext *ctx) override;
    void exitFunctionCallExpression(C_parser::C_grammarParser::FunctionCallExpressionContext *ctx) override;

    void exitCompilationUnit(C_parser::C_grammarParser::CompilationUnitContext *ctx) override;

    std::shared_ptr<hl_ast_node> get_ast(){
        return root;
    };

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
    FRIEND_TEST( cTreeVisitor, assignmentExpressions);
    FRIEND_TEST(cTreeVisitor, definition);
    FRIEND_TEST(cTreeVisitor, function_def);
    FRIEND_TEST(cTreeVisitor, function_call);
    FRIEND_TEST(cFrontend, returnTest);

    template<typename T>
    void processExpression(unsigned int expression_size, const T& operands_array, std::map<std::string, expression_type_t> &expr_map);

    std::vector<std::shared_ptr<hl_ast_node>> ext_decl;
    std::vector<std::shared_ptr<hl_definition_node>> parameters_list;
    std::vector<std::shared_ptr<hl_ast_node>> functions;
    std::vector<std::shared_ptr<hl_ast_node>> function_body;

    std::stack<std::shared_ptr<hl_ast_node>> expressions_stack;
    std::vector<std::shared_ptr<hl_ast_node>> argument_vector;

    std::shared_ptr<hl_function_def_node> current_function;

    std::shared_ptr<hl_ast_node> current_initializer;
    std::shared_ptr<hl_ast_node> current_block_item;

    std::shared_ptr<hl_ast_node> root;

    bool in_function_declaration;
    bool in_function_body;
};

#endif //FCORE_TOOLCHAIN_ASMTREE_VISITOR_HPP
