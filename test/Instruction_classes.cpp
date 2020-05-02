#include "catch.hpp"
#include "../src/code_elements/instruction.h"

#include <memory>

TEST_CASE( "immediate_instruction", "[imm_instr]" ) {

    instruction instr(9, 4, 100);
    uint32_t result = instr.emit();
    REQUIRE( result == 0x6449 );
}

TEST_CASE( "register_instruction", "[reg_instr]" ) {

    instruction instr(5, 2, 3,4);
    uint32_t result = instr.emit();
    REQUIRE( result == 0x4325);
}

TEST_CASE( "independent_instruction", "[indep_instr]" ) {

    instruction instr(12);
    uint32_t result = instr.emit();
    REQUIRE( result == 12);
}
