
// Generated from /home/fils/git/fCore_has/src/frontend/fs_grammar.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "fs_grammarVisitor.h"


namespace fs_parser {

/**
 * This class provides an empty implementation of fs_grammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  fs_grammarBaseVisitor : public fs_grammarVisitor {
public:

  virtual antlrcpp::Any visitProgram(fs_grammarParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCode(fs_grammarParser::CodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstruction(fs_grammarParser::InstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReg_instr(fs_grammarParser::Reg_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImm_instr(fs_grammarParser::Imm_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBranch_instr(fs_grammarParser::Branch_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIndep_instr(fs_grammarParser::Indep_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPseudo_instr(fs_grammarParser::Pseudo_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReg_opcode(fs_grammarParser::Reg_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImm_opcode(fs_grammarParser::Imm_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBranch_opcode(fs_grammarParser::Branch_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPseudo_opcode(fs_grammarParser::Pseudo_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFcore_reg(fs_grammarParser::Fcore_regContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor_block(fs_grammarParser::For_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor_incr(fs_grammarParser::For_incrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor_dec(fs_grammarParser::For_decContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor_decl(fs_grammarParser::For_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor_end(fs_grammarParser::For_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor_end_comp_type(fs_grammarParser::For_end_comp_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPragma(fs_grammarParser::PragmaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImmediate(fs_grammarParser::ImmediateContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace fs_parser
