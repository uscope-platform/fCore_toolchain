#include "includes/catch.hpp"
#include "../src/code_elements/instruction.h"

#include <memory>

TEST_CASE( "immediate_instruction" ) {

    std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
    std::shared_ptr<variable> imm = std::make_shared<variable>(true, "100");
    std::vector<std::shared_ptr<variable>> args = {dest, imm};
    instruction instr(IMMEDIATE_INSTRUCTION,"ldr", args);

    SECTION("emit"){

        uint32_t result = instr.emit();

        REQUIRE( result == 0xc88b );
    }
    SECTION("print"){
        std::stringstream buffer;
        std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
        instr.print();
        std::string result = buffer.str();
        std::cout.rdbuf(old);
        std::string golden_standard = "c88b -> OPCODE: ldr DESTINATION: r4 IMMEDIATE: 100\n";
        REQUIRE(result == golden_standard);
    }
}

TEST_CASE( "register_instruction" ) {

    std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r2");
    std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r3");
    std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};

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


TEST_CASE( "alu_immediate" ) {

    std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r2");
    std::shared_ptr<variable> op_b = std::make_shared<variable>(true, "100");
    std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};

    instruction instr(ALU_IMMEDIATE_INSTRUCTION,"addi", args);

    SECTION("emit"){

        uint32_t result = instr.emit();

        REQUIRE(result == 0xc8851);
    }
    SECTION("print"){
        std::stringstream buffer;
        std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
        instr.print();
        std::string result = buffer.str();
        std::cout.rdbuf(old);
        std::string golden_standard = "c8851 -> OPCODE: addi OPERAND A: r2 DESTINATION: r4 IMMEDIATE: 100\n";
        REQUIRE(result == golden_standard);
    }

}



TEST_CASE( "independent_instruction" ) {
    std::vector<std::shared_ptr<variable>> args = {};
    instruction instr(INDEPENDENT_INSTRUCTION,"stop", args);

    SECTION("emit"){

        uint32_t result = instr.emit();

        REQUIRE( result == 0x10);
    }
    SECTION("print"){
        std::stringstream buffer;
        std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
        instr.print();
        std::string result = buffer.str();
        std::cout.rdbuf(old);
        std::string golden_standard = "0010 -> OPCODE: stop\n";
        REQUIRE(result == golden_standard);
    }

}

