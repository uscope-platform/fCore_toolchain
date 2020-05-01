//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_TREE_VISITOR_HPP
#define FCORE_HAS_TREE_VISITOR_HPP

#include "../../include/fs_parser/fs_grammarBaseListener.h"
#include "../../include/fCore_isa.hpp"
#include "../code_elements/instruction.h"
#include "../code_elements/immediate_instruction.h"
#include "../code_elements/register_operating_instruction.h"
#include "../code_elements/independent_instruction.hpp"
#include "../code_elements/for_loop.hpp"
#include "../code_elements/code_element.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace fs_parser;

class Tree_visitor : public  fs_grammarBaseListener{
public:
    Tree_visitor();
    void exitImm_instr(fs_grammarParser::Imm_instrContext * ctx) override;
    void exitReg_instr(fs_grammarParser::Reg_instrContext * ctx) override;
    void exitIndep_instr(fs_grammarParser::Indep_instrContext * ctx) override;
    void enterFor_block(fs_grammarParser::For_blockContext * ctx) override;
    void exitFor_block(fs_grammarParser::For_blockContext * ctx) override;
    void exitProgram(fs_grammarParser::ProgramContext * ctx) override;
    void enterProgram(fs_grammarParser::ProgramContext *ctx) override;
    void exitPragma(fs_grammarParser::PragmaContext *ctx) override;
    std::shared_ptr<code_element> get_program() ;
private:
    std::shared_ptr<code_element> program_head;
    std::shared_ptr<code_element> current_element;
};

#endif //FCORE_HAS_TREE_VISITOR_HPP
