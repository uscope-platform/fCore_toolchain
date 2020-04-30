
// Generated from /home/fils/git/fCore_has/src/fs_grammar.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "fs_grammarParser.h"


namespace fs_parser {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by fs_grammarParser.
 */
class  fs_grammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by fs_grammarParser.
   */
    virtual antlrcpp::Any visitProgram(fs_grammarParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitCode(fs_grammarParser::CodeContext *context) = 0;

    virtual antlrcpp::Any visitReg_instr(fs_grammarParser::Reg_instrContext *context) = 0;

    virtual antlrcpp::Any visitImm_instr(fs_grammarParser::Imm_instrContext *context) = 0;

    virtual antlrcpp::Any visitIndep_instr(fs_grammarParser::Indep_instrContext *context) = 0;

    virtual antlrcpp::Any visitReg_opcode(fs_grammarParser::Reg_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitImm_opcode(fs_grammarParser::Imm_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitFcore_reg(fs_grammarParser::Fcore_regContext *context) = 0;

    virtual antlrcpp::Any visitFor_block(fs_grammarParser::For_blockContext *context) = 0;

    virtual antlrcpp::Any visitFor_incr(fs_grammarParser::For_incrContext *context) = 0;

    virtual antlrcpp::Any visitFor_dec(fs_grammarParser::For_decContext *context) = 0;

    virtual antlrcpp::Any visitFor_decl(fs_grammarParser::For_declContext *context) = 0;

    virtual antlrcpp::Any visitFor_end(fs_grammarParser::For_endContext *context) = 0;


};

}  // namespace fs_parser
