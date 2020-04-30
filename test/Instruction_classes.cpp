#include "catch.hpp"
#include "../src/frontend/immediate_instruction.h"
#include "../src/frontend/register_operating_instruction.h"
#include "../src/frontend/independent_instruction.hpp"
#include "../src/frontend/code_element.hpp"
#include "../src/backend/output_writer.hpp"
#include "../src/file_parser.h"
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

TEST_CASE( "complete_file", "[cmpl_file]" ) {
    std::string input_file = "test_add.s";

    std::shared_ptr<code_element> ast = parse(input_file);
    output_writer writer(ast);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0x6449, 0xc859, 0x6541,0xc};
    REQUIRE( result == gold_standard);
}