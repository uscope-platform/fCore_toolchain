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

#include "ast/low_level/ll_ast_node.hpp"
#include "passes/ll_passes.hpp"
#include "backend/output_generator.hpp"
#include "frontend/asm/asm_language_parser.h"


TEST(llPassesTest, pseudo_inst_pass) {

    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);

    std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r3");
    std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r4");
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b};

    std::shared_ptr<ll_instruction_node> instr = std::make_shared<ll_instruction_node>(isa_pseudo_instruction, "mov", args);
    AST->add_content(instr);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();

    ll_pass_manager manager = create_ll_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0x80061};
    ASSERT_EQ(result, gold_standard);
}


TEST(llPassesTest, instruction_count_pass) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r3");
    std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r4");
    std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r5");
    std::shared_ptr<variable> imm = std::make_shared<variable>(true, "100");
    std::shared_ptr<variable> fltc = std::make_shared<variable>(true, "1.5464", true);
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_instruction_node> instr = std::make_shared<ll_instruction_node>(isa_independent_instruction, "nop", args);
    AST->add_content(instr);

    args = {op_a, op_b};
    instr = std::make_shared<ll_instruction_node>(isa_pseudo_instruction, "mov", args); // +1
    AST->add_content(instr);

    args = {dest, imm};
    instr = std::make_shared<ll_instruction_node>(isa_immediate_instruction, "ldr", args); // +1
    AST->add_content(instr);

    args = {op_a, op_b,dest};
    instr = std::make_shared<ll_instruction_node>(isa_register_instruction, "add", args); // +1
    AST->add_content(instr);

    args = {dest};
    instr = std::make_shared<ll_instruction_node>(isa_load_constant_instruction, "ldc", args);// +2
    AST->add_content(instr);

    instr = std::make_shared<ll_instruction_node>(isa_intercalated_constant, 1.456);// +0
    AST->add_content(instr);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();

    ll_pass_manager manager = create_ll_pass_manager(map);
    manager.run_analysis_passes(AST);
    int count = manager.analysis_passes["instruction_counting"]->get_analysis_result()[0];


    ASSERT_EQ( count, 6);
}

TEST(llPassesTest, loop_less) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_pragma> loop_pragma = std::make_shared<ll_ast_pragma>("unroll");
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_instruction_node> loop_instr = std::make_shared<ll_instruction_node>(isa_independent_instruction, "nop", args);
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    loop_start_t start = {"j", 0};
    loop_advance_t  adv = {true,1};
    loop_end_t end = {3, "<"};

    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();
    lvl_1->set_advance(adv);
    lvl_1->set_loop_start(start);
    lvl_1->set_loop_end(end);

    lvl_1->set_content(l1_content);

    AST->add_content(lvl_1);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();

    ll_pass_manager manager = create_ll_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0, 0, 0};
    ASSERT_TRUE(result == gold_standard);
}

TEST(llPassesTest, loop_less_equal) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_pragma> loop_pragma = std::make_shared<ll_ast_pragma>("unroll");
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_instruction_node> loop_instr = std::make_shared<ll_instruction_node>(isa_independent_instruction, "nop", args);
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    loop_start_t start = {"j", 0};
    loop_advance_t  adv = {true,1};
    loop_end_t end = {3, "<="};

    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();
    lvl_1->set_advance(adv);
    lvl_1->set_loop_start(start);
    lvl_1->set_loop_end(end);

    lvl_1->set_content(l1_content);

    AST->add_content(lvl_1);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();

    ll_pass_manager manager = create_ll_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0, 0};
    ASSERT_TRUE(result == gold_standard);
}

TEST(llPassesTest, loop_more) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_pragma> loop_pragma = std::make_shared<ll_ast_pragma>("unroll");
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_instruction_node> loop_instr = std::make_shared<ll_instruction_node>(isa_independent_instruction, "nop", args);
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    loop_start_t start = {"j", 3};
    loop_advance_t  adv = {false,1};
    loop_end_t end = {1, ">"};


    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();

    lvl_1->set_advance(adv);
    lvl_1->set_loop_start(start);
    lvl_1->set_loop_end(end);

    lvl_1->set_content(l1_content);

    AST->add_content(lvl_1);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();

    ll_pass_manager manager = create_ll_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0, 0};
    ASSERT_TRUE(result == gold_standard);
}


TEST(llPassesTest, loop_more_equal) {
    std::shared_ptr<ll_ast_node> AST = std::make_shared<ll_ast_node>(ll_type_program_head);
    std::shared_ptr<ll_ast_pragma> loop_pragma = std::make_shared<ll_ast_pragma>("unroll");
    std::vector<std::shared_ptr<variable>> args = {};
    std::shared_ptr<ll_instruction_node> loop_instr = std::make_shared<ll_instruction_node>(isa_independent_instruction, "nop", args);
    std::vector<std::shared_ptr<ll_ast_node>> l1_content = {loop_pragma, loop_instr};

    loop_start_t start = {"j", 3};
    loop_advance_t  adv = {false,1};
    loop_end_t end = {1, ">="};


    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();
    lvl_1->set_advance(adv);
    lvl_1->set_loop_start(start);
    lvl_1->set_loop_end(end);

    lvl_1->set_content(l1_content);

    AST->add_content(lvl_1);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();

    ll_pass_manager manager = create_ll_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0,0,0};
    ASSERT_TRUE(result == gold_standard);
}


TEST(llPassesTest, deep_copy_element) {
    loop_start_t start = {"j", 36};
    std::vector<std::shared_ptr<variable>> args = {};

    std::shared_ptr<ll_loop_node> lvl_1 = std::make_shared<ll_loop_node>();
    lvl_1->set_loop_start(start);
    std::shared_ptr<ll_instruction_node> level_2 = std::make_shared<ll_instruction_node>(isa_independent_instruction, "nop", args);
    lvl_1->add_content(level_2);
    std::shared_ptr<ll_ast_node> result = ll_ast_node::deep_copy_element(lvl_1);

    ASSERT_EQ(*result, *lvl_1);
}