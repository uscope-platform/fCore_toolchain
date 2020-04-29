
// Generated from /home/fils/git/fCore_has/src/fs_grammar.g4 by ANTLR 4.8


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
  enterRule(_localctx, 0, fs_grammarParser::RuleCode);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(17); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(17);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case fs_grammarParser::T__2:
        case fs_grammarParser::T__3:
        case fs_grammarParser::T__4:
        case fs_grammarParser::T__5:
        case fs_grammarParser::T__6:
        case fs_grammarParser::T__7:
        case fs_grammarParser::T__8:
        case fs_grammarParser::T__9:
        case fs_grammarParser::T__10: {
          setState(14);
          reg_instr();
          break;
        }

        case fs_grammarParser::T__11:
        case fs_grammarParser::Hexnum:
        case fs_grammarParser::Octalnum: {
          setState(15);
          imm_instr();
          break;
        }

        case fs_grammarParser::T__0:
        case fs_grammarParser::T__1: {
          setState(16);
          indep_instr();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(19); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__0)
      | (1ULL << fs_grammarParser::T__1)
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

std::vector<tree::TerminalNode *> fs_grammarParser::Reg_instrContext::Separator() {
  return getTokens(fs_grammarParser::Separator);
}

tree::TerminalNode* fs_grammarParser::Reg_instrContext::Separator(size_t i) {
  return getToken(fs_grammarParser::Separator, i);
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
  enterRule(_localctx, 2, fs_grammarParser::RuleReg_instr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(21);
    reg_opcode();
    setState(22);
    fcore_reg();
    setState(23);
    match(fs_grammarParser::Separator);
    setState(24);
    fcore_reg();
    setState(25);
    match(fs_grammarParser::Separator);
    setState(26);
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

tree::TerminalNode* fs_grammarParser::Imm_instrContext::Separator() {
  return getToken(fs_grammarParser::Separator, 0);
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
  enterRule(_localctx, 4, fs_grammarParser::RuleImm_instr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(35);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case fs_grammarParser::T__11: {
        enterOuterAlt(_localctx, 1);
        setState(28);
        imm_opcode();
        setState(29);
        fcore_reg();
        setState(30);
        match(fs_grammarParser::Separator);
        setState(31);
        match(fs_grammarParser::Integer);
        break;
      }

      case fs_grammarParser::Hexnum: {
        enterOuterAlt(_localctx, 2);
        setState(33);
        match(fs_grammarParser::Hexnum);
        break;
      }

      case fs_grammarParser::Octalnum: {
        enterOuterAlt(_localctx, 3);
        setState(34);
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
  enterRule(_localctx, 6, fs_grammarParser::RuleIndep_instr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    _la = _input->LA(1);
    if (!(_la == fs_grammarParser::T__0

    || _la == fs_grammarParser::T__1)) {
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
  enterRule(_localctx, 8, fs_grammarParser::RuleReg_opcode);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(39);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__2)
      | (1ULL << fs_grammarParser::T__3)
      | (1ULL << fs_grammarParser::T__4)
      | (1ULL << fs_grammarParser::T__5)
      | (1ULL << fs_grammarParser::T__6)
      | (1ULL << fs_grammarParser::T__7)
      | (1ULL << fs_grammarParser::T__8)
      | (1ULL << fs_grammarParser::T__9)
      | (1ULL << fs_grammarParser::T__10))) != 0))) {
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
  enterRule(_localctx, 10, fs_grammarParser::RuleImm_opcode);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(41);
    match(fs_grammarParser::T__11);
   
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
  enterRule(_localctx, 12, fs_grammarParser::RuleFcore_reg);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(43);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__12)
      | (1ULL << fs_grammarParser::T__13)
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
      | (1ULL << fs_grammarParser::T__27))) != 0))) {
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

// Static vars and initialization.
std::vector<dfa::DFA> fs_grammarParser::_decisionToDFA;
atn::PredictionContextCache fs_grammarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN fs_grammarParser::_atn;
std::vector<uint16_t> fs_grammarParser::_serializedATN;

std::vector<std::string> fs_grammarParser::_ruleNames = {
  "code", "reg_instr", "imm_instr", "indep_instr", "reg_opcode", "imm_opcode", 
  "fcore_reg"
};

std::vector<std::string> fs_grammarParser::_literalNames = {
  "", "'stop'", "'nop'", "'add'", "'sub'", "'mul'", "'mac'", "'shl'", "'shr'", 
  "'sal'", "'sar'", "'mov'", "'ldr'", "'r0'", "'r1'", "'r2'", "'r3'", "'r4'", 
  "'r5'", "'r6'", "'r7'", "'r8'", "'r9'", "'r10'", "'r11'", "'r12'", "'r13'", 
  "'r14'", "'r15'", "", "", "", "", "", "", "", "','"
};

std::vector<std::string> fs_grammarParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "Identifier", "Hexnum", "Integer", 
  "Octalnum", "FloatingPointLiteral", "String", "Etiqueta", "Separator", 
  "WS", "BlockComment", "LineComment"
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
    0x3, 0x29, 0x30, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x6, 0x2, 0x14, 0xa, 0x2, 
    0xd, 0x2, 0xe, 0x2, 0x15, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x26, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x2, 0x2, 0x9, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x2, 0x5, 0x3, 0x2, 
    0x3, 0x4, 0x3, 0x2, 0x5, 0xd, 0x3, 0x2, 0xf, 0x1e, 0x2, 0x2d, 0x2, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x17, 0x3, 0x2, 0x2, 0x2, 0x6, 0x25, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x27, 0x3, 0x2, 0x2, 0x2, 0xa, 0x29, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xe, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x14, 0x5, 0x4, 0x3, 0x2, 0x11, 0x14, 0x5, 0x6, 0x4, 0x2, 0x12, 0x14, 
    0x5, 0x8, 0x5, 0x2, 0x13, 0x10, 0x3, 0x2, 0x2, 0x2, 0x13, 0x11, 0x3, 
    0x2, 0x2, 0x2, 0x13, 0x12, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0x3, 0x2, 
    0x2, 0x2, 0x15, 0x13, 0x3, 0x2, 0x2, 0x2, 0x15, 0x16, 0x3, 0x2, 0x2, 
    0x2, 0x16, 0x3, 0x3, 0x2, 0x2, 0x2, 0x17, 0x18, 0x5, 0xa, 0x6, 0x2, 
    0x18, 0x19, 0x5, 0xe, 0x8, 0x2, 0x19, 0x1a, 0x7, 0x26, 0x2, 0x2, 0x1a, 
    0x1b, 0x5, 0xe, 0x8, 0x2, 0x1b, 0x1c, 0x7, 0x26, 0x2, 0x2, 0x1c, 0x1d, 
    0x5, 0xe, 0x8, 0x2, 0x1d, 0x5, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x5, 
    0xc, 0x7, 0x2, 0x1f, 0x20, 0x5, 0xe, 0x8, 0x2, 0x20, 0x21, 0x7, 0x26, 
    0x2, 0x2, 0x21, 0x22, 0x7, 0x21, 0x2, 0x2, 0x22, 0x26, 0x3, 0x2, 0x2, 
    0x2, 0x23, 0x26, 0x7, 0x20, 0x2, 0x2, 0x24, 0x26, 0x7, 0x22, 0x2, 0x2, 
    0x25, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x25, 0x23, 0x3, 0x2, 0x2, 0x2, 0x25, 
    0x24, 0x3, 0x2, 0x2, 0x2, 0x26, 0x7, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 
    0x9, 0x2, 0x2, 0x2, 0x28, 0x9, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x9, 
    0x3, 0x2, 0x2, 0x2a, 0xb, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x7, 0xe, 
    0x2, 0x2, 0x2c, 0xd, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x9, 0x4, 0x2, 
    0x2, 0x2e, 0xf, 0x3, 0x2, 0x2, 0x2, 0x5, 0x13, 0x15, 0x25, 
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
