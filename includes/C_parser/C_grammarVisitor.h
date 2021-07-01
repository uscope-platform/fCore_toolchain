
// Generated from /home/fils/git/fCore_has/src/frontend/C_grammar.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "C_grammarParser.h"


namespace C_parser {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by C_grammarParser.
 */
class  C_grammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by C_grammarParser.
   */
    virtual antlrcpp::Any visitCompilationUnit(C_grammarParser::CompilationUnitContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpression(C_grammarParser::PrimaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPostfixExpression(C_grammarParser::PostfixExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpression(C_grammarParser::UnaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnaryOperator(C_grammarParser::UnaryOperatorContext *context) = 0;

    virtual antlrcpp::Any visitMultiplicativeExpression(C_grammarParser::MultiplicativeExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAdditiveExpression(C_grammarParser::AdditiveExpressionContext *context) = 0;

    virtual antlrcpp::Any visitShiftExpression(C_grammarParser::ShiftExpressionContext *context) = 0;

    virtual antlrcpp::Any visitRelationalExpression(C_grammarParser::RelationalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitEqualityExpression(C_grammarParser::EqualityExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAndExpression(C_grammarParser::AndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExclusiveOrExpression(C_grammarParser::ExclusiveOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitInclusiveOrExpression(C_grammarParser::InclusiveOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLogicalAndExpression(C_grammarParser::LogicalAndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLogicalOrExpression(C_grammarParser::LogicalOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitConditionalExpression(C_grammarParser::ConditionalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAssignmentExpression(C_grammarParser::AssignmentExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAssignmentOperator(C_grammarParser::AssignmentOperatorContext *context) = 0;

    virtual antlrcpp::Any visitExpression(C_grammarParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitConstantExpression(C_grammarParser::ConstantExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration(C_grammarParser::DeclarationContext *context) = 0;

    virtual antlrcpp::Any visitDeclarationSpecifiers(C_grammarParser::DeclarationSpecifiersContext *context) = 0;

    virtual antlrcpp::Any visitDeclarationSpecifier(C_grammarParser::DeclarationSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitInitDeclaratorList(C_grammarParser::InitDeclaratorListContext *context) = 0;

    virtual antlrcpp::Any visitInitDeclarator(C_grammarParser::InitDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitStorageClassSpecifier(C_grammarParser::StorageClassSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitTypeSpecifier(C_grammarParser::TypeSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitSpecifierQualifierList(C_grammarParser::SpecifierQualifierListContext *context) = 0;

    virtual antlrcpp::Any visitTypeQualifier(C_grammarParser::TypeQualifierContext *context) = 0;

    virtual antlrcpp::Any visitDeclarator(C_grammarParser::DeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitDirectDeclarator(C_grammarParser::DirectDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitNestedParenthesesBlock(C_grammarParser::NestedParenthesesBlockContext *context) = 0;

    virtual antlrcpp::Any visitTypeQualifierList(C_grammarParser::TypeQualifierListContext *context) = 0;

    virtual antlrcpp::Any visitParameterTypeList(C_grammarParser::ParameterTypeListContext *context) = 0;

    virtual antlrcpp::Any visitParameterList(C_grammarParser::ParameterListContext *context) = 0;

    virtual antlrcpp::Any visitParameterDeclaration(C_grammarParser::ParameterDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitIdentifierList(C_grammarParser::IdentifierListContext *context) = 0;

    virtual antlrcpp::Any visitTypeName(C_grammarParser::TypeNameContext *context) = 0;

    virtual antlrcpp::Any visitTypedefName(C_grammarParser::TypedefNameContext *context) = 0;

    virtual antlrcpp::Any visitInitializer(C_grammarParser::InitializerContext *context) = 0;

    virtual antlrcpp::Any visitInitializerList(C_grammarParser::InitializerListContext *context) = 0;

    virtual antlrcpp::Any visitDesignation(C_grammarParser::DesignationContext *context) = 0;

    virtual antlrcpp::Any visitDesignatorList(C_grammarParser::DesignatorListContext *context) = 0;

    virtual antlrcpp::Any visitDesignator(C_grammarParser::DesignatorContext *context) = 0;

    virtual antlrcpp::Any visitStatement(C_grammarParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitCompoundStatement(C_grammarParser::CompoundStatementContext *context) = 0;

    virtual antlrcpp::Any visitBlockItemList(C_grammarParser::BlockItemListContext *context) = 0;

    virtual antlrcpp::Any visitBlockItem(C_grammarParser::BlockItemContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(C_grammarParser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitSelectionStatement(C_grammarParser::SelectionStatementContext *context) = 0;

    virtual antlrcpp::Any visitIterationStatement(C_grammarParser::IterationStatementContext *context) = 0;

    virtual antlrcpp::Any visitForCondition(C_grammarParser::ForConditionContext *context) = 0;

    virtual antlrcpp::Any visitForDeclaration(C_grammarParser::ForDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitForExpression(C_grammarParser::ForExpressionContext *context) = 0;

    virtual antlrcpp::Any visitReturnStatement(C_grammarParser::ReturnStatementContext *context) = 0;

    virtual antlrcpp::Any visitTranslationUnit(C_grammarParser::TranslationUnitContext *context) = 0;

    virtual antlrcpp::Any visitExternalDeclaration(C_grammarParser::ExternalDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDefinition(C_grammarParser::FunctionDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitDeclarationList(C_grammarParser::DeclarationListContext *context) = 0;


};

}  // namespace C_parser
