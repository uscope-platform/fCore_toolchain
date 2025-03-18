
// Generated from /home/filssavi/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace C_parser {


class  C_grammarParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, Case = 2, Char = 3, Const = 4, Else = 5, Float = 6, For = 7, 
    If = 8, Int = 9, Long = 10, Return = 11, Short = 12, Signed = 13, Typedef = 14, 
    Unsigned = 15, Void = 16, Volatile = 17, While = 18, LeftParen = 19, 
    RightParen = 20, LeftBracket = 21, RightBracket = 22, LeftBrace = 23, 
    RightBrace = 24, Less = 25, LessEqual = 26, Greater = 27, GreaterEqual = 28, 
    LeftShift = 29, RightShift = 30, Plus = 31, PlusPlus = 32, Minus = 33, 
    MinusMinus = 34, Star = 35, Div = 36, Mod = 37, And = 38, Or = 39, AndAnd = 40, 
    OrOr = 41, Caret = 42, Not = 43, Tilde = 44, Question = 45, Colon = 46, 
    Semi = 47, Comma = 48, Assign = 49, StarAssign = 50, DivAssign = 51, 
    ModAssign = 52, PlusAssign = 53, MinusAssign = 54, LeftShiftAssign = 55, 
    RightShiftAssign = 56, AndAssign = 57, XorAssign = 58, OrAssign = 59, 
    Equal = 60, NotEqual = 61, Arrow = 62, Dot = 63, Ellipsis = 64, Identifier = 65, 
    IntegerConstant = 66, FloatingConstant = 67, DigitSequence = 68, CharacterConstant = 69, 
    StringLiteral = 70, ComplexDefine = 71, IncludeDirective = 72, AsmBlock = 73, 
    LineAfterPreprocessing = 74, LineDirective = 75, PragmaDirective = 76, 
    Whitespace = 77, Newline = 78, BlockComment = 79, LineComment = 80
  };

  enum {
    RuleCompilationUnit = 0, RulePrimaryExpression = 1, RuleUnaryExpression = 2, 
    RuleArrayAccessExpression = 3, RuleUnaryOperator = 4, RuleMultiplicativeOperator = 5, 
    RuleMultiplicativeExpression = 6, RuleAdditiveOperator = 7, RuleAdditiveExpression = 8, 
    RuleShiftOperator = 9, RuleShiftExpression = 10, RuleRelationalOperator = 11, 
    RuleRelationalExpression = 12, RuleEqualityOperator = 13, RuleEqualityExpression = 14, 
    RuleAndExpression = 15, RuleExclusiveOrExpression = 16, RuleInclusiveOrExpression = 17, 
    RuleLogicalAndExpression = 18, RuleLogicalOrExpression = 19, RuleConditionalExpression = 20, 
    RuleAssignmentExpression = 21, RuleAssignmentOperator = 22, RuleExpression = 23, 
    RuleConstantExpression = 24, RuleDeclaration = 25, RuleInitDeclaratorList = 26, 
    RuleInitDeclarator = 27, RuleTypeSpecifier = 28, RuleStructExpression = 29, 
    RuleStructSpecifier = 30, RuleStructDeclarationList = 31, RuleSpecifierQualifierList = 32, 
    RuleStructDeclaration = 33, RuleStructDeclaratorList = 34, RuleStructDeclarator = 35, 
    RuleDeclarator = 36, RuleDirectDeclarator = 37, RuleArrayDeclarator = 38, 
    RuleNestedParenthesesBlock = 39, RuleParameterTypeList = 40, RuleParameterList = 41, 
    RuleParameterDeclaration = 42, RuleIdentifierList = 43, RuleTypeName = 44, 
    RuleTypedefName = 45, RuleInitializer = 46, RuleFunctionCallExpression = 47, 
    RuleArgumentExpressionList = 48, RuleArgumentExpression = 49, RuleInitializerList = 50, 
    RuleDesignation = 51, RuleDesignatorList = 52, RuleDesignator = 53, 
    RuleStatement = 54, RuleCompoundStatement = 55, RuleBlockItem = 56, 
    RuleExpressionStatement = 57, RuleIfContent = 58, RuleElseContent = 59, 
    RuleConditionalBlockItem = 60, RuleConditionContent = 61, RuleSelectionStatement = 62, 
    RuleIterationStatement = 63, RuleForContent = 64, RuleForBlockItem = 65, 
    RuleForExitCondition = 66, RuleForDeclaration = 67, RuleForIterationExpression = 68, 
    RuleReturnStatement = 69, RuleTranslationUnit = 70, RuleExternalDeclaration = 71, 
    RuleFunctionDefinition = 72, RuleDeclarationList = 73, RuleConstant = 74
  };

  explicit C_grammarParser(antlr4::TokenStream *input);

  C_grammarParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~C_grammarParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CompilationUnitContext;
  class PrimaryExpressionContext;
  class UnaryExpressionContext;
  class ArrayAccessExpressionContext;
  class UnaryOperatorContext;
  class MultiplicativeOperatorContext;
  class MultiplicativeExpressionContext;
  class AdditiveOperatorContext;
  class AdditiveExpressionContext;
  class ShiftOperatorContext;
  class ShiftExpressionContext;
  class RelationalOperatorContext;
  class RelationalExpressionContext;
  class EqualityOperatorContext;
  class EqualityExpressionContext;
  class AndExpressionContext;
  class ExclusiveOrExpressionContext;
  class InclusiveOrExpressionContext;
  class LogicalAndExpressionContext;
  class LogicalOrExpressionContext;
  class ConditionalExpressionContext;
  class AssignmentExpressionContext;
  class AssignmentOperatorContext;
  class ExpressionContext;
  class ConstantExpressionContext;
  class DeclarationContext;
  class InitDeclaratorListContext;
  class InitDeclaratorContext;
  class TypeSpecifierContext;
  class StructExpressionContext;
  class StructSpecifierContext;
  class StructDeclarationListContext;
  class SpecifierQualifierListContext;
  class StructDeclarationContext;
  class StructDeclaratorListContext;
  class StructDeclaratorContext;
  class DeclaratorContext;
  class DirectDeclaratorContext;
  class ArrayDeclaratorContext;
  class NestedParenthesesBlockContext;
  class ParameterTypeListContext;
  class ParameterListContext;
  class ParameterDeclarationContext;
  class IdentifierListContext;
  class TypeNameContext;
  class TypedefNameContext;
  class InitializerContext;
  class FunctionCallExpressionContext;
  class ArgumentExpressionListContext;
  class ArgumentExpressionContext;
  class InitializerListContext;
  class DesignationContext;
  class DesignatorListContext;
  class DesignatorContext;
  class StatementContext;
  class CompoundStatementContext;
  class BlockItemContext;
  class ExpressionStatementContext;
  class IfContentContext;
  class ElseContentContext;
  class ConditionalBlockItemContext;
  class ConditionContentContext;
  class SelectionStatementContext;
  class IterationStatementContext;
  class ForContentContext;
  class ForBlockItemContext;
  class ForExitConditionContext;
  class ForDeclarationContext;
  class ForIterationExpressionContext;
  class ReturnStatementContext;
  class TranslationUnitContext;
  class ExternalDeclarationContext;
  class FunctionDefinitionContext;
  class DeclarationListContext;
  class ConstantContext; 

  class  CompilationUnitContext : public antlr4::ParserRuleContext {
  public:
    CompilationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    TranslationUnitContext *translationUnit();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompilationUnitContext* compilationUnit();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    ConstantContext *constant();
    std::vector<antlr4::tree::TerminalNode *> StringLiteral();
    antlr4::tree::TerminalNode* StringLiteral(size_t i);
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StructExpressionContext *structExpression();
    PrimaryExpressionContext *primaryExpression();
    UnaryOperatorContext *unaryOperator();
    UnaryExpressionContext *unaryExpression();
    FunctionCallExpressionContext *functionCallExpression();
    std::vector<antlr4::tree::TerminalNode *> PlusPlus();
    antlr4::tree::TerminalNode* PlusPlus(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MinusMinus();
    antlr4::tree::TerminalNode* MinusMinus(size_t i);
    ArrayAccessExpressionContext *arrayAccessExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryExpressionContext* unaryExpression();

  class  ArrayAccessExpressionContext : public antlr4::ParserRuleContext {
  public:
    ArrayAccessExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PrimaryExpressionContext *> primaryExpression();
    PrimaryExpressionContext* primaryExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayAccessExpressionContext* arrayAccessExpression();

  class  UnaryOperatorContext : public antlr4::ParserRuleContext {
  public:
    UnaryOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Minus();
    antlr4::tree::TerminalNode *Tilde();
    antlr4::tree::TerminalNode *Not();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryOperatorContext* unaryOperator();

  class  MultiplicativeOperatorContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *Div();
    antlr4::tree::TerminalNode *Mod();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicativeOperatorContext* multiplicativeOperator();

  class  MultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExpressionContext *> unaryExpression();
    UnaryExpressionContext* unaryExpression(size_t i);
    std::vector<MultiplicativeOperatorContext *> multiplicativeOperator();
    MultiplicativeOperatorContext* multiplicativeOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicativeExpressionContext* multiplicativeExpression();

  class  AdditiveOperatorContext : public antlr4::ParserRuleContext {
  public:
    AdditiveOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdditiveOperatorContext* additiveOperator();

  class  AdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    AdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);
    std::vector<AdditiveOperatorContext *> additiveOperator();
    AdditiveOperatorContext* additiveOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdditiveExpressionContext* additiveExpression();

  class  ShiftOperatorContext : public antlr4::ParserRuleContext {
  public:
    ShiftOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftShift();
    antlr4::tree::TerminalNode *RightShift();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ShiftOperatorContext* shiftOperator();

  class  ShiftExpressionContext : public antlr4::ParserRuleContext {
  public:
    ShiftExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AdditiveExpressionContext *> additiveExpression();
    AdditiveExpressionContext* additiveExpression(size_t i);
    std::vector<ShiftOperatorContext *> shiftOperator();
    ShiftOperatorContext* shiftOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ShiftExpressionContext* shiftExpression();

  class  RelationalOperatorContext : public antlr4::ParserRuleContext {
  public:
    RelationalOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *LessEqual();
    antlr4::tree::TerminalNode *GreaterEqual();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelationalOperatorContext* relationalOperator();

  class  RelationalExpressionContext : public antlr4::ParserRuleContext {
  public:
    RelationalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ShiftExpressionContext *> shiftExpression();
    ShiftExpressionContext* shiftExpression(size_t i);
    std::vector<RelationalOperatorContext *> relationalOperator();
    RelationalOperatorContext* relationalOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelationalExpressionContext* relationalExpression();

  class  EqualityOperatorContext : public antlr4::ParserRuleContext {
  public:
    EqualityOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Equal();
    antlr4::tree::TerminalNode *NotEqual();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqualityOperatorContext* equalityOperator();

  class  EqualityExpressionContext : public antlr4::ParserRuleContext {
  public:
    EqualityExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RelationalExpressionContext *> relationalExpression();
    RelationalExpressionContext* relationalExpression(size_t i);
    std::vector<EqualityOperatorContext *> equalityOperator();
    EqualityOperatorContext* equalityOperator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqualityExpressionContext* equalityExpression();

  class  AndExpressionContext : public antlr4::ParserRuleContext {
  public:
    AndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EqualityExpressionContext *> equalityExpression();
    EqualityExpressionContext* equalityExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> And();
    antlr4::tree::TerminalNode* And(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AndExpressionContext* andExpression();

  class  ExclusiveOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExclusiveOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AndExpressionContext *> andExpression();
    AndExpressionContext* andExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Caret();
    antlr4::tree::TerminalNode* Caret(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExclusiveOrExpressionContext* exclusiveOrExpression();

  class  InclusiveOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    InclusiveOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExclusiveOrExpressionContext *> exclusiveOrExpression();
    ExclusiveOrExpressionContext* exclusiveOrExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Or();
    antlr4::tree::TerminalNode* Or(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InclusiveOrExpressionContext* inclusiveOrExpression();

  class  LogicalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InclusiveOrExpressionContext *> inclusiveOrExpression();
    InclusiveOrExpressionContext* inclusiveOrExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AndAnd();
    antlr4::tree::TerminalNode* AndAnd(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalAndExpressionContext* logicalAndExpression();

  class  LogicalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LogicalAndExpressionContext *> logicalAndExpression();
    LogicalAndExpressionContext* logicalAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OrOr();
    antlr4::tree::TerminalNode* OrOr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalOrExpressionContext* logicalOrExpression();

  class  ConditionalExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicalOrExpressionContext *logicalOrExpression();
    antlr4::tree::TerminalNode *Question();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *Colon();
    ConditionalExpressionContext *conditionalExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionalExpressionContext* conditionalExpression();

  class  AssignmentExpressionContext : public antlr4::ParserRuleContext {
  public:
    AssignmentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionalExpressionContext *conditionalExpression();
    UnaryExpressionContext *unaryExpression();
    AssignmentOperatorContext *assignmentOperator();
    AssignmentExpressionContext *assignmentExpression();
    antlr4::tree::TerminalNode *DigitSequence();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentExpressionContext* assignmentExpression();

  class  AssignmentOperatorContext : public antlr4::ParserRuleContext {
  public:
    AssignmentOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Assign();
    antlr4::tree::TerminalNode *StarAssign();
    antlr4::tree::TerminalNode *DivAssign();
    antlr4::tree::TerminalNode *ModAssign();
    antlr4::tree::TerminalNode *PlusAssign();
    antlr4::tree::TerminalNode *MinusAssign();
    antlr4::tree::TerminalNode *LeftShiftAssign();
    antlr4::tree::TerminalNode *RightShiftAssign();
    antlr4::tree::TerminalNode *AndAssign();
    antlr4::tree::TerminalNode *XorAssign();
    antlr4::tree::TerminalNode *OrAssign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentOperatorContext* assignmentOperator();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AssignmentExpressionContext *> assignmentExpression();
    AssignmentExpressionContext* assignmentExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  ConstantExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConstantExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionalExpressionContext *conditionalExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantExpressionContext* constantExpression();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSpecifierContext *typeSpecifier();
    antlr4::tree::TerminalNode *Const();
    InitDeclaratorListContext *initDeclaratorList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  InitDeclaratorListContext : public antlr4::ParserRuleContext {
  public:
    InitDeclaratorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InitDeclaratorContext *> initDeclarator();
    InitDeclaratorContext* initDeclarator(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitDeclaratorListContext* initDeclaratorList();

  class  InitDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    InitDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *Assign();
    InitializerContext *initializer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitDeclaratorContext* initDeclarator();

  class  TypeSpecifierContext : public antlr4::ParserRuleContext {
  public:
    TypeSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Void();
    antlr4::tree::TerminalNode *Char();
    antlr4::tree::TerminalNode *Short();
    antlr4::tree::TerminalNode *Int();
    antlr4::tree::TerminalNode *Long();
    antlr4::tree::TerminalNode *Float();
    antlr4::tree::TerminalNode *Signed();
    antlr4::tree::TerminalNode *Unsigned();
    StructSpecifierContext *structSpecifier();
    TypedefNameContext *typedefName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeSpecifierContext* typeSpecifier();

  class  StructExpressionContext : public antlr4::ParserRuleContext {
  public:
    StructExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExpressionContext *primaryExpression();
    std::vector<antlr4::tree::TerminalNode *> Dot();
    antlr4::tree::TerminalNode* Dot(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructExpressionContext* structExpression();

  class  StructSpecifierContext : public antlr4::ParserRuleContext {
  public:
    StructSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    StructDeclarationListContext *structDeclarationList();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructSpecifierContext* structSpecifier();

  class  StructDeclarationListContext : public antlr4::ParserRuleContext {
  public:
    StructDeclarationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StructDeclarationContext *> structDeclaration();
    StructDeclarationContext* structDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDeclarationListContext* structDeclarationList();

  class  SpecifierQualifierListContext : public antlr4::ParserRuleContext {
  public:
    SpecifierQualifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSpecifierContext *typeSpecifier();
    antlr4::tree::TerminalNode *Const();
    SpecifierQualifierListContext *specifierQualifierList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecifierQualifierListContext* specifierQualifierList();

  class  StructDeclarationContext : public antlr4::ParserRuleContext {
  public:
    StructDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SpecifierQualifierListContext *specifierQualifierList();
    StructDeclaratorListContext *structDeclaratorList();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDeclarationContext* structDeclaration();

  class  StructDeclaratorListContext : public antlr4::ParserRuleContext {
  public:
    StructDeclaratorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StructDeclaratorContext *> structDeclarator();
    StructDeclaratorContext* structDeclarator(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDeclaratorListContext* structDeclaratorList();

  class  StructDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    StructDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *Colon();
    ConstantExpressionContext *constantExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDeclaratorContext* structDeclarator();

  class  DeclaratorContext : public antlr4::ParserRuleContext {
  public:
    DeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DirectDeclaratorContext *directDeclarator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclaratorContext* declarator();

  class  DirectDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    DirectDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *RightParen();
    antlr4::tree::TerminalNode *Colon();
    antlr4::tree::TerminalNode *DigitSequence();
    DirectDeclaratorContext *directDeclarator();
    std::vector<ArrayDeclaratorContext *> arrayDeclarator();
    ArrayDeclaratorContext* arrayDeclarator(size_t i);
    ParameterTypeListContext *parameterTypeList();
    IdentifierListContext *identifierList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DirectDeclaratorContext* directDeclarator();
  DirectDeclaratorContext* directDeclarator(int precedence);
  class  ArrayDeclaratorContext : public antlr4::ParserRuleContext {
  public:
    ArrayDeclaratorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *Const();
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayDeclaratorContext* arrayDeclarator();

  class  NestedParenthesesBlockContext : public antlr4::ParserRuleContext {
  public:
    NestedParenthesesBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> LeftParen();
    antlr4::tree::TerminalNode* LeftParen(size_t i);
    std::vector<NestedParenthesesBlockContext *> nestedParenthesesBlock();
    NestedParenthesesBlockContext* nestedParenthesesBlock(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightParen();
    antlr4::tree::TerminalNode* RightParen(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NestedParenthesesBlockContext* nestedParenthesesBlock();

  class  ParameterTypeListContext : public antlr4::ParserRuleContext {
  public:
    ParameterTypeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *Comma();
    antlr4::tree::TerminalNode *Ellipsis();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterTypeListContext* parameterTypeList();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterDeclarationContext *> parameterDeclaration();
    ParameterDeclarationContext* parameterDeclaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();

  class  ParameterDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ParameterDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeSpecifierContext *typeSpecifier();
    DeclaratorContext *declarator();
    antlr4::tree::TerminalNode *Const();
    StructSpecifierContext *structSpecifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterDeclarationContext* parameterDeclaration();

  class  IdentifierListContext : public antlr4::ParserRuleContext {
  public:
    IdentifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierListContext* identifierList();

  class  TypeNameContext : public antlr4::ParserRuleContext {
  public:
    TypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SpecifierQualifierListContext *specifierQualifierList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeNameContext* typeName();

  class  TypedefNameContext : public antlr4::ParserRuleContext {
  public:
    TypedefNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypedefNameContext* typedefName();

  class  InitializerContext : public antlr4::ParserRuleContext {
  public:
    InitializerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();
    antlr4::tree::TerminalNode *LeftBrace();
    InitializerListContext *initializerList();
    antlr4::tree::TerminalNode *RightBrace();
    antlr4::tree::TerminalNode *Comma();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitializerContext* initializer();

  class  FunctionCallExpressionContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypedefNameContext *typedefName();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    ArgumentExpressionListContext *argumentExpressionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionCallExpressionContext* functionCallExpression();

  class  ArgumentExpressionListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentExpressionContext *> argumentExpression();
    ArgumentExpressionContext* argumentExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentExpressionListContext* argumentExpressionList();

  class  ArgumentExpressionContext : public antlr4::ParserRuleContext {
  public:
    ArgumentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentExpressionContext* argumentExpression();

  class  InitializerListContext : public antlr4::ParserRuleContext {
  public:
    InitializerListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InitializerContext *> initializer();
    InitializerContext* initializer(size_t i);
    std::vector<DesignationContext *> designation();
    DesignationContext* designation(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitializerListContext* initializerList();

  class  DesignationContext : public antlr4::ParserRuleContext {
  public:
    DesignationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DesignatorListContext *designatorList();
    antlr4::tree::TerminalNode *Assign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DesignationContext* designation();

  class  DesignatorListContext : public antlr4::ParserRuleContext {
  public:
    DesignatorListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DesignatorContext *> designator();
    DesignatorContext* designator(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DesignatorListContext* designatorList();

  class  DesignatorContext : public antlr4::ParserRuleContext {
  public:
    DesignatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *RightBracket();
    antlr4::tree::TerminalNode *Dot();
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DesignatorContext* designator();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionStatementContext *expressionStatement();
    antlr4::tree::TerminalNode *Semi();
    SelectionStatementContext *selectionStatement();
    IterationStatementContext *iterationStatement();
    ReturnStatementContext *returnStatement();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<LogicalOrExpressionContext *> logicalOrExpression();
    LogicalOrExpressionContext* logicalOrExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Colon();
    antlr4::tree::TerminalNode* Colon(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  CompoundStatementContext : public antlr4::ParserRuleContext {
  public:
    CompoundStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    std::vector<BlockItemContext *> blockItem();
    BlockItemContext* blockItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompoundStatementContext* compoundStatement();

  class  BlockItemContext : public antlr4::ParserRuleContext {
  public:
    BlockItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    DeclarationContext *declaration();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockItemContext* blockItem();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  IfContentContext : public antlr4::ParserRuleContext {
  public:
    IfContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    std::vector<ConditionalBlockItemContext *> conditionalBlockItem();
    ConditionalBlockItemContext* conditionalBlockItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfContentContext* ifContent();

  class  ElseContentContext : public antlr4::ParserRuleContext {
  public:
    ElseContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    std::vector<ConditionalBlockItemContext *> conditionalBlockItem();
    ConditionalBlockItemContext* conditionalBlockItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElseContentContext* elseContent();

  class  ConditionalBlockItemContext : public antlr4::ParserRuleContext {
  public:
    ConditionalBlockItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    DeclarationContext *declaration();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionalBlockItemContext* conditionalBlockItem();

  class  ConditionContentContext : public antlr4::ParserRuleContext {
  public:
    ConditionContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionContentContext* conditionContent();

  class  SelectionStatementContext : public antlr4::ParserRuleContext {
  public:
    SelectionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *If();
    antlr4::tree::TerminalNode *LeftParen();
    ConditionContentContext *conditionContent();
    antlr4::tree::TerminalNode *RightParen();
    IfContentContext *ifContent();
    antlr4::tree::TerminalNode *Else();
    ElseContentContext *elseContent();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectionStatementContext* selectionStatement();

  class  IterationStatementContext : public antlr4::ParserRuleContext {
  public:
    IterationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *For();
    antlr4::tree::TerminalNode *LeftParen();
    ForDeclarationContext *forDeclaration();
    std::vector<antlr4::tree::TerminalNode *> Semi();
    antlr4::tree::TerminalNode* Semi(size_t i);
    ForExitConditionContext *forExitCondition();
    ForIterationExpressionContext *forIterationExpression();
    antlr4::tree::TerminalNode *RightParen();
    ForContentContext *forContent();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IterationStatementContext* iterationStatement();

  class  ForContentContext : public antlr4::ParserRuleContext {
  public:
    ForContentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    std::vector<ForBlockItemContext *> forBlockItem();
    ForBlockItemContext* forBlockItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForContentContext* forContent();

  class  ForBlockItemContext : public antlr4::ParserRuleContext {
  public:
    ForBlockItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    DeclarationContext *declaration();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForBlockItemContext* forBlockItem();

  class  ForExitConditionContext : public antlr4::ParserRuleContext {
  public:
    ForExitConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentExpressionContext *assignmentExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForExitConditionContext* forExitCondition();

  class  ForDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ForDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclarationContext *declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForDeclarationContext* forDeclaration();

  class  ForIterationExpressionContext : public antlr4::ParserRuleContext {
  public:
    ForIterationExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AssignmentExpressionContext *> assignmentExpression();
    AssignmentExpressionContext* assignmentExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForIterationExpressionContext* forIterationExpression();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Return();
    antlr4::tree::TerminalNode *Semi();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  TranslationUnitContext : public antlr4::ParserRuleContext {
  public:
    TranslationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExternalDeclarationContext *> externalDeclaration();
    ExternalDeclarationContext* externalDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TranslationUnitContext* translationUnit();

  class  ExternalDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ExternalDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDefinitionContext *functionDefinition();
    DeclarationContext *declaration();
    antlr4::tree::TerminalNode *Semi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExternalDeclarationContext* externalDeclaration();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclaratorContext *declarator();
    CompoundStatementContext *compoundStatement();
    TypeSpecifierContext *typeSpecifier();
    DeclarationListContext *declarationList();
    antlr4::tree::TerminalNode *Const();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  DeclarationListContext : public antlr4::ParserRuleContext {
  public:
    DeclarationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Semi();
    antlr4::tree::TerminalNode* Semi(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationListContext* declarationList();

  class  ConstantContext : public antlr4::ParserRuleContext {
  public:
    ConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntegerConstant();
    antlr4::tree::TerminalNode *Minus();
    antlr4::tree::TerminalNode *FloatingConstant();
    antlr4::tree::TerminalNode *CharacterConstant();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantContext* constant();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool directDeclaratorSempred(DirectDeclaratorContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

}  // namespace C_parser
