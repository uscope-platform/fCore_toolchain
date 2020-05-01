//
// Created by fils on 29/04/20.
//

#include "Tree_visitor.hpp"

Tree_visitor::Tree_visitor() {
    program_head = std::make_shared<code_element>(code_element());
    current_element = std::make_shared<code_element>(code_element());
}

void Tree_visitor::exitImm_instr(fs_grammarParser::Imm_instrContext * ctx) {
    std::string opcode = ctx->imm_opcode()->getText();
    std::string imm_str = ctx->Integer()->getText();
    std::string dest = ctx->fcore_reg()->getText();
    uint16_t immediate =  std::stoi(imm_str,nullptr, 0);
    std::shared_ptr<instruction> instr = std::make_unique<immediate_instruction>(fcore_opcodes[opcode],fcore_registers[dest], immediate);
    current_element->add_content(instr);
}

void Tree_visitor::exitReg_instr(fs_grammarParser::Reg_instrContext *ctx) {
    std::string opcode = ctx->reg_opcode()->getText();
    std::vector<fs_grammarParser::Fcore_regContext*> ops = ctx->fcore_reg();
    std::string op_a = ops[0]->getText();
    std::string op_b = ops[1]->getText();
    std::string dest = ops[2]->getText();
    std::shared_ptr<instruction> instr = std::make_unique<register_operating_instruction>(fcore_opcodes[opcode],fcore_registers[op_a],fcore_registers[op_b],fcore_registers[dest]);
    current_element->add_content(instr);
}

void Tree_visitor::exitIndep_instr(fs_grammarParser::Indep_instrContext *ctx) {
    std::string opcode = ctx->getText();
    std::shared_ptr<instruction> instr = std::make_unique<independent_instruction>(fcore_opcodes[opcode]);
    current_element->add_content(instr);
}

void Tree_visitor::enterFor_block(fs_grammarParser::For_blockContext *ctx) {
    current_element = std::make_shared<for_loop>(type_for_block, current_element);

}
void Tree_visitor::exitFor_block(fs_grammarParser::For_blockContext *ctx) {
    //Process loop initialization
    loop_start_t start;
    start.variable = ctx->for_decl()->Identifier()->getText();
    start.starting_value = std::stoi(ctx->for_decl()->Integer()->getText(), nullptr, 0);

    //Process advancement expression
    fs_grammarParser::For_incrContext *for_incr = ctx->for_incr();
    loop_advance_t adv;
    adv.loop_increment = 1;
    adv.direction = for_incr != nullptr; // variable increment -> direction true; variable decrement -> direction false;

    //Process end condition
    loop_end_t end;
    end.condition = ctx->for_end()->for_end_comp_type()->getText();
    end.end_count =std::stoi(ctx->for_end()->Integer()->getText(), nullptr, 0);

    //Add loop properties to current element
    current_element->set_loop_start(start);
    current_element->set_loop_end(end);
    current_element->set_advance(adv);

    //add current element to the  AST
    std::shared_ptr<code_element> this_element = current_element;
    current_element = current_element->get_parent();
    current_element->add_content(this_element);

}


void Tree_visitor::enterProgram(fs_grammarParser::ProgramContext *ctx) {
    current_element = std::make_shared<code_element>(type_program_head, nullptr);
}

void Tree_visitor::exitProgram(fs_grammarParser::ProgramContext *ctx) {
    program_head = current_element;
}

std::shared_ptr<code_element> Tree_visitor::get_program() {
    return program_head;
}

void Tree_visitor::exitPragma(fs_grammarParser::PragmaContext *ctx) {
    std::shared_ptr<code_element> tmp_element =  std::make_shared<code_element>(type_pragma, nullptr);
    tmp_element->set_directive(ctx->Identifier()->getText());
    current_element->add_content(tmp_element);
}


