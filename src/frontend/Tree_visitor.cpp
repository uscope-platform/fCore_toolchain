//
// Created by fils on 29/04/20.
//

#include "Tree_visitor.hpp"

Tree_visitor::Tree_visitor() = default;


void Tree_visitor::exitImm_instr(fs_grammarParser::Imm_instrContext * ctx) {

    std::string opcode = ctx->imm_opcode()->getText();

    variable dest(false, ctx->destination()->Identifier()->getText());
    variable immediate(true, ctx->Integer()->getText());

    std::vector<variable> arguments;
    arguments.push_back(dest);
    arguments.push_back(immediate);

    code_element this_inst = code_element(type_instr, instruction(IMMEDIATE_INSTRUCTION,opcode, arguments));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitReg_instr(fs_grammarParser::Reg_instrContext *ctx) {
    std::string opcode = ctx->reg_opcode()->getText();


    variable op_a(false,ctx->operand(0)->getText());
    variable op_b(false,ctx->operand(1)->getText());
    variable dest(false, ctx->destination()->getText());
    std::vector<variable> arguments = {op_a, op_b, dest};

    code_element this_inst = code_element(type_instr, instruction(REGISTER_INSTRUCTION,opcode, arguments));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitImm_alu_instr(fs_grammarParser::Imm_alu_instrContext *ctx) {
    std::string opcode = ctx->imm_alu_opcode()->getText();

    variable op_a(false,ctx->operand()->getText());
    variable imm(true,ctx->Integer()->getText());
    variable dest(false,ctx->destination()->getText());
    std::vector<variable> arguments = {op_a, imm, dest};

    code_element this_inst = code_element(type_instr, instruction(ALU_IMMEDIATE_INSTRUCTION, opcode, arguments));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitBranch_instr(fs_grammarParser::Branch_instrContext *ctx) {
    std::string opcode = ctx->branch_opcode()->getText();

    std::vector<variable> arguments;
    variable op_a(false,ctx->operand(0)->getText());
    variable op_b(false,ctx->operand(1)->getText());
    variable dest(true,ctx->immediate()->Hexnum()->getText());
    arguments = {op_a, op_b, dest};
    code_element this_inst = code_element(type_instr, instruction(BRANCH_INSTRUCTION, opcode,arguments));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitPseudo_instr(fs_grammarParser::Pseudo_instrContext *ctx) {
    std::string opcode = ctx->pseudo_opcode()->getText();

    variable op_a(false,ctx->Identifier(0)->getText());
    variable op_b(false,ctx->Identifier(1)->getText());
    std::vector<variable> arguments = {op_a, op_b};

    if(ctx->Identifier().size()>2) {
        variable dest(false,ctx->Identifier(2)->getText());
        arguments.push_back(dest);
    }

    code_element this_inst = code_element(type_instr, instruction(PSEUDO_INSTRUCTION,opcode,arguments));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitIndep_instr(fs_grammarParser::Indep_instrContext *ctx) {
    std::string opcode = ctx->getText();
    std::vector<variable> arguments;

    code_element this_inst = code_element(type_instr, instruction(INDEPENDENT_INSTRUCTION,opcode,arguments));

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
    ast_t tmp_parent = parent_elements.top();
    parent_elements.pop();
    ast_t this_element = current_element;
    current_element = tmp_parent;
    current_element->add_content(this_element);
}


void Tree_visitor::enterProgram(fs_grammarParser::ProgramContext *ctx) {
    current_element = std::make_shared<code_element>(type_program_head);
}

void Tree_visitor::exitProgram(fs_grammarParser::ProgramContext *ctx) {
    program_head = current_element;
}

ast_t Tree_visitor::get_program() {
    return program_head;
}

void Tree_visitor::exitPragma(fs_grammarParser::PragmaContext *ctx) {
    code_element this_inst = code_element(type_pragma,
                                          pragma(ctx->Identifier()->getText()));
    current_element->add_content(std::make_shared<code_element>(this_inst));
}

void Tree_visitor::exitConstant_decl(fs_grammarParser::Constant_declContext *ctx) {
    std::string identifier = ctx->Identifier()->getText();
    variable tmp = variable(true, identifier);
    var_map[identifier] = std::make_shared<variable>(tmp);
}

void Tree_visitor::exitVariable_decl(fs_grammarParser::Variable_declContext *ctx) {
    std::string identifier = ctx->Identifier()->getText();
    variable tmp = variable(false, identifier);
    var_map[identifier] = std::make_shared<variable>(tmp);
}

std::unordered_map<std::string, std::shared_ptr<variable>> Tree_visitor::get_varmap() {
    return var_map;
}

