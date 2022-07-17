
// Generated from /home/fils/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.9.3


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
    setState(139);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::LeftParen - 2))
      | (1ULL << (C_grammarParser::Semi - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0)) {
      setState(138);
      translationUnit();
    }
    setState(141);
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
    setState(154);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(143);
        match(C_grammarParser::Identifier);
        break;
      }

      case C_grammarParser::Minus:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::CharacterConstant: {
        enterOuterAlt(_localctx, 2);
        setState(144);
        constant();
        break;
      }

      case C_grammarParser::StringLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(146); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(145);
          match(C_grammarParser::StringLiteral);
          setState(148); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == C_grammarParser::StringLiteral);
        break;
      }

      case C_grammarParser::LeftParen: {
        enterOuterAlt(_localctx, 4);
        setState(150);
        match(C_grammarParser::LeftParen);
        setState(151);
        expression();
        setState(152);
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

C_grammarParser::FunctionCallExpressionContext* C_grammarParser::UnaryExpressionContext::functionCallExpression() {
  return getRuleContext<C_grammarParser::FunctionCallExpressionContext>(0);
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

C_grammarParser::ArrayAccessExpressionContext* C_grammarParser::UnaryExpressionContext::arrayAccessExpression() {
  return getRuleContext<C_grammarParser::ArrayAccessExpressionContext>(0);
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
    setState(170);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C_grammarParser::PlusPlus

      || _la == C_grammarParser::MinusMinus) {
        setState(156);
        _la = _input->LA(1);
        if (!(_la == C_grammarParser::PlusPlus

        || _la == C_grammarParser::MinusMinus)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(161);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(167);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(162);
        primaryExpression();
        break;
      }

      case 2: {
        setState(163);
        unaryOperator();
        setState(164);
        unaryExpression();
        break;
      }

      case 3: {
        setState(166);
        functionCallExpression();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(169);
      arrayAccessExpression();
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

//----------------- ArrayAccessExpressionContext ------------------------------------------------------------------

C_grammarParser::ArrayAccessExpressionContext::ArrayAccessExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::PrimaryExpressionContext *> C_grammarParser::ArrayAccessExpressionContext::primaryExpression() {
  return getRuleContexts<C_grammarParser::PrimaryExpressionContext>();
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::ArrayAccessExpressionContext::primaryExpression(size_t i) {
  return getRuleContext<C_grammarParser::PrimaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ArrayAccessExpressionContext::LeftBracket() {
  return getTokens(C_grammarParser::LeftBracket);
}

tree::TerminalNode* C_grammarParser::ArrayAccessExpressionContext::LeftBracket(size_t i) {
  return getToken(C_grammarParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ArrayAccessExpressionContext::RightBracket() {
  return getTokens(C_grammarParser::RightBracket);
}

tree::TerminalNode* C_grammarParser::ArrayAccessExpressionContext::RightBracket(size_t i) {
  return getToken(C_grammarParser::RightBracket, i);
}


size_t C_grammarParser::ArrayAccessExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleArrayAccessExpression;
}

void C_grammarParser::ArrayAccessExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayAccessExpression(this);
}

void C_grammarParser::ArrayAccessExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayAccessExpression(this);
}


antlrcpp::Any C_grammarParser::ArrayAccessExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArrayAccessExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArrayAccessExpressionContext* C_grammarParser::arrayAccessExpression() {
  ArrayAccessExpressionContext *_localctx = _tracker.createInstance<ArrayAccessExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, C_grammarParser::RuleArrayAccessExpression);
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
    setState(172);
    primaryExpression();
    setState(177); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(173);
      match(C_grammarParser::LeftBracket);
      setState(174);
      primaryExpression();
      setState(175);
      match(C_grammarParser::RightBracket);
      setState(179); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == C_grammarParser::LeftBracket);
   
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
  enterRule(_localctx, 8, C_grammarParser::RuleUnaryOperator);
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
    setState(181);
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
  enterRule(_localctx, 10, C_grammarParser::RuleMultiplicativeOperator);
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
    setState(183);
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
  enterRule(_localctx, 12, C_grammarParser::RuleMultiplicativeExpression);
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
    setState(185);
    unaryExpression();
    setState(191);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Star)
      | (1ULL << C_grammarParser::Div)
      | (1ULL << C_grammarParser::Mod))) != 0)) {
      setState(186);
      multiplicativeOperator();
      setState(187);
      unaryExpression();
      setState(193);
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

//----------------- AdditiveOperatorContext ------------------------------------------------------------------

C_grammarParser::AdditiveOperatorContext::AdditiveOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::AdditiveOperatorContext::Plus() {
  return getToken(C_grammarParser::Plus, 0);
}

tree::TerminalNode* C_grammarParser::AdditiveOperatorContext::Minus() {
  return getToken(C_grammarParser::Minus, 0);
}


size_t C_grammarParser::AdditiveOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleAdditiveOperator;
}

void C_grammarParser::AdditiveOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveOperator(this);
}

void C_grammarParser::AdditiveOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveOperator(this);
}


antlrcpp::Any C_grammarParser::AdditiveOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAdditiveOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AdditiveOperatorContext* C_grammarParser::additiveOperator() {
  AdditiveOperatorContext *_localctx = _tracker.createInstance<AdditiveOperatorContext>(_ctx, getState());
  enterRule(_localctx, 14, C_grammarParser::RuleAdditiveOperator);
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
    setState(194);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::Plus

    || _la == C_grammarParser::Minus)) {
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

std::vector<C_grammarParser::AdditiveOperatorContext *> C_grammarParser::AdditiveExpressionContext::additiveOperator() {
  return getRuleContexts<C_grammarParser::AdditiveOperatorContext>();
}

C_grammarParser::AdditiveOperatorContext* C_grammarParser::AdditiveExpressionContext::additiveOperator(size_t i) {
  return getRuleContext<C_grammarParser::AdditiveOperatorContext>(i);
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
  enterRule(_localctx, 16, C_grammarParser::RuleAdditiveExpression);
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
    setState(196);
    multiplicativeExpression();
    setState(202);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Plus

    || _la == C_grammarParser::Minus) {
      setState(197);
      additiveOperator();
      setState(198);
      multiplicativeExpression();
      setState(204);
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

//----------------- ShiftOperatorContext ------------------------------------------------------------------

C_grammarParser::ShiftOperatorContext::ShiftOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ShiftOperatorContext::LeftShift() {
  return getToken(C_grammarParser::LeftShift, 0);
}

tree::TerminalNode* C_grammarParser::ShiftOperatorContext::RightShift() {
  return getToken(C_grammarParser::RightShift, 0);
}


size_t C_grammarParser::ShiftOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleShiftOperator;
}

void C_grammarParser::ShiftOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftOperator(this);
}

void C_grammarParser::ShiftOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftOperator(this);
}


antlrcpp::Any C_grammarParser::ShiftOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitShiftOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ShiftOperatorContext* C_grammarParser::shiftOperator() {
  ShiftOperatorContext *_localctx = _tracker.createInstance<ShiftOperatorContext>(_ctx, getState());
  enterRule(_localctx, 18, C_grammarParser::RuleShiftOperator);
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
    setState(205);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::LeftShift

    || _la == C_grammarParser::RightShift)) {
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

std::vector<C_grammarParser::ShiftOperatorContext *> C_grammarParser::ShiftExpressionContext::shiftOperator() {
  return getRuleContexts<C_grammarParser::ShiftOperatorContext>();
}

C_grammarParser::ShiftOperatorContext* C_grammarParser::ShiftExpressionContext::shiftOperator(size_t i) {
  return getRuleContext<C_grammarParser::ShiftOperatorContext>(i);
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
  enterRule(_localctx, 20, C_grammarParser::RuleShiftExpression);
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
    setState(207);
    additiveExpression();
    setState(213);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::LeftShift

    || _la == C_grammarParser::RightShift) {
      setState(208);
      shiftOperator();
      setState(209);
      additiveExpression();
      setState(215);
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

//----------------- RelationalOperatorContext ------------------------------------------------------------------

C_grammarParser::RelationalOperatorContext::RelationalOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::Less() {
  return getToken(C_grammarParser::Less, 0);
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::Greater() {
  return getToken(C_grammarParser::Greater, 0);
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::LessEqual() {
  return getToken(C_grammarParser::LessEqual, 0);
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::GreaterEqual() {
  return getToken(C_grammarParser::GreaterEqual, 0);
}


size_t C_grammarParser::RelationalOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleRelationalOperator;
}

void C_grammarParser::RelationalOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalOperator(this);
}

void C_grammarParser::RelationalOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalOperator(this);
}


antlrcpp::Any C_grammarParser::RelationalOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitRelationalOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::RelationalOperatorContext* C_grammarParser::relationalOperator() {
  RelationalOperatorContext *_localctx = _tracker.createInstance<RelationalOperatorContext>(_ctx, getState());
  enterRule(_localctx, 22, C_grammarParser::RuleRelationalOperator);
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
    setState(216);
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

std::vector<C_grammarParser::RelationalOperatorContext *> C_grammarParser::RelationalExpressionContext::relationalOperator() {
  return getRuleContexts<C_grammarParser::RelationalOperatorContext>();
}

C_grammarParser::RelationalOperatorContext* C_grammarParser::RelationalExpressionContext::relationalOperator(size_t i) {
  return getRuleContext<C_grammarParser::RelationalOperatorContext>(i);
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
  enterRule(_localctx, 24, C_grammarParser::RuleRelationalExpression);
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
    setState(218);
    shiftExpression();
    setState(224);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Less)
      | (1ULL << C_grammarParser::LessEqual)
      | (1ULL << C_grammarParser::Greater)
      | (1ULL << C_grammarParser::GreaterEqual))) != 0)) {
      setState(219);
      relationalOperator();
      setState(220);
      shiftExpression();
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

//----------------- EqualityOperatorContext ------------------------------------------------------------------

C_grammarParser::EqualityOperatorContext::EqualityOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::EqualityOperatorContext::Equal() {
  return getToken(C_grammarParser::Equal, 0);
}

tree::TerminalNode* C_grammarParser::EqualityOperatorContext::NotEqual() {
  return getToken(C_grammarParser::NotEqual, 0);
}


size_t C_grammarParser::EqualityOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleEqualityOperator;
}

void C_grammarParser::EqualityOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityOperator(this);
}

void C_grammarParser::EqualityOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityOperator(this);
}


antlrcpp::Any C_grammarParser::EqualityOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEqualityOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EqualityOperatorContext* C_grammarParser::equalityOperator() {
  EqualityOperatorContext *_localctx = _tracker.createInstance<EqualityOperatorContext>(_ctx, getState());
  enterRule(_localctx, 26, C_grammarParser::RuleEqualityOperator);
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
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::Equal

    || _la == C_grammarParser::NotEqual)) {
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

std::vector<C_grammarParser::EqualityOperatorContext *> C_grammarParser::EqualityExpressionContext::equalityOperator() {
  return getRuleContexts<C_grammarParser::EqualityOperatorContext>();
}

C_grammarParser::EqualityOperatorContext* C_grammarParser::EqualityExpressionContext::equalityOperator(size_t i) {
  return getRuleContext<C_grammarParser::EqualityOperatorContext>(i);
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
  enterRule(_localctx, 28, C_grammarParser::RuleEqualityExpression);
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
    setState(229);
    relationalExpression();
    setState(235);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Equal

    || _la == C_grammarParser::NotEqual) {
      setState(230);
      equalityOperator();
      setState(231);
      relationalExpression();
      setState(237);
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
  enterRule(_localctx, 30, C_grammarParser::RuleAndExpression);
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
    setState(238);
    equalityExpression();
    setState(243);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::And) {
      setState(239);
      match(C_grammarParser::And);
      setState(240);
      equalityExpression();
      setState(245);
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
  enterRule(_localctx, 32, C_grammarParser::RuleExclusiveOrExpression);
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
    setState(246);
    andExpression();
    setState(251);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Caret) {
      setState(247);
      match(C_grammarParser::Caret);
      setState(248);
      andExpression();
      setState(253);
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
  enterRule(_localctx, 34, C_grammarParser::RuleInclusiveOrExpression);
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
    setState(254);
    exclusiveOrExpression();
    setState(259);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Or) {
      setState(255);
      match(C_grammarParser::Or);
      setState(256);
      exclusiveOrExpression();
      setState(261);
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
  enterRule(_localctx, 36, C_grammarParser::RuleLogicalAndExpression);
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
    setState(262);
    inclusiveOrExpression();
    setState(267);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::AndAnd) {
      setState(263);
      match(C_grammarParser::AndAnd);
      setState(264);
      inclusiveOrExpression();
      setState(269);
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
  enterRule(_localctx, 38, C_grammarParser::RuleLogicalOrExpression);
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
    setState(270);
    logicalAndExpression();
    setState(275);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::OrOr) {
      setState(271);
      match(C_grammarParser::OrOr);
      setState(272);
      logicalAndExpression();
      setState(277);
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
  enterRule(_localctx, 40, C_grammarParser::RuleConditionalExpression);
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
    setState(278);
    logicalOrExpression();
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Question) {
      setState(279);
      match(C_grammarParser::Question);
      setState(280);
      expression();
      setState(281);
      match(C_grammarParser::Colon);
      setState(282);
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
  enterRule(_localctx, 42, C_grammarParser::RuleAssignmentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(292);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(286);
      conditionalExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(287);
      unaryExpression();
      setState(288);
      assignmentOperator();
      setState(289);
      assignmentExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(291);
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
  enterRule(_localctx, 44, C_grammarParser::RuleAssignmentOperator);
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
    setState(294);
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
  enterRule(_localctx, 46, C_grammarParser::RuleExpression);
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
    setState(296);
    assignmentExpression();
    setState(301);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(297);
      match(C_grammarParser::Comma);
      setState(298);
      assignmentExpression();
      setState(303);
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
  enterRule(_localctx, 48, C_grammarParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(304);
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

C_grammarParser::TypeSpecifierContext* C_grammarParser::DeclarationContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

tree::TerminalNode* C_grammarParser::DeclarationContext::Const() {
  return getToken(C_grammarParser::Const, 0);
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
  enterRule(_localctx, 50, C_grammarParser::RuleDeclaration);
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
    setState(307);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Const) {
      setState(306);
      match(C_grammarParser::Const);
    }
    setState(309);
    typeSpecifier();
    setState(311);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftParen

    || _la == C_grammarParser::Identifier) {
      setState(310);
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
  enterRule(_localctx, 52, C_grammarParser::RuleInitDeclaratorList);
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
    setState(313);
    initDeclarator();
    setState(318);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(314);
      match(C_grammarParser::Comma);
      setState(315);
      initDeclarator();
      setState(320);
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
  enterRule(_localctx, 54, C_grammarParser::RuleInitDeclarator);
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
    setState(321);
    declarator();
    setState(324);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Assign) {
      setState(322);
      match(C_grammarParser::Assign);
      setState(323);
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
  enterRule(_localctx, 56, C_grammarParser::RuleTypeSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(328);
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
        setState(326);
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
        setState(327);
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

tree::TerminalNode* C_grammarParser::SpecifierQualifierListContext::Const() {
  return getToken(C_grammarParser::Const, 0);
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
  enterRule(_localctx, 58, C_grammarParser::RuleSpecifierQualifierList);
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
    setState(332);
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
        setState(330);
        typeSpecifier();
        break;
      }

      case C_grammarParser::Const: {
        setState(331);
        match(C_grammarParser::Const);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(335);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0)) {
      setState(334);
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
  enterRule(_localctx, 60, C_grammarParser::RuleDeclarator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
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

std::vector<C_grammarParser::ArrayDeclaratorContext *> C_grammarParser::DirectDeclaratorContext::arrayDeclarator() {
  return getRuleContexts<C_grammarParser::ArrayDeclaratorContext>();
}

C_grammarParser::ArrayDeclaratorContext* C_grammarParser::DirectDeclaratorContext::arrayDeclarator(size_t i) {
  return getRuleContext<C_grammarParser::ArrayDeclaratorContext>(i);
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
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, C_grammarParser::RuleDirectDeclarator, precedence);

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
    setState(348);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      setState(340);
      match(C_grammarParser::Identifier);
      break;
    }

    case 2: {
      setState(341);
      match(C_grammarParser::LeftParen);
      setState(342);
      declarator();
      setState(343);
      match(C_grammarParser::RightParen);
      break;
    }

    case 3: {
      setState(345);
      match(C_grammarParser::Identifier);
      setState(346);
      match(C_grammarParser::Colon);
      setState(347);
      match(C_grammarParser::DigitSequence);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(369);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(367);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(350);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(352); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(351);
                    arrayDeclarator();
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(354); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(356);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(357);
          match(C_grammarParser::LeftParen);
          setState(358);
          parameterTypeList();
          setState(359);
          match(C_grammarParser::RightParen);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(361);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(362);
          match(C_grammarParser::LeftParen);
          setState(364);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == C_grammarParser::Identifier) {
            setState(363);
            identifierList();
          }
          setState(366);
          match(C_grammarParser::RightParen);
          break;
        }

        default:
          break;
        } 
      }
      setState(371);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ArrayDeclaratorContext ------------------------------------------------------------------

C_grammarParser::ArrayDeclaratorContext::ArrayDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ArrayDeclaratorContext::LeftBracket() {
  return getToken(C_grammarParser::LeftBracket, 0);
}

tree::TerminalNode* C_grammarParser::ArrayDeclaratorContext::RightBracket() {
  return getToken(C_grammarParser::RightBracket, 0);
}

tree::TerminalNode* C_grammarParser::ArrayDeclaratorContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ArrayDeclaratorContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}


size_t C_grammarParser::ArrayDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleArrayDeclarator;
}

void C_grammarParser::ArrayDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayDeclarator(this);
}

void C_grammarParser::ArrayDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayDeclarator(this);
}


antlrcpp::Any C_grammarParser::ArrayDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArrayDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArrayDeclaratorContext* C_grammarParser::arrayDeclarator() {
  ArrayDeclaratorContext *_localctx = _tracker.createInstance<ArrayDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 64, C_grammarParser::RuleArrayDeclarator);
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
    setState(372);
    match(C_grammarParser::LeftBracket);
    setState(374);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Const) {
      setState(373);
      match(C_grammarParser::Const);
    }
    setState(377);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
      | (1ULL << (C_grammarParser::PlusPlus - 18))
      | (1ULL << (C_grammarParser::Minus - 18))
      | (1ULL << (C_grammarParser::MinusMinus - 18))
      | (1ULL << (C_grammarParser::Not - 18))
      | (1ULL << (C_grammarParser::Tilde - 18))
      | (1ULL << (C_grammarParser::Identifier - 18))
      | (1ULL << (C_grammarParser::IntegerConstant - 18))
      | (1ULL << (C_grammarParser::FloatingConstant - 18))
      | (1ULL << (C_grammarParser::DigitSequence - 18))
      | (1ULL << (C_grammarParser::CharacterConstant - 18))
      | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
      setState(376);
      assignmentExpression();
    }
    setState(379);
    match(C_grammarParser::RightBracket);
   
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
  enterRule(_localctx, 66, C_grammarParser::RuleNestedParenthesesBlock);
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
    setState(388);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Case)
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
      | (1ULL << C_grammarParser::OrAssign)
      | (1ULL << C_grammarParser::Equal)
      | (1ULL << C_grammarParser::NotEqual)
      | (1ULL << C_grammarParser::Arrow)
      | (1ULL << C_grammarParser::Dot)
      | (1ULL << C_grammarParser::Ellipsis))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
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
      setState(386);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
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
          setState(381);
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
          setState(382);
          match(C_grammarParser::LeftParen);
          setState(383);
          nestedParenthesesBlock();
          setState(384);
          match(C_grammarParser::RightParen);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(390);
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
  enterRule(_localctx, 68, C_grammarParser::RuleParameterTypeList);
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
    setState(391);
    parameterList();
    setState(394);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Comma) {
      setState(392);
      match(C_grammarParser::Comma);
      setState(393);
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
  enterRule(_localctx, 70, C_grammarParser::RuleParameterList);

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
    setState(396);
    parameterDeclaration();
    setState(401);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(397);
        match(C_grammarParser::Comma);
        setState(398);
        parameterDeclaration(); 
      }
      setState(403);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
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

C_grammarParser::TypeSpecifierContext* C_grammarParser::ParameterDeclarationContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

C_grammarParser::DeclaratorContext* C_grammarParser::ParameterDeclarationContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::ParameterDeclarationContext::Const() {
  return getToken(C_grammarParser::Const, 0);
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
  enterRule(_localctx, 72, C_grammarParser::RuleParameterDeclaration);
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
    setState(405);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Const) {
      setState(404);
      match(C_grammarParser::Const);
    }
    setState(407);
    typeSpecifier();
    setState(408);
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
  enterRule(_localctx, 74, C_grammarParser::RuleIdentifierList);
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
    setState(410);
    match(C_grammarParser::Identifier);
    setState(415);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(411);
      match(C_grammarParser::Comma);
      setState(412);
      match(C_grammarParser::Identifier);
      setState(417);
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
  enterRule(_localctx, 76, C_grammarParser::RuleTypeName);
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
    setState(419);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0)) {
      setState(418);
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
  enterRule(_localctx, 78, C_grammarParser::RuleTypedefName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(421);
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
  enterRule(_localctx, 80, C_grammarParser::RuleInitializer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(431);
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
        setState(423);
        assignmentExpression();
        break;
      }

      case C_grammarParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(424);
        match(C_grammarParser::LeftBrace);
        setState(425);
        initializerList();
        setState(427);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::Comma) {
          setState(426);
          match(C_grammarParser::Comma);
        }
        setState(429);
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

//----------------- FunctionCallExpressionContext ------------------------------------------------------------------

C_grammarParser::FunctionCallExpressionContext::FunctionCallExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypedefNameContext* C_grammarParser::FunctionCallExpressionContext::typedefName() {
  return getRuleContext<C_grammarParser::TypedefNameContext>(0);
}

tree::TerminalNode* C_grammarParser::FunctionCallExpressionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::FunctionCallExpressionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::ArgumentExpressionListContext* C_grammarParser::FunctionCallExpressionContext::argumentExpressionList() {
  return getRuleContext<C_grammarParser::ArgumentExpressionListContext>(0);
}


size_t C_grammarParser::FunctionCallExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleFunctionCallExpression;
}

void C_grammarParser::FunctionCallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallExpression(this);
}

void C_grammarParser::FunctionCallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallExpression(this);
}


antlrcpp::Any C_grammarParser::FunctionCallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitFunctionCallExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::FunctionCallExpressionContext* C_grammarParser::functionCallExpression() {
  FunctionCallExpressionContext *_localctx = _tracker.createInstance<FunctionCallExpressionContext>(_ctx, getState());
  enterRule(_localctx, 82, C_grammarParser::RuleFunctionCallExpression);
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
    setState(433);
    typedefName();
    setState(434);
    match(C_grammarParser::LeftParen);
    setState(436);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
      | (1ULL << (C_grammarParser::PlusPlus - 18))
      | (1ULL << (C_grammarParser::Minus - 18))
      | (1ULL << (C_grammarParser::MinusMinus - 18))
      | (1ULL << (C_grammarParser::Not - 18))
      | (1ULL << (C_grammarParser::Tilde - 18))
      | (1ULL << (C_grammarParser::Identifier - 18))
      | (1ULL << (C_grammarParser::IntegerConstant - 18))
      | (1ULL << (C_grammarParser::FloatingConstant - 18))
      | (1ULL << (C_grammarParser::DigitSequence - 18))
      | (1ULL << (C_grammarParser::CharacterConstant - 18))
      | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
      setState(435);
      argumentExpressionList();
    }
    setState(438);
    match(C_grammarParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentExpressionListContext ------------------------------------------------------------------

C_grammarParser::ArgumentExpressionListContext::ArgumentExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ArgumentExpressionContext *> C_grammarParser::ArgumentExpressionListContext::argumentExpression() {
  return getRuleContexts<C_grammarParser::ArgumentExpressionContext>();
}

C_grammarParser::ArgumentExpressionContext* C_grammarParser::ArgumentExpressionListContext::argumentExpression(size_t i) {
  return getRuleContext<C_grammarParser::ArgumentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ArgumentExpressionListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ArgumentExpressionListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ArgumentExpressionListContext::getRuleIndex() const {
  return C_grammarParser::RuleArgumentExpressionList;
}

void C_grammarParser::ArgumentExpressionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentExpressionList(this);
}

void C_grammarParser::ArgumentExpressionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentExpressionList(this);
}


antlrcpp::Any C_grammarParser::ArgumentExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArgumentExpressionList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArgumentExpressionListContext* C_grammarParser::argumentExpressionList() {
  ArgumentExpressionListContext *_localctx = _tracker.createInstance<ArgumentExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 84, C_grammarParser::RuleArgumentExpressionList);
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
    argumentExpression();
    setState(445);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(441);
      match(C_grammarParser::Comma);
      setState(442);
      argumentExpression();
      setState(447);
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

//----------------- ArgumentExpressionContext ------------------------------------------------------------------

C_grammarParser::ArgumentExpressionContext::ArgumentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ArgumentExpressionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}


size_t C_grammarParser::ArgumentExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleArgumentExpression;
}

void C_grammarParser::ArgumentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentExpression(this);
}

void C_grammarParser::ArgumentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentExpression(this);
}


antlrcpp::Any C_grammarParser::ArgumentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArgumentExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArgumentExpressionContext* C_grammarParser::argumentExpression() {
  ArgumentExpressionContext *_localctx = _tracker.createInstance<ArgumentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 86, C_grammarParser::RuleArgumentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(448);
    assignmentExpression();
   
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
  enterRule(_localctx, 88, C_grammarParser::RuleInitializerList);
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
    setState(451);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftBracket

    || _la == C_grammarParser::Dot) {
      setState(450);
      designation();
    }
    setState(453);
    initializer();
    setState(461);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(454);
        match(C_grammarParser::Comma);
        setState(456);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::LeftBracket

        || _la == C_grammarParser::Dot) {
          setState(455);
          designation();
        }
        setState(458);
        initializer(); 
      }
      setState(463);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
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
  enterRule(_localctx, 90, C_grammarParser::RuleDesignation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(464);
    designatorList();
    setState(465);
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
  enterRule(_localctx, 92, C_grammarParser::RuleDesignatorList);
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
    setState(468); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(467);
      designator();
      setState(470); 
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
  enterRule(_localctx, 94, C_grammarParser::RuleDesignator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(478);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBracket: {
        enterOuterAlt(_localctx, 1);
        setState(472);
        match(C_grammarParser::LeftBracket);
        setState(473);
        constantExpression();
        setState(474);
        match(C_grammarParser::RightBracket);
        break;
      }

      case C_grammarParser::Dot: {
        enterOuterAlt(_localctx, 2);
        setState(476);
        match(C_grammarParser::Dot);
        setState(477);
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

C_grammarParser::ExpressionStatementContext* C_grammarParser::StatementContext::expressionStatement() {
  return getRuleContext<C_grammarParser::ExpressionStatementContext>(0);
}

tree::TerminalNode* C_grammarParser::StatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
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
  enterRule(_localctx, 96, C_grammarParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(515);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(480);
      expressionStatement();
      setState(481);
      match(C_grammarParser::Semi);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(483);
      selectionStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(484);
      iterationStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(485);
      returnStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(486);
      match(C_grammarParser::LeftParen);
      setState(495);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 18) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
        | (1ULL << (C_grammarParser::PlusPlus - 18))
        | (1ULL << (C_grammarParser::Minus - 18))
        | (1ULL << (C_grammarParser::MinusMinus - 18))
        | (1ULL << (C_grammarParser::Not - 18))
        | (1ULL << (C_grammarParser::Tilde - 18))
        | (1ULL << (C_grammarParser::Identifier - 18))
        | (1ULL << (C_grammarParser::IntegerConstant - 18))
        | (1ULL << (C_grammarParser::FloatingConstant - 18))
        | (1ULL << (C_grammarParser::CharacterConstant - 18))
        | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
        setState(487);
        logicalOrExpression();
        setState(492);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == C_grammarParser::Comma) {
          setState(488);
          match(C_grammarParser::Comma);
          setState(489);
          logicalOrExpression();
          setState(494);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(510);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C_grammarParser::Colon) {
        setState(497);
        match(C_grammarParser::Colon);
        setState(506);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 18) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
          | (1ULL << (C_grammarParser::PlusPlus - 18))
          | (1ULL << (C_grammarParser::Minus - 18))
          | (1ULL << (C_grammarParser::MinusMinus - 18))
          | (1ULL << (C_grammarParser::Not - 18))
          | (1ULL << (C_grammarParser::Tilde - 18))
          | (1ULL << (C_grammarParser::Identifier - 18))
          | (1ULL << (C_grammarParser::IntegerConstant - 18))
          | (1ULL << (C_grammarParser::FloatingConstant - 18))
          | (1ULL << (C_grammarParser::CharacterConstant - 18))
          | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
          setState(498);
          logicalOrExpression();
          setState(503);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == C_grammarParser::Comma) {
            setState(499);
            match(C_grammarParser::Comma);
            setState(500);
            logicalOrExpression();
            setState(505);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(512);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(513);
      match(C_grammarParser::RightParen);
      setState(514);
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

std::vector<C_grammarParser::BlockItemContext *> C_grammarParser::CompoundStatementContext::blockItem() {
  return getRuleContexts<C_grammarParser::BlockItemContext>();
}

C_grammarParser::BlockItemContext* C_grammarParser::CompoundStatementContext::blockItem(size_t i) {
  return getRuleContext<C_grammarParser::BlockItemContext>(i);
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
  enterRule(_localctx, 98, C_grammarParser::RuleCompoundStatement);
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
    setState(517);
    match(C_grammarParser::LeftBrace);
    setState(521);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::PlusPlus)
      | (1ULL << C_grammarParser::Minus)
      | (1ULL << C_grammarParser::MinusMinus)
      | (1ULL << C_grammarParser::Not)
      | (1ULL << C_grammarParser::Tilde)
      | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
      | (1ULL << (C_grammarParser::IntegerConstant - 64))
      | (1ULL << (C_grammarParser::FloatingConstant - 64))
      | (1ULL << (C_grammarParser::DigitSequence - 64))
      | (1ULL << (C_grammarParser::CharacterConstant - 64))
      | (1ULL << (C_grammarParser::StringLiteral - 64)))) != 0)) {
      setState(518);
      blockItem();
      setState(523);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(524);
    match(C_grammarParser::RightBrace);
   
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

tree::TerminalNode* C_grammarParser::BlockItemContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
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
  enterRule(_localctx, 100, C_grammarParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(530);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(526);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(527);
      declaration();
      setState(528);
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

//----------------- ExpressionStatementContext ------------------------------------------------------------------

C_grammarParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
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
  enterRule(_localctx, 102, C_grammarParser::RuleExpressionStatement);
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
    setState(533);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
      | (1ULL << (C_grammarParser::PlusPlus - 18))
      | (1ULL << (C_grammarParser::Minus - 18))
      | (1ULL << (C_grammarParser::MinusMinus - 18))
      | (1ULL << (C_grammarParser::Not - 18))
      | (1ULL << (C_grammarParser::Tilde - 18))
      | (1ULL << (C_grammarParser::Identifier - 18))
      | (1ULL << (C_grammarParser::IntegerConstant - 18))
      | (1ULL << (C_grammarParser::FloatingConstant - 18))
      | (1ULL << (C_grammarParser::DigitSequence - 18))
      | (1ULL << (C_grammarParser::CharacterConstant - 18))
      | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
      setState(532);
      expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfContentContext ------------------------------------------------------------------

C_grammarParser::IfContentContext::IfContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::IfContentContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::IfContentContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::ConditionalBlockItemContext *> C_grammarParser::IfContentContext::conditionalBlockItem() {
  return getRuleContexts<C_grammarParser::ConditionalBlockItemContext>();
}

C_grammarParser::ConditionalBlockItemContext* C_grammarParser::IfContentContext::conditionalBlockItem(size_t i) {
  return getRuleContext<C_grammarParser::ConditionalBlockItemContext>(i);
}


size_t C_grammarParser::IfContentContext::getRuleIndex() const {
  return C_grammarParser::RuleIfContent;
}

void C_grammarParser::IfContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfContent(this);
}

void C_grammarParser::IfContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfContent(this);
}


antlrcpp::Any C_grammarParser::IfContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitIfContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::IfContentContext* C_grammarParser::ifContent() {
  IfContentContext *_localctx = _tracker.createInstance<IfContentContext>(_ctx, getState());
  enterRule(_localctx, 104, C_grammarParser::RuleIfContent);
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
    setState(544);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBrace: {
        setState(535);
        match(C_grammarParser::LeftBrace);
        setState(539);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
          | (1ULL << C_grammarParser::Const)
          | (1ULL << C_grammarParser::Float)
          | (1ULL << C_grammarParser::For)
          | (1ULL << C_grammarParser::If)
          | (1ULL << C_grammarParser::Int)
          | (1ULL << C_grammarParser::Long)
          | (1ULL << C_grammarParser::Return)
          | (1ULL << C_grammarParser::Short)
          | (1ULL << C_grammarParser::Signed)
          | (1ULL << C_grammarParser::Unsigned)
          | (1ULL << C_grammarParser::Void)
          | (1ULL << C_grammarParser::LeftParen)
          | (1ULL << C_grammarParser::PlusPlus)
          | (1ULL << C_grammarParser::Minus)
          | (1ULL << C_grammarParser::MinusMinus)
          | (1ULL << C_grammarParser::Not)
          | (1ULL << C_grammarParser::Tilde)
          | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
          | (1ULL << (C_grammarParser::IntegerConstant - 64))
          | (1ULL << (C_grammarParser::FloatingConstant - 64))
          | (1ULL << (C_grammarParser::DigitSequence - 64))
          | (1ULL << (C_grammarParser::CharacterConstant - 64))
          | (1ULL << (C_grammarParser::StringLiteral - 64)))) != 0)) {
          setState(536);
          conditionalBlockItem();
          setState(541);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(542);
        match(C_grammarParser::RightBrace);
        break;
      }

      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Float:
      case C_grammarParser::For:
      case C_grammarParser::If:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Return:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Semi:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(543);
        conditionalBlockItem();
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

//----------------- ElseContentContext ------------------------------------------------------------------

C_grammarParser::ElseContentContext::ElseContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ElseContentContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::ElseContentContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::ConditionalBlockItemContext *> C_grammarParser::ElseContentContext::conditionalBlockItem() {
  return getRuleContexts<C_grammarParser::ConditionalBlockItemContext>();
}

C_grammarParser::ConditionalBlockItemContext* C_grammarParser::ElseContentContext::conditionalBlockItem(size_t i) {
  return getRuleContext<C_grammarParser::ConditionalBlockItemContext>(i);
}


size_t C_grammarParser::ElseContentContext::getRuleIndex() const {
  return C_grammarParser::RuleElseContent;
}

void C_grammarParser::ElseContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseContent(this);
}

void C_grammarParser::ElseContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseContent(this);
}


antlrcpp::Any C_grammarParser::ElseContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitElseContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ElseContentContext* C_grammarParser::elseContent() {
  ElseContentContext *_localctx = _tracker.createInstance<ElseContentContext>(_ctx, getState());
  enterRule(_localctx, 106, C_grammarParser::RuleElseContent);
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
    setState(555);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBrace: {
        setState(546);
        match(C_grammarParser::LeftBrace);
        setState(550);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
          | (1ULL << C_grammarParser::Const)
          | (1ULL << C_grammarParser::Float)
          | (1ULL << C_grammarParser::For)
          | (1ULL << C_grammarParser::If)
          | (1ULL << C_grammarParser::Int)
          | (1ULL << C_grammarParser::Long)
          | (1ULL << C_grammarParser::Return)
          | (1ULL << C_grammarParser::Short)
          | (1ULL << C_grammarParser::Signed)
          | (1ULL << C_grammarParser::Unsigned)
          | (1ULL << C_grammarParser::Void)
          | (1ULL << C_grammarParser::LeftParen)
          | (1ULL << C_grammarParser::PlusPlus)
          | (1ULL << C_grammarParser::Minus)
          | (1ULL << C_grammarParser::MinusMinus)
          | (1ULL << C_grammarParser::Not)
          | (1ULL << C_grammarParser::Tilde)
          | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
          | (1ULL << (C_grammarParser::IntegerConstant - 64))
          | (1ULL << (C_grammarParser::FloatingConstant - 64))
          | (1ULL << (C_grammarParser::DigitSequence - 64))
          | (1ULL << (C_grammarParser::CharacterConstant - 64))
          | (1ULL << (C_grammarParser::StringLiteral - 64)))) != 0)) {
          setState(547);
          conditionalBlockItem();
          setState(552);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(553);
        match(C_grammarParser::RightBrace);
        break;
      }

      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Float:
      case C_grammarParser::For:
      case C_grammarParser::If:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Return:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Semi:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(554);
        conditionalBlockItem();
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

//----------------- ConditionalBlockItemContext ------------------------------------------------------------------

C_grammarParser::ConditionalBlockItemContext::ConditionalBlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StatementContext* C_grammarParser::ConditionalBlockItemContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::ConditionalBlockItemContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::ConditionalBlockItemContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::ConditionalBlockItemContext::getRuleIndex() const {
  return C_grammarParser::RuleConditionalBlockItem;
}

void C_grammarParser::ConditionalBlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalBlockItem(this);
}

void C_grammarParser::ConditionalBlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalBlockItem(this);
}


antlrcpp::Any C_grammarParser::ConditionalBlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConditionalBlockItem(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConditionalBlockItemContext* C_grammarParser::conditionalBlockItem() {
  ConditionalBlockItemContext *_localctx = _tracker.createInstance<ConditionalBlockItemContext>(_ctx, getState());
  enterRule(_localctx, 108, C_grammarParser::RuleConditionalBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(561);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(557);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(558);
      declaration();
      setState(559);
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

//----------------- ConditionContentContext ------------------------------------------------------------------

C_grammarParser::ConditionContentContext::ConditionContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ExpressionContext* C_grammarParser::ConditionContentContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ConditionContentContext::getRuleIndex() const {
  return C_grammarParser::RuleConditionContent;
}

void C_grammarParser::ConditionContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionContent(this);
}

void C_grammarParser::ConditionContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionContent(this);
}


antlrcpp::Any C_grammarParser::ConditionContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConditionContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConditionContentContext* C_grammarParser::conditionContent() {
  ConditionContentContext *_localctx = _tracker.createInstance<ConditionContentContext>(_ctx, getState());
  enterRule(_localctx, 110, C_grammarParser::RuleConditionContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(563);
    expression();
   
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

C_grammarParser::ConditionContentContext* C_grammarParser::SelectionStatementContext::conditionContent() {
  return getRuleContext<C_grammarParser::ConditionContentContext>(0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::IfContentContext* C_grammarParser::SelectionStatementContext::ifContent() {
  return getRuleContext<C_grammarParser::IfContentContext>(0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::Else() {
  return getToken(C_grammarParser::Else, 0);
}

C_grammarParser::ElseContentContext* C_grammarParser::SelectionStatementContext::elseContent() {
  return getRuleContext<C_grammarParser::ElseContentContext>(0);
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
  enterRule(_localctx, 112, C_grammarParser::RuleSelectionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(565);
    match(C_grammarParser::If);
    setState(566);
    match(C_grammarParser::LeftParen);
    setState(567);
    conditionContent();
    setState(568);
    match(C_grammarParser::RightParen);
    setState(569);
    ifContent();
    setState(572);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      setState(570);
      match(C_grammarParser::Else);
      setState(571);
      elseContent();
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

C_grammarParser::ForDeclarationContext* C_grammarParser::IterationStatementContext::forDeclaration() {
  return getRuleContext<C_grammarParser::ForDeclarationContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::IterationStatementContext::Semi() {
  return getTokens(C_grammarParser::Semi);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::Semi(size_t i) {
  return getToken(C_grammarParser::Semi, i);
}

C_grammarParser::ForExitConditionContext* C_grammarParser::IterationStatementContext::forExitCondition() {
  return getRuleContext<C_grammarParser::ForExitConditionContext>(0);
}

C_grammarParser::ForIterationExpressionContext* C_grammarParser::IterationStatementContext::forIterationExpression() {
  return getRuleContext<C_grammarParser::ForIterationExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::ForContentContext* C_grammarParser::IterationStatementContext::forContent() {
  return getRuleContext<C_grammarParser::ForContentContext>(0);
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
  enterRule(_localctx, 114, C_grammarParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(574);
    match(C_grammarParser::For);
    setState(575);
    match(C_grammarParser::LeftParen);
    setState(576);
    forDeclaration();
    setState(577);
    match(C_grammarParser::Semi);
    setState(578);
    forExitCondition();
    setState(579);
    match(C_grammarParser::Semi);
    setState(580);
    forIterationExpression();
    setState(581);
    match(C_grammarParser::RightParen);
    setState(582);
    forContent();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForContentContext ------------------------------------------------------------------

C_grammarParser::ForContentContext::ForContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ForContentContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::ForContentContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::ForBlockItemContext *> C_grammarParser::ForContentContext::forBlockItem() {
  return getRuleContexts<C_grammarParser::ForBlockItemContext>();
}

C_grammarParser::ForBlockItemContext* C_grammarParser::ForContentContext::forBlockItem(size_t i) {
  return getRuleContext<C_grammarParser::ForBlockItemContext>(i);
}


size_t C_grammarParser::ForContentContext::getRuleIndex() const {
  return C_grammarParser::RuleForContent;
}

void C_grammarParser::ForContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForContent(this);
}

void C_grammarParser::ForContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForContent(this);
}


antlrcpp::Any C_grammarParser::ForContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForContentContext* C_grammarParser::forContent() {
  ForContentContext *_localctx = _tracker.createInstance<ForContentContext>(_ctx, getState());
  enterRule(_localctx, 116, C_grammarParser::RuleForContent);
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
    setState(593);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBrace: {
        setState(584);
        match(C_grammarParser::LeftBrace);
        setState(588);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::Char)
          | (1ULL << C_grammarParser::Const)
          | (1ULL << C_grammarParser::Float)
          | (1ULL << C_grammarParser::For)
          | (1ULL << C_grammarParser::If)
          | (1ULL << C_grammarParser::Int)
          | (1ULL << C_grammarParser::Long)
          | (1ULL << C_grammarParser::Return)
          | (1ULL << C_grammarParser::Short)
          | (1ULL << C_grammarParser::Signed)
          | (1ULL << C_grammarParser::Unsigned)
          | (1ULL << C_grammarParser::Void)
          | (1ULL << C_grammarParser::LeftParen)
          | (1ULL << C_grammarParser::PlusPlus)
          | (1ULL << C_grammarParser::Minus)
          | (1ULL << C_grammarParser::MinusMinus)
          | (1ULL << C_grammarParser::Not)
          | (1ULL << C_grammarParser::Tilde)
          | (1ULL << C_grammarParser::Semi))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::Identifier - 64))
          | (1ULL << (C_grammarParser::IntegerConstant - 64))
          | (1ULL << (C_grammarParser::FloatingConstant - 64))
          | (1ULL << (C_grammarParser::DigitSequence - 64))
          | (1ULL << (C_grammarParser::CharacterConstant - 64))
          | (1ULL << (C_grammarParser::StringLiteral - 64)))) != 0)) {
          setState(585);
          forBlockItem();
          setState(590);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(591);
        match(C_grammarParser::RightBrace);
        break;
      }

      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Float:
      case C_grammarParser::For:
      case C_grammarParser::If:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Return:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Semi:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(592);
        forBlockItem();
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

//----------------- ForBlockItemContext ------------------------------------------------------------------

C_grammarParser::ForBlockItemContext::ForBlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StatementContext* C_grammarParser::ForBlockItemContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::ForBlockItemContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::ForBlockItemContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::ForBlockItemContext::getRuleIndex() const {
  return C_grammarParser::RuleForBlockItem;
}

void C_grammarParser::ForBlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForBlockItem(this);
}

void C_grammarParser::ForBlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForBlockItem(this);
}


antlrcpp::Any C_grammarParser::ForBlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForBlockItem(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForBlockItemContext* C_grammarParser::forBlockItem() {
  ForBlockItemContext *_localctx = _tracker.createInstance<ForBlockItemContext>(_ctx, getState());
  enterRule(_localctx, 118, C_grammarParser::RuleForBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(599);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(595);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(596);
      declaration();
      setState(597);
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

//----------------- ForExitConditionContext ------------------------------------------------------------------

C_grammarParser::ForExitConditionContext::ForExitConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ForExitConditionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}


size_t C_grammarParser::ForExitConditionContext::getRuleIndex() const {
  return C_grammarParser::RuleForExitCondition;
}

void C_grammarParser::ForExitConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForExitCondition(this);
}

void C_grammarParser::ForExitConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForExitCondition(this);
}


antlrcpp::Any C_grammarParser::ForExitConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForExitCondition(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForExitConditionContext* C_grammarParser::forExitCondition() {
  ForExitConditionContext *_localctx = _tracker.createInstance<ForExitConditionContext>(_ctx, getState());
  enterRule(_localctx, 120, C_grammarParser::RuleForExitCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(601);
    assignmentExpression();
   
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

C_grammarParser::DeclarationContext* C_grammarParser::ForDeclarationContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
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
  enterRule(_localctx, 122, C_grammarParser::RuleForDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(603);
    declaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForIterationExpressionContext ------------------------------------------------------------------

C_grammarParser::ForIterationExpressionContext::ForIterationExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AssignmentExpressionContext *> C_grammarParser::ForIterationExpressionContext::assignmentExpression() {
  return getRuleContexts<C_grammarParser::AssignmentExpressionContext>();
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ForIterationExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ForIterationExpressionContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ForIterationExpressionContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ForIterationExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleForIterationExpression;
}

void C_grammarParser::ForIterationExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForIterationExpression(this);
}

void C_grammarParser::ForIterationExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForIterationExpression(this);
}


antlrcpp::Any C_grammarParser::ForIterationExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForIterationExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForIterationExpressionContext* C_grammarParser::forIterationExpression() {
  ForIterationExpressionContext *_localctx = _tracker.createInstance<ForIterationExpressionContext>(_ctx, getState());
  enterRule(_localctx, 124, C_grammarParser::RuleForIterationExpression);
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
    setState(605);
    assignmentExpression();
    setState(610);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(606);
      match(C_grammarParser::Comma);
      setState(607);
      assignmentExpression();
      setState(612);
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
  enterRule(_localctx, 126, C_grammarParser::RuleReturnStatement);
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
    setState(613);
    match(C_grammarParser::Return);
    setState(615);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 18) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 18)) & ((1ULL << (C_grammarParser::LeftParen - 18))
      | (1ULL << (C_grammarParser::PlusPlus - 18))
      | (1ULL << (C_grammarParser::Minus - 18))
      | (1ULL << (C_grammarParser::MinusMinus - 18))
      | (1ULL << (C_grammarParser::Not - 18))
      | (1ULL << (C_grammarParser::Tilde - 18))
      | (1ULL << (C_grammarParser::Identifier - 18))
      | (1ULL << (C_grammarParser::IntegerConstant - 18))
      | (1ULL << (C_grammarParser::FloatingConstant - 18))
      | (1ULL << (C_grammarParser::DigitSequence - 18))
      | (1ULL << (C_grammarParser::CharacterConstant - 18))
      | (1ULL << (C_grammarParser::StringLiteral - 18)))) != 0)) {
      setState(614);
      expression();
    }
    setState(617);
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
  enterRule(_localctx, 128, C_grammarParser::RuleTranslationUnit);
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
    setState(620); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(619);
      externalDeclaration();
      setState(622); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::LeftParen - 2))
      | (1ULL << (C_grammarParser::Semi - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0));
   
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
  enterRule(_localctx, 130, C_grammarParser::RuleExternalDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(629);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(624);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(625);
      declaration();
      setState(626);
      match(C_grammarParser::Semi);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(628);
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

C_grammarParser::TypeSpecifierContext* C_grammarParser::FunctionDefinitionContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

C_grammarParser::DeclarationListContext* C_grammarParser::FunctionDefinitionContext::declarationList() {
  return getRuleContext<C_grammarParser::DeclarationListContext>(0);
}

tree::TerminalNode* C_grammarParser::FunctionDefinitionContext::Const() {
  return getToken(C_grammarParser::Const, 0);
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
  enterRule(_localctx, 132, C_grammarParser::RuleFunctionDefinition);
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
    setState(635);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      setState(632);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Const) {
        setState(631);
        match(C_grammarParser::Const);
      }
      setState(634);
      typeSpecifier();
      break;
    }

    default:
      break;
    }
    setState(637);
    declarator();
    setState(639);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0)) {
      setState(638);
      declarationList();
    }
    setState(641);
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

std::vector<tree::TerminalNode *> C_grammarParser::DeclarationListContext::Semi() {
  return getTokens(C_grammarParser::Semi);
}

tree::TerminalNode* C_grammarParser::DeclarationListContext::Semi(size_t i) {
  return getToken(C_grammarParser::Semi, i);
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
  enterRule(_localctx, 134, C_grammarParser::RuleDeclarationList);
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
    setState(646); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(643);
      declaration();
      setState(644);
      match(C_grammarParser::Semi);
      setState(648); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 2) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 2)) & ((1ULL << (C_grammarParser::Char - 2))
      | (1ULL << (C_grammarParser::Const - 2))
      | (1ULL << (C_grammarParser::Float - 2))
      | (1ULL << (C_grammarParser::Int - 2))
      | (1ULL << (C_grammarParser::Long - 2))
      | (1ULL << (C_grammarParser::Short - 2))
      | (1ULL << (C_grammarParser::Signed - 2))
      | (1ULL << (C_grammarParser::Unsigned - 2))
      | (1ULL << (C_grammarParser::Void - 2))
      | (1ULL << (C_grammarParser::Identifier - 2)))) != 0));
   
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

tree::TerminalNode* C_grammarParser::ConstantContext::Minus() {
  return getToken(C_grammarParser::Minus, 0);
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
  enterRule(_localctx, 136, C_grammarParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(659);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(651);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Minus) {
        setState(650);
        match(C_grammarParser::Minus);
      }
      setState(653);
      match(C_grammarParser::IntegerConstant);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(655);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Minus) {
        setState(654);
        match(C_grammarParser::Minus);
      }
      setState(657);
      match(C_grammarParser::FloatingConstant);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(658);
      match(C_grammarParser::CharacterConstant);
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

bool C_grammarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 31: return directDeclaratorSempred(antlrcpp::downCast<DirectDeclaratorContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool C_grammarParser::directDeclaratorSempred(DirectDeclaratorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);
    case 2: return precpred(_ctx, 2);

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
  "compilationUnit", "primaryExpression", "unaryExpression", "arrayAccessExpression", 
  "unaryOperator", "multiplicativeOperator", "multiplicativeExpression", 
  "additiveOperator", "additiveExpression", "shiftOperator", "shiftExpression", 
  "relationalOperator", "relationalExpression", "equalityOperator", "equalityExpression", 
  "andExpression", "exclusiveOrExpression", "inclusiveOrExpression", "logicalAndExpression", 
  "logicalOrExpression", "conditionalExpression", "assignmentExpression", 
  "assignmentOperator", "expression", "constantExpression", "declaration", 
  "initDeclaratorList", "initDeclarator", "typeSpecifier", "specifierQualifierList", 
  "declarator", "directDeclarator", "arrayDeclarator", "nestedParenthesesBlock", 
  "parameterTypeList", "parameterList", "parameterDeclaration", "identifierList", 
  "typeName", "typedefName", "initializer", "functionCallExpression", "argumentExpressionList", 
  "argumentExpression", "initializerList", "designation", "designatorList", 
  "designator", "statement", "compoundStatement", "blockItem", "expressionStatement", 
  "ifContent", "elseContent", "conditionalBlockItem", "conditionContent", 
  "selectionStatement", "iterationStatement", "forContent", "forBlockItem", 
  "forExitCondition", "forDeclaration", "forIterationExpression", "returnStatement", 
  "translationUnit", "externalDeclaration", "functionDefinition", "declarationList", 
  "constant"
};

std::vector<std::string> C_grammarParser::_literalNames = {
  "", "'case'", "'char'", "'const'", "'else'", "'float'", "'for'", "'if'", 
  "'int'", "'long'", "'return'", "'short'", "'signed'", "'typedef'", "'unsigned'", 
  "'void'", "'volatile'", "'while'", "'('", "')'", "'['", "']'", "'{'", 
  "'}'", "'<'", "'<='", "'>'", "'>='", "'<<'", "'>>'", "'+'", "'++'", "'-'", 
  "'--'", "'*'", "'/'", "'%'", "'&'", "'|'", "'&&'", "'||'", "'^'", "'!'", 
  "'~'", "'\u003F'", "':'", "';'", "','", "'='", "'*='", "'/='", "'%='", 
  "'+='", "'-='", "'<<='", "'>>='", "'&='", "'^='", "'|='", "'=='", "'!='", 
  "'->'", "'.'", "'...'"
};

std::vector<std::string> C_grammarParser::_symbolicNames = {
  "", "Case", "Char", "Const", "Else", "Float", "For", "If", "Int", "Long", 
  "Return", "Short", "Signed", "Typedef", "Unsigned", "Void", "Volatile", 
  "While", "LeftParen", "RightParen", "LeftBracket", "RightBracket", "LeftBrace", 
  "RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", "LeftShift", 
  "RightShift", "Plus", "PlusPlus", "Minus", "MinusMinus", "Star", "Div", 
  "Mod", "And", "Or", "AndAnd", "OrOr", "Caret", "Not", "Tilde", "Question", 
  "Colon", "Semi", "Comma", "Assign", "StarAssign", "DivAssign", "ModAssign", 
  "PlusAssign", "MinusAssign", "LeftShiftAssign", "RightShiftAssign", "AndAssign", 
  "XorAssign", "OrAssign", "Equal", "NotEqual", "Arrow", "Dot", "Ellipsis", 
  "Identifier", "IntegerConstant", "FloatingConstant", "DigitSequence", 
  "CharacterConstant", "StringLiteral", "ComplexDefine", "IncludeDirective", 
  "AsmBlock", "LineAfterPreprocessing", "LineDirective", "PragmaDirective", 
  "Whitespace", "Newline", "BlockComment", "LineComment"
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

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x51, 0x298, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x4, 0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 
       0x9, 0x14, 0x4, 0x15, 0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 
       0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 
       0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 
       0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 0x9, 0x1f, 0x4, 0x20, 
       0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 0x9, 0x22, 0x4, 0x23, 
       0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 0x25, 0x4, 0x26, 
       0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 0x4, 0x29, 
       0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 0x2c, 
       0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
       0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 
       0x9, 0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 
       0x9, 0x35, 0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 
       0x9, 0x38, 0x4, 0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 
       0x9, 0x3b, 0x4, 0x3c, 0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 
       0x9, 0x3e, 0x4, 0x3f, 0x9, 0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 
       0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 
       0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 0x46, 0x9, 0x46, 0x3, 0x2, 
       0x5, 0x2, 0x8e, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x6, 0x3, 0x95, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 0x96, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x9d, 0xa, 0x3, 0x3, 
       0x4, 0x7, 0x4, 0xa0, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0xa3, 0xb, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0xaa, 
       0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 0xad, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x6, 0x5, 0xb4, 0xa, 0x5, 0xd, 0x5, 
       0xe, 0x5, 0xb5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0xc0, 0xa, 0x8, 0xc, 0x8, 
       0xe, 0x8, 0xc3, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 
       0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0xcb, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 
       0xce, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
       0x3, 0xc, 0x7, 0xc, 0xd6, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0xd9, 0xb, 
       0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x7, 0xe, 0xe1, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xe4, 0xb, 0xe, 0x3, 
       0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 0x10, 
       0xec, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0xef, 0xb, 0x10, 0x3, 0x11, 
       0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 0xf4, 0xa, 0x11, 0xc, 0x11, 0xe, 
       0x11, 0xf7, 0xb, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x7, 0x12, 
       0xfc, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0xff, 0xb, 0x12, 0x3, 0x13, 
       0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0x104, 0xa, 0x13, 0xc, 0x13, 0xe, 
       0x13, 0x107, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 
       0x10c, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0x10f, 0xb, 0x14, 0x3, 0x15, 
       0x3, 0x15, 0x3, 0x15, 0x7, 0x15, 0x114, 0xa, 0x15, 0xc, 0x15, 0xe, 
       0x15, 0x117, 0xb, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
       0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x11f, 0xa, 0x16, 0x3, 0x17, 0x3, 
       0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x127, 
       0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
       0x7, 0x19, 0x12e, 0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 0x131, 0xb, 0x19, 
       0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x5, 0x1b, 0x136, 0xa, 0x1b, 0x3, 
       0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x13a, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 
       0x3, 0x1c, 0x7, 0x1c, 0x13f, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x142, 
       0xb, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x147, 0xa, 
       0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x14b, 0xa, 0x1e, 0x3, 0x1f, 
       0x3, 0x1f, 0x5, 0x1f, 0x14f, 0xa, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x152, 
       0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
       0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
       0x5, 0x21, 0x15f, 0xa, 0x21, 0x3, 0x21, 0x3, 0x21, 0x6, 0x21, 0x163, 
       0xa, 0x21, 0xd, 0x21, 0xe, 0x21, 0x164, 0x3, 0x21, 0x3, 0x21, 0x3, 
       0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 
       0x21, 0x16f, 0xa, 0x21, 0x3, 0x21, 0x7, 0x21, 0x172, 0xa, 0x21, 0xc, 
       0x21, 0xe, 0x21, 0x175, 0xb, 0x21, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 
       0x179, 0xa, 0x22, 0x3, 0x22, 0x5, 0x22, 0x17c, 0xa, 0x22, 0x3, 0x22, 
       0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
       0x7, 0x23, 0x185, 0xa, 0x23, 0xc, 0x23, 0xe, 0x23, 0x188, 0xb, 0x23, 
       0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x18d, 0xa, 0x24, 0x3, 
       0x25, 0x3, 0x25, 0x3, 0x25, 0x7, 0x25, 0x192, 0xa, 0x25, 0xc, 0x25, 
       0xe, 0x25, 0x195, 0xb, 0x25, 0x3, 0x26, 0x5, 0x26, 0x198, 0xa, 0x26, 
       0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 
       0x7, 0x27, 0x1a0, 0xa, 0x27, 0xc, 0x27, 0xe, 0x27, 0x1a3, 0xb, 0x27, 
       0x3, 0x28, 0x5, 0x28, 0x1a6, 0xa, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 
       0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x1ae, 0xa, 0x2a, 
       0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x1b2, 0xa, 0x2a, 0x3, 0x2b, 0x3, 
       0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x1b7, 0xa, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 
       0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x7, 0x2c, 0x1be, 0xa, 0x2c, 0xc, 
       0x2c, 0xe, 0x2c, 0x1c1, 0xb, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2e, 
       0x5, 0x2e, 0x1c6, 0xa, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x5, 
       0x2e, 0x1cb, 0xa, 0x2e, 0x3, 0x2e, 0x7, 0x2e, 0x1ce, 0xa, 0x2e, 0xc, 
       0x2e, 0xe, 0x2e, 0x1d1, 0xb, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 
       0x3, 0x30, 0x6, 0x30, 0x1d7, 0xa, 0x30, 0xd, 0x30, 0xe, 0x30, 0x1d8, 
       0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 
       0x5, 0x31, 0x1e1, 0xa, 0x31, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 
       0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 
       0x32, 0x7, 0x32, 0x1ed, 0xa, 0x32, 0xc, 0x32, 0xe, 0x32, 0x1f0, 0xb, 
       0x32, 0x5, 0x32, 0x1f2, 0xa, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 
       0x3, 0x32, 0x7, 0x32, 0x1f8, 0xa, 0x32, 0xc, 0x32, 0xe, 0x32, 0x1fb, 
       0xb, 0x32, 0x5, 0x32, 0x1fd, 0xa, 0x32, 0x7, 0x32, 0x1ff, 0xa, 0x32, 
       0xc, 0x32, 0xe, 0x32, 0x202, 0xb, 0x32, 0x3, 0x32, 0x3, 0x32, 0x5, 
       0x32, 0x206, 0xa, 0x32, 0x3, 0x33, 0x3, 0x33, 0x7, 0x33, 0x20a, 0xa, 
       0x33, 0xc, 0x33, 0xe, 0x33, 0x20d, 0xb, 0x33, 0x3, 0x33, 0x3, 0x33, 
       0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x5, 0x34, 0x215, 0xa, 
       0x34, 0x3, 0x35, 0x5, 0x35, 0x218, 0xa, 0x35, 0x3, 0x36, 0x3, 0x36, 
       0x7, 0x36, 0x21c, 0xa, 0x36, 0xc, 0x36, 0xe, 0x36, 0x21f, 0xb, 0x36, 
       0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x223, 0xa, 0x36, 0x3, 0x37, 0x3, 
       0x37, 0x7, 0x37, 0x227, 0xa, 0x37, 0xc, 0x37, 0xe, 0x37, 0x22a, 0xb, 
       0x37, 0x3, 0x37, 0x3, 0x37, 0x5, 0x37, 0x22e, 0xa, 0x37, 0x3, 0x38, 
       0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x5, 0x38, 0x234, 0xa, 0x38, 0x3, 
       0x39, 0x3, 0x39, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 
       0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 0x23f, 0xa, 0x3a, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 
       0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3c, 0x3, 0x3c, 0x7, 0x3c, 
       0x24d, 0xa, 0x3c, 0xc, 0x3c, 0xe, 0x3c, 0x250, 0xb, 0x3c, 0x3, 0x3c, 
       0x3, 0x3c, 0x5, 0x3c, 0x254, 0xa, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 0x3, 
       0x3d, 0x3, 0x3d, 0x5, 0x3d, 0x25a, 0xa, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 
       0x3, 0x3f, 0x3, 0x3f, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 
       0x263, 0xa, 0x40, 0xc, 0x40, 0xe, 0x40, 0x266, 0xb, 0x40, 0x3, 0x41, 
       0x3, 0x41, 0x5, 0x41, 0x26a, 0xa, 0x41, 0x3, 0x41, 0x3, 0x41, 0x3, 
       0x42, 0x6, 0x42, 0x26f, 0xa, 0x42, 0xd, 0x42, 0xe, 0x42, 0x270, 0x3, 
       0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x5, 0x43, 0x278, 
       0xa, 0x43, 0x3, 0x44, 0x5, 0x44, 0x27b, 0xa, 0x44, 0x3, 0x44, 0x5, 
       0x44, 0x27e, 0xa, 0x44, 0x3, 0x44, 0x3, 0x44, 0x5, 0x44, 0x282, 0xa, 
       0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x6, 
       0x45, 0x289, 0xa, 0x45, 0xd, 0x45, 0xe, 0x45, 0x28a, 0x3, 0x46, 0x5, 
       0x46, 0x28e, 0xa, 0x46, 0x3, 0x46, 0x3, 0x46, 0x5, 0x46, 0x292, 0xa, 
       0x46, 0x3, 0x46, 0x3, 0x46, 0x5, 0x46, 0x296, 0xa, 0x46, 0x3, 0x46, 
       0x2, 0x3, 0x40, 0x47, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 
       0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 
       0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 
       0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 
       0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 
       0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e, 0x80, 
       0x82, 0x84, 0x86, 0x88, 0x8a, 0x2, 0xc, 0x4, 0x2, 0x21, 0x21, 0x23, 
       0x23, 0x4, 0x2, 0x22, 0x22, 0x2c, 0x2d, 0x3, 0x2, 0x24, 0x26, 0x4, 
       0x2, 0x20, 0x20, 0x22, 0x22, 0x3, 0x2, 0x1e, 0x1f, 0x3, 0x2, 0x1a, 
       0x1d, 0x3, 0x2, 0x3d, 0x3e, 0x3, 0x2, 0x32, 0x3c, 0x7, 0x2, 0x4, 
       0x4, 0x7, 0x7, 0xa, 0xb, 0xd, 0xe, 0x10, 0x11, 0x3, 0x2, 0x14, 0x15, 
       0x2, 0x2ac, 0x2, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x4, 0x9c, 0x3, 0x2, 0x2, 
       0x2, 0x6, 0xac, 0x3, 0x2, 0x2, 0x2, 0x8, 0xae, 0x3, 0x2, 0x2, 0x2, 
       0xa, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xc, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xe, 
       0xbb, 0x3, 0x2, 0x2, 0x2, 0x10, 0xc4, 0x3, 0x2, 0x2, 0x2, 0x12, 0xc6, 
       0x3, 0x2, 0x2, 0x2, 0x14, 0xcf, 0x3, 0x2, 0x2, 0x2, 0x16, 0xd1, 0x3, 
       0x2, 0x2, 0x2, 0x18, 0xda, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xdc, 0x3, 0x2, 
       0x2, 0x2, 0x1c, 0xe5, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xe7, 0x3, 0x2, 0x2, 
       0x2, 0x20, 0xf0, 0x3, 0x2, 0x2, 0x2, 0x22, 0xf8, 0x3, 0x2, 0x2, 0x2, 
       0x24, 0x100, 0x3, 0x2, 0x2, 0x2, 0x26, 0x108, 0x3, 0x2, 0x2, 0x2, 
       0x28, 0x110, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x118, 0x3, 0x2, 0x2, 0x2, 
       0x2c, 0x126, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x128, 0x3, 0x2, 0x2, 0x2, 
       0x30, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x32, 0x132, 0x3, 0x2, 0x2, 0x2, 
       0x34, 0x135, 0x3, 0x2, 0x2, 0x2, 0x36, 0x13b, 0x3, 0x2, 0x2, 0x2, 
       0x38, 0x143, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x14a, 0x3, 0x2, 0x2, 0x2, 
       0x3c, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x153, 0x3, 0x2, 0x2, 0x2, 
       0x40, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x42, 0x176, 0x3, 0x2, 0x2, 0x2, 
       0x44, 0x186, 0x3, 0x2, 0x2, 0x2, 0x46, 0x189, 0x3, 0x2, 0x2, 0x2, 
       0x48, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x197, 0x3, 0x2, 0x2, 0x2, 
       0x4c, 0x19c, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x1a5, 0x3, 0x2, 0x2, 0x2, 
       0x50, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x52, 0x1b1, 0x3, 0x2, 0x2, 0x2, 
       0x54, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x56, 0x1ba, 0x3, 0x2, 0x2, 0x2, 
       0x58, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x1c5, 0x3, 0x2, 0x2, 0x2, 
       0x5c, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x1d6, 0x3, 0x2, 0x2, 0x2, 
       0x60, 0x1e0, 0x3, 0x2, 0x2, 0x2, 0x62, 0x205, 0x3, 0x2, 0x2, 0x2, 
       0x64, 0x207, 0x3, 0x2, 0x2, 0x2, 0x66, 0x214, 0x3, 0x2, 0x2, 0x2, 
       0x68, 0x217, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x222, 0x3, 0x2, 0x2, 0x2, 
       0x6c, 0x22d, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x233, 0x3, 0x2, 0x2, 0x2, 
       0x70, 0x235, 0x3, 0x2, 0x2, 0x2, 0x72, 0x237, 0x3, 0x2, 0x2, 0x2, 
       0x74, 0x240, 0x3, 0x2, 0x2, 0x2, 0x76, 0x253, 0x3, 0x2, 0x2, 0x2, 
       0x78, 0x259, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x25b, 0x3, 0x2, 0x2, 0x2, 
       0x7c, 0x25d, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x25f, 0x3, 0x2, 0x2, 0x2, 
       0x80, 0x267, 0x3, 0x2, 0x2, 0x2, 0x82, 0x26e, 0x3, 0x2, 0x2, 0x2, 
       0x84, 0x277, 0x3, 0x2, 0x2, 0x2, 0x86, 0x27d, 0x3, 0x2, 0x2, 0x2, 
       0x88, 0x288, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x295, 0x3, 0x2, 0x2, 0x2, 
       0x8c, 0x8e, 0x5, 0x82, 0x42, 0x2, 0x8d, 0x8c, 0x3, 0x2, 0x2, 0x2, 
       0x8d, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x8f, 
       0x90, 0x7, 0x2, 0x2, 0x3, 0x90, 0x3, 0x3, 0x2, 0x2, 0x2, 0x91, 0x9d, 
       0x7, 0x42, 0x2, 0x2, 0x92, 0x9d, 0x5, 0x8a, 0x46, 0x2, 0x93, 0x95, 
       0x7, 0x47, 0x2, 0x2, 0x94, 0x93, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 
       0x3, 0x2, 0x2, 0x2, 0x96, 0x94, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 0x3, 
       0x2, 0x2, 0x2, 0x97, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x7, 0x14, 
       0x2, 0x2, 0x99, 0x9a, 0x5, 0x30, 0x19, 0x2, 0x9a, 0x9b, 0x7, 0x15, 
       0x2, 0x2, 0x9b, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x91, 0x3, 0x2, 0x2, 
       0x2, 0x9c, 0x92, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x94, 0x3, 0x2, 0x2, 0x2, 
       0x9c, 0x98, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x5, 0x3, 0x2, 0x2, 0x2, 0x9e, 
       0xa0, 0x9, 0x2, 0x2, 0x2, 0x9f, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa3, 
       0x3, 0x2, 0x2, 0x2, 0xa1, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0x3, 
       0x2, 0x2, 0x2, 0xa2, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa1, 0x3, 0x2, 
       0x2, 0x2, 0xa4, 0xaa, 0x5, 0x4, 0x3, 0x2, 0xa5, 0xa6, 0x5, 0xa, 0x6, 
       0x2, 0xa6, 0xa7, 0x5, 0x6, 0x4, 0x2, 0xa7, 0xaa, 0x3, 0x2, 0x2, 0x2, 
       0xa8, 0xaa, 0x5, 0x54, 0x2b, 0x2, 0xa9, 0xa4, 0x3, 0x2, 0x2, 0x2, 
       0xa9, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xaa, 
       0xad, 0x3, 0x2, 0x2, 0x2, 0xab, 0xad, 0x5, 0x8, 0x5, 0x2, 0xac, 0xa1, 
       0x3, 0x2, 0x2, 0x2, 0xac, 0xab, 0x3, 0x2, 0x2, 0x2, 0xad, 0x7, 0x3, 
       0x2, 0x2, 0x2, 0xae, 0xb3, 0x5, 0x4, 0x3, 0x2, 0xaf, 0xb0, 0x7, 0x16, 
       0x2, 0x2, 0xb0, 0xb1, 0x5, 0x4, 0x3, 0x2, 0xb1, 0xb2, 0x7, 0x17, 
       0x2, 0x2, 0xb2, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xaf, 0x3, 0x2, 0x2, 
       0x2, 0xb4, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb3, 0x3, 0x2, 0x2, 0x2, 
       0xb5, 0xb6, 0x3, 0x2, 0x2, 0x2, 0xb6, 0x9, 0x3, 0x2, 0x2, 0x2, 0xb7, 
       0xb8, 0x9, 0x3, 0x2, 0x2, 0xb8, 0xb, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xba, 
       0x9, 0x4, 0x2, 0x2, 0xba, 0xd, 0x3, 0x2, 0x2, 0x2, 0xbb, 0xc1, 0x5, 
       0x6, 0x4, 0x2, 0xbc, 0xbd, 0x5, 0xc, 0x7, 0x2, 0xbd, 0xbe, 0x5, 0x6, 
       0x4, 0x2, 0xbe, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xbc, 0x3, 0x2, 0x2, 
       0x2, 0xc0, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xbf, 0x3, 0x2, 0x2, 0x2, 
       0xc1, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xf, 0x3, 0x2, 0x2, 0x2, 0xc3, 
       0xc1, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x9, 0x5, 0x2, 0x2, 0xc5, 0x11, 
       0x3, 0x2, 0x2, 0x2, 0xc6, 0xcc, 0x5, 0xe, 0x8, 0x2, 0xc7, 0xc8, 0x5, 
       0x10, 0x9, 0x2, 0xc8, 0xc9, 0x5, 0xe, 0x8, 0x2, 0xc9, 0xcb, 0x3, 
       0x2, 0x2, 0x2, 0xca, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xce, 0x3, 0x2, 
       0x2, 0x2, 0xcc, 0xca, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xcd, 0x3, 0x2, 0x2, 
       0x2, 0xcd, 0x13, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcc, 0x3, 0x2, 0x2, 0x2, 
       0xcf, 0xd0, 0x9, 0x6, 0x2, 0x2, 0xd0, 0x15, 0x3, 0x2, 0x2, 0x2, 0xd1, 
       0xd7, 0x5, 0x12, 0xa, 0x2, 0xd2, 0xd3, 0x5, 0x14, 0xb, 0x2, 0xd3, 
       0xd4, 0x5, 0x12, 0xa, 0x2, 0xd4, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd5, 
       0xd2, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd5, 
       0x3, 0x2, 0x2, 0x2, 0xd7, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xd8, 0x17, 0x3, 
       0x2, 0x2, 0x2, 0xd9, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xda, 0xdb, 0x9, 0x7, 
       0x2, 0x2, 0xdb, 0x19, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xe2, 0x5, 0x16, 
       0xc, 0x2, 0xdd, 0xde, 0x5, 0x18, 0xd, 0x2, 0xde, 0xdf, 0x5, 0x16, 
       0xc, 0x2, 0xdf, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xdd, 0x3, 0x2, 0x2, 
       0x2, 0xe1, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe0, 0x3, 0x2, 0x2, 0x2, 
       0xe2, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe3, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xe4, 
       0xe2, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe6, 0x9, 0x8, 0x2, 0x2, 0xe6, 0x1d, 
       0x3, 0x2, 0x2, 0x2, 0xe7, 0xed, 0x5, 0x1a, 0xe, 0x2, 0xe8, 0xe9, 
       0x5, 0x1c, 0xf, 0x2, 0xe9, 0xea, 0x5, 0x1a, 0xe, 0x2, 0xea, 0xec, 
       0x3, 0x2, 0x2, 0x2, 0xeb, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xec, 0xef, 0x3, 
       0x2, 0x2, 0x2, 0xed, 0xeb, 0x3, 0x2, 0x2, 0x2, 0xed, 0xee, 0x3, 0x2, 
       0x2, 0x2, 0xee, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xef, 0xed, 0x3, 0x2, 0x2, 
       0x2, 0xf0, 0xf5, 0x5, 0x1e, 0x10, 0x2, 0xf1, 0xf2, 0x7, 0x27, 0x2, 
       0x2, 0xf2, 0xf4, 0x5, 0x1e, 0x10, 0x2, 0xf3, 0xf1, 0x3, 0x2, 0x2, 
       0x2, 0xf4, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf3, 0x3, 0x2, 0x2, 0x2, 
       0xf5, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf6, 0x21, 0x3, 0x2, 0x2, 0x2, 0xf7, 
       0xf5, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xfd, 0x5, 0x20, 0x11, 0x2, 0xf9, 
       0xfa, 0x7, 0x2b, 0x2, 0x2, 0xfa, 0xfc, 0x5, 0x20, 0x11, 0x2, 0xfb, 
       0xf9, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xff, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfb, 
       0x3, 0x2, 0x2, 0x2, 0xfd, 0xfe, 0x3, 0x2, 0x2, 0x2, 0xfe, 0x23, 0x3, 
       0x2, 0x2, 0x2, 0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x100, 0x105, 0x5, 
       0x22, 0x12, 0x2, 0x101, 0x102, 0x7, 0x28, 0x2, 0x2, 0x102, 0x104, 
       0x5, 0x22, 0x12, 0x2, 0x103, 0x101, 0x3, 0x2, 0x2, 0x2, 0x104, 0x107, 
       0x3, 0x2, 0x2, 0x2, 0x105, 0x103, 0x3, 0x2, 0x2, 0x2, 0x105, 0x106, 
       0x3, 0x2, 0x2, 0x2, 0x106, 0x25, 0x3, 0x2, 0x2, 0x2, 0x107, 0x105, 
       0x3, 0x2, 0x2, 0x2, 0x108, 0x10d, 0x5, 0x24, 0x13, 0x2, 0x109, 0x10a, 
       0x7, 0x29, 0x2, 0x2, 0x10a, 0x10c, 0x5, 0x24, 0x13, 0x2, 0x10b, 0x109, 
       0x3, 0x2, 0x2, 0x2, 0x10c, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10b, 
       0x3, 0x2, 0x2, 0x2, 0x10d, 0x10e, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x27, 
       0x3, 0x2, 0x2, 0x2, 0x10f, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x110, 0x115, 
       0x5, 0x26, 0x14, 0x2, 0x111, 0x112, 0x7, 0x2a, 0x2, 0x2, 0x112, 0x114, 
       0x5, 0x26, 0x14, 0x2, 0x113, 0x111, 0x3, 0x2, 0x2, 0x2, 0x114, 0x117, 
       0x3, 0x2, 0x2, 0x2, 0x115, 0x113, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 
       0x3, 0x2, 0x2, 0x2, 0x116, 0x29, 0x3, 0x2, 0x2, 0x2, 0x117, 0x115, 
       0x3, 0x2, 0x2, 0x2, 0x118, 0x11e, 0x5, 0x28, 0x15, 0x2, 0x119, 0x11a, 
       0x7, 0x2e, 0x2, 0x2, 0x11a, 0x11b, 0x5, 0x30, 0x19, 0x2, 0x11b, 0x11c, 
       0x7, 0x2f, 0x2, 0x2, 0x11c, 0x11d, 0x5, 0x2a, 0x16, 0x2, 0x11d, 0x11f, 
       0x3, 0x2, 0x2, 0x2, 0x11e, 0x119, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x11f, 
       0x3, 0x2, 0x2, 0x2, 0x11f, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x120, 0x127, 
       0x5, 0x2a, 0x16, 0x2, 0x121, 0x122, 0x5, 0x6, 0x4, 0x2, 0x122, 0x123, 
       0x5, 0x2e, 0x18, 0x2, 0x123, 0x124, 0x5, 0x2c, 0x17, 0x2, 0x124, 
       0x127, 0x3, 0x2, 0x2, 0x2, 0x125, 0x127, 0x7, 0x45, 0x2, 0x2, 0x126, 
       0x120, 0x3, 0x2, 0x2, 0x2, 0x126, 0x121, 0x3, 0x2, 0x2, 0x2, 0x126, 
       0x125, 0x3, 0x2, 0x2, 0x2, 0x127, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x128, 
       0x129, 0x9, 0x9, 0x2, 0x2, 0x129, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x12a, 
       0x12f, 0x5, 0x2c, 0x17, 0x2, 0x12b, 0x12c, 0x7, 0x31, 0x2, 0x2, 0x12c, 
       0x12e, 0x5, 0x2c, 0x17, 0x2, 0x12d, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x12e, 
       0x131, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x12f, 
       0x130, 0x3, 0x2, 0x2, 0x2, 0x130, 0x31, 0x3, 0x2, 0x2, 0x2, 0x131, 
       0x12f, 0x3, 0x2, 0x2, 0x2, 0x132, 0x133, 0x5, 0x2a, 0x16, 0x2, 0x133, 
       0x33, 0x3, 0x2, 0x2, 0x2, 0x134, 0x136, 0x7, 0x5, 0x2, 0x2, 0x135, 
       0x134, 0x3, 0x2, 0x2, 0x2, 0x135, 0x136, 0x3, 0x2, 0x2, 0x2, 0x136, 
       0x137, 0x3, 0x2, 0x2, 0x2, 0x137, 0x139, 0x5, 0x3a, 0x1e, 0x2, 0x138, 
       0x13a, 0x5, 0x36, 0x1c, 0x2, 0x139, 0x138, 0x3, 0x2, 0x2, 0x2, 0x139, 
       0x13a, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x35, 0x3, 0x2, 0x2, 0x2, 0x13b, 
       0x140, 0x5, 0x38, 0x1d, 0x2, 0x13c, 0x13d, 0x7, 0x31, 0x2, 0x2, 0x13d, 
       0x13f, 0x5, 0x38, 0x1d, 0x2, 0x13e, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x13f, 
       0x142, 0x3, 0x2, 0x2, 0x2, 0x140, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x140, 
       0x141, 0x3, 0x2, 0x2, 0x2, 0x141, 0x37, 0x3, 0x2, 0x2, 0x2, 0x142, 
       0x140, 0x3, 0x2, 0x2, 0x2, 0x143, 0x146, 0x5, 0x3e, 0x20, 0x2, 0x144, 
       0x145, 0x7, 0x32, 0x2, 0x2, 0x145, 0x147, 0x5, 0x52, 0x2a, 0x2, 0x146, 
       0x144, 0x3, 0x2, 0x2, 0x2, 0x146, 0x147, 0x3, 0x2, 0x2, 0x2, 0x147, 
       0x39, 0x3, 0x2, 0x2, 0x2, 0x148, 0x14b, 0x9, 0xa, 0x2, 0x2, 0x149, 
       0x14b, 0x5, 0x50, 0x29, 0x2, 0x14a, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14a, 
       0x149, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x14c, 
       0x14f, 0x5, 0x3a, 0x1e, 0x2, 0x14d, 0x14f, 0x7, 0x5, 0x2, 0x2, 0x14e, 
       0x14c, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x14f, 
       0x151, 0x3, 0x2, 0x2, 0x2, 0x150, 0x152, 0x5, 0x3c, 0x1f, 0x2, 0x151, 
       0x150, 0x3, 0x2, 0x2, 0x2, 0x151, 0x152, 0x3, 0x2, 0x2, 0x2, 0x152, 
       0x3d, 0x3, 0x2, 0x2, 0x2, 0x153, 0x154, 0x5, 0x40, 0x21, 0x2, 0x154, 
       0x3f, 0x3, 0x2, 0x2, 0x2, 0x155, 0x156, 0x8, 0x21, 0x1, 0x2, 0x156, 
       0x15f, 0x7, 0x42, 0x2, 0x2, 0x157, 0x158, 0x7, 0x14, 0x2, 0x2, 0x158, 
       0x159, 0x5, 0x3e, 0x20, 0x2, 0x159, 0x15a, 0x7, 0x15, 0x2, 0x2, 0x15a, 
       0x15f, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x15c, 0x7, 0x42, 0x2, 0x2, 0x15c, 
       0x15d, 0x7, 0x2f, 0x2, 0x2, 0x15d, 0x15f, 0x7, 0x45, 0x2, 0x2, 0x15e, 
       0x155, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x157, 0x3, 0x2, 0x2, 0x2, 0x15e, 
       0x15b, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x173, 0x3, 0x2, 0x2, 0x2, 0x160, 
       0x162, 0xc, 0x6, 0x2, 0x2, 0x161, 0x163, 0x5, 0x42, 0x22, 0x2, 0x162, 
       0x161, 0x3, 0x2, 0x2, 0x2, 0x163, 0x164, 0x3, 0x2, 0x2, 0x2, 0x164, 
       0x162, 0x3, 0x2, 0x2, 0x2, 0x164, 0x165, 0x3, 0x2, 0x2, 0x2, 0x165, 
       0x172, 0x3, 0x2, 0x2, 0x2, 0x166, 0x167, 0xc, 0x5, 0x2, 0x2, 0x167, 
       0x168, 0x7, 0x14, 0x2, 0x2, 0x168, 0x169, 0x5, 0x46, 0x24, 0x2, 0x169, 
       0x16a, 0x7, 0x15, 0x2, 0x2, 0x16a, 0x172, 0x3, 0x2, 0x2, 0x2, 0x16b, 
       0x16c, 0xc, 0x4, 0x2, 0x2, 0x16c, 0x16e, 0x7, 0x14, 0x2, 0x2, 0x16d, 
       0x16f, 0x5, 0x4c, 0x27, 0x2, 0x16e, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x16e, 
       0x16f, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 0x3, 0x2, 0x2, 0x2, 0x170, 
       0x172, 0x7, 0x15, 0x2, 0x2, 0x171, 0x160, 0x3, 0x2, 0x2, 0x2, 0x171, 
       0x166, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x172, 
       0x175, 0x3, 0x2, 0x2, 0x2, 0x173, 0x171, 0x3, 0x2, 0x2, 0x2, 0x173, 
       0x174, 0x3, 0x2, 0x2, 0x2, 0x174, 0x41, 0x3, 0x2, 0x2, 0x2, 0x175, 
       0x173, 0x3, 0x2, 0x2, 0x2, 0x176, 0x178, 0x7, 0x16, 0x2, 0x2, 0x177, 
       0x179, 0x7, 0x5, 0x2, 0x2, 0x178, 0x177, 0x3, 0x2, 0x2, 0x2, 0x178, 
       0x179, 0x3, 0x2, 0x2, 0x2, 0x179, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x17a, 
       0x17c, 0x5, 0x2c, 0x17, 0x2, 0x17b, 0x17a, 0x3, 0x2, 0x2, 0x2, 0x17b, 
       0x17c, 0x3, 0x2, 0x2, 0x2, 0x17c, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x17d, 
       0x17e, 0x7, 0x17, 0x2, 0x2, 0x17e, 0x43, 0x3, 0x2, 0x2, 0x2, 0x17f, 
       0x185, 0xa, 0xb, 0x2, 0x2, 0x180, 0x181, 0x7, 0x14, 0x2, 0x2, 0x181, 
       0x182, 0x5, 0x44, 0x23, 0x2, 0x182, 0x183, 0x7, 0x15, 0x2, 0x2, 0x183, 
       0x185, 0x3, 0x2, 0x2, 0x2, 0x184, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x184, 
       0x180, 0x3, 0x2, 0x2, 0x2, 0x185, 0x188, 0x3, 0x2, 0x2, 0x2, 0x186, 
       0x184, 0x3, 0x2, 0x2, 0x2, 0x186, 0x187, 0x3, 0x2, 0x2, 0x2, 0x187, 
       0x45, 0x3, 0x2, 0x2, 0x2, 0x188, 0x186, 0x3, 0x2, 0x2, 0x2, 0x189, 
       0x18c, 0x5, 0x48, 0x25, 0x2, 0x18a, 0x18b, 0x7, 0x31, 0x2, 0x2, 0x18b, 
       0x18d, 0x7, 0x41, 0x2, 0x2, 0x18c, 0x18a, 0x3, 0x2, 0x2, 0x2, 0x18c, 
       0x18d, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x47, 0x3, 0x2, 0x2, 0x2, 0x18e, 
       0x193, 0x5, 0x4a, 0x26, 0x2, 0x18f, 0x190, 0x7, 0x31, 0x2, 0x2, 0x190, 
       0x192, 0x5, 0x4a, 0x26, 0x2, 0x191, 0x18f, 0x3, 0x2, 0x2, 0x2, 0x192, 
       0x195, 0x3, 0x2, 0x2, 0x2, 0x193, 0x191, 0x3, 0x2, 0x2, 0x2, 0x193, 
       0x194, 0x3, 0x2, 0x2, 0x2, 0x194, 0x49, 0x3, 0x2, 0x2, 0x2, 0x195, 
       0x193, 0x3, 0x2, 0x2, 0x2, 0x196, 0x198, 0x7, 0x5, 0x2, 0x2, 0x197, 
       0x196, 0x3, 0x2, 0x2, 0x2, 0x197, 0x198, 0x3, 0x2, 0x2, 0x2, 0x198, 
       0x199, 0x3, 0x2, 0x2, 0x2, 0x199, 0x19a, 0x5, 0x3a, 0x1e, 0x2, 0x19a, 
       0x19b, 0x5, 0x3e, 0x20, 0x2, 0x19b, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x19c, 
       0x1a1, 0x7, 0x42, 0x2, 0x2, 0x19d, 0x19e, 0x7, 0x31, 0x2, 0x2, 0x19e, 
       0x1a0, 0x7, 0x42, 0x2, 0x2, 0x19f, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x1a0, 
       0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x1a1, 
       0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x1a3, 
       0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a6, 0x5, 0x3c, 0x1f, 0x2, 0x1a5, 
       0x1a4, 0x3, 0x2, 0x2, 0x2, 0x1a5, 0x1a6, 0x3, 0x2, 0x2, 0x2, 0x1a6, 
       0x4f, 0x3, 0x2, 0x2, 0x2, 0x1a7, 0x1a8, 0x7, 0x42, 0x2, 0x2, 0x1a8, 
       0x51, 0x3, 0x2, 0x2, 0x2, 0x1a9, 0x1b2, 0x5, 0x2c, 0x17, 0x2, 0x1aa, 
       0x1ab, 0x7, 0x18, 0x2, 0x2, 0x1ab, 0x1ad, 0x5, 0x5a, 0x2e, 0x2, 0x1ac, 
       0x1ae, 0x7, 0x31, 0x2, 0x2, 0x1ad, 0x1ac, 0x3, 0x2, 0x2, 0x2, 0x1ad, 
       0x1ae, 0x3, 0x2, 0x2, 0x2, 0x1ae, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1af, 
       0x1b0, 0x7, 0x19, 0x2, 0x2, 0x1b0, 0x1b2, 0x3, 0x2, 0x2, 0x2, 0x1b1, 
       0x1a9, 0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1aa, 0x3, 0x2, 0x2, 0x2, 0x1b2, 
       0x53, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1b4, 0x5, 0x50, 0x29, 0x2, 0x1b4, 
       0x1b6, 0x7, 0x14, 0x2, 0x2, 0x1b5, 0x1b7, 0x5, 0x56, 0x2c, 0x2, 0x1b6, 
       0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b6, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x1b7, 
       0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1b8, 0x1b9, 0x7, 0x15, 0x2, 0x2, 0x1b9, 
       0x55, 0x3, 0x2, 0x2, 0x2, 0x1ba, 0x1bf, 0x5, 0x58, 0x2d, 0x2, 0x1bb, 
       0x1bc, 0x7, 0x31, 0x2, 0x2, 0x1bc, 0x1be, 0x5, 0x58, 0x2d, 0x2, 0x1bd, 
       0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1be, 0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1bf, 
       0x1bd, 0x3, 0x2, 0x2, 0x2, 0x1bf, 0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1c0, 
       0x57, 0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1c2, 
       0x1c3, 0x5, 0x2c, 0x17, 0x2, 0x1c3, 0x59, 0x3, 0x2, 0x2, 0x2, 0x1c4, 
       0x1c6, 0x5, 0x5c, 0x2f, 0x2, 0x1c5, 0x1c4, 0x3, 0x2, 0x2, 0x2, 0x1c5, 
       0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1c6, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x1c7, 
       0x1cf, 0x5, 0x52, 0x2a, 0x2, 0x1c8, 0x1ca, 0x7, 0x31, 0x2, 0x2, 0x1c9, 
       0x1cb, 0x5, 0x5c, 0x2f, 0x2, 0x1ca, 0x1c9, 0x3, 0x2, 0x2, 0x2, 0x1ca, 
       0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1cc, 0x3, 0x2, 0x2, 0x2, 0x1cc, 
       0x1ce, 0x5, 0x52, 0x2a, 0x2, 0x1cd, 0x1c8, 0x3, 0x2, 0x2, 0x2, 0x1ce, 
       0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1cf, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1cf, 
       0x1d0, 0x3, 0x2, 0x2, 0x2, 0x1d0, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x1d1, 
       0x1cf, 0x3, 0x2, 0x2, 0x2, 0x1d2, 0x1d3, 0x5, 0x5e, 0x30, 0x2, 0x1d3, 
       0x1d4, 0x7, 0x32, 0x2, 0x2, 0x1d4, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x1d5, 
       0x1d7, 0x5, 0x60, 0x31, 0x2, 0x1d6, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d7, 
       0x1d8, 0x3, 0x2, 0x2, 0x2, 0x1d8, 0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1d8, 
       0x1d9, 0x3, 0x2, 0x2, 0x2, 0x1d9, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x1da, 
       0x1db, 0x7, 0x16, 0x2, 0x2, 0x1db, 0x1dc, 0x5, 0x32, 0x1a, 0x2, 0x1dc, 
       0x1dd, 0x7, 0x17, 0x2, 0x2, 0x1dd, 0x1e1, 0x3, 0x2, 0x2, 0x2, 0x1de, 
       0x1df, 0x7, 0x40, 0x2, 0x2, 0x1df, 0x1e1, 0x7, 0x42, 0x2, 0x2, 0x1e0, 
       0x1da, 0x3, 0x2, 0x2, 0x2, 0x1e0, 0x1de, 0x3, 0x2, 0x2, 0x2, 0x1e1, 
       0x61, 0x3, 0x2, 0x2, 0x2, 0x1e2, 0x1e3, 0x5, 0x68, 0x35, 0x2, 0x1e3, 
       0x1e4, 0x7, 0x30, 0x2, 0x2, 0x1e4, 0x206, 0x3, 0x2, 0x2, 0x2, 0x1e5, 
       0x206, 0x5, 0x72, 0x3a, 0x2, 0x1e6, 0x206, 0x5, 0x74, 0x3b, 0x2, 
       0x1e7, 0x206, 0x5, 0x80, 0x41, 0x2, 0x1e8, 0x1f1, 0x7, 0x14, 0x2, 
       0x2, 0x1e9, 0x1ee, 0x5, 0x28, 0x15, 0x2, 0x1ea, 0x1eb, 0x7, 0x31, 
       0x2, 0x2, 0x1eb, 0x1ed, 0x5, 0x28, 0x15, 0x2, 0x1ec, 0x1ea, 0x3, 
       0x2, 0x2, 0x2, 0x1ed, 0x1f0, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1ec, 0x3, 
       0x2, 0x2, 0x2, 0x1ee, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1ef, 0x1f2, 0x3, 
       0x2, 0x2, 0x2, 0x1f0, 0x1ee, 0x3, 0x2, 0x2, 0x2, 0x1f1, 0x1e9, 0x3, 
       0x2, 0x2, 0x2, 0x1f1, 0x1f2, 0x3, 0x2, 0x2, 0x2, 0x1f2, 0x200, 0x3, 
       0x2, 0x2, 0x2, 0x1f3, 0x1fc, 0x7, 0x2f, 0x2, 0x2, 0x1f4, 0x1f9, 0x5, 
       0x28, 0x15, 0x2, 0x1f5, 0x1f6, 0x7, 0x31, 0x2, 0x2, 0x1f6, 0x1f8, 
       0x5, 0x28, 0x15, 0x2, 0x1f7, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1f8, 0x1fb, 
       0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1f7, 0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1fa, 
       0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fd, 0x3, 0x2, 0x2, 0x2, 0x1fb, 0x1f9, 
       0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1f4, 0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fd, 
       0x3, 0x2, 0x2, 0x2, 0x1fd, 0x1ff, 0x3, 0x2, 0x2, 0x2, 0x1fe, 0x1f3, 
       0x3, 0x2, 0x2, 0x2, 0x1ff, 0x202, 0x3, 0x2, 0x2, 0x2, 0x200, 0x1fe, 
       0x3, 0x2, 0x2, 0x2, 0x200, 0x201, 0x3, 0x2, 0x2, 0x2, 0x201, 0x203, 
       0x3, 0x2, 0x2, 0x2, 0x202, 0x200, 0x3, 0x2, 0x2, 0x2, 0x203, 0x204, 
       0x7, 0x15, 0x2, 0x2, 0x204, 0x206, 0x7, 0x30, 0x2, 0x2, 0x205, 0x1e2, 
       0x3, 0x2, 0x2, 0x2, 0x205, 0x1e5, 0x3, 0x2, 0x2, 0x2, 0x205, 0x1e6, 
       0x3, 0x2, 0x2, 0x2, 0x205, 0x1e7, 0x3, 0x2, 0x2, 0x2, 0x205, 0x1e8, 
       0x3, 0x2, 0x2, 0x2, 0x206, 0x63, 0x3, 0x2, 0x2, 0x2, 0x207, 0x20b, 
       0x7, 0x18, 0x2, 0x2, 0x208, 0x20a, 0x5, 0x66, 0x34, 0x2, 0x209, 0x208, 
       0x3, 0x2, 0x2, 0x2, 0x20a, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x209, 
       0x3, 0x2, 0x2, 0x2, 0x20b, 0x20c, 0x3, 0x2, 0x2, 0x2, 0x20c, 0x20e, 
       0x3, 0x2, 0x2, 0x2, 0x20d, 0x20b, 0x3, 0x2, 0x2, 0x2, 0x20e, 0x20f, 
       0x7, 0x19, 0x2, 0x2, 0x20f, 0x65, 0x3, 0x2, 0x2, 0x2, 0x210, 0x215, 
       0x5, 0x62, 0x32, 0x2, 0x211, 0x212, 0x5, 0x34, 0x1b, 0x2, 0x212, 
       0x213, 0x7, 0x30, 0x2, 0x2, 0x213, 0x215, 0x3, 0x2, 0x2, 0x2, 0x214, 
       0x210, 0x3, 0x2, 0x2, 0x2, 0x214, 0x211, 0x3, 0x2, 0x2, 0x2, 0x215, 
       0x67, 0x3, 0x2, 0x2, 0x2, 0x216, 0x218, 0x5, 0x30, 0x19, 0x2, 0x217, 
       0x216, 0x3, 0x2, 0x2, 0x2, 0x217, 0x218, 0x3, 0x2, 0x2, 0x2, 0x218, 
       0x69, 0x3, 0x2, 0x2, 0x2, 0x219, 0x21d, 0x7, 0x18, 0x2, 0x2, 0x21a, 
       0x21c, 0x5, 0x6e, 0x38, 0x2, 0x21b, 0x21a, 0x3, 0x2, 0x2, 0x2, 0x21c, 
       0x21f, 0x3, 0x2, 0x2, 0x2, 0x21d, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x21d, 
       0x21e, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x220, 0x3, 0x2, 0x2, 0x2, 0x21f, 
       0x21d, 0x3, 0x2, 0x2, 0x2, 0x220, 0x223, 0x7, 0x19, 0x2, 0x2, 0x221, 
       0x223, 0x5, 0x6e, 0x38, 0x2, 0x222, 0x219, 0x3, 0x2, 0x2, 0x2, 0x222, 
       0x221, 0x3, 0x2, 0x2, 0x2, 0x223, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x224, 
       0x228, 0x7, 0x18, 0x2, 0x2, 0x225, 0x227, 0x5, 0x6e, 0x38, 0x2, 0x226, 
       0x225, 0x3, 0x2, 0x2, 0x2, 0x227, 0x22a, 0x3, 0x2, 0x2, 0x2, 0x228, 
       0x226, 0x3, 0x2, 0x2, 0x2, 0x228, 0x229, 0x3, 0x2, 0x2, 0x2, 0x229, 
       0x22b, 0x3, 0x2, 0x2, 0x2, 0x22a, 0x228, 0x3, 0x2, 0x2, 0x2, 0x22b, 
       0x22e, 0x7, 0x19, 0x2, 0x2, 0x22c, 0x22e, 0x5, 0x6e, 0x38, 0x2, 0x22d, 
       0x224, 0x3, 0x2, 0x2, 0x2, 0x22d, 0x22c, 0x3, 0x2, 0x2, 0x2, 0x22e, 
       0x6d, 0x3, 0x2, 0x2, 0x2, 0x22f, 0x234, 0x5, 0x62, 0x32, 0x2, 0x230, 
       0x231, 0x5, 0x34, 0x1b, 0x2, 0x231, 0x232, 0x7, 0x30, 0x2, 0x2, 0x232, 
       0x234, 0x3, 0x2, 0x2, 0x2, 0x233, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x233, 
       0x230, 0x3, 0x2, 0x2, 0x2, 0x234, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x235, 
       0x236, 0x5, 0x30, 0x19, 0x2, 0x236, 0x71, 0x3, 0x2, 0x2, 0x2, 0x237, 
       0x238, 0x7, 0x9, 0x2, 0x2, 0x238, 0x239, 0x7, 0x14, 0x2, 0x2, 0x239, 
       0x23a, 0x5, 0x70, 0x39, 0x2, 0x23a, 0x23b, 0x7, 0x15, 0x2, 0x2, 0x23b, 
       0x23e, 0x5, 0x6a, 0x36, 0x2, 0x23c, 0x23d, 0x7, 0x6, 0x2, 0x2, 0x23d, 
       0x23f, 0x5, 0x6c, 0x37, 0x2, 0x23e, 0x23c, 0x3, 0x2, 0x2, 0x2, 0x23e, 
       0x23f, 0x3, 0x2, 0x2, 0x2, 0x23f, 0x73, 0x3, 0x2, 0x2, 0x2, 0x240, 
       0x241, 0x7, 0x8, 0x2, 0x2, 0x241, 0x242, 0x7, 0x14, 0x2, 0x2, 0x242, 
       0x243, 0x5, 0x7c, 0x3f, 0x2, 0x243, 0x244, 0x7, 0x30, 0x2, 0x2, 0x244, 
       0x245, 0x5, 0x7a, 0x3e, 0x2, 0x245, 0x246, 0x7, 0x30, 0x2, 0x2, 0x246, 
       0x247, 0x5, 0x7e, 0x40, 0x2, 0x247, 0x248, 0x7, 0x15, 0x2, 0x2, 0x248, 
       0x249, 0x5, 0x76, 0x3c, 0x2, 0x249, 0x75, 0x3, 0x2, 0x2, 0x2, 0x24a, 
       0x24e, 0x7, 0x18, 0x2, 0x2, 0x24b, 0x24d, 0x5, 0x78, 0x3d, 0x2, 0x24c, 
       0x24b, 0x3, 0x2, 0x2, 0x2, 0x24d, 0x250, 0x3, 0x2, 0x2, 0x2, 0x24e, 
       0x24c, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x24f, 0x3, 0x2, 0x2, 0x2, 0x24f, 
       0x251, 0x3, 0x2, 0x2, 0x2, 0x250, 0x24e, 0x3, 0x2, 0x2, 0x2, 0x251, 
       0x254, 0x7, 0x19, 0x2, 0x2, 0x252, 0x254, 0x5, 0x78, 0x3d, 0x2, 0x253, 
       0x24a, 0x3, 0x2, 0x2, 0x2, 0x253, 0x252, 0x3, 0x2, 0x2, 0x2, 0x254, 
       0x77, 0x3, 0x2, 0x2, 0x2, 0x255, 0x25a, 0x5, 0x62, 0x32, 0x2, 0x256, 
       0x257, 0x5, 0x34, 0x1b, 0x2, 0x257, 0x258, 0x7, 0x30, 0x2, 0x2, 0x258, 
       0x25a, 0x3, 0x2, 0x2, 0x2, 0x259, 0x255, 0x3, 0x2, 0x2, 0x2, 0x259, 
       0x256, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x79, 0x3, 0x2, 0x2, 0x2, 0x25b, 
       0x25c, 0x5, 0x2c, 0x17, 0x2, 0x25c, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x25d, 
       0x25e, 0x5, 0x34, 0x1b, 0x2, 0x25e, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x25f, 
       0x264, 0x5, 0x2c, 0x17, 0x2, 0x260, 0x261, 0x7, 0x31, 0x2, 0x2, 0x261, 
       0x263, 0x5, 0x2c, 0x17, 0x2, 0x262, 0x260, 0x3, 0x2, 0x2, 0x2, 0x263, 
       0x266, 0x3, 0x2, 0x2, 0x2, 0x264, 0x262, 0x3, 0x2, 0x2, 0x2, 0x264, 
       0x265, 0x3, 0x2, 0x2, 0x2, 0x265, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x266, 
       0x264, 0x3, 0x2, 0x2, 0x2, 0x267, 0x269, 0x7, 0xc, 0x2, 0x2, 0x268, 
       0x26a, 0x5, 0x30, 0x19, 0x2, 0x269, 0x268, 0x3, 0x2, 0x2, 0x2, 0x269, 
       0x26a, 0x3, 0x2, 0x2, 0x2, 0x26a, 0x26b, 0x3, 0x2, 0x2, 0x2, 0x26b, 
       0x26c, 0x7, 0x30, 0x2, 0x2, 0x26c, 0x81, 0x3, 0x2, 0x2, 0x2, 0x26d, 
       0x26f, 0x5, 0x84, 0x43, 0x2, 0x26e, 0x26d, 0x3, 0x2, 0x2, 0x2, 0x26f, 
       0x270, 0x3, 0x2, 0x2, 0x2, 0x270, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x270, 
       0x271, 0x3, 0x2, 0x2, 0x2, 0x271, 0x83, 0x3, 0x2, 0x2, 0x2, 0x272, 
       0x278, 0x5, 0x86, 0x44, 0x2, 0x273, 0x274, 0x5, 0x34, 0x1b, 0x2, 
       0x274, 0x275, 0x7, 0x30, 0x2, 0x2, 0x275, 0x278, 0x3, 0x2, 0x2, 0x2, 
       0x276, 0x278, 0x7, 0x30, 0x2, 0x2, 0x277, 0x272, 0x3, 0x2, 0x2, 0x2, 
       0x277, 0x273, 0x3, 0x2, 0x2, 0x2, 0x277, 0x276, 0x3, 0x2, 0x2, 0x2, 
       0x278, 0x85, 0x3, 0x2, 0x2, 0x2, 0x279, 0x27b, 0x7, 0x5, 0x2, 0x2, 
       0x27a, 0x279, 0x3, 0x2, 0x2, 0x2, 0x27a, 0x27b, 0x3, 0x2, 0x2, 0x2, 
       0x27b, 0x27c, 0x3, 0x2, 0x2, 0x2, 0x27c, 0x27e, 0x5, 0x3a, 0x1e, 
       0x2, 0x27d, 0x27a, 0x3, 0x2, 0x2, 0x2, 0x27d, 0x27e, 0x3, 0x2, 0x2, 
       0x2, 0x27e, 0x27f, 0x3, 0x2, 0x2, 0x2, 0x27f, 0x281, 0x5, 0x3e, 0x20, 
       0x2, 0x280, 0x282, 0x5, 0x88, 0x45, 0x2, 0x281, 0x280, 0x3, 0x2, 
       0x2, 0x2, 0x281, 0x282, 0x3, 0x2, 0x2, 0x2, 0x282, 0x283, 0x3, 0x2, 
       0x2, 0x2, 0x283, 0x284, 0x5, 0x64, 0x33, 0x2, 0x284, 0x87, 0x3, 0x2, 
       0x2, 0x2, 0x285, 0x286, 0x5, 0x34, 0x1b, 0x2, 0x286, 0x287, 0x7, 
       0x30, 0x2, 0x2, 0x287, 0x289, 0x3, 0x2, 0x2, 0x2, 0x288, 0x285, 0x3, 
       0x2, 0x2, 0x2, 0x289, 0x28a, 0x3, 0x2, 0x2, 0x2, 0x28a, 0x288, 0x3, 
       0x2, 0x2, 0x2, 0x28a, 0x28b, 0x3, 0x2, 0x2, 0x2, 0x28b, 0x89, 0x3, 
       0x2, 0x2, 0x2, 0x28c, 0x28e, 0x7, 0x22, 0x2, 0x2, 0x28d, 0x28c, 0x3, 
       0x2, 0x2, 0x2, 0x28d, 0x28e, 0x3, 0x2, 0x2, 0x2, 0x28e, 0x28f, 0x3, 
       0x2, 0x2, 0x2, 0x28f, 0x296, 0x7, 0x43, 0x2, 0x2, 0x290, 0x292, 0x7, 
       0x22, 0x2, 0x2, 0x291, 0x290, 0x3, 0x2, 0x2, 0x2, 0x291, 0x292, 0x3, 
       0x2, 0x2, 0x2, 0x292, 0x293, 0x3, 0x2, 0x2, 0x2, 0x293, 0x296, 0x7, 
       0x44, 0x2, 0x2, 0x294, 0x296, 0x7, 0x46, 0x2, 0x2, 0x295, 0x28d, 
       0x3, 0x2, 0x2, 0x2, 0x295, 0x291, 0x3, 0x2, 0x2, 0x2, 0x295, 0x294, 
       0x3, 0x2, 0x2, 0x2, 0x296, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x51, 0x8d, 
       0x96, 0x9c, 0xa1, 0xa9, 0xac, 0xb5, 0xc1, 0xcc, 0xd7, 0xe2, 0xed, 
       0xf5, 0xfd, 0x105, 0x10d, 0x115, 0x11e, 0x126, 0x12f, 0x135, 0x139, 
       0x140, 0x146, 0x14a, 0x14e, 0x151, 0x15e, 0x164, 0x16e, 0x171, 0x173, 
       0x178, 0x17b, 0x184, 0x186, 0x18c, 0x193, 0x197, 0x1a1, 0x1a5, 0x1ad, 
       0x1b1, 0x1b6, 0x1bf, 0x1c5, 0x1ca, 0x1cf, 0x1d8, 0x1e0, 0x1ee, 0x1f1, 
       0x1f9, 0x1fc, 0x200, 0x205, 0x20b, 0x214, 0x217, 0x21d, 0x222, 0x228, 
       0x22d, 0x233, 0x23e, 0x24e, 0x253, 0x259, 0x264, 0x269, 0x270, 0x277, 
       0x27a, 0x27d, 0x281, 0x28a, 0x28d, 0x291, 0x295, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

C_grammarParser::Initializer C_grammarParser::_init;
