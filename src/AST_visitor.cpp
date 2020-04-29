//
// Created by fils on 29/04/20.
//

#include "AST_visitor.hpp"

void AST_visitor::exitImm_instr(fs_grammarParser::Imm_instrContext * ctx) {


    std::string opcode = ctx->imm_opcode()->getText();
    std::string imm_str = ctx->Integer()->getText();
    std::string dest = ctx->fcore_reg()->getText();
    uint16_t immediate =  std::stoi(imm_str,nullptr, 0);
    std::shared_ptr<instruction> instr = std::make_unique<immediate_instruction>(fcore_opcodes[opcode],fcore_registers[dest], immediate);
    program.push_back(instr);
}

std::vector<std::shared_ptr<instruction>> AST_visitor::get_program() {
    return program;
}

void AST_visitor::exitReg_instr(fs_grammarParser::Reg_instrContext *ctx) {

    std::string opcode = ctx->reg_opcode()->getText();
    std::vector<fs_grammarParser::Fcore_regContext*> ops = ctx->fcore_reg();
    std::string op_a = ops[0]->getText();
    std::string op_b = ops[1]->getText();
    std::string dest = ops[2]->getText();
    std::shared_ptr<instruction> instr = std::make_unique<register_operating_instruction>(fcore_opcodes[opcode],fcore_registers[op_a],fcore_registers[op_b],fcore_registers[dest]);
    program.push_back(instr);
}

void AST_visitor::exitIndep_instr(fs_grammarParser::Indep_instrContext *ctx) {
    std::string opcode = ctx->getText();
    std::shared_ptr<instruction> instr = std::make_unique<independent_instruction>(fcore_opcodes[opcode]);
    program.push_back(instr);
}
