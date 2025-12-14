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

#include "backend/binary_generator.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "fcore_cc.hpp"

using namespace fcore;

TEST(virtual_instructions, virtual_instruction_implementation) {


    auto op_a = std::make_shared<variable>("r3");
    auto op_b = std::make_shared<variable>("r4");
    std::vector args = {op_a, op_b};


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(pseudo_instruction(opcode_mov, args)));

    auto ic =  std::make_shared<instrumentation_core>();
    stream_pass_manager sman( ic,stream_pass_manager::asm_language, 1);
    program_stream = sman.process_stream(program_stream);

    writer.process_stream(program_stream, false);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x8006E};
    ASSERT_EQ(result, gold_standard);
}


TEST(virtual_instructions, ternary_reduction) {


    auto op_a = std::make_shared<variable>("r3");
    auto op_b = std::make_shared<variable>("r4");
    std::vector args = {op_a, op_b};


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(pseudo_instruction(opcode_mov, args)));

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( ic, stream_pass_manager::asm_language, 1);
    program_stream = sman.process_stream(program_stream);

    writer.process_stream(program_stream, false);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x8006E};
    ASSERT_EQ(result, gold_standard);
}
