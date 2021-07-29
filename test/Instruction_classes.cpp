// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.


#include <gtest/gtest.h>
#include <memory>

#include "tools/variable.hpp"
#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "fCore_isa.hpp"

TEST(InstructionClasses, register_instruction) {

    std::shared_ptr<variable> op_a = std::make_shared<variable>("r2");
    std::shared_ptr<variable> op_b = std::make_shared<variable>("r3");
    std::shared_ptr<variable> dest = std::make_shared<variable>("r4");

    ll_register_instr_node instr("add", op_a, op_b, dest);

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

    ll_independent_inst_node instr("stop");


    ASSERT_EQ( instr.emit(), 0xc);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    instr.print();
    std::string result = buffer.str();
    std::cout.rdbuf(old);
    std::string golden_standard = "000c -> OPCODE: stop\n";
    ASSERT_EQ(result, golden_standard);


}

