#include "catch.hpp"
#include "../src/code_elements/immediate_instruction.h"
#include "../src/code_elements/register_operating_instruction.h"
#include "../src/code_elements/independent_instruction.hpp"

#include <memory>

TEST_CASE( "immediate_instruction", "[imm_instr]" ) {

    immediate_instruction instr(9, 4, 100);
    uint32_t result = instr.emit();
    REQUIRE( result == 0x6449 );
}

TEST_CASE( "register_instruction", "[reg_instr]" ) {

    register_operating_instruction instr(5, 2, 3,4);
    uint32_t result = instr.emit();
    REQUIRE( result == 0x4325);
}

TEST_CASE( "independent_instruction", "[indep_instr]" ) {

    independent_instruction instr(12);
    uint32_t result = instr.emit();
    REQUIRE( result == 12);
}
