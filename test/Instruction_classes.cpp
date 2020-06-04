#include "includes/catch.hpp"
#include "../src/code_elements/instruction.h"

#include <memory>

TEST_CASE( "immediate_instruction" ) {

    std::vector<uint16_t> args = {9,4,100};
    instruction instr(IMMEDIATE_INSTRUCTION,args);

    SECTION("emit"){

        uint32_t result = instr.emit();

        REQUIRE( result == 0xc889 );
    }
    SECTION("print"){
        std::stringstream buffer;
        std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
        instr.print();
        std::string result = buffer.str();
        std::cout.rdbuf(old);
        std::string golden_standard = "c889 -> OPCODE: 9 DESTINATION: 4 IMMEDIATE: 64\n";
        REQUIRE(result == golden_standard);
    }
}

TEST_CASE( "register_instruction" ) {
    std::vector<uint16_t> args = {5, 2, 3,4};
    instruction instr(REGISTER_INSTRUCTION,args);

    SECTION("emit"){

        uint32_t result = instr.emit();

        REQUIRE(result == 0x8645);
    }
    SECTION("print"){
        std::stringstream buffer;
        std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
        instr.print();
        std::string result = buffer.str();
        std::cout.rdbuf(old);
        std::string golden_standard = "8645 -> OPCODE: 5 OPERAND A: 2 OPERAND B: 3 DESTINATION: 4\n";
        REQUIRE(result == golden_standard);
    }

}

TEST_CASE( "independent_instruction" ) {
    std::vector<uint16_t> args = {12};
    instruction instr(INDEPENDENT_INSTRUCTION,args);

    SECTION("emit"){

        uint32_t result = instr.emit();

        REQUIRE( result == 0xC );
    }
    SECTION("print"){
        std::stringstream buffer;
        std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
        instr.print();
        std::string result = buffer.str();
        std::cout.rdbuf(old);
        std::string golden_standard = "000c -> OPCODE: c\n";
        REQUIRE(result == golden_standard);
    }

}

