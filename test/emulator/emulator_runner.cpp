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

#include "emulator/v2/emulator_runner.hpp"
#include "fcore_has.hpp"

using namespace fcore;
using namespace fcore::emulator_v2;

program_bundle prepare_test_bundle(std::vector<uint32_t> program){

    program_bundle b;
    b.name = "test_prog";
    b.program.binary = program;
    b.program.program_length.fixed_portion = 5;
    b.program.program_length.per_channel_portion = 1;
    b.io.emplace(0, 2, "i");
    b.io.emplace(1, 1, "i");
    b.io.emplace(10, 3, "o");

    emulator_v2::emulator_input_specs s;
    s.name = "a";
    s.metadata.type = type_float;
    s.metadata.width = 32;
    s.metadata.is_signed = true;
    s.is_vector = false;
    s.vector_size = 1;
    s.source_type = constant_input;
    s.data.emplace_back(std::vector<float>({2.3}));
    b.input.push_back(s);

    emulator_v2::emulator_input_specs s2;
    s2.name = "b";
    s2.metadata.type = type_float;
    s2.metadata.width = 32;
    s2.metadata.is_signed = true;
    s2.is_vector = false;
    s2.vector_size = 1;
    s2.source_type = constant_input;
    s2.data.emplace_back(std::vector<float>({1.5}));
    b.input.push_back(s2);
    b.sampling_frequency = 1;
    b.execution_order = 0;
    b.active_channels = 1;
    b.efi_selector = efi_none;
    b.comparator_type = comparator_full;

    return b;
}


TEST(Emulator_runner, run_simple_emulator) {


    std::istringstream stream(R"(
        add r2, r1, r3
        nop
        nop
        nop
        nop
        nop
        nop
        stop
    )");

    std::map<std::string, std::vector<uint32_t>> io_map = {{"r2", {2}}, {"r1", {1}}, {"r3", {3}}};

    fcore_has has(stream, false, io_map);

    std::vector<uint32_t> test_exec = has.get_executable();


    auto bundle = prepare_test_bundle(test_exec);

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    auto bus_engine = std::make_shared<bus_allocator>();

    core_endpoint ep;
    ep.bus_addresses = {0};
    bus_engine->add_destination("test_prog", "a", ep);

    ep.bus_addresses = {1};
    bus_engine->add_destination("test_prog", "b", ep);

    emulator_runner uut(bundle, bus_engine);

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

    std::istringstream stream(R"(
        add r2, r1, r3
        nop
        nop
        nop
        nop
        nop
        nop
        stop
    )");

    std::map<std::string, std::vector<uint32_t>> io_map = {{"r2", {2}}, {"r1", {1}}, {"r3", {3}}};

    fcore_has has(stream, false, io_map);

    std::vector<uint32_t> test_exec = has.get_executable();


    auto bundle = prepare_test_bundle(test_exec);


    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    bundle.input.clear();
    auto bus_engine = std::make_shared<bus_allocator>();
    emulator_runner uut(bundle, bus_engine);


    core_step_metadata m;
    m.id = "test_prog";
    m.running = true;
    m.order = 0;
    m.step_n = 0;
    auto res = uut.dma_write(0, 0, 0x40133333);
    EXPECT_TRUE(res);
    res =  uut.dma_write(1, 0, 0x3fc00000);
    EXPECT_TRUE(res);
    uut.emulation_phase(0, 0);
    auto result = uut.dma_read(10, 0);
    ASSERT_EQ(result, 0x40733333);
}



TEST(Emulator_runner, breakpoint) {

    std::istringstream stream(R"(
        ldc r1, 1.000000
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        stop
    )");

    std::map<std::string, std::vector<uint32_t>> io_map = {{"r63", {63}}};

    fcore_has has(stream, false, io_map);

    std::vector<uint32_t> test_exec = has.get_executable();

    auto bundle = prepare_test_bundle(test_exec);

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    bundle.input.clear();
    auto bus_engine = std::make_shared<bus_allocator>();
    emulator_runner uut(bundle, bus_engine);

    uut.set_active_channels(1);
    uint32_t line = 10;

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

    std::istringstream stream(R"(
        ldc r1, 1.000000
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        stop
    )");

    std::map<std::string, std::vector<uint32_t>> io_map = {{"r63", {63}}};

    fcore_has has(stream, false, io_map);

    std::vector<uint32_t> test_exec = has.get_executable();

    auto bundle = prepare_test_bundle(test_exec);


    bundle.io.emplace(20,63,"o");

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    bundle.input.clear();
    auto bus_engine = std::make_shared<bus_allocator>();
    emulator_runner uut(bundle, bus_engine);
    uut.set_active_channels(2);

    uint32_t line = 10;

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
    base.next_program = "test_2";
    base.core_name = "name";
    base.completed_round = false;
    base.progress.current = 12;
    base.progress.total_steps = 22;
    base.progress.channel = 3;
    base.progress.period = 0.1;

    nlohmann::json uut = base;

    std::string ref = R"({"breakpoint":23,"completed_round":false,"core_name":"name","inputs":{"test":1},"memory_view":[11,23,65],"next_program":"test_2","progress":{"channel":3,"current":12,"period":0.10000000149011612,"total_steps":22},"status":"in_progress"})";
    std::string result = uut.dump();

    EXPECT_EQ(ref, result);

    debug_checkpoint test_2 = uut;
    EXPECT_EQ(base, test_2);
}

TEST(Emulator_runner, single_stepping) {

    std::istringstream stream(R"(
        ldc r1, 1.000000
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        stop
    )");

    std::map<std::string, std::vector<uint32_t>> io_map = {{"r63", {63}}};

    fcore_has has(stream, false, io_map);

    std::vector<uint32_t> test_exec = has.get_executable();

    auto bundle = prepare_test_bundle(test_exec);

    bundle.io.emplace(20,63,"o");

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    bundle.input.clear();
    auto bus_engine = std::make_shared<bus_allocator>();
    emulator_runner uut(bundle, bus_engine);
    uut.set_active_channels(1);
    uint32_t line = 14;

    uut.add_breakpoint(line);

    try{
        uut.emulation_phase(0, 0);
        ASSERT_TRUE(false);
    } catch (BreakpointException &ex){
        EXPECT_EQ(ex.data.breakpoint, line);
        EXPECT_EQ(ex.data.memory_view[63], 0x3f800000);
    }

    uut.step_over(0);
    uut.step_over(0);
    auto checkpoint = uut.step_over(0);

    EXPECT_EQ(checkpoint.status, "in_progress");
    EXPECT_EQ(checkpoint.core_name, "test_prog");
    EXPECT_EQ(checkpoint.breakpoint, 17);
    EXPECT_EQ(checkpoint.completed_round, false);
    EXPECT_TRUE(checkpoint.inputs.empty());
    std::vector<uint32_t> expected_mem(64, 0);
    expected_mem[1] = 0x3f800000;
    expected_mem[63] = 0x40000000;
    EXPECT_EQ(checkpoint.memory_view, expected_mem);

    uut.step_over(0);
    uut.step_over(0);
    uut.step_over(0);
    uut.step_over(0);



    auto result = uut.dma_read(20, 0);
    EXPECT_EQ(result, 0x40000000);
}


TEST(Emulator_runner, single_step_conclusionp) {

    std::istringstream stream(R"(
        ldc r63, 52.5000
        ldc r1, 2.000000
        nop
        add r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        mul r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        sub r63, r1, r63
        nop
        nop
        nop
        nop
        nop
        nop
        stop
    )");

    std::map<std::string, std::vector<uint32_t>> io_map = {{"r63", {63}}};

    fcore_has has(stream, false, io_map);

    std::vector<uint32_t> test_exec = has.get_executable();

    auto bundle = prepare_test_bundle(test_exec);

    bundle.io.emplace(20,63,"o");

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    bundle.input.clear();
    auto bus_engine = std::make_shared<bus_allocator>();
    emulator_runner uut(bundle, bus_engine);

    uint32_t line = 24;

    uut.add_breakpoint(line);

    try{
        uut.emulation_phase(0, 0);
        ASSERT_TRUE(false);
    } catch (BreakpointException &ex){
        EXPECT_EQ(ex.data.breakpoint, line);
        EXPECT_EQ(ex.data.memory_view[63], 0x42d60000);
    }

    auto checkpoint = uut.step_over(0);

    EXPECT_EQ(checkpoint.status, "complete");
    EXPECT_EQ(checkpoint.core_name, "test_prog");
    EXPECT_EQ(checkpoint.breakpoint, 0);
    EXPECT_EQ(checkpoint.completed_round, true);
    EXPECT_TRUE(checkpoint.inputs.empty());
}

