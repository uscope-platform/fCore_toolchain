// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.


#include <gtest/gtest.h>
#include <memory>

#include "ast/variable.hpp"
#include "ast/low_level/ll_instruction_node.hpp"
#include "fCore_isa.hpp"

TEST(InstructionClasses, immediate_instruction ) {

    std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
    std::shared_ptr<variable> imm = std::make_shared<variable>(true, "100");
    std::vector<std::shared_ptr<variable>> args = {dest, imm};
    ll_instruction_node instr(isa_immediate_instruction,"ldr", args);

    ASSERT_EQ( instr.emit(),  0x32087);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    instr.print();
    std::string result = buffer.str();
    std::cout.rdbuf(old);
    std::string golden_standard = "32087 -> OPCODE: ldr DESTINATION: r4 IMMEDIATE: 100\n";
    ASSERT_EQ(result, golden_standard);
}

TEST(InstructionClasses, register_instruction ) {

    std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r2");
    std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r3");
    std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};

    ll_instruction_node instr(isa_register_instruction,"add", args);

    ASSERT_EQ(instr.emit(), 0x81841);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    instr.print();
    std::string result = buffer.str();
    std::cout.rdbuf(old);
    std::string golden_standard = "81841 -> OPCODE: add OPERAND A: r2 OPERAND B: r3 DESTINATION: r4\n";
    ASSERT_EQ(result,  golden_standard);

}



TEST(InstructionClasses, independent_instruction ) {
    std::vector<std::shared_ptr<variable>> args = {};
    ll_instruction_node instr(isa_independent_instruction,"stop", args);


    ASSERT_EQ( instr.emit(), 0xc);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    instr.print();
    std::string result = buffer.str();
    std::cout.rdbuf(old);
    std::string golden_standard = "000c -> OPCODE: stop\n";
    ASSERT_EQ(result, golden_standard);


}

