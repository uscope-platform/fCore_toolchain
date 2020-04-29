//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_AST_VISITOR_HPP
#define FCORE_HAS_AST_VISITOR_HPP

#include "../include/fs_parser/fs_grammarBaseListener.h"
#include "../include/fCore_isa.hpp"
#include "instruction.h"
#include "immediate_instruction.h"
#include "register_operating_instruction.h"
#include "independent_instruction.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace fs_parser;

class AST_visitor : public  fs_grammarBaseListener{
public:
    void exitImm_instr(fs_grammarParser::Imm_instrContext * ctx) override;
    void exitReg_instr(fs_grammarParser::Reg_instrContext * ctx) override;
    void exitIndep_instr(fs_grammarParser::Indep_instrContext * ctx) override;
    std::vector<std::shared_ptr<instruction>> get_program();
private:
    std::vector<std::shared_ptr<instruction>> program;
};

#endif //FCORE_HAS_AST_VISITOR_HPP
