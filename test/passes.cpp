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


#include <gtest/gtest.h>

#include "code_elements/ll_ast/ll_loop.hpp"
#include "code_elements/ll_ast/ll_instruction.h"
#include "code_elements/ll_ast/ll_ast_node.hpp"
#include "passes/passes.hpp"
#include "backend/output_generator.hpp"
#include "frontend/asm/asm_language_parser.h"


TEST(PassesTest, pseudo_inst_pass) {

    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);

    std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r3");
    std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r4");
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b};

    std::shared_ptr<ll_ast_node> instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(PSEUDO_INSTRUCTION, "mov", args));
    AST->add_content(instr);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    std::ifstream stream;
    stream.open("register_defs.s");
    asm_language_parser p1(stream, map);

    pass_manager manager = create_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0x80061};
    ASSERT_EQ(result, gold_standard);
}


TEST(PassesTest, instruction_count_pass) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r3");
    std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r4");
    std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r5");
    std::shared_ptr<variable> imm = std::make_shared<variable>(true, "100");
    std::shared_ptr<variable> fltc = std::make_shared<variable>(true, "1.5464", true);
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_ast_node> instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(INDEPENDENT_INSTRUCTION, "nop", args));
    AST->add_content(instr);

    args = {op_a, op_b};
    instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(PSEUDO_INSTRUCTION, "mov", args)); // +1
    AST->add_content(instr);

    args = {dest, imm};
    instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(IMMEDIATE_INSTRUCTION, "ldr", args)); // +1
    AST->add_content(instr);

    args = {op_a, op_b,dest};
    instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(REGISTER_INSTRUCTION, "add", args)); // +1
    AST->add_content(instr);

    args = {dest};
    instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(LOAD_CONSTANT_INSTRUCTION, "ldc", args));// +2
    AST->add_content(instr);

    instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(INTERCALATED_CONSTANT, 1.456));// +0
    AST->add_content(instr);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    std::ifstream stream;
    stream.open("register_defs.s");
    asm_language_parser p1(stream, map);
    pass_manager manager = create_pass_manager(map);
    manager.run_analysis_passes(AST);
    int count = manager.analysis_passes["instruction_counting"]->get_analysis_result()[0];


    ASSERT_EQ( count, 6);
}

TEST(PassesTest, loop_less) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_node> loop_pragma = std::make_shared<ll_ast_node>(ll_type_pragma, pragma("unroll"));
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_ast_node> loop_instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(INDEPENDENT_INSTRUCTION, "nop", args));
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    ll_loop loop;
    loop_start_t start = {"j", 0};
    loop_advance_t  adv = {true,1};
    loop_end_t end = {3, "<"};

    loop.set_loop_start(start);
    loop.set_advance(adv);
    loop.set_loop_end(end);

    std::shared_ptr<ll_ast_node> level_1 = std::make_shared<ll_ast_node>(ll_type_for_block, loop);
    level_1->set_content(l1_content);

    AST->add_content(level_1);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    std::ifstream stream;
    stream.open("register_defs.s");
    asm_language_parser p1(stream, map);

    pass_manager manager = create_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0, 0, 0};
    ASSERT_TRUE(result == gold_standard);
}

TEST(PassesTest, loop_less_equal) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_node> loop_pragma = std::make_shared<ll_ast_node>(ll_type_pragma, pragma("unroll"));
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_ast_node> loop_instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(INDEPENDENT_INSTRUCTION, "nop", args));
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    ll_loop loop;
    loop_start_t start = {"j", 0};
    loop_advance_t  adv = {true,1};
    loop_end_t end = {3, "<="};

    loop.set_loop_start(start);
    loop.set_advance(adv);
    loop.set_loop_end(end);

    std::shared_ptr<ll_ast_node> level_1 = std::make_shared<ll_ast_node>(ll_type_for_block, loop);
    level_1->set_content(l1_content);

    AST->add_content(level_1);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    std::ifstream stream;
    stream.open("register_defs.s");
    asm_language_parser p1(stream, map);
    pass_manager manager = create_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0, 0};
    ASSERT_TRUE(result == gold_standard);
}

TEST(PassesTest, loop_more) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_node> loop_pragma = std::make_shared<ll_ast_node>(ll_type_pragma, pragma("unroll"));
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_ast_node> loop_instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(INDEPENDENT_INSTRUCTION, "nop", args));
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    ll_loop loop;
    loop_start_t start = {"j", 3};
    loop_advance_t  adv = {false,1};
    loop_end_t end = {1, ">"};

    loop.set_loop_start(start);
    loop.set_advance(adv);
    loop.set_loop_end(end);

    std::shared_ptr<ll_ast_node> level_1 = std::make_shared<ll_ast_node>(ll_type_for_block, loop);
    level_1->set_content(l1_content);

    AST->add_content(level_1);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    std::ifstream stream;
    stream.open("register_defs.s");
    asm_language_parser p1(stream, map);
    pass_manager manager = create_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0, 0};
    ASSERT_TRUE(result == gold_standard);
}


TEST(PassesTest, loop_more_equal) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_node> loop_pragma = std::make_shared<ll_ast_node>(ll_type_pragma, pragma("unroll"));
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_ast_node> loop_instr = std::make_shared<ll_ast_node>(ll_type_instr, ll_instruction(INDEPENDENT_INSTRUCTION, "nop", args));
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    ll_loop loop;
    loop_start_t start = {"j", 3};
    loop_advance_t  adv = {false,1};
    loop_end_t end = {1, ">="};

    loop.set_loop_start(start);
    loop.set_advance(adv);
    loop.set_loop_end(end);

    std::shared_ptr<ll_ast_node> level_1 = std::make_shared<ll_ast_node>(ll_type_for_block, loop);
    level_1->set_content(l1_content);

    AST->add_content(level_1);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    std::ifstream stream;
    stream.open("register_defs.s");
    asm_language_parser p1(stream, map);
    pass_manager manager = create_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0,0,0};
    ASSERT_TRUE(result == gold_standard);
}


TEST(PassesTest, deep_copy_element) {
    ll_loop loop;
    loop_start_t start = {"j", 36};
    loop.set_loop_start(start);
    std::vector<std::shared_ptr<variable>> args = {};
    ll_instruction inst(INDEPENDENT_INSTRUCTION, "nop", args);
    std::shared_ptr<ll_ast_node> level_1 = std::make_shared<ll_ast_node>(ll_type_for_block, loop);
    std::shared_ptr<ll_ast_node> level_2 = std::make_shared<ll_ast_node>(ll_type_instr, inst);
    level_1->add_content(level_2);
    std::shared_ptr<ll_ast_node> result = ll_ast_node::deep_copy_element(level_1);
    bool test_types = level_1->type == result->type && level_2->type == result->get_content()[0]->type;
    bool test_instr_content = result->get_content()[0]->inst.emit() == level_2->inst.emit();
    bool test_loop_content = result->loop.get_loop_start().starting_value == start.starting_value;
    bool result_check = test_types && test_instr_content && test_loop_content;
    ASSERT_TRUE(result_check);
}