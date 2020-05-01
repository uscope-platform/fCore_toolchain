
// Generated from /home/fils/git/fCore_has/src/frontend/fs_grammar.g4 by ANTLR 4.8


#include "fs_grammarListener.h"
#include "fs_grammarVisitor.h"

#include "fs_grammarParser.h"


using namespace antlrcpp;
using namespace fs_parser;
using namespace antlr4;

fs_grammarParser::fs_grammarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

fs_grammarParser::~fs_grammarParser() {
  delete _interpreter;
}

std::string fs_grammarParser::getGrammarFileName() const {
  return "fs_grammar.g4";
}

const std::vector<std::string>& fs_grammarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& fs_grammarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

fs_grammarParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::CodeContext* fs_grammarParser::ProgramContext::code() {
  return getRuleContext<fs_grammarParser::CodeContext>(0);
}


size_t fs_grammarParser::ProgramContext::getRuleIndex() const {
  return fs_grammarParser::RuleProgram;
}

void fs_grammarParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void fs_grammarParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any fs_grammarParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::ProgramContext* fs_grammarParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, fs_grammarParser::RuleProgram);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
    code();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CodeContext ------------------------------------------------------------------

fs_grammarParser::CodeContext::CodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<fs_grammarParser::Reg_instrContext *> fs_grammarParser::CodeContext::reg_instr() {
  return getRuleContexts<fs_grammarParser::Reg_instrContext>();
}

fs_grammarParser::Reg_instrContext* fs_grammarParser::CodeContext::reg_instr(size_t i) {
  return getRuleContext<fs_grammarParser::Reg_instrContext>(i);
}

std::vector<fs_grammarParser::Imm_instrContext *> fs_grammarParser::CodeContext::imm_instr() {
  return getRuleContexts<fs_grammarParser::Imm_instrContext>();
}

fs_grammarParser::Imm_instrContext* fs_grammarParser::CodeContext::imm_instr(size_t i) {
  return getRuleContext<fs_grammarParser::Imm_instrContext>(i);
}

std::vector<fs_grammarParser::Indep_instrContext *> fs_grammarParser::CodeContext::indep_instr() {
  return getRuleContexts<fs_grammarParser::Indep_instrContext>();
}

fs_grammarParser::Indep_instrContext* fs_grammarParser::CodeContext::indep_instr(size_t i) {
  return getRuleContext<fs_grammarParser::Indep_instrContext>(i);
}

std::vector<fs_grammarParser::For_blockContext *> fs_grammarParser::CodeContext::for_block() {
  return getRuleContexts<fs_grammarParser::For_blockContext>();
}

fs_grammarParser::For_blockContext* fs_grammarParser::CodeContext::for_block(size_t i) {
  return getRuleContext<fs_grammarParser::For_blockContext>(i);
}

std::vector<fs_grammarParser::PragmaContext *> fs_grammarParser::CodeContext::pragma() {
  return getRuleContexts<fs_grammarParser::PragmaContext>();
}

fs_grammarParser::PragmaContext* fs_grammarParser::CodeContext::pragma(size_t i) {
  return getRuleContext<fs_grammarParser::PragmaContext>(i);
}


size_t fs_grammarParser::CodeContext::getRuleIndex() const {
  return fs_grammarParser::RuleCode;
}

void fs_grammarParser::CodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCode(this);
}

void fs_grammarParser::CodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCode(this);
}


antlrcpp::Any fs_grammarParser::CodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitCode(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::CodeContext* fs_grammarParser::code() {
  CodeContext *_localctx = _tracker.createInstance<CodeContext>(_ctx, getState());
  enterRule(_localctx, 2, fs_grammarParser::RuleCode);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(37);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case fs_grammarParser::T__3:
        case fs_grammarParser::T__4:
        case fs_grammarParser::T__5:
        case fs_grammarParser::T__6:
        case fs_grammarParser::T__7:
        case fs_grammarParser::T__8:
        case fs_grammarParser::T__9:
        case fs_grammarParser::T__10:
        case fs_grammarParser::T__11: {
          setState(32);
          reg_instr();
          break;
        }

        case fs_grammarParser::T__12:
        case fs_grammarParser::Hexnum:
        case fs_grammarParser::Octalnum: {
          setState(33);
          imm_instr();
          break;
        }

        case fs_grammarParser::T__1:
        case fs_grammarParser::T__2: {
          setState(34);
          indep_instr();
          break;
        }

        case fs_grammarParser::T__29: {
          setState(35);
          for_block();
          break;
        }

        case fs_grammarParser::T__41: {
          setState(36);
          pragma();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(39); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__1)
      | (1ULL << fs_grammarParser::T__2)
      | (1ULL << fs_grammarParser::T__3)
      | (1ULL << fs_grammarParser::T__4)
      | (1ULL << fs_grammarParser::T__5)
      | (1ULL << fs_grammarParser::T__6)
      | (1ULL << fs_grammarParser::T__7)
      | (1ULL << fs_grammarParser::T__8)
      | (1ULL << fs_grammarParser::T__9)
      | (1ULL << fs_grammarParser::T__10)
      | (1ULL << fs_grammarParser::T__11)
      | (1ULL << fs_grammarParser::T__12)
      | (1ULL << fs_grammarParser::T__29)
      | (1ULL << fs_grammarParser::T__41)
      | (1ULL << fs_grammarParser::Hexnum)
      | (1ULL << fs_grammarParser::Octalnum))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Reg_instrContext ------------------------------------------------------------------

fs_grammarParser::Reg_instrContext::Reg_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Reg_opcodeContext* fs_grammarParser::Reg_instrContext::reg_opcode() {
  return getRuleContext<fs_grammarParser::Reg_opcodeContext>(0);
}

std::vector<fs_grammarParser::Fcore_regContext *> fs_grammarParser::Reg_instrContext::fcore_reg() {
  return getRuleContexts<fs_grammarParser::Fcore_regContext>();
}

fs_grammarParser::Fcore_regContext* fs_grammarParser::Reg_instrContext::fcore_reg(size_t i) {
  return getRuleContext<fs_grammarParser::Fcore_regContext>(i);
}


size_t fs_grammarParser::Reg_instrContext::getRuleIndex() const {
  return fs_grammarParser::RuleReg_instr;
}

void fs_grammarParser::Reg_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReg_instr(this);
}

void fs_grammarParser::Reg_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReg_instr(this);
}


antlrcpp::Any fs_grammarParser::Reg_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitReg_instr(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Reg_instrContext* fs_grammarParser::reg_instr() {
  Reg_instrContext *_localctx = _tracker.createInstance<Reg_instrContext>(_ctx, getState());
  enterRule(_localctx, 4, fs_grammarParser::RuleReg_instr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(41);
    reg_opcode();
    setState(42);
    fcore_reg();
    setState(43);
    match(fs_grammarParser::T__0);
    setState(44);
    fcore_reg();
    setState(45);
    match(fs_grammarParser::T__0);
    setState(46);
    fcore_reg();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Imm_instrContext ------------------------------------------------------------------

fs_grammarParser::Imm_instrContext::Imm_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Imm_opcodeContext* fs_grammarParser::Imm_instrContext::imm_opcode() {
  return getRuleContext<fs_grammarParser::Imm_opcodeContext>(0);
}

fs_grammarParser::Fcore_regContext* fs_grammarParser::Imm_instrContext::fcore_reg() {
  return getRuleContext<fs_grammarParser::Fcore_regContext>(0);
}

tree::TerminalNode* fs_grammarParser::Imm_instrContext::Integer() {
  return getToken(fs_grammarParser::Integer, 0);
}

tree::TerminalNode* fs_grammarParser::Imm_instrContext::Hexnum() {
  return getToken(fs_grammarParser::Hexnum, 0);
}

tree::TerminalNode* fs_grammarParser::Imm_instrContext::Octalnum() {
  return getToken(fs_grammarParser::Octalnum, 0);
}


size_t fs_grammarParser::Imm_instrContext::getRuleIndex() const {
  return fs_grammarParser::RuleImm_instr;
}

void fs_grammarParser::Imm_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImm_instr(this);
}

void fs_grammarParser::Imm_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImm_instr(this);
}


antlrcpp::Any fs_grammarParser::Imm_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitImm_instr(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Imm_instrContext* fs_grammarParser::imm_instr() {
  Imm_instrContext *_localctx = _tracker.createInstance<Imm_instrContext>(_ctx, getState());
  enterRule(_localctx, 6, fs_grammarParser::RuleImm_instr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(55);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case fs_grammarParser::T__12: {
        enterOuterAlt(_localctx, 1);
        setState(48);
        imm_opcode();
        setState(49);
        fcore_reg();
        setState(50);
        match(fs_grammarParser::T__0);
        setState(51);
        match(fs_grammarParser::Integer);
        break;
      }

      case fs_grammarParser::Hexnum: {
        enterOuterAlt(_localctx, 2);
        setState(53);
        match(fs_grammarParser::Hexnum);
        break;
      }

      case fs_grammarParser::Octalnum: {
        enterOuterAlt(_localctx, 3);
        setState(54);
        match(fs_grammarParser::Octalnum);
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

//----------------- Indep_instrContext ------------------------------------------------------------------

fs_grammarParser::Indep_instrContext::Indep_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fs_grammarParser::Indep_instrContext::getRuleIndex() const {
  return fs_grammarParser::RuleIndep_instr;
}

void fs_grammarParser::Indep_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndep_instr(this);
}

void fs_grammarParser::Indep_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndep_instr(this);
}


antlrcpp::Any fs_grammarParser::Indep_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitIndep_instr(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Indep_instrContext* fs_grammarParser::indep_instr() {
  Indep_instrContext *_localctx = _tracker.createInstance<Indep_instrContext>(_ctx, getState());
  enterRule(_localctx, 8, fs_grammarParser::RuleIndep_instr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    _la = _input->LA(1);
    if (!(_la == fs_grammarParser::T__1

    || _la == fs_grammarParser::T__2)) {
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

//----------------- Reg_opcodeContext ------------------------------------------------------------------

fs_grammarParser::Reg_opcodeContext::Reg_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fs_grammarParser::Reg_opcodeContext::getRuleIndex() const {
  return fs_grammarParser::RuleReg_opcode;
}

void fs_grammarParser::Reg_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReg_opcode(this);
}

void fs_grammarParser::Reg_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReg_opcode(this);
}


antlrcpp::Any fs_grammarParser::Reg_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitReg_opcode(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Reg_opcodeContext* fs_grammarParser::reg_opcode() {
  Reg_opcodeContext *_localctx = _tracker.createInstance<Reg_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 10, fs_grammarParser::RuleReg_opcode);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__3)
      | (1ULL << fs_grammarParser::T__4)
      | (1ULL << fs_grammarParser::T__5)
      | (1ULL << fs_grammarParser::T__6)
      | (1ULL << fs_grammarParser::T__7)
      | (1ULL << fs_grammarParser::T__8)
      | (1ULL << fs_grammarParser::T__9)
      | (1ULL << fs_grammarParser::T__10)
      | (1ULL << fs_grammarParser::T__11))) != 0))) {
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

//----------------- Imm_opcodeContext ------------------------------------------------------------------

fs_grammarParser::Imm_opcodeContext::Imm_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fs_grammarParser::Imm_opcodeContext::getRuleIndex() const {
  return fs_grammarParser::RuleImm_opcode;
}

void fs_grammarParser::Imm_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImm_opcode(this);
}

void fs_grammarParser::Imm_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImm_opcode(this);
}


antlrcpp::Any fs_grammarParser::Imm_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitImm_opcode(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Imm_opcodeContext* fs_grammarParser::imm_opcode() {
  Imm_opcodeContext *_localctx = _tracker.createInstance<Imm_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 12, fs_grammarParser::RuleImm_opcode);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    match(fs_grammarParser::T__12);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fcore_regContext ------------------------------------------------------------------

fs_grammarParser::Fcore_regContext::Fcore_regContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fs_grammarParser::Fcore_regContext::getRuleIndex() const {
  return fs_grammarParser::RuleFcore_reg;
}

void fs_grammarParser::Fcore_regContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFcore_reg(this);
}

void fs_grammarParser::Fcore_regContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFcore_reg(this);
}


antlrcpp::Any fs_grammarParser::Fcore_regContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitFcore_reg(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Fcore_regContext* fs_grammarParser::fcore_reg() {
  Fcore_regContext *_localctx = _tracker.createInstance<Fcore_regContext>(_ctx, getState());
  enterRule(_localctx, 14, fs_grammarParser::RuleFcore_reg);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__13)
      | (1ULL << fs_grammarParser::T__14)
      | (1ULL << fs_grammarParser::T__15)
      | (1ULL << fs_grammarParser::T__16)
      | (1ULL << fs_grammarParser::T__17)
      | (1ULL << fs_grammarParser::T__18)
      | (1ULL << fs_grammarParser::T__19)
      | (1ULL << fs_grammarParser::T__20)
      | (1ULL << fs_grammarParser::T__21)
      | (1ULL << fs_grammarParser::T__22)
      | (1ULL << fs_grammarParser::T__23)
      | (1ULL << fs_grammarParser::T__24)
      | (1ULL << fs_grammarParser::T__25)
      | (1ULL << fs_grammarParser::T__26)
      | (1ULL << fs_grammarParser::T__27)
      | (1ULL << fs_grammarParser::T__28))) != 0))) {
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

//----------------- For_blockContext ------------------------------------------------------------------

fs_grammarParser::For_blockContext::For_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::For_declContext* fs_grammarParser::For_blockContext::for_decl() {
  return getRuleContext<fs_grammarParser::For_declContext>(0);
}

fs_grammarParser::For_endContext* fs_grammarParser::For_blockContext::for_end() {
  return getRuleContext<fs_grammarParser::For_endContext>(0);
}

fs_grammarParser::CodeContext* fs_grammarParser::For_blockContext::code() {
  return getRuleContext<fs_grammarParser::CodeContext>(0);
}

fs_grammarParser::For_incrContext* fs_grammarParser::For_blockContext::for_incr() {
  return getRuleContext<fs_grammarParser::For_incrContext>(0);
}

fs_grammarParser::For_decContext* fs_grammarParser::For_blockContext::for_dec() {
  return getRuleContext<fs_grammarParser::For_decContext>(0);
}


size_t fs_grammarParser::For_blockContext::getRuleIndex() const {
  return fs_grammarParser::RuleFor_block;
}

void fs_grammarParser::For_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_block(this);
}

void fs_grammarParser::For_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_block(this);
}


antlrcpp::Any fs_grammarParser::For_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_block(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::For_blockContext* fs_grammarParser::for_block() {
  For_blockContext *_localctx = _tracker.createInstance<For_blockContext>(_ctx, getState());
  enterRule(_localctx, 16, fs_grammarParser::RuleFor_block);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    match(fs_grammarParser::T__29);
    setState(66);
    for_decl();
    setState(67);
    match(fs_grammarParser::T__30);
    setState(68);
    for_end();
    setState(69);
    match(fs_grammarParser::T__30);
    setState(72);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(70);
      for_incr();
      break;
    }

    case 2: {
      setState(71);
      for_dec();
      break;
    }

    }
    setState(74);
    match(fs_grammarParser::T__31);
    setState(75);
    match(fs_grammarParser::T__32);
    setState(76);
    code();
    setState(77);
    match(fs_grammarParser::T__33);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_incrContext ------------------------------------------------------------------

fs_grammarParser::For_incrContext::For_incrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::For_incrContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::For_incrContext::getRuleIndex() const {
  return fs_grammarParser::RuleFor_incr;
}

void fs_grammarParser::For_incrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_incr(this);
}

void fs_grammarParser::For_incrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_incr(this);
}


antlrcpp::Any fs_grammarParser::For_incrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_incr(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::For_incrContext* fs_grammarParser::for_incr() {
  For_incrContext *_localctx = _tracker.createInstance<For_incrContext>(_ctx, getState());
  enterRule(_localctx, 18, fs_grammarParser::RuleFor_incr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(79);
    match(fs_grammarParser::Identifier);

    setState(80);
    match(fs_grammarParser::T__34);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_decContext ------------------------------------------------------------------

fs_grammarParser::For_decContext::For_decContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::For_decContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::For_decContext::getRuleIndex() const {
  return fs_grammarParser::RuleFor_dec;
}

void fs_grammarParser::For_decContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_dec(this);
}

void fs_grammarParser::For_decContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_dec(this);
}


antlrcpp::Any fs_grammarParser::For_decContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_dec(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::For_decContext* fs_grammarParser::for_dec() {
  For_decContext *_localctx = _tracker.createInstance<For_decContext>(_ctx, getState());
  enterRule(_localctx, 20, fs_grammarParser::RuleFor_dec);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(fs_grammarParser::Identifier);

    setState(83);
    match(fs_grammarParser::T__35);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_declContext ------------------------------------------------------------------

fs_grammarParser::For_declContext::For_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::For_declContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}

tree::TerminalNode* fs_grammarParser::For_declContext::Integer() {
  return getToken(fs_grammarParser::Integer, 0);
}


size_t fs_grammarParser::For_declContext::getRuleIndex() const {
  return fs_grammarParser::RuleFor_decl;
}

void fs_grammarParser::For_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_decl(this);
}

void fs_grammarParser::For_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_decl(this);
}


antlrcpp::Any fs_grammarParser::For_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_decl(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::For_declContext* fs_grammarParser::for_decl() {
  For_declContext *_localctx = _tracker.createInstance<For_declContext>(_ctx, getState());
  enterRule(_localctx, 22, fs_grammarParser::RuleFor_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(fs_grammarParser::Identifier);
    setState(86);
    match(fs_grammarParser::T__36);
    setState(87);
    match(fs_grammarParser::Integer);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_endContext ------------------------------------------------------------------

fs_grammarParser::For_endContext::For_endContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::For_endContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}

fs_grammarParser::For_end_comp_typeContext* fs_grammarParser::For_endContext::for_end_comp_type() {
  return getRuleContext<fs_grammarParser::For_end_comp_typeContext>(0);
}

tree::TerminalNode* fs_grammarParser::For_endContext::Integer() {
  return getToken(fs_grammarParser::Integer, 0);
}


size_t fs_grammarParser::For_endContext::getRuleIndex() const {
  return fs_grammarParser::RuleFor_end;
}

void fs_grammarParser::For_endContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_end(this);
}

void fs_grammarParser::For_endContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_end(this);
}


antlrcpp::Any fs_grammarParser::For_endContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_end(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::For_endContext* fs_grammarParser::for_end() {
  For_endContext *_localctx = _tracker.createInstance<For_endContext>(_ctx, getState());
  enterRule(_localctx, 24, fs_grammarParser::RuleFor_end);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    match(fs_grammarParser::Identifier);
    setState(90);
    for_end_comp_type();
    setState(91);
    match(fs_grammarParser::Integer);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_end_comp_typeContext ------------------------------------------------------------------

fs_grammarParser::For_end_comp_typeContext::For_end_comp_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fs_grammarParser::For_end_comp_typeContext::getRuleIndex() const {
  return fs_grammarParser::RuleFor_end_comp_type;
}

void fs_grammarParser::For_end_comp_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_end_comp_type(this);
}

void fs_grammarParser::For_end_comp_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_end_comp_type(this);
}


antlrcpp::Any fs_grammarParser::For_end_comp_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitFor_end_comp_type(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::For_end_comp_typeContext* fs_grammarParser::for_end_comp_type() {
  For_end_comp_typeContext *_localctx = _tracker.createInstance<For_end_comp_typeContext>(_ctx, getState());
  enterRule(_localctx, 26, fs_grammarParser::RuleFor_end_comp_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__37)
      | (1ULL << fs_grammarParser::T__38)
      | (1ULL << fs_grammarParser::T__39)
      | (1ULL << fs_grammarParser::T__40))) != 0))) {
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

//----------------- PragmaContext ------------------------------------------------------------------

fs_grammarParser::PragmaContext::PragmaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::PragmaContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::PragmaContext::getRuleIndex() const {
  return fs_grammarParser::RulePragma;
}

void fs_grammarParser::PragmaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPragma(this);
}

void fs_grammarParser::PragmaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPragma(this);
}


antlrcpp::Any fs_grammarParser::PragmaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitPragma(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::PragmaContext* fs_grammarParser::pragma() {
  PragmaContext *_localctx = _tracker.createInstance<PragmaContext>(_ctx, getState());
  enterRule(_localctx, 28, fs_grammarParser::RulePragma);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(95);
    match(fs_grammarParser::T__41);
    setState(96);
    match(fs_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> fs_grammarParser::_decisionToDFA;
atn::PredictionContextCache fs_grammarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN fs_grammarParser::_atn;
std::vector<uint16_t> fs_grammarParser::_serializedATN;

std::vector<std::string> fs_grammarParser::_ruleNames = {
  "program", "code", "reg_instr", "imm_instr", "indep_instr", "reg_opcode", 
  "imm_opcode", "fcore_reg", "for_block", "for_incr", "for_dec", "for_decl", 
  "for_end", "for_end_comp_type", "pragma"
};

std::vector<std::string> fs_grammarParser::_literalNames = {
  "", "','", "'stop'", "'nop'", "'add'", "'sub'", "'mul'", "'mac'", "'shl'", 
  "'shr'", "'sal'", "'sar'", "'mov'", "'ldr'", "'r0'", "'r1'", "'r2'", "'r3'", 
  "'r4'", "'r5'", "'r6'", "'r7'", "'r8'", "'r9'", "'r10'", "'r11'", "'r12'", 
  "'r13'", "'r14'", "'r15'", "'for('", "';'", "')'", "'{'", "'}'", "'++'", 
  "'--'", "'='", "'<'", "'>'", "'<='", "'>='", "'#pragma '"
};

std::vector<std::string> fs_grammarParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "Identifier", "Hexnum", "Integer", "Octalnum", 
  "FloatingPointLiteral", "String", "Label", "WS", "BlockComment", "LineComment"
};

dfa::Vocabulary fs_grammarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> fs_grammarParser::_tokenNames;

fs_grammarParser::Initializer::Initializer() {
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
    0x3, 0x36, 0x65, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x28, 0xa, 0x3, 0xd, 0x3, 
    0xe, 0x3, 0x29, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x5, 0x5, 0x3a, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x4b, 0xa, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x2, 0x2, 0x11, 0x2, 
    0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 
    0x1e, 0x2, 0x6, 0x3, 0x2, 0x4, 0x5, 0x3, 0x2, 0x6, 0xe, 0x3, 0x2, 0x10, 
    0x1f, 0x3, 0x2, 0x28, 0x2b, 0x2, 0x5d, 0x2, 0x20, 0x3, 0x2, 0x2, 0x2, 
    0x4, 0x27, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x8, 0x39, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x3b, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3d, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x10, 0x41, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x43, 0x3, 0x2, 0x2, 0x2, 0x14, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x54, 0x3, 0x2, 0x2, 0x2, 0x18, 0x57, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x5b, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x61, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x5, 0x4, 0x3, 0x2, 0x21, 0x3, 0x3, 
    0x2, 0x2, 0x2, 0x22, 0x28, 0x5, 0x6, 0x4, 0x2, 0x23, 0x28, 0x5, 0x8, 
    0x5, 0x2, 0x24, 0x28, 0x5, 0xa, 0x6, 0x2, 0x25, 0x28, 0x5, 0x12, 0xa, 
    0x2, 0x26, 0x28, 0x5, 0x1e, 0x10, 0x2, 0x27, 0x22, 0x3, 0x2, 0x2, 0x2, 
    0x27, 0x23, 0x3, 0x2, 0x2, 0x2, 0x27, 0x24, 0x3, 0x2, 0x2, 0x2, 0x27, 
    0x25, 0x3, 0x2, 0x2, 0x2, 0x27, 0x26, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x5, 0xc, 
    0x7, 0x2, 0x2c, 0x2d, 0x5, 0x10, 0x9, 0x2, 0x2d, 0x2e, 0x7, 0x3, 0x2, 
    0x2, 0x2e, 0x2f, 0x5, 0x10, 0x9, 0x2, 0x2f, 0x30, 0x7, 0x3, 0x2, 0x2, 
    0x30, 0x31, 0x5, 0x10, 0x9, 0x2, 0x31, 0x7, 0x3, 0x2, 0x2, 0x2, 0x32, 
    0x33, 0x5, 0xe, 0x8, 0x2, 0x33, 0x34, 0x5, 0x10, 0x9, 0x2, 0x34, 0x35, 
    0x7, 0x3, 0x2, 0x2, 0x35, 0x36, 0x7, 0x2f, 0x2, 0x2, 0x36, 0x3a, 0x3, 
    0x2, 0x2, 0x2, 0x37, 0x3a, 0x7, 0x2e, 0x2, 0x2, 0x38, 0x3a, 0x7, 0x30, 
    0x2, 0x2, 0x39, 0x32, 0x3, 0x2, 0x2, 0x2, 0x39, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x39, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x9, 0x3, 0x2, 0x2, 0x2, 
    0x3b, 0x3c, 0x9, 0x2, 0x2, 0x2, 0x3c, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3d, 
    0x3e, 0x9, 0x3, 0x2, 0x2, 0x3e, 0xd, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 
    0x7, 0xf, 0x2, 0x2, 0x40, 0xf, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0x9, 
    0x4, 0x2, 0x2, 0x42, 0x11, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x7, 0x20, 
    0x2, 0x2, 0x44, 0x45, 0x5, 0x18, 0xd, 0x2, 0x45, 0x46, 0x7, 0x21, 0x2, 
    0x2, 0x46, 0x47, 0x5, 0x1a, 0xe, 0x2, 0x47, 0x4a, 0x7, 0x21, 0x2, 0x2, 
    0x48, 0x4b, 0x5, 0x14, 0xb, 0x2, 0x49, 0x4b, 0x5, 0x16, 0xc, 0x2, 0x4a, 
    0x48, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 
    0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x7, 0x22, 0x2, 0x2, 0x4d, 0x4e, 0x7, 
    0x23, 0x2, 0x2, 0x4e, 0x4f, 0x5, 0x4, 0x3, 0x2, 0x4f, 0x50, 0x7, 0x24, 
    0x2, 0x2, 0x50, 0x13, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x7, 0x2d, 0x2, 
    0x2, 0x52, 0x53, 0x7, 0x25, 0x2, 0x2, 0x53, 0x15, 0x3, 0x2, 0x2, 0x2, 
    0x54, 0x55, 0x7, 0x2d, 0x2, 0x2, 0x55, 0x56, 0x7, 0x26, 0x2, 0x2, 0x56, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0x7, 0x2d, 0x2, 0x2, 0x58, 0x59, 
    0x7, 0x27, 0x2, 0x2, 0x59, 0x5a, 0x7, 0x2f, 0x2, 0x2, 0x5a, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0x5b, 0x5c, 0x7, 0x2d, 0x2, 0x2, 0x5c, 0x5d, 0x5, 0x1c, 
    0xf, 0x2, 0x5d, 0x5e, 0x7, 0x2f, 0x2, 0x2, 0x5e, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x5f, 0x60, 0x9, 0x5, 0x2, 0x2, 0x60, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0x61, 0x62, 0x7, 0x2c, 0x2, 0x2, 0x62, 0x63, 0x7, 0x2d, 0x2, 0x2, 0x63, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0x6, 0x27, 0x29, 0x39, 0x4a, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

fs_grammarParser::Initializer fs_grammarParser::_init;
