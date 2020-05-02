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
    std::shared_ptr<code_element> level_1 = std::make_shared<code_element>(type_for_block, nullptr, loop);
    std::shared_ptr<code_element> level_2 = std::make_shared<code_element>(type_instr, level_1, inst);
    level_1->add_content(level_2);
    std::shared_ptr<code_element> result = deep_copy_element(level_1, nullptr);
    //TODO: IMPLEMENT DEEP COMPARE TO CHECK THE RESULT (PARENT/CHILD RELATIONSHIPS IGNORED)
    //TODO: CHECK PARTENT/CHILD RELATIONSHIP SEAPARATELY
    //TODO: INVESTIGATE REMOVING PARENT ALLTOGETHER (MORE HASSLE THAN IT IS WORTH?)
    REQUIRE(false);
}