
// Generated from /home/fils/git/fCore_has/src/fs_grammar.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime/antlr4-runtime.h"
#include "fs_grammarVisitor.h"


namespace fs_parser {

/**
 * This class provides an empty implementation of fs_grammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  fs_grammarBaseVisitor : public fs_grammarVisitor {
public:

  virtual antlrcpp::Any visitCode(fs_grammarParser::CodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReg_instr(fs_grammarParser::Reg_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImm_instr(fs_grammarParser::Imm_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIndep_instr(fs_grammarParser::Indep_instrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReg_opcode(fs_grammarParser::Reg_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImm_opcode(fs_grammarParser::Imm_opcodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFcore_reg(fs_grammarParser::Fcore_regContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace fs_parser
