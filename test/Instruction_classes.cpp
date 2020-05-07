#include "includes/catch.hpp"
#include "../src/code_elements/instruction.h"

#include <memory>

TEST_CASE( "immediate_instruction", "[imm_instr]" ) {
    std::vector<uint16_t> args = {9,4,100};
    instruction instr(IMMEDIATE_INSTRUCTION,args);
    uint32_t result = instr.emit();
    REQUIRE( result == 0x6449 );
}

TEST_CASE( "register_instruction", "[reg_instr]" ) {
    std::vector<uint16_t> args = {5, 2, 3,4};
    instruction instr(REGISTER_INSTRUCTION,args);
    uint32_t result = instr.emit();
    REQUIRE( result == 0x4325);
}

TEST_CASE( "independent_instruction", "[indep_instr]" ) {
    std::vector<uint16_t> args = {12};
    instruction instr(INDEPENDENT_INSTRUCTION,args);
    uint32_t result = instr.emit();
    REQUIRE( result == 12);
}
