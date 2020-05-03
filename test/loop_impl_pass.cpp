//
// Created by fils on 01/05/20.
//

#include "catch.hpp"
#include "../src/code_elements/for_loop.hpp"
#include "../src/code_elements/instruction.h"
#include "../src/code_elements/code_element.hpp"


TEST_CASE( "deep_copy_element") {



    for_loop loop;
    loop_start_t start = {"j", 36};
    loop.set_loop_start(start);
    instruction inst(3);
    std::shared_ptr<code_element> level_1 = std::make_shared<code_element>(type_for_block, loop);
    std::shared_ptr<code_element> level_2 = std::make_shared<code_element>(type_instr, inst);
    level_1->add_content(level_2);
    std::shared_ptr<code_element> result = deep_copy_element(level_1);
    bool test_types = level_1->type == result->type && level_2->type == result->get_content()[0]->type;
    bool test_instr_content = result->get_content()[0]->inst.emit() == level_2->inst.emit();
    bool test_loop_content = result->loop.get_loop_start().starting_value == start.starting_value;
    bool result_check = test_types && test_instr_content && test_loop_content;
    REQUIRE(result_check);
}