
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


//----------------- PrimaryExpressionContext ------------------------------------------------------------------

C_grammarParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::Constant() {
  return getToken(C_grammarParser::Constant, 0);
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

C_grammarParser::GenericSelectionContext* C_grammarParser::PrimaryExpressionContext::genericSelection() {
  return getRuleContext<C_grammarParser::GenericSelectionContext>(0);
}

C_grammarParser::CompoundStatementContext* C_grammarParser::PrimaryExpressionContext::compoundStatement() {
  return getRuleContext<C_grammarParser::CompoundStatementContext>(0);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::PrimaryExpressionContext::unaryExpression() {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}

C_grammarParser::TypeNameContext* C_grammarParser::PrimaryExpressionContext::typeName() {
  return getRuleContext<C_grammarParser::TypeNameContext>(0);
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
  enterRule(_localctx, 0, C_grammarParser::RulePrimaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(207);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(174);
      match(C_grammarParser::Identifier);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(175);
      match(C_grammarParser::Constant);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(177); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(176);
        match(C_grammarParser::StringLiteral);
        setState(179); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == C_grammarParser::StringLiteral);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(181);
      match(C_grammarParser::LeftParen);
      setState(182);
      expression();
      setState(183);
      match(C_grammarParser::RightParen);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(185);
      genericSelection();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(187);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::T__0) {
        setState(186);
        match(C_grammarParser::T__0);
      }
      setState(189);
      match(C_grammarParser::LeftParen);
      setState(190);
      compoundStatement();
      setState(191);
      match(C_grammarParser::RightParen);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(193);
      match(C_grammarParser::T__1);
      setState(194);
      match(C_grammarParser::LeftParen);
      setState(195);
      unaryExpression();
      setState(196);
      match(C_grammarParser::Comma);
      setState(197);
      typeName();
      setState(198);
      match(C_grammarParser::RightParen);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(200);
      match(C_grammarParser::T__2);
      setState(201);
      match(C_grammarParser::LeftParen);
      setState(202);
      typeName();
      setState(203);
      match(C_grammarParser::Comma);
      setState(204);
      unaryExpression();
      setState(205);
      match(C_grammarParser::RightParen);
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

//----------------- GenericSelectionContext ------------------------------------------------------------------

C_grammarParser::GenericSelectionContext::GenericSelectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::GenericSelectionContext::Generic() {
  return getToken(C_grammarParser::Generic, 0);
}

tree::TerminalNode* C_grammarParser::GenericSelectionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::GenericSelectionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::GenericSelectionContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}

C_grammarParser::GenericAssocListContext* C_grammarParser::GenericSelectionContext::genericAssocList() {
  return getRuleContext<C_grammarParser::GenericAssocListContext>(0);
}

tree::TerminalNode* C_grammarParser::GenericSelectionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}


size_t C_grammarParser::GenericSelectionContext::getRuleIndex() const {
  return C_grammarParser::RuleGenericSelection;
}

void C_grammarParser::GenericSelectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericSelection(this);
}

void C_grammarParser::GenericSelectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericSelection(this);
}


antlrcpp::Any C_grammarParser::GenericSelectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitGenericSelection(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::GenericSelectionContext* C_grammarParser::genericSelection() {
  GenericSelectionContext *_localctx = _tracker.createInstance<GenericSelectionContext>(_ctx, getState());
  enterRule(_localctx, 2, C_grammarParser::RuleGenericSelection);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    match(C_grammarParser::Generic);
    setState(210);
    match(C_grammarParser::LeftParen);
    setState(211);
    assignmentExpression();
    setState(212);
    match(C_grammarParser::Comma);
    setState(213);
    genericAssocList();
    setState(214);
    match(C_grammarParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericAssocListContext ------------------------------------------------------------------

C_grammarParser::GenericAssocListContext::GenericAssocListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::GenericAssociationContext *> C_grammarParser::GenericAssocListContext::genericAssociation() {
  return getRuleContexts<C_grammarParser::GenericAssociationContext>();
}

C_grammarParser::GenericAssociationContext* C_grammarParser::GenericAssocListContext::genericAssociation(size_t i) {
  return getRuleContext<C_grammarParser::GenericAssociationContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::GenericAssocListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::GenericAssocListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::GenericAssocListContext::getRuleIndex() const {
  return C_grammarParser::RuleGenericAssocList;
}

void C_grammarParser::GenericAssocListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericAssocList(this);
}

void C_grammarParser::GenericAssocListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericAssocList(this);
}


antlrcpp::Any C_grammarParser::GenericAssocListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitGenericAssocList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::GenericAssocListContext* C_grammarParser::genericAssocList() {
  GenericAssocListContext *_localctx = _tracker.createInstance<GenericAssocListContext>(_ctx, getState());
  enterRule(_localctx, 4, C_grammarParser::RuleGenericAssocList);
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
    genericAssociation();
    setState(221);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(217);
      match(C_grammarParser::Comma);
      setState(218);
      genericAssociation();
      setState(223);
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

//----------------- GenericAssociationContext ------------------------------------------------------------------

C_grammarParser::GenericAssociationContext::GenericAssociationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::GenericAssociationContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::GenericAssociationContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

C_grammarParser::TypeNameContext* C_grammarParser::GenericAssociationContext::typeName() {
  return getRuleContext<C_grammarParser::TypeNameContext>(0);
}

tree::TerminalNode* C_grammarParser::GenericAssociationContext::Default() {
  return getToken(C_grammarParser::Default, 0);
}


size_t C_grammarParser::GenericAssociationContext::getRuleIndex() const {
  return C_grammarParser::RuleGenericAssociation;
}

void C_grammarParser::GenericAssociationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGenericAssociation(this);
}

void C_grammarParser::GenericAssociationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGenericAssociation(this);
}


antlrcpp::Any C_grammarParser::GenericAssociationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitGenericAssociation(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::GenericAssociationContext* C_grammarParser::genericAssociation() {
  GenericAssociationContext *_localctx = _tracker.createInstance<GenericAssociationContext>(_ctx, getState());
  enterRule(_localctx, 6, C_grammarParser::RuleGenericAssociation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(226);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::T__0:
      case C_grammarParser::T__3:
      case C_grammarParser::T__4:
      case C_grammarParser::T__5:
      case C_grammarParser::T__6:
      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Double:
      case C_grammarParser::Enum:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Restrict:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Struct:
      case C_grammarParser::Union:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::Volatile:
      case C_grammarParser::Atomic:
      case C_grammarParser::Bool:
      case C_grammarParser::Complex:
      case C_grammarParser::Identifier: {
        setState(224);
        typeName();
        break;
      }

      case C_grammarParser::Default: {
        setState(225);
        match(C_grammarParser::Default);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(228);
    match(C_grammarParser::Colon);
    setState(229);
    assignmentExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixExpressionContext ------------------------------------------------------------------

C_grammarParser::PostfixExpressionContext::PostfixExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::PostfixExpressionContext::primaryExpression() {
  return getRuleContext<C_grammarParser::PrimaryExpressionContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::PostfixExpressionContext::LeftParen() {
  return getTokens(C_grammarParser::LeftParen);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::LeftParen(size_t i) {
  return getToken(C_grammarParser::LeftParen, i);
}

C_grammarParser::TypeNameContext* C_grammarParser::PostfixExpressionContext::typeName() {
  return getRuleContext<C_grammarParser::TypeNameContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::PostfixExpressionContext::RightParen() {
  return getTokens(C_grammarParser::RightParen);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::RightParen(size_t i) {
  return getToken(C_grammarParser::RightParen, i);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

C_grammarParser::InitializerListContext* C_grammarParser::PostfixExpressionContext::initializerList() {
  return getRuleContext<C_grammarParser::InitializerListContext>(0);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<tree::TerminalNode *> C_grammarParser::PostfixExpressionContext::LeftBracket() {
  return getTokens(C_grammarParser::LeftBracket);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::LeftBracket(size_t i) {
  return getToken(C_grammarParser::LeftBracket, i);
}

std::vector<C_grammarParser::ExpressionContext *> C_grammarParser::PostfixExpressionContext::expression() {
  return getRuleContexts<C_grammarParser::ExpressionContext>();
}

C_grammarParser::ExpressionContext* C_grammarParser::PostfixExpressionContext::expression(size_t i) {
  return getRuleContext<C_grammarParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::PostfixExpressionContext::RightBracket() {
  return getTokens(C_grammarParser::RightBracket);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::RightBracket(size_t i) {
  return getToken(C_grammarParser::RightBracket, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::PostfixExpressionContext::Identifier() {
  return getTokens(C_grammarParser::Identifier);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::Identifier(size_t i) {
  return getToken(C_grammarParser::Identifier, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::PostfixExpressionContext::Dot() {
  return getTokens(C_grammarParser::Dot);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::Dot(size_t i) {
  return getToken(C_grammarParser::Dot, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::PostfixExpressionContext::Arrow() {
  return getTokens(C_grammarParser::Arrow);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::Arrow(size_t i) {
  return getToken(C_grammarParser::Arrow, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::PostfixExpressionContext::PlusPlus() {
  return getTokens(C_grammarParser::PlusPlus);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::PlusPlus(size_t i) {
  return getToken(C_grammarParser::PlusPlus, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::PostfixExpressionContext::MinusMinus() {
  return getTokens(C_grammarParser::MinusMinus);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::MinusMinus(size_t i) {
  return getToken(C_grammarParser::MinusMinus, i);
}

tree::TerminalNode* C_grammarParser::PostfixExpressionContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}

std::vector<C_grammarParser::ArgumentExpressionListContext *> C_grammarParser::PostfixExpressionContext::argumentExpressionList() {
  return getRuleContexts<C_grammarParser::ArgumentExpressionListContext>();
}

C_grammarParser::ArgumentExpressionListContext* C_grammarParser::PostfixExpressionContext::argumentExpressionList(size_t i) {
  return getRuleContext<C_grammarParser::ArgumentExpressionListContext>(i);
}


size_t C_grammarParser::PostfixExpressionContext::getRuleIndex() const {
  return C_grammarParser::RulePostfixExpression;
}

void C_grammarParser::PostfixExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPostfixExpression(this);
}

void C_grammarParser::PostfixExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPostfixExpression(this);
}


antlrcpp::Any C_grammarParser::PostfixExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitPostfixExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::PostfixExpressionContext* C_grammarParser::postfixExpression() {
  PostfixExpressionContext *_localctx = _tracker.createInstance<PostfixExpressionContext>(_ctx, getState());
  enterRule(_localctx, 8, C_grammarParser::RulePostfixExpression);
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
    setState(245);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(231);
      primaryExpression();
      break;
    }

    case 2: {
      setState(233);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::T__0) {
        setState(232);
        match(C_grammarParser::T__0);
      }
      setState(235);
      match(C_grammarParser::LeftParen);
      setState(236);
      typeName();
      setState(237);
      match(C_grammarParser::RightParen);
      setState(238);
      match(C_grammarParser::LeftBrace);
      setState(239);
      initializerList();
      setState(241);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Comma) {
        setState(240);
        match(C_grammarParser::Comma);
      }
      setState(243);
      match(C_grammarParser::RightBrace);
      break;
    }

    default:
      break;
    }
    setState(261);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 59) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 59)) & ((1ULL << (C_grammarParser::LeftParen - 59))
      | (1ULL << (C_grammarParser::LeftBracket - 59))
      | (1ULL << (C_grammarParser::PlusPlus - 59))
      | (1ULL << (C_grammarParser::MinusMinus - 59))
      | (1ULL << (C_grammarParser::Arrow - 59))
      | (1ULL << (C_grammarParser::Dot - 59)))) != 0)) {
      setState(259);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case C_grammarParser::LeftBracket: {
          setState(247);
          match(C_grammarParser::LeftBracket);
          setState(248);
          expression();
          setState(249);
          match(C_grammarParser::RightBracket);
          break;
        }

        case C_grammarParser::LeftParen: {
          setState(251);
          match(C_grammarParser::LeftParen);
          setState(253);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
            | (1ULL << C_grammarParser::T__1)
            | (1ULL << C_grammarParser::T__2)
            | (1ULL << C_grammarParser::Sizeof)
            | (1ULL << C_grammarParser::Alignof)
            | (1ULL << C_grammarParser::Generic)
            | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
            | (1ULL << (C_grammarParser::PlusPlus - 71))
            | (1ULL << (C_grammarParser::Minus - 71))
            | (1ULL << (C_grammarParser::MinusMinus - 71))
            | (1ULL << (C_grammarParser::Star - 71))
            | (1ULL << (C_grammarParser::And - 71))
            | (1ULL << (C_grammarParser::AndAnd - 71))
            | (1ULL << (C_grammarParser::Not - 71))
            | (1ULL << (C_grammarParser::Tilde - 71))
            | (1ULL << (C_grammarParser::Identifier - 71))
            | (1ULL << (C_grammarParser::Constant - 71))
            | (1ULL << (C_grammarParser::DigitSequence - 71))
            | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
            setState(252);
            argumentExpressionList();
          }
          setState(255);
          match(C_grammarParser::RightParen);
          break;
        }

        case C_grammarParser::Arrow:
        case C_grammarParser::Dot: {
          setState(256);
          _la = _input->LA(1);
          if (!(_la == C_grammarParser::Arrow

          || _la == C_grammarParser::Dot)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(257);
          match(C_grammarParser::Identifier);
          break;
        }

        case C_grammarParser::PlusPlus:
        case C_grammarParser::MinusMinus: {
          setState(258);
          _la = _input->LA(1);
          if (!(_la == C_grammarParser::PlusPlus

          || _la == C_grammarParser::MinusMinus)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(263);
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

//----------------- ArgumentExpressionListContext ------------------------------------------------------------------

C_grammarParser::ArgumentExpressionListContext::ArgumentExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AssignmentExpressionContext *> C_grammarParser::ArgumentExpressionListContext::assignmentExpression() {
  return getRuleContexts<C_grammarParser::AssignmentExpressionContext>();
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ArgumentExpressionListContext::assignmentExpression(size_t i) {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(i);
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
  enterRule(_localctx, 10, C_grammarParser::RuleArgumentExpressionList);
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
    setState(264);
    assignmentExpression();
    setState(269);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(265);
      match(C_grammarParser::Comma);
      setState(266);
      assignmentExpression();
      setState(271);
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

//----------------- UnaryExpressionContext ------------------------------------------------------------------

C_grammarParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::PostfixExpressionContext* C_grammarParser::UnaryExpressionContext::postfixExpression() {
  return getRuleContext<C_grammarParser::PostfixExpressionContext>(0);
}

C_grammarParser::UnaryOperatorContext* C_grammarParser::UnaryExpressionContext::unaryOperator() {
  return getRuleContext<C_grammarParser::UnaryOperatorContext>(0);
}

C_grammarParser::CastExpressionContext* C_grammarParser::UnaryExpressionContext::castExpression() {
  return getRuleContext<C_grammarParser::CastExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::TypeNameContext* C_grammarParser::UnaryExpressionContext::typeName() {
  return getRuleContext<C_grammarParser::TypeNameContext>(0);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::AndAnd() {
  return getToken(C_grammarParser::AndAnd, 0);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> C_grammarParser::UnaryExpressionContext::Sizeof() {
  return getTokens(C_grammarParser::Sizeof);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::Sizeof(size_t i) {
  return getToken(C_grammarParser::Sizeof, i);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::Alignof() {
  return getToken(C_grammarParser::Alignof, 0);
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
  enterRule(_localctx, 12, C_grammarParser::RuleUnaryExpression);
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
    setState(275);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(272);
        _la = _input->LA(1);
        if (!(((((_la - 39) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 39)) & ((1ULL << (C_grammarParser::Sizeof - 39))
          | (1ULL << (C_grammarParser::PlusPlus - 39))
          | (1ULL << (C_grammarParser::MinusMinus - 39)))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        } 
      }
      setState(277);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
    setState(289);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::T__0:
      case C_grammarParser::T__1:
      case C_grammarParser::T__2:
      case C_grammarParser::Generic:
      case C_grammarParser::LeftParen:
      case C_grammarParser::Identifier:
      case C_grammarParser::Constant:
      case C_grammarParser::StringLiteral: {
        setState(278);
        postfixExpression();
        break;
      }

      case C_grammarParser::Plus:
      case C_grammarParser::Minus:
      case C_grammarParser::Star:
      case C_grammarParser::And:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde: {
        setState(279);
        unaryOperator();
        setState(280);
        castExpression();
        break;
      }

      case C_grammarParser::Sizeof:
      case C_grammarParser::Alignof: {
        setState(282);
        _la = _input->LA(1);
        if (!(_la == C_grammarParser::Sizeof

        || _la == C_grammarParser::Alignof)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(283);
        match(C_grammarParser::LeftParen);
        setState(284);
        typeName();
        setState(285);
        match(C_grammarParser::RightParen);
        break;
      }

      case C_grammarParser::AndAnd: {
        setState(287);
        match(C_grammarParser::AndAnd);
        setState(288);
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

//----------------- UnaryOperatorContext ------------------------------------------------------------------

C_grammarParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::And() {
  return getToken(C_grammarParser::And, 0);
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Star() {
  return getToken(C_grammarParser::Star, 0);
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Plus() {
  return getToken(C_grammarParser::Plus, 0);
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
  enterRule(_localctx, 14, C_grammarParser::RuleUnaryOperator);
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
    setState(291);
    _la = _input->LA(1);
    if (!(((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
      | (1ULL << (C_grammarParser::Minus - 71))
      | (1ULL << (C_grammarParser::Star - 71))
      | (1ULL << (C_grammarParser::And - 71))
      | (1ULL << (C_grammarParser::Not - 71))
      | (1ULL << (C_grammarParser::Tilde - 71)))) != 0))) {
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

//----------------- CastExpressionContext ------------------------------------------------------------------

C_grammarParser::CastExpressionContext::CastExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::CastExpressionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::TypeNameContext* C_grammarParser::CastExpressionContext::typeName() {
  return getRuleContext<C_grammarParser::TypeNameContext>(0);
}

tree::TerminalNode* C_grammarParser::CastExpressionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::CastExpressionContext* C_grammarParser::CastExpressionContext::castExpression() {
  return getRuleContext<C_grammarParser::CastExpressionContext>(0);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::CastExpressionContext::unaryExpression() {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::CastExpressionContext::DigitSequence() {
  return getToken(C_grammarParser::DigitSequence, 0);
}


size_t C_grammarParser::CastExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleCastExpression;
}

void C_grammarParser::CastExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCastExpression(this);
}

void C_grammarParser::CastExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCastExpression(this);
}


antlrcpp::Any C_grammarParser::CastExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitCastExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::CastExpressionContext* C_grammarParser::castExpression() {
  CastExpressionContext *_localctx = _tracker.createInstance<CastExpressionContext>(_ctx, getState());
  enterRule(_localctx, 16, C_grammarParser::RuleCastExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(303);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(294);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::T__0) {
        setState(293);
        match(C_grammarParser::T__0);
      }
      setState(296);
      match(C_grammarParser::LeftParen);
      setState(297);
      typeName();
      setState(298);
      match(C_grammarParser::RightParen);
      setState(299);
      castExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(301);
      unaryExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(302);
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

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

C_grammarParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::CastExpressionContext *> C_grammarParser::MultiplicativeExpressionContext::castExpression() {
  return getRuleContexts<C_grammarParser::CastExpressionContext>();
}

C_grammarParser::CastExpressionContext* C_grammarParser::MultiplicativeExpressionContext::castExpression(size_t i) {
  return getRuleContext<C_grammarParser::CastExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::MultiplicativeExpressionContext::Star() {
  return getTokens(C_grammarParser::Star);
}

tree::TerminalNode* C_grammarParser::MultiplicativeExpressionContext::Star(size_t i) {
  return getToken(C_grammarParser::Star, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::MultiplicativeExpressionContext::Div() {
  return getTokens(C_grammarParser::Div);
}

tree::TerminalNode* C_grammarParser::MultiplicativeExpressionContext::Div(size_t i) {
  return getToken(C_grammarParser::Div, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::MultiplicativeExpressionContext::Mod() {
  return getTokens(C_grammarParser::Mod);
}

tree::TerminalNode* C_grammarParser::MultiplicativeExpressionContext::Mod(size_t i) {
  return getToken(C_grammarParser::Mod, i);
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
  enterRule(_localctx, 18, C_grammarParser::RuleMultiplicativeExpression);
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
    castExpression();
    setState(310);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & ((1ULL << (C_grammarParser::Star - 75))
      | (1ULL << (C_grammarParser::Div - 75))
      | (1ULL << (C_grammarParser::Mod - 75)))) != 0)) {
      setState(306);
      _la = _input->LA(1);
      if (!(((((_la - 75) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 75)) & ((1ULL << (C_grammarParser::Star - 75))
        | (1ULL << (C_grammarParser::Div - 75))
        | (1ULL << (C_grammarParser::Mod - 75)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(307);
      castExpression();
      setState(312);
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
  enterRule(_localctx, 20, C_grammarParser::RuleAdditiveExpression);
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
    multiplicativeExpression();
    setState(318);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Plus

    || _la == C_grammarParser::Minus) {
      setState(314);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::Plus

      || _la == C_grammarParser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(315);
      multiplicativeExpression();
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
  enterRule(_localctx, 22, C_grammarParser::RuleShiftExpression);
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
    additiveExpression();
    setState(326);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::LeftShift

    || _la == C_grammarParser::RightShift) {
      setState(322);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::LeftShift

      || _la == C_grammarParser::RightShift)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(323);
      additiveExpression();
      setState(328);
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
    setState(329);
    shiftExpression();
    setState(334);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & ((1ULL << (C_grammarParser::Less - 65))
      | (1ULL << (C_grammarParser::LessEqual - 65))
      | (1ULL << (C_grammarParser::Greater - 65))
      | (1ULL << (C_grammarParser::GreaterEqual - 65)))) != 0)) {
      setState(330);
      _la = _input->LA(1);
      if (!(((((_la - 65) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 65)) & ((1ULL << (C_grammarParser::Less - 65))
        | (1ULL << (C_grammarParser::LessEqual - 65))
        | (1ULL << (C_grammarParser::Greater - 65))
        | (1ULL << (C_grammarParser::GreaterEqual - 65)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(331);
      shiftExpression();
      setState(336);
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
  enterRule(_localctx, 26, C_grammarParser::RuleEqualityExpression);
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
    setState(337);
    relationalExpression();
    setState(342);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Equal

    || _la == C_grammarParser::NotEqual) {
      setState(338);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::Equal

      || _la == C_grammarParser::NotEqual)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(339);
      relationalExpression();
      setState(344);
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
  enterRule(_localctx, 28, C_grammarParser::RuleAndExpression);
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
    setState(345);
    equalityExpression();
    setState(350);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::And) {
      setState(346);
      match(C_grammarParser::And);
      setState(347);
      equalityExpression();
      setState(352);
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
  enterRule(_localctx, 30, C_grammarParser::RuleExclusiveOrExpression);
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
    setState(353);
    andExpression();
    setState(358);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Caret) {
      setState(354);
      match(C_grammarParser::Caret);
      setState(355);
      andExpression();
      setState(360);
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
  enterRule(_localctx, 32, C_grammarParser::RuleInclusiveOrExpression);
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
    setState(361);
    exclusiveOrExpression();
    setState(366);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Or) {
      setState(362);
      match(C_grammarParser::Or);
      setState(363);
      exclusiveOrExpression();
      setState(368);
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
  enterRule(_localctx, 34, C_grammarParser::RuleLogicalAndExpression);
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
    setState(369);
    inclusiveOrExpression();
    setState(374);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::AndAnd) {
      setState(370);
      match(C_grammarParser::AndAnd);
      setState(371);
      inclusiveOrExpression();
      setState(376);
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
  enterRule(_localctx, 36, C_grammarParser::RuleLogicalOrExpression);
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
    setState(377);
    logicalAndExpression();
    setState(382);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::OrOr) {
      setState(378);
      match(C_grammarParser::OrOr);
      setState(379);
      logicalAndExpression();
      setState(384);
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
  enterRule(_localctx, 38, C_grammarParser::RuleConditionalExpression);
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
    setState(385);
    logicalOrExpression();
    setState(391);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Question) {
      setState(386);
      match(C_grammarParser::Question);
      setState(387);
      expression();
      setState(388);
      match(C_grammarParser::Colon);
      setState(389);
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
  enterRule(_localctx, 40, C_grammarParser::RuleAssignmentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(399);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(393);
      conditionalExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(394);
      unaryExpression();
      setState(395);
      assignmentOperator();
      setState(396);
      assignmentExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(398);
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
  enterRule(_localctx, 42, C_grammarParser::RuleAssignmentOperator);
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
    setState(401);
    _la = _input->LA(1);
    if (!(((((_la - 89) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 89)) & ((1ULL << (C_grammarParser::Assign - 89))
      | (1ULL << (C_grammarParser::StarAssign - 89))
      | (1ULL << (C_grammarParser::DivAssign - 89))
      | (1ULL << (C_grammarParser::ModAssign - 89))
      | (1ULL << (C_grammarParser::PlusAssign - 89))
      | (1ULL << (C_grammarParser::MinusAssign - 89))
      | (1ULL << (C_grammarParser::LeftShiftAssign - 89))
      | (1ULL << (C_grammarParser::RightShiftAssign - 89))
      | (1ULL << (C_grammarParser::AndAssign - 89))
      | (1ULL << (C_grammarParser::XorAssign - 89))
      | (1ULL << (C_grammarParser::OrAssign - 89)))) != 0))) {
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
  enterRule(_localctx, 44, C_grammarParser::RuleExpression);
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
    setState(403);
    assignmentExpression();
    setState(408);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(404);
      match(C_grammarParser::Comma);
      setState(405);
      assignmentExpression();
      setState(410);
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
  enterRule(_localctx, 46, C_grammarParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(411);
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

C_grammarParser::StaticAssertDeclarationContext* C_grammarParser::DeclarationContext::staticAssertDeclaration() {
  return getRuleContext<C_grammarParser::StaticAssertDeclarationContext>(0);
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
  enterRule(_localctx, 48, C_grammarParser::RuleDeclaration);
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
      case C_grammarParser::T__0:
      case C_grammarParser::T__3:
      case C_grammarParser::T__4:
      case C_grammarParser::T__5:
      case C_grammarParser::T__6:
      case C_grammarParser::T__7:
      case C_grammarParser::T__8:
      case C_grammarParser::T__9:
      case C_grammarParser::T__11:
      case C_grammarParser::Auto:
      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Double:
      case C_grammarParser::Enum:
      case C_grammarParser::Extern:
      case C_grammarParser::Float:
      case C_grammarParser::Inline:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Register:
      case C_grammarParser::Restrict:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Static:
      case C_grammarParser::Struct:
      case C_grammarParser::Typedef:
      case C_grammarParser::Union:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::Volatile:
      case C_grammarParser::Alignas:
      case C_grammarParser::Atomic:
      case C_grammarParser::Bool:
      case C_grammarParser::Complex:
      case C_grammarParser::Noreturn:
      case C_grammarParser::ThreadLocal:
      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(413);
        declarationSpecifiers();
        setState(415);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 59) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 59)) & ((1ULL << (C_grammarParser::LeftParen - 59))
          | (1ULL << (C_grammarParser::Star - 59))
          | (1ULL << (C_grammarParser::Caret - 59))
          | (1ULL << (C_grammarParser::Identifier - 59)))) != 0)) {
          setState(414);
          initDeclaratorList();
        }
        setState(417);
        match(C_grammarParser::Semi);
        break;
      }

      case C_grammarParser::StaticAssert: {
        enterOuterAlt(_localctx, 2);
        setState(419);
        staticAssertDeclaration();
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
  enterRule(_localctx, 50, C_grammarParser::RuleDeclarationSpecifiers);

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
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(422);
              declarationSpecifier();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(425); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationSpecifiers2Context ------------------------------------------------------------------

C_grammarParser::DeclarationSpecifiers2Context::DeclarationSpecifiers2Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::DeclarationSpecifierContext *> C_grammarParser::DeclarationSpecifiers2Context::declarationSpecifier() {
  return getRuleContexts<C_grammarParser::DeclarationSpecifierContext>();
}

C_grammarParser::DeclarationSpecifierContext* C_grammarParser::DeclarationSpecifiers2Context::declarationSpecifier(size_t i) {
  return getRuleContext<C_grammarParser::DeclarationSpecifierContext>(i);
}


size_t C_grammarParser::DeclarationSpecifiers2Context::getRuleIndex() const {
  return C_grammarParser::RuleDeclarationSpecifiers2;
}

void C_grammarParser::DeclarationSpecifiers2Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarationSpecifiers2(this);
}

void C_grammarParser::DeclarationSpecifiers2Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarationSpecifiers2(this);
}


antlrcpp::Any C_grammarParser::DeclarationSpecifiers2Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclarationSpecifiers2(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclarationSpecifiers2Context* C_grammarParser::declarationSpecifiers2() {
  DeclarationSpecifiers2Context *_localctx = _tracker.createInstance<DeclarationSpecifiers2Context>(_ctx, getState());
  enterRule(_localctx, 52, C_grammarParser::RuleDeclarationSpecifiers2);
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
    setState(428); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(427);
      declarationSpecifier();
      setState(430); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::T__7)
      | (1ULL << C_grammarParser::T__8)
      | (1ULL << C_grammarParser::T__9)
      | (1ULL << C_grammarParser::T__11)
      | (1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Inline)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::Alignas)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::Noreturn)
      | (1ULL << C_grammarParser::ThreadLocal))) != 0) || _la == C_grammarParser::Identifier);
   
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

C_grammarParser::FunctionSpecifierContext* C_grammarParser::DeclarationSpecifierContext::functionSpecifier() {
  return getRuleContext<C_grammarParser::FunctionSpecifierContext>(0);
}

C_grammarParser::AlignmentSpecifierContext* C_grammarParser::DeclarationSpecifierContext::alignmentSpecifier() {
  return getRuleContext<C_grammarParser::AlignmentSpecifierContext>(0);
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
  enterRule(_localctx, 54, C_grammarParser::RuleDeclarationSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(437);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(432);
      storageClassSpecifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(433);
      typeSpecifier(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(434);
      typeQualifier();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(435);
      functionSpecifier();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(436);
      alignmentSpecifier();
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
  enterRule(_localctx, 56, C_grammarParser::RuleInitDeclaratorList);
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
    setState(439);
    initDeclarator();
    setState(444);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(440);
      match(C_grammarParser::Comma);
      setState(441);
      initDeclarator();
      setState(446);
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
  enterRule(_localctx, 58, C_grammarParser::RuleInitDeclarator);
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
    setState(447);
    declarator();
    setState(450);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Assign) {
      setState(448);
      match(C_grammarParser::Assign);
      setState(449);
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

tree::TerminalNode* C_grammarParser::StorageClassSpecifierContext::Extern() {
  return getToken(C_grammarParser::Extern, 0);
}

tree::TerminalNode* C_grammarParser::StorageClassSpecifierContext::Static() {
  return getToken(C_grammarParser::Static, 0);
}

tree::TerminalNode* C_grammarParser::StorageClassSpecifierContext::ThreadLocal() {
  return getToken(C_grammarParser::ThreadLocal, 0);
}

tree::TerminalNode* C_grammarParser::StorageClassSpecifierContext::Auto() {
  return getToken(C_grammarParser::Auto, 0);
}

tree::TerminalNode* C_grammarParser::StorageClassSpecifierContext::Register() {
  return getToken(C_grammarParser::Register, 0);
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
  enterRule(_localctx, 60, C_grammarParser::RuleStorageClassSpecifier);
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
    setState(452);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::ThreadLocal))) != 0))) {
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

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Double() {
  return getToken(C_grammarParser::Double, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Signed() {
  return getToken(C_grammarParser::Signed, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Unsigned() {
  return getToken(C_grammarParser::Unsigned, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Bool() {
  return getToken(C_grammarParser::Bool, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Complex() {
  return getToken(C_grammarParser::Complex, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::AtomicTypeSpecifierContext* C_grammarParser::TypeSpecifierContext::atomicTypeSpecifier() {
  return getRuleContext<C_grammarParser::AtomicTypeSpecifierContext>(0);
}

C_grammarParser::StructOrUnionSpecifierContext* C_grammarParser::TypeSpecifierContext::structOrUnionSpecifier() {
  return getRuleContext<C_grammarParser::StructOrUnionSpecifierContext>(0);
}

C_grammarParser::EnumSpecifierContext* C_grammarParser::TypeSpecifierContext::enumSpecifier() {
  return getRuleContext<C_grammarParser::EnumSpecifierContext>(0);
}

C_grammarParser::TypedefNameContext* C_grammarParser::TypeSpecifierContext::typedefName() {
  return getRuleContext<C_grammarParser::TypedefNameContext>(0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::TypeSpecifierContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::TypeSpecifierContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

C_grammarParser::PointerContext* C_grammarParser::TypeSpecifierContext::pointer() {
  return getRuleContext<C_grammarParser::PointerContext>(0);
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
   return typeSpecifier(0);
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::typeSpecifier(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C_grammarParser::TypeSpecifierContext *_localctx = _tracker.createInstance<TypeSpecifierContext>(_ctx, parentState);
  C_grammarParser::TypeSpecifierContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, C_grammarParser::RuleTypeSpecifier, precedence);

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
    setState(469);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::T__3:
      case C_grammarParser::T__4:
      case C_grammarParser::T__5:
      case C_grammarParser::Char:
      case C_grammarParser::Double:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::Bool:
      case C_grammarParser::Complex: {
        setState(455);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::T__3)
          | (1ULL << C_grammarParser::T__4)
          | (1ULL << C_grammarParser::T__5)
          | (1ULL << C_grammarParser::Char)
          | (1ULL << C_grammarParser::Double)
          | (1ULL << C_grammarParser::Float)
          | (1ULL << C_grammarParser::Int)
          | (1ULL << C_grammarParser::Long)
          | (1ULL << C_grammarParser::Short)
          | (1ULL << C_grammarParser::Signed)
          | (1ULL << C_grammarParser::Unsigned)
          | (1ULL << C_grammarParser::Void)
          | (1ULL << C_grammarParser::Bool)
          | (1ULL << C_grammarParser::Complex))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case C_grammarParser::T__0: {
        setState(456);
        match(C_grammarParser::T__0);
        setState(457);
        match(C_grammarParser::LeftParen);
        setState(458);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::T__3)
          | (1ULL << C_grammarParser::T__4)
          | (1ULL << C_grammarParser::T__5))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(459);
        match(C_grammarParser::RightParen);
        break;
      }

      case C_grammarParser::Atomic: {
        setState(460);
        atomicTypeSpecifier();
        break;
      }

      case C_grammarParser::Struct:
      case C_grammarParser::Union: {
        setState(461);
        structOrUnionSpecifier();
        break;
      }

      case C_grammarParser::Enum: {
        setState(462);
        enumSpecifier();
        break;
      }

      case C_grammarParser::Identifier: {
        setState(463);
        typedefName();
        break;
      }

      case C_grammarParser::T__6: {
        setState(464);
        match(C_grammarParser::T__6);
        setState(465);
        match(C_grammarParser::LeftParen);
        setState(466);
        constantExpression();
        setState(467);
        match(C_grammarParser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(475);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeSpecifierContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleTypeSpecifier);
        setState(471);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(472);
        pointer(); 
      }
      setState(477);
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

//----------------- StructOrUnionSpecifierContext ------------------------------------------------------------------

C_grammarParser::StructOrUnionSpecifierContext::StructOrUnionSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StructOrUnionContext* C_grammarParser::StructOrUnionSpecifierContext::structOrUnion() {
  return getRuleContext<C_grammarParser::StructOrUnionContext>(0);
}

tree::TerminalNode* C_grammarParser::StructOrUnionSpecifierContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

C_grammarParser::StructDeclarationListContext* C_grammarParser::StructOrUnionSpecifierContext::structDeclarationList() {
  return getRuleContext<C_grammarParser::StructDeclarationListContext>(0);
}

tree::TerminalNode* C_grammarParser::StructOrUnionSpecifierContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

tree::TerminalNode* C_grammarParser::StructOrUnionSpecifierContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::StructOrUnionSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleStructOrUnionSpecifier;
}

void C_grammarParser::StructOrUnionSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructOrUnionSpecifier(this);
}

void C_grammarParser::StructOrUnionSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructOrUnionSpecifier(this);
}


antlrcpp::Any C_grammarParser::StructOrUnionSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructOrUnionSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructOrUnionSpecifierContext* C_grammarParser::structOrUnionSpecifier() {
  StructOrUnionSpecifierContext *_localctx = _tracker.createInstance<StructOrUnionSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 64, C_grammarParser::RuleStructOrUnionSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(489);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(478);
      structOrUnion();
      setState(480);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Identifier) {
        setState(479);
        match(C_grammarParser::Identifier);
      }
      setState(482);
      match(C_grammarParser::LeftBrace);
      setState(483);
      structDeclarationList();
      setState(484);
      match(C_grammarParser::RightBrace);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(486);
      structOrUnion();
      setState(487);
      match(C_grammarParser::Identifier);
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

//----------------- StructOrUnionContext ------------------------------------------------------------------

C_grammarParser::StructOrUnionContext::StructOrUnionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::StructOrUnionContext::Struct() {
  return getToken(C_grammarParser::Struct, 0);
}

tree::TerminalNode* C_grammarParser::StructOrUnionContext::Union() {
  return getToken(C_grammarParser::Union, 0);
}


size_t C_grammarParser::StructOrUnionContext::getRuleIndex() const {
  return C_grammarParser::RuleStructOrUnion;
}

void C_grammarParser::StructOrUnionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructOrUnion(this);
}

void C_grammarParser::StructOrUnionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructOrUnion(this);
}


antlrcpp::Any C_grammarParser::StructOrUnionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructOrUnion(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructOrUnionContext* C_grammarParser::structOrUnion() {
  StructOrUnionContext *_localctx = _tracker.createInstance<StructOrUnionContext>(_ctx, getState());
  enterRule(_localctx, 66, C_grammarParser::RuleStructOrUnion);
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
    setState(491);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::Struct

    || _la == C_grammarParser::Union)) {
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

//----------------- StructDeclarationListContext ------------------------------------------------------------------

C_grammarParser::StructDeclarationListContext::StructDeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::StructDeclarationContext *> C_grammarParser::StructDeclarationListContext::structDeclaration() {
  return getRuleContexts<C_grammarParser::StructDeclarationContext>();
}

C_grammarParser::StructDeclarationContext* C_grammarParser::StructDeclarationListContext::structDeclaration(size_t i) {
  return getRuleContext<C_grammarParser::StructDeclarationContext>(i);
}


size_t C_grammarParser::StructDeclarationListContext::getRuleIndex() const {
  return C_grammarParser::RuleStructDeclarationList;
}

void C_grammarParser::StructDeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDeclarationList(this);
}

void C_grammarParser::StructDeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDeclarationList(this);
}


antlrcpp::Any C_grammarParser::StructDeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructDeclarationListContext* C_grammarParser::structDeclarationList() {
  StructDeclarationListContext *_localctx = _tracker.createInstance<StructDeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 68, C_grammarParser::RuleStructDeclarationList);
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
    setState(494); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(493);
      structDeclaration();
      setState(496); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::StaticAssert))) != 0) || _la == C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDeclarationContext ------------------------------------------------------------------

C_grammarParser::StructDeclarationContext::StructDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::StructDeclarationContext::specifierQualifierList() {
  return getRuleContext<C_grammarParser::SpecifierQualifierListContext>(0);
}

tree::TerminalNode* C_grammarParser::StructDeclarationContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

C_grammarParser::StructDeclaratorListContext* C_grammarParser::StructDeclarationContext::structDeclaratorList() {
  return getRuleContext<C_grammarParser::StructDeclaratorListContext>(0);
}

C_grammarParser::StaticAssertDeclarationContext* C_grammarParser::StructDeclarationContext::staticAssertDeclaration() {
  return getRuleContext<C_grammarParser::StaticAssertDeclarationContext>(0);
}


size_t C_grammarParser::StructDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleStructDeclaration;
}

void C_grammarParser::StructDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDeclaration(this);
}

void C_grammarParser::StructDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDeclaration(this);
}


antlrcpp::Any C_grammarParser::StructDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructDeclarationContext* C_grammarParser::structDeclaration() {
  StructDeclarationContext *_localctx = _tracker.createInstance<StructDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 70, C_grammarParser::RuleStructDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(505);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::T__0:
      case C_grammarParser::T__3:
      case C_grammarParser::T__4:
      case C_grammarParser::T__5:
      case C_grammarParser::T__6:
      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Double:
      case C_grammarParser::Enum:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Restrict:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Struct:
      case C_grammarParser::Union:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::Volatile:
      case C_grammarParser::Atomic:
      case C_grammarParser::Bool:
      case C_grammarParser::Complex:
      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(498);
        specifierQualifierList();
        setState(500);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 59) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 59)) & ((1ULL << (C_grammarParser::LeftParen - 59))
          | (1ULL << (C_grammarParser::Star - 59))
          | (1ULL << (C_grammarParser::Caret - 59))
          | (1ULL << (C_grammarParser::Colon - 59))
          | (1ULL << (C_grammarParser::Identifier - 59)))) != 0)) {
          setState(499);
          structDeclaratorList();
        }
        setState(502);
        match(C_grammarParser::Semi);
        break;
      }

      case C_grammarParser::StaticAssert: {
        enterOuterAlt(_localctx, 2);
        setState(504);
        staticAssertDeclaration();
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
  enterRule(_localctx, 72, C_grammarParser::RuleSpecifierQualifierList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(509);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      setState(507);
      typeSpecifier(0);
      break;
    }

    case 2: {
      setState(508);
      typeQualifier();
      break;
    }

    default:
      break;
    }
    setState(512);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      setState(511);
      specifierQualifierList();
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

//----------------- StructDeclaratorListContext ------------------------------------------------------------------

C_grammarParser::StructDeclaratorListContext::StructDeclaratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::StructDeclaratorContext *> C_grammarParser::StructDeclaratorListContext::structDeclarator() {
  return getRuleContexts<C_grammarParser::StructDeclaratorContext>();
}

C_grammarParser::StructDeclaratorContext* C_grammarParser::StructDeclaratorListContext::structDeclarator(size_t i) {
  return getRuleContext<C_grammarParser::StructDeclaratorContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::StructDeclaratorListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::StructDeclaratorListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::StructDeclaratorListContext::getRuleIndex() const {
  return C_grammarParser::RuleStructDeclaratorList;
}

void C_grammarParser::StructDeclaratorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDeclaratorList(this);
}

void C_grammarParser::StructDeclaratorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDeclaratorList(this);
}


antlrcpp::Any C_grammarParser::StructDeclaratorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructDeclaratorList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructDeclaratorListContext* C_grammarParser::structDeclaratorList() {
  StructDeclaratorListContext *_localctx = _tracker.createInstance<StructDeclaratorListContext>(_ctx, getState());
  enterRule(_localctx, 74, C_grammarParser::RuleStructDeclaratorList);
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
    setState(514);
    structDeclarator();
    setState(519);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(515);
      match(C_grammarParser::Comma);
      setState(516);
      structDeclarator();
      setState(521);
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

//----------------- StructDeclaratorContext ------------------------------------------------------------------

C_grammarParser::StructDeclaratorContext::StructDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclaratorContext* C_grammarParser::StructDeclaratorContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::StructDeclaratorContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::StructDeclaratorContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}


size_t C_grammarParser::StructDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleStructDeclarator;
}

void C_grammarParser::StructDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDeclarator(this);
}

void C_grammarParser::StructDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDeclarator(this);
}


antlrcpp::Any C_grammarParser::StructDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructDeclaratorContext* C_grammarParser::structDeclarator() {
  StructDeclaratorContext *_localctx = _tracker.createInstance<StructDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 76, C_grammarParser::RuleStructDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(528);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(522);
      declarator();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(524);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 59) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 59)) & ((1ULL << (C_grammarParser::LeftParen - 59))
        | (1ULL << (C_grammarParser::Star - 59))
        | (1ULL << (C_grammarParser::Caret - 59))
        | (1ULL << (C_grammarParser::Identifier - 59)))) != 0)) {
        setState(523);
        declarator();
      }
      setState(526);
      match(C_grammarParser::Colon);
      setState(527);
      constantExpression();
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

//----------------- EnumSpecifierContext ------------------------------------------------------------------

C_grammarParser::EnumSpecifierContext::EnumSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::EnumSpecifierContext::Enum() {
  return getToken(C_grammarParser::Enum, 0);
}

tree::TerminalNode* C_grammarParser::EnumSpecifierContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

C_grammarParser::EnumeratorListContext* C_grammarParser::EnumSpecifierContext::enumeratorList() {
  return getRuleContext<C_grammarParser::EnumeratorListContext>(0);
}

tree::TerminalNode* C_grammarParser::EnumSpecifierContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

tree::TerminalNode* C_grammarParser::EnumSpecifierContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

tree::TerminalNode* C_grammarParser::EnumSpecifierContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}


size_t C_grammarParser::EnumSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleEnumSpecifier;
}

void C_grammarParser::EnumSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumSpecifier(this);
}

void C_grammarParser::EnumSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumSpecifier(this);
}


antlrcpp::Any C_grammarParser::EnumSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEnumSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EnumSpecifierContext* C_grammarParser::enumSpecifier() {
  EnumSpecifierContext *_localctx = _tracker.createInstance<EnumSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 78, C_grammarParser::RuleEnumSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(543);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(530);
      match(C_grammarParser::Enum);
      setState(532);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Identifier) {
        setState(531);
        match(C_grammarParser::Identifier);
      }
      setState(534);
      match(C_grammarParser::LeftBrace);
      setState(535);
      enumeratorList();
      setState(537);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Comma) {
        setState(536);
        match(C_grammarParser::Comma);
      }
      setState(539);
      match(C_grammarParser::RightBrace);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(541);
      match(C_grammarParser::Enum);
      setState(542);
      match(C_grammarParser::Identifier);
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

//----------------- EnumeratorListContext ------------------------------------------------------------------

C_grammarParser::EnumeratorListContext::EnumeratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::EnumeratorContext *> C_grammarParser::EnumeratorListContext::enumerator() {
  return getRuleContexts<C_grammarParser::EnumeratorContext>();
}

C_grammarParser::EnumeratorContext* C_grammarParser::EnumeratorListContext::enumerator(size_t i) {
  return getRuleContext<C_grammarParser::EnumeratorContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::EnumeratorListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::EnumeratorListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::EnumeratorListContext::getRuleIndex() const {
  return C_grammarParser::RuleEnumeratorList;
}

void C_grammarParser::EnumeratorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumeratorList(this);
}

void C_grammarParser::EnumeratorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumeratorList(this);
}


antlrcpp::Any C_grammarParser::EnumeratorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEnumeratorList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EnumeratorListContext* C_grammarParser::enumeratorList() {
  EnumeratorListContext *_localctx = _tracker.createInstance<EnumeratorListContext>(_ctx, getState());
  enterRule(_localctx, 80, C_grammarParser::RuleEnumeratorList);

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
    setState(545);
    enumerator();
    setState(550);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(546);
        match(C_grammarParser::Comma);
        setState(547);
        enumerator(); 
      }
      setState(552);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumeratorContext ------------------------------------------------------------------

C_grammarParser::EnumeratorContext::EnumeratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::EnumerationConstantContext* C_grammarParser::EnumeratorContext::enumerationConstant() {
  return getRuleContext<C_grammarParser::EnumerationConstantContext>(0);
}

tree::TerminalNode* C_grammarParser::EnumeratorContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::EnumeratorContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}


size_t C_grammarParser::EnumeratorContext::getRuleIndex() const {
  return C_grammarParser::RuleEnumerator;
}

void C_grammarParser::EnumeratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumerator(this);
}

void C_grammarParser::EnumeratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumerator(this);
}


antlrcpp::Any C_grammarParser::EnumeratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEnumerator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EnumeratorContext* C_grammarParser::enumerator() {
  EnumeratorContext *_localctx = _tracker.createInstance<EnumeratorContext>(_ctx, getState());
  enterRule(_localctx, 82, C_grammarParser::RuleEnumerator);
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
    setState(553);
    enumerationConstant();
    setState(556);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Assign) {
      setState(554);
      match(C_grammarParser::Assign);
      setState(555);
      constantExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumerationConstantContext ------------------------------------------------------------------

C_grammarParser::EnumerationConstantContext::EnumerationConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::EnumerationConstantContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::EnumerationConstantContext::getRuleIndex() const {
  return C_grammarParser::RuleEnumerationConstant;
}

void C_grammarParser::EnumerationConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumerationConstant(this);
}

void C_grammarParser::EnumerationConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumerationConstant(this);
}


antlrcpp::Any C_grammarParser::EnumerationConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEnumerationConstant(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EnumerationConstantContext* C_grammarParser::enumerationConstant() {
  EnumerationConstantContext *_localctx = _tracker.createInstance<EnumerationConstantContext>(_ctx, getState());
  enterRule(_localctx, 84, C_grammarParser::RuleEnumerationConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(558);
    match(C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomicTypeSpecifierContext ------------------------------------------------------------------

C_grammarParser::AtomicTypeSpecifierContext::AtomicTypeSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::AtomicTypeSpecifierContext::Atomic() {
  return getToken(C_grammarParser::Atomic, 0);
}

tree::TerminalNode* C_grammarParser::AtomicTypeSpecifierContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::TypeNameContext* C_grammarParser::AtomicTypeSpecifierContext::typeName() {
  return getRuleContext<C_grammarParser::TypeNameContext>(0);
}

tree::TerminalNode* C_grammarParser::AtomicTypeSpecifierContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}


size_t C_grammarParser::AtomicTypeSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleAtomicTypeSpecifier;
}

void C_grammarParser::AtomicTypeSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtomicTypeSpecifier(this);
}

void C_grammarParser::AtomicTypeSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtomicTypeSpecifier(this);
}


antlrcpp::Any C_grammarParser::AtomicTypeSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAtomicTypeSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AtomicTypeSpecifierContext* C_grammarParser::atomicTypeSpecifier() {
  AtomicTypeSpecifierContext *_localctx = _tracker.createInstance<AtomicTypeSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 86, C_grammarParser::RuleAtomicTypeSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(560);
    match(C_grammarParser::Atomic);
    setState(561);
    match(C_grammarParser::LeftParen);
    setState(562);
    typeName();
    setState(563);
    match(C_grammarParser::RightParen);
   
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

tree::TerminalNode* C_grammarParser::TypeQualifierContext::Restrict() {
  return getToken(C_grammarParser::Restrict, 0);
}

tree::TerminalNode* C_grammarParser::TypeQualifierContext::Volatile() {
  return getToken(C_grammarParser::Volatile, 0);
}

tree::TerminalNode* C_grammarParser::TypeQualifierContext::Atomic() {
  return getToken(C_grammarParser::Atomic, 0);
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
  enterRule(_localctx, 88, C_grammarParser::RuleTypeQualifier);
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
    setState(565);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::Atomic))) != 0))) {
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

//----------------- FunctionSpecifierContext ------------------------------------------------------------------

C_grammarParser::FunctionSpecifierContext::FunctionSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::FunctionSpecifierContext::Inline() {
  return getToken(C_grammarParser::Inline, 0);
}

tree::TerminalNode* C_grammarParser::FunctionSpecifierContext::Noreturn() {
  return getToken(C_grammarParser::Noreturn, 0);
}

C_grammarParser::GccAttributeSpecifierContext* C_grammarParser::FunctionSpecifierContext::gccAttributeSpecifier() {
  return getRuleContext<C_grammarParser::GccAttributeSpecifierContext>(0);
}

tree::TerminalNode* C_grammarParser::FunctionSpecifierContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::FunctionSpecifierContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

tree::TerminalNode* C_grammarParser::FunctionSpecifierContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}


size_t C_grammarParser::FunctionSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleFunctionSpecifier;
}

void C_grammarParser::FunctionSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionSpecifier(this);
}

void C_grammarParser::FunctionSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionSpecifier(this);
}


antlrcpp::Any C_grammarParser::FunctionSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitFunctionSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::FunctionSpecifierContext* C_grammarParser::functionSpecifier() {
  FunctionSpecifierContext *_localctx = _tracker.createInstance<FunctionSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 90, C_grammarParser::RuleFunctionSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(573);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::T__7:
      case C_grammarParser::T__8:
      case C_grammarParser::Inline:
      case C_grammarParser::Noreturn: {
        enterOuterAlt(_localctx, 1);
        setState(567);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::T__7)
          | (1ULL << C_grammarParser::T__8)
          | (1ULL << C_grammarParser::Inline)
          | (1ULL << C_grammarParser::Noreturn))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case C_grammarParser::T__11: {
        enterOuterAlt(_localctx, 2);
        setState(568);
        gccAttributeSpecifier();
        break;
      }

      case C_grammarParser::T__9: {
        enterOuterAlt(_localctx, 3);
        setState(569);
        match(C_grammarParser::T__9);
        setState(570);
        match(C_grammarParser::LeftParen);
        setState(571);
        match(C_grammarParser::Identifier);
        setState(572);
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

//----------------- AlignmentSpecifierContext ------------------------------------------------------------------

C_grammarParser::AlignmentSpecifierContext::AlignmentSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::AlignmentSpecifierContext::Alignas() {
  return getToken(C_grammarParser::Alignas, 0);
}

tree::TerminalNode* C_grammarParser::AlignmentSpecifierContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::AlignmentSpecifierContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::TypeNameContext* C_grammarParser::AlignmentSpecifierContext::typeName() {
  return getRuleContext<C_grammarParser::TypeNameContext>(0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::AlignmentSpecifierContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}


size_t C_grammarParser::AlignmentSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleAlignmentSpecifier;
}

void C_grammarParser::AlignmentSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlignmentSpecifier(this);
}

void C_grammarParser::AlignmentSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlignmentSpecifier(this);
}


antlrcpp::Any C_grammarParser::AlignmentSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAlignmentSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AlignmentSpecifierContext* C_grammarParser::alignmentSpecifier() {
  AlignmentSpecifierContext *_localctx = _tracker.createInstance<AlignmentSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 92, C_grammarParser::RuleAlignmentSpecifier);

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
    match(C_grammarParser::Alignas);
    setState(576);
    match(C_grammarParser::LeftParen);
    setState(579);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      setState(577);
      typeName();
      break;
    }

    case 2: {
      setState(578);
      constantExpression();
      break;
    }

    default:
      break;
    }
    setState(581);
    match(C_grammarParser::RightParen);
   
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

C_grammarParser::PointerContext* C_grammarParser::DeclaratorContext::pointer() {
  return getRuleContext<C_grammarParser::PointerContext>(0);
}

std::vector<C_grammarParser::GccDeclaratorExtensionContext *> C_grammarParser::DeclaratorContext::gccDeclaratorExtension() {
  return getRuleContexts<C_grammarParser::GccDeclaratorExtensionContext>();
}

C_grammarParser::GccDeclaratorExtensionContext* C_grammarParser::DeclaratorContext::gccDeclaratorExtension(size_t i) {
  return getRuleContext<C_grammarParser::GccDeclaratorExtensionContext>(i);
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
  enterRule(_localctx, 94, C_grammarParser::RuleDeclarator);
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
    setState(584);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Star

    || _la == C_grammarParser::Caret) {
      setState(583);
      pointer();
    }
    setState(586);
    directDeclarator(0);
    setState(590);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(587);
        gccDeclaratorExtension(); 
      }
      setState(592);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    }
   
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

C_grammarParser::PointerContext* C_grammarParser::DirectDeclaratorContext::pointer() {
  return getRuleContext<C_grammarParser::PointerContext>(0);
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::DirectDeclaratorContext::directDeclarator() {
  return getRuleContext<C_grammarParser::DirectDeclaratorContext>(0);
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::DirectDeclaratorContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
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

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::Static() {
  return getToken(C_grammarParser::Static, 0);
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
  size_t startState = 96;
  enterRecursionRule(_localctx, 96, C_grammarParser::RuleDirectDeclarator, precedence);

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
    setState(610);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(594);
      match(C_grammarParser::Identifier);
      break;
    }

    case 2: {
      setState(595);
      match(C_grammarParser::LeftParen);
      setState(596);
      declarator();
      setState(597);
      match(C_grammarParser::RightParen);
      break;
    }

    case 3: {
      setState(599);
      match(C_grammarParser::Identifier);
      setState(600);
      match(C_grammarParser::Colon);
      setState(601);
      match(C_grammarParser::DigitSequence);
      break;
    }

    case 4: {
      setState(602);
      match(C_grammarParser::LeftParen);
      setState(604);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
        | (1ULL << C_grammarParser::T__3)
        | (1ULL << C_grammarParser::T__4)
        | (1ULL << C_grammarParser::T__5)
        | (1ULL << C_grammarParser::T__6)
        | (1ULL << C_grammarParser::Char)
        | (1ULL << C_grammarParser::Double)
        | (1ULL << C_grammarParser::Enum)
        | (1ULL << C_grammarParser::Float)
        | (1ULL << C_grammarParser::Int)
        | (1ULL << C_grammarParser::Long)
        | (1ULL << C_grammarParser::Short)
        | (1ULL << C_grammarParser::Signed)
        | (1ULL << C_grammarParser::Struct)
        | (1ULL << C_grammarParser::Union)
        | (1ULL << C_grammarParser::Unsigned)
        | (1ULL << C_grammarParser::Void)
        | (1ULL << C_grammarParser::Atomic)
        | (1ULL << C_grammarParser::Bool)
        | (1ULL << C_grammarParser::Complex))) != 0) || _la == C_grammarParser::Identifier) {
        setState(603);
        typeSpecifier(0);
      }
      setState(606);
      pointer();
      setState(607);
      directDeclarator(0);
      setState(608);
      match(C_grammarParser::RightParen);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(657);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(655);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(612);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(613);
          match(C_grammarParser::LeftBracket);
          setState(615);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::Const)
            | (1ULL << C_grammarParser::Restrict)
            | (1ULL << C_grammarParser::Volatile)
            | (1ULL << C_grammarParser::Atomic))) != 0)) {
            setState(614);
            typeQualifierList();
          }
          setState(618);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
            | (1ULL << C_grammarParser::T__1)
            | (1ULL << C_grammarParser::T__2)
            | (1ULL << C_grammarParser::Sizeof)
            | (1ULL << C_grammarParser::Alignof)
            | (1ULL << C_grammarParser::Generic)
            | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
            | (1ULL << (C_grammarParser::PlusPlus - 71))
            | (1ULL << (C_grammarParser::Minus - 71))
            | (1ULL << (C_grammarParser::MinusMinus - 71))
            | (1ULL << (C_grammarParser::Star - 71))
            | (1ULL << (C_grammarParser::And - 71))
            | (1ULL << (C_grammarParser::AndAnd - 71))
            | (1ULL << (C_grammarParser::Not - 71))
            | (1ULL << (C_grammarParser::Tilde - 71))
            | (1ULL << (C_grammarParser::Identifier - 71))
            | (1ULL << (C_grammarParser::Constant - 71))
            | (1ULL << (C_grammarParser::DigitSequence - 71))
            | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
            setState(617);
            assignmentExpression();
          }
          setState(620);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(621);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(622);
          match(C_grammarParser::LeftBracket);
          setState(623);
          match(C_grammarParser::Static);
          setState(625);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::Const)
            | (1ULL << C_grammarParser::Restrict)
            | (1ULL << C_grammarParser::Volatile)
            | (1ULL << C_grammarParser::Atomic))) != 0)) {
            setState(624);
            typeQualifierList();
          }
          setState(627);
          assignmentExpression();
          setState(628);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(630);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(631);
          match(C_grammarParser::LeftBracket);
          setState(632);
          typeQualifierList();
          setState(633);
          match(C_grammarParser::Static);
          setState(634);
          assignmentExpression();
          setState(635);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(637);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(638);
          match(C_grammarParser::LeftBracket);
          setState(640);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::Const)
            | (1ULL << C_grammarParser::Restrict)
            | (1ULL << C_grammarParser::Volatile)
            | (1ULL << C_grammarParser::Atomic))) != 0)) {
            setState(639);
            typeQualifierList();
          }
          setState(642);
          match(C_grammarParser::Star);
          setState(643);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(644);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(645);
          match(C_grammarParser::LeftParen);
          setState(646);
          parameterTypeList();
          setState(647);
          match(C_grammarParser::RightParen);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(649);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(650);
          match(C_grammarParser::LeftParen);
          setState(652);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == C_grammarParser::Identifier) {
            setState(651);
            identifierList();
          }
          setState(654);
          match(C_grammarParser::RightParen);
          break;
        }

        default:
          break;
        } 
      }
      setState(659);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- GccDeclaratorExtensionContext ------------------------------------------------------------------

C_grammarParser::GccDeclaratorExtensionContext::GccDeclaratorExtensionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::GccDeclaratorExtensionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::GccDeclaratorExtensionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

std::vector<tree::TerminalNode *> C_grammarParser::GccDeclaratorExtensionContext::StringLiteral() {
  return getTokens(C_grammarParser::StringLiteral);
}

tree::TerminalNode* C_grammarParser::GccDeclaratorExtensionContext::StringLiteral(size_t i) {
  return getToken(C_grammarParser::StringLiteral, i);
}

C_grammarParser::GccAttributeSpecifierContext* C_grammarParser::GccDeclaratorExtensionContext::gccAttributeSpecifier() {
  return getRuleContext<C_grammarParser::GccAttributeSpecifierContext>(0);
}


size_t C_grammarParser::GccDeclaratorExtensionContext::getRuleIndex() const {
  return C_grammarParser::RuleGccDeclaratorExtension;
}

void C_grammarParser::GccDeclaratorExtensionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGccDeclaratorExtension(this);
}

void C_grammarParser::GccDeclaratorExtensionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGccDeclaratorExtension(this);
}


antlrcpp::Any C_grammarParser::GccDeclaratorExtensionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitGccDeclaratorExtension(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::GccDeclaratorExtensionContext* C_grammarParser::gccDeclaratorExtension() {
  GccDeclaratorExtensionContext *_localctx = _tracker.createInstance<GccDeclaratorExtensionContext>(_ctx, getState());
  enterRule(_localctx, 98, C_grammarParser::RuleGccDeclaratorExtension);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(669);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::T__10: {
        enterOuterAlt(_localctx, 1);
        setState(660);
        match(C_grammarParser::T__10);
        setState(661);
        match(C_grammarParser::LeftParen);
        setState(663); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(662);
          match(C_grammarParser::StringLiteral);
          setState(665); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == C_grammarParser::StringLiteral);
        setState(667);
        match(C_grammarParser::RightParen);
        break;
      }

      case C_grammarParser::T__11: {
        enterOuterAlt(_localctx, 2);
        setState(668);
        gccAttributeSpecifier();
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

//----------------- GccAttributeSpecifierContext ------------------------------------------------------------------

C_grammarParser::GccAttributeSpecifierContext::GccAttributeSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> C_grammarParser::GccAttributeSpecifierContext::LeftParen() {
  return getTokens(C_grammarParser::LeftParen);
}

tree::TerminalNode* C_grammarParser::GccAttributeSpecifierContext::LeftParen(size_t i) {
  return getToken(C_grammarParser::LeftParen, i);
}

C_grammarParser::GccAttributeListContext* C_grammarParser::GccAttributeSpecifierContext::gccAttributeList() {
  return getRuleContext<C_grammarParser::GccAttributeListContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::GccAttributeSpecifierContext::RightParen() {
  return getTokens(C_grammarParser::RightParen);
}

tree::TerminalNode* C_grammarParser::GccAttributeSpecifierContext::RightParen(size_t i) {
  return getToken(C_grammarParser::RightParen, i);
}


size_t C_grammarParser::GccAttributeSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleGccAttributeSpecifier;
}

void C_grammarParser::GccAttributeSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGccAttributeSpecifier(this);
}

void C_grammarParser::GccAttributeSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGccAttributeSpecifier(this);
}


antlrcpp::Any C_grammarParser::GccAttributeSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitGccAttributeSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::GccAttributeSpecifierContext* C_grammarParser::gccAttributeSpecifier() {
  GccAttributeSpecifierContext *_localctx = _tracker.createInstance<GccAttributeSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 100, C_grammarParser::RuleGccAttributeSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(671);
    match(C_grammarParser::T__11);
    setState(672);
    match(C_grammarParser::LeftParen);
    setState(673);
    match(C_grammarParser::LeftParen);
    setState(674);
    gccAttributeList();
    setState(675);
    match(C_grammarParser::RightParen);
    setState(676);
    match(C_grammarParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GccAttributeListContext ------------------------------------------------------------------

C_grammarParser::GccAttributeListContext::GccAttributeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::GccAttributeContext *> C_grammarParser::GccAttributeListContext::gccAttribute() {
  return getRuleContexts<C_grammarParser::GccAttributeContext>();
}

C_grammarParser::GccAttributeContext* C_grammarParser::GccAttributeListContext::gccAttribute(size_t i) {
  return getRuleContext<C_grammarParser::GccAttributeContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::GccAttributeListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::GccAttributeListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::GccAttributeListContext::getRuleIndex() const {
  return C_grammarParser::RuleGccAttributeList;
}

void C_grammarParser::GccAttributeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGccAttributeList(this);
}

void C_grammarParser::GccAttributeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGccAttributeList(this);
}


antlrcpp::Any C_grammarParser::GccAttributeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitGccAttributeList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::GccAttributeListContext* C_grammarParser::gccAttributeList() {
  GccAttributeListContext *_localctx = _tracker.createInstance<GccAttributeListContext>(_ctx, getState());
  enterRule(_localctx, 102, C_grammarParser::RuleGccAttributeList);
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
    setState(679);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::T__7)
      | (1ULL << C_grammarParser::T__8)
      | (1ULL << C_grammarParser::T__9)
      | (1ULL << C_grammarParser::T__10)
      | (1ULL << C_grammarParser::T__11)
      | (1ULL << C_grammarParser::T__12)
      | (1ULL << C_grammarParser::T__13)
      | (1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Break)
      | (1ULL << C_grammarParser::Case)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Continue)
      | (1ULL << C_grammarParser::Default)
      | (1ULL << C_grammarParser::Do)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Else)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::Goto)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Inline)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Sizeof)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Switch)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::While)
      | (1ULL << C_grammarParser::Alignas)
      | (1ULL << C_grammarParser::Alignof)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::Generic)
      | (1ULL << C_grammarParser::Imaginary)
      | (1ULL << C_grammarParser::Noreturn)
      | (1ULL << C_grammarParser::StaticAssert)
      | (1ULL << C_grammarParser::ThreadLocal)
      | (1ULL << C_grammarParser::LeftBracket)
      | (1ULL << C_grammarParser::RightBracket)
      | (1ULL << C_grammarParser::LeftBrace))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::RightBrace - 64))
      | (1ULL << (C_grammarParser::Less - 64))
      | (1ULL << (C_grammarParser::LessEqual - 64))
      | (1ULL << (C_grammarParser::Greater - 64))
      | (1ULL << (C_grammarParser::GreaterEqual - 64))
      | (1ULL << (C_grammarParser::LeftShift - 64))
      | (1ULL << (C_grammarParser::RightShift - 64))
      | (1ULL << (C_grammarParser::Plus - 64))
      | (1ULL << (C_grammarParser::PlusPlus - 64))
      | (1ULL << (C_grammarParser::Minus - 64))
      | (1ULL << (C_grammarParser::MinusMinus - 64))
      | (1ULL << (C_grammarParser::Star - 64))
      | (1ULL << (C_grammarParser::Div - 64))
      | (1ULL << (C_grammarParser::Mod - 64))
      | (1ULL << (C_grammarParser::And - 64))
      | (1ULL << (C_grammarParser::Or - 64))
      | (1ULL << (C_grammarParser::AndAnd - 64))
      | (1ULL << (C_grammarParser::OrOr - 64))
      | (1ULL << (C_grammarParser::Caret - 64))
      | (1ULL << (C_grammarParser::Not - 64))
      | (1ULL << (C_grammarParser::Tilde - 64))
      | (1ULL << (C_grammarParser::Question - 64))
      | (1ULL << (C_grammarParser::Colon - 64))
      | (1ULL << (C_grammarParser::Semi - 64))
      | (1ULL << (C_grammarParser::Assign - 64))
      | (1ULL << (C_grammarParser::StarAssign - 64))
      | (1ULL << (C_grammarParser::DivAssign - 64))
      | (1ULL << (C_grammarParser::ModAssign - 64))
      | (1ULL << (C_grammarParser::PlusAssign - 64))
      | (1ULL << (C_grammarParser::MinusAssign - 64))
      | (1ULL << (C_grammarParser::LeftShiftAssign - 64))
      | (1ULL << (C_grammarParser::RightShiftAssign - 64))
      | (1ULL << (C_grammarParser::AndAssign - 64))
      | (1ULL << (C_grammarParser::XorAssign - 64))
      | (1ULL << (C_grammarParser::OrAssign - 64))
      | (1ULL << (C_grammarParser::Equal - 64))
      | (1ULL << (C_grammarParser::NotEqual - 64))
      | (1ULL << (C_grammarParser::Arrow - 64))
      | (1ULL << (C_grammarParser::Dot - 64))
      | (1ULL << (C_grammarParser::Ellipsis - 64))
      | (1ULL << (C_grammarParser::Identifier - 64))
      | (1ULL << (C_grammarParser::Constant - 64))
      | (1ULL << (C_grammarParser::DigitSequence - 64))
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
      setState(678);
      gccAttribute();
    }
    setState(687);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(681);
      match(C_grammarParser::Comma);
      setState(683);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
        | (1ULL << C_grammarParser::T__1)
        | (1ULL << C_grammarParser::T__2)
        | (1ULL << C_grammarParser::T__3)
        | (1ULL << C_grammarParser::T__4)
        | (1ULL << C_grammarParser::T__5)
        | (1ULL << C_grammarParser::T__6)
        | (1ULL << C_grammarParser::T__7)
        | (1ULL << C_grammarParser::T__8)
        | (1ULL << C_grammarParser::T__9)
        | (1ULL << C_grammarParser::T__10)
        | (1ULL << C_grammarParser::T__11)
        | (1ULL << C_grammarParser::T__12)
        | (1ULL << C_grammarParser::T__13)
        | (1ULL << C_grammarParser::Auto)
        | (1ULL << C_grammarParser::Break)
        | (1ULL << C_grammarParser::Case)
        | (1ULL << C_grammarParser::Char)
        | (1ULL << C_grammarParser::Const)
        | (1ULL << C_grammarParser::Continue)
        | (1ULL << C_grammarParser::Default)
        | (1ULL << C_grammarParser::Do)
        | (1ULL << C_grammarParser::Double)
        | (1ULL << C_grammarParser::Else)
        | (1ULL << C_grammarParser::Enum)
        | (1ULL << C_grammarParser::Extern)
        | (1ULL << C_grammarParser::Float)
        | (1ULL << C_grammarParser::For)
        | (1ULL << C_grammarParser::Goto)
        | (1ULL << C_grammarParser::If)
        | (1ULL << C_grammarParser::Inline)
        | (1ULL << C_grammarParser::Int)
        | (1ULL << C_grammarParser::Long)
        | (1ULL << C_grammarParser::Register)
        | (1ULL << C_grammarParser::Restrict)
        | (1ULL << C_grammarParser::Return)
        | (1ULL << C_grammarParser::Short)
        | (1ULL << C_grammarParser::Signed)
        | (1ULL << C_grammarParser::Sizeof)
        | (1ULL << C_grammarParser::Static)
        | (1ULL << C_grammarParser::Struct)
        | (1ULL << C_grammarParser::Switch)
        | (1ULL << C_grammarParser::Typedef)
        | (1ULL << C_grammarParser::Union)
        | (1ULL << C_grammarParser::Unsigned)
        | (1ULL << C_grammarParser::Void)
        | (1ULL << C_grammarParser::Volatile)
        | (1ULL << C_grammarParser::While)
        | (1ULL << C_grammarParser::Alignas)
        | (1ULL << C_grammarParser::Alignof)
        | (1ULL << C_grammarParser::Atomic)
        | (1ULL << C_grammarParser::Bool)
        | (1ULL << C_grammarParser::Complex)
        | (1ULL << C_grammarParser::Generic)
        | (1ULL << C_grammarParser::Imaginary)
        | (1ULL << C_grammarParser::Noreturn)
        | (1ULL << C_grammarParser::StaticAssert)
        | (1ULL << C_grammarParser::ThreadLocal)
        | (1ULL << C_grammarParser::LeftBracket)
        | (1ULL << C_grammarParser::RightBracket)
        | (1ULL << C_grammarParser::LeftBrace))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::RightBrace - 64))
        | (1ULL << (C_grammarParser::Less - 64))
        | (1ULL << (C_grammarParser::LessEqual - 64))
        | (1ULL << (C_grammarParser::Greater - 64))
        | (1ULL << (C_grammarParser::GreaterEqual - 64))
        | (1ULL << (C_grammarParser::LeftShift - 64))
        | (1ULL << (C_grammarParser::RightShift - 64))
        | (1ULL << (C_grammarParser::Plus - 64))
        | (1ULL << (C_grammarParser::PlusPlus - 64))
        | (1ULL << (C_grammarParser::Minus - 64))
        | (1ULL << (C_grammarParser::MinusMinus - 64))
        | (1ULL << (C_grammarParser::Star - 64))
        | (1ULL << (C_grammarParser::Div - 64))
        | (1ULL << (C_grammarParser::Mod - 64))
        | (1ULL << (C_grammarParser::And - 64))
        | (1ULL << (C_grammarParser::Or - 64))
        | (1ULL << (C_grammarParser::AndAnd - 64))
        | (1ULL << (C_grammarParser::OrOr - 64))
        | (1ULL << (C_grammarParser::Caret - 64))
        | (1ULL << (C_grammarParser::Not - 64))
        | (1ULL << (C_grammarParser::Tilde - 64))
        | (1ULL << (C_grammarParser::Question - 64))
        | (1ULL << (C_grammarParser::Colon - 64))
        | (1ULL << (C_grammarParser::Semi - 64))
        | (1ULL << (C_grammarParser::Assign - 64))
        | (1ULL << (C_grammarParser::StarAssign - 64))
        | (1ULL << (C_grammarParser::DivAssign - 64))
        | (1ULL << (C_grammarParser::ModAssign - 64))
        | (1ULL << (C_grammarParser::PlusAssign - 64))
        | (1ULL << (C_grammarParser::MinusAssign - 64))
        | (1ULL << (C_grammarParser::LeftShiftAssign - 64))
        | (1ULL << (C_grammarParser::RightShiftAssign - 64))
        | (1ULL << (C_grammarParser::AndAssign - 64))
        | (1ULL << (C_grammarParser::XorAssign - 64))
        | (1ULL << (C_grammarParser::OrAssign - 64))
        | (1ULL << (C_grammarParser::Equal - 64))
        | (1ULL << (C_grammarParser::NotEqual - 64))
        | (1ULL << (C_grammarParser::Arrow - 64))
        | (1ULL << (C_grammarParser::Dot - 64))
        | (1ULL << (C_grammarParser::Ellipsis - 64))
        | (1ULL << (C_grammarParser::Identifier - 64))
        | (1ULL << (C_grammarParser::Constant - 64))
        | (1ULL << (C_grammarParser::DigitSequence - 64))
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
        setState(682);
        gccAttribute();
      }
      setState(689);
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

//----------------- GccAttributeContext ------------------------------------------------------------------

C_grammarParser::GccAttributeContext::GccAttributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::GccAttributeContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}

std::vector<tree::TerminalNode *> C_grammarParser::GccAttributeContext::LeftParen() {
  return getTokens(C_grammarParser::LeftParen);
}

tree::TerminalNode* C_grammarParser::GccAttributeContext::LeftParen(size_t i) {
  return getToken(C_grammarParser::LeftParen, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::GccAttributeContext::RightParen() {
  return getTokens(C_grammarParser::RightParen);
}

tree::TerminalNode* C_grammarParser::GccAttributeContext::RightParen(size_t i) {
  return getToken(C_grammarParser::RightParen, i);
}

C_grammarParser::ArgumentExpressionListContext* C_grammarParser::GccAttributeContext::argumentExpressionList() {
  return getRuleContext<C_grammarParser::ArgumentExpressionListContext>(0);
}


size_t C_grammarParser::GccAttributeContext::getRuleIndex() const {
  return C_grammarParser::RuleGccAttribute;
}

void C_grammarParser::GccAttributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGccAttribute(this);
}

void C_grammarParser::GccAttributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGccAttribute(this);
}


antlrcpp::Any C_grammarParser::GccAttributeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitGccAttribute(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::GccAttributeContext* C_grammarParser::gccAttribute() {
  GccAttributeContext *_localctx = _tracker.createInstance<GccAttributeContext>(_ctx, getState());
  enterRule(_localctx, 104, C_grammarParser::RuleGccAttribute);
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
    setState(690);
    _la = _input->LA(1);
    if (_la == 0 || _la == Token::EOF || (((((_la - 59) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 59)) & ((1ULL << (C_grammarParser::LeftParen - 59))
      | (1ULL << (C_grammarParser::RightParen - 59))
      | (1ULL << (C_grammarParser::Comma - 59)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(696);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftParen) {
      setState(691);
      match(C_grammarParser::LeftParen);
      setState(693);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
        | (1ULL << C_grammarParser::T__1)
        | (1ULL << C_grammarParser::T__2)
        | (1ULL << C_grammarParser::Sizeof)
        | (1ULL << C_grammarParser::Alignof)
        | (1ULL << C_grammarParser::Generic)
        | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
        | (1ULL << (C_grammarParser::PlusPlus - 71))
        | (1ULL << (C_grammarParser::Minus - 71))
        | (1ULL << (C_grammarParser::MinusMinus - 71))
        | (1ULL << (C_grammarParser::Star - 71))
        | (1ULL << (C_grammarParser::And - 71))
        | (1ULL << (C_grammarParser::AndAnd - 71))
        | (1ULL << (C_grammarParser::Not - 71))
        | (1ULL << (C_grammarParser::Tilde - 71))
        | (1ULL << (C_grammarParser::Identifier - 71))
        | (1ULL << (C_grammarParser::Constant - 71))
        | (1ULL << (C_grammarParser::DigitSequence - 71))
        | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
        setState(692);
        argumentExpressionList();
      }
      setState(695);
      match(C_grammarParser::RightParen);
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
  enterRule(_localctx, 106, C_grammarParser::RuleNestedParenthesesBlock);
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
    setState(705);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::T__7)
      | (1ULL << C_grammarParser::T__8)
      | (1ULL << C_grammarParser::T__9)
      | (1ULL << C_grammarParser::T__10)
      | (1ULL << C_grammarParser::T__11)
      | (1ULL << C_grammarParser::T__12)
      | (1ULL << C_grammarParser::T__13)
      | (1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Break)
      | (1ULL << C_grammarParser::Case)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Continue)
      | (1ULL << C_grammarParser::Default)
      | (1ULL << C_grammarParser::Do)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Else)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::Goto)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Inline)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Sizeof)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Switch)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::While)
      | (1ULL << C_grammarParser::Alignas)
      | (1ULL << C_grammarParser::Alignof)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::Generic)
      | (1ULL << C_grammarParser::Imaginary)
      | (1ULL << C_grammarParser::Noreturn)
      | (1ULL << C_grammarParser::StaticAssert)
      | (1ULL << C_grammarParser::ThreadLocal)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::LeftBracket)
      | (1ULL << C_grammarParser::RightBracket)
      | (1ULL << C_grammarParser::LeftBrace))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (C_grammarParser::RightBrace - 64))
      | (1ULL << (C_grammarParser::Less - 64))
      | (1ULL << (C_grammarParser::LessEqual - 64))
      | (1ULL << (C_grammarParser::Greater - 64))
      | (1ULL << (C_grammarParser::GreaterEqual - 64))
      | (1ULL << (C_grammarParser::LeftShift - 64))
      | (1ULL << (C_grammarParser::RightShift - 64))
      | (1ULL << (C_grammarParser::Plus - 64))
      | (1ULL << (C_grammarParser::PlusPlus - 64))
      | (1ULL << (C_grammarParser::Minus - 64))
      | (1ULL << (C_grammarParser::MinusMinus - 64))
      | (1ULL << (C_grammarParser::Star - 64))
      | (1ULL << (C_grammarParser::Div - 64))
      | (1ULL << (C_grammarParser::Mod - 64))
      | (1ULL << (C_grammarParser::And - 64))
      | (1ULL << (C_grammarParser::Or - 64))
      | (1ULL << (C_grammarParser::AndAnd - 64))
      | (1ULL << (C_grammarParser::OrOr - 64))
      | (1ULL << (C_grammarParser::Caret - 64))
      | (1ULL << (C_grammarParser::Not - 64))
      | (1ULL << (C_grammarParser::Tilde - 64))
      | (1ULL << (C_grammarParser::Question - 64))
      | (1ULL << (C_grammarParser::Colon - 64))
      | (1ULL << (C_grammarParser::Semi - 64))
      | (1ULL << (C_grammarParser::Comma - 64))
      | (1ULL << (C_grammarParser::Assign - 64))
      | (1ULL << (C_grammarParser::StarAssign - 64))
      | (1ULL << (C_grammarParser::DivAssign - 64))
      | (1ULL << (C_grammarParser::ModAssign - 64))
      | (1ULL << (C_grammarParser::PlusAssign - 64))
      | (1ULL << (C_grammarParser::MinusAssign - 64))
      | (1ULL << (C_grammarParser::LeftShiftAssign - 64))
      | (1ULL << (C_grammarParser::RightShiftAssign - 64))
      | (1ULL << (C_grammarParser::AndAssign - 64))
      | (1ULL << (C_grammarParser::XorAssign - 64))
      | (1ULL << (C_grammarParser::OrAssign - 64))
      | (1ULL << (C_grammarParser::Equal - 64))
      | (1ULL << (C_grammarParser::NotEqual - 64))
      | (1ULL << (C_grammarParser::Arrow - 64))
      | (1ULL << (C_grammarParser::Dot - 64))
      | (1ULL << (C_grammarParser::Ellipsis - 64))
      | (1ULL << (C_grammarParser::Identifier - 64))
      | (1ULL << (C_grammarParser::Constant - 64))
      | (1ULL << (C_grammarParser::DigitSequence - 64))
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
      setState(703);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case C_grammarParser::T__0:
        case C_grammarParser::T__1:
        case C_grammarParser::T__2:
        case C_grammarParser::T__3:
        case C_grammarParser::T__4:
        case C_grammarParser::T__5:
        case C_grammarParser::T__6:
        case C_grammarParser::T__7:
        case C_grammarParser::T__8:
        case C_grammarParser::T__9:
        case C_grammarParser::T__10:
        case C_grammarParser::T__11:
        case C_grammarParser::T__12:
        case C_grammarParser::T__13:
        case C_grammarParser::Auto:
        case C_grammarParser::Break:
        case C_grammarParser::Case:
        case C_grammarParser::Char:
        case C_grammarParser::Const:
        case C_grammarParser::Continue:
        case C_grammarParser::Default:
        case C_grammarParser::Do:
        case C_grammarParser::Double:
        case C_grammarParser::Else:
        case C_grammarParser::Enum:
        case C_grammarParser::Extern:
        case C_grammarParser::Float:
        case C_grammarParser::For:
        case C_grammarParser::Goto:
        case C_grammarParser::If:
        case C_grammarParser::Inline:
        case C_grammarParser::Int:
        case C_grammarParser::Long:
        case C_grammarParser::Register:
        case C_grammarParser::Restrict:
        case C_grammarParser::Return:
        case C_grammarParser::Short:
        case C_grammarParser::Signed:
        case C_grammarParser::Sizeof:
        case C_grammarParser::Static:
        case C_grammarParser::Struct:
        case C_grammarParser::Switch:
        case C_grammarParser::Typedef:
        case C_grammarParser::Union:
        case C_grammarParser::Unsigned:
        case C_grammarParser::Void:
        case C_grammarParser::Volatile:
        case C_grammarParser::While:
        case C_grammarParser::Alignas:
        case C_grammarParser::Alignof:
        case C_grammarParser::Atomic:
        case C_grammarParser::Bool:
        case C_grammarParser::Complex:
        case C_grammarParser::Generic:
        case C_grammarParser::Imaginary:
        case C_grammarParser::Noreturn:
        case C_grammarParser::StaticAssert:
        case C_grammarParser::ThreadLocal:
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
        case C_grammarParser::Constant:
        case C_grammarParser::DigitSequence:
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
          setState(698);
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
          setState(699);
          match(C_grammarParser::LeftParen);
          setState(700);
          nestedParenthesesBlock();
          setState(701);
          match(C_grammarParser::RightParen);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(707);
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

//----------------- PointerContext ------------------------------------------------------------------

C_grammarParser::PointerContext::PointerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> C_grammarParser::PointerContext::Star() {
  return getTokens(C_grammarParser::Star);
}

tree::TerminalNode* C_grammarParser::PointerContext::Star(size_t i) {
  return getToken(C_grammarParser::Star, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::PointerContext::Caret() {
  return getTokens(C_grammarParser::Caret);
}

tree::TerminalNode* C_grammarParser::PointerContext::Caret(size_t i) {
  return getToken(C_grammarParser::Caret, i);
}

std::vector<C_grammarParser::TypeQualifierListContext *> C_grammarParser::PointerContext::typeQualifierList() {
  return getRuleContexts<C_grammarParser::TypeQualifierListContext>();
}

C_grammarParser::TypeQualifierListContext* C_grammarParser::PointerContext::typeQualifierList(size_t i) {
  return getRuleContext<C_grammarParser::TypeQualifierListContext>(i);
}


size_t C_grammarParser::PointerContext::getRuleIndex() const {
  return C_grammarParser::RulePointer;
}

void C_grammarParser::PointerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPointer(this);
}

void C_grammarParser::PointerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPointer(this);
}


antlrcpp::Any C_grammarParser::PointerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitPointer(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::PointerContext* C_grammarParser::pointer() {
  PointerContext *_localctx = _tracker.createInstance<PointerContext>(_ctx, getState());
  enterRule(_localctx, 108, C_grammarParser::RulePointer);
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
    setState(712); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(708);
              _la = _input->LA(1);
              if (!(_la == C_grammarParser::Star

              || _la == C_grammarParser::Caret)) {
              _errHandler->recoverInline(this);
              }
              else {
                _errHandler->reportMatch(this);
                consume();
              }
              setState(710);
              _errHandler->sync(this);

              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
              case 1: {
                setState(709);
                typeQualifierList();
                break;
              }

              default:
                break;
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(714); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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
  enterRule(_localctx, 110, C_grammarParser::RuleTypeQualifierList);

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
    setState(717); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(716);
              typeQualifier();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(719); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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
  enterRule(_localctx, 112, C_grammarParser::RuleParameterTypeList);
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
    setState(721);
    parameterList();
    setState(724);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Comma) {
      setState(722);
      match(C_grammarParser::Comma);
      setState(723);
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
  enterRule(_localctx, 114, C_grammarParser::RuleParameterList);

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
    setState(726);
    parameterDeclaration();
    setState(731);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(727);
        match(C_grammarParser::Comma);
        setState(728);
        parameterDeclaration(); 
      }
      setState(733);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
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

C_grammarParser::DeclarationSpecifiers2Context* C_grammarParser::ParameterDeclarationContext::declarationSpecifiers2() {
  return getRuleContext<C_grammarParser::DeclarationSpecifiers2Context>(0);
}

C_grammarParser::AbstractDeclaratorContext* C_grammarParser::ParameterDeclarationContext::abstractDeclarator() {
  return getRuleContext<C_grammarParser::AbstractDeclaratorContext>(0);
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
  enterRule(_localctx, 116, C_grammarParser::RuleParameterDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(741);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(734);
      declarationSpecifiers();
      setState(735);
      declarator();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(737);
      declarationSpecifiers2();
      setState(739);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 59) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 59)) & ((1ULL << (C_grammarParser::LeftParen - 59))
        | (1ULL << (C_grammarParser::LeftBracket - 59))
        | (1ULL << (C_grammarParser::Star - 59))
        | (1ULL << (C_grammarParser::Caret - 59)))) != 0)) {
        setState(738);
        abstractDeclarator();
      }
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
  enterRule(_localctx, 118, C_grammarParser::RuleIdentifierList);
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
    setState(743);
    match(C_grammarParser::Identifier);
    setState(748);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(744);
      match(C_grammarParser::Comma);
      setState(745);
      match(C_grammarParser::Identifier);
      setState(750);
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

C_grammarParser::AbstractDeclaratorContext* C_grammarParser::TypeNameContext::abstractDeclarator() {
  return getRuleContext<C_grammarParser::AbstractDeclaratorContext>(0);
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
  enterRule(_localctx, 120, C_grammarParser::RuleTypeName);
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
    setState(751);
    specifierQualifierList();
    setState(753);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 59) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 59)) & ((1ULL << (C_grammarParser::LeftParen - 59))
      | (1ULL << (C_grammarParser::LeftBracket - 59))
      | (1ULL << (C_grammarParser::Star - 59))
      | (1ULL << (C_grammarParser::Caret - 59)))) != 0)) {
      setState(752);
      abstractDeclarator();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AbstractDeclaratorContext ------------------------------------------------------------------

C_grammarParser::AbstractDeclaratorContext::AbstractDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::PointerContext* C_grammarParser::AbstractDeclaratorContext::pointer() {
  return getRuleContext<C_grammarParser::PointerContext>(0);
}

C_grammarParser::DirectAbstractDeclaratorContext* C_grammarParser::AbstractDeclaratorContext::directAbstractDeclarator() {
  return getRuleContext<C_grammarParser::DirectAbstractDeclaratorContext>(0);
}

std::vector<C_grammarParser::GccDeclaratorExtensionContext *> C_grammarParser::AbstractDeclaratorContext::gccDeclaratorExtension() {
  return getRuleContexts<C_grammarParser::GccDeclaratorExtensionContext>();
}

C_grammarParser::GccDeclaratorExtensionContext* C_grammarParser::AbstractDeclaratorContext::gccDeclaratorExtension(size_t i) {
  return getRuleContext<C_grammarParser::GccDeclaratorExtensionContext>(i);
}


size_t C_grammarParser::AbstractDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleAbstractDeclarator;
}

void C_grammarParser::AbstractDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAbstractDeclarator(this);
}

void C_grammarParser::AbstractDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAbstractDeclarator(this);
}


antlrcpp::Any C_grammarParser::AbstractDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAbstractDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AbstractDeclaratorContext* C_grammarParser::abstractDeclarator() {
  AbstractDeclaratorContext *_localctx = _tracker.createInstance<AbstractDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 122, C_grammarParser::RuleAbstractDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(766);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(755);
      pointer();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(757);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Star

      || _la == C_grammarParser::Caret) {
        setState(756);
        pointer();
      }
      setState(759);
      directAbstractDeclarator(0);
      setState(763);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C_grammarParser::T__10

      || _la == C_grammarParser::T__11) {
        setState(760);
        gccDeclaratorExtension();
        setState(765);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
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

//----------------- DirectAbstractDeclaratorContext ------------------------------------------------------------------

C_grammarParser::DirectAbstractDeclaratorContext::DirectAbstractDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::DirectAbstractDeclaratorContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::AbstractDeclaratorContext* C_grammarParser::DirectAbstractDeclaratorContext::abstractDeclarator() {
  return getRuleContext<C_grammarParser::AbstractDeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::DirectAbstractDeclaratorContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

std::vector<C_grammarParser::GccDeclaratorExtensionContext *> C_grammarParser::DirectAbstractDeclaratorContext::gccDeclaratorExtension() {
  return getRuleContexts<C_grammarParser::GccDeclaratorExtensionContext>();
}

C_grammarParser::GccDeclaratorExtensionContext* C_grammarParser::DirectAbstractDeclaratorContext::gccDeclaratorExtension(size_t i) {
  return getRuleContext<C_grammarParser::GccDeclaratorExtensionContext>(i);
}

tree::TerminalNode* C_grammarParser::DirectAbstractDeclaratorContext::LeftBracket() {
  return getToken(C_grammarParser::LeftBracket, 0);
}

tree::TerminalNode* C_grammarParser::DirectAbstractDeclaratorContext::RightBracket() {
  return getToken(C_grammarParser::RightBracket, 0);
}

C_grammarParser::TypeQualifierListContext* C_grammarParser::DirectAbstractDeclaratorContext::typeQualifierList() {
  return getRuleContext<C_grammarParser::TypeQualifierListContext>(0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::DirectAbstractDeclaratorContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::DirectAbstractDeclaratorContext::Static() {
  return getToken(C_grammarParser::Static, 0);
}

tree::TerminalNode* C_grammarParser::DirectAbstractDeclaratorContext::Star() {
  return getToken(C_grammarParser::Star, 0);
}

C_grammarParser::ParameterTypeListContext* C_grammarParser::DirectAbstractDeclaratorContext::parameterTypeList() {
  return getRuleContext<C_grammarParser::ParameterTypeListContext>(0);
}

C_grammarParser::DirectAbstractDeclaratorContext* C_grammarParser::DirectAbstractDeclaratorContext::directAbstractDeclarator() {
  return getRuleContext<C_grammarParser::DirectAbstractDeclaratorContext>(0);
}


size_t C_grammarParser::DirectAbstractDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleDirectAbstractDeclarator;
}

void C_grammarParser::DirectAbstractDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirectAbstractDeclarator(this);
}

void C_grammarParser::DirectAbstractDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirectAbstractDeclarator(this);
}


antlrcpp::Any C_grammarParser::DirectAbstractDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDirectAbstractDeclarator(this);
  else
    return visitor->visitChildren(this);
}


C_grammarParser::DirectAbstractDeclaratorContext* C_grammarParser::directAbstractDeclarator() {
   return directAbstractDeclarator(0);
}

C_grammarParser::DirectAbstractDeclaratorContext* C_grammarParser::directAbstractDeclarator(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C_grammarParser::DirectAbstractDeclaratorContext *_localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(_ctx, parentState);
  C_grammarParser::DirectAbstractDeclaratorContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 124;
  enterRecursionRule(_localctx, 124, C_grammarParser::RuleDirectAbstractDeclarator, precedence);

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
    setState(814);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
    case 1: {
      setState(769);
      match(C_grammarParser::LeftParen);
      setState(770);
      abstractDeclarator();
      setState(771);
      match(C_grammarParser::RightParen);
      setState(775);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(772);
          gccDeclaratorExtension(); 
        }
        setState(777);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx);
      }
      break;
    }

    case 2: {
      setState(778);
      match(C_grammarParser::LeftBracket);
      setState(780);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::Const)
        | (1ULL << C_grammarParser::Restrict)
        | (1ULL << C_grammarParser::Volatile)
        | (1ULL << C_grammarParser::Atomic))) != 0)) {
        setState(779);
        typeQualifierList();
      }
      setState(783);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
        | (1ULL << C_grammarParser::T__1)
        | (1ULL << C_grammarParser::T__2)
        | (1ULL << C_grammarParser::Sizeof)
        | (1ULL << C_grammarParser::Alignof)
        | (1ULL << C_grammarParser::Generic)
        | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
        | (1ULL << (C_grammarParser::PlusPlus - 71))
        | (1ULL << (C_grammarParser::Minus - 71))
        | (1ULL << (C_grammarParser::MinusMinus - 71))
        | (1ULL << (C_grammarParser::Star - 71))
        | (1ULL << (C_grammarParser::And - 71))
        | (1ULL << (C_grammarParser::AndAnd - 71))
        | (1ULL << (C_grammarParser::Not - 71))
        | (1ULL << (C_grammarParser::Tilde - 71))
        | (1ULL << (C_grammarParser::Identifier - 71))
        | (1ULL << (C_grammarParser::Constant - 71))
        | (1ULL << (C_grammarParser::DigitSequence - 71))
        | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
        setState(782);
        assignmentExpression();
      }
      setState(785);
      match(C_grammarParser::RightBracket);
      break;
    }

    case 3: {
      setState(786);
      match(C_grammarParser::LeftBracket);
      setState(787);
      match(C_grammarParser::Static);
      setState(789);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::Const)
        | (1ULL << C_grammarParser::Restrict)
        | (1ULL << C_grammarParser::Volatile)
        | (1ULL << C_grammarParser::Atomic))) != 0)) {
        setState(788);
        typeQualifierList();
      }
      setState(791);
      assignmentExpression();
      setState(792);
      match(C_grammarParser::RightBracket);
      break;
    }

    case 4: {
      setState(794);
      match(C_grammarParser::LeftBracket);
      setState(795);
      typeQualifierList();
      setState(796);
      match(C_grammarParser::Static);
      setState(797);
      assignmentExpression();
      setState(798);
      match(C_grammarParser::RightBracket);
      break;
    }

    case 5: {
      setState(800);
      match(C_grammarParser::LeftBracket);
      setState(801);
      match(C_grammarParser::Star);
      setState(802);
      match(C_grammarParser::RightBracket);
      break;
    }

    case 6: {
      setState(803);
      match(C_grammarParser::LeftParen);
      setState(805);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
        | (1ULL << C_grammarParser::T__3)
        | (1ULL << C_grammarParser::T__4)
        | (1ULL << C_grammarParser::T__5)
        | (1ULL << C_grammarParser::T__6)
        | (1ULL << C_grammarParser::T__7)
        | (1ULL << C_grammarParser::T__8)
        | (1ULL << C_grammarParser::T__9)
        | (1ULL << C_grammarParser::T__11)
        | (1ULL << C_grammarParser::Auto)
        | (1ULL << C_grammarParser::Char)
        | (1ULL << C_grammarParser::Const)
        | (1ULL << C_grammarParser::Double)
        | (1ULL << C_grammarParser::Enum)
        | (1ULL << C_grammarParser::Extern)
        | (1ULL << C_grammarParser::Float)
        | (1ULL << C_grammarParser::Inline)
        | (1ULL << C_grammarParser::Int)
        | (1ULL << C_grammarParser::Long)
        | (1ULL << C_grammarParser::Register)
        | (1ULL << C_grammarParser::Restrict)
        | (1ULL << C_grammarParser::Short)
        | (1ULL << C_grammarParser::Signed)
        | (1ULL << C_grammarParser::Static)
        | (1ULL << C_grammarParser::Struct)
        | (1ULL << C_grammarParser::Typedef)
        | (1ULL << C_grammarParser::Union)
        | (1ULL << C_grammarParser::Unsigned)
        | (1ULL << C_grammarParser::Void)
        | (1ULL << C_grammarParser::Volatile)
        | (1ULL << C_grammarParser::Alignas)
        | (1ULL << C_grammarParser::Atomic)
        | (1ULL << C_grammarParser::Bool)
        | (1ULL << C_grammarParser::Complex)
        | (1ULL << C_grammarParser::Noreturn)
        | (1ULL << C_grammarParser::ThreadLocal))) != 0) || _la == C_grammarParser::Identifier) {
        setState(804);
        parameterTypeList();
      }
      setState(807);
      match(C_grammarParser::RightParen);
      setState(811);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(808);
          gccDeclaratorExtension(); 
        }
        setState(813);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx);
      }
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(859);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(857);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 99, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(816);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(817);
          match(C_grammarParser::LeftBracket);
          setState(819);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::Const)
            | (1ULL << C_grammarParser::Restrict)
            | (1ULL << C_grammarParser::Volatile)
            | (1ULL << C_grammarParser::Atomic))) != 0)) {
            setState(818);
            typeQualifierList();
          }
          setState(822);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
            | (1ULL << C_grammarParser::T__1)
            | (1ULL << C_grammarParser::T__2)
            | (1ULL << C_grammarParser::Sizeof)
            | (1ULL << C_grammarParser::Alignof)
            | (1ULL << C_grammarParser::Generic)
            | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
            | (1ULL << (C_grammarParser::PlusPlus - 71))
            | (1ULL << (C_grammarParser::Minus - 71))
            | (1ULL << (C_grammarParser::MinusMinus - 71))
            | (1ULL << (C_grammarParser::Star - 71))
            | (1ULL << (C_grammarParser::And - 71))
            | (1ULL << (C_grammarParser::AndAnd - 71))
            | (1ULL << (C_grammarParser::Not - 71))
            | (1ULL << (C_grammarParser::Tilde - 71))
            | (1ULL << (C_grammarParser::Identifier - 71))
            | (1ULL << (C_grammarParser::Constant - 71))
            | (1ULL << (C_grammarParser::DigitSequence - 71))
            | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
            setState(821);
            assignmentExpression();
          }
          setState(824);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(825);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(826);
          match(C_grammarParser::LeftBracket);
          setState(827);
          match(C_grammarParser::Static);
          setState(829);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::Const)
            | (1ULL << C_grammarParser::Restrict)
            | (1ULL << C_grammarParser::Volatile)
            | (1ULL << C_grammarParser::Atomic))) != 0)) {
            setState(828);
            typeQualifierList();
          }
          setState(831);
          assignmentExpression();
          setState(832);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(834);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(835);
          match(C_grammarParser::LeftBracket);
          setState(836);
          typeQualifierList();
          setState(837);
          match(C_grammarParser::Static);
          setState(838);
          assignmentExpression();
          setState(839);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(841);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(842);
          match(C_grammarParser::LeftBracket);
          setState(843);
          match(C_grammarParser::Star);
          setState(844);
          match(C_grammarParser::RightBracket);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<DirectAbstractDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectAbstractDeclarator);
          setState(845);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(846);
          match(C_grammarParser::LeftParen);
          setState(848);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
            | (1ULL << C_grammarParser::T__3)
            | (1ULL << C_grammarParser::T__4)
            | (1ULL << C_grammarParser::T__5)
            | (1ULL << C_grammarParser::T__6)
            | (1ULL << C_grammarParser::T__7)
            | (1ULL << C_grammarParser::T__8)
            | (1ULL << C_grammarParser::T__9)
            | (1ULL << C_grammarParser::T__11)
            | (1ULL << C_grammarParser::Auto)
            | (1ULL << C_grammarParser::Char)
            | (1ULL << C_grammarParser::Const)
            | (1ULL << C_grammarParser::Double)
            | (1ULL << C_grammarParser::Enum)
            | (1ULL << C_grammarParser::Extern)
            | (1ULL << C_grammarParser::Float)
            | (1ULL << C_grammarParser::Inline)
            | (1ULL << C_grammarParser::Int)
            | (1ULL << C_grammarParser::Long)
            | (1ULL << C_grammarParser::Register)
            | (1ULL << C_grammarParser::Restrict)
            | (1ULL << C_grammarParser::Short)
            | (1ULL << C_grammarParser::Signed)
            | (1ULL << C_grammarParser::Static)
            | (1ULL << C_grammarParser::Struct)
            | (1ULL << C_grammarParser::Typedef)
            | (1ULL << C_grammarParser::Union)
            | (1ULL << C_grammarParser::Unsigned)
            | (1ULL << C_grammarParser::Void)
            | (1ULL << C_grammarParser::Volatile)
            | (1ULL << C_grammarParser::Alignas)
            | (1ULL << C_grammarParser::Atomic)
            | (1ULL << C_grammarParser::Bool)
            | (1ULL << C_grammarParser::Complex)
            | (1ULL << C_grammarParser::Noreturn)
            | (1ULL << C_grammarParser::ThreadLocal))) != 0) || _la == C_grammarParser::Identifier) {
            setState(847);
            parameterTypeList();
          }
          setState(850);
          match(C_grammarParser::RightParen);
          setState(854);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(851);
              gccDeclaratorExtension(); 
            }
            setState(856);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx);
          }
          break;
        }

        default:
          break;
        } 
      }
      setState(861);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx);
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
  enterRule(_localctx, 126, C_grammarParser::RuleTypedefName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(862);
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
  enterRule(_localctx, 128, C_grammarParser::RuleInitializer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(872);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::T__0:
      case C_grammarParser::T__1:
      case C_grammarParser::T__2:
      case C_grammarParser::Sizeof:
      case C_grammarParser::Alignof:
      case C_grammarParser::Generic:
      case C_grammarParser::LeftParen:
      case C_grammarParser::Plus:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Star:
      case C_grammarParser::And:
      case C_grammarParser::AndAnd:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Identifier:
      case C_grammarParser::Constant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::StringLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(864);
        assignmentExpression();
        break;
      }

      case C_grammarParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(865);
        match(C_grammarParser::LeftBrace);
        setState(866);
        initializerList();
        setState(868);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::Comma) {
          setState(867);
          match(C_grammarParser::Comma);
        }
        setState(870);
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
  enterRule(_localctx, 130, C_grammarParser::RuleInitializerList);
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
    setState(875);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftBracket

    || _la == C_grammarParser::Dot) {
      setState(874);
      designation();
    }
    setState(877);
    initializer();
    setState(885);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(878);
        match(C_grammarParser::Comma);
        setState(880);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::LeftBracket

        || _la == C_grammarParser::Dot) {
          setState(879);
          designation();
        }
        setState(882);
        initializer(); 
      }
      setState(887);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx);
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
  enterRule(_localctx, 132, C_grammarParser::RuleDesignation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(888);
    designatorList();
    setState(889);
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
  enterRule(_localctx, 134, C_grammarParser::RuleDesignatorList);
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
    setState(892); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(891);
      designator();
      setState(894); 
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
  enterRule(_localctx, 136, C_grammarParser::RuleDesignator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(902);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBracket: {
        enterOuterAlt(_localctx, 1);
        setState(896);
        match(C_grammarParser::LeftBracket);
        setState(897);
        constantExpression();
        setState(898);
        match(C_grammarParser::RightBracket);
        break;
      }

      case C_grammarParser::Dot: {
        enterOuterAlt(_localctx, 2);
        setState(900);
        match(C_grammarParser::Dot);
        setState(901);
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

//----------------- StaticAssertDeclarationContext ------------------------------------------------------------------

C_grammarParser::StaticAssertDeclarationContext::StaticAssertDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::StaticAssertDeclarationContext::StaticAssert() {
  return getToken(C_grammarParser::StaticAssert, 0);
}

tree::TerminalNode* C_grammarParser::StaticAssertDeclarationContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::StaticAssertDeclarationContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::StaticAssertDeclarationContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}

tree::TerminalNode* C_grammarParser::StaticAssertDeclarationContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

tree::TerminalNode* C_grammarParser::StaticAssertDeclarationContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

std::vector<tree::TerminalNode *> C_grammarParser::StaticAssertDeclarationContext::StringLiteral() {
  return getTokens(C_grammarParser::StringLiteral);
}

tree::TerminalNode* C_grammarParser::StaticAssertDeclarationContext::StringLiteral(size_t i) {
  return getToken(C_grammarParser::StringLiteral, i);
}


size_t C_grammarParser::StaticAssertDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleStaticAssertDeclaration;
}

void C_grammarParser::StaticAssertDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStaticAssertDeclaration(this);
}

void C_grammarParser::StaticAssertDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStaticAssertDeclaration(this);
}


antlrcpp::Any C_grammarParser::StaticAssertDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStaticAssertDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StaticAssertDeclarationContext* C_grammarParser::staticAssertDeclaration() {
  StaticAssertDeclarationContext *_localctx = _tracker.createInstance<StaticAssertDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 138, C_grammarParser::RuleStaticAssertDeclaration);
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
    setState(904);
    match(C_grammarParser::StaticAssert);
    setState(905);
    match(C_grammarParser::LeftParen);
    setState(906);
    constantExpression();
    setState(907);
    match(C_grammarParser::Comma);
    setState(909); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(908);
      match(C_grammarParser::StringLiteral);
      setState(911); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == C_grammarParser::StringLiteral);
    setState(913);
    match(C_grammarParser::RightParen);
    setState(914);
    match(C_grammarParser::Semi);
   
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

C_grammarParser::LabeledStatementContext* C_grammarParser::StatementContext::labeledStatement() {
  return getRuleContext<C_grammarParser::LabeledStatementContext>(0);
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

C_grammarParser::JumpStatementContext* C_grammarParser::StatementContext::jumpStatement() {
  return getRuleContext<C_grammarParser::JumpStatementContext>(0);
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

tree::TerminalNode* C_grammarParser::StatementContext::Volatile() {
  return getToken(C_grammarParser::Volatile, 0);
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
  enterRule(_localctx, 140, C_grammarParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(953);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 114, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(916);
      labeledStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(917);
      compoundStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(918);
      expressionStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(919);
      selectionStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(920);
      iterationStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(921);
      jumpStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(922);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::T__10

      || _la == C_grammarParser::T__12)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(923);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::T__13

      || _la == C_grammarParser::Volatile)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(924);
      match(C_grammarParser::LeftParen);
      setState(933);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
        | (1ULL << C_grammarParser::T__1)
        | (1ULL << C_grammarParser::T__2)
        | (1ULL << C_grammarParser::Sizeof)
        | (1ULL << C_grammarParser::Alignof)
        | (1ULL << C_grammarParser::Generic)
        | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
        | (1ULL << (C_grammarParser::PlusPlus - 71))
        | (1ULL << (C_grammarParser::Minus - 71))
        | (1ULL << (C_grammarParser::MinusMinus - 71))
        | (1ULL << (C_grammarParser::Star - 71))
        | (1ULL << (C_grammarParser::And - 71))
        | (1ULL << (C_grammarParser::AndAnd - 71))
        | (1ULL << (C_grammarParser::Not - 71))
        | (1ULL << (C_grammarParser::Tilde - 71))
        | (1ULL << (C_grammarParser::Identifier - 71))
        | (1ULL << (C_grammarParser::Constant - 71))
        | (1ULL << (C_grammarParser::DigitSequence - 71))
        | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
        setState(925);
        logicalOrExpression();
        setState(930);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == C_grammarParser::Comma) {
          setState(926);
          match(C_grammarParser::Comma);
          setState(927);
          logicalOrExpression();
          setState(932);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(948);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C_grammarParser::Colon) {
        setState(935);
        match(C_grammarParser::Colon);
        setState(944);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
          | (1ULL << C_grammarParser::T__1)
          | (1ULL << C_grammarParser::T__2)
          | (1ULL << C_grammarParser::Sizeof)
          | (1ULL << C_grammarParser::Alignof)
          | (1ULL << C_grammarParser::Generic)
          | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
          | (1ULL << (C_grammarParser::PlusPlus - 71))
          | (1ULL << (C_grammarParser::Minus - 71))
          | (1ULL << (C_grammarParser::MinusMinus - 71))
          | (1ULL << (C_grammarParser::Star - 71))
          | (1ULL << (C_grammarParser::And - 71))
          | (1ULL << (C_grammarParser::AndAnd - 71))
          | (1ULL << (C_grammarParser::Not - 71))
          | (1ULL << (C_grammarParser::Tilde - 71))
          | (1ULL << (C_grammarParser::Identifier - 71))
          | (1ULL << (C_grammarParser::Constant - 71))
          | (1ULL << (C_grammarParser::DigitSequence - 71))
          | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
          setState(936);
          logicalOrExpression();
          setState(941);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == C_grammarParser::Comma) {
            setState(937);
            match(C_grammarParser::Comma);
            setState(938);
            logicalOrExpression();
            setState(943);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(950);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(951);
      match(C_grammarParser::RightParen);
      setState(952);
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

//----------------- LabeledStatementContext ------------------------------------------------------------------

C_grammarParser::LabeledStatementContext::LabeledStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::LabeledStatementContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

tree::TerminalNode* C_grammarParser::LabeledStatementContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

C_grammarParser::StatementContext* C_grammarParser::LabeledStatementContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

tree::TerminalNode* C_grammarParser::LabeledStatementContext::Case() {
  return getToken(C_grammarParser::Case, 0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::LabeledStatementContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::LabeledStatementContext::Default() {
  return getToken(C_grammarParser::Default, 0);
}


size_t C_grammarParser::LabeledStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleLabeledStatement;
}

void C_grammarParser::LabeledStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLabeledStatement(this);
}

void C_grammarParser::LabeledStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLabeledStatement(this);
}


antlrcpp::Any C_grammarParser::LabeledStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitLabeledStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::LabeledStatementContext* C_grammarParser::labeledStatement() {
  LabeledStatementContext *_localctx = _tracker.createInstance<LabeledStatementContext>(_ctx, getState());
  enterRule(_localctx, 142, C_grammarParser::RuleLabeledStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(966);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(955);
        match(C_grammarParser::Identifier);
        setState(956);
        match(C_grammarParser::Colon);
        setState(957);
        statement();
        break;
      }

      case C_grammarParser::Case: {
        enterOuterAlt(_localctx, 2);
        setState(958);
        match(C_grammarParser::Case);
        setState(959);
        constantExpression();
        setState(960);
        match(C_grammarParser::Colon);
        setState(961);
        statement();
        break;
      }

      case C_grammarParser::Default: {
        enterOuterAlt(_localctx, 3);
        setState(963);
        match(C_grammarParser::Default);
        setState(964);
        match(C_grammarParser::Colon);
        setState(965);
        statement();
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
  enterRule(_localctx, 144, C_grammarParser::RuleCompoundStatement);
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
    setState(968);
    match(C_grammarParser::LeftBrace);
    setState(970);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::T__7)
      | (1ULL << C_grammarParser::T__8)
      | (1ULL << C_grammarParser::T__9)
      | (1ULL << C_grammarParser::T__10)
      | (1ULL << C_grammarParser::T__11)
      | (1ULL << C_grammarParser::T__12)
      | (1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Break)
      | (1ULL << C_grammarParser::Case)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Continue)
      | (1ULL << C_grammarParser::Default)
      | (1ULL << C_grammarParser::Do)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::Goto)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Inline)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Sizeof)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Switch)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::While)
      | (1ULL << C_grammarParser::Alignas)
      | (1ULL << C_grammarParser::Alignof)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::Generic)
      | (1ULL << C_grammarParser::Noreturn)
      | (1ULL << C_grammarParser::StaticAssert)
      | (1ULL << C_grammarParser::ThreadLocal)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::LeftBrace))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
      | (1ULL << (C_grammarParser::PlusPlus - 71))
      | (1ULL << (C_grammarParser::Minus - 71))
      | (1ULL << (C_grammarParser::MinusMinus - 71))
      | (1ULL << (C_grammarParser::Star - 71))
      | (1ULL << (C_grammarParser::And - 71))
      | (1ULL << (C_grammarParser::AndAnd - 71))
      | (1ULL << (C_grammarParser::Not - 71))
      | (1ULL << (C_grammarParser::Tilde - 71))
      | (1ULL << (C_grammarParser::Semi - 71))
      | (1ULL << (C_grammarParser::Identifier - 71))
      | (1ULL << (C_grammarParser::Constant - 71))
      | (1ULL << (C_grammarParser::DigitSequence - 71))
      | (1ULL << (C_grammarParser::StringLiteral - 71))
      | (1ULL << (C_grammarParser::PragmaDirective - 71)))) != 0)) {
      setState(969);
      blockItemList();
    }
    setState(972);
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
  enterRule(_localctx, 146, C_grammarParser::RuleBlockItemList);
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
    setState(975); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(974);
      blockItem();
      setState(977); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::T__7)
      | (1ULL << C_grammarParser::T__8)
      | (1ULL << C_grammarParser::T__9)
      | (1ULL << C_grammarParser::T__10)
      | (1ULL << C_grammarParser::T__11)
      | (1ULL << C_grammarParser::T__12)
      | (1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Break)
      | (1ULL << C_grammarParser::Case)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Continue)
      | (1ULL << C_grammarParser::Default)
      | (1ULL << C_grammarParser::Do)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::For)
      | (1ULL << C_grammarParser::Goto)
      | (1ULL << C_grammarParser::If)
      | (1ULL << C_grammarParser::Inline)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Return)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Sizeof)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Switch)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::While)
      | (1ULL << C_grammarParser::Alignas)
      | (1ULL << C_grammarParser::Alignof)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::Generic)
      | (1ULL << C_grammarParser::Noreturn)
      | (1ULL << C_grammarParser::StaticAssert)
      | (1ULL << C_grammarParser::ThreadLocal)
      | (1ULL << C_grammarParser::LeftParen)
      | (1ULL << C_grammarParser::LeftBrace))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
      | (1ULL << (C_grammarParser::PlusPlus - 71))
      | (1ULL << (C_grammarParser::Minus - 71))
      | (1ULL << (C_grammarParser::MinusMinus - 71))
      | (1ULL << (C_grammarParser::Star - 71))
      | (1ULL << (C_grammarParser::And - 71))
      | (1ULL << (C_grammarParser::AndAnd - 71))
      | (1ULL << (C_grammarParser::Not - 71))
      | (1ULL << (C_grammarParser::Tilde - 71))
      | (1ULL << (C_grammarParser::Semi - 71))
      | (1ULL << (C_grammarParser::Identifier - 71))
      | (1ULL << (C_grammarParser::Constant - 71))
      | (1ULL << (C_grammarParser::DigitSequence - 71))
      | (1ULL << (C_grammarParser::StringLiteral - 71))
      | (1ULL << (C_grammarParser::PragmaDirective - 71)))) != 0));
   
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

tree::TerminalNode* C_grammarParser::BlockItemContext::PragmaDirective() {
  return getToken(C_grammarParser::PragmaDirective, 0);
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
  enterRule(_localctx, 148, C_grammarParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(982);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 118, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(979);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(980);
      declaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(981);
      match(C_grammarParser::PragmaDirective);
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
  enterRule(_localctx, 150, C_grammarParser::RuleExpressionStatement);
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
    setState(985);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::Sizeof)
      | (1ULL << C_grammarParser::Alignof)
      | (1ULL << C_grammarParser::Generic)
      | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
      | (1ULL << (C_grammarParser::PlusPlus - 71))
      | (1ULL << (C_grammarParser::Minus - 71))
      | (1ULL << (C_grammarParser::MinusMinus - 71))
      | (1ULL << (C_grammarParser::Star - 71))
      | (1ULL << (C_grammarParser::And - 71))
      | (1ULL << (C_grammarParser::AndAnd - 71))
      | (1ULL << (C_grammarParser::Not - 71))
      | (1ULL << (C_grammarParser::Tilde - 71))
      | (1ULL << (C_grammarParser::Identifier - 71))
      | (1ULL << (C_grammarParser::Constant - 71))
      | (1ULL << (C_grammarParser::DigitSequence - 71))
      | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
      setState(984);
      expression();
    }
    setState(987);
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

tree::TerminalNode* C_grammarParser::SelectionStatementContext::Switch() {
  return getToken(C_grammarParser::Switch, 0);
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
  enterRule(_localctx, 152, C_grammarParser::RuleSelectionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1004);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::If: {
        enterOuterAlt(_localctx, 1);
        setState(989);
        match(C_grammarParser::If);
        setState(990);
        match(C_grammarParser::LeftParen);
        setState(991);
        expression();
        setState(992);
        match(C_grammarParser::RightParen);
        setState(993);
        statement();
        setState(996);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 120, _ctx)) {
        case 1: {
          setState(994);
          match(C_grammarParser::Else);
          setState(995);
          statement();
          break;
        }

        default:
          break;
        }
        break;
      }

      case C_grammarParser::Switch: {
        enterOuterAlt(_localctx, 2);
        setState(998);
        match(C_grammarParser::Switch);
        setState(999);
        match(C_grammarParser::LeftParen);
        setState(1000);
        expression();
        setState(1001);
        match(C_grammarParser::RightParen);
        setState(1002);
        statement();
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

//----------------- IterationStatementContext ------------------------------------------------------------------

C_grammarParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::While() {
  return getToken(C_grammarParser::While, 0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::IterationStatementContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::StatementContext* C_grammarParser::IterationStatementContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::Do() {
  return getToken(C_grammarParser::Do, 0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::For() {
  return getToken(C_grammarParser::For, 0);
}

C_grammarParser::ForConditionContext* C_grammarParser::IterationStatementContext::forCondition() {
  return getRuleContext<C_grammarParser::ForConditionContext>(0);
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
  enterRule(_localctx, 154, C_grammarParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1026);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::While: {
        enterOuterAlt(_localctx, 1);
        setState(1006);
        match(C_grammarParser::While);
        setState(1007);
        match(C_grammarParser::LeftParen);
        setState(1008);
        expression();
        setState(1009);
        match(C_grammarParser::RightParen);
        setState(1010);
        statement();
        break;
      }

      case C_grammarParser::Do: {
        enterOuterAlt(_localctx, 2);
        setState(1012);
        match(C_grammarParser::Do);
        setState(1013);
        statement();
        setState(1014);
        match(C_grammarParser::While);
        setState(1015);
        match(C_grammarParser::LeftParen);
        setState(1016);
        expression();
        setState(1017);
        match(C_grammarParser::RightParen);
        setState(1018);
        match(C_grammarParser::Semi);
        break;
      }

      case C_grammarParser::For: {
        enterOuterAlt(_localctx, 3);
        setState(1020);
        match(C_grammarParser::For);
        setState(1021);
        match(C_grammarParser::LeftParen);
        setState(1022);
        forCondition();
        setState(1023);
        match(C_grammarParser::RightParen);
        setState(1024);
        statement();
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
  enterRule(_localctx, 156, C_grammarParser::RuleForCondition);
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
    setState(1032);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 124, _ctx)) {
    case 1: {
      setState(1028);
      forDeclaration();
      break;
    }

    case 2: {
      setState(1030);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
        | (1ULL << C_grammarParser::T__1)
        | (1ULL << C_grammarParser::T__2)
        | (1ULL << C_grammarParser::Sizeof)
        | (1ULL << C_grammarParser::Alignof)
        | (1ULL << C_grammarParser::Generic)
        | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
        | (1ULL << (C_grammarParser::PlusPlus - 71))
        | (1ULL << (C_grammarParser::Minus - 71))
        | (1ULL << (C_grammarParser::MinusMinus - 71))
        | (1ULL << (C_grammarParser::Star - 71))
        | (1ULL << (C_grammarParser::And - 71))
        | (1ULL << (C_grammarParser::AndAnd - 71))
        | (1ULL << (C_grammarParser::Not - 71))
        | (1ULL << (C_grammarParser::Tilde - 71))
        | (1ULL << (C_grammarParser::Identifier - 71))
        | (1ULL << (C_grammarParser::Constant - 71))
        | (1ULL << (C_grammarParser::DigitSequence - 71))
        | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
        setState(1029);
        expression();
      }
      break;
    }

    default:
      break;
    }
    setState(1034);
    match(C_grammarParser::Semi);
    setState(1036);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::Sizeof)
      | (1ULL << C_grammarParser::Alignof)
      | (1ULL << C_grammarParser::Generic)
      | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
      | (1ULL << (C_grammarParser::PlusPlus - 71))
      | (1ULL << (C_grammarParser::Minus - 71))
      | (1ULL << (C_grammarParser::MinusMinus - 71))
      | (1ULL << (C_grammarParser::Star - 71))
      | (1ULL << (C_grammarParser::And - 71))
      | (1ULL << (C_grammarParser::AndAnd - 71))
      | (1ULL << (C_grammarParser::Not - 71))
      | (1ULL << (C_grammarParser::Tilde - 71))
      | (1ULL << (C_grammarParser::Identifier - 71))
      | (1ULL << (C_grammarParser::Constant - 71))
      | (1ULL << (C_grammarParser::DigitSequence - 71))
      | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
      setState(1035);
      forExpression();
    }
    setState(1038);
    match(C_grammarParser::Semi);
    setState(1040);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__1)
      | (1ULL << C_grammarParser::T__2)
      | (1ULL << C_grammarParser::Sizeof)
      | (1ULL << C_grammarParser::Alignof)
      | (1ULL << C_grammarParser::Generic)
      | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
      | (1ULL << (C_grammarParser::PlusPlus - 71))
      | (1ULL << (C_grammarParser::Minus - 71))
      | (1ULL << (C_grammarParser::MinusMinus - 71))
      | (1ULL << (C_grammarParser::Star - 71))
      | (1ULL << (C_grammarParser::And - 71))
      | (1ULL << (C_grammarParser::AndAnd - 71))
      | (1ULL << (C_grammarParser::Not - 71))
      | (1ULL << (C_grammarParser::Tilde - 71))
      | (1ULL << (C_grammarParser::Identifier - 71))
      | (1ULL << (C_grammarParser::Constant - 71))
      | (1ULL << (C_grammarParser::DigitSequence - 71))
      | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
      setState(1039);
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
  enterRule(_localctx, 158, C_grammarParser::RuleForDeclaration);
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
    setState(1042);
    declarationSpecifiers();
    setState(1044);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 59) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 59)) & ((1ULL << (C_grammarParser::LeftParen - 59))
      | (1ULL << (C_grammarParser::Star - 59))
      | (1ULL << (C_grammarParser::Caret - 59))
      | (1ULL << (C_grammarParser::Identifier - 59)))) != 0)) {
      setState(1043);
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
  enterRule(_localctx, 160, C_grammarParser::RuleForExpression);
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
    setState(1046);
    assignmentExpression();
    setState(1051);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(1047);
      match(C_grammarParser::Comma);
      setState(1048);
      assignmentExpression();
      setState(1053);
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

//----------------- JumpStatementContext ------------------------------------------------------------------

C_grammarParser::JumpStatementContext::JumpStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::JumpStatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

tree::TerminalNode* C_grammarParser::JumpStatementContext::Goto() {
  return getToken(C_grammarParser::Goto, 0);
}

tree::TerminalNode* C_grammarParser::JumpStatementContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

tree::TerminalNode* C_grammarParser::JumpStatementContext::Return() {
  return getToken(C_grammarParser::Return, 0);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::JumpStatementContext::unaryExpression() {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::JumpStatementContext::Continue() {
  return getToken(C_grammarParser::Continue, 0);
}

tree::TerminalNode* C_grammarParser::JumpStatementContext::Break() {
  return getToken(C_grammarParser::Break, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::JumpStatementContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::JumpStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleJumpStatement;
}

void C_grammarParser::JumpStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJumpStatement(this);
}

void C_grammarParser::JumpStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJumpStatement(this);
}


antlrcpp::Any C_grammarParser::JumpStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitJumpStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::JumpStatementContext* C_grammarParser::jumpStatement() {
  JumpStatementContext *_localctx = _tracker.createInstance<JumpStatementContext>(_ctx, getState());
  enterRule(_localctx, 162, C_grammarParser::RuleJumpStatement);
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
    setState(1063);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 130, _ctx)) {
    case 1: {
      setState(1054);
      match(C_grammarParser::Goto);
      setState(1055);
      match(C_grammarParser::Identifier);
      break;
    }

    case 2: {
      setState(1056);
      _la = _input->LA(1);
      if (!(_la == C_grammarParser::Break

      || _la == C_grammarParser::Continue)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      break;
    }

    case 3: {
      setState(1057);
      match(C_grammarParser::Return);
      setState(1059);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
        | (1ULL << C_grammarParser::T__1)
        | (1ULL << C_grammarParser::T__2)
        | (1ULL << C_grammarParser::Sizeof)
        | (1ULL << C_grammarParser::Alignof)
        | (1ULL << C_grammarParser::Generic)
        | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 71)) & ((1ULL << (C_grammarParser::Plus - 71))
        | (1ULL << (C_grammarParser::PlusPlus - 71))
        | (1ULL << (C_grammarParser::Minus - 71))
        | (1ULL << (C_grammarParser::MinusMinus - 71))
        | (1ULL << (C_grammarParser::Star - 71))
        | (1ULL << (C_grammarParser::And - 71))
        | (1ULL << (C_grammarParser::AndAnd - 71))
        | (1ULL << (C_grammarParser::Not - 71))
        | (1ULL << (C_grammarParser::Tilde - 71))
        | (1ULL << (C_grammarParser::Identifier - 71))
        | (1ULL << (C_grammarParser::Constant - 71))
        | (1ULL << (C_grammarParser::DigitSequence - 71))
        | (1ULL << (C_grammarParser::StringLiteral - 71)))) != 0)) {
        setState(1058);
        expression();
      }
      break;
    }

    case 4: {
      setState(1061);
      match(C_grammarParser::Goto);
      setState(1062);
      unaryExpression();
      break;
    }

    default:
      break;
    }
    setState(1065);
    match(C_grammarParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
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
  enterRule(_localctx, 164, C_grammarParser::RuleCompilationUnit);
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
    setState(1068);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::T__7)
      | (1ULL << C_grammarParser::T__8)
      | (1ULL << C_grammarParser::T__9)
      | (1ULL << C_grammarParser::T__11)
      | (1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Inline)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::Alignas)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::Noreturn)
      | (1ULL << C_grammarParser::StaticAssert)
      | (1ULL << C_grammarParser::ThreadLocal)
      | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & ((1ULL << (C_grammarParser::Star - 75))
      | (1ULL << (C_grammarParser::Caret - 75))
      | (1ULL << (C_grammarParser::Semi - 75))
      | (1ULL << (C_grammarParser::Identifier - 75)))) != 0)) {
      setState(1067);
      translationUnit();
    }
    setState(1070);
    match(C_grammarParser::EOF);
   
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
  enterRule(_localctx, 166, C_grammarParser::RuleTranslationUnit);
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
    setState(1073); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(1072);
      externalDeclaration();
      setState(1075); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::T__7)
      | (1ULL << C_grammarParser::T__8)
      | (1ULL << C_grammarParser::T__9)
      | (1ULL << C_grammarParser::T__11)
      | (1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Inline)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::Alignas)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::Noreturn)
      | (1ULL << C_grammarParser::StaticAssert)
      | (1ULL << C_grammarParser::ThreadLocal)
      | (1ULL << C_grammarParser::LeftParen))) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & ((1ULL << (C_grammarParser::Star - 75))
      | (1ULL << (C_grammarParser::Caret - 75))
      | (1ULL << (C_grammarParser::Semi - 75))
      | (1ULL << (C_grammarParser::Identifier - 75)))) != 0));
   
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
  enterRule(_localctx, 168, C_grammarParser::RuleExternalDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1080);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 133, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1077);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1078);
      declaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1079);
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
  enterRule(_localctx, 170, C_grammarParser::RuleFunctionDefinition);
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
    setState(1083);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 134, _ctx)) {
    case 1: {
      setState(1082);
      declarationSpecifiers();
      break;
    }

    default:
      break;
    }
    setState(1085);
    declarator();
    setState(1087);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::T__7)
      | (1ULL << C_grammarParser::T__8)
      | (1ULL << C_grammarParser::T__9)
      | (1ULL << C_grammarParser::T__11)
      | (1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Inline)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::Alignas)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::Noreturn)
      | (1ULL << C_grammarParser::StaticAssert)
      | (1ULL << C_grammarParser::ThreadLocal))) != 0) || _la == C_grammarParser::Identifier) {
      setState(1086);
      declarationList();
    }
    setState(1089);
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
  enterRule(_localctx, 172, C_grammarParser::RuleDeclarationList);
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
    setState(1092); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(1091);
      declaration();
      setState(1094); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << C_grammarParser::T__0)
      | (1ULL << C_grammarParser::T__3)
      | (1ULL << C_grammarParser::T__4)
      | (1ULL << C_grammarParser::T__5)
      | (1ULL << C_grammarParser::T__6)
      | (1ULL << C_grammarParser::T__7)
      | (1ULL << C_grammarParser::T__8)
      | (1ULL << C_grammarParser::T__9)
      | (1ULL << C_grammarParser::T__11)
      | (1ULL << C_grammarParser::Auto)
      | (1ULL << C_grammarParser::Char)
      | (1ULL << C_grammarParser::Const)
      | (1ULL << C_grammarParser::Double)
      | (1ULL << C_grammarParser::Enum)
      | (1ULL << C_grammarParser::Extern)
      | (1ULL << C_grammarParser::Float)
      | (1ULL << C_grammarParser::Inline)
      | (1ULL << C_grammarParser::Int)
      | (1ULL << C_grammarParser::Long)
      | (1ULL << C_grammarParser::Register)
      | (1ULL << C_grammarParser::Restrict)
      | (1ULL << C_grammarParser::Short)
      | (1ULL << C_grammarParser::Signed)
      | (1ULL << C_grammarParser::Static)
      | (1ULL << C_grammarParser::Struct)
      | (1ULL << C_grammarParser::Typedef)
      | (1ULL << C_grammarParser::Union)
      | (1ULL << C_grammarParser::Unsigned)
      | (1ULL << C_grammarParser::Void)
      | (1ULL << C_grammarParser::Volatile)
      | (1ULL << C_grammarParser::Alignas)
      | (1ULL << C_grammarParser::Atomic)
      | (1ULL << C_grammarParser::Bool)
      | (1ULL << C_grammarParser::Complex)
      | (1ULL << C_grammarParser::Noreturn)
      | (1ULL << C_grammarParser::StaticAssert)
      | (1ULL << C_grammarParser::ThreadLocal))) != 0) || _la == C_grammarParser::Identifier);
   
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
    case 31: return typeSpecifierSempred(dynamic_cast<TypeSpecifierContext *>(context), predicateIndex);
    case 48: return directDeclaratorSempred(dynamic_cast<DirectDeclaratorContext *>(context), predicateIndex);
    case 62: return directAbstractDeclaratorSempred(dynamic_cast<DirectAbstractDeclaratorContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool C_grammarParser::typeSpecifierSempred(TypeSpecifierContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C_grammarParser::directDeclaratorSempred(DirectDeclaratorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 8);
    case 2: return precpred(_ctx, 7);
    case 3: return precpred(_ctx, 6);
    case 4: return precpred(_ctx, 5);
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool C_grammarParser::directAbstractDeclaratorSempred(DirectAbstractDeclaratorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 7: return precpred(_ctx, 5);
    case 8: return precpred(_ctx, 4);
    case 9: return precpred(_ctx, 3);
    case 10: return precpred(_ctx, 2);
    case 11: return precpred(_ctx, 1);

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
  "primaryExpression", "genericSelection", "genericAssocList", "genericAssociation", 
  "postfixExpression", "argumentExpressionList", "unaryExpression", "unaryOperator", 
  "castExpression", "multiplicativeExpression", "additiveExpression", "shiftExpression", 
  "relationalExpression", "equalityExpression", "andExpression", "exclusiveOrExpression", 
  "inclusiveOrExpression", "logicalAndExpression", "logicalOrExpression", 
  "conditionalExpression", "assignmentExpression", "assignmentOperator", 
  "expression", "constantExpression", "declaration", "declarationSpecifiers", 
  "declarationSpecifiers2", "declarationSpecifier", "initDeclaratorList", 
  "initDeclarator", "storageClassSpecifier", "typeSpecifier", "structOrUnionSpecifier", 
  "structOrUnion", "structDeclarationList", "structDeclaration", "specifierQualifierList", 
  "structDeclaratorList", "structDeclarator", "enumSpecifier", "enumeratorList", 
  "enumerator", "enumerationConstant", "atomicTypeSpecifier", "typeQualifier", 
  "functionSpecifier", "alignmentSpecifier", "declarator", "directDeclarator", 
  "gccDeclaratorExtension", "gccAttributeSpecifier", "gccAttributeList", 
  "gccAttribute", "nestedParenthesesBlock", "pointer", "typeQualifierList", 
  "parameterTypeList", "parameterList", "parameterDeclaration", "identifierList", 
  "typeName", "abstractDeclarator", "directAbstractDeclarator", "typedefName", 
  "initializer", "initializerList", "designation", "designatorList", "designator", 
  "staticAssertDeclaration", "statement", "labeledStatement", "compoundStatement", 
  "blockItemList", "blockItem", "expressionStatement", "selectionStatement", 
  "iterationStatement", "forCondition", "forDeclaration", "forExpression", 
  "jumpStatement", "compilationUnit", "translationUnit", "externalDeclaration", 
  "functionDefinition", "declarationList"
};

std::vector<std::string> C_grammarParser::_literalNames = {
  "", "'__extension__'", "'__builtin_va_arg'", "'__builtin_offsetof'", "'__m128'", 
  "'__m128d'", "'__m128i'", "'__typeof__'", "'__inline__'", "'__stdcall'", 
  "'__declspec'", "'__asm'", "'__attribute__'", "'__asm__'", "'__volatile__'", 
  "'auto'", "'break'", "'case'", "'char'", "'const'", "'continue'", "'default'", 
  "'do'", "'double'", "'else'", "'enum'", "'extern'", "'float'", "'for'", 
  "'goto'", "'if'", "'inline'", "'int'", "'long'", "'register'", "'restrict'", 
  "'return'", "'short'", "'signed'", "'sizeof'", "'static'", "'struct'", 
  "'switch'", "'typedef'", "'union'", "'unsigned'", "'void'", "'volatile'", 
  "'while'", "'_Alignas'", "'_Alignof'", "'_Atomic'", "'_Bool'", "'_Complex'", 
  "'_Generic'", "'_Imaginary'", "'_Noreturn'", "'_Static_assert'", "'_Thread_local'", 
  "'('", "')'", "'['", "']'", "'{'", "'}'", "'<'", "'<='", "'>'", "'>='", 
  "'<<'", "'>>'", "'+'", "'++'", "'-'", "'--'", "'*'", "'/'", "'%'", "'&'", 
  "'|'", "'&&'", "'||'", "'^'", "'!'", "'~'", "'\u003F'", "':'", "';'", 
  "','", "'='", "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", 
  "'&='", "'^='", "'|='", "'=='", "'!='", "'->'", "'.'", "'...'"
};

std::vector<std::string> C_grammarParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "Auto", "Break", 
  "Case", "Char", "Const", "Continue", "Default", "Do", "Double", "Else", 
  "Enum", "Extern", "Float", "For", "Goto", "If", "Inline", "Int", "Long", 
  "Register", "Restrict", "Return", "Short", "Signed", "Sizeof", "Static", 
  "Struct", "Switch", "Typedef", "Union", "Unsigned", "Void", "Volatile", 
  "While", "Alignas", "Alignof", "Atomic", "Bool", "Complex", "Generic", 
  "Imaginary", "Noreturn", "StaticAssert", "ThreadLocal", "LeftParen", "RightParen", 
  "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "Less", "LessEqual", 
  "Greater", "GreaterEqual", "LeftShift", "RightShift", "Plus", "PlusPlus", 
  "Minus", "MinusMinus", "Star", "Div", "Mod", "And", "Or", "AndAnd", "OrOr", 
  "Caret", "Not", "Tilde", "Question", "Colon", "Semi", "Comma", "Assign", 
  "StarAssign", "DivAssign", "ModAssign", "PlusAssign", "MinusAssign", "LeftShiftAssign", 
  "RightShiftAssign", "AndAssign", "XorAssign", "OrAssign", "Equal", "NotEqual", 
  "Arrow", "Dot", "Ellipsis", "Identifier", "Constant", "DigitSequence", 
  "StringLiteral", "ComplexDefine", "IncludeDirective", "AsmBlock", "LineAfterPreprocessing", 
  "LineDirective", "PragmaDirective", "Whitespace", "Newline", "BlockComment", 
  "LineComment"
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
    0x3, 0x78, 0x44b, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9, 
    0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 
    0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 
    0x46, 0x9, 0x46, 0x4, 0x47, 0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 
    0x9, 0x49, 0x4, 0x4a, 0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 
    0x4c, 0x4, 0x4d, 0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 
    0x4, 0x50, 0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 
    0x53, 0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56, 
    0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x6, 0x2, 0xb4, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0xb5, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0xbe, 
    0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0xd2, 0xa, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0xde, 0xa, 0x4, 0xc, 0x4, 
    0xe, 0x4, 0xe1, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0xe5, 0xa, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0xec, 0xa, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 
    0x6, 0xf4, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0xf8, 0xa, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x100, 
    0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x106, 0xa, 
    0x6, 0xc, 0x6, 0xe, 0x6, 0x109, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x7, 0x7, 0x10e, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x111, 0xb, 0x7, 0x3, 
    0x8, 0x7, 0x8, 0x114, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x117, 0xb, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x124, 0xa, 0x8, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0xa, 0x5, 0xa, 0x129, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x132, 0xa, 
    0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x137, 0xa, 0xb, 0xc, 0xb, 
    0xe, 0xb, 0x13a, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x13f, 
    0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x142, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x7, 0xd, 0x147, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x14a, 0xb, 0xd, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0x14f, 0xa, 0xe, 0xc, 0xe, 0xe, 
    0xe, 0x152, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0x157, 
    0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0x15a, 0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x7, 0x10, 0x15f, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x162, 
    0xb, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 0x167, 0xa, 0x11, 
    0xc, 0x11, 0xe, 0x11, 0x16a, 0xb, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x7, 0x12, 0x16f, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x172, 0xb, 0x12, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0x177, 0xa, 0x13, 0xc, 0x13, 
    0xe, 0x13, 0x17a, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 
    0x17f, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0x182, 0xb, 0x14, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x18a, 
    0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 
    0x16, 0x5, 0x16, 0x192, 0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x7, 0x18, 0x199, 0xa, 0x18, 0xc, 0x18, 0xe, 0x18, 
    0x19c, 0xb, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 
    0x1a2, 0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x1a7, 
    0xa, 0x1a, 0x3, 0x1b, 0x6, 0x1b, 0x1aa, 0xa, 0x1b, 0xd, 0x1b, 0xe, 0x1b, 
    0x1ab, 0x3, 0x1c, 0x6, 0x1c, 0x1af, 0xa, 0x1c, 0xd, 0x1c, 0xe, 0x1c, 
    0x1b0, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 
    0x1b8, 0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x1bd, 
    0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 0x1c0, 0xb, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 
    0x3, 0x1f, 0x5, 0x1f, 0x1c5, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 
    0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x5, 0x21, 0x1d8, 0xa, 0x21, 0x3, 0x21, 0x3, 0x21, 0x7, 0x21, 
    0x1dc, 0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x1df, 0xb, 0x21, 0x3, 0x22, 
    0x3, 0x22, 0x5, 0x22, 0x1e3, 0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x1ec, 0xa, 0x22, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x6, 0x24, 0x1f1, 0xa, 0x24, 0xd, 0x24, 
    0xe, 0x24, 0x1f2, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x1f7, 0xa, 0x25, 
    0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x1fc, 0xa, 0x25, 0x3, 0x26, 
    0x3, 0x26, 0x5, 0x26, 0x200, 0xa, 0x26, 0x3, 0x26, 0x5, 0x26, 0x203, 
    0xa, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x7, 0x27, 0x208, 0xa, 0x27, 
    0xc, 0x27, 0xe, 0x27, 0x20b, 0xb, 0x27, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 
    0x20f, 0xa, 0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 0x213, 0xa, 0x28, 
    0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x217, 0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 
    0x3, 0x29, 0x5, 0x29, 0x21c, 0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 
    0x3, 0x29, 0x5, 0x29, 0x222, 0xa, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
    0x7, 0x2a, 0x227, 0xa, 0x2a, 0xc, 0x2a, 0xe, 0x2a, 0x22a, 0xb, 0x2a, 
    0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x22f, 0xa, 0x2b, 0x3, 0x2c, 
    0x3, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 
    0x2e, 0x3, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 
    0x3, 0x2f, 0x5, 0x2f, 0x240, 0xa, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 
    0x3, 0x30, 0x5, 0x30, 0x246, 0xa, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x31, 
    0x5, 0x31, 0x24b, 0xa, 0x31, 0x3, 0x31, 0x3, 0x31, 0x7, 0x31, 0x24f, 
    0xa, 0x31, 0xc, 0x31, 0xe, 0x31, 0x252, 0xb, 0x31, 0x3, 0x32, 0x3, 0x32, 
    0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 
    0x32, 0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x25f, 0xa, 0x32, 0x3, 0x32, 
    0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x265, 0xa, 0x32, 0x3, 0x32, 
    0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x26a, 0xa, 0x32, 0x3, 0x32, 0x5, 0x32, 
    0x26d, 0xa, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 
    0x5, 0x32, 0x274, 0xa, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 
    0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 
    0x32, 0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x283, 0xa, 0x32, 0x3, 0x32, 
    0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 
    0x32, 0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x28f, 0xa, 0x32, 0x3, 0x32, 
    0x7, 0x32, 0x292, 0xa, 0x32, 0xc, 0x32, 0xe, 0x32, 0x295, 0xb, 0x32, 
    0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x6, 0x33, 0x29a, 0xa, 0x33, 0xd, 0x33, 
    0xe, 0x33, 0x29b, 0x3, 0x33, 0x3, 0x33, 0x5, 0x33, 0x2a0, 0xa, 0x33, 
    0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 
    0x34, 0x3, 0x35, 0x5, 0x35, 0x2aa, 0xa, 0x35, 0x3, 0x35, 0x3, 0x35, 
    0x5, 0x35, 0x2ae, 0xa, 0x35, 0x7, 0x35, 0x2b0, 0xa, 0x35, 0xc, 0x35, 
    0xe, 0x35, 0x2b3, 0xb, 0x35, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 
    0x2b8, 0xa, 0x36, 0x3, 0x36, 0x5, 0x36, 0x2bb, 0xa, 0x36, 0x3, 0x37, 
    0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x7, 0x37, 0x2c2, 0xa, 0x37, 
    0xc, 0x37, 0xe, 0x37, 0x2c5, 0xb, 0x37, 0x3, 0x38, 0x3, 0x38, 0x5, 0x38, 
    0x2c9, 0xa, 0x38, 0x6, 0x38, 0x2cb, 0xa, 0x38, 0xd, 0x38, 0xe, 0x38, 
    0x2cc, 0x3, 0x39, 0x6, 0x39, 0x2d0, 0xa, 0x39, 0xd, 0x39, 0xe, 0x39, 
    0x2d1, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 0x2d7, 0xa, 0x3a, 
    0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x7, 0x3b, 0x2dc, 0xa, 0x3b, 0xc, 0x3b, 
    0xe, 0x3b, 0x2df, 0xb, 0x3b, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 
    0x3, 0x3c, 0x5, 0x3c, 0x2e6, 0xa, 0x3c, 0x5, 0x3c, 0x2e8, 0xa, 0x3c, 
    0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x7, 0x3d, 0x2ed, 0xa, 0x3d, 0xc, 0x3d, 
    0xe, 0x3d, 0x2f0, 0xb, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 0x5, 0x3e, 0x2f4, 
    0xa, 0x3e, 0x3, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 0x2f8, 0xa, 0x3f, 0x3, 0x3f, 
    0x3, 0x3f, 0x7, 0x3f, 0x2fc, 0xa, 0x3f, 0xc, 0x3f, 0xe, 0x3f, 0x2ff, 
    0xb, 0x3f, 0x5, 0x3f, 0x301, 0xa, 0x3f, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x308, 0xa, 0x40, 0xc, 0x40, 0xe, 0x40, 
    0x30b, 0xb, 0x40, 0x3, 0x40, 0x3, 0x40, 0x5, 0x40, 0x30f, 0xa, 0x40, 
    0x3, 0x40, 0x5, 0x40, 0x312, 0xa, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x5, 0x40, 0x318, 0xa, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 
    0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x5, 0x40, 0x328, 
    0xa, 0x40, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x32c, 0xa, 0x40, 0xc, 0x40, 
    0xe, 0x40, 0x32f, 0xb, 0x40, 0x5, 0x40, 0x331, 0xa, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x3, 0x40, 0x5, 0x40, 0x336, 0xa, 0x40, 0x3, 0x40, 0x5, 0x40, 
    0x339, 0xa, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x5, 0x40, 0x340, 0xa, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 
    0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x5, 0x40, 0x353, 0xa, 0x40, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x357, 
    0xa, 0x40, 0xc, 0x40, 0xe, 0x40, 0x35a, 0xb, 0x40, 0x7, 0x40, 0x35c, 
    0xa, 0x40, 0xc, 0x40, 0xe, 0x40, 0x35f, 0xb, 0x40, 0x3, 0x41, 0x3, 0x41, 
    0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x367, 0xa, 0x42, 
    0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x36b, 0xa, 0x42, 0x3, 0x43, 0x5, 0x43, 
    0x36e, 0xa, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x5, 0x43, 0x373, 
    0xa, 0x43, 0x3, 0x43, 0x7, 0x43, 0x376, 0xa, 0x43, 0xc, 0x43, 0xe, 0x43, 
    0x379, 0xb, 0x43, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x45, 0x6, 0x45, 
    0x37f, 0xa, 0x45, 0xd, 0x45, 0xe, 0x45, 0x380, 0x3, 0x46, 0x3, 0x46, 
    0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x5, 0x46, 0x389, 0xa, 0x46, 
    0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x6, 0x47, 0x390, 
    0xa, 0x47, 0xd, 0x47, 0xe, 0x47, 0x391, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 
    0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 
    0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x7, 0x48, 
    0x3a3, 0xa, 0x48, 0xc, 0x48, 0xe, 0x48, 0x3a6, 0xb, 0x48, 0x5, 0x48, 
    0x3a8, 0xa, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x7, 0x48, 
    0x3ae, 0xa, 0x48, 0xc, 0x48, 0xe, 0x48, 0x3b1, 0xb, 0x48, 0x5, 0x48, 
    0x3b3, 0xa, 0x48, 0x7, 0x48, 0x3b5, 0xa, 0x48, 0xc, 0x48, 0xe, 0x48, 
    0x3b8, 0xb, 0x48, 0x3, 0x48, 0x3, 0x48, 0x5, 0x48, 0x3bc, 0xa, 0x48, 
    0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 
    0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x5, 0x49, 0x3c9, 
    0xa, 0x49, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x3cd, 0xa, 0x4a, 0x3, 0x4a, 
    0x3, 0x4a, 0x3, 0x4b, 0x6, 0x4b, 0x3d2, 0xa, 0x4b, 0xd, 0x4b, 0xe, 0x4b, 
    0x3d3, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x3d9, 0xa, 0x4c, 
    0x3, 0x4d, 0x5, 0x4d, 0x3dc, 0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4e, 
    0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x5, 
    0x4e, 0x3e7, 0xa, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 
    0x3, 0x4e, 0x3, 0x4e, 0x5, 0x4e, 0x3ef, 0xa, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 
    0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 
    0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 
    0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x5, 0x4f, 0x405, 
    0xa, 0x4f, 0x3, 0x50, 0x3, 0x50, 0x5, 0x50, 0x409, 0xa, 0x50, 0x5, 0x50, 
    0x40b, 0xa, 0x50, 0x3, 0x50, 0x3, 0x50, 0x5, 0x50, 0x40f, 0xa, 0x50, 
    0x3, 0x50, 0x3, 0x50, 0x5, 0x50, 0x413, 0xa, 0x50, 0x3, 0x51, 0x3, 0x51, 
    0x5, 0x51, 0x417, 0xa, 0x51, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x7, 0x52, 
    0x41c, 0xa, 0x52, 0xc, 0x52, 0xe, 0x52, 0x41f, 0xb, 0x52, 0x3, 0x53, 
    0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x5, 0x53, 0x426, 0xa, 0x53, 
    0x3, 0x53, 0x3, 0x53, 0x5, 0x53, 0x42a, 0xa, 0x53, 0x3, 0x53, 0x3, 0x53, 
    0x3, 0x54, 0x5, 0x54, 0x42f, 0xa, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x55, 
    0x6, 0x55, 0x434, 0xa, 0x55, 0xd, 0x55, 0xe, 0x55, 0x435, 0x3, 0x56, 
    0x3, 0x56, 0x3, 0x56, 0x5, 0x56, 0x43b, 0xa, 0x56, 0x3, 0x57, 0x5, 0x57, 
    0x43e, 0xa, 0x57, 0x3, 0x57, 0x3, 0x57, 0x5, 0x57, 0x442, 0xa, 0x57, 
    0x3, 0x57, 0x3, 0x57, 0x3, 0x58, 0x6, 0x58, 0x447, 0xa, 0x58, 0xd, 0x58, 
    0xe, 0x58, 0x448, 0x3, 0x58, 0x2, 0x5, 0x40, 0x62, 0x7e, 0x59, 0x2, 
    0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 
    0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 
    0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 
    0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 
    0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 
    0x7e, 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 
    0x96, 0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 
    0xae, 0x2, 0x19, 0x3, 0x2, 0x68, 0x69, 0x4, 0x2, 0x4a, 0x4a, 0x4c, 0x4c, 
    0x5, 0x2, 0x29, 0x29, 0x4a, 0x4a, 0x4c, 0x4c, 0x4, 0x2, 0x29, 0x29, 
    0x34, 0x34, 0x7, 0x2, 0x49, 0x49, 0x4b, 0x4b, 0x4d, 0x4d, 0x50, 0x50, 
    0x55, 0x56, 0x3, 0x2, 0x4d, 0x4f, 0x4, 0x2, 0x49, 0x49, 0x4b, 0x4b, 
    0x3, 0x2, 0x47, 0x48, 0x3, 0x2, 0x43, 0x46, 0x3, 0x2, 0x66, 0x67, 0x3, 
    0x2, 0x5b, 0x65, 0x8, 0x2, 0x11, 0x11, 0x1c, 0x1c, 0x24, 0x24, 0x2a, 
    0x2a, 0x2d, 0x2d, 0x3c, 0x3c, 0xa, 0x2, 0x6, 0x8, 0x14, 0x14, 0x19, 
    0x19, 0x1d, 0x1d, 0x22, 0x23, 0x27, 0x28, 0x2f, 0x30, 0x36, 0x37, 0x3, 
    0x2, 0x6, 0x8, 0x4, 0x2, 0x2b, 0x2b, 0x2e, 0x2e, 0x6, 0x2, 0x15, 0x15, 
    0x25, 0x25, 0x31, 0x31, 0x35, 0x35, 0x5, 0x2, 0xa, 0xb, 0x21, 0x21, 
    0x3a, 0x3a, 0x4, 0x2, 0x3d, 0x3e, 0x5a, 0x5a, 0x3, 0x2, 0x3d, 0x3e, 
    0x4, 0x2, 0x4d, 0x4d, 0x54, 0x54, 0x4, 0x2, 0xd, 0xd, 0xf, 0xf, 0x4, 
    0x2, 0x10, 0x10, 0x31, 0x31, 0x4, 0x2, 0x12, 0x12, 0x16, 0x16, 0x2, 
    0x4a9, 0x2, 0xd1, 0x3, 0x2, 0x2, 0x2, 0x4, 0xd3, 0x3, 0x2, 0x2, 0x2, 
    0x6, 0xda, 0x3, 0x2, 0x2, 0x2, 0x8, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xa, 0xf7, 
    0x3, 0x2, 0x2, 0x2, 0xc, 0x10a, 0x3, 0x2, 0x2, 0x2, 0xe, 0x115, 0x3, 
    0x2, 0x2, 0x2, 0x10, 0x125, 0x3, 0x2, 0x2, 0x2, 0x12, 0x131, 0x3, 0x2, 
    0x2, 0x2, 0x14, 0x133, 0x3, 0x2, 0x2, 0x2, 0x16, 0x13b, 0x3, 0x2, 0x2, 
    0x2, 0x18, 0x143, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x14b, 0x3, 0x2, 0x2, 0x2, 
    0x1c, 0x153, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x20, 
    0x163, 0x3, 0x2, 0x2, 0x2, 0x22, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x24, 0x173, 
    0x3, 0x2, 0x2, 0x2, 0x26, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x28, 0x183, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x191, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x193, 0x3, 0x2, 
    0x2, 0x2, 0x2e, 0x195, 0x3, 0x2, 0x2, 0x2, 0x30, 0x19d, 0x3, 0x2, 0x2, 
    0x2, 0x32, 0x1a6, 0x3, 0x2, 0x2, 0x2, 0x34, 0x1a9, 0x3, 0x2, 0x2, 0x2, 
    0x36, 0x1ae, 0x3, 0x2, 0x2, 0x2, 0x38, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x3a, 
    0x1b9, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x1c1, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x1c6, 
    0x3, 0x2, 0x2, 0x2, 0x40, 0x1d7, 0x3, 0x2, 0x2, 0x2, 0x42, 0x1eb, 0x3, 
    0x2, 0x2, 0x2, 0x44, 0x1ed, 0x3, 0x2, 0x2, 0x2, 0x46, 0x1f0, 0x3, 0x2, 
    0x2, 0x2, 0x48, 0x1fb, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x1ff, 0x3, 0x2, 0x2, 
    0x2, 0x4c, 0x204, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x212, 0x3, 0x2, 0x2, 0x2, 
    0x50, 0x221, 0x3, 0x2, 0x2, 0x2, 0x52, 0x223, 0x3, 0x2, 0x2, 0x2, 0x54, 
    0x22b, 0x3, 0x2, 0x2, 0x2, 0x56, 0x230, 0x3, 0x2, 0x2, 0x2, 0x58, 0x232, 
    0x3, 0x2, 0x2, 0x2, 0x5a, 0x237, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x23f, 0x3, 
    0x2, 0x2, 0x2, 0x5e, 0x241, 0x3, 0x2, 0x2, 0x2, 0x60, 0x24a, 0x3, 0x2, 
    0x2, 0x2, 0x62, 0x264, 0x3, 0x2, 0x2, 0x2, 0x64, 0x29f, 0x3, 0x2, 0x2, 
    0x2, 0x66, 0x2a1, 0x3, 0x2, 0x2, 0x2, 0x68, 0x2a9, 0x3, 0x2, 0x2, 0x2, 
    0x6a, 0x2b4, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x2c3, 0x3, 0x2, 0x2, 0x2, 0x6e, 
    0x2ca, 0x3, 0x2, 0x2, 0x2, 0x70, 0x2cf, 0x3, 0x2, 0x2, 0x2, 0x72, 0x2d3, 
    0x3, 0x2, 0x2, 0x2, 0x74, 0x2d8, 0x3, 0x2, 0x2, 0x2, 0x76, 0x2e7, 0x3, 
    0x2, 0x2, 0x2, 0x78, 0x2e9, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x2f1, 0x3, 0x2, 
    0x2, 0x2, 0x7c, 0x300, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x330, 0x3, 0x2, 0x2, 
    0x2, 0x80, 0x360, 0x3, 0x2, 0x2, 0x2, 0x82, 0x36a, 0x3, 0x2, 0x2, 0x2, 
    0x84, 0x36d, 0x3, 0x2, 0x2, 0x2, 0x86, 0x37a, 0x3, 0x2, 0x2, 0x2, 0x88, 
    0x37e, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x388, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x38a, 
    0x3, 0x2, 0x2, 0x2, 0x8e, 0x3bb, 0x3, 0x2, 0x2, 0x2, 0x90, 0x3c8, 0x3, 
    0x2, 0x2, 0x2, 0x92, 0x3ca, 0x3, 0x2, 0x2, 0x2, 0x94, 0x3d1, 0x3, 0x2, 
    0x2, 0x2, 0x96, 0x3d8, 0x3, 0x2, 0x2, 0x2, 0x98, 0x3db, 0x3, 0x2, 0x2, 
    0x2, 0x9a, 0x3ee, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x404, 0x3, 0x2, 0x2, 0x2, 
    0x9e, 0x40a, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x414, 0x3, 0x2, 0x2, 0x2, 0xa2, 
    0x418, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x429, 0x3, 0x2, 0x2, 0x2, 0xa6, 0x42e, 
    0x3, 0x2, 0x2, 0x2, 0xa8, 0x433, 0x3, 0x2, 0x2, 0x2, 0xaa, 0x43a, 0x3, 
    0x2, 0x2, 0x2, 0xac, 0x43d, 0x3, 0x2, 0x2, 0x2, 0xae, 0x446, 0x3, 0x2, 
    0x2, 0x2, 0xb0, 0xd2, 0x7, 0x6b, 0x2, 0x2, 0xb1, 0xd2, 0x7, 0x6c, 0x2, 
    0x2, 0xb2, 0xb4, 0x7, 0x6e, 0x2, 0x2, 0xb3, 0xb2, 0x3, 0x2, 0x2, 0x2, 
    0xb4, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb5, 
    0xb6, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 
    0x7, 0x3d, 0x2, 0x2, 0xb8, 0xb9, 0x5, 0x2e, 0x18, 0x2, 0xb9, 0xba, 0x7, 
    0x3e, 0x2, 0x2, 0xba, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xbb, 0xd2, 0x5, 0x4, 
    0x3, 0x2, 0xbc, 0xbe, 0x7, 0x3, 0x2, 0x2, 0xbd, 0xbc, 0x3, 0x2, 0x2, 
    0x2, 0xbd, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 
    0xbf, 0xc0, 0x7, 0x3d, 0x2, 0x2, 0xc0, 0xc1, 0x5, 0x92, 0x4a, 0x2, 0xc1, 
    0xc2, 0x7, 0x3e, 0x2, 0x2, 0xc2, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 
    0x7, 0x4, 0x2, 0x2, 0xc4, 0xc5, 0x7, 0x3d, 0x2, 0x2, 0xc5, 0xc6, 0x5, 
    0xe, 0x8, 0x2, 0xc6, 0xc7, 0x7, 0x5a, 0x2, 0x2, 0xc7, 0xc8, 0x5, 0x7a, 
    0x3e, 0x2, 0xc8, 0xc9, 0x7, 0x3e, 0x2, 0x2, 0xc9, 0xd2, 0x3, 0x2, 0x2, 
    0x2, 0xca, 0xcb, 0x7, 0x5, 0x2, 0x2, 0xcb, 0xcc, 0x7, 0x3d, 0x2, 0x2, 
    0xcc, 0xcd, 0x5, 0x7a, 0x3e, 0x2, 0xcd, 0xce, 0x7, 0x5a, 0x2, 0x2, 0xce, 
    0xcf, 0x5, 0xe, 0x8, 0x2, 0xcf, 0xd0, 0x7, 0x3e, 0x2, 0x2, 0xd0, 0xd2, 
    0x3, 0x2, 0x2, 0x2, 0xd1, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xb1, 0x3, 
    0x2, 0x2, 0x2, 0xd1, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xb7, 0x3, 0x2, 
    0x2, 0x2, 0xd1, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xbd, 0x3, 0x2, 0x2, 
    0x2, 0xd1, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xca, 0x3, 0x2, 0x2, 0x2, 
    0xd2, 0x3, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd4, 0x7, 0x38, 0x2, 0x2, 0xd4, 
    0xd5, 0x7, 0x3d, 0x2, 0x2, 0xd5, 0xd6, 0x5, 0x2a, 0x16, 0x2, 0xd6, 0xd7, 
    0x7, 0x5a, 0x2, 0x2, 0xd7, 0xd8, 0x5, 0x6, 0x4, 0x2, 0xd8, 0xd9, 0x7, 
    0x3e, 0x2, 0x2, 0xd9, 0x5, 0x3, 0x2, 0x2, 0x2, 0xda, 0xdf, 0x5, 0x8, 
    0x5, 0x2, 0xdb, 0xdc, 0x7, 0x5a, 0x2, 0x2, 0xdc, 0xde, 0x5, 0x8, 0x5, 
    0x2, 0xdd, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xde, 0xe1, 0x3, 0x2, 0x2, 0x2, 
    0xdf, 0xdd, 0x3, 0x2, 0x2, 0x2, 0xdf, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe0, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xdf, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe5, 
    0x5, 0x7a, 0x3e, 0x2, 0xe3, 0xe5, 0x7, 0x17, 0x2, 0x2, 0xe4, 0xe2, 0x3, 
    0x2, 0x2, 0x2, 0xe4, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe6, 0x3, 0x2, 
    0x2, 0x2, 0xe6, 0xe7, 0x7, 0x58, 0x2, 0x2, 0xe7, 0xe8, 0x5, 0x2a, 0x16, 
    0x2, 0xe8, 0x9, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xf8, 0x5, 0x2, 0x2, 0x2, 
    0xea, 0xec, 0x7, 0x3, 0x2, 0x2, 0xeb, 0xea, 0x3, 0x2, 0x2, 0x2, 0xeb, 
    0xec, 0x3, 0x2, 0x2, 0x2, 0xec, 0xed, 0x3, 0x2, 0x2, 0x2, 0xed, 0xee, 
    0x7, 0x3d, 0x2, 0x2, 0xee, 0xef, 0x5, 0x7a, 0x3e, 0x2, 0xef, 0xf0, 0x7, 
    0x3e, 0x2, 0x2, 0xf0, 0xf1, 0x7, 0x41, 0x2, 0x2, 0xf1, 0xf3, 0x5, 0x84, 
    0x43, 0x2, 0xf2, 0xf4, 0x7, 0x5a, 0x2, 0x2, 0xf3, 0xf2, 0x3, 0x2, 0x2, 
    0x2, 0xf3, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf5, 0x3, 0x2, 0x2, 0x2, 
    0xf5, 0xf6, 0x7, 0x42, 0x2, 0x2, 0xf6, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xf7, 
    0xe9, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xeb, 0x3, 0x2, 0x2, 0x2, 0xf8, 0x107, 
    0x3, 0x2, 0x2, 0x2, 0xf9, 0xfa, 0x7, 0x3f, 0x2, 0x2, 0xfa, 0xfb, 0x5, 
    0x2e, 0x18, 0x2, 0xfb, 0xfc, 0x7, 0x40, 0x2, 0x2, 0xfc, 0x106, 0x3, 
    0x2, 0x2, 0x2, 0xfd, 0xff, 0x7, 0x3d, 0x2, 0x2, 0xfe, 0x100, 0x5, 0xc, 
    0x7, 0x2, 0xff, 0xfe, 0x3, 0x2, 0x2, 0x2, 0xff, 0x100, 0x3, 0x2, 0x2, 
    0x2, 0x100, 0x101, 0x3, 0x2, 0x2, 0x2, 0x101, 0x106, 0x7, 0x3e, 0x2, 
    0x2, 0x102, 0x103, 0x9, 0x2, 0x2, 0x2, 0x103, 0x106, 0x7, 0x6b, 0x2, 
    0x2, 0x104, 0x106, 0x9, 0x3, 0x2, 0x2, 0x105, 0xf9, 0x3, 0x2, 0x2, 0x2, 
    0x105, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x105, 0x102, 0x3, 0x2, 0x2, 0x2, 0x105, 
    0x104, 0x3, 0x2, 0x2, 0x2, 0x106, 0x109, 0x3, 0x2, 0x2, 0x2, 0x107, 
    0x105, 0x3, 0x2, 0x2, 0x2, 0x107, 0x108, 0x3, 0x2, 0x2, 0x2, 0x108, 
    0xb, 0x3, 0x2, 0x2, 0x2, 0x109, 0x107, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10f, 
    0x5, 0x2a, 0x16, 0x2, 0x10b, 0x10c, 0x7, 0x5a, 0x2, 0x2, 0x10c, 0x10e, 
    0x5, 0x2a, 0x16, 0x2, 0x10d, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x111, 
    0x3, 0x2, 0x2, 0x2, 0x10f, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x110, 
    0x3, 0x2, 0x2, 0x2, 0x110, 0xd, 0x3, 0x2, 0x2, 0x2, 0x111, 0x10f, 0x3, 
    0x2, 0x2, 0x2, 0x112, 0x114, 0x9, 0x4, 0x2, 0x2, 0x113, 0x112, 0x3, 
    0x2, 0x2, 0x2, 0x114, 0x117, 0x3, 0x2, 0x2, 0x2, 0x115, 0x113, 0x3, 
    0x2, 0x2, 0x2, 0x115, 0x116, 0x3, 0x2, 0x2, 0x2, 0x116, 0x123, 0x3, 
    0x2, 0x2, 0x2, 0x117, 0x115, 0x3, 0x2, 0x2, 0x2, 0x118, 0x124, 0x5, 
    0xa, 0x6, 0x2, 0x119, 0x11a, 0x5, 0x10, 0x9, 0x2, 0x11a, 0x11b, 0x5, 
    0x12, 0xa, 0x2, 0x11b, 0x124, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x11d, 0x9, 
    0x5, 0x2, 0x2, 0x11d, 0x11e, 0x7, 0x3d, 0x2, 0x2, 0x11e, 0x11f, 0x5, 
    0x7a, 0x3e, 0x2, 0x11f, 0x120, 0x7, 0x3e, 0x2, 0x2, 0x120, 0x124, 0x3, 
    0x2, 0x2, 0x2, 0x121, 0x122, 0x7, 0x52, 0x2, 0x2, 0x122, 0x124, 0x7, 
    0x6b, 0x2, 0x2, 0x123, 0x118, 0x3, 0x2, 0x2, 0x2, 0x123, 0x119, 0x3, 
    0x2, 0x2, 0x2, 0x123, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x123, 0x121, 0x3, 
    0x2, 0x2, 0x2, 0x124, 0xf, 0x3, 0x2, 0x2, 0x2, 0x125, 0x126, 0x9, 0x6, 
    0x2, 0x2, 0x126, 0x11, 0x3, 0x2, 0x2, 0x2, 0x127, 0x129, 0x7, 0x3, 0x2, 
    0x2, 0x128, 0x127, 0x3, 0x2, 0x2, 0x2, 0x128, 0x129, 0x3, 0x2, 0x2, 
    0x2, 0x129, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12b, 0x7, 0x3d, 0x2, 
    0x2, 0x12b, 0x12c, 0x5, 0x7a, 0x3e, 0x2, 0x12c, 0x12d, 0x7, 0x3e, 0x2, 
    0x2, 0x12d, 0x12e, 0x5, 0x12, 0xa, 0x2, 0x12e, 0x132, 0x3, 0x2, 0x2, 
    0x2, 0x12f, 0x132, 0x5, 0xe, 0x8, 0x2, 0x130, 0x132, 0x7, 0x6d, 0x2, 
    0x2, 0x131, 0x128, 0x3, 0x2, 0x2, 0x2, 0x131, 0x12f, 0x3, 0x2, 0x2, 
    0x2, 0x131, 0x130, 0x3, 0x2, 0x2, 0x2, 0x132, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0x133, 0x138, 0x5, 0x12, 0xa, 0x2, 0x134, 0x135, 0x9, 0x7, 0x2, 0x2, 
    0x135, 0x137, 0x5, 0x12, 0xa, 0x2, 0x136, 0x134, 0x3, 0x2, 0x2, 0x2, 
    0x137, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x138, 0x136, 0x3, 0x2, 0x2, 0x2, 
    0x138, 0x139, 0x3, 0x2, 0x2, 0x2, 0x139, 0x15, 0x3, 0x2, 0x2, 0x2, 0x13a, 
    0x138, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x140, 0x5, 0x14, 0xb, 0x2, 0x13c, 
    0x13d, 0x9, 0x8, 0x2, 0x2, 0x13d, 0x13f, 0x5, 0x14, 0xb, 0x2, 0x13e, 
    0x13c, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x142, 0x3, 0x2, 0x2, 0x2, 0x140, 
    0x13e, 0x3, 0x2, 0x2, 0x2, 0x140, 0x141, 0x3, 0x2, 0x2, 0x2, 0x141, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x142, 0x140, 0x3, 0x2, 0x2, 0x2, 0x143, 0x148, 
    0x5, 0x16, 0xc, 0x2, 0x144, 0x145, 0x9, 0x9, 0x2, 0x2, 0x145, 0x147, 
    0x5, 0x16, 0xc, 0x2, 0x146, 0x144, 0x3, 0x2, 0x2, 0x2, 0x147, 0x14a, 
    0x3, 0x2, 0x2, 0x2, 0x148, 0x146, 0x3, 0x2, 0x2, 0x2, 0x148, 0x149, 
    0x3, 0x2, 0x2, 0x2, 0x149, 0x19, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x148, 0x3, 
    0x2, 0x2, 0x2, 0x14b, 0x150, 0x5, 0x18, 0xd, 0x2, 0x14c, 0x14d, 0x9, 
    0xa, 0x2, 0x2, 0x14d, 0x14f, 0x5, 0x18, 0xd, 0x2, 0x14e, 0x14c, 0x3, 
    0x2, 0x2, 0x2, 0x14f, 0x152, 0x3, 0x2, 0x2, 0x2, 0x150, 0x14e, 0x3, 
    0x2, 0x2, 0x2, 0x150, 0x151, 0x3, 0x2, 0x2, 0x2, 0x151, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0x152, 0x150, 0x3, 0x2, 0x2, 0x2, 0x153, 0x158, 0x5, 0x1a, 
    0xe, 0x2, 0x154, 0x155, 0x9, 0xb, 0x2, 0x2, 0x155, 0x157, 0x5, 0x1a, 
    0xe, 0x2, 0x156, 0x154, 0x3, 0x2, 0x2, 0x2, 0x157, 0x15a, 0x3, 0x2, 
    0x2, 0x2, 0x158, 0x156, 0x3, 0x2, 0x2, 0x2, 0x158, 0x159, 0x3, 0x2, 
    0x2, 0x2, 0x159, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x158, 0x3, 0x2, 0x2, 
    0x2, 0x15b, 0x160, 0x5, 0x1c, 0xf, 0x2, 0x15c, 0x15d, 0x7, 0x50, 0x2, 
    0x2, 0x15d, 0x15f, 0x5, 0x1c, 0xf, 0x2, 0x15e, 0x15c, 0x3, 0x2, 0x2, 
    0x2, 0x15f, 0x162, 0x3, 0x2, 0x2, 0x2, 0x160, 0x15e, 0x3, 0x2, 0x2, 
    0x2, 0x160, 0x161, 0x3, 0x2, 0x2, 0x2, 0x161, 0x1f, 0x3, 0x2, 0x2, 0x2, 
    0x162, 0x160, 0x3, 0x2, 0x2, 0x2, 0x163, 0x168, 0x5, 0x1e, 0x10, 0x2, 
    0x164, 0x165, 0x7, 0x54, 0x2, 0x2, 0x165, 0x167, 0x5, 0x1e, 0x10, 0x2, 
    0x166, 0x164, 0x3, 0x2, 0x2, 0x2, 0x167, 0x16a, 0x3, 0x2, 0x2, 0x2, 
    0x168, 0x166, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x3, 0x2, 0x2, 0x2, 
    0x169, 0x21, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x168, 0x3, 0x2, 0x2, 0x2, 0x16b, 
    0x170, 0x5, 0x20, 0x11, 0x2, 0x16c, 0x16d, 0x7, 0x51, 0x2, 0x2, 0x16d, 
    0x16f, 0x5, 0x20, 0x11, 0x2, 0x16e, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x16f, 
    0x172, 0x3, 0x2, 0x2, 0x2, 0x170, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x170, 
    0x171, 0x3, 0x2, 0x2, 0x2, 0x171, 0x23, 0x3, 0x2, 0x2, 0x2, 0x172, 0x170, 
    0x3, 0x2, 0x2, 0x2, 0x173, 0x178, 0x5, 0x22, 0x12, 0x2, 0x174, 0x175, 
    0x7, 0x52, 0x2, 0x2, 0x175, 0x177, 0x5, 0x22, 0x12, 0x2, 0x176, 0x174, 
    0x3, 0x2, 0x2, 0x2, 0x177, 0x17a, 0x3, 0x2, 0x2, 0x2, 0x178, 0x176, 
    0x3, 0x2, 0x2, 0x2, 0x178, 0x179, 0x3, 0x2, 0x2, 0x2, 0x179, 0x25, 0x3, 
    0x2, 0x2, 0x2, 0x17a, 0x178, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x180, 0x5, 
    0x24, 0x13, 0x2, 0x17c, 0x17d, 0x7, 0x53, 0x2, 0x2, 0x17d, 0x17f, 0x5, 
    0x24, 0x13, 0x2, 0x17e, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x182, 0x3, 
    0x2, 0x2, 0x2, 0x180, 0x17e, 0x3, 0x2, 0x2, 0x2, 0x180, 0x181, 0x3, 
    0x2, 0x2, 0x2, 0x181, 0x27, 0x3, 0x2, 0x2, 0x2, 0x182, 0x180, 0x3, 0x2, 
    0x2, 0x2, 0x183, 0x189, 0x5, 0x26, 0x14, 0x2, 0x184, 0x185, 0x7, 0x57, 
    0x2, 0x2, 0x185, 0x186, 0x5, 0x2e, 0x18, 0x2, 0x186, 0x187, 0x7, 0x58, 
    0x2, 0x2, 0x187, 0x188, 0x5, 0x28, 0x15, 0x2, 0x188, 0x18a, 0x3, 0x2, 
    0x2, 0x2, 0x189, 0x184, 0x3, 0x2, 0x2, 0x2, 0x189, 0x18a, 0x3, 0x2, 
    0x2, 0x2, 0x18a, 0x29, 0x3, 0x2, 0x2, 0x2, 0x18b, 0x192, 0x5, 0x28, 
    0x15, 0x2, 0x18c, 0x18d, 0x5, 0xe, 0x8, 0x2, 0x18d, 0x18e, 0x5, 0x2c, 
    0x17, 0x2, 0x18e, 0x18f, 0x5, 0x2a, 0x16, 0x2, 0x18f, 0x192, 0x3, 0x2, 
    0x2, 0x2, 0x190, 0x192, 0x7, 0x6d, 0x2, 0x2, 0x191, 0x18b, 0x3, 0x2, 
    0x2, 0x2, 0x191, 0x18c, 0x3, 0x2, 0x2, 0x2, 0x191, 0x190, 0x3, 0x2, 
    0x2, 0x2, 0x192, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x193, 0x194, 0x9, 0xc, 0x2, 
    0x2, 0x194, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x195, 0x19a, 0x5, 0x2a, 0x16, 
    0x2, 0x196, 0x197, 0x7, 0x5a, 0x2, 0x2, 0x197, 0x199, 0x5, 0x2a, 0x16, 
    0x2, 0x198, 0x196, 0x3, 0x2, 0x2, 0x2, 0x199, 0x19c, 0x3, 0x2, 0x2, 
    0x2, 0x19a, 0x198, 0x3, 0x2, 0x2, 0x2, 0x19a, 0x19b, 0x3, 0x2, 0x2, 
    0x2, 0x19b, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19a, 0x3, 0x2, 0x2, 0x2, 
    0x19d, 0x19e, 0x5, 0x28, 0x15, 0x2, 0x19e, 0x31, 0x3, 0x2, 0x2, 0x2, 
    0x19f, 0x1a1, 0x5, 0x34, 0x1b, 0x2, 0x1a0, 0x1a2, 0x5, 0x3a, 0x1e, 0x2, 
    0x1a1, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x1a2, 0x3, 0x2, 0x2, 0x2, 
    0x1a2, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a4, 0x7, 0x59, 0x2, 0x2, 
    0x1a4, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1a5, 0x1a7, 0x5, 0x8c, 0x47, 0x2, 
    0x1a6, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1a5, 0x3, 0x2, 0x2, 0x2, 
    0x1a7, 0x33, 0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1aa, 0x5, 0x38, 0x1d, 0x2, 
    0x1a9, 0x1a8, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x1ab, 0x3, 0x2, 0x2, 0x2, 
    0x1ab, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1ac, 0x3, 0x2, 0x2, 0x2, 
    0x1ac, 0x35, 0x3, 0x2, 0x2, 0x2, 0x1ad, 0x1af, 0x5, 0x38, 0x1d, 0x2, 
    0x1ae, 0x1ad, 0x3, 0x2, 0x2, 0x2, 0x1af, 0x1b0, 0x3, 0x2, 0x2, 0x2, 
    0x1b0, 0x1ae, 0x3, 0x2, 0x2, 0x2, 0x1b0, 0x1b1, 0x3, 0x2, 0x2, 0x2, 
    0x1b1, 0x37, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1b8, 0x5, 0x3e, 0x20, 0x2, 
    0x1b3, 0x1b8, 0x5, 0x40, 0x21, 0x2, 0x1b4, 0x1b8, 0x5, 0x5a, 0x2e, 0x2, 
    0x1b5, 0x1b8, 0x5, 0x5c, 0x2f, 0x2, 0x1b6, 0x1b8, 0x5, 0x5e, 0x30, 0x2, 
    0x1b7, 0x1b2, 0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1b3, 0x3, 0x2, 0x2, 0x2, 
    0x1b7, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1b5, 0x3, 0x2, 0x2, 0x2, 
    0x1b7, 0x1b6, 0x3, 0x2, 0x2, 0x2, 0x1b8, 0x39, 0x3, 0x2, 0x2, 0x2, 0x1b9, 
    0x1be, 0x5, 0x3c, 0x1f, 0x2, 0x1ba, 0x1bb, 0x7, 0x5a, 0x2, 0x2, 0x1bb, 
    0x1bd, 0x5, 0x3c, 0x1f, 0x2, 0x1bc, 0x1ba, 0x3, 0x2, 0x2, 0x2, 0x1bd, 
    0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1be, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x1be, 
    0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1bf, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1be, 
    0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1c4, 0x5, 0x60, 0x31, 0x2, 0x1c2, 0x1c3, 
    0x7, 0x5b, 0x2, 0x2, 0x1c3, 0x1c5, 0x5, 0x82, 0x42, 0x2, 0x1c4, 0x1c2, 
    0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x3d, 0x3, 
    0x2, 0x2, 0x2, 0x1c6, 0x1c7, 0x9, 0xd, 0x2, 0x2, 0x1c7, 0x3f, 0x3, 0x2, 
    0x2, 0x2, 0x1c8, 0x1c9, 0x8, 0x21, 0x1, 0x2, 0x1c9, 0x1d8, 0x9, 0xe, 
    0x2, 0x2, 0x1ca, 0x1cb, 0x7, 0x3, 0x2, 0x2, 0x1cb, 0x1cc, 0x7, 0x3d, 
    0x2, 0x2, 0x1cc, 0x1cd, 0x9, 0xf, 0x2, 0x2, 0x1cd, 0x1d8, 0x7, 0x3e, 
    0x2, 0x2, 0x1ce, 0x1d8, 0x5, 0x58, 0x2d, 0x2, 0x1cf, 0x1d8, 0x5, 0x42, 
    0x22, 0x2, 0x1d0, 0x1d8, 0x5, 0x50, 0x29, 0x2, 0x1d1, 0x1d8, 0x5, 0x80, 
    0x41, 0x2, 0x1d2, 0x1d3, 0x7, 0x9, 0x2, 0x2, 0x1d3, 0x1d4, 0x7, 0x3d, 
    0x2, 0x2, 0x1d4, 0x1d5, 0x5, 0x30, 0x19, 0x2, 0x1d5, 0x1d6, 0x7, 0x3e, 
    0x2, 0x2, 0x1d6, 0x1d8, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x1c8, 0x3, 0x2, 
    0x2, 0x2, 0x1d7, 0x1ca, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x1ce, 0x3, 0x2, 
    0x2, 0x2, 0x1d7, 0x1cf, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x1d0, 0x3, 0x2, 
    0x2, 0x2, 0x1d7, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x1d2, 0x3, 0x2, 
    0x2, 0x2, 0x1d8, 0x1dd, 0x3, 0x2, 0x2, 0x2, 0x1d9, 0x1da, 0xc, 0x3, 
    0x2, 0x2, 0x1da, 0x1dc, 0x5, 0x6e, 0x38, 0x2, 0x1db, 0x1d9, 0x3, 0x2, 
    0x2, 0x2, 0x1dc, 0x1df, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1db, 0x3, 0x2, 
    0x2, 0x2, 0x1dd, 0x1de, 0x3, 0x2, 0x2, 0x2, 0x1de, 0x41, 0x3, 0x2, 0x2, 
    0x2, 0x1df, 0x1dd, 0x3, 0x2, 0x2, 0x2, 0x1e0, 0x1e2, 0x5, 0x44, 0x23, 
    0x2, 0x1e1, 0x1e3, 0x7, 0x6b, 0x2, 0x2, 0x1e2, 0x1e1, 0x3, 0x2, 0x2, 
    0x2, 0x1e2, 0x1e3, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e4, 0x3, 0x2, 0x2, 
    0x2, 0x1e4, 0x1e5, 0x7, 0x41, 0x2, 0x2, 0x1e5, 0x1e6, 0x5, 0x46, 0x24, 
    0x2, 0x1e6, 0x1e7, 0x7, 0x42, 0x2, 0x2, 0x1e7, 0x1ec, 0x3, 0x2, 0x2, 
    0x2, 0x1e8, 0x1e9, 0x5, 0x44, 0x23, 0x2, 0x1e9, 0x1ea, 0x7, 0x6b, 0x2, 
    0x2, 0x1ea, 0x1ec, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1e0, 0x3, 0x2, 0x2, 
    0x2, 0x1eb, 0x1e8, 0x3, 0x2, 0x2, 0x2, 0x1ec, 0x43, 0x3, 0x2, 0x2, 0x2, 
    0x1ed, 0x1ee, 0x9, 0x10, 0x2, 0x2, 0x1ee, 0x45, 0x3, 0x2, 0x2, 0x2, 
    0x1ef, 0x1f1, 0x5, 0x48, 0x25, 0x2, 0x1f0, 0x1ef, 0x3, 0x2, 0x2, 0x2, 
    0x1f1, 0x1f2, 0x3, 0x2, 0x2, 0x2, 0x1f2, 0x1f0, 0x3, 0x2, 0x2, 0x2, 
    0x1f2, 0x1f3, 0x3, 0x2, 0x2, 0x2, 0x1f3, 0x47, 0x3, 0x2, 0x2, 0x2, 0x1f4, 
    0x1f6, 0x5, 0x4a, 0x26, 0x2, 0x1f5, 0x1f7, 0x5, 0x4c, 0x27, 0x2, 0x1f6, 
    0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1f6, 0x1f7, 0x3, 0x2, 0x2, 0x2, 0x1f7, 
    0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1f8, 0x1f9, 0x7, 0x59, 0x2, 0x2, 0x1f9, 
    0x1fc, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fc, 0x5, 0x8c, 0x47, 0x2, 0x1fb, 
    0x1f4, 0x3, 0x2, 0x2, 0x2, 0x1fb, 0x1fa, 0x3, 0x2, 0x2, 0x2, 0x1fc, 
    0x49, 0x3, 0x2, 0x2, 0x2, 0x1fd, 0x200, 0x5, 0x40, 0x21, 0x2, 0x1fe, 
    0x200, 0x5, 0x5a, 0x2e, 0x2, 0x1ff, 0x1fd, 0x3, 0x2, 0x2, 0x2, 0x1ff, 
    0x1fe, 0x3, 0x2, 0x2, 0x2, 0x200, 0x202, 0x3, 0x2, 0x2, 0x2, 0x201, 
    0x203, 0x5, 0x4a, 0x26, 0x2, 0x202, 0x201, 0x3, 0x2, 0x2, 0x2, 0x202, 
    0x203, 0x3, 0x2, 0x2, 0x2, 0x203, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x204, 0x209, 
    0x5, 0x4e, 0x28, 0x2, 0x205, 0x206, 0x7, 0x5a, 0x2, 0x2, 0x206, 0x208, 
    0x5, 0x4e, 0x28, 0x2, 0x207, 0x205, 0x3, 0x2, 0x2, 0x2, 0x208, 0x20b, 
    0x3, 0x2, 0x2, 0x2, 0x209, 0x207, 0x3, 0x2, 0x2, 0x2, 0x209, 0x20a, 
    0x3, 0x2, 0x2, 0x2, 0x20a, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x209, 0x3, 
    0x2, 0x2, 0x2, 0x20c, 0x213, 0x5, 0x60, 0x31, 0x2, 0x20d, 0x20f, 0x5, 
    0x60, 0x31, 0x2, 0x20e, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x20e, 0x20f, 0x3, 
    0x2, 0x2, 0x2, 0x20f, 0x210, 0x3, 0x2, 0x2, 0x2, 0x210, 0x211, 0x7, 
    0x58, 0x2, 0x2, 0x211, 0x213, 0x5, 0x30, 0x19, 0x2, 0x212, 0x20c, 0x3, 
    0x2, 0x2, 0x2, 0x212, 0x20e, 0x3, 0x2, 0x2, 0x2, 0x213, 0x4f, 0x3, 0x2, 
    0x2, 0x2, 0x214, 0x216, 0x7, 0x1b, 0x2, 0x2, 0x215, 0x217, 0x7, 0x6b, 
    0x2, 0x2, 0x216, 0x215, 0x3, 0x2, 0x2, 0x2, 0x216, 0x217, 0x3, 0x2, 
    0x2, 0x2, 0x217, 0x218, 0x3, 0x2, 0x2, 0x2, 0x218, 0x219, 0x7, 0x41, 
    0x2, 0x2, 0x219, 0x21b, 0x5, 0x52, 0x2a, 0x2, 0x21a, 0x21c, 0x7, 0x5a, 
    0x2, 0x2, 0x21b, 0x21a, 0x3, 0x2, 0x2, 0x2, 0x21b, 0x21c, 0x3, 0x2, 
    0x2, 0x2, 0x21c, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x21d, 0x21e, 0x7, 0x42, 
    0x2, 0x2, 0x21e, 0x222, 0x3, 0x2, 0x2, 0x2, 0x21f, 0x220, 0x7, 0x1b, 
    0x2, 0x2, 0x220, 0x222, 0x7, 0x6b, 0x2, 0x2, 0x221, 0x214, 0x3, 0x2, 
    0x2, 0x2, 0x221, 0x21f, 0x3, 0x2, 0x2, 0x2, 0x222, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x223, 0x228, 0x5, 0x54, 0x2b, 0x2, 0x224, 0x225, 0x7, 0x5a, 0x2, 
    0x2, 0x225, 0x227, 0x5, 0x54, 0x2b, 0x2, 0x226, 0x224, 0x3, 0x2, 0x2, 
    0x2, 0x227, 0x22a, 0x3, 0x2, 0x2, 0x2, 0x228, 0x226, 0x3, 0x2, 0x2, 
    0x2, 0x228, 0x229, 0x3, 0x2, 0x2, 0x2, 0x229, 0x53, 0x3, 0x2, 0x2, 0x2, 
    0x22a, 0x228, 0x3, 0x2, 0x2, 0x2, 0x22b, 0x22e, 0x5, 0x56, 0x2c, 0x2, 
    0x22c, 0x22d, 0x7, 0x5b, 0x2, 0x2, 0x22d, 0x22f, 0x5, 0x30, 0x19, 0x2, 
    0x22e, 0x22c, 0x3, 0x2, 0x2, 0x2, 0x22e, 0x22f, 0x3, 0x2, 0x2, 0x2, 
    0x22f, 0x55, 0x3, 0x2, 0x2, 0x2, 0x230, 0x231, 0x7, 0x6b, 0x2, 0x2, 
    0x231, 0x57, 0x3, 0x2, 0x2, 0x2, 0x232, 0x233, 0x7, 0x35, 0x2, 0x2, 
    0x233, 0x234, 0x7, 0x3d, 0x2, 0x2, 0x234, 0x235, 0x5, 0x7a, 0x3e, 0x2, 
    0x235, 0x236, 0x7, 0x3e, 0x2, 0x2, 0x236, 0x59, 0x3, 0x2, 0x2, 0x2, 
    0x237, 0x238, 0x9, 0x11, 0x2, 0x2, 0x238, 0x5b, 0x3, 0x2, 0x2, 0x2, 
    0x239, 0x240, 0x9, 0x12, 0x2, 0x2, 0x23a, 0x240, 0x5, 0x66, 0x34, 0x2, 
    0x23b, 0x23c, 0x7, 0xc, 0x2, 0x2, 0x23c, 0x23d, 0x7, 0x3d, 0x2, 0x2, 
    0x23d, 0x23e, 0x7, 0x6b, 0x2, 0x2, 0x23e, 0x240, 0x7, 0x3e, 0x2, 0x2, 
    0x23f, 0x239, 0x3, 0x2, 0x2, 0x2, 0x23f, 0x23a, 0x3, 0x2, 0x2, 0x2, 
    0x23f, 0x23b, 0x3, 0x2, 0x2, 0x2, 0x240, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x241, 
    0x242, 0x7, 0x33, 0x2, 0x2, 0x242, 0x245, 0x7, 0x3d, 0x2, 0x2, 0x243, 
    0x246, 0x5, 0x7a, 0x3e, 0x2, 0x244, 0x246, 0x5, 0x30, 0x19, 0x2, 0x245, 
    0x243, 0x3, 0x2, 0x2, 0x2, 0x245, 0x244, 0x3, 0x2, 0x2, 0x2, 0x246, 
    0x247, 0x3, 0x2, 0x2, 0x2, 0x247, 0x248, 0x7, 0x3e, 0x2, 0x2, 0x248, 
    0x5f, 0x3, 0x2, 0x2, 0x2, 0x249, 0x24b, 0x5, 0x6e, 0x38, 0x2, 0x24a, 
    0x249, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x24b, 0x3, 0x2, 0x2, 0x2, 0x24b, 
    0x24c, 0x3, 0x2, 0x2, 0x2, 0x24c, 0x250, 0x5, 0x62, 0x32, 0x2, 0x24d, 
    0x24f, 0x5, 0x64, 0x33, 0x2, 0x24e, 0x24d, 0x3, 0x2, 0x2, 0x2, 0x24f, 
    0x252, 0x3, 0x2, 0x2, 0x2, 0x250, 0x24e, 0x3, 0x2, 0x2, 0x2, 0x250, 
    0x251, 0x3, 0x2, 0x2, 0x2, 0x251, 0x61, 0x3, 0x2, 0x2, 0x2, 0x252, 0x250, 
    0x3, 0x2, 0x2, 0x2, 0x253, 0x254, 0x8, 0x32, 0x1, 0x2, 0x254, 0x265, 
    0x7, 0x6b, 0x2, 0x2, 0x255, 0x256, 0x7, 0x3d, 0x2, 0x2, 0x256, 0x257, 
    0x5, 0x60, 0x31, 0x2, 0x257, 0x258, 0x7, 0x3e, 0x2, 0x2, 0x258, 0x265, 
    0x3, 0x2, 0x2, 0x2, 0x259, 0x25a, 0x7, 0x6b, 0x2, 0x2, 0x25a, 0x25b, 
    0x7, 0x58, 0x2, 0x2, 0x25b, 0x265, 0x7, 0x6d, 0x2, 0x2, 0x25c, 0x25e, 
    0x7, 0x3d, 0x2, 0x2, 0x25d, 0x25f, 0x5, 0x40, 0x21, 0x2, 0x25e, 0x25d, 
    0x3, 0x2, 0x2, 0x2, 0x25e, 0x25f, 0x3, 0x2, 0x2, 0x2, 0x25f, 0x260, 
    0x3, 0x2, 0x2, 0x2, 0x260, 0x261, 0x5, 0x6e, 0x38, 0x2, 0x261, 0x262, 
    0x5, 0x62, 0x32, 0x2, 0x262, 0x263, 0x7, 0x3e, 0x2, 0x2, 0x263, 0x265, 
    0x3, 0x2, 0x2, 0x2, 0x264, 0x253, 0x3, 0x2, 0x2, 0x2, 0x264, 0x255, 
    0x3, 0x2, 0x2, 0x2, 0x264, 0x259, 0x3, 0x2, 0x2, 0x2, 0x264, 0x25c, 
    0x3, 0x2, 0x2, 0x2, 0x265, 0x293, 0x3, 0x2, 0x2, 0x2, 0x266, 0x267, 
    0xc, 0xa, 0x2, 0x2, 0x267, 0x269, 0x7, 0x3f, 0x2, 0x2, 0x268, 0x26a, 
    0x5, 0x70, 0x39, 0x2, 0x269, 0x268, 0x3, 0x2, 0x2, 0x2, 0x269, 0x26a, 
    0x3, 0x2, 0x2, 0x2, 0x26a, 0x26c, 0x3, 0x2, 0x2, 0x2, 0x26b, 0x26d, 
    0x5, 0x2a, 0x16, 0x2, 0x26c, 0x26b, 0x3, 0x2, 0x2, 0x2, 0x26c, 0x26d, 
    0x3, 0x2, 0x2, 0x2, 0x26d, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x26e, 0x292, 
    0x7, 0x40, 0x2, 0x2, 0x26f, 0x270, 0xc, 0x9, 0x2, 0x2, 0x270, 0x271, 
    0x7, 0x3f, 0x2, 0x2, 0x271, 0x273, 0x7, 0x2a, 0x2, 0x2, 0x272, 0x274, 
    0x5, 0x70, 0x39, 0x2, 0x273, 0x272, 0x3, 0x2, 0x2, 0x2, 0x273, 0x274, 
    0x3, 0x2, 0x2, 0x2, 0x274, 0x275, 0x3, 0x2, 0x2, 0x2, 0x275, 0x276, 
    0x5, 0x2a, 0x16, 0x2, 0x276, 0x277, 0x7, 0x40, 0x2, 0x2, 0x277, 0x292, 
    0x3, 0x2, 0x2, 0x2, 0x278, 0x279, 0xc, 0x8, 0x2, 0x2, 0x279, 0x27a, 
    0x7, 0x3f, 0x2, 0x2, 0x27a, 0x27b, 0x5, 0x70, 0x39, 0x2, 0x27b, 0x27c, 
    0x7, 0x2a, 0x2, 0x2, 0x27c, 0x27d, 0x5, 0x2a, 0x16, 0x2, 0x27d, 0x27e, 
    0x7, 0x40, 0x2, 0x2, 0x27e, 0x292, 0x3, 0x2, 0x2, 0x2, 0x27f, 0x280, 
    0xc, 0x7, 0x2, 0x2, 0x280, 0x282, 0x7, 0x3f, 0x2, 0x2, 0x281, 0x283, 
    0x5, 0x70, 0x39, 0x2, 0x282, 0x281, 0x3, 0x2, 0x2, 0x2, 0x282, 0x283, 
    0x3, 0x2, 0x2, 0x2, 0x283, 0x284, 0x3, 0x2, 0x2, 0x2, 0x284, 0x285, 
    0x7, 0x4d, 0x2, 0x2, 0x285, 0x292, 0x7, 0x40, 0x2, 0x2, 0x286, 0x287, 
    0xc, 0x6, 0x2, 0x2, 0x287, 0x288, 0x7, 0x3d, 0x2, 0x2, 0x288, 0x289, 
    0x5, 0x72, 0x3a, 0x2, 0x289, 0x28a, 0x7, 0x3e, 0x2, 0x2, 0x28a, 0x292, 
    0x3, 0x2, 0x2, 0x2, 0x28b, 0x28c, 0xc, 0x5, 0x2, 0x2, 0x28c, 0x28e, 
    0x7, 0x3d, 0x2, 0x2, 0x28d, 0x28f, 0x5, 0x78, 0x3d, 0x2, 0x28e, 0x28d, 
    0x3, 0x2, 0x2, 0x2, 0x28e, 0x28f, 0x3, 0x2, 0x2, 0x2, 0x28f, 0x290, 
    0x3, 0x2, 0x2, 0x2, 0x290, 0x292, 0x7, 0x3e, 0x2, 0x2, 0x291, 0x266, 
    0x3, 0x2, 0x2, 0x2, 0x291, 0x26f, 0x3, 0x2, 0x2, 0x2, 0x291, 0x278, 
    0x3, 0x2, 0x2, 0x2, 0x291, 0x27f, 0x3, 0x2, 0x2, 0x2, 0x291, 0x286, 
    0x3, 0x2, 0x2, 0x2, 0x291, 0x28b, 0x3, 0x2, 0x2, 0x2, 0x292, 0x295, 
    0x3, 0x2, 0x2, 0x2, 0x293, 0x291, 0x3, 0x2, 0x2, 0x2, 0x293, 0x294, 
    0x3, 0x2, 0x2, 0x2, 0x294, 0x63, 0x3, 0x2, 0x2, 0x2, 0x295, 0x293, 0x3, 
    0x2, 0x2, 0x2, 0x296, 0x297, 0x7, 0xd, 0x2, 0x2, 0x297, 0x299, 0x7, 
    0x3d, 0x2, 0x2, 0x298, 0x29a, 0x7, 0x6e, 0x2, 0x2, 0x299, 0x298, 0x3, 
    0x2, 0x2, 0x2, 0x29a, 0x29b, 0x3, 0x2, 0x2, 0x2, 0x29b, 0x299, 0x3, 
    0x2, 0x2, 0x2, 0x29b, 0x29c, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x29d, 0x3, 
    0x2, 0x2, 0x2, 0x29d, 0x2a0, 0x7, 0x3e, 0x2, 0x2, 0x29e, 0x2a0, 0x5, 
    0x66, 0x34, 0x2, 0x29f, 0x296, 0x3, 0x2, 0x2, 0x2, 0x29f, 0x29e, 0x3, 
    0x2, 0x2, 0x2, 0x2a0, 0x65, 0x3, 0x2, 0x2, 0x2, 0x2a1, 0x2a2, 0x7, 0xe, 
    0x2, 0x2, 0x2a2, 0x2a3, 0x7, 0x3d, 0x2, 0x2, 0x2a3, 0x2a4, 0x7, 0x3d, 
    0x2, 0x2, 0x2a4, 0x2a5, 0x5, 0x68, 0x35, 0x2, 0x2a5, 0x2a6, 0x7, 0x3e, 
    0x2, 0x2, 0x2a6, 0x2a7, 0x7, 0x3e, 0x2, 0x2, 0x2a7, 0x67, 0x3, 0x2, 
    0x2, 0x2, 0x2a8, 0x2aa, 0x5, 0x6a, 0x36, 0x2, 0x2a9, 0x2a8, 0x3, 0x2, 
    0x2, 0x2, 0x2a9, 0x2aa, 0x3, 0x2, 0x2, 0x2, 0x2aa, 0x2b1, 0x3, 0x2, 
    0x2, 0x2, 0x2ab, 0x2ad, 0x7, 0x5a, 0x2, 0x2, 0x2ac, 0x2ae, 0x5, 0x6a, 
    0x36, 0x2, 0x2ad, 0x2ac, 0x3, 0x2, 0x2, 0x2, 0x2ad, 0x2ae, 0x3, 0x2, 
    0x2, 0x2, 0x2ae, 0x2b0, 0x3, 0x2, 0x2, 0x2, 0x2af, 0x2ab, 0x3, 0x2, 
    0x2, 0x2, 0x2b0, 0x2b3, 0x3, 0x2, 0x2, 0x2, 0x2b1, 0x2af, 0x3, 0x2, 
    0x2, 0x2, 0x2b1, 0x2b2, 0x3, 0x2, 0x2, 0x2, 0x2b2, 0x69, 0x3, 0x2, 0x2, 
    0x2, 0x2b3, 0x2b1, 0x3, 0x2, 0x2, 0x2, 0x2b4, 0x2ba, 0xa, 0x13, 0x2, 
    0x2, 0x2b5, 0x2b7, 0x7, 0x3d, 0x2, 0x2, 0x2b6, 0x2b8, 0x5, 0xc, 0x7, 
    0x2, 0x2b7, 0x2b6, 0x3, 0x2, 0x2, 0x2, 0x2b7, 0x2b8, 0x3, 0x2, 0x2, 
    0x2, 0x2b8, 0x2b9, 0x3, 0x2, 0x2, 0x2, 0x2b9, 0x2bb, 0x7, 0x3e, 0x2, 
    0x2, 0x2ba, 0x2b5, 0x3, 0x2, 0x2, 0x2, 0x2ba, 0x2bb, 0x3, 0x2, 0x2, 
    0x2, 0x2bb, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x2bc, 0x2c2, 0xa, 0x14, 0x2, 
    0x2, 0x2bd, 0x2be, 0x7, 0x3d, 0x2, 0x2, 0x2be, 0x2bf, 0x5, 0x6c, 0x37, 
    0x2, 0x2bf, 0x2c0, 0x7, 0x3e, 0x2, 0x2, 0x2c0, 0x2c2, 0x3, 0x2, 0x2, 
    0x2, 0x2c1, 0x2bc, 0x3, 0x2, 0x2, 0x2, 0x2c1, 0x2bd, 0x3, 0x2, 0x2, 
    0x2, 0x2c2, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2c3, 0x2c1, 0x3, 0x2, 0x2, 
    0x2, 0x2c3, 0x2c4, 0x3, 0x2, 0x2, 0x2, 0x2c4, 0x6d, 0x3, 0x2, 0x2, 0x2, 
    0x2c5, 0x2c3, 0x3, 0x2, 0x2, 0x2, 0x2c6, 0x2c8, 0x9, 0x15, 0x2, 0x2, 
    0x2c7, 0x2c9, 0x5, 0x70, 0x39, 0x2, 0x2c8, 0x2c7, 0x3, 0x2, 0x2, 0x2, 
    0x2c8, 0x2c9, 0x3, 0x2, 0x2, 0x2, 0x2c9, 0x2cb, 0x3, 0x2, 0x2, 0x2, 
    0x2ca, 0x2c6, 0x3, 0x2, 0x2, 0x2, 0x2cb, 0x2cc, 0x3, 0x2, 0x2, 0x2, 
    0x2cc, 0x2ca, 0x3, 0x2, 0x2, 0x2, 0x2cc, 0x2cd, 0x3, 0x2, 0x2, 0x2, 
    0x2cd, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x2ce, 0x2d0, 0x5, 0x5a, 0x2e, 0x2, 
    0x2cf, 0x2ce, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2d1, 0x3, 0x2, 0x2, 0x2, 
    0x2d1, 0x2cf, 0x3, 0x2, 0x2, 0x2, 0x2d1, 0x2d2, 0x3, 0x2, 0x2, 0x2, 
    0x2d2, 0x71, 0x3, 0x2, 0x2, 0x2, 0x2d3, 0x2d6, 0x5, 0x74, 0x3b, 0x2, 
    0x2d4, 0x2d5, 0x7, 0x5a, 0x2, 0x2, 0x2d5, 0x2d7, 0x7, 0x6a, 0x2, 0x2, 
    0x2d6, 0x2d4, 0x3, 0x2, 0x2, 0x2, 0x2d6, 0x2d7, 0x3, 0x2, 0x2, 0x2, 
    0x2d7, 0x73, 0x3, 0x2, 0x2, 0x2, 0x2d8, 0x2dd, 0x5, 0x76, 0x3c, 0x2, 
    0x2d9, 0x2da, 0x7, 0x5a, 0x2, 0x2, 0x2da, 0x2dc, 0x5, 0x76, 0x3c, 0x2, 
    0x2db, 0x2d9, 0x3, 0x2, 0x2, 0x2, 0x2dc, 0x2df, 0x3, 0x2, 0x2, 0x2, 
    0x2dd, 0x2db, 0x3, 0x2, 0x2, 0x2, 0x2dd, 0x2de, 0x3, 0x2, 0x2, 0x2, 
    0x2de, 0x75, 0x3, 0x2, 0x2, 0x2, 0x2df, 0x2dd, 0x3, 0x2, 0x2, 0x2, 0x2e0, 
    0x2e1, 0x5, 0x34, 0x1b, 0x2, 0x2e1, 0x2e2, 0x5, 0x60, 0x31, 0x2, 0x2e2, 
    0x2e8, 0x3, 0x2, 0x2, 0x2, 0x2e3, 0x2e5, 0x5, 0x36, 0x1c, 0x2, 0x2e4, 
    0x2e6, 0x5, 0x7c, 0x3f, 0x2, 0x2e5, 0x2e4, 0x3, 0x2, 0x2, 0x2, 0x2e5, 
    0x2e6, 0x3, 0x2, 0x2, 0x2, 0x2e6, 0x2e8, 0x3, 0x2, 0x2, 0x2, 0x2e7, 
    0x2e0, 0x3, 0x2, 0x2, 0x2, 0x2e7, 0x2e3, 0x3, 0x2, 0x2, 0x2, 0x2e8, 
    0x77, 0x3, 0x2, 0x2, 0x2, 0x2e9, 0x2ee, 0x7, 0x6b, 0x2, 0x2, 0x2ea, 
    0x2eb, 0x7, 0x5a, 0x2, 0x2, 0x2eb, 0x2ed, 0x7, 0x6b, 0x2, 0x2, 0x2ec, 
    0x2ea, 0x3, 0x2, 0x2, 0x2, 0x2ed, 0x2f0, 0x3, 0x2, 0x2, 0x2, 0x2ee, 
    0x2ec, 0x3, 0x2, 0x2, 0x2, 0x2ee, 0x2ef, 0x3, 0x2, 0x2, 0x2, 0x2ef, 
    0x79, 0x3, 0x2, 0x2, 0x2, 0x2f0, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x2f1, 0x2f3, 
    0x5, 0x4a, 0x26, 0x2, 0x2f2, 0x2f4, 0x5, 0x7c, 0x3f, 0x2, 0x2f3, 0x2f2, 
    0x3, 0x2, 0x2, 0x2, 0x2f3, 0x2f4, 0x3, 0x2, 0x2, 0x2, 0x2f4, 0x7b, 0x3, 
    0x2, 0x2, 0x2, 0x2f5, 0x301, 0x5, 0x6e, 0x38, 0x2, 0x2f6, 0x2f8, 0x5, 
    0x6e, 0x38, 0x2, 0x2f7, 0x2f6, 0x3, 0x2, 0x2, 0x2, 0x2f7, 0x2f8, 0x3, 
    0x2, 0x2, 0x2, 0x2f8, 0x2f9, 0x3, 0x2, 0x2, 0x2, 0x2f9, 0x2fd, 0x5, 
    0x7e, 0x40, 0x2, 0x2fa, 0x2fc, 0x5, 0x64, 0x33, 0x2, 0x2fb, 0x2fa, 0x3, 
    0x2, 0x2, 0x2, 0x2fc, 0x2ff, 0x3, 0x2, 0x2, 0x2, 0x2fd, 0x2fb, 0x3, 
    0x2, 0x2, 0x2, 0x2fd, 0x2fe, 0x3, 0x2, 0x2, 0x2, 0x2fe, 0x301, 0x3, 
    0x2, 0x2, 0x2, 0x2ff, 0x2fd, 0x3, 0x2, 0x2, 0x2, 0x300, 0x2f5, 0x3, 
    0x2, 0x2, 0x2, 0x300, 0x2f7, 0x3, 0x2, 0x2, 0x2, 0x301, 0x7d, 0x3, 0x2, 
    0x2, 0x2, 0x302, 0x303, 0x8, 0x40, 0x1, 0x2, 0x303, 0x304, 0x7, 0x3d, 
    0x2, 0x2, 0x304, 0x305, 0x5, 0x7c, 0x3f, 0x2, 0x305, 0x309, 0x7, 0x3e, 
    0x2, 0x2, 0x306, 0x308, 0x5, 0x64, 0x33, 0x2, 0x307, 0x306, 0x3, 0x2, 
    0x2, 0x2, 0x308, 0x30b, 0x3, 0x2, 0x2, 0x2, 0x309, 0x307, 0x3, 0x2, 
    0x2, 0x2, 0x309, 0x30a, 0x3, 0x2, 0x2, 0x2, 0x30a, 0x331, 0x3, 0x2, 
    0x2, 0x2, 0x30b, 0x309, 0x3, 0x2, 0x2, 0x2, 0x30c, 0x30e, 0x7, 0x3f, 
    0x2, 0x2, 0x30d, 0x30f, 0x5, 0x70, 0x39, 0x2, 0x30e, 0x30d, 0x3, 0x2, 
    0x2, 0x2, 0x30e, 0x30f, 0x3, 0x2, 0x2, 0x2, 0x30f, 0x311, 0x3, 0x2, 
    0x2, 0x2, 0x310, 0x312, 0x5, 0x2a, 0x16, 0x2, 0x311, 0x310, 0x3, 0x2, 
    0x2, 0x2, 0x311, 0x312, 0x3, 0x2, 0x2, 0x2, 0x312, 0x313, 0x3, 0x2, 
    0x2, 0x2, 0x313, 0x331, 0x7, 0x40, 0x2, 0x2, 0x314, 0x315, 0x7, 0x3f, 
    0x2, 0x2, 0x315, 0x317, 0x7, 0x2a, 0x2, 0x2, 0x316, 0x318, 0x5, 0x70, 
    0x39, 0x2, 0x317, 0x316, 0x3, 0x2, 0x2, 0x2, 0x317, 0x318, 0x3, 0x2, 
    0x2, 0x2, 0x318, 0x319, 0x3, 0x2, 0x2, 0x2, 0x319, 0x31a, 0x5, 0x2a, 
    0x16, 0x2, 0x31a, 0x31b, 0x7, 0x40, 0x2, 0x2, 0x31b, 0x331, 0x3, 0x2, 
    0x2, 0x2, 0x31c, 0x31d, 0x7, 0x3f, 0x2, 0x2, 0x31d, 0x31e, 0x5, 0x70, 
    0x39, 0x2, 0x31e, 0x31f, 0x7, 0x2a, 0x2, 0x2, 0x31f, 0x320, 0x5, 0x2a, 
    0x16, 0x2, 0x320, 0x321, 0x7, 0x40, 0x2, 0x2, 0x321, 0x331, 0x3, 0x2, 
    0x2, 0x2, 0x322, 0x323, 0x7, 0x3f, 0x2, 0x2, 0x323, 0x324, 0x7, 0x4d, 
    0x2, 0x2, 0x324, 0x331, 0x7, 0x40, 0x2, 0x2, 0x325, 0x327, 0x7, 0x3d, 
    0x2, 0x2, 0x326, 0x328, 0x5, 0x72, 0x3a, 0x2, 0x327, 0x326, 0x3, 0x2, 
    0x2, 0x2, 0x327, 0x328, 0x3, 0x2, 0x2, 0x2, 0x328, 0x329, 0x3, 0x2, 
    0x2, 0x2, 0x329, 0x32d, 0x7, 0x3e, 0x2, 0x2, 0x32a, 0x32c, 0x5, 0x64, 
    0x33, 0x2, 0x32b, 0x32a, 0x3, 0x2, 0x2, 0x2, 0x32c, 0x32f, 0x3, 0x2, 
    0x2, 0x2, 0x32d, 0x32b, 0x3, 0x2, 0x2, 0x2, 0x32d, 0x32e, 0x3, 0x2, 
    0x2, 0x2, 0x32e, 0x331, 0x3, 0x2, 0x2, 0x2, 0x32f, 0x32d, 0x3, 0x2, 
    0x2, 0x2, 0x330, 0x302, 0x3, 0x2, 0x2, 0x2, 0x330, 0x30c, 0x3, 0x2, 
    0x2, 0x2, 0x330, 0x314, 0x3, 0x2, 0x2, 0x2, 0x330, 0x31c, 0x3, 0x2, 
    0x2, 0x2, 0x330, 0x322, 0x3, 0x2, 0x2, 0x2, 0x330, 0x325, 0x3, 0x2, 
    0x2, 0x2, 0x331, 0x35d, 0x3, 0x2, 0x2, 0x2, 0x332, 0x333, 0xc, 0x7, 
    0x2, 0x2, 0x333, 0x335, 0x7, 0x3f, 0x2, 0x2, 0x334, 0x336, 0x5, 0x70, 
    0x39, 0x2, 0x335, 0x334, 0x3, 0x2, 0x2, 0x2, 0x335, 0x336, 0x3, 0x2, 
    0x2, 0x2, 0x336, 0x338, 0x3, 0x2, 0x2, 0x2, 0x337, 0x339, 0x5, 0x2a, 
    0x16, 0x2, 0x338, 0x337, 0x3, 0x2, 0x2, 0x2, 0x338, 0x339, 0x3, 0x2, 
    0x2, 0x2, 0x339, 0x33a, 0x3, 0x2, 0x2, 0x2, 0x33a, 0x35c, 0x7, 0x40, 
    0x2, 0x2, 0x33b, 0x33c, 0xc, 0x6, 0x2, 0x2, 0x33c, 0x33d, 0x7, 0x3f, 
    0x2, 0x2, 0x33d, 0x33f, 0x7, 0x2a, 0x2, 0x2, 0x33e, 0x340, 0x5, 0x70, 
    0x39, 0x2, 0x33f, 0x33e, 0x3, 0x2, 0x2, 0x2, 0x33f, 0x340, 0x3, 0x2, 
    0x2, 0x2, 0x340, 0x341, 0x3, 0x2, 0x2, 0x2, 0x341, 0x342, 0x5, 0x2a, 
    0x16, 0x2, 0x342, 0x343, 0x7, 0x40, 0x2, 0x2, 0x343, 0x35c, 0x3, 0x2, 
    0x2, 0x2, 0x344, 0x345, 0xc, 0x5, 0x2, 0x2, 0x345, 0x346, 0x7, 0x3f, 
    0x2, 0x2, 0x346, 0x347, 0x5, 0x70, 0x39, 0x2, 0x347, 0x348, 0x7, 0x2a, 
    0x2, 0x2, 0x348, 0x349, 0x5, 0x2a, 0x16, 0x2, 0x349, 0x34a, 0x7, 0x40, 
    0x2, 0x2, 0x34a, 0x35c, 0x3, 0x2, 0x2, 0x2, 0x34b, 0x34c, 0xc, 0x4, 
    0x2, 0x2, 0x34c, 0x34d, 0x7, 0x3f, 0x2, 0x2, 0x34d, 0x34e, 0x7, 0x4d, 
    0x2, 0x2, 0x34e, 0x35c, 0x7, 0x40, 0x2, 0x2, 0x34f, 0x350, 0xc, 0x3, 
    0x2, 0x2, 0x350, 0x352, 0x7, 0x3d, 0x2, 0x2, 0x351, 0x353, 0x5, 0x72, 
    0x3a, 0x2, 0x352, 0x351, 0x3, 0x2, 0x2, 0x2, 0x352, 0x353, 0x3, 0x2, 
    0x2, 0x2, 0x353, 0x354, 0x3, 0x2, 0x2, 0x2, 0x354, 0x358, 0x7, 0x3e, 
    0x2, 0x2, 0x355, 0x357, 0x5, 0x64, 0x33, 0x2, 0x356, 0x355, 0x3, 0x2, 
    0x2, 0x2, 0x357, 0x35a, 0x3, 0x2, 0x2, 0x2, 0x358, 0x356, 0x3, 0x2, 
    0x2, 0x2, 0x358, 0x359, 0x3, 0x2, 0x2, 0x2, 0x359, 0x35c, 0x3, 0x2, 
    0x2, 0x2, 0x35a, 0x358, 0x3, 0x2, 0x2, 0x2, 0x35b, 0x332, 0x3, 0x2, 
    0x2, 0x2, 0x35b, 0x33b, 0x3, 0x2, 0x2, 0x2, 0x35b, 0x344, 0x3, 0x2, 
    0x2, 0x2, 0x35b, 0x34b, 0x3, 0x2, 0x2, 0x2, 0x35b, 0x34f, 0x3, 0x2, 
    0x2, 0x2, 0x35c, 0x35f, 0x3, 0x2, 0x2, 0x2, 0x35d, 0x35b, 0x3, 0x2, 
    0x2, 0x2, 0x35d, 0x35e, 0x3, 0x2, 0x2, 0x2, 0x35e, 0x7f, 0x3, 0x2, 0x2, 
    0x2, 0x35f, 0x35d, 0x3, 0x2, 0x2, 0x2, 0x360, 0x361, 0x7, 0x6b, 0x2, 
    0x2, 0x361, 0x81, 0x3, 0x2, 0x2, 0x2, 0x362, 0x36b, 0x5, 0x2a, 0x16, 
    0x2, 0x363, 0x364, 0x7, 0x41, 0x2, 0x2, 0x364, 0x366, 0x5, 0x84, 0x43, 
    0x2, 0x365, 0x367, 0x7, 0x5a, 0x2, 0x2, 0x366, 0x365, 0x3, 0x2, 0x2, 
    0x2, 0x366, 0x367, 0x3, 0x2, 0x2, 0x2, 0x367, 0x368, 0x3, 0x2, 0x2, 
    0x2, 0x368, 0x369, 0x7, 0x42, 0x2, 0x2, 0x369, 0x36b, 0x3, 0x2, 0x2, 
    0x2, 0x36a, 0x362, 0x3, 0x2, 0x2, 0x2, 0x36a, 0x363, 0x3, 0x2, 0x2, 
    0x2, 0x36b, 0x83, 0x3, 0x2, 0x2, 0x2, 0x36c, 0x36e, 0x5, 0x86, 0x44, 
    0x2, 0x36d, 0x36c, 0x3, 0x2, 0x2, 0x2, 0x36d, 0x36e, 0x3, 0x2, 0x2, 
    0x2, 0x36e, 0x36f, 0x3, 0x2, 0x2, 0x2, 0x36f, 0x377, 0x5, 0x82, 0x42, 
    0x2, 0x370, 0x372, 0x7, 0x5a, 0x2, 0x2, 0x371, 0x373, 0x5, 0x86, 0x44, 
    0x2, 0x372, 0x371, 0x3, 0x2, 0x2, 0x2, 0x372, 0x373, 0x3, 0x2, 0x2, 
    0x2, 0x373, 0x374, 0x3, 0x2, 0x2, 0x2, 0x374, 0x376, 0x5, 0x82, 0x42, 
    0x2, 0x375, 0x370, 0x3, 0x2, 0x2, 0x2, 0x376, 0x379, 0x3, 0x2, 0x2, 
    0x2, 0x377, 0x375, 0x3, 0x2, 0x2, 0x2, 0x377, 0x378, 0x3, 0x2, 0x2, 
    0x2, 0x378, 0x85, 0x3, 0x2, 0x2, 0x2, 0x379, 0x377, 0x3, 0x2, 0x2, 0x2, 
    0x37a, 0x37b, 0x5, 0x88, 0x45, 0x2, 0x37b, 0x37c, 0x7, 0x5b, 0x2, 0x2, 
    0x37c, 0x87, 0x3, 0x2, 0x2, 0x2, 0x37d, 0x37f, 0x5, 0x8a, 0x46, 0x2, 
    0x37e, 0x37d, 0x3, 0x2, 0x2, 0x2, 0x37f, 0x380, 0x3, 0x2, 0x2, 0x2, 
    0x380, 0x37e, 0x3, 0x2, 0x2, 0x2, 0x380, 0x381, 0x3, 0x2, 0x2, 0x2, 
    0x381, 0x89, 0x3, 0x2, 0x2, 0x2, 0x382, 0x383, 0x7, 0x3f, 0x2, 0x2, 
    0x383, 0x384, 0x5, 0x30, 0x19, 0x2, 0x384, 0x385, 0x7, 0x40, 0x2, 0x2, 
    0x385, 0x389, 0x3, 0x2, 0x2, 0x2, 0x386, 0x387, 0x7, 0x69, 0x2, 0x2, 
    0x387, 0x389, 0x7, 0x6b, 0x2, 0x2, 0x388, 0x382, 0x3, 0x2, 0x2, 0x2, 
    0x388, 0x386, 0x3, 0x2, 0x2, 0x2, 0x389, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x38a, 
    0x38b, 0x7, 0x3b, 0x2, 0x2, 0x38b, 0x38c, 0x7, 0x3d, 0x2, 0x2, 0x38c, 
    0x38d, 0x5, 0x30, 0x19, 0x2, 0x38d, 0x38f, 0x7, 0x5a, 0x2, 0x2, 0x38e, 
    0x390, 0x7, 0x6e, 0x2, 0x2, 0x38f, 0x38e, 0x3, 0x2, 0x2, 0x2, 0x390, 
    0x391, 0x3, 0x2, 0x2, 0x2, 0x391, 0x38f, 0x3, 0x2, 0x2, 0x2, 0x391, 
    0x392, 0x3, 0x2, 0x2, 0x2, 0x392, 0x393, 0x3, 0x2, 0x2, 0x2, 0x393, 
    0x394, 0x7, 0x3e, 0x2, 0x2, 0x394, 0x395, 0x7, 0x59, 0x2, 0x2, 0x395, 
    0x8d, 0x3, 0x2, 0x2, 0x2, 0x396, 0x3bc, 0x5, 0x90, 0x49, 0x2, 0x397, 
    0x3bc, 0x5, 0x92, 0x4a, 0x2, 0x398, 0x3bc, 0x5, 0x98, 0x4d, 0x2, 0x399, 
    0x3bc, 0x5, 0x9a, 0x4e, 0x2, 0x39a, 0x3bc, 0x5, 0x9c, 0x4f, 0x2, 0x39b, 
    0x3bc, 0x5, 0xa4, 0x53, 0x2, 0x39c, 0x39d, 0x9, 0x16, 0x2, 0x2, 0x39d, 
    0x39e, 0x9, 0x17, 0x2, 0x2, 0x39e, 0x3a7, 0x7, 0x3d, 0x2, 0x2, 0x39f, 
    0x3a4, 0x5, 0x26, 0x14, 0x2, 0x3a0, 0x3a1, 0x7, 0x5a, 0x2, 0x2, 0x3a1, 
    0x3a3, 0x5, 0x26, 0x14, 0x2, 0x3a2, 0x3a0, 0x3, 0x2, 0x2, 0x2, 0x3a3, 
    0x3a6, 0x3, 0x2, 0x2, 0x2, 0x3a4, 0x3a2, 0x3, 0x2, 0x2, 0x2, 0x3a4, 
    0x3a5, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a8, 0x3, 0x2, 0x2, 0x2, 0x3a6, 
    0x3a4, 0x3, 0x2, 0x2, 0x2, 0x3a7, 0x39f, 0x3, 0x2, 0x2, 0x2, 0x3a7, 
    0x3a8, 0x3, 0x2, 0x2, 0x2, 0x3a8, 0x3b6, 0x3, 0x2, 0x2, 0x2, 0x3a9, 
    0x3b2, 0x7, 0x58, 0x2, 0x2, 0x3aa, 0x3af, 0x5, 0x26, 0x14, 0x2, 0x3ab, 
    0x3ac, 0x7, 0x5a, 0x2, 0x2, 0x3ac, 0x3ae, 0x5, 0x26, 0x14, 0x2, 0x3ad, 
    0x3ab, 0x3, 0x2, 0x2, 0x2, 0x3ae, 0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3af, 
    0x3ad, 0x3, 0x2, 0x2, 0x2, 0x3af, 0x3b0, 0x3, 0x2, 0x2, 0x2, 0x3b0, 
    0x3b3, 0x3, 0x2, 0x2, 0x2, 0x3b1, 0x3af, 0x3, 0x2, 0x2, 0x2, 0x3b2, 
    0x3aa, 0x3, 0x2, 0x2, 0x2, 0x3b2, 0x3b3, 0x3, 0x2, 0x2, 0x2, 0x3b3, 
    0x3b5, 0x3, 0x2, 0x2, 0x2, 0x3b4, 0x3a9, 0x3, 0x2, 0x2, 0x2, 0x3b5, 
    0x3b8, 0x3, 0x2, 0x2, 0x2, 0x3b6, 0x3b4, 0x3, 0x2, 0x2, 0x2, 0x3b6, 
    0x3b7, 0x3, 0x2, 0x2, 0x2, 0x3b7, 0x3b9, 0x3, 0x2, 0x2, 0x2, 0x3b8, 
    0x3b6, 0x3, 0x2, 0x2, 0x2, 0x3b9, 0x3ba, 0x7, 0x3e, 0x2, 0x2, 0x3ba, 
    0x3bc, 0x7, 0x59, 0x2, 0x2, 0x3bb, 0x396, 0x3, 0x2, 0x2, 0x2, 0x3bb, 
    0x397, 0x3, 0x2, 0x2, 0x2, 0x3bb, 0x398, 0x3, 0x2, 0x2, 0x2, 0x3bb, 
    0x399, 0x3, 0x2, 0x2, 0x2, 0x3bb, 0x39a, 0x3, 0x2, 0x2, 0x2, 0x3bb, 
    0x39b, 0x3, 0x2, 0x2, 0x2, 0x3bb, 0x39c, 0x3, 0x2, 0x2, 0x2, 0x3bc, 
    0x8f, 0x3, 0x2, 0x2, 0x2, 0x3bd, 0x3be, 0x7, 0x6b, 0x2, 0x2, 0x3be, 
    0x3bf, 0x7, 0x58, 0x2, 0x2, 0x3bf, 0x3c9, 0x5, 0x8e, 0x48, 0x2, 0x3c0, 
    0x3c1, 0x7, 0x13, 0x2, 0x2, 0x3c1, 0x3c2, 0x5, 0x30, 0x19, 0x2, 0x3c2, 
    0x3c3, 0x7, 0x58, 0x2, 0x2, 0x3c3, 0x3c4, 0x5, 0x8e, 0x48, 0x2, 0x3c4, 
    0x3c9, 0x3, 0x2, 0x2, 0x2, 0x3c5, 0x3c6, 0x7, 0x17, 0x2, 0x2, 0x3c6, 
    0x3c7, 0x7, 0x58, 0x2, 0x2, 0x3c7, 0x3c9, 0x5, 0x8e, 0x48, 0x2, 0x3c8, 
    0x3bd, 0x3, 0x2, 0x2, 0x2, 0x3c8, 0x3c0, 0x3, 0x2, 0x2, 0x2, 0x3c8, 
    0x3c5, 0x3, 0x2, 0x2, 0x2, 0x3c9, 0x91, 0x3, 0x2, 0x2, 0x2, 0x3ca, 0x3cc, 
    0x7, 0x41, 0x2, 0x2, 0x3cb, 0x3cd, 0x5, 0x94, 0x4b, 0x2, 0x3cc, 0x3cb, 
    0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3cd, 0x3, 0x2, 0x2, 0x2, 0x3cd, 0x3ce, 
    0x3, 0x2, 0x2, 0x2, 0x3ce, 0x3cf, 0x7, 0x42, 0x2, 0x2, 0x3cf, 0x93, 
    0x3, 0x2, 0x2, 0x2, 0x3d0, 0x3d2, 0x5, 0x96, 0x4c, 0x2, 0x3d1, 0x3d0, 
    0x3, 0x2, 0x2, 0x2, 0x3d2, 0x3d3, 0x3, 0x2, 0x2, 0x2, 0x3d3, 0x3d1, 
    0x3, 0x2, 0x2, 0x2, 0x3d3, 0x3d4, 0x3, 0x2, 0x2, 0x2, 0x3d4, 0x95, 0x3, 
    0x2, 0x2, 0x2, 0x3d5, 0x3d9, 0x5, 0x8e, 0x48, 0x2, 0x3d6, 0x3d9, 0x5, 
    0x32, 0x1a, 0x2, 0x3d7, 0x3d9, 0x7, 0x74, 0x2, 0x2, 0x3d8, 0x3d5, 0x3, 
    0x2, 0x2, 0x2, 0x3d8, 0x3d6, 0x3, 0x2, 0x2, 0x2, 0x3d8, 0x3d7, 0x3, 
    0x2, 0x2, 0x2, 0x3d9, 0x97, 0x3, 0x2, 0x2, 0x2, 0x3da, 0x3dc, 0x5, 0x2e, 
    0x18, 0x2, 0x3db, 0x3da, 0x3, 0x2, 0x2, 0x2, 0x3db, 0x3dc, 0x3, 0x2, 
    0x2, 0x2, 0x3dc, 0x3dd, 0x3, 0x2, 0x2, 0x2, 0x3dd, 0x3de, 0x7, 0x59, 
    0x2, 0x2, 0x3de, 0x99, 0x3, 0x2, 0x2, 0x2, 0x3df, 0x3e0, 0x7, 0x20, 
    0x2, 0x2, 0x3e0, 0x3e1, 0x7, 0x3d, 0x2, 0x2, 0x3e1, 0x3e2, 0x5, 0x2e, 
    0x18, 0x2, 0x3e2, 0x3e3, 0x7, 0x3e, 0x2, 0x2, 0x3e3, 0x3e6, 0x5, 0x8e, 
    0x48, 0x2, 0x3e4, 0x3e5, 0x7, 0x1a, 0x2, 0x2, 0x3e5, 0x3e7, 0x5, 0x8e, 
    0x48, 0x2, 0x3e6, 0x3e4, 0x3, 0x2, 0x2, 0x2, 0x3e6, 0x3e7, 0x3, 0x2, 
    0x2, 0x2, 0x3e7, 0x3ef, 0x3, 0x2, 0x2, 0x2, 0x3e8, 0x3e9, 0x7, 0x2c, 
    0x2, 0x2, 0x3e9, 0x3ea, 0x7, 0x3d, 0x2, 0x2, 0x3ea, 0x3eb, 0x5, 0x2e, 
    0x18, 0x2, 0x3eb, 0x3ec, 0x7, 0x3e, 0x2, 0x2, 0x3ec, 0x3ed, 0x5, 0x8e, 
    0x48, 0x2, 0x3ed, 0x3ef, 0x3, 0x2, 0x2, 0x2, 0x3ee, 0x3df, 0x3, 0x2, 
    0x2, 0x2, 0x3ee, 0x3e8, 0x3, 0x2, 0x2, 0x2, 0x3ef, 0x9b, 0x3, 0x2, 0x2, 
    0x2, 0x3f0, 0x3f1, 0x7, 0x32, 0x2, 0x2, 0x3f1, 0x3f2, 0x7, 0x3d, 0x2, 
    0x2, 0x3f2, 0x3f3, 0x5, 0x2e, 0x18, 0x2, 0x3f3, 0x3f4, 0x7, 0x3e, 0x2, 
    0x2, 0x3f4, 0x3f5, 0x5, 0x8e, 0x48, 0x2, 0x3f5, 0x405, 0x3, 0x2, 0x2, 
    0x2, 0x3f6, 0x3f7, 0x7, 0x18, 0x2, 0x2, 0x3f7, 0x3f8, 0x5, 0x8e, 0x48, 
    0x2, 0x3f8, 0x3f9, 0x7, 0x32, 0x2, 0x2, 0x3f9, 0x3fa, 0x7, 0x3d, 0x2, 
    0x2, 0x3fa, 0x3fb, 0x5, 0x2e, 0x18, 0x2, 0x3fb, 0x3fc, 0x7, 0x3e, 0x2, 
    0x2, 0x3fc, 0x3fd, 0x7, 0x59, 0x2, 0x2, 0x3fd, 0x405, 0x3, 0x2, 0x2, 
    0x2, 0x3fe, 0x3ff, 0x7, 0x1e, 0x2, 0x2, 0x3ff, 0x400, 0x7, 0x3d, 0x2, 
    0x2, 0x400, 0x401, 0x5, 0x9e, 0x50, 0x2, 0x401, 0x402, 0x7, 0x3e, 0x2, 
    0x2, 0x402, 0x403, 0x5, 0x8e, 0x48, 0x2, 0x403, 0x405, 0x3, 0x2, 0x2, 
    0x2, 0x404, 0x3f0, 0x3, 0x2, 0x2, 0x2, 0x404, 0x3f6, 0x3, 0x2, 0x2, 
    0x2, 0x404, 0x3fe, 0x3, 0x2, 0x2, 0x2, 0x405, 0x9d, 0x3, 0x2, 0x2, 0x2, 
    0x406, 0x40b, 0x5, 0xa0, 0x51, 0x2, 0x407, 0x409, 0x5, 0x2e, 0x18, 0x2, 
    0x408, 0x407, 0x3, 0x2, 0x2, 0x2, 0x408, 0x409, 0x3, 0x2, 0x2, 0x2, 
    0x409, 0x40b, 0x3, 0x2, 0x2, 0x2, 0x40a, 0x406, 0x3, 0x2, 0x2, 0x2, 
    0x40a, 0x408, 0x3, 0x2, 0x2, 0x2, 0x40b, 0x40c, 0x3, 0x2, 0x2, 0x2, 
    0x40c, 0x40e, 0x7, 0x59, 0x2, 0x2, 0x40d, 0x40f, 0x5, 0xa2, 0x52, 0x2, 
    0x40e, 0x40d, 0x3, 0x2, 0x2, 0x2, 0x40e, 0x40f, 0x3, 0x2, 0x2, 0x2, 
    0x40f, 0x410, 0x3, 0x2, 0x2, 0x2, 0x410, 0x412, 0x7, 0x59, 0x2, 0x2, 
    0x411, 0x413, 0x5, 0xa2, 0x52, 0x2, 0x412, 0x411, 0x3, 0x2, 0x2, 0x2, 
    0x412, 0x413, 0x3, 0x2, 0x2, 0x2, 0x413, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x414, 
    0x416, 0x5, 0x34, 0x1b, 0x2, 0x415, 0x417, 0x5, 0x3a, 0x1e, 0x2, 0x416, 
    0x415, 0x3, 0x2, 0x2, 0x2, 0x416, 0x417, 0x3, 0x2, 0x2, 0x2, 0x417, 
    0xa1, 0x3, 0x2, 0x2, 0x2, 0x418, 0x41d, 0x5, 0x2a, 0x16, 0x2, 0x419, 
    0x41a, 0x7, 0x5a, 0x2, 0x2, 0x41a, 0x41c, 0x5, 0x2a, 0x16, 0x2, 0x41b, 
    0x419, 0x3, 0x2, 0x2, 0x2, 0x41c, 0x41f, 0x3, 0x2, 0x2, 0x2, 0x41d, 
    0x41b, 0x3, 0x2, 0x2, 0x2, 0x41d, 0x41e, 0x3, 0x2, 0x2, 0x2, 0x41e, 
    0xa3, 0x3, 0x2, 0x2, 0x2, 0x41f, 0x41d, 0x3, 0x2, 0x2, 0x2, 0x420, 0x421, 
    0x7, 0x1f, 0x2, 0x2, 0x421, 0x42a, 0x7, 0x6b, 0x2, 0x2, 0x422, 0x42a, 
    0x9, 0x18, 0x2, 0x2, 0x423, 0x425, 0x7, 0x26, 0x2, 0x2, 0x424, 0x426, 
    0x5, 0x2e, 0x18, 0x2, 0x425, 0x424, 0x3, 0x2, 0x2, 0x2, 0x425, 0x426, 
    0x3, 0x2, 0x2, 0x2, 0x426, 0x42a, 0x3, 0x2, 0x2, 0x2, 0x427, 0x428, 
    0x7, 0x1f, 0x2, 0x2, 0x428, 0x42a, 0x5, 0xe, 0x8, 0x2, 0x429, 0x420, 
    0x3, 0x2, 0x2, 0x2, 0x429, 0x422, 0x3, 0x2, 0x2, 0x2, 0x429, 0x423, 
    0x3, 0x2, 0x2, 0x2, 0x429, 0x427, 0x3, 0x2, 0x2, 0x2, 0x42a, 0x42b, 
    0x3, 0x2, 0x2, 0x2, 0x42b, 0x42c, 0x7, 0x59, 0x2, 0x2, 0x42c, 0xa5, 
    0x3, 0x2, 0x2, 0x2, 0x42d, 0x42f, 0x5, 0xa8, 0x55, 0x2, 0x42e, 0x42d, 
    0x3, 0x2, 0x2, 0x2, 0x42e, 0x42f, 0x3, 0x2, 0x2, 0x2, 0x42f, 0x430, 
    0x3, 0x2, 0x2, 0x2, 0x430, 0x431, 0x7, 0x2, 0x2, 0x3, 0x431, 0xa7, 0x3, 
    0x2, 0x2, 0x2, 0x432, 0x434, 0x5, 0xaa, 0x56, 0x2, 0x433, 0x432, 0x3, 
    0x2, 0x2, 0x2, 0x434, 0x435, 0x3, 0x2, 0x2, 0x2, 0x435, 0x433, 0x3, 
    0x2, 0x2, 0x2, 0x435, 0x436, 0x3, 0x2, 0x2, 0x2, 0x436, 0xa9, 0x3, 0x2, 
    0x2, 0x2, 0x437, 0x43b, 0x5, 0xac, 0x57, 0x2, 0x438, 0x43b, 0x5, 0x32, 
    0x1a, 0x2, 0x439, 0x43b, 0x7, 0x59, 0x2, 0x2, 0x43a, 0x437, 0x3, 0x2, 
    0x2, 0x2, 0x43a, 0x438, 0x3, 0x2, 0x2, 0x2, 0x43a, 0x439, 0x3, 0x2, 
    0x2, 0x2, 0x43b, 0xab, 0x3, 0x2, 0x2, 0x2, 0x43c, 0x43e, 0x5, 0x34, 
    0x1b, 0x2, 0x43d, 0x43c, 0x3, 0x2, 0x2, 0x2, 0x43d, 0x43e, 0x3, 0x2, 
    0x2, 0x2, 0x43e, 0x43f, 0x3, 0x2, 0x2, 0x2, 0x43f, 0x441, 0x5, 0x60, 
    0x31, 0x2, 0x440, 0x442, 0x5, 0xae, 0x58, 0x2, 0x441, 0x440, 0x3, 0x2, 
    0x2, 0x2, 0x441, 0x442, 0x3, 0x2, 0x2, 0x2, 0x442, 0x443, 0x3, 0x2, 
    0x2, 0x2, 0x443, 0x444, 0x5, 0x92, 0x4a, 0x2, 0x444, 0xad, 0x3, 0x2, 
    0x2, 0x2, 0x445, 0x447, 0x5, 0x32, 0x1a, 0x2, 0x446, 0x445, 0x3, 0x2, 
    0x2, 0x2, 0x447, 0x448, 0x3, 0x2, 0x2, 0x2, 0x448, 0x446, 0x3, 0x2, 
    0x2, 0x2, 0x448, 0x449, 0x3, 0x2, 0x2, 0x2, 0x449, 0xaf, 0x3, 0x2, 0x2, 
    0x2, 0x8b, 0xb5, 0xbd, 0xd1, 0xdf, 0xe4, 0xeb, 0xf3, 0xf7, 0xff, 0x105, 
    0x107, 0x10f, 0x115, 0x123, 0x128, 0x131, 0x138, 0x140, 0x148, 0x150, 
    0x158, 0x160, 0x168, 0x170, 0x178, 0x180, 0x189, 0x191, 0x19a, 0x1a1, 
    0x1a6, 0x1ab, 0x1b0, 0x1b7, 0x1be, 0x1c4, 0x1d7, 0x1dd, 0x1e2, 0x1eb, 
    0x1f2, 0x1f6, 0x1fb, 0x1ff, 0x202, 0x209, 0x20e, 0x212, 0x216, 0x21b, 
    0x221, 0x228, 0x22e, 0x23f, 0x245, 0x24a, 0x250, 0x25e, 0x264, 0x269, 
    0x26c, 0x273, 0x282, 0x28e, 0x291, 0x293, 0x29b, 0x29f, 0x2a9, 0x2ad, 
    0x2b1, 0x2b7, 0x2ba, 0x2c1, 0x2c3, 0x2c8, 0x2cc, 0x2d1, 0x2d6, 0x2dd, 
    0x2e5, 0x2e7, 0x2ee, 0x2f3, 0x2f7, 0x2fd, 0x300, 0x309, 0x30e, 0x311, 
    0x317, 0x327, 0x32d, 0x330, 0x335, 0x338, 0x33f, 0x352, 0x358, 0x35b, 
    0x35d, 0x366, 0x36a, 0x36d, 0x372, 0x377, 0x380, 0x388, 0x391, 0x3a4, 
    0x3a7, 0x3af, 0x3b2, 0x3b6, 0x3bb, 0x3c8, 0x3cc, 0x3d3, 0x3d8, 0x3db, 
    0x3e6, 0x3ee, 0x404, 0x408, 0x40a, 0x40e, 0x412, 0x416, 0x41d, 0x425, 
    0x429, 0x42e, 0x435, 0x43a, 0x43d, 0x441, 0x448, 
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
