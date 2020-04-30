
// Generated from /home/fils/git/fCore_has/src/fs_grammar.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "fs_grammarListener.h"


namespace fs_parser {

/**
 * This class provides an empty implementation of fs_grammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  fs_grammarBaseListener : public fs_grammarListener {
public:

  virtual void enterProgram(fs_grammarParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(fs_grammarParser::ProgramContext * /*ctx*/) override { }

  virtual void enterCode(fs_grammarParser::CodeContext * /*ctx*/) override { }
  virtual void exitCode(fs_grammarParser::CodeContext * /*ctx*/) override { }

  virtual void enterReg_instr(fs_grammarParser::Reg_instrContext * /*ctx*/) override { }
  virtual void exitReg_instr(fs_grammarParser::Reg_instrContext * /*ctx*/) override { }

  virtual void enterImm_instr(fs_grammarParser::Imm_instrContext * /*ctx*/) override { }
  virtual void exitImm_instr(fs_grammarParser::Imm_instrContext * /*ctx*/) override { }

  virtual void enterIndep_instr(fs_grammarParser::Indep_instrContext * /*ctx*/) override { }
  virtual void exitIndep_instr(fs_grammarParser::Indep_instrContext * /*ctx*/) override { }

  virtual void enterReg_opcode(fs_grammarParser::Reg_opcodeContext * /*ctx*/) override { }
  virtual void exitReg_opcode(fs_grammarParser::Reg_opcodeContext * /*ctx*/) override { }

  virtual void enterImm_opcode(fs_grammarParser::Imm_opcodeContext * /*ctx*/) override { }
  virtual void exitImm_opcode(fs_grammarParser::Imm_opcodeContext * /*ctx*/) override { }

  virtual void enterFcore_reg(fs_grammarParser::Fcore_regContext * /*ctx*/) override { }
  virtual void exitFcore_reg(fs_grammarParser::Fcore_regContext * /*ctx*/) override { }

  virtual void enterFor_block(fs_grammarParser::For_blockContext * /*ctx*/) override { }
  virtual void exitFor_block(fs_grammarParser::For_blockContext * /*ctx*/) override { }

  virtual void enterFor_incr(fs_grammarParser::For_incrContext * /*ctx*/) override { }
  virtual void exitFor_incr(fs_grammarParser::For_incrContext * /*ctx*/) override { }

  virtual void enterFor_dec(fs_grammarParser::For_decContext * /*ctx*/) override { }
  virtual void exitFor_dec(fs_grammarParser::For_decContext * /*ctx*/) override { }

  virtual void enterFor_decl(fs_grammarParser::For_declContext * /*ctx*/) override { }
  virtual void exitFor_decl(fs_grammarParser::For_declContext * /*ctx*/) override { }

  virtual void enterFor_end(fs_grammarParser::For_endContext * /*ctx*/) override { }
  virtual void exitFor_end(fs_grammarParser::For_endContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace fs_parser
