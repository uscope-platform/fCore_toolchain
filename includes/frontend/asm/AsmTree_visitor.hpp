// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_ASMTREE_VISITOR_HPP
#define FCORE_TOOLCHAIN_ASMTREE_VISITOR_HPP

#include "asm_parser/asm_grammarBaseListener.h"
#include "asm_parser/asm_grammarParser.h"
#include "fCore_isa.hpp"
#include "data_structures/low_level_ast/ll_instruction_node.hpp"
#include "data_structures/low_level_ast/ll_ast_pragma.hpp"
#include "data_structures/low_level_ast/ll_ast_node.hpp"
#include "data_structures/low_level_ast/ll_loop_node.hpp"
#include "tools/variable.hpp"
#include "tools/variable_map.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>


typedef std::unordered_map<std::string, std::shared_ptr<variable>>  varmap_t;

class AsmTree_visitor : public  asm_parser::asm_grammarBaseListener{
public:
    explicit AsmTree_visitor(std::shared_ptr<variable_map> map);
    void exitImm_instr(asm_parser::asm_grammarParser::Imm_instrContext * ctx) override;
    void exitReg_instr(asm_parser::asm_grammarParser::Reg_instrContext * ctx) override;
    void exitPseudo_instr(asm_parser::asm_grammarParser::Pseudo_instrContext *ctx) override;
    void exitIndep_instr(asm_parser::asm_grammarParser::Indep_instrContext * ctx) override;
    void exitBranch_instr(asm_parser::asm_grammarParser::Branch_instrContext * ctx) override;
    void exitConv_instr(asm_parser::asm_grammarParser::Conv_instrContext *ctx) override;
    void exitLoad_instr(asm_parser::asm_grammarParser::Load_instrContext *ctx) override;
    void enterFor_block(asm_parser::asm_grammarParser::For_blockContext * ctx) override;
    void exitFor_block(asm_parser::asm_grammarParser::For_blockContext * ctx) override;
    void exitProgram(asm_parser::asm_grammarParser::ProgramContext * ctx) override;
    void enterProgram(asm_parser::asm_grammarParser::ProgramContext *ctx) override;
    void exitPragma(asm_parser::asm_grammarParser::PragmaContext *ctx) override;
    void exitConstant_decl(asm_parser::asm_grammarParser::Constant_declContext *ctx) override;
    void exitVariable_decl(asm_parser::asm_grammarParser::Variable_declContext *ctx) override;
    void exitInput_decl(asm_parser::asm_grammarParser::Input_declContext *ctx) override;
    void exitOutput_decl(asm_parser::asm_grammarParser::Output_declContext *ctx) override;
    void exitImmediate(asm_parser::asm_grammarParser::ImmediateContext *ctx) override;
    void exitFloat_const(asm_parser::asm_grammarParser::Float_constContext *ctx) override;
    std::shared_ptr<ll_ast_node> get_program();

private:
    std::shared_ptr<ll_ast_node> program_head{};
    std::shared_ptr<ll_ast_node> current_element{};
    std::stack<std::shared_ptr<ll_ast_node>> parent_elements;
    std::shared_ptr<variable_map> varmap;

    std::shared_ptr<variable> get_variable(const std::string &variable_name, bool is_const) const;
};

#endif //FCORE_TOOLCHAIN_ASMTREE_VISITOR_HPP
