
// Generated from /home/fils/git/fCore_has/src/frontend/fs_grammar.g4 by ANTLR 4.9.1


#include "fs_grammarListener.h"
#include "fs_grammarVisitor.h"

#include "fs_grammarParser.h"


using namespace antlrcpp;
using namespace asm_parser;
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
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

std::vector<fs_grammarParser::InstructionContext *> fs_grammarParser::CodeContext::instruction() {
  return getRuleContexts<fs_grammarParser::InstructionContext>();
}

fs_grammarParser::InstructionContext* fs_grammarParser::CodeContext::instruction(size_t i) {
  return getRuleContext<fs_grammarParser::InstructionContext>(i);
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

std::vector<fs_grammarParser::DeclarationContext *> fs_grammarParser::CodeContext::declaration() {
  return getRuleContexts<fs_grammarParser::DeclarationContext>();
}

fs_grammarParser::DeclarationContext* fs_grammarParser::CodeContext::declaration(size_t i) {
  return getRuleContext<fs_grammarParser::DeclarationContext>(i);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(68);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case fs_grammarParser::T__1:
        case fs_grammarParser::T__2:
        case fs_grammarParser::T__3:
        case fs_grammarParser::T__4:
        case fs_grammarParser::T__5:
        case fs_grammarParser::T__6:
        case fs_grammarParser::T__7:
        case fs_grammarParser::T__8:
        case fs_grammarParser::T__9:
        case fs_grammarParser::T__10:
        case fs_grammarParser::T__11:
        case fs_grammarParser::T__12:
        case fs_grammarParser::T__13:
        case fs_grammarParser::T__14:
        case fs_grammarParser::T__15:
        case fs_grammarParser::T__16:
        case fs_grammarParser::T__17:
        case fs_grammarParser::T__18:
        case fs_grammarParser::T__19:
        case fs_grammarParser::T__20: {
          setState(64);
          instruction();
          break;
        }

        case fs_grammarParser::T__21: {
          setState(65);
          for_block();
          break;
        }

        case fs_grammarParser::T__33: {
          setState(66);
          pragma();
          break;
        }

        case fs_grammarParser::T__34:
        case fs_grammarParser::T__35:
        case fs_grammarParser::T__36:
        case fs_grammarParser::T__37: {
          setState(67);
          declaration();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(70); 
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
      | (1ULL << fs_grammarParser::T__13)
      | (1ULL << fs_grammarParser::T__14)
      | (1ULL << fs_grammarParser::T__15)
      | (1ULL << fs_grammarParser::T__16)
      | (1ULL << fs_grammarParser::T__17)
      | (1ULL << fs_grammarParser::T__18)
      | (1ULL << fs_grammarParser::T__19)
      | (1ULL << fs_grammarParser::T__20)
      | (1ULL << fs_grammarParser::T__21)
      | (1ULL << fs_grammarParser::T__33)
      | (1ULL << fs_grammarParser::T__34)
      | (1ULL << fs_grammarParser::T__35)
      | (1ULL << fs_grammarParser::T__36)
      | (1ULL << fs_grammarParser::T__37))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

fs_grammarParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Input_declContext* fs_grammarParser::DeclarationContext::input_decl() {
  return getRuleContext<fs_grammarParser::Input_declContext>(0);
}

fs_grammarParser::Variable_declContext* fs_grammarParser::DeclarationContext::variable_decl() {
  return getRuleContext<fs_grammarParser::Variable_declContext>(0);
}

fs_grammarParser::Constant_declContext* fs_grammarParser::DeclarationContext::constant_decl() {
  return getRuleContext<fs_grammarParser::Constant_declContext>(0);
}

fs_grammarParser::Output_declContext* fs_grammarParser::DeclarationContext::output_decl() {
  return getRuleContext<fs_grammarParser::Output_declContext>(0);
}


size_t fs_grammarParser::DeclarationContext::getRuleIndex() const {
  return fs_grammarParser::RuleDeclaration;
}

void fs_grammarParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void fs_grammarParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


antlrcpp::Any fs_grammarParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::DeclarationContext* fs_grammarParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, fs_grammarParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case fs_grammarParser::T__36: {
        setState(72);
        input_decl();
        break;
      }

      case fs_grammarParser::T__34: {
        setState(73);
        variable_decl();
        break;
      }

      case fs_grammarParser::T__35: {
        setState(74);
        constant_decl();
        break;
      }

      case fs_grammarParser::T__37: {
        setState(75);
        output_decl();
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

//----------------- InstructionContext ------------------------------------------------------------------

fs_grammarParser::InstructionContext::InstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Reg_instrContext* fs_grammarParser::InstructionContext::reg_instr() {
  return getRuleContext<fs_grammarParser::Reg_instrContext>(0);
}

fs_grammarParser::Imm_instrContext* fs_grammarParser::InstructionContext::imm_instr() {
  return getRuleContext<fs_grammarParser::Imm_instrContext>(0);
}

fs_grammarParser::Indep_instrContext* fs_grammarParser::InstructionContext::indep_instr() {
  return getRuleContext<fs_grammarParser::Indep_instrContext>(0);
}

fs_grammarParser::Pseudo_instrContext* fs_grammarParser::InstructionContext::pseudo_instr() {
  return getRuleContext<fs_grammarParser::Pseudo_instrContext>(0);
}

fs_grammarParser::Branch_instrContext* fs_grammarParser::InstructionContext::branch_instr() {
  return getRuleContext<fs_grammarParser::Branch_instrContext>(0);
}

fs_grammarParser::Conv_instrContext* fs_grammarParser::InstructionContext::conv_instr() {
  return getRuleContext<fs_grammarParser::Conv_instrContext>(0);
}

fs_grammarParser::Load_instrContext* fs_grammarParser::InstructionContext::load_instr() {
  return getRuleContext<fs_grammarParser::Load_instrContext>(0);
}


size_t fs_grammarParser::InstructionContext::getRuleIndex() const {
  return fs_grammarParser::RuleInstruction;
}

void fs_grammarParser::InstructionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInstruction(this);
}

void fs_grammarParser::InstructionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInstruction(this);
}


antlrcpp::Any fs_grammarParser::InstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitInstruction(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::InstructionContext* fs_grammarParser::instruction() {
  InstructionContext *_localctx = _tracker.createInstance<InstructionContext>(_ctx, getState());
  enterRule(_localctx, 6, fs_grammarParser::RuleInstruction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(85);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case fs_grammarParser::T__4:
      case fs_grammarParser::T__5:
      case fs_grammarParser::T__6:
      case fs_grammarParser::T__7:
      case fs_grammarParser::T__8:
      case fs_grammarParser::T__9:
      case fs_grammarParser::T__10: {
        enterOuterAlt(_localctx, 1);
        setState(78);
        reg_instr();
        break;
      }

      case fs_grammarParser::T__15: {
        enterOuterAlt(_localctx, 2);
        setState(79);
        imm_instr();
        break;
      }

      case fs_grammarParser::T__2:
      case fs_grammarParser::T__3: {
        enterOuterAlt(_localctx, 3);
        setState(80);
        indep_instr();
        break;
      }

      case fs_grammarParser::T__20: {
        enterOuterAlt(_localctx, 4);
        setState(81);
        pseudo_instr();
        break;
      }

      case fs_grammarParser::T__16:
      case fs_grammarParser::T__17:
      case fs_grammarParser::T__18:
      case fs_grammarParser::T__19: {
        enterOuterAlt(_localctx, 5);
        setState(82);
        branch_instr();
        break;
      }

      case fs_grammarParser::T__11:
      case fs_grammarParser::T__12:
      case fs_grammarParser::T__13:
      case fs_grammarParser::T__14: {
        enterOuterAlt(_localctx, 6);
        setState(83);
        conv_instr();
        break;
      }

      case fs_grammarParser::T__1: {
        enterOuterAlt(_localctx, 7);
        setState(84);
        load_instr();
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

//----------------- Reg_instrContext ------------------------------------------------------------------

fs_grammarParser::Reg_instrContext::Reg_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Reg_opcodeContext* fs_grammarParser::Reg_instrContext::reg_opcode() {
  return getRuleContext<fs_grammarParser::Reg_opcodeContext>(0);
}

std::vector<fs_grammarParser::OperandContext *> fs_grammarParser::Reg_instrContext::operand() {
  return getRuleContexts<fs_grammarParser::OperandContext>();
}

fs_grammarParser::OperandContext* fs_grammarParser::Reg_instrContext::operand(size_t i) {
  return getRuleContext<fs_grammarParser::OperandContext>(i);
}

fs_grammarParser::DestinationContext* fs_grammarParser::Reg_instrContext::destination() {
  return getRuleContext<fs_grammarParser::DestinationContext>(0);
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
  enterRule(_localctx, 8, fs_grammarParser::RuleReg_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    reg_opcode();
    setState(88);
    operand();
    setState(89);
    match(fs_grammarParser::T__0);
    setState(90);
    operand();
    setState(91);
    match(fs_grammarParser::T__0);
    setState(92);
    destination();
   
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

fs_grammarParser::DestinationContext* fs_grammarParser::Imm_instrContext::destination() {
  return getRuleContext<fs_grammarParser::DestinationContext>(0);
}

fs_grammarParser::ImmediateContext* fs_grammarParser::Imm_instrContext::immediate() {
  return getRuleContext<fs_grammarParser::ImmediateContext>(0);
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
  enterRule(_localctx, 10, fs_grammarParser::RuleImm_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    imm_opcode();
    setState(95);
    destination();
    setState(96);
    match(fs_grammarParser::T__0);
    setState(97);
    immediate();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Load_instrContext ------------------------------------------------------------------

fs_grammarParser::Load_instrContext::Load_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::DestinationContext* fs_grammarParser::Load_instrContext::destination() {
  return getRuleContext<fs_grammarParser::DestinationContext>(0);
}

tree::TerminalNode* fs_grammarParser::Load_instrContext::FloatingPointLiteral() {
  return getToken(fs_grammarParser::FloatingPointLiteral, 0);
}


size_t fs_grammarParser::Load_instrContext::getRuleIndex() const {
  return fs_grammarParser::RuleLoad_instr;
}

void fs_grammarParser::Load_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoad_instr(this);
}

void fs_grammarParser::Load_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoad_instr(this);
}


antlrcpp::Any fs_grammarParser::Load_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitLoad_instr(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Load_instrContext* fs_grammarParser::load_instr() {
  Load_instrContext *_localctx = _tracker.createInstance<Load_instrContext>(_ctx, getState());
  enterRule(_localctx, 12, fs_grammarParser::RuleLoad_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(99);
    match(fs_grammarParser::T__1);
    setState(100);
    destination();
    setState(101);
    match(fs_grammarParser::T__0);
    setState(102);
    match(fs_grammarParser::FloatingPointLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Branch_instrContext ------------------------------------------------------------------

fs_grammarParser::Branch_instrContext::Branch_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Branch_opcodeContext* fs_grammarParser::Branch_instrContext::branch_opcode() {
  return getRuleContext<fs_grammarParser::Branch_opcodeContext>(0);
}

std::vector<fs_grammarParser::OperandContext *> fs_grammarParser::Branch_instrContext::operand() {
  return getRuleContexts<fs_grammarParser::OperandContext>();
}

fs_grammarParser::OperandContext* fs_grammarParser::Branch_instrContext::operand(size_t i) {
  return getRuleContext<fs_grammarParser::OperandContext>(i);
}


size_t fs_grammarParser::Branch_instrContext::getRuleIndex() const {
  return fs_grammarParser::RuleBranch_instr;
}

void fs_grammarParser::Branch_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBranch_instr(this);
}

void fs_grammarParser::Branch_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBranch_instr(this);
}


antlrcpp::Any fs_grammarParser::Branch_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitBranch_instr(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Branch_instrContext* fs_grammarParser::branch_instr() {
  Branch_instrContext *_localctx = _tracker.createInstance<Branch_instrContext>(_ctx, getState());
  enterRule(_localctx, 14, fs_grammarParser::RuleBranch_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(104);
    branch_opcode();
    setState(105);
    operand();
    setState(106);
    match(fs_grammarParser::T__0);
    setState(107);
    operand();
    setState(108);
    match(fs_grammarParser::T__0);
    setState(109);
    operand();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Conv_instrContext ------------------------------------------------------------------

fs_grammarParser::Conv_instrContext::Conv_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Conv_opcodeContext* fs_grammarParser::Conv_instrContext::conv_opcode() {
  return getRuleContext<fs_grammarParser::Conv_opcodeContext>(0);
}

std::vector<fs_grammarParser::OperandContext *> fs_grammarParser::Conv_instrContext::operand() {
  return getRuleContexts<fs_grammarParser::OperandContext>();
}

fs_grammarParser::OperandContext* fs_grammarParser::Conv_instrContext::operand(size_t i) {
  return getRuleContext<fs_grammarParser::OperandContext>(i);
}


size_t fs_grammarParser::Conv_instrContext::getRuleIndex() const {
  return fs_grammarParser::RuleConv_instr;
}

void fs_grammarParser::Conv_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConv_instr(this);
}

void fs_grammarParser::Conv_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConv_instr(this);
}


antlrcpp::Any fs_grammarParser::Conv_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitConv_instr(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Conv_instrContext* fs_grammarParser::conv_instr() {
  Conv_instrContext *_localctx = _tracker.createInstance<Conv_instrContext>(_ctx, getState());
  enterRule(_localctx, 16, fs_grammarParser::RuleConv_instr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    conv_opcode();
    setState(112);
    operand();
    setState(113);
    match(fs_grammarParser::T__0);
    setState(114);
    operand();
   
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
  enterRule(_localctx, 18, fs_grammarParser::RuleIndep_instr);
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
    setState(116);
    _la = _input->LA(1);
    if (!(_la == fs_grammarParser::T__2

    || _la == fs_grammarParser::T__3)) {
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

//----------------- Pseudo_instrContext ------------------------------------------------------------------

fs_grammarParser::Pseudo_instrContext::Pseudo_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Pseudo_opcodeContext* fs_grammarParser::Pseudo_instrContext::pseudo_opcode() {
  return getRuleContext<fs_grammarParser::Pseudo_opcodeContext>(0);
}

std::vector<fs_grammarParser::OperandContext *> fs_grammarParser::Pseudo_instrContext::operand() {
  return getRuleContexts<fs_grammarParser::OperandContext>();
}

fs_grammarParser::OperandContext* fs_grammarParser::Pseudo_instrContext::operand(size_t i) {
  return getRuleContext<fs_grammarParser::OperandContext>(i);
}


size_t fs_grammarParser::Pseudo_instrContext::getRuleIndex() const {
  return fs_grammarParser::RulePseudo_instr;
}

void fs_grammarParser::Pseudo_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudo_instr(this);
}

void fs_grammarParser::Pseudo_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudo_instr(this);
}


antlrcpp::Any fs_grammarParser::Pseudo_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitPseudo_instr(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Pseudo_instrContext* fs_grammarParser::pseudo_instr() {
  Pseudo_instrContext *_localctx = _tracker.createInstance<Pseudo_instrContext>(_ctx, getState());
  enterRule(_localctx, 20, fs_grammarParser::RulePseudo_instr);
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
    setState(118);
    pseudo_opcode();
    setState(119);
    operand();
    setState(120);
    match(fs_grammarParser::T__0);
    setState(121);
    operand();
    setState(126);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == fs_grammarParser::T__0) {
      setState(122);
      match(fs_grammarParser::T__0);
      setState(123);
      operand();
      setState(128);
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

//----------------- OperandContext ------------------------------------------------------------------

fs_grammarParser::OperandContext::OperandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::OperandContext::Register() {
  return getToken(fs_grammarParser::Register, 0);
}

tree::TerminalNode* fs_grammarParser::OperandContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::OperandContext::getRuleIndex() const {
  return fs_grammarParser::RuleOperand;
}

void fs_grammarParser::OperandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperand(this);
}

void fs_grammarParser::OperandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperand(this);
}


antlrcpp::Any fs_grammarParser::OperandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitOperand(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::OperandContext* fs_grammarParser::operand() {
  OperandContext *_localctx = _tracker.createInstance<OperandContext>(_ctx, getState());
  enterRule(_localctx, 22, fs_grammarParser::RuleOperand);
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
    setState(129);
    _la = _input->LA(1);
    if (!(_la == fs_grammarParser::Register

    || _la == fs_grammarParser::Identifier)) {
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

//----------------- DestinationContext ------------------------------------------------------------------

fs_grammarParser::DestinationContext::DestinationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::DestinationContext::Register() {
  return getToken(fs_grammarParser::Register, 0);
}

tree::TerminalNode* fs_grammarParser::DestinationContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::DestinationContext::getRuleIndex() const {
  return fs_grammarParser::RuleDestination;
}

void fs_grammarParser::DestinationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDestination(this);
}

void fs_grammarParser::DestinationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDestination(this);
}


antlrcpp::Any fs_grammarParser::DestinationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitDestination(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::DestinationContext* fs_grammarParser::destination() {
  DestinationContext *_localctx = _tracker.createInstance<DestinationContext>(_ctx, getState());
  enterRule(_localctx, 24, fs_grammarParser::RuleDestination);
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
    setState(131);
    _la = _input->LA(1);
    if (!(_la == fs_grammarParser::Register

    || _la == fs_grammarParser::Identifier)) {
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

//----------------- ImmediateContext ------------------------------------------------------------------

fs_grammarParser::ImmediateContext::ImmediateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::ImmediateContext::Integer() {
  return getToken(fs_grammarParser::Integer, 0);
}

tree::TerminalNode* fs_grammarParser::ImmediateContext::Hexnum() {
  return getToken(fs_grammarParser::Hexnum, 0);
}

tree::TerminalNode* fs_grammarParser::ImmediateContext::Octalnum() {
  return getToken(fs_grammarParser::Octalnum, 0);
}

tree::TerminalNode* fs_grammarParser::ImmediateContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::ImmediateContext::getRuleIndex() const {
  return fs_grammarParser::RuleImmediate;
}

void fs_grammarParser::ImmediateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImmediate(this);
}

void fs_grammarParser::ImmediateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImmediate(this);
}


antlrcpp::Any fs_grammarParser::ImmediateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitImmediate(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::ImmediateContext* fs_grammarParser::immediate() {
  ImmediateContext *_localctx = _tracker.createInstance<ImmediateContext>(_ctx, getState());
  enterRule(_localctx, 26, fs_grammarParser::RuleImmediate);
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
    setState(133);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::Identifier)
      | (1ULL << fs_grammarParser::Hexnum)
      | (1ULL << fs_grammarParser::Integer)
      | (1ULL << fs_grammarParser::Octalnum))) != 0))) {
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

//----------------- Float_constContext ------------------------------------------------------------------

fs_grammarParser::Float_constContext::Float_constContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::Float_constContext::FloatingPointLiteral() {
  return getToken(fs_grammarParser::FloatingPointLiteral, 0);
}


size_t fs_grammarParser::Float_constContext::getRuleIndex() const {
  return fs_grammarParser::RuleFloat_const;
}

void fs_grammarParser::Float_constContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloat_const(this);
}

void fs_grammarParser::Float_constContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloat_const(this);
}


antlrcpp::Any fs_grammarParser::Float_constContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitFloat_const(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Float_constContext* fs_grammarParser::float_const() {
  Float_constContext *_localctx = _tracker.createInstance<Float_constContext>(_ctx, getState());
  enterRule(_localctx, 28, fs_grammarParser::RuleFloat_const);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(135);
    match(fs_grammarParser::FloatingPointLiteral);
   
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
  enterRule(_localctx, 30, fs_grammarParser::RuleReg_opcode);
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
    setState(137);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__4)
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

//----------------- Conv_opcodeContext ------------------------------------------------------------------

fs_grammarParser::Conv_opcodeContext::Conv_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fs_grammarParser::Conv_opcodeContext::getRuleIndex() const {
  return fs_grammarParser::RuleConv_opcode;
}

void fs_grammarParser::Conv_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConv_opcode(this);
}

void fs_grammarParser::Conv_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConv_opcode(this);
}


antlrcpp::Any fs_grammarParser::Conv_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitConv_opcode(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Conv_opcodeContext* fs_grammarParser::conv_opcode() {
  Conv_opcodeContext *_localctx = _tracker.createInstance<Conv_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 32, fs_grammarParser::RuleConv_opcode);
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
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__11)
      | (1ULL << fs_grammarParser::T__12)
      | (1ULL << fs_grammarParser::T__13)
      | (1ULL << fs_grammarParser::T__14))) != 0))) {
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
  enterRule(_localctx, 34, fs_grammarParser::RuleImm_opcode);

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
    match(fs_grammarParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Branch_opcodeContext ------------------------------------------------------------------

fs_grammarParser::Branch_opcodeContext::Branch_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fs_grammarParser::Branch_opcodeContext::getRuleIndex() const {
  return fs_grammarParser::RuleBranch_opcode;
}

void fs_grammarParser::Branch_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBranch_opcode(this);
}

void fs_grammarParser::Branch_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBranch_opcode(this);
}


antlrcpp::Any fs_grammarParser::Branch_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitBranch_opcode(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Branch_opcodeContext* fs_grammarParser::branch_opcode() {
  Branch_opcodeContext *_localctx = _tracker.createInstance<Branch_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 36, fs_grammarParser::RuleBranch_opcode);
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
    setState(143);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__16)
      | (1ULL << fs_grammarParser::T__17)
      | (1ULL << fs_grammarParser::T__18)
      | (1ULL << fs_grammarParser::T__19))) != 0))) {
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

//----------------- Pseudo_opcodeContext ------------------------------------------------------------------

fs_grammarParser::Pseudo_opcodeContext::Pseudo_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fs_grammarParser::Pseudo_opcodeContext::getRuleIndex() const {
  return fs_grammarParser::RulePseudo_opcode;
}

void fs_grammarParser::Pseudo_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPseudo_opcode(this);
}

void fs_grammarParser::Pseudo_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPseudo_opcode(this);
}


antlrcpp::Any fs_grammarParser::Pseudo_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitPseudo_opcode(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Pseudo_opcodeContext* fs_grammarParser::pseudo_opcode() {
  Pseudo_opcodeContext *_localctx = _tracker.createInstance<Pseudo_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 38, fs_grammarParser::RulePseudo_opcode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(fs_grammarParser::T__20);
   
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
  enterRule(_localctx, 40, fs_grammarParser::RuleFor_block);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    match(fs_grammarParser::T__21);
    setState(148);
    for_decl();
    setState(149);
    match(fs_grammarParser::T__22);
    setState(150);
    for_end();
    setState(151);
    match(fs_grammarParser::T__22);
    setState(154);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(152);
      for_incr();
      break;
    }

    case 2: {
      setState(153);
      for_dec();
      break;
    }

    default:
      break;
    }
    setState(156);
    match(fs_grammarParser::T__23);
    setState(157);
    match(fs_grammarParser::T__24);
    setState(158);
    code();
    setState(159);
    match(fs_grammarParser::T__25);
   
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
  enterRule(_localctx, 42, fs_grammarParser::RuleFor_incr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    match(fs_grammarParser::Identifier);

    setState(162);
    match(fs_grammarParser::T__26);
   
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
  enterRule(_localctx, 44, fs_grammarParser::RuleFor_dec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(fs_grammarParser::Identifier);

    setState(165);
    match(fs_grammarParser::T__27);
   
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
  enterRule(_localctx, 46, fs_grammarParser::RuleFor_decl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(167);
    match(fs_grammarParser::Identifier);
    setState(168);
    match(fs_grammarParser::T__28);
    setState(169);
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
  enterRule(_localctx, 48, fs_grammarParser::RuleFor_end);

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
    match(fs_grammarParser::Identifier);
    setState(172);
    for_end_comp_type();
    setState(173);
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
  enterRule(_localctx, 50, fs_grammarParser::RuleFor_end_comp_type);
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
    setState(175);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__29)
      | (1ULL << fs_grammarParser::T__30)
      | (1ULL << fs_grammarParser::T__31)
      | (1ULL << fs_grammarParser::T__32))) != 0))) {
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
  enterRule(_localctx, 52, fs_grammarParser::RulePragma);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    match(fs_grammarParser::T__33);
    setState(178);
    match(fs_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_declContext ------------------------------------------------------------------

fs_grammarParser::Variable_declContext::Variable_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::Variable_declContext::Register() {
  return getToken(fs_grammarParser::Register, 0);
}

tree::TerminalNode* fs_grammarParser::Variable_declContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::Variable_declContext::getRuleIndex() const {
  return fs_grammarParser::RuleVariable_decl;
}

void fs_grammarParser::Variable_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable_decl(this);
}

void fs_grammarParser::Variable_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable_decl(this);
}


antlrcpp::Any fs_grammarParser::Variable_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitVariable_decl(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Variable_declContext* fs_grammarParser::variable_decl() {
  Variable_declContext *_localctx = _tracker.createInstance<Variable_declContext>(_ctx, getState());
  enterRule(_localctx, 54, fs_grammarParser::RuleVariable_decl);
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
    setState(180);
    match(fs_grammarParser::T__34);
    setState(181);
    _la = _input->LA(1);
    if (!(_la == fs_grammarParser::Register

    || _la == fs_grammarParser::Identifier)) {
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

//----------------- Constant_declContext ------------------------------------------------------------------

fs_grammarParser::Constant_declContext::Constant_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::Constant_declContext::Register() {
  return getToken(fs_grammarParser::Register, 0);
}

tree::TerminalNode* fs_grammarParser::Constant_declContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::Constant_declContext::getRuleIndex() const {
  return fs_grammarParser::RuleConstant_decl;
}

void fs_grammarParser::Constant_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstant_decl(this);
}

void fs_grammarParser::Constant_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstant_decl(this);
}


antlrcpp::Any fs_grammarParser::Constant_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitConstant_decl(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Constant_declContext* fs_grammarParser::constant_decl() {
  Constant_declContext *_localctx = _tracker.createInstance<Constant_declContext>(_ctx, getState());
  enterRule(_localctx, 56, fs_grammarParser::RuleConstant_decl);
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
    match(fs_grammarParser::T__35);
    setState(184);
    _la = _input->LA(1);
    if (!(_la == fs_grammarParser::Register

    || _la == fs_grammarParser::Identifier)) {
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

//----------------- Input_declContext ------------------------------------------------------------------

fs_grammarParser::Input_declContext::Input_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::Input_declContext::Register() {
  return getToken(fs_grammarParser::Register, 0);
}

tree::TerminalNode* fs_grammarParser::Input_declContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::Input_declContext::getRuleIndex() const {
  return fs_grammarParser::RuleInput_decl;
}

void fs_grammarParser::Input_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInput_decl(this);
}

void fs_grammarParser::Input_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInput_decl(this);
}


antlrcpp::Any fs_grammarParser::Input_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitInput_decl(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Input_declContext* fs_grammarParser::input_decl() {
  Input_declContext *_localctx = _tracker.createInstance<Input_declContext>(_ctx, getState());
  enterRule(_localctx, 58, fs_grammarParser::RuleInput_decl);
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
    setState(186);
    match(fs_grammarParser::T__36);
    setState(187);
    _la = _input->LA(1);
    if (!(_la == fs_grammarParser::Register

    || _la == fs_grammarParser::Identifier)) {
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

//----------------- Output_declContext ------------------------------------------------------------------

fs_grammarParser::Output_declContext::Output_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fs_grammarParser::Output_declContext::Register() {
  return getToken(fs_grammarParser::Register, 0);
}

tree::TerminalNode* fs_grammarParser::Output_declContext::Identifier() {
  return getToken(fs_grammarParser::Identifier, 0);
}


size_t fs_grammarParser::Output_declContext::getRuleIndex() const {
  return fs_grammarParser::RuleOutput_decl;
}

void fs_grammarParser::Output_declContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOutput_decl(this);
}

void fs_grammarParser::Output_declContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOutput_decl(this);
}


antlrcpp::Any fs_grammarParser::Output_declContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitOutput_decl(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Output_declContext* fs_grammarParser::output_decl() {
  Output_declContext *_localctx = _tracker.createInstance<Output_declContext>(_ctx, getState());
  enterRule(_localctx, 60, fs_grammarParser::RuleOutput_decl);
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
    setState(189);
    match(fs_grammarParser::T__37);
    setState(190);
    _la = _input->LA(1);
    if (!(_la == fs_grammarParser::Register

    || _la == fs_grammarParser::Identifier)) {
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
  "program", "code", "declaration", "instruction", "reg_instr", "imm_instr", 
  "load_instr", "branch_instr", "conv_instr", "indep_instr", "pseudo_instr", 
  "operand", "destination", "immediate", "float_const", "reg_opcode", "conv_opcode", 
  "imm_opcode", "branch_opcode", "pseudo_opcode", "for_block", "for_incr", 
  "for_dec", "for_decl", "for_end", "for_end_comp_type", "pragma", "variable_decl", 
  "constant_decl", "input_decl", "output_decl"
};

std::vector<std::string> fs_grammarParser::_literalNames = {
  "", "','", "'ldc'", "'stop'", "'nop'", "'add'", "'sub'", "'mul'", "'and'", 
  "'or'", "'satp'", "'satn'", "'itf'", "'fti'", "'not'", "'rec'", "'ldr'", 
  "'ble'", "'bgt'", "'beq'", "'bne'", "'mov'", "'for('", "';'", "')'", "'{'", 
  "'}'", "'++'", "'--'", "'='", "'<'", "'>'", "'<='", "'>='", "'#pragma '", 
  "'let'", "'const'", "'input'", "'output'"
};

std::vector<std::string> fs_grammarParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "Register", "Identifier", "Hexnum", "Integer", "Octalnum", 
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
    0x3, 0x33, 0xc3, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 
    0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 
    0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 
    0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x47, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0x48, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x4f, 0xa, 0x4, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x5, 0x5, 0x58, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x7f, 0xa, 0xc, 
    0xc, 0xc, 0xe, 0xc, 0x82, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x9d, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x2, 0x2, 0x21, 0x2, 0x4, 0x6, 0x8, 0xa, 
    0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 
    0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 
    0x3c, 0x3e, 0x2, 0x9, 0x3, 0x2, 0x5, 0x6, 0x3, 0x2, 0x29, 0x2a, 0x3, 
    0x2, 0x2a, 0x2d, 0x3, 0x2, 0x7, 0xd, 0x3, 0x2, 0xe, 0x11, 0x3, 0x2, 
    0x13, 0x16, 0x3, 0x2, 0x20, 0x23, 0x2, 0xb2, 0x2, 0x40, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x46, 0x3, 0x2, 0x2, 0x2, 0x6, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0xa, 0x59, 0x3, 0x2, 0x2, 0x2, 0xc, 0x60, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x65, 0x3, 0x2, 0x2, 0x2, 0x10, 0x6a, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x71, 0x3, 0x2, 0x2, 0x2, 0x14, 0x76, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x78, 0x3, 0x2, 0x2, 0x2, 0x18, 0x83, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x85, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x87, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x89, 0x3, 0x2, 0x2, 0x2, 0x20, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0x8d, 0x3, 0x2, 0x2, 0x2, 0x24, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x26, 0x91, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0x93, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x95, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xa6, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x32, 0xad, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0xb1, 0x3, 0x2, 0x2, 0x2, 0x36, 0xb3, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0xb6, 0x3, 0x2, 0x2, 0x2, 0x3a, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0xbc, 0x3, 0x2, 0x2, 0x2, 0x3e, 0xbf, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 
    0x5, 0x4, 0x3, 0x2, 0x41, 0x3, 0x3, 0x2, 0x2, 0x2, 0x42, 0x47, 0x5, 
    0x8, 0x5, 0x2, 0x43, 0x47, 0x5, 0x2a, 0x16, 0x2, 0x44, 0x47, 0x5, 0x36, 
    0x1c, 0x2, 0x45, 0x47, 0x5, 0x6, 0x4, 0x2, 0x46, 0x42, 0x3, 0x2, 0x2, 
    0x2, 0x46, 0x43, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x45, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 0x2, 0x48, 
    0x46, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x3, 0x2, 0x2, 0x2, 0x49, 0x5, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x4f, 0x5, 0x3c, 0x1f, 0x2, 0x4b, 0x4f, 0x5, 
    0x38, 0x1d, 0x2, 0x4c, 0x4f, 0x5, 0x3a, 0x1e, 0x2, 0x4d, 0x4f, 0x5, 
    0x3e, 0x20, 0x2, 0x4e, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4b, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4d, 0x3, 0x2, 0x2, 
    0x2, 0x4f, 0x7, 0x3, 0x2, 0x2, 0x2, 0x50, 0x58, 0x5, 0xa, 0x6, 0x2, 
    0x51, 0x58, 0x5, 0xc, 0x7, 0x2, 0x52, 0x58, 0x5, 0x14, 0xb, 0x2, 0x53, 
    0x58, 0x5, 0x16, 0xc, 0x2, 0x54, 0x58, 0x5, 0x10, 0x9, 0x2, 0x55, 0x58, 
    0x5, 0x12, 0xa, 0x2, 0x56, 0x58, 0x5, 0xe, 0x8, 0x2, 0x57, 0x50, 0x3, 
    0x2, 0x2, 0x2, 0x57, 0x51, 0x3, 0x2, 0x2, 0x2, 0x57, 0x52, 0x3, 0x2, 
    0x2, 0x2, 0x57, 0x53, 0x3, 0x2, 0x2, 0x2, 0x57, 0x54, 0x3, 0x2, 0x2, 
    0x2, 0x57, 0x55, 0x3, 0x2, 0x2, 0x2, 0x57, 0x56, 0x3, 0x2, 0x2, 0x2, 
    0x58, 0x9, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x5, 0x20, 0x11, 0x2, 0x5a, 
    0x5b, 0x5, 0x18, 0xd, 0x2, 0x5b, 0x5c, 0x7, 0x3, 0x2, 0x2, 0x5c, 0x5d, 
    0x5, 0x18, 0xd, 0x2, 0x5d, 0x5e, 0x7, 0x3, 0x2, 0x2, 0x5e, 0x5f, 0x5, 
    0x1a, 0xe, 0x2, 0x5f, 0xb, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x5, 0x24, 
    0x13, 0x2, 0x61, 0x62, 0x5, 0x1a, 0xe, 0x2, 0x62, 0x63, 0x7, 0x3, 0x2, 
    0x2, 0x63, 0x64, 0x5, 0x1c, 0xf, 0x2, 0x64, 0xd, 0x3, 0x2, 0x2, 0x2, 
    0x65, 0x66, 0x7, 0x4, 0x2, 0x2, 0x66, 0x67, 0x5, 0x1a, 0xe, 0x2, 0x67, 
    0x68, 0x7, 0x3, 0x2, 0x2, 0x68, 0x69, 0x7, 0x2e, 0x2, 0x2, 0x69, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 0x5, 0x26, 0x14, 0x2, 0x6b, 0x6c, 0x5, 
    0x18, 0xd, 0x2, 0x6c, 0x6d, 0x7, 0x3, 0x2, 0x2, 0x6d, 0x6e, 0x5, 0x18, 
    0xd, 0x2, 0x6e, 0x6f, 0x7, 0x3, 0x2, 0x2, 0x6f, 0x70, 0x5, 0x18, 0xd, 
    0x2, 0x70, 0x11, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x5, 0x22, 0x12, 0x2, 
    0x72, 0x73, 0x5, 0x18, 0xd, 0x2, 0x73, 0x74, 0x7, 0x3, 0x2, 0x2, 0x74, 
    0x75, 0x5, 0x18, 0xd, 0x2, 0x75, 0x13, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 
    0x9, 0x2, 0x2, 0x2, 0x77, 0x15, 0x3, 0x2, 0x2, 0x2, 0x78, 0x79, 0x5, 
    0x28, 0x15, 0x2, 0x79, 0x7a, 0x5, 0x18, 0xd, 0x2, 0x7a, 0x7b, 0x7, 0x3, 
    0x2, 0x2, 0x7b, 0x80, 0x5, 0x18, 0xd, 0x2, 0x7c, 0x7d, 0x7, 0x3, 0x2, 
    0x2, 0x7d, 0x7f, 0x5, 0x18, 0xd, 0x2, 0x7e, 0x7c, 0x3, 0x2, 0x2, 0x2, 
    0x7f, 0x82, 0x3, 0x2, 0x2, 0x2, 0x80, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x80, 
    0x81, 0x3, 0x2, 0x2, 0x2, 0x81, 0x17, 0x3, 0x2, 0x2, 0x2, 0x82, 0x80, 
    0x3, 0x2, 0x2, 0x2, 0x83, 0x84, 0x9, 0x3, 0x2, 0x2, 0x84, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0x85, 0x86, 0x9, 0x3, 0x2, 0x2, 0x86, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0x87, 0x88, 0x9, 0x4, 0x2, 0x2, 0x88, 0x1d, 0x3, 0x2, 0x2, 
    0x2, 0x89, 0x8a, 0x7, 0x2e, 0x2, 0x2, 0x8a, 0x1f, 0x3, 0x2, 0x2, 0x2, 
    0x8b, 0x8c, 0x9, 0x5, 0x2, 0x2, 0x8c, 0x21, 0x3, 0x2, 0x2, 0x2, 0x8d, 
    0x8e, 0x9, 0x6, 0x2, 0x2, 0x8e, 0x23, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x90, 
    0x7, 0x12, 0x2, 0x2, 0x90, 0x25, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x9, 
    0x7, 0x2, 0x2, 0x92, 0x27, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x7, 0x17, 
    0x2, 0x2, 0x94, 0x29, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x7, 0x18, 0x2, 
    0x2, 0x96, 0x97, 0x5, 0x30, 0x19, 0x2, 0x97, 0x98, 0x7, 0x19, 0x2, 0x2, 
    0x98, 0x99, 0x5, 0x32, 0x1a, 0x2, 0x99, 0x9c, 0x7, 0x19, 0x2, 0x2, 0x9a, 
    0x9d, 0x5, 0x2c, 0x17, 0x2, 0x9b, 0x9d, 0x5, 0x2e, 0x18, 0x2, 0x9c, 
    0x9a, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 
    0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x1a, 0x2, 0x2, 0x9f, 0xa0, 0x7, 
    0x1b, 0x2, 0x2, 0xa0, 0xa1, 0x5, 0x4, 0x3, 0x2, 0xa1, 0xa2, 0x7, 0x1c, 
    0x2, 0x2, 0xa2, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa4, 0x7, 0x2a, 0x2, 
    0x2, 0xa4, 0xa5, 0x7, 0x1d, 0x2, 0x2, 0xa5, 0x2d, 0x3, 0x2, 0x2, 0x2, 
    0xa6, 0xa7, 0x7, 0x2a, 0x2, 0x2, 0xa7, 0xa8, 0x7, 0x1e, 0x2, 0x2, 0xa8, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xaa, 0x7, 0x2a, 0x2, 0x2, 0xaa, 0xab, 
    0x7, 0x1f, 0x2, 0x2, 0xab, 0xac, 0x7, 0x2c, 0x2, 0x2, 0xac, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0xad, 0xae, 0x7, 0x2a, 0x2, 0x2, 0xae, 0xaf, 0x5, 0x34, 
    0x1b, 0x2, 0xaf, 0xb0, 0x7, 0x2c, 0x2, 0x2, 0xb0, 0x33, 0x3, 0x2, 0x2, 
    0x2, 0xb1, 0xb2, 0x9, 0x8, 0x2, 0x2, 0xb2, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0xb3, 0xb4, 0x7, 0x24, 0x2, 0x2, 0xb4, 0xb5, 0x7, 0x2a, 0x2, 0x2, 0xb5, 
    0x37, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x7, 0x25, 0x2, 0x2, 0xb7, 0xb8, 
    0x9, 0x3, 0x2, 0x2, 0xb8, 0x39, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xba, 0x7, 
    0x26, 0x2, 0x2, 0xba, 0xbb, 0x9, 0x3, 0x2, 0x2, 0xbb, 0x3b, 0x3, 0x2, 
    0x2, 0x2, 0xbc, 0xbd, 0x7, 0x27, 0x2, 0x2, 0xbd, 0xbe, 0x9, 0x3, 0x2, 
    0x2, 0xbe, 0x3d, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 0x7, 0x28, 0x2, 0x2, 
    0xc0, 0xc1, 0x9, 0x3, 0x2, 0x2, 0xc1, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x46, 0x48, 0x4e, 0x57, 0x80, 0x9c, 
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
