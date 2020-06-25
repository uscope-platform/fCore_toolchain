
// Generated from /home/fils/git/fCore_has/src/frontend/fs_grammar.g4 by ANTLR 4.8

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

    virtual antlrcpp::Any visitDeclaration(fs_grammarParser::DeclarationContext *context) = 0;

    virtual antlrcpp::Any visitInstruction(fs_grammarParser::InstructionContext *context) = 0;

    virtual antlrcpp::Any visitReg_instr(fs_grammarParser::Reg_instrContext *context) = 0;

    virtual antlrcpp::Any visitImm_instr(fs_grammarParser::Imm_instrContext *context) = 0;

    virtual antlrcpp::Any visitBranch_instr(fs_grammarParser::Branch_instrContext *context) = 0;

    virtual antlrcpp::Any visitConv_instr(fs_grammarParser::Conv_instrContext *context) = 0;

    virtual antlrcpp::Any visitIndep_instr(fs_grammarParser::Indep_instrContext *context) = 0;

    virtual antlrcpp::Any visitPseudo_instr(fs_grammarParser::Pseudo_instrContext *context) = 0;

    virtual antlrcpp::Any visitOperand(fs_grammarParser::OperandContext *context) = 0;

    virtual antlrcpp::Any visitDestination(fs_grammarParser::DestinationContext *context) = 0;

    virtual antlrcpp::Any visitImmediate(fs_grammarParser::ImmediateContext *context) = 0;

    virtual antlrcpp::Any visitFloat_const(fs_grammarParser::Float_constContext *context) = 0;

    virtual antlrcpp::Any visitReg_opcode(fs_grammarParser::Reg_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitConv_opcode(fs_grammarParser::Conv_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitImm_opcode(fs_grammarParser::Imm_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitBranch_opcode(fs_grammarParser::Branch_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitPseudo_opcode(fs_grammarParser::Pseudo_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitFor_block(fs_grammarParser::For_blockContext *context) = 0;

    virtual antlrcpp::Any visitFor_incr(fs_grammarParser::For_incrContext *context) = 0;

    virtual antlrcpp::Any visitFor_dec(fs_grammarParser::For_decContext *context) = 0;

    virtual antlrcpp::Any visitFor_decl(fs_grammarParser::For_declContext *context) = 0;

    virtual antlrcpp::Any visitFor_end(fs_grammarParser::For_endContext *context) = 0;

    virtual antlrcpp::Any visitFor_end_comp_type(fs_grammarParser::For_end_comp_typeContext *context) = 0;

    virtual antlrcpp::Any visitPragma(fs_grammarParser::PragmaContext *context) = 0;

    virtual antlrcpp::Any visitVariable_decl(fs_grammarParser::Variable_declContext *context) = 0;

    virtual antlrcpp::Any visitConstant_decl(fs_grammarParser::Constant_declContext *context) = 0;

    virtual antlrcpp::Any visitInput_decl(fs_grammarParser::Input_declContext *context) = 0;

    virtual antlrcpp::Any visitOutput_decl(fs_grammarParser::Output_declContext *context) = 0;


};

}  // namespace fs_parser
