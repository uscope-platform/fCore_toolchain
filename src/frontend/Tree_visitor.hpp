//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_TREE_VISITOR_HPP
#define FCORE_HAS_TREE_VISITOR_HPP

#include "../../include/fs_parser/fs_grammarBaseListener.h"
#include "../../include/fs_parser/fs_grammarParser.h"
#include "../../include/fCore_isa.hpp"
#include "../code_elements/instruction.h"
#include "../code_elements/for_loop.hpp"
#include "../code_elements/code_element.hpp"
#include "../code_elements/variable.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace fs_parser;

typedef std::unordered_map<std::string, std::shared_ptr<variable>>  varmap_t;

class Tree_visitor : public  fs_grammarBaseListener{
public:
    Tree_visitor();
    void exitImm_instr(fs_grammarParser::Imm_instrContext * ctx) override;
    void exitReg_instr(fs_grammarParser::Reg_instrContext * ctx) override;
    void exitImm_alu_instr(fs_grammarParser::Imm_alu_instrContext *ctx) override;
    void exitPseudo_instr(fs_grammarParser::Pseudo_instrContext *ctx) override;
    void exitIndep_instr(fs_grammarParser::Indep_instrContext * ctx) override;
    void exitBranch_instr(fs_grammarParser::Branch_instrContext * ctx) override;
    void enterFor_block(fs_grammarParser::For_blockContext * ctx) override;
    void exitFor_block(fs_grammarParser::For_blockContext * ctx) override;
    void exitProgram(fs_grammarParser::ProgramContext * ctx) override;
    void enterProgram(fs_grammarParser::ProgramContext *ctx) override;
    void exitPragma(fs_grammarParser::PragmaContext *ctx) override;
    void exitConstant_decl(fs_grammarParser::Constant_declContext *ctx) override;
    void exitVariable_decl(fs_grammarParser::Variable_declContext *ctx) override;
    ast_t get_program();
    varmap_t get_varmap();
    void set_varmap(varmap_t &new_varmap);
private:
    ast_t program_head{};
    ast_t current_element{};
    std::stack<ast_t> parent_elements;
    varmap_t *var_map;

    std::shared_ptr<variable> get_variable(const std::string &variable_name, bool is_const) const;
};

#endif //FCORE_HAS_TREE_VISITOR_HPP
