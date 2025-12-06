//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <gtest/gtest.h>

#include "passes/instruction_stream/stall_insertion.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "backend/binary_generator.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"
#include "data_structures/common/io_map.hpp"

using namespace fcore;

TEST(pipeline_hazards, reg_instruction_stall_a) {


    auto r3 = std::make_shared<variable>("r3");
    r3->set_bound_reg(3);
    auto r4 = std::make_shared<variable>("r4");
    r4->set_bound_reg(4);
    auto r5 = std::make_shared<variable>("r5");
    r5->set_bound_reg(5);
    auto r6 = std::make_shared<variable>("r6");
    r6->set_bound_reg(6);


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(register_instruction("add", r3, r4, r5)));
    program_stream.push_back(instruction_variant(register_instruction("add", r5, r4, r6)));

    auto bindings_map = std::make_shared<std::map<std::string, memory_range_t>>();
    std::shared_ptr<io_map> allocation_map;

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( bindings_map, allocation_map, ic, stream_pass_manager::asm_language);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>());

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0xa2061, 0, 0, 0, 0, 0, 0, 0xc20a1};
    ASSERT_EQ(result, gold_standard);
}


TEST(pipeline_hazards, reg_instruction_stall_b) {


    auto r3 = std::make_shared<variable>("r3");
    r3->set_bound_reg(3);
    auto r4 = std::make_shared<variable>("r4");
    r4->set_bound_reg(4);
    auto r5 = std::make_shared<variable>("r5");
    r5->set_bound_reg(5);
    auto r6 = std::make_shared<variable>("r6");
    r6->set_bound_reg(6);


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(register_instruction("add", r3, r4, r5)));
    program_stream.push_back(instruction_variant(register_instruction("add", r4, r5, r6)));

    auto bindings_map = std::make_shared<std::map<std::string, memory_range_t>>();
    std::shared_ptr<io_map> allocation_map;

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( bindings_map, allocation_map, ic, stream_pass_manager::asm_language);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>());

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0xa2061, 0, 0, 0, 0, 0, 0, 0xc2881};
    ASSERT_EQ(result, gold_standard);
}


TEST(pipeline_hazards, conv_instruction_stall) {


    auto r3 = std::make_shared<variable>("r3");
    r3->set_bound_reg(3);
    auto r5 = std::make_shared<variable>("r5");
    r5->set_bound_reg(5);
    auto r6 = std::make_shared<variable>("r6");
    r6->set_bound_reg(6);


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(conversion_instruction("itf", r3,  r5)));
    program_stream.push_back(instruction_variant(conversion_instruction("fti", r5, r6)));

    auto bindings_map = std::make_shared<std::map<std::string, memory_range_t>>();
    std::shared_ptr<io_map> allocation_map;

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( bindings_map, allocation_map, ic, stream_pass_manager::asm_language);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>());

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x2864, 0, 0, 0, 0, 0x30a5};
    ASSERT_EQ(result, gold_standard);
}



TEST(pipeline_hazards, partial_stall_needed) {


    auto r3 = std::make_shared<variable>("r3");
    r3->set_bound_reg(3);
    auto r4 = std::make_shared<variable>("r4");
    r4->set_bound_reg(4);
    auto r5 = std::make_shared<variable>("r5");
    r5->set_bound_reg(5);
    auto r6 = std::make_shared<variable>("r6");
    r6->set_bound_reg(6);
    auto r7 = std::make_shared<variable>("r7");
    r7->set_bound_reg(7);


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(register_instruction("add", r3, r4, r5)));
    program_stream.push_back(instruction_variant(register_instruction("add", r3, r4, r7)));
    program_stream.push_back(instruction_variant(register_instruction("add", r3, r4, r7)));
    program_stream.push_back(instruction_variant(register_instruction("add", r5, r4, r6)));

    auto bindings_map = std::make_shared<std::map<std::string, memory_range_t>>();
    std::shared_ptr<io_map> allocation_map;

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( bindings_map, allocation_map, ic, stream_pass_manager::asm_language);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>());

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0xa2061, 0xe2061, 0xe2061, 0, 0, 0, 0, 0xc20a1};
    ASSERT_EQ(result, gold_standard);
}


TEST(pipeline_hazards, csel_instruction_stall) {


    auto r3 = std::make_shared<variable>("r3");
    r3->set_bound_reg(3);
    auto r4 = std::make_shared<variable>("r4");
    r4->set_bound_reg(4);
    auto r5 = std::make_shared<variable>("r5");
    r5->set_bound_reg(5);
    auto r6 = std::make_shared<variable>("r6");
    r6->set_bound_reg(6);


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(ternary_instruction("csel", r6, r4, r5, r6)));
    program_stream.push_back(instruction_variant(register_instruction("add", r4,r6, r4)));

    auto bindings_map = std::make_shared<std::map<std::string, memory_range_t>>();
    std::shared_ptr<io_map> allocation_map;

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( bindings_map, allocation_map, ic, stream_pass_manager::asm_language);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>());

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0xa20db, 0, 0, 0x83081};
    ASSERT_EQ(result, gold_standard);
}
