//
// Created by fils on 29/04/20.
//

#include "Tree_visitor.hpp"

Tree_visitor::Tree_visitor() {
}

void Tree_visitor::exitImm_instr(fs_grammarParser::Imm_instrContext * ctx) {

    std::string opcode = ctx->imm_opcode()->getText();
    std::string imm_str = ctx->Integer()->getText();
    std::string dest = ctx->fcore_reg()->getText();
    uint16_t immediate =  std::stoi(imm_str,nullptr, 0);

    std::vector<uint16_t> arguments;
    arguments.push_back(fcore_opcodes[opcode]);
    arguments.push_back(fcore_registers[dest]);
    arguments.push_back(immediate);

    code_element this_inst = code_element(type_instr, instruction(IMMEDIATE_INSTRUCTION,arguments));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitReg_instr(fs_grammarParser::Reg_instrContext *ctx) {
    std::string opcode = ctx->reg_opcode()->getText();
    std::vector<fs_grammarParser::Fcore_regContext*> ops = ctx->fcore_reg();

    std::vector<uint16_t> arguments;
    arguments.push_back(fcore_opcodes[opcode]);
    arguments.push_back(fcore_registers[ops[0]->getText()]);
    arguments.push_back(fcore_registers[ops[1]->getText()]);
    arguments.push_back(fcore_registers[ops[2]->getText()]);

    code_element this_inst = code_element(type_instr, instruction(REGISTER_INSTRUCTION,arguments));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitBranch_instr(fs_grammarParser::Branch_instrContext *ctx) {
    std::string opcode = ctx->branch_opcode()->getText();
    std::vector<fs_grammarParser::Fcore_regContext*> ops = ctx->fcore_reg();

    std::vector<uint16_t> arguments;
    arguments.push_back(fcore_opcodes[opcode]);
    arguments.push_back(fcore_registers[ops[0]->getText()]);
    arguments.push_back(fcore_registers[ops[1]->getText()]);
    arguments.push_back(std::stoi(ctx->immediate()->Hexnum()->getText(), nullptr, 16));
    code_element this_inst = code_element(type_instr, instruction(BRANCH_INSTRUCTION,arguments));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitPseudo_instr(fs_grammarParser::Pseudo_instrContext *ctx) {
    std::string opcode = ctx->pseudo_opcode()->getText();
    std::vector<fs_grammarParser::Fcore_regContext*> ops = ctx->fcore_reg();

    std::vector<uint16_t> arguments;
    arguments.push_back(fcore_registers[ops[0]->getText()]);
    arguments.push_back(fcore_registers[ops[1]->getText()]);
    if(ops.size()>2)
        arguments.push_back(fcore_registers[ops[2]->getText()]);
    code_element this_inst = code_element(type_instr, instruction(PSEUDO_INSTRUCTION,opcode,arguments));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitIndep_instr(fs_grammarParser::Indep_instrContext *ctx) {
    std::string opcode = ctx->getText();

    std::vector<uint16_t> arguments;
    arguments.push_back(fcore_opcodes[opcode]);

    code_element this_inst = code_element(type_instr, instruction(INDEPENDENT_INSTRUCTION,arguments));

    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::enterFor_block(fs_grammarParser::For_blockContext *ctx) {
    for_loop loop;
    parent_elements.push(current_element);
    current_element = std::make_shared<code_element>(type_for_block,loop);

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
    current_element->loop.set_loop_start(start);
    current_element->loop.set_loop_end(end);
    current_element->loop.set_advance(adv);

    //add current element to the  AST
    std::shared_ptr<code_element> tmp_parent = parent_elements.top();
    parent_elements.pop();
    std::shared_ptr<code_element> this_element = current_element;
    current_element = tmp_parent;
    current_element->add_content(this_element);
}


void Tree_visitor::enterProgram(fs_grammarParser::ProgramContext *ctx) {
    current_element = std::make_shared<code_element>(type_program_head);
}

void Tree_visitor::exitProgram(fs_grammarParser::ProgramContext *ctx) {
    program_head = current_element;
}

std::shared_ptr<code_element> Tree_visitor::get_program() {
    return program_head;
}

void Tree_visitor::exitPragma(fs_grammarParser::PragmaContext *ctx) {
    code_element this_inst = code_element(type_pragma,
                                          pragma(ctx->Identifier()->getText()));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

