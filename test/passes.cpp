//
// Created by fils on 01/05/20.
//

#include "includes/catch.hpp"
#include "../src/code_elements/for_loop.hpp"
#include "../src/code_elements/instruction.h"
#include "../src/code_elements/code_element.hpp"
#include "../src/passes/passes.hpp"
#include "../src/backend/output_writer.hpp"


TEST_CASE( "pseudo_inst_pass") {


    ast_t AST = std::make_shared<code_element>(type_program_head);

    std::vector<uint16_t> args = {3, 4};
    ast_t instr = std::make_shared<code_element>(type_instr, instruction(PSEUDO_INSTRUCTION,"mov", args));
    AST->add_content(instr);

    pass_manager manager = create_pass_manager();
    manager.run_morphing_passes(AST);

    output_writer writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0x8061};
    REQUIRE(result == gold_standard);
}


TEST_CASE( "loop_pass") {
    ast_t AST = std::make_shared<code_element>(type_program_head);
    ast_t loop_pragma = std::make_shared<code_element>(type_pragma, pragma("unroll"));
    std::vector<uint16_t> args = {3};
    ast_t loop_instr = std::make_shared<code_element>(type_instr, instruction(INDEPENDENT_INSTRUCTION, args));
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
        pass_manager manager = create_pass_manager();
        manager.run_morphing_passes(AST);

        output_writer writer(AST,false);
        std::vector<uint32_t> result = writer.get_raw_program();
        std::vector<uint32_t> gold_standard = {3, 3, 3};
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
        pass_manager manager = create_pass_manager();
        manager.run_morphing_passes(AST);

        output_writer writer(AST,false);
        std::vector<uint32_t> result = writer.get_raw_program();
        std::vector<uint32_t> gold_standard = {3, 3};
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
        pass_manager manager = create_pass_manager();
        manager.run_morphing_passes(AST);

        output_writer writer(AST,false);
        std::vector<uint32_t> result = writer.get_raw_program();
        std::vector<uint32_t> gold_standard = {3, 3};
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
        pass_manager manager = create_pass_manager();
        manager.run_morphing_passes(AST);

        output_writer writer(AST,false);
        std::vector<uint32_t> result = writer.get_raw_program();
        std::vector<uint32_t> gold_standard = {3,3,3};
        REQUIRE(result == gold_standard);
    }

}


TEST_CASE( "deep_copy_element") {
    for_loop loop;
    loop_start_t start = {"j", 36};
    loop.set_loop_start(start);
    std::vector<uint16_t> args = {3};
    instruction inst(IMMEDIATE_INSTRUCTION, args);
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