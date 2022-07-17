
// Generated from /home/fils/git/fCore_toolchain/src/frontend/asm_grammar.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "asm_grammarParser.h"


namespace asm_parser {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by asm_grammarParser.
 */
class  asm_grammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by asm_grammarParser.
   */
    virtual antlrcpp::Any visitProgram(asm_grammarParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitCode(asm_grammarParser::CodeContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration(asm_grammarParser::DeclarationContext *context) = 0;

    virtual antlrcpp::Any visitInstruction(asm_grammarParser::InstructionContext *context) = 0;

    virtual antlrcpp::Any visitReg_instr(asm_grammarParser::Reg_instrContext *context) = 0;

    virtual antlrcpp::Any visitImm_instr(asm_grammarParser::Imm_instrContext *context) = 0;

    virtual antlrcpp::Any visitLoad_instr(asm_grammarParser::Load_instrContext *context) = 0;

    virtual antlrcpp::Any visitBranch_instr(asm_grammarParser::Branch_instrContext *context) = 0;

    virtual antlrcpp::Any visitConv_instr(asm_grammarParser::Conv_instrContext *context) = 0;

    virtual antlrcpp::Any visitIndep_instr(asm_grammarParser::Indep_instrContext *context) = 0;

    virtual antlrcpp::Any visitPseudo_instr(asm_grammarParser::Pseudo_instrContext *context) = 0;

    virtual antlrcpp::Any visitOperand(asm_grammarParser::OperandContext *context) = 0;

    virtual antlrcpp::Any visitDestination(asm_grammarParser::DestinationContext *context) = 0;

    virtual antlrcpp::Any visitImmediate(asm_grammarParser::ImmediateContext *context) = 0;

    virtual antlrcpp::Any visitFloat_const(asm_grammarParser::Float_constContext *context) = 0;

    virtual antlrcpp::Any visitReg_opcode(asm_grammarParser::Reg_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitConv_opcode(asm_grammarParser::Conv_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitImm_opcode(asm_grammarParser::Imm_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitBranch_opcode(asm_grammarParser::Branch_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitPseudo_opcode(asm_grammarParser::Pseudo_opcodeContext *context) = 0;

    virtual antlrcpp::Any visitFor_block(asm_grammarParser::For_blockContext *context) = 0;

    virtual antlrcpp::Any visitFor_incr(asm_grammarParser::For_incrContext *context) = 0;

    virtual antlrcpp::Any visitFor_dec(asm_grammarParser::For_decContext *context) = 0;

    virtual antlrcpp::Any visitFor_decl(asm_grammarParser::For_declContext *context) = 0;

    virtual antlrcpp::Any visitFor_end(asm_grammarParser::For_endContext *context) = 0;

    virtual antlrcpp::Any visitFor_end_comp_type(asm_grammarParser::For_end_comp_typeContext *context) = 0;

    virtual antlrcpp::Any visitPragma(asm_grammarParser::PragmaContext *context) = 0;

    virtual antlrcpp::Any visitVariable_decl(asm_grammarParser::Variable_declContext *context) = 0;

    virtual antlrcpp::Any visitConstant_decl(asm_grammarParser::Constant_declContext *context) = 0;

    virtual antlrcpp::Any visitInput_decl(asm_grammarParser::Input_declContext *context) = 0;

    virtual antlrcpp::Any visitOutput_decl(asm_grammarParser::Output_declContext *context) = 0;


};

}  // namespace asm_parser
