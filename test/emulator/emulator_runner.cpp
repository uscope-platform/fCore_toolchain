//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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

#include "emulator/emulator_runner.hpp"

using namespace fcore;

program_bundle prepare_test_bundle(std::vector<uint32_t> program){

    program_bundle b;
    b.name = "test_prog";
    b.program.binary = program;
    b.program.program_length.fixed_portion = 5;
    b.program.program_length.per_channel_portion = 1;
    b.io.emplace(0, 2, "i");
    b.io.emplace(1, 1, "i");
    b.io.emplace(10, 3, "o");

    emulator::emulator_input_specs s;
    s.name = "a";
    s.metadata.type = emulator::type_float;
    s.metadata.width = 32;
    s.metadata.is_signed = true;
    s.source_type = emulator::constant_input;
    s.data.emplace_back(std::vector<float>({2.3}));
    s.address = {0};
    s.channel = {0};
    b.input.push_back(s);

    emulator::emulator_input_specs s2;
    s2.name = "b";
    s2.metadata.type = emulator::type_float;
    s2.metadata.width = 32;
    s2.metadata.is_signed = true;
    s2.source_type = emulator::constant_input;
    s2.data.emplace_back(std::vector<float>({1.5}));
    s2.address = {1};
    s2.channel = {0};
    b.input.push_back(s2);
    b.sampling_frequency = 1;
    b.execution_order = 0;
    b.active_channels = 1;
    b.efi_selector = efi_none;
    b.comparator_type = comparator_full;

    return b;
}


TEST(Emulator_runner, run_simple_emulator) {
    auto bundle = prepare_test_bundle({0x20004, 0xc, 0x20000, 0x10001, 0x3000a, 0xc, 0xc, 0x60841, 0xc});

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    emulator_runner uut(bundle);

    core_step_metadata m;
    m.id = "test_prog";
    m.running = true;
    m.order = 0;
    m.step_n = 0;
    uut.inputs_phase(m, 0);
    uut.emulation_phase(0, 0);
    auto result = uut.dma_read(10, 0);
    ASSERT_EQ(result, 0x40733333);
}


TEST(Emulator_runner, run_simple_emulator_inputs) {
    auto bundle = prepare_test_bundle({0x20004, 0xc, 0x20000, 0x10001, 0x3000a, 0xc, 0xc, 0x60841, 0xc});

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    bundle.input.clear();
    emulator_runner uut(bundle);


    core_step_metadata m;
    m.id = "test_prog";
    m.running = true;
    m.order = 0;
    m.step_n = 0;
    uut.dma_write(0, 0, 0x40133333);
    uut.dma_write(1, 0, 0x3fc00000);
    uut.emulation_phase(0, 0);
    auto result = uut.dma_read(10, 0);
    ASSERT_EQ(result, 0x40733333);
}



TEST(Emulator_runner, breakpoint) {
    auto bundle = prepare_test_bundle({0x40002, 0xc, 0x3f0014, 0xc, 0xc,0x26, 0x3f800000, 0x7e0fe1,  0x7e0fe1,  0x7e0fe1, 0xc});

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    bundle.input.clear();
    emulator_runner uut(bundle);

    uint32_t line = 3;

    uut.add_breakpoint(line);

    try{
        uut.emulation_phase(0, 0);
        ASSERT_TRUE(false);
    } catch (BreakpointException &ex){
        EXPECT_EQ(ex.data.breakpoint, line);
        EXPECT_EQ(ex.data.memory_view[63], 0x3f800000);
    }
}


TEST(Emulator_runner, continue_emulation) {
    auto bundle = prepare_test_bundle({0x40002, 0xc, 0x3f0014, 0xc, 0xc,0x26, 0x3f800000, 0x7e0fe1,  0x7e0fe1,  0x7e0fe1, 0xc});

    bundle.io.emplace(20,63,"o");

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    bundle.input.clear();
    emulator_runner uut(bundle);

    uint32_t line = 3;

    uut.add_breakpoint(line);

    try{
        uut.emulation_phase(0, 0);
        ASSERT_TRUE(false);
    } catch (BreakpointException &ex) {
        EXPECT_EQ(ex.data.breakpoint, line);
        EXPECT_EQ(ex.data.memory_view[63], 0x3f800000);
    }
    uut.remove_breakpoint(line);
    uut.emulation_phase(0, line);

    auto result = uut.dma_read(20, 0);
    EXPECT_EQ(result, 0x40400000);
}



TEST(Emulator_runner, debug_checkpoint_serialization) {
    debug_checkpoint base;
    base.breakpoint = 23;
    base.memory_view = {11,23,65};
    base.inputs= {{"test",1}, {"test",2}};
    base.status = "in_progress";
    base.core_name = "name";
    nlohmann::json uut = base;

    std::string ref = R"({"breakpoint":23,"core_name":"name","inputs":{"test":1},"memory_view":[11,23,65],"status":"in_progress"})";
    std::string result = uut.dump();

    EXPECT_EQ(ref, result);

    debug_checkpoint test_2 = uut;
    EXPECT_EQ(base, test_2);
}

TEST(Emulator_runner, single_stepping) {
    auto bundle = prepare_test_bundle({0x40002, 0xc, 0x3f0014, 0xc, 0xc,0x26, 0x3f800000, 0x7e0fe1,  0x7e0fe1,  0x7e0fe1, 0xc});

    bundle.io.emplace(20,63,"o");

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    bundle.input.clear();
    emulator_runner uut(bundle);

    uint32_t line = 3;

    uut.add_breakpoint(line);

    try{
        uut.emulation_phase(0, 0);
        ASSERT_TRUE(false);
    } catch (BreakpointException &ex){
        EXPECT_EQ(ex.data.breakpoint, line);
        EXPECT_EQ(ex.data.memory_view[63], 0x3f800000);
    }

    auto checkpoint = uut.step_over();

    EXPECT_EQ(checkpoint.status, "in_progress");
    EXPECT_EQ(checkpoint.core_name, "test_prog");
    EXPECT_EQ(checkpoint.breakpoint, 4);
    EXPECT_EQ(checkpoint.completed_round, false);
    EXPECT_TRUE(checkpoint.inputs.empty());
    std::vector<uint32_t> expected_mem(64, 0);
    expected_mem[1] = 0x3f800000;
    expected_mem[63] = 0x40000000;
    EXPECT_EQ(checkpoint.memory_view, expected_mem);


    auto result = uut.dma_read(20, 0);
    EXPECT_EQ(result, 0x40000000);
}

