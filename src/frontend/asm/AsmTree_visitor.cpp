// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "frontend/asm/AsmTree_visitor.hpp"



fcore::AsmTree_visitor::AsmTree_visitor(std::shared_ptr<variable_map> map) {
    varmap = std::move(map);
}


void fcore::AsmTree_visitor::exitReg_instr(asm_parser::asm_grammarParser::Reg_instrContext *ctx) {
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

    std::shared_ptr<variable> op_a = std::make_shared<variable>(op_a_str);
    op_a->set_used(true);
    std::shared_ptr<variable> op_b = std::make_shared<variable>(op_b_str);
    op_b->set_used(true);
    std::shared_ptr<variable> dest = std::make_shared<variable>(dest_str);


    std::shared_ptr<ll_register_instr_node> node = std::make_shared<ll_register_instr_node>(opcode, op_a, op_b, dest);
    program.push_back(node);
}

void fcore::AsmTree_visitor::exitConv_instr(asm_parser::asm_grammarParser::Conv_instrContext *ctx) {
    std::string opcode = ctx->conv_opcode()->getText();

    std::shared_ptr<variable> op_a = std::make_shared<variable>(ctx->operand(0)->getText());
    op_a->set_used(true);
    std::shared_ptr<variable> op_b = std::make_shared<variable>(ctx->operand(1)->getText());

    std::shared_ptr<ll_conversion_instr_node> node = std::make_shared<ll_conversion_instr_node>(opcode, op_a, op_b);
    program.push_back(node);
}

void fcore::AsmTree_visitor::exitBranch_instr(asm_parser::asm_grammarParser::Branch_instrContext *ctx) {
    std::string opcode = ctx->branch_opcode()->getText();

    std::shared_ptr<variable> op_a = std::make_shared<variable>(ctx->operand(0)->getText());
    op_a->set_used(true);
    std::shared_ptr<variable> op_b = std::make_shared<variable>(ctx->operand(1)->getText());
    op_b->set_used(true);
    std::shared_ptr<variable> dest = std::make_shared<variable>(ctx->operand(2)->getText());

    std::shared_ptr<ll_register_instr_node> node = std::make_shared<ll_register_instr_node>(opcode, op_a, op_b, dest);
    program.push_back(node);

}

void fcore::AsmTree_visitor::exitPseudo_instr(asm_parser::asm_grammarParser::Pseudo_instrContext *ctx) {
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



    std::shared_ptr<variable> op_a = std::make_shared<variable>(op_a_str);
    op_a->set_used(true);
    std::shared_ptr<variable> op_b = std::make_shared<variable>(op_b_str);
    op_b->set_used(true);

    std::vector<std::shared_ptr<variable>> arguments = {op_a, op_b};

    if(ctx->operand().size()>2) {
        std::string dest_str;
        if(ctx->operand(2)->Identifier() != nullptr)
            dest_str = ctx->operand(2)->Identifier()->getText();
        else if (ctx->operand(2)->Register() != nullptr)
            dest_str = ctx->operand(2)->Register()->getText();
        std::shared_ptr<variable> dest =std::make_shared<variable>(dest_str);
        arguments.push_back(dest);
    }

    std::shared_ptr<ll_pseudo_instr_node> node = std::make_shared<ll_pseudo_instr_node>(opcode, arguments);
    program.push_back(node);

}

void fcore::AsmTree_visitor::exitIndep_instr(asm_parser::asm_grammarParser::Indep_instrContext *ctx) {
    std::string opcode = ctx->getText();


    std::shared_ptr<ll_independent_inst_node> node = std::make_shared<ll_independent_inst_node>(opcode);
    program.push_back(node);

}

void fcore::AsmTree_visitor::exitLoad_instr(asm_parser::asm_grammarParser::Load_instrContext *ctx) {

    std::string dest_str;
    if(ctx->destination()->Identifier() != nullptr)
        dest_str = ctx->destination()->Identifier()->getText();
    else if (ctx->destination()->Register() != nullptr)
        dest_str = ctx->destination()->Register()->getText();

    std::shared_ptr<variable> dest = std::make_shared<variable>(dest_str);
    std::shared_ptr<variable> immediate;

    std::shared_ptr<ll_intercalated_const_instr_node> constant_node;
    if(ctx->FloatingPointLiteral() != nullptr){
        immediate = std::make_shared<variable>("constant", std::stof(ctx->FloatingPointLiteral()->getText()));
        constant_node = std::make_shared<ll_intercalated_const_instr_node>(immediate->get_const_f());
    } else if(ctx->integer_const() != nullptr){
        uint32_t const_val =  std::stoul(ctx->integer_const()->getText(), nullptr, 0);
        immediate = std::make_shared<variable>("constant",*(int*)&const_val);
        constant_node = std::make_shared<ll_intercalated_const_instr_node>(const_val);
    }

    std::shared_ptr<ll_load_constant_instr_node> instruction_node = std::make_shared<ll_load_constant_instr_node>("ldc", dest, immediate);

    program.push_back(instruction_node);
    program.push_back(constant_node);

}

fcore::instruction_stream fcore::AsmTree_visitor::get_program() {
    return program;
}

void fcore::AsmTree_visitor::exitConstant_decl(asm_parser::asm_grammarParser::Constant_declContext *ctx) {
    std::string identifier;
    if(ctx->Identifier() != nullptr) {
        identifier = ctx->Identifier()->getText();
    } else if (ctx->Register() != nullptr){
        identifier = ctx->Register()->getText();
    }

    variable tmp = variable(identifier);
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}

void fcore::AsmTree_visitor::exitVariable_decl(asm_parser::asm_grammarParser::Variable_declContext *ctx) {
    std::string identifier;

    if(ctx->Identifier() != nullptr) {
        identifier = ctx->Identifier()->getText();
    } else if (ctx->Register() != nullptr){
        identifier = ctx->Register()->getText();
    }

    variable tmp = variable(identifier);
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}

void fcore::AsmTree_visitor::exitInput_decl(asm_parser::asm_grammarParser::Input_declContext *ctx) {
    std::string identifier = ctx->Identifier()->getText();
    variable tmp = variable(identifier);
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}

void fcore::AsmTree_visitor::exitOutput_decl(asm_parser::asm_grammarParser::Output_declContext *ctx) {
    std::string identifier = ctx->Identifier()->getText();
    variable tmp = variable( identifier);
    tmp.set_used(true);
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}


void fcore::AsmTree_visitor::exitImmediate(asm_parser::asm_grammarParser::ImmediateContext *ctx) {
    if(ctx->Identifier()== nullptr){
        std::string identifier;
        if(ctx->Integer() != nullptr)
            identifier = ctx->Integer()->getText();
        else if (ctx->Octalnum() != nullptr)
            identifier = ctx->Octalnum()->getText();
        else if(ctx->Hexnum() != nullptr)
            identifier = ctx->Hexnum()->getText();

        variable tmp = variable("constant", std::stoi(identifier));
        varmap->insert(identifier, std::make_shared<variable>(tmp));
    }
}

void fcore::AsmTree_visitor::exitFloat_const(asm_parser::asm_grammarParser::Float_constContext *ctx) {
    std::string identifier = ctx->FloatingPointLiteral()->getText();
    variable tmp = variable("constant", std::stof(identifier));
    varmap->insert(identifier, std::make_shared<variable>(tmp));
}

