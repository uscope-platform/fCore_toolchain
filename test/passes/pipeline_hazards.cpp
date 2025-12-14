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
#include <pstl/algorithm_fwd.h>

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
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, r4, r5)));
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r5, r4, r6)));

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 1);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(1));

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0xa2061, 0, 0, 0, 0, 0, 0, 0xc20a1};
    ASSERT_EQ(result, gold_standard);
}


TEST(pipeline_hazards, reg_instruction_stall_a_2_ch) {


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
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, r4, r5)));
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r5, r4, r6)));

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 2);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(2));

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0xa2061, 0, 0, 0, 0xc20a1};
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
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, r4, r5)));
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r4, r5, r6)));

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 1);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(1));

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
    program_stream.push_back(instruction_variant(conversion_instruction(opcode_itf, r3,  r5)));
    program_stream.push_back(instruction_variant(conversion_instruction(opcode_fti, r5, r6)));


    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 1);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(1));

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
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, r4, r5)));
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, r4, r7)));
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, r4, r7)));
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r5, r4, r6)));

    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 1);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(1));

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0xa2061, 0xe2061, 0xe2061, 0, 0, 0, 0, 0xc20a1};
    ASSERT_EQ(result, gold_standard);
}


TEST(pipeline_hazards, csel_source_stall) {


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
    program_stream.push_back(instruction_variant(ternary_instruction(opcode_csel, r6, r4, r5, r6)));
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r4,r6, r4)));


    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 1);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(1));

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0xa20db, 0, 0, 0x83081};
    ASSERT_EQ(result, gold_standard);
}


TEST(pipeline_hazards, csel_destination_stall) {


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
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r4,r6, r4)));
    program_stream.push_back(instruction_variant(ternary_instruction(opcode_csel, r6, r4, r5, r6)));


    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 1);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(1));

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x83081, 0, 0, 0, 0 ,0, 0, 0xa20db};
    ASSERT_EQ(result, gold_standard);
}



TEST(pipeline_hazards, ldc_stall) {


    auto r3 = std::make_shared<variable>("r3");
    r3->set_bound_reg(3);
    auto r4 = std::make_shared<variable>("r4");
    r4->set_bound_reg(4);
    auto const_var = std::make_shared<variable>("constant",4.5f);


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(load_constant_instruction(opcode_ldc,r4, const_var)));
    program_stream.push_back(instruction_variant(intercalated_constant(4.5f)));
    program_stream.push_back(instruction_variant(conversion_instruction(opcode_fti, r4, r3)));



    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( ic, stream_pass_manager::asm_language, 1);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(1));

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x86,0x40900000, 0, 0x1885};
    ASSERT_EQ(result, gold_standard);
}



TEST(pipeline_hazards, ldc_stall_3_ch) {


    auto r3 = std::make_shared<variable>("r3");
    r3->set_bound_reg(3);
    auto r4 = std::make_shared<variable>("r4");
    r4->set_bound_reg(4);
    auto const_var = std::make_shared<variable>("constant",4.5f);


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(load_constant_instruction(opcode_ldc,r4, const_var)));
    program_stream.push_back(instruction_variant(intercalated_constant(4.5f)));
    program_stream.push_back(instruction_variant(conversion_instruction(opcode_fti, r4, r3)));


    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( ic, stream_pass_manager::asm_language, 3);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(3));

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x86,0x40900000, 0x1885};
    ASSERT_EQ(result, gold_standard);
}

TEST(pipeline_hazards, result_collision_avoidance) {


    auto r2 = std::make_shared<variable>("r2");
    r2->set_bound_reg(2);
    auto r3 = std::make_shared<variable>("r3");
    r3->set_bound_reg(3);
    auto r5 = std::make_shared<variable>("r5");
    r5->set_bound_reg(5);
    auto r7 = std::make_shared<variable>("r7");
    r7->set_bound_reg(7);
    auto r6 = std::make_shared<variable>("r6");
    r6->set_bound_reg(6);


    auto const1 = std::make_shared<variable>("constant",1.0f);
    auto const2 = std::make_shared<variable>("constant",2.0f);
    auto const3 = std::make_shared<variable>("constant",5);

    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(load_constant_instruction(opcode_ldc,r3, const1)));
    program_stream.push_back(instruction_variant(intercalated_constant(1.0f)));
    program_stream.push_back(instruction_variant(load_constant_instruction(opcode_ldc,r2, const2)));
    program_stream.push_back(instruction_variant(intercalated_constant(2.0f)));
    program_stream.push_back(instruction_variant(load_constant_instruction(opcode_ldc,r5, const3)));
    program_stream.push_back(instruction_variant(intercalated_constant(static_cast<uint32_t>(5))));

    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, r2,r6)));
    program_stream.push_back(instruction_variant(independent_instruction(opcode_nop)));
    program_stream.push_back(instruction_variant(conversion_instruction(opcode_itf, r5, r7)));



    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( ic, stream_pass_manager::asm_language, 1);
    program_stream = sman.apply_pass(program_stream, std::make_shared<result_deconfliction>(1));

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x66,0x3F800000, 0x46,0x40000000, 0xa6, 5, 0xc1061, 0, 0, 0x38a4};
    ASSERT_EQ(result, gold_standard);
}




TEST(pipeline_hazards, ldc_after_mul) {


    auto r1 = std::make_shared<variable>("r1");
    r1->set_bound_reg(1);
    auto r2 = std::make_shared<variable>("r2");
    r2->set_bound_reg(2);
    auto r6 = std::make_shared<variable>("r6");
    r6->set_bound_reg(6);
    auto r3 = std::make_shared<variable>("r3");
    r3->set_bound_reg(3);
    auto const1 = std::make_shared<variable>("constant",1.0f);

    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(register_instruction(opcode_mul, r6, r1,r2)));
    program_stream.push_back(instruction_variant(load_constant_instruction(opcode_ldc,r1, const1)));
    program_stream.push_back(instruction_variant(intercalated_constant(1.0f)));
    program_stream.push_back(instruction_variant(register_instruction(opcode_mul, r2, r1,r3)));



    auto ic =  std::make_shared<instrumentation_core>();

    stream_pass_manager sman( ic, stream_pass_manager::asm_language, 2);
    program_stream = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(2));

    writer.process_stream(program_stream, true);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x408c3, 0x26,0x3F800000, 0, 0, 0x60843};
    ASSERT_EQ(result, gold_standard);
}