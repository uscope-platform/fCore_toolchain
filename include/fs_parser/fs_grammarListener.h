
// Generated from /home/fils/git/fCore_has/src/fs_grammar.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "fs_grammarParser.h"


namespace fs_parser {

/**
 * This interface defines an abstract listener for a parse tree produced by fs_grammarParser.
 */
class  fs_grammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(fs_grammarParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(fs_grammarParser::ProgramContext *ctx) = 0;

  virtual void enterCode(fs_grammarParser::CodeContext *ctx) = 0;
  virtual void exitCode(fs_grammarParser::CodeContext *ctx) = 0;

  virtual void enterReg_instr(fs_grammarParser::Reg_instrContext *ctx) = 0;
  virtual void exitReg_instr(fs_grammarParser::Reg_instrContext *ctx) = 0;

  virtual void enterImm_instr(fs_grammarParser::Imm_instrContext *ctx) = 0;
  virtual void exitImm_instr(fs_grammarParser::Imm_instrContext *ctx) = 0;

  virtual void enterIndep_instr(fs_grammarParser::Indep_instrContext *ctx) = 0;
  virtual void exitIndep_instr(fs_grammarParser::Indep_instrContext *ctx) = 0;

  virtual void enterReg_opcode(fs_grammarParser::Reg_opcodeContext *ctx) = 0;
  virtual void exitReg_opcode(fs_grammarParser::Reg_opcodeContext *ctx) = 0;

  virtual void enterImm_opcode(fs_grammarParser::Imm_opcodeContext *ctx) = 0;
  virtual void exitImm_opcode(fs_grammarParser::Imm_opcodeContext *ctx) = 0;

  virtual void enterFcore_reg(fs_grammarParser::Fcore_regContext *ctx) = 0;
  virtual void exitFcore_reg(fs_grammarParser::Fcore_regContext *ctx) = 0;

  virtual void enterFor_block(fs_grammarParser::For_blockContext *ctx) = 0;
  virtual void exitFor_block(fs_grammarParser::For_blockContext *ctx) = 0;

  virtual void enterFor_incr(fs_grammarParser::For_incrContext *ctx) = 0;
  virtual void exitFor_incr(fs_grammarParser::For_incrContext *ctx) = 0;

  virtual void enterFor_dec(fs_grammarParser::For_decContext *ctx) = 0;
  virtual void exitFor_dec(fs_grammarParser::For_decContext *ctx) = 0;

  virtual void enterFor_decl(fs_grammarParser::For_declContext *ctx) = 0;
  virtual void exitFor_decl(fs_grammarParser::For_declContext *ctx) = 0;

  virtual void enterFor_end(fs_grammarParser::For_endContext *ctx) = 0;
  virtual void exitFor_end(fs_grammarParser::For_endContext *ctx) = 0;


};

}  // namespace fs_parser
