
// Generated from /home/fils/git/fCore_has/src/frontend/C_grammar.g4 by ANTLR 4.9.1


#include "C_grammarListener.h"
#include "C_grammarVisitor.h"

#include "C_grammarParser.h"


using namespace antlrcpp;
using namespace C_parser;
using namespace antlr4;

C_grammarParser::C_grammarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

C_grammarParser::~C_grammarParser() {
  delete _interpreter;
}

std::string C_grammarParser::getGrammarFileName() const {
  return "C_grammar.g4";
}

const std::vector<std::string>& C_grammarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& C_grammarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

C_grammarParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::CompilationUnitContext::EOF() {
  return getToken(C_grammarParser::EOF, 0);
}

C_grammarParser::TranslationUnitContext* C_grammarParser::CompilationUnitContext::translationUnit() {
  return getRuleContext<C_grammarParser::TranslationUnitContext>(0);
}


size_t C_grammarParser::CompilationUnitContext::getRuleIndex() const {
  return C_grammarParser::RuleCompilationUnit;
}

void C_grammarParser::CompilationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompilationUnit(this);
}

void C_grammarParser::CompilationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompilationUnit(this);
}


antlrcpp::Any C_grammarParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::CompilationUnitContext* C_grammarParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, C_grammarParser::RuleCompilationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::Semi))) != 0) || _la == C_grammarParser::Identifier) {
      setState(120);
      translationUnit();
    }
    setState(123);
    match(C_grammarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

C_grammarParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

C_grammarParser::ConstantContext* C_grammarParser::PrimaryExpressionContext::constant() {
  return getRuleContext<C_grammarParser::ConstantContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::PrimaryExpressionContext::StringLiteral() {
  return getTokens(C_grammarParser::StringLiteral);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::StringLiteral(size_t i) {
  return getToken(C_grammarParser::StringLiteral, i);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::PrimaryExpressionContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}


size_t C_grammarParser::PrimaryExpressionContext::getRuleIndex() const {
  return C_grammarParser::RulePrimaryExpression;
}

void C_grammarParser::PrimaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpression(this);
}

void C_grammarParser::PrimaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpression(this);
}


antlrcpp::Any C_grammarParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 2, C_grammarParser::RulePrimaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(136);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(125);
        match(C_grammarParser::Identifier);
        break;
      }

      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::CharacterConstant: {
        enterOuterAlt(_localctx, 2);
        setState(126);
        constant();
        break;
      }

      case C_grammarParser::StringLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(128); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(127);
          match(C_grammarParser::StringLiteral);
          setState(130); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == C_grammarParser::StringLiteral);
        break;
      }

      case C_grammarParser::LeftParen: {
        enterOuterAlt(_localctx, 4);
        setState(132);
        match(C_grammarParser::LeftParen);
        setState(133);
        expression();
        setState(134);
        match(C_grammarParser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

C_grammarParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<C_grammarParser::PrimaryExpressionContext>(0);
}

C_grammarParser::UnaryOperatorContext* C_grammarParser::UnaryExpressionContext::unaryOperator() {
  return getRuleContext<C_grammarParser::UnaryOperatorContext>(0);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::UnaryExpressionContext::PlusPlus() {
  return getTokens(C_grammarParser::PlusPlus);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::PlusPlus(size_t i) {
  return getToken(C_grammarParser::PlusPlus, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::UnaryExpressionContext::MinusMinus() {
  return getTokens(C_grammarParser::MinusMinus);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::MinusMinus(size_t i) {
  return getToken(C_grammarParser::MinusMinus, i);
}


size_t C_grammarParser::UnaryExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleUnaryExpression;
}

void C_grammarParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void C_grammarParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}


antlrcpp::Any C_grammarParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 4, C_grammarParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::PlusPlus

    || _la == C_grammarParser::MinusMinus) {
      setState(138);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::PlusPlus

      || _la == C_grammarParser::MinusMinus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(143);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(148);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftParen:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(144);
        primaryExpression();
        break;
      }

      case C_grammarParser::Minus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde: {
        setState(145);
        unaryOperator();
        setState(146);
        unaryExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOperatorContext ------------------------------------------------------------------

C_grammarParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Minus() {
  return getToken(C_grammarParser::Minus, 0);
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Tilde() {
  return getToken(C_grammarParser::Tilde, 0);
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Not() {
  return getToken(C_grammarParser::Not, 0);
}


size_t C_grammarParser::UnaryOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleUnaryOperator;
}

void C_grammarParser::UnaryOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOperator(this);
}

void C_grammarParser::UnaryOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOperator(this);
}


antlrcpp::Any C_grammarParser::UnaryOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitUnaryOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::UnaryOperatorContext* C_grammarParser::unaryOperator() {
  UnaryOperatorContext *_localctx = _tracker.createInstance<UnaryOperatorContext>(_ctx, getState());
  enterRule(_localctx, 6, C_grammarParser::RuleUnaryOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Minus)
      | (1ULL << C_grammarParser::Not)
      | (1ULL << C_grammarParser::Tilde))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeOperatorContext ------------------------------------------------------------------

C_grammarParser::MultiplicativeOperatorContext::MultiplicativeOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::MultiplicativeOperatorContext::Star() {
  return getToken(C_grammarParser::Star, 0);
}

tree::TerminalNode* C_grammarParser::MultiplicativeOperatorContext::Div() {
  return getToken(C_grammarParser::Div, 0);
}

tree::TerminalNode* C_grammarParser::MultiplicativeOperatorContext::Mod() {
  return getToken(C_grammarParser::Mod, 0);
}


size_t C_grammarParser::MultiplicativeOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleMultiplicativeOperator;
}

void C_grammarParser::MultiplicativeOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeOperator(this);
}

void C_grammarParser::MultiplicativeOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeOperator(this);
}


antlrcpp::Any C_grammarParser::MultiplicativeOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::MultiplicativeOperatorContext* C_grammarParser::multiplicativeOperator() {
  MultiplicativeOperatorContext *_localctx = _tracker.createInstance<MultiplicativeOperatorContext>(_ctx, getState());
  enterRule(_localctx, 8, C_grammarParser::RuleMultiplicativeOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Star)
      | (1ULL << C_grammarParser::Div)
      | (1ULL << C_grammarParser::Mod))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

C_grammarParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::UnaryExpressionContext *> C_grammarParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<C_grammarParser::UnaryExpressionContext>();
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(i);
}

std::vector<C_grammarParser::MultiplicativeOperatorContext *> C_grammarParser::MultiplicativeExpressionContext::multiplicativeOperator() {
  return getRuleContexts<C_grammarParser::MultiplicativeOperatorContext>();
}

C_grammarParser::MultiplicativeOperatorContext* C_grammarParser::MultiplicativeExpressionContext::multiplicativeOperator(size_t i) {
  return getRuleContext<C_grammarParser::MultiplicativeOperatorContext>(i);
}


size_t C_grammarParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleMultiplicativeExpression;
}

void C_grammarParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void C_grammarParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}


antlrcpp::Any C_grammarParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::MultiplicativeExpressionContext* C_grammarParser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 10, C_grammarParser::RuleMultiplicativeExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    unaryExpression();
    setState(160);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Star)
      | (1ULL << C_grammarParser::Div)
      | (1ULL << C_grammarParser::Mod))) != 0)) {
      setState(155);
      multiplicativeOperator();
      setState(156);
      unaryExpression();
      setState(162);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

C_grammarParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::MultiplicativeExpressionContext *> C_grammarParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContexts<C_grammarParser::MultiplicativeExpressionContext>();
}

C_grammarParser::MultiplicativeExpressionContext* C_grammarParser::AdditiveExpressionContext::multiplicativeExpression(size_t i) {
  return getRuleContext<C_grammarParser::MultiplicativeExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::AdditiveExpressionContext::Plus() {
  return getTokens(C_grammarParser::Plus);
}

tree::TerminalNode* C_grammarParser::AdditiveExpressionContext::Plus(size_t i) {
  return getToken(C_grammarParser::Plus, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::AdditiveExpressionContext::Minus() {
  return getTokens(C_grammarParser::Minus);
}

tree::TerminalNode* C_grammarParser::AdditiveExpressionContext::Minus(size_t i) {
  return getToken(C_grammarParser::Minus, i);
}


size_t C_grammarParser::AdditiveExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleAdditiveExpression;
}

void C_grammarParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void C_grammarParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}


antlrcpp::Any C_grammarParser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AdditiveExpressionContext* C_grammarParser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 12, C_grammarParser::RuleAdditiveExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(163);
    multiplicativeExpression();
    setState(168);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Plus

    || _la == C_grammarParser::Minus) {
      setState(164);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::Plus

      || _la == C_grammarParser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(165);
      multiplicativeExpression();
      setState(170);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftExpressionContext ------------------------------------------------------------------

C_grammarParser::ShiftExpressionContext::ShiftExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AdditiveExpressionContext *> C_grammarParser::ShiftExpressionContext::additiveExpression() {
  return getRuleContexts<C_grammarParser::AdditiveExpressionContext>();
}

C_grammarParser::AdditiveExpressionContext* C_grammarParser::ShiftExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<C_grammarParser::AdditiveExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ShiftExpressionContext::LeftShift() {
  return getTokens(C_grammarParser::LeftShift);
}

tree::TerminalNode* C_grammarParser::ShiftExpressionContext::LeftShift(size_t i) {
  return getToken(C_grammarParser::LeftShift, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ShiftExpressionContext::RightShift() {
  return getTokens(C_grammarParser::RightShift);
}

tree::TerminalNode* C_grammarParser::ShiftExpressionContext::RightShift(size_t i) {
  return getToken(C_grammarParser::RightShift, i);
}


size_t C_grammarParser::ShiftExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleShiftExpression;
}

void C_grammarParser::ShiftExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftExpression(this);
}

void C_grammarParser::ShiftExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftExpression(this);
}


antlrcpp::Any C_grammarParser::ShiftExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitShiftExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ShiftExpressionContext* C_grammarParser::shiftExpression() {
  ShiftExpressionContext *_localctx = _tracker.createInstance<ShiftExpressionContext>(_ctx, getState());
  enterRule(_localctx, 14, C_grammarParser::RuleShiftExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(171);
    additiveExpression();
    setState(176);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::LeftShift

    || _la == C_grammarParser::RightShift) {
      setState(172);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::LeftShift

      || _la == C_grammarParser::RightShift)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(173);
      additiveExpression();
      setState(178);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

C_grammarParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ShiftExpressionContext *> C_grammarParser::RelationalExpressionContext::shiftExpression() {
  return getRuleContexts<C_grammarParser::ShiftExpressionContext>();
}

C_grammarParser::ShiftExpressionContext* C_grammarParser::RelationalExpressionContext::shiftExpression(size_t i) {
  return getRuleContext<C_grammarParser::ShiftExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::RelationalExpressionContext::Less() {
  return getTokens(C_grammarParser::Less);
}

tree::TerminalNode* C_grammarParser::RelationalExpressionContext::Less(size_t i) {
  return getToken(C_grammarParser::Less, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::RelationalExpressionContext::Greater() {
  return getTokens(C_grammarParser::Greater);
}

tree::TerminalNode* C_grammarParser::RelationalExpressionContext::Greater(size_t i) {
  return getToken(C_grammarParser::Greater, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::RelationalExpressionContext::LessEqual() {
  return getTokens(C_grammarParser::LessEqual);
}

tree::TerminalNode* C_grammarParser::RelationalExpressionContext::LessEqual(size_t i) {
  return getToken(C_grammarParser::LessEqual, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::RelationalExpressionContext::GreaterEqual() {
  return getTokens(C_grammarParser::GreaterEqual);
}

tree::TerminalNode* C_grammarParser::RelationalExpressionContext::GreaterEqual(size_t i) {
  return getToken(C_grammarParser::GreaterEqual, i);
}


size_t C_grammarParser::RelationalExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleRelationalExpression;
}

void C_grammarParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void C_grammarParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}


antlrcpp::Any C_grammarParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::RelationalExpressionContext* C_grammarParser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 16, C_grammarParser::RuleRelationalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(179);
    shiftExpression();
    setState(184);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Less)
      | (1ULL << C_grammarParser::LessEqual)
      | (1ULL << C_grammarParser::Greater)
      | (1ULL << C_grammarParser::GreaterEqual))) != 0)) {
      setState(180);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::Less)
        | (1ULL << C_grammarParser::LessEqual)
        | (1ULL << C_grammarParser::Greater)
        | (1ULL << C_grammarParser::GreaterEqual))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(181);
      shiftExpression();
      setState(186);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

C_grammarParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::RelationalExpressionContext *> C_grammarParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContexts<C_grammarParser::RelationalExpressionContext>();
}

C_grammarParser::RelationalExpressionContext* C_grammarParser::EqualityExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<C_grammarParser::RelationalExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::EqualityExpressionContext::Equal() {
  return getTokens(C_grammarParser::Equal);
}

tree::TerminalNode* C_grammarParser::EqualityExpressionContext::Equal(size_t i) {
  return getToken(C_grammarParser::Equal, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::EqualityExpressionContext::NotEqual() {
  return getTokens(C_grammarParser::NotEqual);
}

tree::TerminalNode* C_grammarParser::EqualityExpressionContext::NotEqual(size_t i) {
  return getToken(C_grammarParser::NotEqual, i);
}


size_t C_grammarParser::EqualityExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleEqualityExpression;
}

void C_grammarParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}

void C_grammarParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}


antlrcpp::Any C_grammarParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EqualityExpressionContext* C_grammarParser::equalityExpression() {
  EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, getState());
  enterRule(_localctx, 18, C_grammarParser::RuleEqualityExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    relationalExpression();
    setState(192);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Equal

    || _la == C_grammarParser::NotEqual) {
      setState(188);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::Equal

      || _la == C_grammarParser::NotEqual)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(189);
      relationalExpression();
      setState(194);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AndExpressionContext ------------------------------------------------------------------

C_grammarParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::EqualityExpressionContext *> C_grammarParser::AndExpressionContext::equalityExpression() {
  return getRuleContexts<C_grammarParser::EqualityExpressionContext>();
}

C_grammarParser::EqualityExpressionContext* C_grammarParser::AndExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<C_grammarParser::EqualityExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::AndExpressionContext::And() {
  return getTokens(C_grammarParser::And);
}

tree::TerminalNode* C_grammarParser::AndExpressionContext::And(size_t i) {
  return getToken(C_grammarParser::And, i);
}


size_t C_grammarParser::AndExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleAndExpression;
}

void C_grammarParser::AndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpression(this);
}

void C_grammarParser::AndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpression(this);
}


antlrcpp::Any C_grammarParser::AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAndExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AndExpressionContext* C_grammarParser::andExpression() {
  AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 20, C_grammarParser::RuleAndExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    equalityExpression();
    setState(200);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::And) {
      setState(196);
      match(C_grammarParser::And);
      setState(197);
      equalityExpression();
      setState(202);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExclusiveOrExpressionContext ------------------------------------------------------------------

C_grammarParser::ExclusiveOrExpressionContext::ExclusiveOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AndExpressionContext *> C_grammarParser::ExclusiveOrExpressionContext::andExpression() {
  return getRuleContexts<C_grammarParser::AndExpressionContext>();
}

C_grammarParser::AndExpressionContext* C_grammarParser::ExclusiveOrExpressionContext::andExpression(size_t i) {
  return getRuleContext<C_grammarParser::AndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ExclusiveOrExpressionContext::Caret() {
  return getTokens(C_grammarParser::Caret);
}

tree::TerminalNode* C_grammarParser::ExclusiveOrExpressionContext::Caret(size_t i) {
  return getToken(C_grammarParser::Caret, i);
}


size_t C_grammarParser::ExclusiveOrExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleExclusiveOrExpression;
}

void C_grammarParser::ExclusiveOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExclusiveOrExpression(this);
}

void C_grammarParser::ExclusiveOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExclusiveOrExpression(this);
}


antlrcpp::Any C_grammarParser::ExclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExclusiveOrExpressionContext* C_grammarParser::exclusiveOrExpression() {
  ExclusiveOrExpressionContext *_localctx = _tracker.createInstance<ExclusiveOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 22, C_grammarParser::RuleExclusiveOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    andExpression();
    setState(208);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Caret) {
      setState(204);
      match(C_grammarParser::Caret);
      setState(205);
      andExpression();
      setState(210);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InclusiveOrExpressionContext ------------------------------------------------------------------

C_grammarParser::InclusiveOrExpressionContext::InclusiveOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ExclusiveOrExpressionContext *> C_grammarParser::InclusiveOrExpressionContext::exclusiveOrExpression() {
  return getRuleContexts<C_grammarParser::ExclusiveOrExpressionContext>();
}

C_grammarParser::ExclusiveOrExpressionContext* C_grammarParser::InclusiveOrExpressionContext::exclusiveOrExpression(size_t i) {
  return getRuleContext<C_grammarParser::ExclusiveOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::InclusiveOrExpressionContext::Or() {
  return getTokens(C_grammarParser::Or);
}

tree::TerminalNode* C_grammarParser::InclusiveOrExpressionContext::Or(size_t i) {
  return getToken(C_grammarParser::Or, i);
}


size_t C_grammarParser::InclusiveOrExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleInclusiveOrExpression;
}

void C_grammarParser::InclusiveOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInclusiveOrExpression(this);
}

void C_grammarParser::InclusiveOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInclusiveOrExpression(this);
}


antlrcpp::Any C_grammarParser::InclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InclusiveOrExpressionContext* C_grammarParser::inclusiveOrExpression() {
  InclusiveOrExpressionContext *_localctx = _tracker.createInstance<InclusiveOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 24, C_grammarParser::RuleInclusiveOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(211);
    exclusiveOrExpression();
    setState(216);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Or) {
      setState(212);
      match(C_grammarParser::Or);
      setState(213);
      exclusiveOrExpression();
      setState(218);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

C_grammarParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::InclusiveOrExpressionContext *> C_grammarParser::LogicalAndExpressionContext::inclusiveOrExpression() {
  return getRuleContexts<C_grammarParser::InclusiveOrExpressionContext>();
}

C_grammarParser::InclusiveOrExpressionContext* C_grammarParser::LogicalAndExpressionContext::inclusiveOrExpression(size_t i) {
  return getRuleContext<C_grammarParser::InclusiveOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::LogicalAndExpressionContext::AndAnd() {
  return getTokens(C_grammarParser::AndAnd);
}

tree::TerminalNode* C_grammarParser::LogicalAndExpressionContext::AndAnd(size_t i) {
  return getToken(C_grammarParser::AndAnd, i);
}


size_t C_grammarParser::LogicalAndExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleLogicalAndExpression;
}

void C_grammarParser::LogicalAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAndExpression(this);
}

void C_grammarParser::LogicalAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAndExpression(this);
}


antlrcpp::Any C_grammarParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::LogicalAndExpressionContext* C_grammarParser::logicalAndExpression() {
  LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 26, C_grammarParser::RuleLogicalAndExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    inclusiveOrExpression();
    setState(224);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::AndAnd) {
      setState(220);
      match(C_grammarParser::AndAnd);
      setState(221);
      inclusiveOrExpression();
      setState(226);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

C_grammarParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::LogicalAndExpressionContext *> C_grammarParser::LogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContexts<C_grammarParser::LogicalAndExpressionContext>();
}

C_grammarParser::LogicalAndExpressionContext* C_grammarParser::LogicalOrExpressionContext::logicalAndExpression(size_t i) {
  return getRuleContext<C_grammarParser::LogicalAndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::LogicalOrExpressionContext::OrOr() {
  return getTokens(C_grammarParser::OrOr);
}

tree::TerminalNode* C_grammarParser::LogicalOrExpressionContext::OrOr(size_t i) {
  return getToken(C_grammarParser::OrOr, i);
}


size_t C_grammarParser::LogicalOrExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleLogicalOrExpression;
}

void C_grammarParser::LogicalOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOrExpression(this);
}

void C_grammarParser::LogicalOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOrExpression(this);
}


antlrcpp::Any C_grammarParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::LogicalOrExpressionContext* C_grammarParser::logicalOrExpression() {
  LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 28, C_grammarParser::RuleLogicalOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(227);
    logicalAndExpression();
    setState(232);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::OrOr) {
      setState(228);
      match(C_grammarParser::OrOr);
      setState(229);
      logicalAndExpression();
      setState(234);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalExpressionContext ------------------------------------------------------------------

C_grammarParser::ConditionalExpressionContext::ConditionalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::LogicalOrExpressionContext* C_grammarParser::ConditionalExpressionContext::logicalOrExpression() {
  return getRuleContext<C_grammarParser::LogicalOrExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::ConditionalExpressionContext::Question() {
  return getToken(C_grammarParser::Question, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::ConditionalExpressionContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::ConditionalExpressionContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::ConditionalExpressionContext::conditionalExpression() {
  return getRuleContext<C_grammarParser::ConditionalExpressionContext>(0);
}


size_t C_grammarParser::ConditionalExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleConditionalExpression;
}

void C_grammarParser::ConditionalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalExpression(this);
}

void C_grammarParser::ConditionalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalExpression(this);
}


antlrcpp::Any C_grammarParser::ConditionalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConditionalExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::conditionalExpression() {
  ConditionalExpressionContext *_localctx = _tracker.createInstance<ConditionalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 30, C_grammarParser::RuleConditionalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(235);
    logicalOrExpression();
    setState(241);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Question) {
      setState(236);
      match(C_grammarParser::Question);
      setState(237);
      expression();
      setState(238);
      match(C_grammarParser::Colon);
      setState(239);
      conditionalExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentExpressionContext ------------------------------------------------------------------

C_grammarParser::AssignmentExpressionContext::AssignmentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::AssignmentExpressionContext::conditionalExpression() {
  return getRuleContext<C_grammarParser::ConditionalExpressionContext>(0);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::AssignmentExpressionContext::unaryExpression() {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(0);
}

C_grammarParser::AssignmentOperatorContext* C_grammarParser::AssignmentExpressionContext::assignmentOperator() {
  return getRuleContext<C_grammarParser::AssignmentOperatorContext>(0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::AssignmentExpressionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::AssignmentExpressionContext::DigitSequence() {
  return getToken(C_grammarParser::DigitSequence, 0);
}


size_t C_grammarParser::AssignmentExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleAssignmentExpression;
}

void C_grammarParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}

void C_grammarParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}


antlrcpp::Any C_grammarParser::AssignmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAssignmentExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::assignmentExpression() {
  AssignmentExpressionContext *_localctx = _tracker.createInstance<AssignmentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, C_grammarParser::RuleAssignmentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(249);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(243);
      conditionalExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(244);
      unaryExpression();
      setState(245);
      assignmentOperator();
      setState(246);
      assignmentExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(248);
      match(C_grammarParser::DigitSequence);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentOperatorContext ------------------------------------------------------------------

C_grammarParser::AssignmentOperatorContext::AssignmentOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::StarAssign() {
  return getToken(C_grammarParser::StarAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::DivAssign() {
  return getToken(C_grammarParser::DivAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::ModAssign() {
  return getToken(C_grammarParser::ModAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::PlusAssign() {
  return getToken(C_grammarParser::PlusAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::MinusAssign() {
  return getToken(C_grammarParser::MinusAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::LeftShiftAssign() {
  return getToken(C_grammarParser::LeftShiftAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::RightShiftAssign() {
  return getToken(C_grammarParser::RightShiftAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::AndAssign() {
  return getToken(C_grammarParser::AndAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::XorAssign() {
  return getToken(C_grammarParser::XorAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::OrAssign() {
  return getToken(C_grammarParser::OrAssign, 0);
}


size_t C_grammarParser::AssignmentOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleAssignmentOperator;
}

void C_grammarParser::AssignmentOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentOperator(this);
}

void C_grammarParser::AssignmentOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentOperator(this);
}


antlrcpp::Any C_grammarParser::AssignmentOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAssignmentOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AssignmentOperatorContext* C_grammarParser::assignmentOperator() {
  AssignmentOperatorContext *_localctx = _tracker.createInstance<AssignmentOperatorContext>(_ctx, getState());
  enterRule(_localctx, 34, C_grammarParser::RuleAssignmentOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(251);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Assign)
      | (1ULL << C_grammarParser::StarAssign)
      | (1ULL << C_grammarParser::DivAssign)
      | (1ULL << C_grammarParser::ModAssign)
      | (1ULL << C_grammarParser::PlusAssign)
      | (1ULL << C_grammarParser::MinusAssign)
      | (1ULL << C_grammarParser::LeftShiftAssign)
      | (1ULL << C_grammarParser::RightShiftAssign)
      | (1ULL << C_grammarParser::AndAssign)
      | (1ULL << C_grammarParser::XorAssign)
      | (1ULL << C_grammarParser::OrAssign))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

C_grammarParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AssignmentExpressionContext *> C_grammarParser::ExpressionContext::assignmentExpression() {
  return getRuleContexts<C_grammarParser::AssignmentExpressionContext>();
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ExpressionContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ExpressionContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleExpression;
}

void C_grammarParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void C_grammarParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


antlrcpp::Any C_grammarParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExpressionContext* C_grammarParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 36, C_grammarParser::RuleExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(253);
    assignmentExpression();
    setState(258);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(254);
      match(C_grammarParser::Comma);
      setState(255);
      assignmentExpression();
      setState(260);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantExpressionContext ------------------------------------------------------------------

C_grammarParser::ConstantExpressionContext::ConstantExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::ConstantExpressionContext::conditionalExpression() {
  return getRuleContext<C_grammarParser::ConditionalExpressionContext>(0);
}


size_t C_grammarParser::ConstantExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleConstantExpression;
}

void C_grammarParser::ConstantExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstantExpression(this);
}

void C_grammarParser::ConstantExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstantExpression(this);
}


antlrcpp::Any C_grammarParser::ConstantExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConstantExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::constantExpression() {
  ConstantExpressionContext *_localctx = _tracker.createInstance<ConstantExpressionContext>(_ctx, getState());
  enterRule(_localctx, 38, C_grammarParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(261);
    conditionalExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

C_grammarParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclarationSpecifiersContext* C_grammarParser::DeclarationContext::declarationSpecifiers() {
  return getRuleContext<C_grammarParser::DeclarationSpecifiersContext>(0);
}

tree::TerminalNode* C_grammarParser::DeclarationContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

C_grammarParser::InitDeclaratorListContext* C_grammarParser::DeclarationContext::initDeclaratorList() {
  return getRuleContext<C_grammarParser::InitDeclaratorListContext>(0);
}


size_t C_grammarParser::DeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclaration;
}

void C_grammarParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void C_grammarParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


antlrcpp::Any C_grammarParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclarationContext* C_grammarParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 40, C_grammarParser::RuleDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(263);
    declarationSpecifiers();
    setState(265);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftParen

    || _la == C_grammarParser::Identifier) {
      setState(264);
      initDeclaratorList();
    }
    setState(267);
    match(C_grammarParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationSpecifiersContext ------------------------------------------------------------------

C_grammarParser::DeclarationSpecifiersContext::DeclarationSpecifiersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::DeclarationSpecifierContext *> C_grammarParser::DeclarationSpecifiersContext::declarationSpecifier() {
  return getRuleContexts<C_grammarParser::DeclarationSpecifierContext>();
}

C_grammarParser::DeclarationSpecifierContext* C_grammarParser::DeclarationSpecifiersContext::declarationSpecifier(size_t i) {
  return getRuleContext<C_grammarParser::DeclarationSpecifierContext>(i);
}


size_t C_grammarParser::DeclarationSpecifiersContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclarationSpecifiers;
}

void C_grammarParser::DeclarationSpecifiersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarationSpecifiers(this);
}

void C_grammarParser::DeclarationSpecifiersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarationSpecifiers(this);
}


antlrcpp::Any C_grammarParser::DeclarationSpecifiersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclarationSpecifiers(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclarationSpecifiersContext* C_grammarParser::declarationSpecifiers() {
  DeclarationSpecifiersContext *_localctx = _tracker.createInstance<DeclarationSpecifiersContext>(_ctx, getState());
  enterRule(_localctx, 42, C_grammarParser::RuleDeclarationSpecifiers);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(270); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(269);
              declarationSpecifier();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(272); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationSpecifierContext ------------------------------------------------------------------

C_grammarParser::DeclarationSpecifierContext::DeclarationSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StorageClassSpecifierContext* C_grammarParser::DeclarationSpecifierContext::storageClassSpecifier() {
  return getRuleContext<C_grammarParser::StorageClassSpecifierContext>(0);
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::DeclarationSpecifierContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

C_grammarParser::TypeQualifierContext* C_grammarParser::DeclarationSpecifierContext::typeQualifier() {
  return getRuleContext<C_grammarParser::TypeQualifierContext>(0);
}


size_t C_grammarParser::DeclarationSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclarationSpecifier;
}

void C_grammarParser::DeclarationSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarationSpecifier(this);
}

void C_grammarParser::DeclarationSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarationSpecifier(this);
}


antlrcpp::Any C_grammarParser::DeclarationSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclarationSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclarationSpecifierContext* C_grammarParser::declarationSpecifier() {
  DeclarationSpecifierContext *_localctx = _tracker.createInstance<DeclarationSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 44, C_grammarParser::RuleDeclarationSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(277);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::T__0:
      case C_grammarParser::T__1:
      case C_grammarParser::T__2:
      case C_grammarParser::T__3:
      case C_grammarParser::Typedef: {
        enterOuterAlt(_localctx, 1);
        setState(274);
        storageClassSpecifier();
        break;
      }

      case C_grammarParser::Char:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(275);
        typeSpecifier();
        break;
      }

      case C_grammarParser::T__4:
      case C_grammarParser::Const:
      case C_grammarParser::Volatile: {
        enterOuterAlt(_localctx, 3);
        setState(276);
        typeQualifier();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitDeclaratorListContext ------------------------------------------------------------------

C_grammarParser::InitDeclaratorListContext::InitDeclaratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::InitDeclaratorContext *> C_grammarParser::InitDeclaratorListContext::initDeclarator() {
  return getRuleContexts<C_grammarParser::InitDeclaratorContext>();
}

C_grammarParser::InitDeclaratorContext* C_grammarParser::InitDeclaratorListContext::initDeclarator(size_t i) {
  return getRuleContext<C_grammarParser::InitDeclaratorContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::InitDeclaratorListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::InitDeclaratorListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::InitDeclaratorListContext::getRuleIndex() const {
  return C_grammarParser::RuleInitDeclaratorList;
}

void C_grammarParser::InitDeclaratorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitDeclaratorList(this);
}

void C_grammarParser::InitDeclaratorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitDeclaratorList(this);
}


antlrcpp::Any C_grammarParser::InitDeclaratorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitDeclaratorList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitDeclaratorListContext* C_grammarParser::initDeclaratorList() {
  InitDeclaratorListContext *_localctx = _tracker.createInstance<InitDeclaratorListContext>(_ctx, getState());
  enterRule(_localctx, 46, C_grammarParser::RuleInitDeclaratorList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(279);
    initDeclarator();
    setState(284);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(280);
      match(C_grammarParser::Comma);
      setState(281);
      initDeclarator();
      setState(286);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitDeclaratorContext ------------------------------------------------------------------

C_grammarParser::InitDeclaratorContext::InitDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclaratorContext* C_grammarParser::InitDeclaratorContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::InitDeclaratorContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}

C_grammarParser::InitializerContext* C_grammarParser::InitDeclaratorContext::initializer() {
  return getRuleContext<C_grammarParser::InitializerContext>(0);
}


size_t C_grammarParser::InitDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleInitDeclarator;
}

void C_grammarParser::InitDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitDeclarator(this);
}

void C_grammarParser::InitDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitDeclarator(this);
}


antlrcpp::Any C_grammarParser::InitDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitDeclaratorContext* C_grammarParser::initDeclarator() {
  InitDeclaratorContext *_localctx = _tracker.createInstance<InitDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 48, C_grammarParser::RuleInitDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(287);
    declarator();
    setState(290);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Assign) {
      setState(288);
      match(C_grammarParser::Assign);
      setState(289);
      initializer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StorageClassSpecifierContext ------------------------------------------------------------------

C_grammarParser::StorageClassSpecifierContext::StorageClassSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::StorageClassSpecifierContext::Typedef() {
  return getToken(C_grammarParser::Typedef, 0);
}


size_t C_grammarParser::StorageClassSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleStorageClassSpecifier;
}

void C_grammarParser::StorageClassSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStorageClassSpecifier(this);
}

void C_grammarParser::StorageClassSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStorageClassSpecifier(this);
}


antlrcpp::Any C_grammarParser::StorageClassSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStorageClassSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StorageClassSpecifierContext* C_grammarParser::storageClassSpecifier() {
  StorageClassSpecifierContext *_localctx = _tracker.createInstance<StorageClassSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 50, C_grammarParser::RuleStorageClassSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::Typedef))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSpecifierContext ------------------------------------------------------------------

C_grammarParser::TypeSpecifierContext::TypeSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Void() {
  return getToken(C_grammarParser::Void, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Char() {
  return getToken(C_grammarParser::Char, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Short() {
  return getToken(C_grammarParser::Short, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Int() {
  return getToken(C_grammarParser::Int, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Long() {
  return getToken(C_grammarParser::Long, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Float() {
  return getToken(C_grammarParser::Float, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Signed() {
  return getToken(C_grammarParser::Signed, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Unsigned() {
  return getToken(C_grammarParser::Unsigned, 0);
}

C_grammarParser::TypedefNameContext* C_grammarParser::TypeSpecifierContext::typedefName() {
  return getRuleContext<C_grammarParser::TypedefNameContext>(0);
}


size_t C_grammarParser::TypeSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleTypeSpecifier;
}

void C_grammarParser::TypeSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSpecifier(this);
}

void C_grammarParser::TypeSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSpecifier(this);
}


antlrcpp::Any C_grammarParser::TypeSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypeSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::typeSpecifier() {
  TypeSpecifierContext *_localctx = _tracker.createInstance<TypeSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 52, C_grammarParser::RuleTypeSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(296);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Char:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void: {
        enterOuterAlt(_localctx, 1);
        setState(294);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
          | (1ULL << C_grammarParser::Float)
          | (1ULL << C_grammarParser::Int)
          | (1ULL << C_grammarParser::Long)
          | (1ULL << C_grammarParser::Short)
          | (1ULL << C_grammarParser::Signed)
          | (1ULL << C_grammarParser::Unsigned)
          | (1ULL << C_grammarParser::Void))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(295);
        typedefName();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SpecifierQualifierListContext ------------------------------------------------------------------

C_grammarParser::SpecifierQualifierListContext::SpecifierQualifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::SpecifierQualifierListContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

C_grammarParser::TypeQualifierContext* C_grammarParser::SpecifierQualifierListContext::typeQualifier() {
  return getRuleContext<C_grammarParser::TypeQualifierContext>(0);
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::SpecifierQualifierListContext::specifierQualifierList() {
  return getRuleContext<C_grammarParser::SpecifierQualifierListContext>(0);
}


size_t C_grammarParser::SpecifierQualifierListContext::getRuleIndex() const {
  return C_grammarParser::RuleSpecifierQualifierList;
}

void C_grammarParser::SpecifierQualifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSpecifierQualifierList(this);
}

void C_grammarParser::SpecifierQualifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSpecifierQualifierList(this);
}


antlrcpp::Any C_grammarParser::SpecifierQualifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitSpecifierQualifierList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::specifierQualifierList() {
  SpecifierQualifierListContext *_localctx = _tracker.createInstance<SpecifierQualifierListContext>(_ctx, getState());
  enterRule(_localctx, 54, C_grammarParser::RuleSpecifierQualifierList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(300);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Char:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::Identifier: {
        setState(298);
        typeSpecifier();
        break;
      }

      case C_grammarParser::T__4:
      case C_grammarParser::Const:
      case C_grammarParser::Volatile: {
        setState(299);
        typeQualifier();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(303);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile))) != 0) || _la == C_grammarParser::Identifier) {
      setState(302);
      specifierQualifierList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeQualifierContext ------------------------------------------------------------------

C_grammarParser::TypeQualifierContext::TypeQualifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::TypeQualifierContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}

tree::TerminalNode* C_grammarParser::TypeQualifierContext::Volatile() {
  return getToken(C_grammarParser::Volatile, 0);
}


size_t C_grammarParser::TypeQualifierContext::getRuleIndex() const {
  return C_grammarParser::RuleTypeQualifier;
}

void C_grammarParser::TypeQualifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeQualifier(this);
}

void C_grammarParser::TypeQualifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeQualifier(this);
}


antlrcpp::Any C_grammarParser::TypeQualifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypeQualifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypeQualifierContext* C_grammarParser::typeQualifier() {
  TypeQualifierContext *_localctx = _tracker.createInstance<TypeQualifierContext>(_ctx, getState());
  enterRule(_localctx, 56, C_grammarParser::RuleTypeQualifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(305);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Volatile))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclaratorContext ------------------------------------------------------------------

C_grammarParser::DeclaratorContext::DeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::DeclaratorContext::directDeclarator() {
  return getRuleContext<C_grammarParser::DirectDeclaratorContext>(0);
}


size_t C_grammarParser::DeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclarator;
}

void C_grammarParser::DeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarator(this);
}

void C_grammarParser::DeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarator(this);
}


antlrcpp::Any C_grammarParser::DeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclaratorContext* C_grammarParser::declarator() {
  DeclaratorContext *_localctx = _tracker.createInstance<DeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 58, C_grammarParser::RuleDeclarator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(307);
    directDeclarator(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DirectDeclaratorContext ------------------------------------------------------------------

C_grammarParser::DirectDeclaratorContext::DirectDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::DeclaratorContext* C_grammarParser::DirectDeclaratorContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::DigitSequence() {
  return getToken(C_grammarParser::DigitSequence, 0);
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::DirectDeclaratorContext::directDeclarator() {
  return getRuleContext<C_grammarParser::DirectDeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::LeftBracket() {
  return getToken(C_grammarParser::LeftBracket, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::RightBracket() {
  return getToken(C_grammarParser::RightBracket, 0);
}

C_grammarParser::TypeQualifierListContext* C_grammarParser::DirectDeclaratorContext::typeQualifierList() {
  return getRuleContext<C_grammarParser::TypeQualifierListContext>(0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::DirectDeclaratorContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::Star() {
  return getToken(C_grammarParser::Star, 0);
}

C_grammarParser::ParameterTypeListContext* C_grammarParser::DirectDeclaratorContext::parameterTypeList() {
  return getRuleContext<C_grammarParser::ParameterTypeListContext>(0);
}

C_grammarParser::IdentifierListContext* C_grammarParser::DirectDeclaratorContext::identifierList() {
  return getRuleContext<C_grammarParser::IdentifierListContext>(0);
}


size_t C_grammarParser::DirectDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleDirectDeclarator;
}

void C_grammarParser::DirectDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirectDeclarator(this);
}

void C_grammarParser::DirectDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirectDeclarator(this);
}


antlrcpp::Any C_grammarParser::DirectDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDirectDeclarator(this);
  else
    return visitor->visitChildren(this);
}


C_grammarParser::DirectDeclaratorContext* C_grammarParser::directDeclarator() {
   return directDeclarator(0);
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::directDeclarator(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C_grammarParser::DirectDeclaratorContext *_localctx = _tracker.createInstance<DirectDeclaratorContext>(_ctx, parentState);
  C_grammarParser::DirectDeclaratorContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, C_grammarParser::RuleDirectDeclarator, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(318);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      setState(310);
      match(C_grammarParser::Identifier);
      break;
    }

    case 2: {
      setState(311);
      match(C_grammarParser::LeftParen);
      setState(312);
      declarator();
      setState(313);
      match(C_grammarParser::RightParen);
      break;
    }

    case 3: {
      setState(315);
      match(C_grammarParser::Identifier);
      setState(316);
      match(C_grammarParser::Colon);
      setState(317);
      match(C_grammarParser::DigitSequence);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(365);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(363);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(320);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(321);
          match(C_grammarParser::LeftBracket);
          setState(323);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::T__4)
            | (1ULL << C_grammarParser::Const)
            | (1ULL << C_grammarParser::Volatile))) != 0)) {
            setState(322);
            typeQualifierList();
          }
          setState(326);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (((((_la - 23) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 23)) & ((1ULL << (C_grammarParser::LeftParen - 23))
            | (1ULL << (C_grammarParser::PlusPlus - 23))
            | (1ULL << (C_grammarParser::Minus - 23))
            | (1ULL << (C_grammarParser::MinusMinus - 23))
            | (1ULL << (C_grammarParser::Not - 23))
            | (1ULL << (C_grammarParser::Tilde - 23))
            | (1ULL << (C_grammarParser::Identifier - 23))
            | (1ULL << (C_grammarParser::IntegerConstant - 23))
            | (1ULL << (C_grammarParser::FloatingConstant - 23))
            | (1ULL << (C_grammarParser::DigitSequence - 23))
            | (1ULL << (C_grammarParser::CharacterConstant - 23))
            | (1ULL << (C_grammarParser::StringLiteral - 23)))) != 0)) {
            setState(325);
            assignmentExpression();
          }
          setState(328);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(329);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(330);
          match(C_grammarParser::LeftBracket);
          setState(331);
          match(C_grammarParser::T__1);
          setState(333);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::T__4)
            | (1ULL << C_grammarParser::Const)
            | (1ULL << C_grammarParser::Volatile))) != 0)) {
            setState(332);
            typeQualifierList();
          }
          setState(335);
          assignmentExpression();
          setState(336);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(338);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(339);
          match(C_grammarParser::LeftBracket);
          setState(340);
          typeQualifierList();
          setState(341);
          match(C_grammarParser::T__1);
          setState(342);
          assignmentExpression();
          setState(343);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(345);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(346);
          match(C_grammarParser::LeftBracket);
          setState(348);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::T__4)
            | (1ULL << C_grammarParser::Const)
            | (1ULL << C_grammarParser::Volatile))) != 0)) {
            setState(347);
            typeQualifierList();
          }
          setState(350);
          match(C_grammarParser::Star);
          setState(351);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(352);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(353);
          match(C_grammarParser::LeftParen);
          setState(354);
          parameterTypeList();
          setState(355);
          match(C_grammarParser::RightParen);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(357);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(358);
          match(C_grammarParser::LeftParen);
          setState(360);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == C_grammarParser::Identifier) {
            setState(359);
            identifierList();
          }
          setState(362);
          match(C_grammarParser::RightParen);
          break;
        }

        default:
          break;
        } 
      }
      setState(367);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NestedParenthesesBlockContext ------------------------------------------------------------------

C_grammarParser::NestedParenthesesBlockContext::NestedParenthesesBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> C_grammarParser::NestedParenthesesBlockContext::LeftParen() {
  return getTokens(C_grammarParser::LeftParen);
}

tree::TerminalNode* C_grammarParser::NestedParenthesesBlockContext::LeftParen(size_t i) {
  return getToken(C_grammarParser::LeftParen, i);
}

std::vector<C_grammarParser::NestedParenthesesBlockContext *> C_grammarParser::NestedParenthesesBlockContext::nestedParenthesesBlock() {
  return getRuleContexts<C_grammarParser::NestedParenthesesBlockContext>();
}

C_grammarParser::NestedParenthesesBlockContext* C_grammarParser::NestedParenthesesBlockContext::nestedParenthesesBlock(size_t i) {
  return getRuleContext<C_grammarParser::NestedParenthesesBlockContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::NestedParenthesesBlockContext::RightParen() {
  return getTokens(C_grammarParser::RightParen);
}

tree::TerminalNode* C_grammarParser::NestedParenthesesBlockContext::RightParen(size_t i) {
  return getToken(C_grammarParser::RightParen, i);
}


size_t C_grammarParser::NestedParenthesesBlockContext::getRuleIndex() const {
  return C_grammarParser::RuleNestedParenthesesBlock;
}

void C_grammarParser::NestedParenthesesBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNestedParenthesesBlock(this);
}

void C_grammarParser::NestedParenthesesBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNestedParenthesesBlock(this);
}


antlrcpp::Any C_grammarParser::NestedParenthesesBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitNestedParenthesesBlock(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::NestedParenthesesBlockContext* C_grammarParser::nestedParenthesesBlock() {
  NestedParenthesesBlockContext *_localctx = _tracker.createInstance<NestedParenthesesBlockContext>(_ctx, getState());
  enterRule(_localctx, 62, C_grammarParser::RuleNestedParenthesesBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(375);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Case)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Else)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::While)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::LeftBracket)
      | (1ULL << C_grammarParser::RightBracket)
      | (1ULL << C_grammarParser::LeftBrace)
      | (1ULL << C_grammarParser::RightBrace)
      | (1ULL << C_grammarParser::Less)
      | (1ULL << C_grammarParser::LessEqual)
      | (1ULL << C_grammarParser::Greater)
      | (1ULL << C_grammarParser::GreaterEqual)
      | (1ULL << C_grammarParser::LeftShift)
      | (1ULL << C_grammarParser::RightShift)
      | (1ULL << C_grammarParser::Plus)
      | (1ULL << C_grammarParser::PlusPlus)
      | (1ULL << C_grammarParser::Minus)
      | (1ULL << C_grammarParser::MinusMinus)
      | (1ULL << C_grammarParser::Star)
      | (1ULL << C_grammarParser::Div)
      | (1ULL << C_grammarParser::Mod)
      | (1ULL << C_grammarParser::And)
      | (1ULL << C_grammarParser::Or)
      | (1ULL << C_grammarParser::AndAnd)
      | (1ULL << C_grammarParser::OrOr)
      | (1ULL << C_grammarParser::Caret)
      | (1ULL << C_grammarParser::Not)
      | (1ULL << C_grammarParser::Tilde)
      | (1ULL << C_grammarParser::Question)
      | (1ULL << C_grammarParser::Colon)
      | (1ULL << C_grammarParser::Semi)
      | (1ULL << C_grammarParser::Comma)
      | (1ULL << C_grammarParser::Assign)
      | (1ULL << C_grammarParser::StarAssign)
      | (1ULL << C_grammarParser::DivAssign)
      | (1ULL << C_grammarParser::ModAssign)
      | (1ULL << C_grammarParser::PlusAssign)
      | (1ULL << C_grammarParser::MinusAssign)
      | (1ULL << C_grammarParser::LeftShiftAssign)
      | (1ULL << C_grammarParser::RightShiftAssign)
      | (1ULL << C_grammarParser::AndAssign)
      | (1ULL << C_grammarParser::XorAssign)
      | (1ULL << C_grammarParser::OrAssign))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Equal - 64))
      | (1ULL << (C_grammarParser::NotEqual - 64))
      | (1ULL << (C_grammarParser::Arrow - 64))
      | (1ULL << (C_grammarParser::Dot - 64))
      | (1ULL << (C_grammarParser::Ellipsis - 64))
      | (1ULL << (C_grammarParser::Identifier - 64))
      | (1ULL << (C_grammarParser::IntegerConstant - 64))
      | (1ULL << (C_grammarParser::FloatingConstant - 64))
      | (1ULL << (C_grammarParser::DigitSequence - 64))
      | (1ULL << (C_grammarParser::CharacterConstant - 64))
      | (1ULL << (C_grammarParser::StringLiteral - 64))
      | (1ULL << (C_grammarParser::ComplexDefine - 64))
      | (1ULL << (C_grammarParser::IncludeDirective - 64))
      | (1ULL << (C_grammarParser::AsmBlock - 64))
      | (1ULL << (C_grammarParser::LineAfterPreprocessing - 64))
      | (1ULL << (C_grammarParser::LineDirective - 64))
      | (1ULL << (C_grammarParser::PragmaDirective - 64))
      | (1ULL << (C_grammarParser::Whitespace - 64))
      | (1ULL << (C_grammarParser::Newline - 64))
      | (1ULL << (C_grammarParser::BlockComment - 64))
      | (1ULL << (C_grammarParser::LineComment - 64)))) != 0)) {
      setState(373);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case C_grammarParser::T__0:
        case C_grammarParser::T__1:
        case C_grammarParser::T__2:
        case C_grammarParser::T__3:
        case C_grammarParser::T__4:
        case C_grammarParser::Case:
        case C_grammarParser::Char:
        case C_grammarParser::Const:
        case C_grammarParser::Else:
        case C_grammarParser::Float:
        case C_grammarParser::For:
        case C_grammarParser::If:
        case C_grammarParser::Int:
        case C_grammarParser::Long:
        case C_grammarParser::Return:
        case C_grammarParser::Short:
        case C_grammarParser::Signed:
        case C_grammarParser::Typedef:
        case C_grammarParser::Unsigned:
        case C_grammarParser::Void:
        case C_grammarParser::Volatile:
        case C_grammarParser::While:
        case C_grammarParser::LeftBracket:
        case C_grammarParser::RightBracket:
        case C_grammarParser::LeftBrace:
        case C_grammarParser::RightBrace:
        case C_grammarParser::Less:
        case C_grammarParser::LessEqual:
        case C_grammarParser::Greater:
        case C_grammarParser::GreaterEqual:
        case C_grammarParser::LeftShift:
        case C_grammarParser::RightShift:
        case C_grammarParser::Plus:
        case C_grammarParser::PlusPlus:
        case C_grammarParser::Minus:
        case C_grammarParser::MinusMinus:
        case C_grammarParser::Star:
        case C_grammarParser::Div:
        case C_grammarParser::Mod:
        case C_grammarParser::And:
        case C_grammarParser::Or:
        case C_grammarParser::AndAnd:
        case C_grammarParser::OrOr:
        case C_grammarParser::Caret:
        case C_grammarParser::Not:
        case C_grammarParser::Tilde:
        case C_grammarParser::Question:
        case C_grammarParser::Colon:
        case C_grammarParser::Semi:
        case C_grammarParser::Comma:
        case C_grammarParser::Assign:
        case C_grammarParser::StarAssign:
        case C_grammarParser::DivAssign:
        case C_grammarParser::ModAssign:
        case C_grammarParser::PlusAssign:
        case C_grammarParser::MinusAssign:
        case C_grammarParser::LeftShiftAssign:
        case C_grammarParser::RightShiftAssign:
        case C_grammarParser::AndAssign:
        case C_grammarParser::XorAssign:
        case C_grammarParser::OrAssign:
        case C_grammarParser::Equal:
        case C_grammarParser::NotEqual:
        case C_grammarParser::Arrow:
        case C_grammarParser::Dot:
        case C_grammarParser::Ellipsis:
        case C_grammarParser::Identifier:
        case C_grammarParser::IntegerConstant:
        case C_grammarParser::FloatingConstant:
        case C_grammarParser::DigitSequence:
        case C_grammarParser::CharacterConstant:
        case C_grammarParser::StringLiteral:
        case C_grammarParser::ComplexDefine:
        case C_grammarParser::IncludeDirective:
        case C_grammarParser::AsmBlock:
        case C_grammarParser::LineAfterPreprocessing:
        case C_grammarParser::LineDirective:
        case C_grammarParser::PragmaDirective:
        case C_grammarParser::Whitespace:
        case C_grammarParser::Newline:
        case C_grammarParser::BlockComment:
        case C_grammarParser::LineComment: {
          setState(368);
          _la = _input->LA(1);
          if (_la == 0 || _la == Token::EOF || (_la == C_grammarParser::LeftParen

          || _la == C_grammarParser::RightParen)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        case C_grammarParser::LeftParen: {
          setState(369);
          match(C_grammarParser::LeftParen);
          setState(370);
          nestedParenthesesBlock();
          setState(371);
          match(C_grammarParser::RightParen);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(377);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeQualifierListContext ------------------------------------------------------------------

C_grammarParser::TypeQualifierListContext::TypeQualifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::TypeQualifierContext *> C_grammarParser::TypeQualifierListContext::typeQualifier() {
  return getRuleContexts<C_grammarParser::TypeQualifierContext>();
}

C_grammarParser::TypeQualifierContext* C_grammarParser::TypeQualifierListContext::typeQualifier(size_t i) {
  return getRuleContext<C_grammarParser::TypeQualifierContext>(i);
}


size_t C_grammarParser::TypeQualifierListContext::getRuleIndex() const {
  return C_grammarParser::RuleTypeQualifierList;
}

void C_grammarParser::TypeQualifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeQualifierList(this);
}

void C_grammarParser::TypeQualifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeQualifierList(this);
}


antlrcpp::Any C_grammarParser::TypeQualifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypeQualifierList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypeQualifierListContext* C_grammarParser::typeQualifierList() {
  TypeQualifierListContext *_localctx = _tracker.createInstance<TypeQualifierListContext>(_ctx, getState());
  enterRule(_localctx, 64, C_grammarParser::RuleTypeQualifierList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(379); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(378);
      typeQualifier();
      setState(381); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Volatile))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterTypeListContext ------------------------------------------------------------------

C_grammarParser::ParameterTypeListContext::ParameterTypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ParameterListContext* C_grammarParser::ParameterTypeListContext::parameterList() {
  return getRuleContext<C_grammarParser::ParameterListContext>(0);
}

tree::TerminalNode* C_grammarParser::ParameterTypeListContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}

tree::TerminalNode* C_grammarParser::ParameterTypeListContext::Ellipsis() {
  return getToken(C_grammarParser::Ellipsis, 0);
}


size_t C_grammarParser::ParameterTypeListContext::getRuleIndex() const {
  return C_grammarParser::RuleParameterTypeList;
}

void C_grammarParser::ParameterTypeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterTypeList(this);
}

void C_grammarParser::ParameterTypeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterTypeList(this);
}


antlrcpp::Any C_grammarParser::ParameterTypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitParameterTypeList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ParameterTypeListContext* C_grammarParser::parameterTypeList() {
  ParameterTypeListContext *_localctx = _tracker.createInstance<ParameterTypeListContext>(_ctx, getState());
  enterRule(_localctx, 66, C_grammarParser::RuleParameterTypeList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(383);
    parameterList();
    setState(386);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Comma) {
      setState(384);
      match(C_grammarParser::Comma);
      setState(385);
      match(C_grammarParser::Ellipsis);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

C_grammarParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ParameterDeclarationContext *> C_grammarParser::ParameterListContext::parameterDeclaration() {
  return getRuleContexts<C_grammarParser::ParameterDeclarationContext>();
}

C_grammarParser::ParameterDeclarationContext* C_grammarParser::ParameterListContext::parameterDeclaration(size_t i) {
  return getRuleContext<C_grammarParser::ParameterDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ParameterListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ParameterListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ParameterListContext::getRuleIndex() const {
  return C_grammarParser::RuleParameterList;
}

void C_grammarParser::ParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterList(this);
}

void C_grammarParser::ParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterList(this);
}


antlrcpp::Any C_grammarParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ParameterListContext* C_grammarParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 68, C_grammarParser::RuleParameterList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(388);
    parameterDeclaration();
    setState(393);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(389);
        match(C_grammarParser::Comma);
        setState(390);
        parameterDeclaration(); 
      }
      setState(395);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterDeclarationContext ------------------------------------------------------------------

C_grammarParser::ParameterDeclarationContext::ParameterDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclarationSpecifiersContext* C_grammarParser::ParameterDeclarationContext::declarationSpecifiers() {
  return getRuleContext<C_grammarParser::DeclarationSpecifiersContext>(0);
}

C_grammarParser::DeclaratorContext* C_grammarParser::ParameterDeclarationContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}


size_t C_grammarParser::ParameterDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleParameterDeclaration;
}

void C_grammarParser::ParameterDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterDeclaration(this);
}

void C_grammarParser::ParameterDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterDeclaration(this);
}


antlrcpp::Any C_grammarParser::ParameterDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitParameterDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ParameterDeclarationContext* C_grammarParser::parameterDeclaration() {
  ParameterDeclarationContext *_localctx = _tracker.createInstance<ParameterDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 70, C_grammarParser::RuleParameterDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(396);
    declarationSpecifiers();
    setState(397);
    declarator();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierListContext ------------------------------------------------------------------

C_grammarParser::IdentifierListContext::IdentifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> C_grammarParser::IdentifierListContext::Identifier() {
  return getTokens(C_grammarParser::Identifier);
}

tree::TerminalNode* C_grammarParser::IdentifierListContext::Identifier(size_t i) {
  return getToken(C_grammarParser::Identifier, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::IdentifierListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::IdentifierListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::IdentifierListContext::getRuleIndex() const {
  return C_grammarParser::RuleIdentifierList;
}

void C_grammarParser::IdentifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierList(this);
}

void C_grammarParser::IdentifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierList(this);
}


antlrcpp::Any C_grammarParser::IdentifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitIdentifierList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::IdentifierListContext* C_grammarParser::identifierList() {
  IdentifierListContext *_localctx = _tracker.createInstance<IdentifierListContext>(_ctx, getState());
  enterRule(_localctx, 72, C_grammarParser::RuleIdentifierList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(399);
    match(C_grammarParser::Identifier);
    setState(404);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(400);
      match(C_grammarParser::Comma);
      setState(401);
      match(C_grammarParser::Identifier);
      setState(406);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameContext ------------------------------------------------------------------

C_grammarParser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::TypeNameContext::specifierQualifierList() {
  return getRuleContext<C_grammarParser::SpecifierQualifierListContext>(0);
}


size_t C_grammarParser::TypeNameContext::getRuleIndex() const {
  return C_grammarParser::RuleTypeName;
}

void C_grammarParser::TypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeName(this);
}

void C_grammarParser::TypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeName(this);
}


antlrcpp::Any C_grammarParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypeNameContext* C_grammarParser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 74, C_grammarParser::RuleTypeName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(408);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile))) != 0) || _la == C_grammarParser::Identifier) {
      setState(407);
      specifierQualifierList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypedefNameContext ------------------------------------------------------------------

C_grammarParser::TypedefNameContext::TypedefNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::TypedefNameContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::TypedefNameContext::getRuleIndex() const {
  return C_grammarParser::RuleTypedefName;
}

void C_grammarParser::TypedefNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypedefName(this);
}

void C_grammarParser::TypedefNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypedefName(this);
}


antlrcpp::Any C_grammarParser::TypedefNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypedefName(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypedefNameContext* C_grammarParser::typedefName() {
  TypedefNameContext *_localctx = _tracker.createInstance<TypedefNameContext>(_ctx, getState());
  enterRule(_localctx, 76, C_grammarParser::RuleTypedefName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(410);
    match(C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerContext ------------------------------------------------------------------

C_grammarParser::InitializerContext::InitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::InitializerContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::InitializerContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

C_grammarParser::InitializerListContext* C_grammarParser::InitializerContext::initializerList() {
  return getRuleContext<C_grammarParser::InitializerListContext>(0);
}

tree::TerminalNode* C_grammarParser::InitializerContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

tree::TerminalNode* C_grammarParser::InitializerContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}


size_t C_grammarParser::InitializerContext::getRuleIndex() const {
  return C_grammarParser::RuleInitializer;
}

void C_grammarParser::InitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializer(this);
}

void C_grammarParser::InitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializer(this);
}


antlrcpp::Any C_grammarParser::InitializerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitializer(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitializerContext* C_grammarParser::initializer() {
  InitializerContext *_localctx = _tracker.createInstance<InitializerContext>(_ctx, getState());
  enterRule(_localctx, 78, C_grammarParser::RuleInitializer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(420);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(412);
        assignmentExpression();
        break;
      }

      case C_grammarParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(413);
        match(C_grammarParser::LeftBrace);
        setState(414);
        initializerList();
        setState(416);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::Comma) {
          setState(415);
          match(C_grammarParser::Comma);
        }
        setState(418);
        match(C_grammarParser::RightBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerListContext ------------------------------------------------------------------

C_grammarParser::InitializerListContext::InitializerListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::InitializerContext *> C_grammarParser::InitializerListContext::initializer() {
  return getRuleContexts<C_grammarParser::InitializerContext>();
}

C_grammarParser::InitializerContext* C_grammarParser::InitializerListContext::initializer(size_t i) {
  return getRuleContext<C_grammarParser::InitializerContext>(i);
}

std::vector<C_grammarParser::DesignationContext *> C_grammarParser::InitializerListContext::designation() {
  return getRuleContexts<C_grammarParser::DesignationContext>();
}

C_grammarParser::DesignationContext* C_grammarParser::InitializerListContext::designation(size_t i) {
  return getRuleContext<C_grammarParser::DesignationContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::InitializerListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::InitializerListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::InitializerListContext::getRuleIndex() const {
  return C_grammarParser::RuleInitializerList;
}

void C_grammarParser::InitializerListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializerList(this);
}

void C_grammarParser::InitializerListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializerList(this);
}


antlrcpp::Any C_grammarParser::InitializerListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitializerList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitializerListContext* C_grammarParser::initializerList() {
  InitializerListContext *_localctx = _tracker.createInstance<InitializerListContext>(_ctx, getState());
  enterRule(_localctx, 80, C_grammarParser::RuleInitializerList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(423);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftBracket

    || _la == C_grammarParser::Dot) {
      setState(422);
      designation();
    }
    setState(425);
    initializer();
    setState(433);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(426);
        match(C_grammarParser::Comma);
        setState(428);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::LeftBracket

        || _la == C_grammarParser::Dot) {
          setState(427);
          designation();
        }
        setState(430);
        initializer(); 
      }
      setState(435);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignationContext ------------------------------------------------------------------

C_grammarParser::DesignationContext::DesignationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DesignatorListContext* C_grammarParser::DesignationContext::designatorList() {
  return getRuleContext<C_grammarParser::DesignatorListContext>(0);
}

tree::TerminalNode* C_grammarParser::DesignationContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}


size_t C_grammarParser::DesignationContext::getRuleIndex() const {
  return C_grammarParser::RuleDesignation;
}

void C_grammarParser::DesignationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDesignation(this);
}

void C_grammarParser::DesignationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDesignation(this);
}


antlrcpp::Any C_grammarParser::DesignationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDesignation(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DesignationContext* C_grammarParser::designation() {
  DesignationContext *_localctx = _tracker.createInstance<DesignationContext>(_ctx, getState());
  enterRule(_localctx, 82, C_grammarParser::RuleDesignation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
    designatorList();
    setState(437);
    match(C_grammarParser::Assign);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignatorListContext ------------------------------------------------------------------

C_grammarParser::DesignatorListContext::DesignatorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::DesignatorContext *> C_grammarParser::DesignatorListContext::designator() {
  return getRuleContexts<C_grammarParser::DesignatorContext>();
}

C_grammarParser::DesignatorContext* C_grammarParser::DesignatorListContext::designator(size_t i) {
  return getRuleContext<C_grammarParser::DesignatorContext>(i);
}


size_t C_grammarParser::DesignatorListContext::getRuleIndex() const {
  return C_grammarParser::RuleDesignatorList;
}

void C_grammarParser::DesignatorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDesignatorList(this);
}

void C_grammarParser::DesignatorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDesignatorList(this);
}


antlrcpp::Any C_grammarParser::DesignatorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDesignatorList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DesignatorListContext* C_grammarParser::designatorList() {
  DesignatorListContext *_localctx = _tracker.createInstance<DesignatorListContext>(_ctx, getState());
  enterRule(_localctx, 84, C_grammarParser::RuleDesignatorList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(440); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(439);
      designator();
      setState(442); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == C_grammarParser::LeftBracket

    || _la == C_grammarParser::Dot);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignatorContext ------------------------------------------------------------------

C_grammarParser::DesignatorContext::DesignatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::DesignatorContext::LeftBracket() {
  return getToken(C_grammarParser::LeftBracket, 0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::DesignatorContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::DesignatorContext::RightBracket() {
  return getToken(C_grammarParser::RightBracket, 0);
}

tree::TerminalNode* C_grammarParser::DesignatorContext::Dot() {
  return getToken(C_grammarParser::Dot, 0);
}

tree::TerminalNode* C_grammarParser::DesignatorContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::DesignatorContext::getRuleIndex() const {
  return C_grammarParser::RuleDesignator;
}

void C_grammarParser::DesignatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDesignator(this);
}

void C_grammarParser::DesignatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDesignator(this);
}


antlrcpp::Any C_grammarParser::DesignatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDesignator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DesignatorContext* C_grammarParser::designator() {
  DesignatorContext *_localctx = _tracker.createInstance<DesignatorContext>(_ctx, getState());
  enterRule(_localctx, 86, C_grammarParser::RuleDesignator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(450);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBracket: {
        enterOuterAlt(_localctx, 1);
        setState(444);
        match(C_grammarParser::LeftBracket);
        setState(445);
        constantExpression();
        setState(446);
        match(C_grammarParser::RightBracket);
        break;
      }

      case C_grammarParser::Dot: {
        enterOuterAlt(_localctx, 2);
        setState(448);
        match(C_grammarParser::Dot);
        setState(449);
        match(C_grammarParser::Identifier);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

C_grammarParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::CompoundStatementContext* C_grammarParser::StatementContext::compoundStatement() {
  return getRuleContext<C_grammarParser::CompoundStatementContext>(0);
}

C_grammarParser::ExpressionStatementContext* C_grammarParser::StatementContext::expressionStatement() {
  return getRuleContext<C_grammarParser::ExpressionStatementContext>(0);
}

C_grammarParser::SelectionStatementContext* C_grammarParser::StatementContext::selectionStatement() {
  return getRuleContext<C_grammarParser::SelectionStatementContext>(0);
}

C_grammarParser::IterationStatementContext* C_grammarParser::StatementContext::iterationStatement() {
  return getRuleContext<C_grammarParser::IterationStatementContext>(0);
}

C_grammarParser::ReturnStatementContext* C_grammarParser::StatementContext::returnStatement() {
  return getRuleContext<C_grammarParser::ReturnStatementContext>(0);
}

tree::TerminalNode* C_grammarParser::StatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::StatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

tree::TerminalNode* C_grammarParser::StatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

std::vector<C_grammarParser::LogicalOrExpressionContext *> C_grammarParser::StatementContext::logicalOrExpression() {
  return getRuleContexts<C_grammarParser::LogicalOrExpressionContext>();
}

C_grammarParser::LogicalOrExpressionContext* C_grammarParser::StatementContext::logicalOrExpression(size_t i) {
  return getRuleContext<C_grammarParser::LogicalOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::StatementContext::Colon() {
  return getTokens(C_grammarParser::Colon);
}

tree::TerminalNode* C_grammarParser::StatementContext::Colon(size_t i) {
  return getToken(C_grammarParser::Colon, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::StatementContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::StatementContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::StatementContext::getRuleIndex() const {
  return C_grammarParser::RuleStatement;
}

void C_grammarParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void C_grammarParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


antlrcpp::Any C_grammarParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StatementContext* C_grammarParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 88, C_grammarParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(486);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(452);
      compoundStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(453);
      expressionStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(454);
      selectionStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(455);
      iterationStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(456);
      returnStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(457);
      match(C_grammarParser::LeftParen);
      setState(466);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 23) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 23)) & ((1ULL << (C_grammarParser::LeftParen - 23))
        | (1ULL << (C_grammarParser::PlusPlus - 23))
        | (1ULL << (C_grammarParser::Minus - 23))
        | (1ULL << (C_grammarParser::MinusMinus - 23))
        | (1ULL << (C_grammarParser::Not - 23))
        | (1ULL << (C_grammarParser::Tilde - 23))
        | (1ULL << (C_grammarParser::Identifier - 23))
        | (1ULL << (C_grammarParser::IntegerConstant - 23))
        | (1ULL << (C_grammarParser::FloatingConstant - 23))
        | (1ULL << (C_grammarParser::CharacterConstant - 23))
        | (1ULL << (C_grammarParser::StringLiteral - 23)))) != 0)) {
        setState(458);
        logicalOrExpression();
        setState(463);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == C_grammarParser::Comma) {
          setState(459);
          match(C_grammarParser::Comma);
          setState(460);
          logicalOrExpression();
          setState(465);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(481);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C_grammarParser::Colon) {
        setState(468);
        match(C_grammarParser::Colon);
        setState(477);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 23) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 23)) & ((1ULL << (C_grammarParser::LeftParen - 23))
          | (1ULL << (C_grammarParser::PlusPlus - 23))
          | (1ULL << (C_grammarParser::Minus - 23))
          | (1ULL << (C_grammarParser::MinusMinus - 23))
          | (1ULL << (C_grammarParser::Not - 23))
          | (1ULL << (C_grammarParser::Tilde - 23))
          | (1ULL << (C_grammarParser::Identifier - 23))
          | (1ULL << (C_grammarParser::IntegerConstant - 23))
          | (1ULL << (C_grammarParser::FloatingConstant - 23))
          | (1ULL << (C_grammarParser::CharacterConstant - 23))
          | (1ULL << (C_grammarParser::StringLiteral - 23)))) != 0)) {
          setState(469);
          logicalOrExpression();
          setState(474);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == C_grammarParser::Comma) {
            setState(470);
            match(C_grammarParser::Comma);
            setState(471);
            logicalOrExpression();
            setState(476);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(483);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(484);
      match(C_grammarParser::RightParen);
      setState(485);
      match(C_grammarParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompoundStatementContext ------------------------------------------------------------------

C_grammarParser::CompoundStatementContext::CompoundStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::CompoundStatementContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::CompoundStatementContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

C_grammarParser::BlockItemListContext* C_grammarParser::CompoundStatementContext::blockItemList() {
  return getRuleContext<C_grammarParser::BlockItemListContext>(0);
}


size_t C_grammarParser::CompoundStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleCompoundStatement;
}

void C_grammarParser::CompoundStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompoundStatement(this);
}

void C_grammarParser::CompoundStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompoundStatement(this);
}


antlrcpp::Any C_grammarParser::CompoundStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitCompoundStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::CompoundStatementContext* C_grammarParser::compoundStatement() {
  CompoundStatementContext *_localctx = _tracker.createInstance<CompoundStatementContext>(_ctx, getState());
  enterRule(_localctx, 90, C_grammarParser::RuleCompoundStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(488);
    match(C_grammarParser::LeftBrace);
    setState(490);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::LeftBrace)
      | (1ULL << C_grammarParser::PlusPlus)
      | (1ULL << C_grammarParser::Minus)
      | (1ULL << C_grammarParser::MinusMinus)
      | (1ULL << C_grammarParser::Not)
      | (1ULL << C_grammarParser::Tilde)
      | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (C_grammarParser::Identifier - 69))
      | (1ULL << (C_grammarParser::IntegerConstant - 69))
      | (1ULL << (C_grammarParser::FloatingConstant - 69))
      | (1ULL << (C_grammarParser::DigitSequence - 69))
      | (1ULL << (C_grammarParser::CharacterConstant - 69))
      | (1ULL << (C_grammarParser::StringLiteral - 69)))) != 0)) {
      setState(489);
      blockItemList();
    }
    setState(492);
    match(C_grammarParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemListContext ------------------------------------------------------------------

C_grammarParser::BlockItemListContext::BlockItemListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::BlockItemContext *> C_grammarParser::BlockItemListContext::blockItem() {
  return getRuleContexts<C_grammarParser::BlockItemContext>();
}

C_grammarParser::BlockItemContext* C_grammarParser::BlockItemListContext::blockItem(size_t i) {
  return getRuleContext<C_grammarParser::BlockItemContext>(i);
}


size_t C_grammarParser::BlockItemListContext::getRuleIndex() const {
  return C_grammarParser::RuleBlockItemList;
}

void C_grammarParser::BlockItemListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockItemList(this);
}

void C_grammarParser::BlockItemListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockItemList(this);
}


antlrcpp::Any C_grammarParser::BlockItemListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitBlockItemList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::BlockItemListContext* C_grammarParser::blockItemList() {
  BlockItemListContext *_localctx = _tracker.createInstance<BlockItemListContext>(_ctx, getState());
  enterRule(_localctx, 92, C_grammarParser::RuleBlockItemList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(495); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(494);
      blockItem();
      setState(497); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::LeftBrace)
      | (1ULL << C_grammarParser::PlusPlus)
      | (1ULL << C_grammarParser::Minus)
      | (1ULL << C_grammarParser::MinusMinus)
      | (1ULL << C_grammarParser::Not)
      | (1ULL << C_grammarParser::Tilde)
      | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (C_grammarParser::Identifier - 69))
      | (1ULL << (C_grammarParser::IntegerConstant - 69))
      | (1ULL << (C_grammarParser::FloatingConstant - 69))
      | (1ULL << (C_grammarParser::DigitSequence - 69))
      | (1ULL << (C_grammarParser::CharacterConstant - 69))
      | (1ULL << (C_grammarParser::StringLiteral - 69)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

C_grammarParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StatementContext* C_grammarParser::BlockItemContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::BlockItemContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}


size_t C_grammarParser::BlockItemContext::getRuleIndex() const {
  return C_grammarParser::RuleBlockItem;
}

void C_grammarParser::BlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockItem(this);
}

void C_grammarParser::BlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockItem(this);
}


antlrcpp::Any C_grammarParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::BlockItemContext* C_grammarParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 94, C_grammarParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(501);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(499);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(500);
      declaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

C_grammarParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ExpressionStatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::ExpressionStatementContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ExpressionStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleExpressionStatement;
}

void C_grammarParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}

void C_grammarParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}


antlrcpp::Any C_grammarParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExpressionStatementContext* C_grammarParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 96, C_grammarParser::RuleExpressionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(504);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 23) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 23)) & ((1ULL << (C_grammarParser::LeftParen - 23))
      | (1ULL << (C_grammarParser::PlusPlus - 23))
      | (1ULL << (C_grammarParser::Minus - 23))
      | (1ULL << (C_grammarParser::MinusMinus - 23))
      | (1ULL << (C_grammarParser::Not - 23))
      | (1ULL << (C_grammarParser::Tilde - 23))
      | (1ULL << (C_grammarParser::Identifier - 23))
      | (1ULL << (C_grammarParser::IntegerConstant - 23))
      | (1ULL << (C_grammarParser::FloatingConstant - 23))
      | (1ULL << (C_grammarParser::DigitSequence - 23))
      | (1ULL << (C_grammarParser::CharacterConstant - 23))
      | (1ULL << (C_grammarParser::StringLiteral - 23)))) != 0)) {
      setState(503);
      expression();
    }
    setState(506);
    match(C_grammarParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectionStatementContext ------------------------------------------------------------------

C_grammarParser::SelectionStatementContext::SelectionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::If() {
  return getToken(C_grammarParser::If, 0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::SelectionStatementContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

std::vector<C_grammarParser::StatementContext *> C_grammarParser::SelectionStatementContext::statement() {
  return getRuleContexts<C_grammarParser::StatementContext>();
}

C_grammarParser::StatementContext* C_grammarParser::SelectionStatementContext::statement(size_t i) {
  return getRuleContext<C_grammarParser::StatementContext>(i);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::Else() {
  return getToken(C_grammarParser::Else, 0);
}


size_t C_grammarParser::SelectionStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleSelectionStatement;
}

void C_grammarParser::SelectionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectionStatement(this);
}

void C_grammarParser::SelectionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectionStatement(this);
}


antlrcpp::Any C_grammarParser::SelectionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitSelectionStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::SelectionStatementContext* C_grammarParser::selectionStatement() {
  SelectionStatementContext *_localctx = _tracker.createInstance<SelectionStatementContext>(_ctx, getState());
  enterRule(_localctx, 98, C_grammarParser::RuleSelectionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(508);
    match(C_grammarParser::If);
    setState(509);
    match(C_grammarParser::LeftParen);
    setState(510);
    expression();
    setState(511);
    match(C_grammarParser::RightParen);
    setState(512);
    statement();
    setState(515);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(513);
      match(C_grammarParser::Else);
      setState(514);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IterationStatementContext ------------------------------------------------------------------

C_grammarParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::For() {
  return getToken(C_grammarParser::For, 0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ForConditionContext* C_grammarParser::IterationStatementContext::forCondition() {
  return getRuleContext<C_grammarParser::ForConditionContext>(0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::StatementContext* C_grammarParser::IterationStatementContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}


size_t C_grammarParser::IterationStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleIterationStatement;
}

void C_grammarParser::IterationStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIterationStatement(this);
}

void C_grammarParser::IterationStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIterationStatement(this);
}


antlrcpp::Any C_grammarParser::IterationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitIterationStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::IterationStatementContext* C_grammarParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 100, C_grammarParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(517);
    match(C_grammarParser::For);
    setState(518);
    match(C_grammarParser::LeftParen);
    setState(519);
    forCondition();
    setState(520);
    match(C_grammarParser::RightParen);
    setState(521);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForConditionContext ------------------------------------------------------------------

C_grammarParser::ForConditionContext::ForConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> C_grammarParser::ForConditionContext::Semi() {
  return getTokens(C_grammarParser::Semi);
}

tree::TerminalNode* C_grammarParser::ForConditionContext::Semi(size_t i) {
  return getToken(C_grammarParser::Semi, i);
}

C_grammarParser::ForDeclarationContext* C_grammarParser::ForConditionContext::forDeclaration() {
  return getRuleContext<C_grammarParser::ForDeclarationContext>(0);
}

std::vector<C_grammarParser::ForExpressionContext *> C_grammarParser::ForConditionContext::forExpression() {
  return getRuleContexts<C_grammarParser::ForExpressionContext>();
}

C_grammarParser::ForExpressionContext* C_grammarParser::ForConditionContext::forExpression(size_t i) {
  return getRuleContext<C_grammarParser::ForExpressionContext>(i);
}

C_grammarParser::ExpressionContext* C_grammarParser::ForConditionContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ForConditionContext::getRuleIndex() const {
  return C_grammarParser::RuleForCondition;
}

void C_grammarParser::ForConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForCondition(this);
}

void C_grammarParser::ForConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForCondition(this);
}


antlrcpp::Any C_grammarParser::ForConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForCondition(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForConditionContext* C_grammarParser::forCondition() {
  ForConditionContext *_localctx = _tracker.createInstance<ForConditionContext>(_ctx, getState());
  enterRule(_localctx, 102, C_grammarParser::RuleForCondition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(527);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
    case 1: {
      setState(523);
      forDeclaration();
      break;
    }

    case 2: {
      setState(525);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 23) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 23)) & ((1ULL << (C_grammarParser::LeftParen - 23))
        | (1ULL << (C_grammarParser::PlusPlus - 23))
        | (1ULL << (C_grammarParser::Minus - 23))
        | (1ULL << (C_grammarParser::MinusMinus - 23))
        | (1ULL << (C_grammarParser::Not - 23))
        | (1ULL << (C_grammarParser::Tilde - 23))
        | (1ULL << (C_grammarParser::Identifier - 23))
        | (1ULL << (C_grammarParser::IntegerConstant - 23))
        | (1ULL << (C_grammarParser::FloatingConstant - 23))
        | (1ULL << (C_grammarParser::DigitSequence - 23))
        | (1ULL << (C_grammarParser::CharacterConstant - 23))
        | (1ULL << (C_grammarParser::StringLiteral - 23)))) != 0)) {
        setState(524);
        expression();
      }
      break;
    }

    default:
      break;
    }
    setState(529);
    match(C_grammarParser::Semi);
    setState(531);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 23) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 23)) & ((1ULL << (C_grammarParser::LeftParen - 23))
      | (1ULL << (C_grammarParser::PlusPlus - 23))
      | (1ULL << (C_grammarParser::Minus - 23))
      | (1ULL << (C_grammarParser::MinusMinus - 23))
      | (1ULL << (C_grammarParser::Not - 23))
      | (1ULL << (C_grammarParser::Tilde - 23))
      | (1ULL << (C_grammarParser::Identifier - 23))
      | (1ULL << (C_grammarParser::IntegerConstant - 23))
      | (1ULL << (C_grammarParser::FloatingConstant - 23))
      | (1ULL << (C_grammarParser::DigitSequence - 23))
      | (1ULL << (C_grammarParser::CharacterConstant - 23))
      | (1ULL << (C_grammarParser::StringLiteral - 23)))) != 0)) {
      setState(530);
      forExpression();
    }
    setState(533);
    match(C_grammarParser::Semi);
    setState(535);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 23) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 23)) & ((1ULL << (C_grammarParser::LeftParen - 23))
      | (1ULL << (C_grammarParser::PlusPlus - 23))
      | (1ULL << (C_grammarParser::Minus - 23))
      | (1ULL << (C_grammarParser::MinusMinus - 23))
      | (1ULL << (C_grammarParser::Not - 23))
      | (1ULL << (C_grammarParser::Tilde - 23))
      | (1ULL << (C_grammarParser::Identifier - 23))
      | (1ULL << (C_grammarParser::IntegerConstant - 23))
      | (1ULL << (C_grammarParser::FloatingConstant - 23))
      | (1ULL << (C_grammarParser::DigitSequence - 23))
      | (1ULL << (C_grammarParser::CharacterConstant - 23))
      | (1ULL << (C_grammarParser::StringLiteral - 23)))) != 0)) {
      setState(534);
      forExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForDeclarationContext ------------------------------------------------------------------

C_grammarParser::ForDeclarationContext::ForDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclarationSpecifiersContext* C_grammarParser::ForDeclarationContext::declarationSpecifiers() {
  return getRuleContext<C_grammarParser::DeclarationSpecifiersContext>(0);
}

C_grammarParser::InitDeclaratorListContext* C_grammarParser::ForDeclarationContext::initDeclaratorList() {
  return getRuleContext<C_grammarParser::InitDeclaratorListContext>(0);
}


size_t C_grammarParser::ForDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleForDeclaration;
}

void C_grammarParser::ForDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForDeclaration(this);
}

void C_grammarParser::ForDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForDeclaration(this);
}


antlrcpp::Any C_grammarParser::ForDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForDeclarationContext* C_grammarParser::forDeclaration() {
  ForDeclarationContext *_localctx = _tracker.createInstance<ForDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 104, C_grammarParser::RuleForDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(537);
    declarationSpecifiers();
    setState(539);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftParen

    || _la == C_grammarParser::Identifier) {
      setState(538);
      initDeclaratorList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForExpressionContext ------------------------------------------------------------------

C_grammarParser::ForExpressionContext::ForExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AssignmentExpressionContext *> C_grammarParser::ForExpressionContext::assignmentExpression() {
  return getRuleContexts<C_grammarParser::AssignmentExpressionContext>();
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ForExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ForExpressionContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ForExpressionContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ForExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleForExpression;
}

void C_grammarParser::ForExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForExpression(this);
}

void C_grammarParser::ForExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForExpression(this);
}


antlrcpp::Any C_grammarParser::ForExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForExpressionContext* C_grammarParser::forExpression() {
  ForExpressionContext *_localctx = _tracker.createInstance<ForExpressionContext>(_ctx, getState());
  enterRule(_localctx, 106, C_grammarParser::RuleForExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(541);
    assignmentExpression();
    setState(546);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(542);
      match(C_grammarParser::Comma);
      setState(543);
      assignmentExpression();
      setState(548);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

C_grammarParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ReturnStatementContext::Return() {
  return getToken(C_grammarParser::Return, 0);
}

tree::TerminalNode* C_grammarParser::ReturnStatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::ReturnStatementContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ReturnStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleReturnStatement;
}

void C_grammarParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void C_grammarParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}


antlrcpp::Any C_grammarParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ReturnStatementContext* C_grammarParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 108, C_grammarParser::RuleReturnStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(549);
    match(C_grammarParser::Return);
    setState(551);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 23) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 23)) & ((1ULL << (C_grammarParser::LeftParen - 23))
      | (1ULL << (C_grammarParser::PlusPlus - 23))
      | (1ULL << (C_grammarParser::Minus - 23))
      | (1ULL << (C_grammarParser::MinusMinus - 23))
      | (1ULL << (C_grammarParser::Not - 23))
      | (1ULL << (C_grammarParser::Tilde - 23))
      | (1ULL << (C_grammarParser::Identifier - 23))
      | (1ULL << (C_grammarParser::IntegerConstant - 23))
      | (1ULL << (C_grammarParser::FloatingConstant - 23))
      | (1ULL << (C_grammarParser::DigitSequence - 23))
      | (1ULL << (C_grammarParser::CharacterConstant - 23))
      | (1ULL << (C_grammarParser::StringLiteral - 23)))) != 0)) {
      setState(550);
      expression();
    }
    setState(553);
    match(C_grammarParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TranslationUnitContext ------------------------------------------------------------------

C_grammarParser::TranslationUnitContext::TranslationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ExternalDeclarationContext *> C_grammarParser::TranslationUnitContext::externalDeclaration() {
  return getRuleContexts<C_grammarParser::ExternalDeclarationContext>();
}

C_grammarParser::ExternalDeclarationContext* C_grammarParser::TranslationUnitContext::externalDeclaration(size_t i) {
  return getRuleContext<C_grammarParser::ExternalDeclarationContext>(i);
}


size_t C_grammarParser::TranslationUnitContext::getRuleIndex() const {
  return C_grammarParser::RuleTranslationUnit;
}

void C_grammarParser::TranslationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTranslationUnit(this);
}

void C_grammarParser::TranslationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTranslationUnit(this);
}


antlrcpp::Any C_grammarParser::TranslationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTranslationUnit(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TranslationUnitContext* C_grammarParser::translationUnit() {
  TranslationUnitContext *_localctx = _tracker.createInstance<TranslationUnitContext>(_ctx, getState());
  enterRule(_localctx, 110, C_grammarParser::RuleTranslationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(556); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(555);
      externalDeclaration();
      setState(558); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::Semi))) != 0) || _la == C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternalDeclarationContext ------------------------------------------------------------------

C_grammarParser::ExternalDeclarationContext::ExternalDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::FunctionDefinitionContext* C_grammarParser::ExternalDeclarationContext::functionDefinition() {
  return getRuleContext<C_grammarParser::FunctionDefinitionContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::ExternalDeclarationContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::ExternalDeclarationContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::ExternalDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleExternalDeclaration;
}

void C_grammarParser::ExternalDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternalDeclaration(this);
}

void C_grammarParser::ExternalDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternalDeclaration(this);
}


antlrcpp::Any C_grammarParser::ExternalDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExternalDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExternalDeclarationContext* C_grammarParser::externalDeclaration() {
  ExternalDeclarationContext *_localctx = _tracker.createInstance<ExternalDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 112, C_grammarParser::RuleExternalDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(563);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(560);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(561);
      declaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(562);
      match(C_grammarParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

C_grammarParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclaratorContext* C_grammarParser::FunctionDefinitionContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

C_grammarParser::CompoundStatementContext* C_grammarParser::FunctionDefinitionContext::compoundStatement() {
  return getRuleContext<C_grammarParser::CompoundStatementContext>(0);
}

C_grammarParser::DeclarationSpecifiersContext* C_grammarParser::FunctionDefinitionContext::declarationSpecifiers() {
  return getRuleContext<C_grammarParser::DeclarationSpecifiersContext>(0);
}

C_grammarParser::DeclarationListContext* C_grammarParser::FunctionDefinitionContext::declarationList() {
  return getRuleContext<C_grammarParser::DeclarationListContext>(0);
}


size_t C_grammarParser::FunctionDefinitionContext::getRuleIndex() const {
  return C_grammarParser::RuleFunctionDefinition;
}

void C_grammarParser::FunctionDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDefinition(this);
}

void C_grammarParser::FunctionDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDefinition(this);
}


antlrcpp::Any C_grammarParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::FunctionDefinitionContext* C_grammarParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 114, C_grammarParser::RuleFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(566);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
    case 1: {
      setState(565);
      declarationSpecifiers();
      break;
    }

    default:
      break;
    }
    setState(568);
    declarator();
    setState(570);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile))) != 0) || _la == C_grammarParser::Identifier) {
      setState(569);
      declarationList();
    }
    setState(572);
    compoundStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationListContext ------------------------------------------------------------------

C_grammarParser::DeclarationListContext::DeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::DeclarationContext *> C_grammarParser::DeclarationListContext::declaration() {
  return getRuleContexts<C_grammarParser::DeclarationContext>();
}

C_grammarParser::DeclarationContext* C_grammarParser::DeclarationListContext::declaration(size_t i) {
  return getRuleContext<C_grammarParser::DeclarationContext>(i);
}


size_t C_grammarParser::DeclarationListContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclarationList;
}

void C_grammarParser::DeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarationList(this);
}

void C_grammarParser::DeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarationList(this);
}


antlrcpp::Any C_grammarParser::DeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclarationListContext* C_grammarParser::declarationList() {
  DeclarationListContext *_localctx = _tracker.createInstance<DeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 116, C_grammarParser::RuleDeclarationList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(575); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(574);
      declaration();
      setState(577); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile))) != 0) || _la == C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

C_grammarParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ConstantContext::IntegerConstant() {
  return getToken(C_grammarParser::IntegerConstant, 0);
}

tree::TerminalNode* C_grammarParser::ConstantContext::FloatingConstant() {
  return getToken(C_grammarParser::FloatingConstant, 0);
}

tree::TerminalNode* C_grammarParser::ConstantContext::CharacterConstant() {
  return getToken(C_grammarParser::CharacterConstant, 0);
}


size_t C_grammarParser::ConstantContext::getRuleIndex() const {
  return C_grammarParser::RuleConstant;
}

void C_grammarParser::ConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstant(this);
}

void C_grammarParser::ConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstant(this);
}


antlrcpp::Any C_grammarParser::ConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConstant(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConstantContext* C_grammarParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 118, C_grammarParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(579);
    _la = _input->LA(1);
    if (!(((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & ((1ULL << (C_grammarParser::IntegerConstant - 70))
      | (1ULL << (C_grammarParser::FloatingConstant - 70))
      | (1ULL << (C_grammarParser::CharacterConstant - 70)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool C_grammarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 30: return directDeclaratorSempred(dynamic_cast<DirectDeclaratorContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool C_grammarParser::directDeclaratorSempred(DirectDeclaratorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 6);
    case 2: return precpred(_ctx, 5);
    case 3: return precpred(_ctx, 4);
    case 4: return precpred(_ctx, 3);
    case 5: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> C_grammarParser::_decisionToDFA;
atn::PredictionContextCache C_grammarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN C_grammarParser::_atn;
std::vector<uint16_t> C_grammarParser::_serializedATN;

std::vector<std::string> C_grammarParser::_ruleNames = {
  "compilationUnit", "primaryExpression", "unaryExpression", "unaryOperator", 
  "multiplicativeOperator", "multiplicativeExpression", "additiveExpression", 
  "shiftExpression", "relationalExpression", "equalityExpression", "andExpression", 
  "exclusiveOrExpression", "inclusiveOrExpression", "logicalAndExpression", 
  "logicalOrExpression", "conditionalExpression", "assignmentExpression", 
  "assignmentOperator", "expression", "constantExpression", "declaration", 
  "declarationSpecifiers", "declarationSpecifier", "initDeclaratorList", 
  "initDeclarator", "storageClassSpecifier", "typeSpecifier", "specifierQualifierList", 
  "typeQualifier", "declarator", "directDeclarator", "nestedParenthesesBlock", 
  "typeQualifierList", "parameterTypeList", "parameterList", "parameterDeclaration", 
  "identifierList", "typeName", "typedefName", "initializer", "initializerList", 
  "designation", "designatorList", "designator", "statement", "compoundStatement", 
  "blockItemList", "blockItem", "expressionStatement", "selectionStatement", 
  "iterationStatement", "forCondition", "forDeclaration", "forExpression", 
  "returnStatement", "translationUnit", "externalDeclaration", "functionDefinition", 
  "declarationList", "constant"
};

std::vector<std::string> C_grammarParser::_literalNames = {
  "", "'extern'", "'static'", "'auto'", "'register'", "'restrict'", "'case'", 
  "'char'", "'const'", "'else'", "'float'", "'for'", "'if'", "'int'", "'long'", 
  "'return'", "'short'", "'signed'", "'typedef'", "'unsigned'", "'void'", 
  "'volatile'", "'while'", "'('", "')'", "'['", "']'", "'{'", "'}'", "'<'", 
  "'<='", "'>'", "'>='", "'<<'", "'>>'", "'+'", "'++'", "'-'", "'--'", "'*'", 
  "'/'", "'%'", "'&'", "'|'", "'&&'", "'||'", "'^'", "'!'", "'~'", "'\u003F'", 
  "':'", "';'", "','", "'='", "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", 
  "'>>='", "'&='", "'^='", "'|='", "'=='", "'!='", "'->'", "'.'", "'...'"
};

std::vector<std::string> C_grammarParser::_symbolicNames = {
  "", "", "", "", "", "", "Case", "Char", "Const", "Else", "Float", "For", 
  "If", "Int", "Long", "Return", "Short", "Signed", "Typedef", "Unsigned", 
  "Void", "Volatile", "While", "LeftParen", "RightParen", "LeftBracket", 
  "RightBracket", "LeftBrace", "RightBrace", "Less", "LessEqual", "Greater", 
  "GreaterEqual", "LeftShift", "RightShift", "Plus", "PlusPlus", "Minus", 
  "MinusMinus", "Star", "Div", "Mod", "And", "Or", "AndAnd", "OrOr", "Caret", 
  "Not", "Tilde", "Question", "Colon", "Semi", "Comma", "Assign", "StarAssign", 
  "DivAssign", "ModAssign", "PlusAssign", "MinusAssign", "LeftShiftAssign", 
  "RightShiftAssign", "AndAssign", "XorAssign", "OrAssign", "Equal", "NotEqual", 
  "Arrow", "Dot", "Ellipsis", "Identifier", "IntegerConstant", "FloatingConstant", 
  "DigitSequence", "CharacterConstant", "StringLiteral", "ComplexDefine", 
  "IncludeDirective", "AsmBlock", "LineAfterPreprocessing", "LineDirective", 
  "PragmaDirective", "Whitespace", "Newline", "BlockComment", "LineComment"
};

dfa::Vocabulary C_grammarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> C_grammarParser::_tokenNames;

C_grammarParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x56, 0x248, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35, 
    0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4, 
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c, 
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x3, 0x2, 0x5, 0x2, 0x7c, 0xa, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x83, 0xa, 
    0x3, 0xd, 0x3, 0xe, 0x3, 0x84, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x5, 0x3, 0x8b, 0xa, 0x3, 0x3, 0x4, 0x7, 0x4, 0x8e, 0xa, 0x4, 0xc, 0x4, 
    0xe, 0x4, 0x91, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 
    0x4, 0x97, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0xa1, 0xa, 0x7, 0xc, 0x7, 0xe, 
    0x7, 0xa4, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0xa9, 0xa, 
    0x8, 0xc, 0x8, 0xe, 0x8, 0xac, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x7, 0x9, 0xb1, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0xb4, 0xb, 0x9, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0xb9, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0xbc, 
    0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0xc1, 0xa, 0xb, 0xc, 
    0xb, 0xe, 0xb, 0xc4, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 
    0xc9, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0xcc, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x7, 0xd, 0xd1, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xd4, 0xb, 0xd, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0xd9, 0xa, 0xe, 0xc, 0xe, 0xe, 
    0xe, 0xdc, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0xe1, 0xa, 
    0xf, 0xc, 0xf, 0xe, 0xf, 0xe4, 0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x7, 0x10, 0xe9, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0xec, 0xb, 0x10, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 
    0x11, 0xf4, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x5, 0x12, 0xfc, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0x103, 0xa, 0x14, 0xc, 0x14, 
    0xe, 0x14, 0x106, 0xb, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 
    0x5, 0x16, 0x10c, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x6, 0x17, 
    0x111, 0xa, 0x17, 0xd, 0x17, 0xe, 0x17, 0x112, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x5, 0x18, 0x118, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x7, 0x19, 0x11d, 0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 0x120, 0xb, 0x19, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x125, 0xa, 0x1a, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x12b, 0xa, 0x1c, 0x3, 0x1d, 
    0x3, 0x1d, 0x5, 0x1d, 0x12f, 0xa, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x132, 
    0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x5, 0x20, 0x141, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x5, 0x20, 0x146, 0xa, 0x20, 0x3, 0x20, 0x5, 0x20, 0x149, 0xa, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x150, 
    0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x5, 0x20, 0x15f, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x5, 0x20, 0x16b, 0xa, 0x20, 0x3, 0x20, 0x7, 0x20, 0x16e, 0xa, 
    0x20, 0xc, 0x20, 0xe, 0x20, 0x171, 0xb, 0x20, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x7, 0x21, 0x178, 0xa, 0x21, 0xc, 0x21, 
    0xe, 0x21, 0x17b, 0xb, 0x21, 0x3, 0x22, 0x6, 0x22, 0x17e, 0xa, 0x22, 
    0xd, 0x22, 0xe, 0x22, 0x17f, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 
    0x185, 0xa, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x7, 0x24, 0x18a, 
    0xa, 0x24, 0xc, 0x24, 0xe, 0x24, 0x18d, 0xb, 0x24, 0x3, 0x25, 0x3, 0x25, 
    0x3, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x7, 0x26, 0x195, 0xa, 0x26, 
    0xc, 0x26, 0xe, 0x26, 0x198, 0xb, 0x26, 0x3, 0x27, 0x5, 0x27, 0x19b, 
    0xa, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 
    0x29, 0x5, 0x29, 0x1a3, 0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 
    0x1a7, 0xa, 0x29, 0x3, 0x2a, 0x5, 0x2a, 0x1aa, 0xa, 0x2a, 0x3, 0x2a, 
    0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x1af, 0xa, 0x2a, 0x3, 0x2a, 0x7, 0x2a, 
    0x1b2, 0xa, 0x2a, 0xc, 0x2a, 0xe, 0x2a, 0x1b5, 0xb, 0x2a, 0x3, 0x2b, 
    0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2c, 0x6, 0x2c, 0x1bb, 0xa, 0x2c, 0xd, 0x2c, 
    0xe, 0x2c, 0x1bc, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 
    0x3, 0x2d, 0x5, 0x2d, 0x1c5, 0xa, 0x2d, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 
    0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x7, 
    0x2e, 0x1d0, 0xa, 0x2e, 0xc, 0x2e, 0xe, 0x2e, 0x1d3, 0xb, 0x2e, 0x5, 
    0x2e, 0x1d5, 0xa, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 
    0x7, 0x2e, 0x1db, 0xa, 0x2e, 0xc, 0x2e, 0xe, 0x2e, 0x1de, 0xb, 0x2e, 
    0x5, 0x2e, 0x1e0, 0xa, 0x2e, 0x7, 0x2e, 0x1e2, 0xa, 0x2e, 0xc, 0x2e, 
    0xe, 0x2e, 0x1e5, 0xb, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x5, 0x2e, 0x1e9, 
    0xa, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 0x1ed, 0xa, 0x2f, 0x3, 0x2f, 
    0x3, 0x2f, 0x3, 0x30, 0x6, 0x30, 0x1f2, 0xa, 0x30, 0xd, 0x30, 0xe, 0x30, 
    0x1f3, 0x3, 0x31, 0x3, 0x31, 0x5, 0x31, 0x1f8, 0xa, 0x31, 0x3, 0x32, 
    0x5, 0x32, 0x1fb, 0xa, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x33, 0x3, 0x33, 
    0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x5, 0x33, 0x206, 
    0xa, 0x33, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 
    0x34, 0x3, 0x35, 0x3, 0x35, 0x5, 0x35, 0x210, 0xa, 0x35, 0x5, 0x35, 
    0x212, 0xa, 0x35, 0x3, 0x35, 0x3, 0x35, 0x5, 0x35, 0x216, 0xa, 0x35, 
    0x3, 0x35, 0x3, 0x35, 0x5, 0x35, 0x21a, 0xa, 0x35, 0x3, 0x36, 0x3, 0x36, 
    0x5, 0x36, 0x21e, 0xa, 0x36, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x7, 0x37, 
    0x223, 0xa, 0x37, 0xc, 0x37, 0xe, 0x37, 0x226, 0xb, 0x37, 0x3, 0x38, 
    0x3, 0x38, 0x5, 0x38, 0x22a, 0xa, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x39, 
    0x6, 0x39, 0x22f, 0xa, 0x39, 0xd, 0x39, 0xe, 0x39, 0x230, 0x3, 0x3a, 
    0x3, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 0x236, 0xa, 0x3a, 0x3, 0x3b, 0x5, 0x3b, 
    0x239, 0xa, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x23d, 0xa, 0x3b, 
    0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3c, 0x6, 0x3c, 0x242, 0xa, 0x3c, 0xd, 0x3c, 
    0xe, 0x3c, 0x243, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x2, 0x3, 0x3e, 0x3e, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 
    0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 
    0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 
    0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 
    0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x2, 
    0xf, 0x4, 0x2, 0x26, 0x26, 0x28, 0x28, 0x4, 0x2, 0x27, 0x27, 0x31, 0x32, 
    0x3, 0x2, 0x29, 0x2b, 0x4, 0x2, 0x25, 0x25, 0x27, 0x27, 0x3, 0x2, 0x23, 
    0x24, 0x3, 0x2, 0x1f, 0x22, 0x3, 0x2, 0x42, 0x43, 0x3, 0x2, 0x37, 0x41, 
    0x4, 0x2, 0x3, 0x6, 0x14, 0x14, 0x7, 0x2, 0x9, 0x9, 0xc, 0xc, 0xf, 0x10, 
    0x12, 0x13, 0x15, 0x16, 0x5, 0x2, 0x7, 0x7, 0xa, 0xa, 0x17, 0x17, 0x3, 
    0x2, 0x19, 0x1a, 0x4, 0x2, 0x48, 0x49, 0x4b, 0x4b, 0x2, 0x260, 0x2, 
    0x7b, 0x3, 0x2, 0x2, 0x2, 0x4, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x6, 0x8f, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0x98, 0x3, 0x2, 0x2, 0x2, 0xa, 0x9a, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x9c, 0x3, 0x2, 0x2, 0x2, 0xe, 0xa5, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0xad, 0x3, 0x2, 0x2, 0x2, 0x12, 0xb5, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0xbd, 0x3, 0x2, 0x2, 0x2, 0x16, 0xc5, 0x3, 0x2, 0x2, 0x2, 0x18, 0xcd, 
    0x3, 0x2, 0x2, 0x2, 0x1a, 0xd5, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xdd, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0xe5, 0x3, 0x2, 0x2, 0x2, 0x20, 0xed, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0xfb, 0x3, 0x2, 0x2, 0x2, 0x24, 0xfd, 0x3, 0x2, 0x2, 
    0x2, 0x26, 0xff, 0x3, 0x2, 0x2, 0x2, 0x28, 0x107, 0x3, 0x2, 0x2, 0x2, 
    0x2a, 0x109, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x110, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0x117, 0x3, 0x2, 0x2, 0x2, 0x30, 0x119, 0x3, 0x2, 0x2, 0x2, 0x32, 0x121, 
    0x3, 0x2, 0x2, 0x2, 0x34, 0x126, 0x3, 0x2, 0x2, 0x2, 0x36, 0x12a, 0x3, 
    0x2, 0x2, 0x2, 0x38, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x133, 0x3, 0x2, 
    0x2, 0x2, 0x3c, 0x135, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x140, 0x3, 0x2, 0x2, 
    0x2, 0x40, 0x179, 0x3, 0x2, 0x2, 0x2, 0x42, 0x17d, 0x3, 0x2, 0x2, 0x2, 
    0x44, 0x181, 0x3, 0x2, 0x2, 0x2, 0x46, 0x186, 0x3, 0x2, 0x2, 0x2, 0x48, 
    0x18e, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x191, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x19a, 
    0x3, 0x2, 0x2, 0x2, 0x4e, 0x19c, 0x3, 0x2, 0x2, 0x2, 0x50, 0x1a6, 0x3, 
    0x2, 0x2, 0x2, 0x52, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x54, 0x1b6, 0x3, 0x2, 
    0x2, 0x2, 0x56, 0x1ba, 0x3, 0x2, 0x2, 0x2, 0x58, 0x1c4, 0x3, 0x2, 0x2, 
    0x2, 0x5a, 0x1e8, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x1ea, 0x3, 0x2, 0x2, 0x2, 
    0x5e, 0x1f1, 0x3, 0x2, 0x2, 0x2, 0x60, 0x1f7, 0x3, 0x2, 0x2, 0x2, 0x62, 
    0x1fa, 0x3, 0x2, 0x2, 0x2, 0x64, 0x1fe, 0x3, 0x2, 0x2, 0x2, 0x66, 0x207, 
    0x3, 0x2, 0x2, 0x2, 0x68, 0x211, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x21b, 0x3, 
    0x2, 0x2, 0x2, 0x6c, 0x21f, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x227, 0x3, 0x2, 
    0x2, 0x2, 0x70, 0x22e, 0x3, 0x2, 0x2, 0x2, 0x72, 0x235, 0x3, 0x2, 0x2, 
    0x2, 0x74, 0x238, 0x3, 0x2, 0x2, 0x2, 0x76, 0x241, 0x3, 0x2, 0x2, 0x2, 
    0x78, 0x245, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7c, 0x5, 0x70, 0x39, 0x2, 0x7b, 
    0x7a, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 
    0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0x2, 0x2, 0x3, 0x7e, 0x3, 0x3, 
    0x2, 0x2, 0x2, 0x7f, 0x8b, 0x7, 0x47, 0x2, 0x2, 0x80, 0x8b, 0x5, 0x78, 
    0x3d, 0x2, 0x81, 0x83, 0x7, 0x4c, 0x2, 0x2, 0x82, 0x81, 0x3, 0x2, 0x2, 
    0x2, 0x83, 0x84, 0x3, 0x2, 0x2, 0x2, 0x84, 0x82, 0x3, 0x2, 0x2, 0x2, 
    0x84, 0x85, 0x3, 0x2, 0x2, 0x2, 0x85, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x86, 
    0x87, 0x7, 0x19, 0x2, 0x2, 0x87, 0x88, 0x5, 0x26, 0x14, 0x2, 0x88, 0x89, 
    0x7, 0x1a, 0x2, 0x2, 0x89, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x7f, 0x3, 
    0x2, 0x2, 0x2, 0x8a, 0x80, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x82, 0x3, 0x2, 
    0x2, 0x2, 0x8a, 0x86, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x5, 0x3, 0x2, 0x2, 
    0x2, 0x8c, 0x8e, 0x9, 0x2, 0x2, 0x2, 0x8d, 0x8c, 0x3, 0x2, 0x2, 0x2, 
    0x8e, 0x91, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x8f, 
    0x90, 0x3, 0x2, 0x2, 0x2, 0x90, 0x96, 0x3, 0x2, 0x2, 0x2, 0x91, 0x8f, 
    0x3, 0x2, 0x2, 0x2, 0x92, 0x97, 0x5, 0x4, 0x3, 0x2, 0x93, 0x94, 0x5, 
    0x8, 0x5, 0x2, 0x94, 0x95, 0x5, 0x6, 0x4, 0x2, 0x95, 0x97, 0x3, 0x2, 
    0x2, 0x2, 0x96, 0x92, 0x3, 0x2, 0x2, 0x2, 0x96, 0x93, 0x3, 0x2, 0x2, 
    0x2, 0x97, 0x7, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x9, 0x3, 0x2, 0x2, 
    0x99, 0x9, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x9, 0x4, 0x2, 0x2, 0x9b, 
    0xb, 0x3, 0x2, 0x2, 0x2, 0x9c, 0xa2, 0x5, 0x6, 0x4, 0x2, 0x9d, 0x9e, 
    0x5, 0xa, 0x6, 0x2, 0x9e, 0x9f, 0x5, 0x6, 0x4, 0x2, 0x9f, 0xa1, 0x3, 
    0x2, 0x2, 0x2, 0xa0, 0x9d, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa4, 0x3, 0x2, 
    0x2, 0x2, 0xa2, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x3, 0x2, 0x2, 
    0x2, 0xa3, 0xd, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa2, 0x3, 0x2, 0x2, 0x2, 
    0xa5, 0xaa, 0x5, 0xc, 0x7, 0x2, 0xa6, 0xa7, 0x9, 0x5, 0x2, 0x2, 0xa7, 
    0xa9, 0x5, 0xc, 0x7, 0x2, 0xa8, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xac, 
    0x3, 0x2, 0x2, 0x2, 0xaa, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0x3, 
    0x2, 0x2, 0x2, 0xab, 0xf, 0x3, 0x2, 0x2, 0x2, 0xac, 0xaa, 0x3, 0x2, 
    0x2, 0x2, 0xad, 0xb2, 0x5, 0xe, 0x8, 0x2, 0xae, 0xaf, 0x9, 0x6, 0x2, 
    0x2, 0xaf, 0xb1, 0x5, 0xe, 0x8, 0x2, 0xb0, 0xae, 0x3, 0x2, 0x2, 0x2, 
    0xb1, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb2, 
    0xb3, 0x3, 0x2, 0x2, 0x2, 0xb3, 0x11, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb2, 
    0x3, 0x2, 0x2, 0x2, 0xb5, 0xba, 0x5, 0x10, 0x9, 0x2, 0xb6, 0xb7, 0x9, 
    0x7, 0x2, 0x2, 0xb7, 0xb9, 0x5, 0x10, 0x9, 0x2, 0xb8, 0xb6, 0x3, 0x2, 
    0x2, 0x2, 0xb9, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb8, 0x3, 0x2, 0x2, 
    0x2, 0xba, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbb, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0xbc, 0xba, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xc2, 0x5, 0x12, 0xa, 0x2, 0xbe, 
    0xbf, 0x9, 0x8, 0x2, 0x2, 0xbf, 0xc1, 0x5, 0x12, 0xa, 0x2, 0xc0, 0xbe, 
    0x3, 0x2, 0x2, 0x2, 0xc1, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc0, 0x3, 
    0x2, 0x2, 0x2, 0xc2, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc3, 0x15, 0x3, 0x2, 
    0x2, 0x2, 0xc4, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xca, 0x5, 0x14, 0xb, 
    0x2, 0xc6, 0xc7, 0x7, 0x2c, 0x2, 0x2, 0xc7, 0xc9, 0x5, 0x14, 0xb, 0x2, 
    0xc8, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xca, 
    0xc8, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcb, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0xcc, 0xca, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xd2, 0x5, 
    0x16, 0xc, 0x2, 0xce, 0xcf, 0x7, 0x30, 0x2, 0x2, 0xcf, 0xd1, 0x5, 0x16, 
    0xc, 0x2, 0xd0, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd4, 0x3, 0x2, 0x2, 
    0x2, 0xd2, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd3, 0x3, 0x2, 0x2, 0x2, 
    0xd3, 0x19, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd5, 
    0xda, 0x5, 0x18, 0xd, 0x2, 0xd6, 0xd7, 0x7, 0x2d, 0x2, 0x2, 0xd7, 0xd9, 
    0x5, 0x18, 0xd, 0x2, 0xd8, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xdc, 0x3, 
    0x2, 0x2, 0x2, 0xda, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xda, 0xdb, 0x3, 0x2, 
    0x2, 0x2, 0xdb, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xda, 0x3, 0x2, 0x2, 
    0x2, 0xdd, 0xe2, 0x5, 0x1a, 0xe, 0x2, 0xde, 0xdf, 0x7, 0x2e, 0x2, 0x2, 
    0xdf, 0xe1, 0x5, 0x1a, 0xe, 0x2, 0xe0, 0xde, 0x3, 0x2, 0x2, 0x2, 0xe1, 
    0xe4, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe3, 
    0x3, 0x2, 0x2, 0x2, 0xe3, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe2, 0x3, 
    0x2, 0x2, 0x2, 0xe5, 0xea, 0x5, 0x1c, 0xf, 0x2, 0xe6, 0xe7, 0x7, 0x2f, 
    0x2, 0x2, 0xe7, 0xe9, 0x5, 0x1c, 0xf, 0x2, 0xe8, 0xe6, 0x3, 0x2, 0x2, 
    0x2, 0xe9, 0xec, 0x3, 0x2, 0x2, 0x2, 0xea, 0xe8, 0x3, 0x2, 0x2, 0x2, 
    0xea, 0xeb, 0x3, 0x2, 0x2, 0x2, 0xeb, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xec, 
    0xea, 0x3, 0x2, 0x2, 0x2, 0xed, 0xf3, 0x5, 0x1e, 0x10, 0x2, 0xee, 0xef, 
    0x7, 0x33, 0x2, 0x2, 0xef, 0xf0, 0x5, 0x26, 0x14, 0x2, 0xf0, 0xf1, 0x7, 
    0x34, 0x2, 0x2, 0xf1, 0xf2, 0x5, 0x20, 0x11, 0x2, 0xf2, 0xf4, 0x3, 0x2, 
    0x2, 0x2, 0xf3, 0xee, 0x3, 0x2, 0x2, 0x2, 0xf3, 0xf4, 0x3, 0x2, 0x2, 
    0x2, 0xf4, 0x21, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xfc, 0x5, 0x20, 0x11, 0x2, 
    0xf6, 0xf7, 0x5, 0x6, 0x4, 0x2, 0xf7, 0xf8, 0x5, 0x24, 0x13, 0x2, 0xf8, 
    0xf9, 0x5, 0x22, 0x12, 0x2, 0xf9, 0xfc, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfc, 
    0x7, 0x4a, 0x2, 0x2, 0xfb, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xfb, 0xf6, 0x3, 
    0x2, 0x2, 0x2, 0xfb, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfc, 0x23, 0x3, 0x2, 
    0x2, 0x2, 0xfd, 0xfe, 0x9, 0x9, 0x2, 0x2, 0xfe, 0x25, 0x3, 0x2, 0x2, 
    0x2, 0xff, 0x104, 0x5, 0x22, 0x12, 0x2, 0x100, 0x101, 0x7, 0x36, 0x2, 
    0x2, 0x101, 0x103, 0x5, 0x22, 0x12, 0x2, 0x102, 0x100, 0x3, 0x2, 0x2, 
    0x2, 0x103, 0x106, 0x3, 0x2, 0x2, 0x2, 0x104, 0x102, 0x3, 0x2, 0x2, 
    0x2, 0x104, 0x105, 0x3, 0x2, 0x2, 0x2, 0x105, 0x27, 0x3, 0x2, 0x2, 0x2, 
    0x106, 0x104, 0x3, 0x2, 0x2, 0x2, 0x107, 0x108, 0x5, 0x20, 0x11, 0x2, 
    0x108, 0x29, 0x3, 0x2, 0x2, 0x2, 0x109, 0x10b, 0x5, 0x2c, 0x17, 0x2, 
    0x10a, 0x10c, 0x5, 0x30, 0x19, 0x2, 0x10b, 0x10a, 0x3, 0x2, 0x2, 0x2, 
    0x10b, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10d, 0x3, 0x2, 0x2, 0x2, 
    0x10d, 0x10e, 0x7, 0x35, 0x2, 0x2, 0x10e, 0x2b, 0x3, 0x2, 0x2, 0x2, 
    0x10f, 0x111, 0x5, 0x2e, 0x18, 0x2, 0x110, 0x10f, 0x3, 0x2, 0x2, 0x2, 
    0x111, 0x112, 0x3, 0x2, 0x2, 0x2, 0x112, 0x110, 0x3, 0x2, 0x2, 0x2, 
    0x112, 0x113, 0x3, 0x2, 0x2, 0x2, 0x113, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x114, 
    0x118, 0x5, 0x34, 0x1b, 0x2, 0x115, 0x118, 0x5, 0x36, 0x1c, 0x2, 0x116, 
    0x118, 0x5, 0x3a, 0x1e, 0x2, 0x117, 0x114, 0x3, 0x2, 0x2, 0x2, 0x117, 
    0x115, 0x3, 0x2, 0x2, 0x2, 0x117, 0x116, 0x3, 0x2, 0x2, 0x2, 0x118, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0x119, 0x11e, 0x5, 0x32, 0x1a, 0x2, 0x11a, 
    0x11b, 0x7, 0x36, 0x2, 0x2, 0x11b, 0x11d, 0x5, 0x32, 0x1a, 0x2, 0x11c, 
    0x11a, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x120, 0x3, 0x2, 0x2, 0x2, 0x11e, 
    0x11c, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x11f, 
    0x31, 0x3, 0x2, 0x2, 0x2, 0x120, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x121, 0x124, 
    0x5, 0x3c, 0x1f, 0x2, 0x122, 0x123, 0x7, 0x37, 0x2, 0x2, 0x123, 0x125, 
    0x5, 0x50, 0x29, 0x2, 0x124, 0x122, 0x3, 0x2, 0x2, 0x2, 0x124, 0x125, 
    0x3, 0x2, 0x2, 0x2, 0x125, 0x33, 0x3, 0x2, 0x2, 0x2, 0x126, 0x127, 0x9, 
    0xa, 0x2, 0x2, 0x127, 0x35, 0x3, 0x2, 0x2, 0x2, 0x128, 0x12b, 0x9, 0xb, 
    0x2, 0x2, 0x129, 0x12b, 0x5, 0x4e, 0x28, 0x2, 0x12a, 0x128, 0x3, 0x2, 
    0x2, 0x2, 0x12a, 0x129, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x12c, 0x12f, 0x5, 0x36, 0x1c, 0x2, 0x12d, 0x12f, 0x5, 0x3a, 0x1e, 
    0x2, 0x12e, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x12d, 0x3, 0x2, 0x2, 
    0x2, 0x12f, 0x131, 0x3, 0x2, 0x2, 0x2, 0x130, 0x132, 0x5, 0x38, 0x1d, 
    0x2, 0x131, 0x130, 0x3, 0x2, 0x2, 0x2, 0x131, 0x132, 0x3, 0x2, 0x2, 
    0x2, 0x132, 0x39, 0x3, 0x2, 0x2, 0x2, 0x133, 0x134, 0x9, 0xc, 0x2, 0x2, 
    0x134, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x135, 0x136, 0x5, 0x3e, 0x20, 0x2, 
    0x136, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x137, 0x138, 0x8, 0x20, 0x1, 0x2, 
    0x138, 0x141, 0x7, 0x47, 0x2, 0x2, 0x139, 0x13a, 0x7, 0x19, 0x2, 0x2, 
    0x13a, 0x13b, 0x5, 0x3c, 0x1f, 0x2, 0x13b, 0x13c, 0x7, 0x1a, 0x2, 0x2, 
    0x13c, 0x141, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13e, 0x7, 0x47, 0x2, 0x2, 
    0x13e, 0x13f, 0x7, 0x34, 0x2, 0x2, 0x13f, 0x141, 0x7, 0x4a, 0x2, 0x2, 
    0x140, 0x137, 0x3, 0x2, 0x2, 0x2, 0x140, 0x139, 0x3, 0x2, 0x2, 0x2, 
    0x140, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x141, 0x16f, 0x3, 0x2, 0x2, 0x2, 
    0x142, 0x143, 0xc, 0x9, 0x2, 0x2, 0x143, 0x145, 0x7, 0x1b, 0x2, 0x2, 
    0x144, 0x146, 0x5, 0x42, 0x22, 0x2, 0x145, 0x144, 0x3, 0x2, 0x2, 0x2, 
    0x145, 0x146, 0x3, 0x2, 0x2, 0x2, 0x146, 0x148, 0x3, 0x2, 0x2, 0x2, 
    0x147, 0x149, 0x5, 0x22, 0x12, 0x2, 0x148, 0x147, 0x3, 0x2, 0x2, 0x2, 
    0x148, 0x149, 0x3, 0x2, 0x2, 0x2, 0x149, 0x14a, 0x3, 0x2, 0x2, 0x2, 
    0x14a, 0x16e, 0x7, 0x1c, 0x2, 0x2, 0x14b, 0x14c, 0xc, 0x8, 0x2, 0x2, 
    0x14c, 0x14d, 0x7, 0x1b, 0x2, 0x2, 0x14d, 0x14f, 0x7, 0x4, 0x2, 0x2, 
    0x14e, 0x150, 0x5, 0x42, 0x22, 0x2, 0x14f, 0x14e, 0x3, 0x2, 0x2, 0x2, 
    0x14f, 0x150, 0x3, 0x2, 0x2, 0x2, 0x150, 0x151, 0x3, 0x2, 0x2, 0x2, 
    0x151, 0x152, 0x5, 0x22, 0x12, 0x2, 0x152, 0x153, 0x7, 0x1c, 0x2, 0x2, 
    0x153, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x154, 0x155, 0xc, 0x7, 0x2, 0x2, 
    0x155, 0x156, 0x7, 0x1b, 0x2, 0x2, 0x156, 0x157, 0x5, 0x42, 0x22, 0x2, 
    0x157, 0x158, 0x7, 0x4, 0x2, 0x2, 0x158, 0x159, 0x5, 0x22, 0x12, 0x2, 
    0x159, 0x15a, 0x7, 0x1c, 0x2, 0x2, 0x15a, 0x16e, 0x3, 0x2, 0x2, 0x2, 
    0x15b, 0x15c, 0xc, 0x6, 0x2, 0x2, 0x15c, 0x15e, 0x7, 0x1b, 0x2, 0x2, 
    0x15d, 0x15f, 0x5, 0x42, 0x22, 0x2, 0x15e, 0x15d, 0x3, 0x2, 0x2, 0x2, 
    0x15e, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x160, 0x3, 0x2, 0x2, 0x2, 
    0x160, 0x161, 0x7, 0x29, 0x2, 0x2, 0x161, 0x16e, 0x7, 0x1c, 0x2, 0x2, 
    0x162, 0x163, 0xc, 0x5, 0x2, 0x2, 0x163, 0x164, 0x7, 0x19, 0x2, 0x2, 
    0x164, 0x165, 0x5, 0x44, 0x23, 0x2, 0x165, 0x166, 0x7, 0x1a, 0x2, 0x2, 
    0x166, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x167, 0x168, 0xc, 0x4, 0x2, 0x2, 
    0x168, 0x16a, 0x7, 0x19, 0x2, 0x2, 0x169, 0x16b, 0x5, 0x4a, 0x26, 0x2, 
    0x16a, 0x169, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x16b, 0x3, 0x2, 0x2, 0x2, 
    0x16b, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16e, 0x7, 0x1a, 0x2, 0x2, 
    0x16d, 0x142, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x14b, 0x3, 0x2, 0x2, 0x2, 
    0x16d, 0x154, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x15b, 0x3, 0x2, 0x2, 0x2, 
    0x16d, 0x162, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x167, 0x3, 0x2, 0x2, 0x2, 
    0x16e, 0x171, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x16d, 0x3, 0x2, 0x2, 0x2, 
    0x16f, 0x170, 0x3, 0x2, 0x2, 0x2, 0x170, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x171, 
    0x16f, 0x3, 0x2, 0x2, 0x2, 0x172, 0x178, 0xa, 0xd, 0x2, 0x2, 0x173, 
    0x174, 0x7, 0x19, 0x2, 0x2, 0x174, 0x175, 0x5, 0x40, 0x21, 0x2, 0x175, 
    0x176, 0x7, 0x1a, 0x2, 0x2, 0x176, 0x178, 0x3, 0x2, 0x2, 0x2, 0x177, 
    0x172, 0x3, 0x2, 0x2, 0x2, 0x177, 0x173, 0x3, 0x2, 0x2, 0x2, 0x178, 
    0x17b, 0x3, 0x2, 0x2, 0x2, 0x179, 0x177, 0x3, 0x2, 0x2, 0x2, 0x179, 
    0x17a, 0x3, 0x2, 0x2, 0x2, 0x17a, 0x41, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x179, 
    0x3, 0x2, 0x2, 0x2, 0x17c, 0x17e, 0x5, 0x3a, 0x1e, 0x2, 0x17d, 0x17c, 
    0x3, 0x2, 0x2, 0x2, 0x17e, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x17d, 
    0x3, 0x2, 0x2, 0x2, 0x17f, 0x180, 0x3, 0x2, 0x2, 0x2, 0x180, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x181, 0x184, 0x5, 0x46, 0x24, 0x2, 0x182, 0x183, 0x7, 
    0x36, 0x2, 0x2, 0x183, 0x185, 0x7, 0x46, 0x2, 0x2, 0x184, 0x182, 0x3, 
    0x2, 0x2, 0x2, 0x184, 0x185, 0x3, 0x2, 0x2, 0x2, 0x185, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x186, 0x18b, 0x5, 0x48, 0x25, 0x2, 0x187, 0x188, 0x7, 0x36, 
    0x2, 0x2, 0x188, 0x18a, 0x5, 0x48, 0x25, 0x2, 0x189, 0x187, 0x3, 0x2, 
    0x2, 0x2, 0x18a, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x18b, 0x189, 0x3, 0x2, 
    0x2, 0x2, 0x18b, 0x18c, 0x3, 0x2, 0x2, 0x2, 0x18c, 0x47, 0x3, 0x2, 0x2, 
    0x2, 0x18d, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x18e, 0x18f, 0x5, 0x2c, 0x17, 
    0x2, 0x18f, 0x190, 0x5, 0x3c, 0x1f, 0x2, 0x190, 0x49, 0x3, 0x2, 0x2, 
    0x2, 0x191, 0x196, 0x7, 0x47, 0x2, 0x2, 0x192, 0x193, 0x7, 0x36, 0x2, 
    0x2, 0x193, 0x195, 0x7, 0x47, 0x2, 0x2, 0x194, 0x192, 0x3, 0x2, 0x2, 
    0x2, 0x195, 0x198, 0x3, 0x2, 0x2, 0x2, 0x196, 0x194, 0x3, 0x2, 0x2, 
    0x2, 0x196, 0x197, 0x3, 0x2, 0x2, 0x2, 0x197, 0x4b, 0x3, 0x2, 0x2, 0x2, 
    0x198, 0x196, 0x3, 0x2, 0x2, 0x2, 0x199, 0x19b, 0x5, 0x38, 0x1d, 0x2, 
    0x19a, 0x199, 0x3, 0x2, 0x2, 0x2, 0x19a, 0x19b, 0x3, 0x2, 0x2, 0x2, 
    0x19b, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19d, 0x7, 0x47, 0x2, 0x2, 
    0x19d, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x1a7, 0x5, 0x22, 0x12, 0x2, 
    0x19f, 0x1a0, 0x7, 0x1d, 0x2, 0x2, 0x1a0, 0x1a2, 0x5, 0x52, 0x2a, 0x2, 
    0x1a1, 0x1a3, 0x7, 0x36, 0x2, 0x2, 0x1a2, 0x1a1, 0x3, 0x2, 0x2, 0x2, 
    0x1a2, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a4, 0x3, 0x2, 0x2, 0x2, 
    0x1a4, 0x1a5, 0x7, 0x1e, 0x2, 0x2, 0x1a5, 0x1a7, 0x3, 0x2, 0x2, 0x2, 
    0x1a6, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x19f, 0x3, 0x2, 0x2, 0x2, 
    0x1a7, 0x51, 0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1aa, 0x5, 0x54, 0x2b, 0x2, 
    0x1a9, 0x1a8, 0x3, 0x2, 0x2, 0x2, 0x1a9, 0x1aa, 0x3, 0x2, 0x2, 0x2, 
    0x1aa, 0x1ab, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1b3, 0x5, 0x50, 0x29, 0x2, 
    0x1ac, 0x1ae, 0x7, 0x36, 0x2, 0x2, 0x1ad, 0x1af, 0x5, 0x54, 0x2b, 0x2, 
    0x1ae, 0x1ad, 0x3, 0x2, 0x2, 0x2, 0x1ae, 0x1af, 0x3, 0x2, 0x2, 0x2, 
    0x1af, 0x1b0, 0x3, 0x2, 0x2, 0x2, 0x1b0, 0x1b2, 0x5, 0x50, 0x29, 0x2, 
    0x1b1, 0x1ac, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1b5, 0x3, 0x2, 0x2, 0x2, 
    0x1b3, 0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1b4, 0x3, 0x2, 0x2, 0x2, 
    0x1b4, 0x53, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x1b6, 
    0x1b7, 0x5, 0x56, 0x2c, 0x2, 0x1b7, 0x1b8, 0x7, 0x37, 0x2, 0x2, 0x1b8, 
    0x55, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1bb, 0x5, 0x58, 0x2d, 0x2, 0x1ba, 
    0x1b9, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x1bc, 
    0x1ba, 0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1bd, 0x3, 0x2, 0x2, 0x2, 0x1bd, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x1be, 0x1bf, 0x7, 0x1b, 0x2, 0x2, 0x1bf, 
    0x1c0, 0x5, 0x28, 0x15, 0x2, 0x1c0, 0x1c1, 0x7, 0x1c, 0x2, 0x2, 0x1c1, 
    0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c2, 0x1c3, 0x7, 0x45, 0x2, 0x2, 0x1c3, 
    0x1c5, 0x7, 0x47, 0x2, 0x2, 0x1c4, 0x1be, 0x3, 0x2, 0x2, 0x2, 0x1c4, 
    0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x59, 0x3, 0x2, 0x2, 0x2, 0x1c6, 0x1e9, 
    0x5, 0x5c, 0x2f, 0x2, 0x1c7, 0x1e9, 0x5, 0x62, 0x32, 0x2, 0x1c8, 0x1e9, 
    0x5, 0x64, 0x33, 0x2, 0x1c9, 0x1e9, 0x5, 0x66, 0x34, 0x2, 0x1ca, 0x1e9, 
    0x5, 0x6e, 0x38, 0x2, 0x1cb, 0x1d4, 0x7, 0x19, 0x2, 0x2, 0x1cc, 0x1d1, 
    0x5, 0x1e, 0x10, 0x2, 0x1cd, 0x1ce, 0x7, 0x36, 0x2, 0x2, 0x1ce, 0x1d0, 
    0x5, 0x1e, 0x10, 0x2, 0x1cf, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1d0, 0x1d3, 
    0x3, 0x2, 0x2, 0x2, 0x1d1, 0x1cf, 0x3, 0x2, 0x2, 0x2, 0x1d1, 0x1d2, 
    0x3, 0x2, 0x2, 0x2, 0x1d2, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d3, 0x1d1, 
    0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1cc, 0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1d5, 
    0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1e3, 0x3, 0x2, 0x2, 0x2, 0x1d6, 0x1df, 
    0x7, 0x34, 0x2, 0x2, 0x1d7, 0x1dc, 0x5, 0x1e, 0x10, 0x2, 0x1d8, 0x1d9, 
    0x7, 0x36, 0x2, 0x2, 0x1d9, 0x1db, 0x5, 0x1e, 0x10, 0x2, 0x1da, 0x1d8, 
    0x3, 0x2, 0x2, 0x2, 0x1db, 0x1de, 0x3, 0x2, 0x2, 0x2, 0x1dc, 0x1da, 
    0x3, 0x2, 0x2, 0x2, 0x1dc, 0x1dd, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1e0, 
    0x3, 0x2, 0x2, 0x2, 0x1de, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1df, 0x1d7, 
    0x3, 0x2, 0x2, 0x2, 0x1df, 0x1e0, 0x3, 0x2, 0x2, 0x2, 0x1e0, 0x1e2, 
    0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1e2, 0x1e5, 
    0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e1, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e4, 
    0x3, 0x2, 0x2, 0x2, 0x1e4, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x1e5, 0x1e3, 
    0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1e7, 0x7, 0x1a, 0x2, 0x2, 0x1e7, 0x1e9, 
    0x7, 0x35, 0x2, 0x2, 0x1e8, 0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1c7, 
    0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1c8, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1c9, 
    0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1ca, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1cb, 
    0x3, 0x2, 0x2, 0x2, 0x1e9, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1ec, 0x7, 
    0x1d, 0x2, 0x2, 0x1eb, 0x1ed, 0x5, 0x5e, 0x30, 0x2, 0x1ec, 0x1eb, 0x3, 
    0x2, 0x2, 0x2, 0x1ec, 0x1ed, 0x3, 0x2, 0x2, 0x2, 0x1ed, 0x1ee, 0x3, 
    0x2, 0x2, 0x2, 0x1ee, 0x1ef, 0x7, 0x1e, 0x2, 0x2, 0x1ef, 0x5d, 0x3, 
    0x2, 0x2, 0x2, 0x1f0, 0x1f2, 0x5, 0x60, 0x31, 0x2, 0x1f1, 0x1f0, 0x3, 
    0x2, 0x2, 0x2, 0x1f2, 0x1f3, 0x3, 0x2, 0x2, 0x2, 0x1f3, 0x1f1, 0x3, 
    0x2, 0x2, 0x2, 0x1f3, 0x1f4, 0x3, 0x2, 0x2, 0x2, 0x1f4, 0x5f, 0x3, 0x2, 
    0x2, 0x2, 0x1f5, 0x1f8, 0x5, 0x5a, 0x2e, 0x2, 0x1f6, 0x1f8, 0x5, 0x2a, 
    0x16, 0x2, 0x1f7, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1f6, 0x3, 0x2, 
    0x2, 0x2, 0x1f8, 0x61, 0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1fb, 0x5, 0x26, 
    0x14, 0x2, 0x1fa, 0x1f9, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fb, 0x3, 0x2, 
    0x2, 0x2, 0x1fb, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fd, 0x7, 0x35, 
    0x2, 0x2, 0x1fd, 0x63, 0x3, 0x2, 0x2, 0x2, 0x1fe, 0x1ff, 0x7, 0xe, 0x2, 
    0x2, 0x1ff, 0x200, 0x7, 0x19, 0x2, 0x2, 0x200, 0x201, 0x5, 0x26, 0x14, 
    0x2, 0x201, 0x202, 0x7, 0x1a, 0x2, 0x2, 0x202, 0x205, 0x5, 0x5a, 0x2e, 
    0x2, 0x203, 0x204, 0x7, 0xb, 0x2, 0x2, 0x204, 0x206, 0x5, 0x5a, 0x2e, 
    0x2, 0x205, 0x203, 0x3, 0x2, 0x2, 0x2, 0x205, 0x206, 0x3, 0x2, 0x2, 
    0x2, 0x206, 0x65, 0x3, 0x2, 0x2, 0x2, 0x207, 0x208, 0x7, 0xd, 0x2, 0x2, 
    0x208, 0x209, 0x7, 0x19, 0x2, 0x2, 0x209, 0x20a, 0x5, 0x68, 0x35, 0x2, 
    0x20a, 0x20b, 0x7, 0x1a, 0x2, 0x2, 0x20b, 0x20c, 0x5, 0x5a, 0x2e, 0x2, 
    0x20c, 0x67, 0x3, 0x2, 0x2, 0x2, 0x20d, 0x212, 0x5, 0x6a, 0x36, 0x2, 
    0x20e, 0x210, 0x5, 0x26, 0x14, 0x2, 0x20f, 0x20e, 0x3, 0x2, 0x2, 0x2, 
    0x20f, 0x210, 0x3, 0x2, 0x2, 0x2, 0x210, 0x212, 0x3, 0x2, 0x2, 0x2, 
    0x211, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x211, 0x20f, 0x3, 0x2, 0x2, 0x2, 
    0x212, 0x213, 0x3, 0x2, 0x2, 0x2, 0x213, 0x215, 0x7, 0x35, 0x2, 0x2, 
    0x214, 0x216, 0x5, 0x6c, 0x37, 0x2, 0x215, 0x214, 0x3, 0x2, 0x2, 0x2, 
    0x215, 0x216, 0x3, 0x2, 0x2, 0x2, 0x216, 0x217, 0x3, 0x2, 0x2, 0x2, 
    0x217, 0x219, 0x7, 0x35, 0x2, 0x2, 0x218, 0x21a, 0x5, 0x6c, 0x37, 0x2, 
    0x219, 0x218, 0x3, 0x2, 0x2, 0x2, 0x219, 0x21a, 0x3, 0x2, 0x2, 0x2, 
    0x21a, 0x69, 0x3, 0x2, 0x2, 0x2, 0x21b, 0x21d, 0x5, 0x2c, 0x17, 0x2, 
    0x21c, 0x21e, 0x5, 0x30, 0x19, 0x2, 0x21d, 0x21c, 0x3, 0x2, 0x2, 0x2, 
    0x21d, 0x21e, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x21f, 
    0x224, 0x5, 0x22, 0x12, 0x2, 0x220, 0x221, 0x7, 0x36, 0x2, 0x2, 0x221, 
    0x223, 0x5, 0x22, 0x12, 0x2, 0x222, 0x220, 0x3, 0x2, 0x2, 0x2, 0x223, 
    0x226, 0x3, 0x2, 0x2, 0x2, 0x224, 0x222, 0x3, 0x2, 0x2, 0x2, 0x224, 
    0x225, 0x3, 0x2, 0x2, 0x2, 0x225, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x226, 0x224, 
    0x3, 0x2, 0x2, 0x2, 0x227, 0x229, 0x7, 0x11, 0x2, 0x2, 0x228, 0x22a, 
    0x5, 0x26, 0x14, 0x2, 0x229, 0x228, 0x3, 0x2, 0x2, 0x2, 0x229, 0x22a, 
    0x3, 0x2, 0x2, 0x2, 0x22a, 0x22b, 0x3, 0x2, 0x2, 0x2, 0x22b, 0x22c, 
    0x7, 0x35, 0x2, 0x2, 0x22c, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x22d, 0x22f, 
    0x5, 0x72, 0x3a, 0x2, 0x22e, 0x22d, 0x3, 0x2, 0x2, 0x2, 0x22f, 0x230, 
    0x3, 0x2, 0x2, 0x2, 0x230, 0x22e, 0x3, 0x2, 0x2, 0x2, 0x230, 0x231, 
    0x3, 0x2, 0x2, 0x2, 0x231, 0x71, 0x3, 0x2, 0x2, 0x2, 0x232, 0x236, 0x5, 
    0x74, 0x3b, 0x2, 0x233, 0x236, 0x5, 0x2a, 0x16, 0x2, 0x234, 0x236, 0x7, 
    0x35, 0x2, 0x2, 0x235, 0x232, 0x3, 0x2, 0x2, 0x2, 0x235, 0x233, 0x3, 
    0x2, 0x2, 0x2, 0x235, 0x234, 0x3, 0x2, 0x2, 0x2, 0x236, 0x73, 0x3, 0x2, 
    0x2, 0x2, 0x237, 0x239, 0x5, 0x2c, 0x17, 0x2, 0x238, 0x237, 0x3, 0x2, 
    0x2, 0x2, 0x238, 0x239, 0x3, 0x2, 0x2, 0x2, 0x239, 0x23a, 0x3, 0x2, 
    0x2, 0x2, 0x23a, 0x23c, 0x5, 0x3c, 0x1f, 0x2, 0x23b, 0x23d, 0x5, 0x76, 
    0x3c, 0x2, 0x23c, 0x23b, 0x3, 0x2, 0x2, 0x2, 0x23c, 0x23d, 0x3, 0x2, 
    0x2, 0x2, 0x23d, 0x23e, 0x3, 0x2, 0x2, 0x2, 0x23e, 0x23f, 0x5, 0x5c, 
    0x2f, 0x2, 0x23f, 0x75, 0x3, 0x2, 0x2, 0x2, 0x240, 0x242, 0x5, 0x2a, 
    0x16, 0x2, 0x241, 0x240, 0x3, 0x2, 0x2, 0x2, 0x242, 0x243, 0x3, 0x2, 
    0x2, 0x2, 0x243, 0x241, 0x3, 0x2, 0x2, 0x2, 0x243, 0x244, 0x3, 0x2, 
    0x2, 0x2, 0x244, 0x77, 0x3, 0x2, 0x2, 0x2, 0x245, 0x246, 0x9, 0xe, 0x2, 
    0x2, 0x246, 0x79, 0x3, 0x2, 0x2, 0x2, 0x49, 0x7b, 0x84, 0x8a, 0x8f, 
    0x96, 0xa2, 0xaa, 0xb2, 0xba, 0xc2, 0xca, 0xd2, 0xda, 0xe2, 0xea, 0xf3, 
    0xfb, 0x104, 0x10b, 0x112, 0x117, 0x11e, 0x124, 0x12a, 0x12e, 0x131, 
    0x140, 0x145, 0x148, 0x14f, 0x15e, 0x16a, 0x16d, 0x16f, 0x177, 0x179, 
    0x17f, 0x184, 0x18b, 0x196, 0x19a, 0x1a2, 0x1a6, 0x1a9, 0x1ae, 0x1b3, 
    0x1bc, 0x1c4, 0x1d1, 0x1d4, 0x1dc, 0x1df, 0x1e3, 0x1e8, 0x1ec, 0x1f3, 
    0x1f7, 0x1fa, 0x205, 0x20f, 0x211, 0x215, 0x219, 0x21d, 0x224, 0x229, 
    0x230, 0x235, 0x238, 0x23c, 0x243, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

C_grammarParser::Initializer C_grammarParser::_init;
