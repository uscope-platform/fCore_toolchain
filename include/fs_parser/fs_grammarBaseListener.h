
// Generated from /home/fils/git/fCore_has/src/frontend/fs_grammar.g4 by ANTLR 4.8

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

  virtual void enterDeclaration(fs_grammarParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(fs_grammarParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterInstruction(fs_grammarParser::InstructionContext * /*ctx*/) override { }
  virtual void exitInstruction(fs_grammarParser::InstructionContext * /*ctx*/) override { }

  virtual void enterReg_instr(fs_grammarParser::Reg_instrContext * /*ctx*/) override { }
  virtual void exitReg_instr(fs_grammarParser::Reg_instrContext * /*ctx*/) override { }

  virtual void enterImm_instr(fs_grammarParser::Imm_instrContext * /*ctx*/) override { }
  virtual void exitImm_instr(fs_grammarParser::Imm_instrContext * /*ctx*/) override { }

  virtual void enterImm_alu_instr(fs_grammarParser::Imm_alu_instrContext * /*ctx*/) override { }
  virtual void exitImm_alu_instr(fs_grammarParser::Imm_alu_instrContext * /*ctx*/) override { }

  virtual void enterBranch_instr(fs_grammarParser::Branch_instrContext * /*ctx*/) override { }
  virtual void exitBranch_instr(fs_grammarParser::Branch_instrContext * /*ctx*/) override { }

  virtual void enterIndep_instr(fs_grammarParser::Indep_instrContext * /*ctx*/) override { }
  virtual void exitIndep_instr(fs_grammarParser::Indep_instrContext * /*ctx*/) override { }

  virtual void enterPseudo_instr(fs_grammarParser::Pseudo_instrContext * /*ctx*/) override { }
  virtual void exitPseudo_instr(fs_grammarParser::Pseudo_instrContext * /*ctx*/) override { }

  virtual void enterOperand(fs_grammarParser::OperandContext * /*ctx*/) override { }
  virtual void exitOperand(fs_grammarParser::OperandContext * /*ctx*/) override { }

  virtual void enterDestination(fs_grammarParser::DestinationContext * /*ctx*/) override { }
  virtual void exitDestination(fs_grammarParser::DestinationContext * /*ctx*/) override { }

  virtual void enterReg_opcode(fs_grammarParser::Reg_opcodeContext * /*ctx*/) override { }
  virtual void exitReg_opcode(fs_grammarParser::Reg_opcodeContext * /*ctx*/) override { }

  virtual void enterImm_alu_opcode(fs_grammarParser::Imm_alu_opcodeContext * /*ctx*/) override { }
  virtual void exitImm_alu_opcode(fs_grammarParser::Imm_alu_opcodeContext * /*ctx*/) override { }

  virtual void enterImm_opcode(fs_grammarParser::Imm_opcodeContext * /*ctx*/) override { }
  virtual void exitImm_opcode(fs_grammarParser::Imm_opcodeContext * /*ctx*/) override { }

  virtual void enterBranch_opcode(fs_grammarParser::Branch_opcodeContext * /*ctx*/) override { }
  virtual void exitBranch_opcode(fs_grammarParser::Branch_opcodeContext * /*ctx*/) override { }

  virtual void enterPseudo_opcode(fs_grammarParser::Pseudo_opcodeContext * /*ctx*/) override { }
  virtual void exitPseudo_opcode(fs_grammarParser::Pseudo_opcodeContext * /*ctx*/) override { }

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

  virtual void enterFor_end_comp_type(fs_grammarParser::For_end_comp_typeContext * /*ctx*/) override { }
  virtual void exitFor_end_comp_type(fs_grammarParser::For_end_comp_typeContext * /*ctx*/) override { }

  virtual void enterPragma(fs_grammarParser::PragmaContext * /*ctx*/) override { }
  virtual void exitPragma(fs_grammarParser::PragmaContext * /*ctx*/) override { }

  virtual void enterImmediate(fs_grammarParser::ImmediateContext * /*ctx*/) override { }
  virtual void exitImmediate(fs_grammarParser::ImmediateContext * /*ctx*/) override { }

  virtual void enterVariable_decl(fs_grammarParser::Variable_declContext * /*ctx*/) override { }
  virtual void exitVariable_decl(fs_grammarParser::Variable_declContext * /*ctx*/) override { }

  virtual void enterConstant_decl(fs_grammarParser::Constant_declContext * /*ctx*/) override { }
  virtual void exitConstant_decl(fs_grammarParser::Constant_declContext * /*ctx*/) override { }

  virtual void enterInput_decl(fs_grammarParser::Input_declContext * /*ctx*/) override { }
  virtual void exitInput_decl(fs_grammarParser::Input_declContext * /*ctx*/) override { }

  virtual void enterOutput_decl(fs_grammarParser::Output_declContext * /*ctx*/) override { }
  virtual void exitOutput_decl(fs_grammarParser::Output_declContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace fs_parser
