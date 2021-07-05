// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#include "frontend/asm/AsmTree_visitor.hpp"

#include <utility>





AsmTree_visitor::AsmTree_visitor(std::shared_ptr<variable_map> map) {
    varmap = std::move(map);
}


void AsmTree_visitor::exitImm_instr(asm_parser::asm_grammarParser::Imm_instrContext * ctx) {
    std::string opcode = ctx->imm_opcode()->getText();



    std::string dest_str;
    if(ctx->destination()->Identifier() != nullptr)
        dest_str = ctx->destination()->Identifier()->getText();
    else if (ctx->destination()->Register() != nullptr)
        dest_str = ctx->destination()->Register()->getText();

    std::shared_ptr<variable> dest = get_variable(dest_str, false);
    std::shared_ptr<variable> immediate = get_variable(ctx->immediate()->getText(), true);

    std::vector<std::shared_ptr<variable>> arguments;
    arguments.push_back(dest);
    arguments.push_back(immediate);

    ll_ast_node this_inst = ll_ast_node(ll_type_instr, ll_instruction(IMMEDIATE_INSTRUCTION, opcode, arguments));
    current_element->add_content(std::make_shared<ll_ast_node>(this_inst));
}



void AsmTree_visitor::exitReg_instr(asm_parser::asm_grammarParser::Reg_instrContext *ctx) {
    std::string opcode = ctx->reg_opcode()->getText();

    std::string op_a_str;
    if(ctx->operand(0)->Identifier() != nullptr)
        op_a_str = ctx->operand(0)->Identifier()->getText();
    else if (ctx->operand(0)->Register() != nullptr)
        op_a_str = ctx->operand(0)->Register()->getText();

    std::string op_b_str;
    if(ctx->operand(1)->Identifier() != nullptr)
        op_b_str = ctx->operand(1)->Identifier()->getText();
    else if (ctx->operand(1)->Register() != nullptr)
        op_b_str = ctx->operand(1)->Register()->getText();

    std::string dest_str;
    if(ctx->destination()->Identifier() != nullptr)
        dest_str = ctx->destination()->Identifier()->getText();
    else if (ctx->destination()->Register() != nullptr)
        dest_str = ctx->destination()->Register()->getText();

    std::shared_ptr<variable> op_a = get_variable(op_a_str, false);
    op_a->set_used(true);
    std::shared_ptr<variable> op_b = get_variable(op_b_str, false);
    op_b->set_used(true);
    std::shared_ptr<variable> dest = get_variable(dest_str, false);

    std::vector<std::shared_ptr<variable>> arguments = {op_a, op_b, dest};

    ll_ast_node this_inst = ll_ast_node(ll_type_instr, ll_instruction(REGISTER_INSTRUCTION, opcode, arguments));
    current_element->add_content(std::make_shared<ll_ast_node>(this_inst));
}

void AsmTree_visitor::exitConv_instr(asm_parser::asm_grammarParser::Conv_instrContext *ctx) {
    std::string opcode = ctx->conv_opcode()->getText();

    std::shared_ptr<variable> op_a = get_variable(ctx->operand(0)->getText(), false);
    op_a->set_used(true);
    std::shared_ptr<variable> op_b = get_variable(ctx->operand(1)->getText(), false);

    std::vector<std::shared_ptr<variable>> arguments = {op_a, op_b};

    ll_ast_node this_inst = ll_ast_node(ll_type_instr, ll_instruction(CONVERSION_INSTRUCTION, opcode, arguments));
    current_element->add_content(std::make_shared<ll_ast_node>(this_inst));
}

void AsmTree_visitor::exitBranch_instr(asm_parser::asm_grammarParser::Branch_instrContext *ctx) {
    std::string opcode = ctx->branch_opcode()->getText();

    std::shared_ptr<variable> op_a = get_variable(ctx->operand(0)->getText(), false);
    op_a->set_used(true);
    std::shared_ptr<variable> op_b = get_variable(ctx->operand(1)->getText(), false);
    op_b->set_used(true);
    std::shared_ptr<variable> dest = get_variable(ctx->operand(2)->getText(), false);

    std::vector<std::shared_ptr<variable>> arguments = {op_a, op_b, dest};

    ll_ast_node this_inst = ll_ast_node(ll_type_instr, ll_instruction(REGISTER_INSTRUCTION, opcode, arguments));
    current_element->add_content(std::make_shared<ll_ast_node>(this_inst));
}

void AsmTree_visitor::exitPseudo_instr(asm_parser::asm_grammarParser::Pseudo_instrContext *ctx) {
    std::string opcode = ctx->pseudo_opcode()->getText();

    std::string op_a_str;
    if(ctx->operand(0)->Identifier() != nullptr)
        op_a_str = ctx->operand(0)->Identifier()->getText();
    else if (ctx->operand(0)->Register() != nullptr)
        op_a_str = ctx->operand(0)->Register()->getText();

    std::string op_b_str;
    if(ctx->operand(1)->Identifier() != nullptr)
        op_b_str = ctx->operand(1)->Identifier()->getText();
    else if (ctx->operand(1)->Register() != nullptr)
        op_b_str = ctx->operand(1)->Register()->getText();



    std::shared_ptr<variable> op_a = get_variable(op_a_str, false);
    op_a->set_used(true);
    std::shared_ptr<variable> op_b = get_variable(op_b_str, false);
    op_b->set_used(true);

    std::vector<std::shared_ptr<variable>> arguments = {op_a, op_b};

    if(ctx->operand().size()>2) {
        std::string dest_str;
        if(ctx->operand(2)->Identifier() != nullptr)
            dest_str = ctx->operand(2)->Identifier()->getText();
        else if (ctx->operand(2)->Register() != nullptr)
            dest_str = ctx->operand(2)->Register()->getText();
        std::shared_ptr<variable> dest = get_variable(dest_str, false);
        arguments.push_back(dest);
    }

    ll_ast_node this_inst = ll_ast_node(ll_type_instr, ll_instruction(PSEUDO_INSTRUCTION, opcode, arguments));
    current_element->add_content(std::make_shared<ll_ast_node>(this_inst));
}

void AsmTree_visitor::exitIndep_instr(asm_parser::asm_grammarParser::Indep_instrContext *ctx) {
    std::string opcode = ctx->getText();
    std::vector<std::shared_ptr<variable>> arguments;

    ll_ast_node this_inst = ll_ast_node(ll_type_instr, ll_instruction(INDEPENDENT_INSTRUCTION, opcode, arguments));

    current_element->add_content(std::make_shared<ll_ast_node>(this_inst));
}

void AsmTree_visitor::exitLoad_instr(asm_parser::asm_grammarParser::Load_instrContext *ctx) {

    std::string dest_str;
    if(ctx->destination()->Identifier() != nullptr)
        dest_str = ctx->destination()->Identifier()->getText();
    else if (ctx->destination()->Register() != nullptr)
        dest_str = ctx->destination()->Register()->getText();

    std::shared_ptr<variable> dest = get_variable(dest_str, false);
    std::shared_ptr<variable> immediate = get_variable(ctx->FloatingPointLiteral()->getText(), true);

    std::vector<std::shared_ptr<variable>> arguments;
    arguments.push_back(dest);
    arguments.push_back(immediate);

    ll_ast_node this_inst = ll_ast_node(ll_type_instr, ll_instruction(LOAD_CONSTANT_INSTRUCTION, "ldc", arguments));
    current_element->add_content(std::make_shared<ll_ast_node>(this_inst));
}

void AsmTree_visitor::enterFor_block(asm_parser::asm_grammarParser::For_blockContext *ctx) {
    ll_loop loop;
    parent_elements.push(current_element);
    current_element = std::make_shared<ll_ast_node>(ll_type_for_block, loop);

}
void AsmTree_visitor::exitFor_block(asm_parser::asm_grammarParser::For_blockContext *ctx) {
    //Process loop initialization
    std::shared_ptr<ll_loop_node> loop = std::make_shared<ll_loop_node>();

    loop_start_t start;
    start.variable = ctx->for_decl()->Identifier()->getText();
    start.starting_value = std::stoi(ctx->for_decl()->Integer()->getText(), nullptr, 0);

    loop->set_loop_start(start);

    //Process advancement expression
    asm_parser::asm_grammarParser::For_incrContext *for_incr = ctx->for_incr();
    loop_advance_t adv;
    adv.loop_increment = 1;
    adv.direction = for_incr != nullptr; // variable increment -> direction true; variable decrement -> direction false;

    loop->set_advance(adv);

    //Process end condition
    loop_end_t end;
    end.condition = ctx->for_end()->for_end_comp_type()->getText();
    end.end_count =std::stoi(ctx->for_end()->Integer()->getText(), nullptr, 0);

    loop->set_loop_end(end);

    loop->loop.set_loop_start(start);
    loop->loop.set_loop_end(end);
    loop->loop.set_advance(adv);
    //Add loop properties to current element
    current_element->loop.set_loop_start(start);
    current_element->loop.set_loop_end(end);
    current_element->loop.set_advance(adv);

    //add current element to the  AST
    std::shared_ptr<ll_ast_node> tmp_parent = parent_elements.top();
    parent_elements.pop();
    std::shared_ptr<ll_ast_node> this_element = current_element;
    current_element = tmp_parent;
    current_element->add_content(this_element);
}


void AsmTree_visitor::enterProgram(asm_parser::asm_grammarParser::ProgramContext *ctx) {
    current_element = std::make_shared<ll_ast_node>(ll_type_program_head);
}

void AsmTree_visitor::exitProgram(asm_parser::asm_grammarParser::ProgramContext *ctx) {
    program_head = current_element;
}

std::shared_ptr<ll_ast_node> AsmTree_visitor::get_program() {
    return program_head;
}

void AsmTree_visitor::exitPragma(asm_parser::asm_grammarParser::PragmaContext *ctx) {
    ll_ast_node this_inst = ll_ast_node(ll_type_pragma,
                                        pragma(ctx->Identifier()->getText()));
    current_element->add_content(std::make_shared<ll_ast_node>(this_inst));
}

void AsmTree_visitor::exitConstant_decl(asm_parser::asm_grammarParser::Constant_declContext *ctx) {
    std::string identifier;
    if(ctx->Identifier() != nullptr)
        identifier = ctx->Identifier()->getText();
    else if (ctx->Register() != nullptr)
        identifier = ctx->Register()->getText();

    variable tmp = variable(true, identifier);
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}

void AsmTree_visitor::exitVariable_decl(asm_parser::asm_grammarParser::Variable_declContext *ctx) {
    std::string identifier;
    if(ctx->Identifier() != nullptr)
        identifier = ctx->Identifier()->getText();
    else if (ctx->Register() != nullptr)
        identifier = ctx->Register()->getText();

    variable tmp = variable(false, identifier);
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}

void AsmTree_visitor::exitInput_decl(asm_parser::asm_grammarParser::Input_declContext *ctx) {
    std::string identifier = ctx->Identifier()->getText();
    variable tmp = variable(false, identifier);
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}

void AsmTree_visitor::exitOutput_decl(asm_parser::asm_grammarParser::Output_declContext *ctx) {
    std::string identifier = ctx->Identifier()->getText();
    variable tmp = variable(false, identifier);
    tmp.set_used(true);
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}


void AsmTree_visitor::exitImmediate(asm_parser::asm_grammarParser::ImmediateContext *ctx) {
    if(ctx->Identifier()== nullptr){
        std::string identifier;
        if(ctx->Integer() != nullptr)
            identifier = ctx->Integer()->getText();
        else if (ctx->Octalnum() != nullptr)
            identifier = ctx->Octalnum()->getText();
        else if(ctx->Hexnum() != nullptr)
            identifier = ctx->Hexnum()->getText();

        variable tmp = variable(true, identifier);
        varmap->insert(identifier, std::make_shared<variable>(tmp));
    }
}

void AsmTree_visitor::exitFloat_const(asm_parser::asm_grammarParser::Float_constContext *ctx) {
    std::string identifier = ctx->FloatingPointLiteral()->getText();
    variable tmp = variable(true, identifier, true);
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}

std::shared_ptr<variable> AsmTree_visitor::get_variable(const std::string &variable_name, bool is_const) const {
    std::shared_ptr<variable> var;
    if(!varmap->count(variable_name))
        var = std::make_shared<variable>(is_const, variable_name);
    else
        var = varmap->at(variable_name);
    return var;
}

