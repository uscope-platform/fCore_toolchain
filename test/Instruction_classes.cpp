// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <gtest/gtest.h>
#include <memory>

#include "data_structures/common/variable.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"


using namespace fcore;

TEST(InstructionClasses, register_instruction) {

    std::shared_ptr<variable> op_a = std::make_shared<variable>("r2");
    std::shared_ptr<variable> op_b = std::make_shared<variable>("r3");
    std::shared_ptr<variable> dest = std::make_shared<variable>("r4");

    register_instruction instr("add", op_a, op_b, dest);

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

    independent_instruction instr("stop");


    ASSERT_EQ( instr.emit(), 0xc);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
    instr.print();
    std::string result = buffer.str();
    std::cout.rdbuf(old);
    std::string golden_standard = "000c -> OPCODE: stop\n";
    ASSERT_EQ(result, golden_standard);


}


TEST(InstructionClasses, variant_instruction_emit) {

    std::shared_ptr<variable> op_a = std::make_shared<variable>("r2");
    std::shared_ptr<variable> op_b = std::make_shared<variable>("r3");
    std::shared_ptr<variable> dest = std::make_shared<variable>("r4");

    register_instruction instr("add", op_a, op_b, dest);

    instruction_variant var(instr);

    ASSERT_EQ(var.emit(), 0x81841);


}
