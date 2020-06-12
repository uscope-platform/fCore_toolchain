
// Generated from /home/fils/git/fCore_has/src/frontend/fs_grammar.g4 by ANTLR 4.8

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

  virtual void enterInstruction(fs_grammarParser::InstructionContext *ctx) = 0;
  virtual void exitInstruction(fs_grammarParser::InstructionContext *ctx) = 0;

  virtual void enterReg_instr(fs_grammarParser::Reg_instrContext *ctx) = 0;
  virtual void exitReg_instr(fs_grammarParser::Reg_instrContext *ctx) = 0;

  virtual void enterImm_instr(fs_grammarParser::Imm_instrContext *ctx) = 0;
  virtual void exitImm_instr(fs_grammarParser::Imm_instrContext *ctx) = 0;

  virtual void enterImm_alu_instr(fs_grammarParser::Imm_alu_instrContext *ctx) = 0;
  virtual void exitImm_alu_instr(fs_grammarParser::Imm_alu_instrContext *ctx) = 0;

  virtual void enterBranch_instr(fs_grammarParser::Branch_instrContext *ctx) = 0;
  virtual void exitBranch_instr(fs_grammarParser::Branch_instrContext *ctx) = 0;

  virtual void enterIndep_instr(fs_grammarParser::Indep_instrContext *ctx) = 0;
  virtual void exitIndep_instr(fs_grammarParser::Indep_instrContext *ctx) = 0;

  virtual void enterPseudo_instr(fs_grammarParser::Pseudo_instrContext *ctx) = 0;
  virtual void exitPseudo_instr(fs_grammarParser::Pseudo_instrContext *ctx) = 0;

  virtual void enterOperand(fs_grammarParser::OperandContext *ctx) = 0;
  virtual void exitOperand(fs_grammarParser::OperandContext *ctx) = 0;

  virtual void enterDestination(fs_grammarParser::DestinationContext *ctx) = 0;
  virtual void exitDestination(fs_grammarParser::DestinationContext *ctx) = 0;

  virtual void enterReg_opcode(fs_grammarParser::Reg_opcodeContext *ctx) = 0;
  virtual void exitReg_opcode(fs_grammarParser::Reg_opcodeContext *ctx) = 0;

  virtual void enterImm_alu_opcode(fs_grammarParser::Imm_alu_opcodeContext *ctx) = 0;
  virtual void exitImm_alu_opcode(fs_grammarParser::Imm_alu_opcodeContext *ctx) = 0;

  virtual void enterImm_opcode(fs_grammarParser::Imm_opcodeContext *ctx) = 0;
  virtual void exitImm_opcode(fs_grammarParser::Imm_opcodeContext *ctx) = 0;

  virtual void enterBranch_opcode(fs_grammarParser::Branch_opcodeContext *ctx) = 0;
  virtual void exitBranch_opcode(fs_grammarParser::Branch_opcodeContext *ctx) = 0;

  virtual void enterPseudo_opcode(fs_grammarParser::Pseudo_opcodeContext *ctx) = 0;
  virtual void exitPseudo_opcode(fs_grammarParser::Pseudo_opcodeContext *ctx) = 0;

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

  virtual void enterFor_end_comp_type(fs_grammarParser::For_end_comp_typeContext *ctx) = 0;
  virtual void exitFor_end_comp_type(fs_grammarParser::For_end_comp_typeContext *ctx) = 0;

  virtual void enterPragma(fs_grammarParser::PragmaContext *ctx) = 0;
  virtual void exitPragma(fs_grammarParser::PragmaContext *ctx) = 0;

  virtual void enterImmediate(fs_grammarParser::ImmediateContext *ctx) = 0;
  virtual void exitImmediate(fs_grammarParser::ImmediateContext *ctx) = 0;

  virtual void enterVariable_decl(fs_grammarParser::Variable_declContext *ctx) = 0;
  virtual void exitVariable_decl(fs_grammarParser::Variable_declContext *ctx) = 0;

  virtual void enterConstant_decl(fs_grammarParser::Constant_declContext *ctx) = 0;
  virtual void exitConstant_decl(fs_grammarParser::Constant_declContext *ctx) = 0;


};

}  // namespace fs_parser
