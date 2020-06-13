#include "includes/catch.hpp"
#include "../src/code_elements/instruction.h"

#include <memory>

TEST_CASE( "immediate_instruction" ) {

    variable dest(false, "r4");
    variable imm(true, "100");
    std::vector<variable> args = {dest, imm};
    instruction instr(IMMEDIATE_INSTRUCTION,"ldr", args);

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
        std::string golden_standard = "c889 -> OPCODE: ldr DESTINATION: r4 IMMEDIATE: 100\n";
        REQUIRE(result == golden_standard);
    }
}

TEST_CASE( "register_instruction" ) {

    variable op_a(false, "r2");
    variable op_b(false, "r3");
    variable dest(false, "r4");
    std::vector<variable> args = {op_a, op_b, dest};

    instruction instr(REGISTER_INSTRUCTION,"shl", args);

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
        std::string golden_standard = "8645 -> OPCODE: shl OPERAND A: r2 OPERAND B: r3 DESTINATION: r4\n";
        REQUIRE(result == golden_standard);
    }

}

TEST_CASE( "independent_instruction" ) {
    std::vector<variable> args = {};
    instruction instr(INDEPENDENT_INSTRUCTION,"stop", args);

    SECTION("emit"){

        uint32_t result = instr.emit();

        REQUIRE( result == 0xE );
    }
    SECTION("print"){
        std::stringstream buffer;
        std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
        instr.print();
        std::string result = buffer.str();
        std::cout.rdbuf(old);
        std::string golden_standard = "000e -> OPCODE: stop\n";
        REQUIRE(result == golden_standard);
    }

}

