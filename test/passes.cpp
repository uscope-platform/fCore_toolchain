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

#include "includes/catch.hpp"
#include "fcore_has/code_elements/for_loop.hpp"
#include "fcore_has/code_elements/instruction.h"
#include "fcore_has/code_elements/code_element.hpp"
#include "fcore_has/passes/passes.hpp"
#include "fcore_has/backend/output_generator.hpp"
#include "fcore_has/frontend/file_parser.h"


TEST_CASE( "pseudo_inst_pass") {

    ast_t AST = std::make_shared<code_element>(type_program_head);

    std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r3");
    std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r4");
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b};

    ast_t instr = std::make_shared<code_element>(type_instr, instruction(PSEUDO_INSTRUCTION,"mov", args));
    AST->add_content(instr);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    std::ifstream stream;
    stream.open("register_defs.s");
    parser p1(stream, map);

    pass_manager manager = create_pass_manager(map);
    manager.run_morphing_passes(AST);

    output_generator writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0x8061};
    REQUIRE(result == gold_standard);
}


TEST_CASE( "instruction_count_pass") {
    ast_t AST = std::make_shared<code_element>(type_program_head);
    std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r3");
    std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r4");
    std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r5");
    std::shared_ptr<variable> imm = std::make_shared<variable>(true, "100");
    std::shared_ptr<variable> fltc = std::make_shared<variable>(true, "1.5464", true);
    std::vector<std::shared_ptr<variable>> args = {};
    ast_t instr = std::make_shared<code_element>(type_instr, instruction(INDEPENDENT_INSTRUCTION, "nop",args));
    AST->add_content(instr);

    args = {op_a, op_b};
    instr = std::make_shared<code_element>(type_instr, instruction(PSEUDO_INSTRUCTION,"mov", args)); // +1
    AST->add_content(instr);

    args = {dest, imm};
    instr = std::make_shared<code_element>(type_instr, instruction(IMMEDIATE_INSTRUCTION,"ldr", args)); // +1
    AST->add_content(instr);

    args = {op_a, op_b,dest};
    instr = std::make_shared<code_element>(type_instr, instruction(REGISTER_INSTRUCTION,"add", args)); // +1
    AST->add_content(instr);

    args = {dest};
    instr = std::make_shared<code_element>(type_instr, instruction(LOAD_CONSTANT_INSTRUCTION,"ldc", args));// +2
    AST->add_content(instr);

    instr = std::make_shared<code_element>(type_instr, instruction(INTERCALATED_CONSTANT,1.456));// +0
    AST->add_content(instr);

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    std::ifstream stream;
    stream.open("register_defs.s");
    parser p1(stream, map);
    pass_manager manager = create_pass_manager(map);
    manager.run_analysis_passes(AST);
    int count = manager.analysis_passes["instruction_counting"]->get_analysis_result()[0];


    REQUIRE( count == 6);
}









TEST_CASE( "loop_pass") {
    ast_t AST = std::make_shared<code_element>(type_program_head);
    ast_t loop_pragma = std::make_shared<code_element>(type_pragma, pragma("unroll"));
    std::vector<std::shared_ptr<variable>> args = {};
    ast_t loop_instr = std::make_shared<code_element>(type_instr, instruction(INDEPENDENT_INSTRUCTION, "nop",args));
    std::vector<ast_t> l1_content = {loop_pragma, loop_instr};
    SECTION("less_than_loop") {
        for_loop loop;
        loop_start_t start = {"j", 0};
        loop_advance_t  adv = {true,1};
        loop_end_t end = {3, "<"};

        loop.set_loop_start(start);
        loop.set_advance(adv);
        loop.set_loop_end(end);

        ast_t level_1 = std::make_shared<code_element>(type_for_block, loop);
        level_1->set_content(l1_content);

        AST->add_content(level_1);

        std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
        std::ifstream stream;
        stream.open("register_defs.s");
        parser p1(stream, map);

        pass_manager manager = create_pass_manager(map);
        manager.run_morphing_passes(AST);

        output_generator writer(AST, false);
        std::vector<uint32_t> result = writer.get_raw_program();
        std::vector<uint32_t> gold_standard = {0, 0, 0};
        REQUIRE(result == gold_standard);
    }
    SECTION("less_eq_than_loop") {
        for_loop loop;
        loop_start_t start = {"j", 0};
        loop_advance_t  adv = {true,1};
        loop_end_t end = {3, "<="};

        loop.set_loop_start(start);
        loop.set_advance(adv);
        loop.set_loop_end(end);

        ast_t level_1 = std::make_shared<code_element>(type_for_block, loop);
        level_1->set_content(l1_content);

        AST->add_content(level_1);

        std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
        std::ifstream stream;
        stream.open("register_defs.s");
        parser p1(stream, map);
        pass_manager manager = create_pass_manager(map);
        manager.run_morphing_passes(AST);

        output_generator writer(AST, false);
        std::vector<uint32_t> result = writer.get_raw_program();
        std::vector<uint32_t> gold_standard = {0, 0};
        REQUIRE(result == gold_standard);
    }
    SECTION("more_than_loop") {
        for_loop loop;
        loop_start_t start = {"j", 3};
        loop_advance_t  adv = {false,1};
        loop_end_t end = {1, ">"};

        loop.set_loop_start(start);
        loop.set_advance(adv);
        loop.set_loop_end(end);

        ast_t level_1 = std::make_shared<code_element>(type_for_block, loop);
        level_1->set_content(l1_content);

        AST->add_content(level_1);

        std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
        std::ifstream stream;
        stream.open("register_defs.s");
        parser p1(stream, map);
        pass_manager manager = create_pass_manager(map);
        manager.run_morphing_passes(AST);

        output_generator writer(AST, false);
        std::vector<uint32_t> result = writer.get_raw_program();
        std::vector<uint32_t> gold_standard = {0, 0};
        REQUIRE(result == gold_standard);
    }
    SECTION("more_eq_than_loop") {
        for_loop loop;
        loop_start_t start = {"j", 3};
        loop_advance_t  adv = {false,1};
        loop_end_t end = {1, ">="};

        loop.set_loop_start(start);
        loop.set_advance(adv);
        loop.set_loop_end(end);

        ast_t level_1 = std::make_shared<code_element>(type_for_block, loop);
        level_1->set_content(l1_content);

        AST->add_content(level_1);

        std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
        std::ifstream stream;
        stream.open("register_defs.s");
        parser p1(stream, map);
        pass_manager manager = create_pass_manager(map);
        manager.run_morphing_passes(AST);

        output_generator writer(AST, false);
        std::vector<uint32_t> result = writer.get_raw_program();
        std::vector<uint32_t> gold_standard = {0,0,0};
        REQUIRE(result == gold_standard);
    }

}



TEST_CASE( "deep_copy_element") {
    for_loop loop;
    loop_start_t start = {"j", 36};
    loop.set_loop_start(start);
    std::vector<std::shared_ptr<variable>> args = {};
    instruction inst(INDEPENDENT_INSTRUCTION, "nop", args);
    ast_t level_1 = std::make_shared<code_element>(type_for_block, loop);
    ast_t level_2 = std::make_shared<code_element>(type_instr, inst);
    level_1->add_content(level_2);
    ast_t result = deep_copy_element(level_1);
    bool test_types = level_1->type == result->type && level_2->type == result->get_content()[0]->type;
    bool test_instr_content = result->get_content()[0]->inst.emit() == level_2->inst.emit();
    bool test_loop_content = result->loop.get_loop_start().starting_value == start.starting_value;
    bool result_check = test_types && test_instr_content && test_loop_content;
    REQUIRE(result_check);
}