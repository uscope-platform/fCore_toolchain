
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
    setState(60);
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

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(66);
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
        case fs_grammarParser::T__20:
        case fs_grammarParser::T__21:
        case fs_grammarParser::T__22:
        case fs_grammarParser::T__23:
        case fs_grammarParser::T__24:
        case fs_grammarParser::T__25:
        case fs_grammarParser::T__26: {
          setState(62);
          instruction();
          break;
        }

        case fs_grammarParser::T__27: {
          setState(63);
          for_block();
          break;
        }

        case fs_grammarParser::T__39: {
          setState(64);
          pragma();
          break;
        }

        case fs_grammarParser::T__40:
        case fs_grammarParser::T__41:
        case fs_grammarParser::T__42:
        case fs_grammarParser::T__43: {
          setState(65);
          declaration();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(68); 
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
      | (1ULL << fs_grammarParser::T__22)
      | (1ULL << fs_grammarParser::T__23)
      | (1ULL << fs_grammarParser::T__24)
      | (1ULL << fs_grammarParser::T__25)
      | (1ULL << fs_grammarParser::T__26)
      | (1ULL << fs_grammarParser::T__27)
      | (1ULL << fs_grammarParser::T__39)
      | (1ULL << fs_grammarParser::T__40)
      | (1ULL << fs_grammarParser::T__41)
      | (1ULL << fs_grammarParser::T__42)
      | (1ULL << fs_grammarParser::T__43))) != 0));
   
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

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case fs_grammarParser::T__42: {
        setState(70);
        input_decl();
        break;
      }

      case fs_grammarParser::T__40: {
        setState(71);
        variable_decl();
        break;
      }

      case fs_grammarParser::T__41: {
        setState(72);
        constant_decl();
        break;
      }

      case fs_grammarParser::T__43: {
        setState(73);
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

fs_grammarParser::Imm_alu_instrContext* fs_grammarParser::InstructionContext::imm_alu_instr() {
  return getRuleContext<fs_grammarParser::Imm_alu_instrContext>(0);
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

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(82);
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
        enterOuterAlt(_localctx, 1);
        setState(76);
        reg_instr();
        break;
      }

      case fs_grammarParser::T__21: {
        enterOuterAlt(_localctx, 2);
        setState(77);
        imm_instr();
        break;
      }

      case fs_grammarParser::T__1:
      case fs_grammarParser::T__2: {
        enterOuterAlt(_localctx, 3);
        setState(78);
        indep_instr();
        break;
      }

      case fs_grammarParser::T__26: {
        enterOuterAlt(_localctx, 4);
        setState(79);
        pseudo_instr();
        break;
      }

      case fs_grammarParser::T__22:
      case fs_grammarParser::T__23:
      case fs_grammarParser::T__24:
      case fs_grammarParser::T__25: {
        enterOuterAlt(_localctx, 5);
        setState(80);
        branch_instr();
        break;
      }

      case fs_grammarParser::T__12:
      case fs_grammarParser::T__13:
      case fs_grammarParser::T__14:
      case fs_grammarParser::T__15:
      case fs_grammarParser::T__16:
      case fs_grammarParser::T__17:
      case fs_grammarParser::T__18:
      case fs_grammarParser::T__19:
      case fs_grammarParser::T__20: {
        enterOuterAlt(_localctx, 6);
        setState(81);
        imm_alu_instr();
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

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    reg_opcode();
    setState(85);
    operand();
    setState(86);
    match(fs_grammarParser::T__0);
    setState(87);
    operand();
    setState(88);
    match(fs_grammarParser::T__0);
    setState(89);
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

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    imm_opcode();
    setState(92);
    destination();
    setState(93);
    match(fs_grammarParser::T__0);
    setState(94);
    immediate();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Imm_alu_instrContext ------------------------------------------------------------------

fs_grammarParser::Imm_alu_instrContext::Imm_alu_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Imm_alu_opcodeContext* fs_grammarParser::Imm_alu_instrContext::imm_alu_opcode() {
  return getRuleContext<fs_grammarParser::Imm_alu_opcodeContext>(0);
}

fs_grammarParser::OperandContext* fs_grammarParser::Imm_alu_instrContext::operand() {
  return getRuleContext<fs_grammarParser::OperandContext>(0);
}

fs_grammarParser::DestinationContext* fs_grammarParser::Imm_alu_instrContext::destination() {
  return getRuleContext<fs_grammarParser::DestinationContext>(0);
}

fs_grammarParser::ImmediateContext* fs_grammarParser::Imm_alu_instrContext::immediate() {
  return getRuleContext<fs_grammarParser::ImmediateContext>(0);
}

fs_grammarParser::Float_constContext* fs_grammarParser::Imm_alu_instrContext::float_const() {
  return getRuleContext<fs_grammarParser::Float_constContext>(0);
}


size_t fs_grammarParser::Imm_alu_instrContext::getRuleIndex() const {
  return fs_grammarParser::RuleImm_alu_instr;
}

void fs_grammarParser::Imm_alu_instrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImm_alu_instr(this);
}

void fs_grammarParser::Imm_alu_instrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImm_alu_instr(this);
}


antlrcpp::Any fs_grammarParser::Imm_alu_instrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitImm_alu_instr(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Imm_alu_instrContext* fs_grammarParser::imm_alu_instr() {
  Imm_alu_instrContext *_localctx = _tracker.createInstance<Imm_alu_instrContext>(_ctx, getState());
  enterRule(_localctx, 12, fs_grammarParser::RuleImm_alu_instr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    imm_alu_opcode();
    setState(97);
    operand();
    setState(98);
    match(fs_grammarParser::T__0);
    setState(101);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case fs_grammarParser::Identifier:
      case fs_grammarParser::Hexnum:
      case fs_grammarParser::Integer:
      case fs_grammarParser::Octalnum: {
        setState(99);
        immediate();
        break;
      }

      case fs_grammarParser::FloatingPointLiteral: {
        setState(100);
        float_const();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(103);
    match(fs_grammarParser::T__0);
    setState(104);
    destination();
   
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

fs_grammarParser::ImmediateContext* fs_grammarParser::Branch_instrContext::immediate() {
  return getRuleContext<fs_grammarParser::ImmediateContext>(0);
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

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    branch_opcode();
    setState(107);
    operand();
    setState(108);
    match(fs_grammarParser::T__0);
    setState(109);
    operand();
    setState(110);
    match(fs_grammarParser::T__0);
    setState(111);
    immediate();
   
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
  enterRule(_localctx, 16, fs_grammarParser::RuleIndep_instr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
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

//----------------- Pseudo_instrContext ------------------------------------------------------------------

fs_grammarParser::Pseudo_instrContext::Pseudo_instrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fs_grammarParser::Pseudo_opcodeContext* fs_grammarParser::Pseudo_instrContext::pseudo_opcode() {
  return getRuleContext<fs_grammarParser::Pseudo_opcodeContext>(0);
}

std::vector<tree::TerminalNode *> fs_grammarParser::Pseudo_instrContext::Identifier() {
  return getTokens(fs_grammarParser::Identifier);
}

tree::TerminalNode* fs_grammarParser::Pseudo_instrContext::Identifier(size_t i) {
  return getToken(fs_grammarParser::Identifier, i);
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
  enterRule(_localctx, 18, fs_grammarParser::RulePseudo_instr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    pseudo_opcode();
    setState(116);
    match(fs_grammarParser::Identifier);
    setState(117);
    match(fs_grammarParser::T__0);
    setState(118);
    match(fs_grammarParser::Identifier);
    setState(123);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == fs_grammarParser::T__0) {
      setState(119);
      match(fs_grammarParser::T__0);
      setState(120);
      match(fs_grammarParser::Identifier);
      setState(125);
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
  enterRule(_localctx, 20, fs_grammarParser::RuleOperand);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    match(fs_grammarParser::Identifier);
   
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
  enterRule(_localctx, 22, fs_grammarParser::RuleDestination);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(128);
    match(fs_grammarParser::Identifier);
   
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
  enterRule(_localctx, 24, fs_grammarParser::RuleImmediate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
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
  enterRule(_localctx, 26, fs_grammarParser::RuleFloat_const);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(132);
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
  enterRule(_localctx, 28, fs_grammarParser::RuleReg_opcode);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
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

//----------------- Imm_alu_opcodeContext ------------------------------------------------------------------

fs_grammarParser::Imm_alu_opcodeContext::Imm_alu_opcodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fs_grammarParser::Imm_alu_opcodeContext::getRuleIndex() const {
  return fs_grammarParser::RuleImm_alu_opcode;
}

void fs_grammarParser::Imm_alu_opcodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImm_alu_opcode(this);
}

void fs_grammarParser::Imm_alu_opcodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fs_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImm_alu_opcode(this);
}


antlrcpp::Any fs_grammarParser::Imm_alu_opcodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fs_grammarVisitor*>(visitor))
    return parserVisitor->visitImm_alu_opcode(this);
  else
    return visitor->visitChildren(this);
}

fs_grammarParser::Imm_alu_opcodeContext* fs_grammarParser::imm_alu_opcode() {
  Imm_alu_opcodeContext *_localctx = _tracker.createInstance<Imm_alu_opcodeContext>(_ctx, getState());
  enterRule(_localctx, 30, fs_grammarParser::RuleImm_alu_opcode);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(136);
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
      | (1ULL << fs_grammarParser::T__20))) != 0))) {
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
  enterRule(_localctx, 32, fs_grammarParser::RuleImm_opcode);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    match(fs_grammarParser::T__21);
   
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
  enterRule(_localctx, 34, fs_grammarParser::RuleBranch_opcode);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(140);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__22)
      | (1ULL << fs_grammarParser::T__23)
      | (1ULL << fs_grammarParser::T__24)
      | (1ULL << fs_grammarParser::T__25))) != 0))) {
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
  enterRule(_localctx, 36, fs_grammarParser::RulePseudo_opcode);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    match(fs_grammarParser::T__26);
   
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
  enterRule(_localctx, 38, fs_grammarParser::RuleFor_block);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
    match(fs_grammarParser::T__27);
    setState(145);
    for_decl();
    setState(146);
    match(fs_grammarParser::T__28);
    setState(147);
    for_end();
    setState(148);
    match(fs_grammarParser::T__28);
    setState(151);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(149);
      for_incr();
      break;
    }

    case 2: {
      setState(150);
      for_dec();
      break;
    }

    }
    setState(153);
    match(fs_grammarParser::T__29);
    setState(154);
    match(fs_grammarParser::T__30);
    setState(155);
    code();
    setState(156);
    match(fs_grammarParser::T__31);
   
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
  enterRule(_localctx, 40, fs_grammarParser::RuleFor_incr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158);
    match(fs_grammarParser::Identifier);

    setState(159);
    match(fs_grammarParser::T__32);
   
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
  enterRule(_localctx, 42, fs_grammarParser::RuleFor_dec);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    match(fs_grammarParser::Identifier);

    setState(162);
    match(fs_grammarParser::T__33);
   
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
  enterRule(_localctx, 44, fs_grammarParser::RuleFor_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(fs_grammarParser::Identifier);
    setState(165);
    match(fs_grammarParser::T__34);
    setState(166);
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
  enterRule(_localctx, 46, fs_grammarParser::RuleFor_end);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    match(fs_grammarParser::Identifier);
    setState(169);
    for_end_comp_type();
    setState(170);
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
  enterRule(_localctx, 48, fs_grammarParser::RuleFor_end_comp_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << fs_grammarParser::T__35)
      | (1ULL << fs_grammarParser::T__36)
      | (1ULL << fs_grammarParser::T__37)
      | (1ULL << fs_grammarParser::T__38))) != 0))) {
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
  enterRule(_localctx, 50, fs_grammarParser::RulePragma);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(174);
    match(fs_grammarParser::T__39);
    setState(175);
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
  enterRule(_localctx, 52, fs_grammarParser::RuleVariable_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    match(fs_grammarParser::T__40);
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

//----------------- Constant_declContext ------------------------------------------------------------------

fs_grammarParser::Constant_declContext::Constant_declContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
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
  enterRule(_localctx, 54, fs_grammarParser::RuleConstant_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    match(fs_grammarParser::T__41);
    setState(181);
    match(fs_grammarParser::Identifier);
   
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
  enterRule(_localctx, 56, fs_grammarParser::RuleInput_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    match(fs_grammarParser::T__42);
    setState(184);
    match(fs_grammarParser::Identifier);
   
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
  enterRule(_localctx, 58, fs_grammarParser::RuleOutput_decl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    match(fs_grammarParser::T__43);
    setState(187);
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
  "program", "code", "declaration", "instruction", "reg_instr", "imm_instr", 
  "imm_alu_instr", "branch_instr", "indep_instr", "pseudo_instr", "operand", 
  "destination", "immediate", "float_const", "reg_opcode", "imm_alu_opcode", 
  "imm_opcode", "branch_opcode", "pseudo_opcode", "for_block", "for_incr", 
  "for_dec", "for_decl", "for_end", "for_end_comp_type", "pragma", "variable_decl", 
  "constant_decl", "input_decl", "output_decl"
};

std::vector<std::string> fs_grammarParser::_literalNames = {
  "", "','", "'stop'", "'nop'", "'add'", "'sub'", "'mul'", "'mulsr'", "'mac'", 
  "'macsr'", "'shl'", "'shr'", "'sar'", "'addi'", "'subi'", "'muli'", "'mulsri'", 
  "'maci'", "'shli'", "'macsri'", "'shri'", "'sari'", "'ldr'", "'ble'", 
  "'bgt'", "'beq'", "'bne'", "'mov'", "'for('", "';'", "')'", "'{'", "'}'", 
  "'++'", "'--'", "'='", "'<'", "'>'", "'<='", "'>='", "'#pragma '", "'let'", 
  "'const'", "'input'", "'output'"
};

std::vector<std::string> fs_grammarParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "Identifier", "Hexnum", "Integer", 
  "Octalnum", "FloatingPointLiteral", "String", "Label", "WS", "BlockComment", 
  "LineComment"
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
    0x3, 0x38, 0xc0, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 
    0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 
    0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 
    0x9, 0x1f, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x6, 0x3, 0x45, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 0x46, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x4d, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x55, 0xa, 0x5, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x68, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x7, 0xb, 0x7c, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x7f, 0xb, 
    0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 
    0x9a, 0xa, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x2, 
    0x2, 0x20, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 
    0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x2, 0x8, 0x3, 0x2, 0x4, 0x5, 
    0x3, 0x2, 0x2f, 0x32, 0x3, 0x2, 0x6, 0xe, 0x3, 0x2, 0xf, 0x17, 0x3, 
    0x2, 0x19, 0x1c, 0x3, 0x2, 0x26, 0x29, 0x2, 0xb0, 0x2, 0x3e, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x44, 0x3, 0x2, 0x2, 0x2, 0x6, 0x4c, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x54, 0x3, 0x2, 0x2, 0x2, 0xa, 0x56, 0x3, 0x2, 0x2, 0x2, 0xc, 0x5d, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x62, 0x3, 0x2, 0x2, 0x2, 0x10, 0x6c, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x73, 0x3, 0x2, 0x2, 0x2, 0x14, 0x75, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x80, 0x3, 0x2, 0x2, 0x2, 0x18, 0x82, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x84, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x86, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x88, 0x3, 0x2, 0x2, 0x2, 0x20, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0x8c, 0x3, 0x2, 0x2, 0x2, 0x24, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x26, 0x90, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0x92, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xa0, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xa6, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0xaa, 0x3, 0x2, 0x2, 0x2, 0x32, 0xae, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0xb0, 0x3, 0x2, 0x2, 0x2, 0x36, 0xb3, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0xb6, 0x3, 0x2, 0x2, 0x2, 0x3a, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0xbc, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0x5, 0x4, 0x3, 0x2, 0x3f, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0x40, 0x45, 0x5, 0x8, 0x5, 0x2, 0x41, 0x45, 0x5, 
    0x28, 0x15, 0x2, 0x42, 0x45, 0x5, 0x34, 0x1b, 0x2, 0x43, 0x45, 0x5, 
    0x6, 0x4, 0x2, 0x44, 0x40, 0x3, 0x2, 0x2, 0x2, 0x44, 0x41, 0x3, 0x2, 
    0x2, 0x2, 0x44, 0x42, 0x3, 0x2, 0x2, 0x2, 0x44, 0x43, 0x3, 0x2, 0x2, 
    0x2, 0x45, 0x46, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0x5, 0x3, 0x2, 0x2, 0x2, 0x48, 
    0x4d, 0x5, 0x3a, 0x1e, 0x2, 0x49, 0x4d, 0x5, 0x36, 0x1c, 0x2, 0x4a, 
    0x4d, 0x5, 0x38, 0x1d, 0x2, 0x4b, 0x4d, 0x5, 0x3c, 0x1f, 0x2, 0x4c, 
    0x48, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4a, 
    0x3, 0x2, 0x2, 0x2, 0x4c, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x55, 0x5, 0xa, 0x6, 0x2, 0x4f, 0x55, 0x5, 0xc, 
    0x7, 0x2, 0x50, 0x55, 0x5, 0x12, 0xa, 0x2, 0x51, 0x55, 0x5, 0x14, 0xb, 
    0x2, 0x52, 0x55, 0x5, 0x10, 0x9, 0x2, 0x53, 0x55, 0x5, 0xe, 0x8, 0x2, 
    0x54, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x54, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x54, 
    0x50, 0x3, 0x2, 0x2, 0x2, 0x54, 0x51, 0x3, 0x2, 0x2, 0x2, 0x54, 0x52, 
    0x3, 0x2, 0x2, 0x2, 0x54, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x56, 0x57, 0x5, 0x1e, 0x10, 0x2, 0x57, 0x58, 0x5, 0x16, 
    0xc, 0x2, 0x58, 0x59, 0x7, 0x3, 0x2, 0x2, 0x59, 0x5a, 0x5, 0x16, 0xc, 
    0x2, 0x5a, 0x5b, 0x7, 0x3, 0x2, 0x2, 0x5b, 0x5c, 0x5, 0x18, 0xd, 0x2, 
    0x5c, 0xb, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x5, 0x22, 0x12, 0x2, 0x5e, 
    0x5f, 0x5, 0x18, 0xd, 0x2, 0x5f, 0x60, 0x7, 0x3, 0x2, 0x2, 0x60, 0x61, 
    0x5, 0x1a, 0xe, 0x2, 0x61, 0xd, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x5, 
    0x20, 0x11, 0x2, 0x63, 0x64, 0x5, 0x16, 0xc, 0x2, 0x64, 0x67, 0x7, 0x3, 
    0x2, 0x2, 0x65, 0x68, 0x5, 0x1a, 0xe, 0x2, 0x66, 0x68, 0x5, 0x1c, 0xf, 
    0x2, 0x67, 0x65, 0x3, 0x2, 0x2, 0x2, 0x67, 0x66, 0x3, 0x2, 0x2, 0x2, 
    0x68, 0x69, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x7, 0x3, 0x2, 0x2, 0x6a, 
    0x6b, 0x5, 0x18, 0xd, 0x2, 0x6b, 0xf, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 
    0x5, 0x24, 0x13, 0x2, 0x6d, 0x6e, 0x5, 0x16, 0xc, 0x2, 0x6e, 0x6f, 0x7, 
    0x3, 0x2, 0x2, 0x6f, 0x70, 0x5, 0x16, 0xc, 0x2, 0x70, 0x71, 0x7, 0x3, 
    0x2, 0x2, 0x71, 0x72, 0x5, 0x1a, 0xe, 0x2, 0x72, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0x73, 0x74, 0x9, 0x2, 0x2, 0x2, 0x74, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0x75, 0x76, 0x5, 0x26, 0x14, 0x2, 0x76, 0x77, 0x7, 0x2f, 0x2, 0x2, 0x77, 
    0x78, 0x7, 0x3, 0x2, 0x2, 0x78, 0x7d, 0x7, 0x2f, 0x2, 0x2, 0x79, 0x7a, 
    0x7, 0x3, 0x2, 0x2, 0x7a, 0x7c, 0x7, 0x2f, 0x2, 0x2, 0x7b, 0x79, 0x3, 
    0x2, 0x2, 0x2, 0x7c, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7b, 0x3, 0x2, 
    0x2, 0x2, 0x7d, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0x7f, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x80, 0x81, 0x7, 0x2f, 0x2, 0x2, 
    0x81, 0x17, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x7, 0x2f, 0x2, 0x2, 0x83, 
    0x19, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x9, 0x3, 0x2, 0x2, 0x85, 0x1b, 
    0x3, 0x2, 0x2, 0x2, 0x86, 0x87, 0x7, 0x33, 0x2, 0x2, 0x87, 0x1d, 0x3, 
    0x2, 0x2, 0x2, 0x88, 0x89, 0x9, 0x4, 0x2, 0x2, 0x89, 0x1f, 0x3, 0x2, 
    0x2, 0x2, 0x8a, 0x8b, 0x9, 0x5, 0x2, 0x2, 0x8b, 0x21, 0x3, 0x2, 0x2, 
    0x2, 0x8c, 0x8d, 0x7, 0x18, 0x2, 0x2, 0x8d, 0x23, 0x3, 0x2, 0x2, 0x2, 
    0x8e, 0x8f, 0x9, 0x6, 0x2, 0x2, 0x8f, 0x25, 0x3, 0x2, 0x2, 0x2, 0x90, 
    0x91, 0x7, 0x1d, 0x2, 0x2, 0x91, 0x27, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 
    0x7, 0x1e, 0x2, 0x2, 0x93, 0x94, 0x5, 0x2e, 0x18, 0x2, 0x94, 0x95, 0x7, 
    0x1f, 0x2, 0x2, 0x95, 0x96, 0x5, 0x30, 0x19, 0x2, 0x96, 0x99, 0x7, 0x1f, 
    0x2, 0x2, 0x97, 0x9a, 0x5, 0x2a, 0x16, 0x2, 0x98, 0x9a, 0x5, 0x2c, 0x17, 
    0x2, 0x99, 0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 0x98, 0x3, 0x2, 0x2, 0x2, 
    0x9a, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 0x7, 0x20, 0x2, 0x2, 0x9c, 
    0x9d, 0x7, 0x21, 0x2, 0x2, 0x9d, 0x9e, 0x5, 0x4, 0x3, 0x2, 0x9e, 0x9f, 
    0x7, 0x22, 0x2, 0x2, 0x9f, 0x29, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x7, 
    0x2f, 0x2, 0x2, 0xa1, 0xa2, 0x7, 0x23, 0x2, 0x2, 0xa2, 0x2b, 0x3, 0x2, 
    0x2, 0x2, 0xa3, 0xa4, 0x7, 0x2f, 0x2, 0x2, 0xa4, 0xa5, 0x7, 0x24, 0x2, 
    0x2, 0xa5, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x7, 0x2f, 0x2, 0x2, 
    0xa7, 0xa8, 0x7, 0x25, 0x2, 0x2, 0xa8, 0xa9, 0x7, 0x31, 0x2, 0x2, 0xa9, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0x7, 0x2f, 0x2, 0x2, 0xab, 0xac, 
    0x5, 0x32, 0x1a, 0x2, 0xac, 0xad, 0x7, 0x31, 0x2, 0x2, 0xad, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0xae, 0xaf, 0x9, 0x7, 0x2, 0x2, 0xaf, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0xb0, 0xb1, 0x7, 0x2a, 0x2, 0x2, 0xb1, 0xb2, 0x7, 0x2f, 0x2, 
    0x2, 0xb2, 0x35, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 0x7, 0x2b, 0x2, 0x2, 
    0xb4, 0xb5, 0x7, 0x2f, 0x2, 0x2, 0xb5, 0x37, 0x3, 0x2, 0x2, 0x2, 0xb6, 
    0xb7, 0x7, 0x2c, 0x2, 0x2, 0xb7, 0xb8, 0x7, 0x2f, 0x2, 0x2, 0xb8, 0x39, 
    0x3, 0x2, 0x2, 0x2, 0xb9, 0xba, 0x7, 0x2d, 0x2, 0x2, 0xba, 0xbb, 0x7, 
    0x2f, 0x2, 0x2, 0xbb, 0x3b, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x7, 0x2e, 
    0x2, 0x2, 0xbd, 0xbe, 0x7, 0x2f, 0x2, 0x2, 0xbe, 0x3d, 0x3, 0x2, 0x2, 
    0x2, 0x9, 0x44, 0x46, 0x4c, 0x54, 0x67, 0x7d, 0x99, 
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
