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
#include "result_helpers.hpp"

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

    auto uut_created = emulator_runner::create(bundle, bus_engine);
    ASSERT_TRUE(uut_created);
    auto uut = uut_created.value();

    core_step_metadata m;
    m.id = "test_prog";
    m.running = true;
    m.order = 0;
    m.step_n = 0;
    ASSERT_TRUE(uut.inputs_phase(m, 0));
    ASSERT_TRUE(uut.emulation_phase(0, 0));
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
    auto uut_created = emulator_runner::create(bundle, bus_engine);
    ASSERT_TRUE(uut_created);
    auto uut = uut_created.value();


    core_step_metadata m;
    m.id = "test_prog";
    m.running = true;
    m.order = 0;
    m.step_n = 0;
    auto res = uut.dma_write(0, 0, 0x40133333);
    EXPECT_TRUE(res);
    res =  uut.dma_write(1, 0, 0x3fc00000);
    EXPECT_TRUE(res);
    ASSERT_TRUE(uut.emulation_phase(0, 0));
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
    auto uut_created = emulator_runner::create(bundle, bus_engine);
    ASSERT_TRUE(uut_created);
    auto uut = uut_created.value();

    uut.set_active_channels(1);
    uint32_t line = 10;

    uut.add_breakpoint(line);

    auto outcome = uut.emulation_phase(0, 0);
    ASSERT_TRUE(outcome);
    ASSERT_TRUE(outcome.value().has_value());
    const auto &hit = outcome.value().value();
        EXPECT_EQ(hit.breakpoint, line);
        EXPECT_EQ(hit.memory_view[63], 0x3f800000);
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
    auto uut_created = emulator_runner::create(bundle, bus_engine);
    ASSERT_TRUE(uut_created);
    auto uut = uut_created.value();
    uut.set_active_channels(2);

    uint32_t line = 10;

    uut.add_breakpoint(line);

    auto outcome = uut.emulation_phase(0, 0);
    ASSERT_TRUE(outcome);
    ASSERT_TRUE(outcome.value().has_value());
    const auto &hit = outcome.value().value();
        EXPECT_EQ(hit.breakpoint, line);
        EXPECT_EQ(hit.memory_view[63], 0x3f800000);
    uut.remove_breakpoint(line);
    ASSERT_TRUE(uut.emulation_phase(0, line));

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
    auto uut_created = emulator_runner::create(bundle, bus_engine);
    ASSERT_TRUE(uut_created);
    auto uut = uut_created.value();
    uut.set_active_channels(1);
    uint32_t line = 14;

    uut.add_breakpoint(line);

    auto outcome = uut.emulation_phase(0, 0);
    ASSERT_TRUE(outcome);
    ASSERT_TRUE(outcome.value().has_value());
    const auto &hit = outcome.value().value();
        EXPECT_EQ(hit.breakpoint, line);
        EXPECT_EQ(hit.memory_view[63], 0x3f800000);

    ASSERT_TRUE(uut.step_over(0));
    ASSERT_TRUE(uut.step_over(0));
    auto checkpoint = expect_value(uut.step_over(0));

    EXPECT_EQ(checkpoint.status, "in_progress");
    EXPECT_EQ(checkpoint.core_name, "test_prog");
    EXPECT_EQ(checkpoint.breakpoint, 17);
    EXPECT_EQ(checkpoint.completed_round, false);
    EXPECT_TRUE(checkpoint.inputs.empty());
    std::vector<uint32_t> expected_mem(64, 0);
    expected_mem[1] = 0x3f800000;
    expected_mem[63] = 0x40000000;
    EXPECT_EQ(checkpoint.memory_view, expected_mem);

    ASSERT_TRUE(uut.step_over(0));
    ASSERT_TRUE(uut.step_over(0));
    ASSERT_TRUE(uut.step_over(0));
    ASSERT_TRUE(uut.step_over(0));



    auto result = uut.dma_read(20, 0);
    EXPECT_EQ(result, 0x40000000);
}


TEST(Emulator_runner, single_step_conclusion) {

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
    auto uut_created = emulator_runner::create(bundle, bus_engine);
    ASSERT_TRUE(uut_created);
    auto uut = uut_created.value();

    uint32_t line = 24;

    uut.add_breakpoint(line);

    auto outcome = uut.emulation_phase(0, 0);
    ASSERT_TRUE(outcome);
    ASSERT_TRUE(outcome.value().has_value());
    const auto &hit = outcome.value().value();
        EXPECT_EQ(hit.breakpoint, line);
        EXPECT_EQ(hit.memory_view[63], 0x42d60000);

    auto checkpoint = expect_value(uut.step_over(0));

    EXPECT_EQ(checkpoint.status, "complete");
    EXPECT_EQ(checkpoint.core_name, "test_prog");
    EXPECT_EQ(checkpoint.breakpoint, 0);
    EXPECT_EQ(checkpoint.completed_round, true);
    EXPECT_TRUE(checkpoint.inputs.empty());
}



namespace {
    /// Runs the assembly on a core with the given options and returns the outcome of the emulation of the first round
    result<round_outcome_t> run_asm_on_core(const std::string &code, comparator_type_t comparators, efi_implementation_t efi) {
        std::istringstream stream(code);
        std::map<std::string, std::vector<uint32_t>> io_map = {{"r1", {1}}, {"r2", {2}}, {"r3", {3}}};
        fcore_has has(stream, false, io_map);

        auto bundle = prepare_test_bundle(has.get_executable());
        bundle.comparator_type = comparators;
        bundle.efi_selector = efi;
        bundle.input.clear();

        auto bus_engine = std::make_shared<bus_allocator>();
        auto created = emulator_runner::create(bundle, bus_engine);
        if(!created) return fail(std::move(created).error());
        auto runner = created.value();
        runner.set_active_channels(1);
        return runner.emulation_phase(0, 0);
    }
}

TEST(Emulator_runner, dma_access_to_an_unmapped_address_fails) {
    std::istringstream stream("add r2, r1, r3\nstop\n");
    std::map<std::string, std::vector<uint32_t>> io_map = {{"r2", {2}}, {"r1", {1}}, {"r3", {3}}};
    fcore_has has(stream, false, io_map);
    auto bundle = prepare_test_bundle(has.get_executable());
    auto bus_engine = std::make_shared<bus_allocator>();
    auto created = emulator_runner::create(bundle, bus_engine);
    ASSERT_TRUE(created);
    auto uut = created.value();

    auto unmapped_read = uut.dma_read(999, 0);
    ASSERT_FALSE(unmapped_read);
    EXPECT_EQ(unmapped_read.error().code, error_code::emulation_error);

    auto unmapped_write = uut.dma_write(999, 0, 1);
    ASSERT_FALSE(unmapped_write);
    EXPECT_EQ(unmapped_write.error().code, error_code::emulation_error);
}

TEST(Emulator_runner, dma_access_to_an_unavailable_channel_fails) {
    std::istringstream stream("add r2, r1, r3\nstop\n");
    std::map<std::string, std::vector<uint32_t>> io_map = {{"r2", {2}}, {"r1", {1}}, {"r3", {3}}};
    fcore_has has(stream, false, io_map);
    auto bundle = prepare_test_bundle(has.get_executable());
    auto bus_engine = std::make_shared<bus_allocator>();
    auto created = emulator_runner::create(bundle, bus_engine);
    ASSERT_TRUE(created);
    auto uut = created.value();

    EXPECT_FALSE(uut.dma_read(10, 5));
    EXPECT_FALSE(uut.dma_write(0, 5, 1));
    EXPECT_FALSE(uut.dump_memory(5));
    EXPECT_TRUE(uut.dump_memory(0));
}

TEST(Emulator_runner, comparison_on_a_core_without_comparators_fails) {
    auto outcome = run_asm_on_core("bgt r1, r2, r3\nnop\nnop\nnop\nnop\nnop\nnop\nstop\n", comparator_none, efi_none);
    ASSERT_FALSE(outcome);
    EXPECT_EQ(outcome.error().code, error_code::emulation_error);
    // where it happened is attached while the error travels up
    ASSERT_FALSE(outcome.error().context.empty());
    EXPECT_NE(outcome.error().context.front().find("running instruction 0"), std::string::npos);
}

TEST(Emulator_runner, efi_on_a_core_without_an_efi_interface_fails) {
    auto outcome = run_asm_on_core("efi r1, r2, r3\nnop\nstop\n", comparator_full, efi_none);
    ASSERT_FALSE(outcome);
    EXPECT_EQ(outcome.error().code, error_code::emulation_error);
}

TEST(Emulator_runner, valid_program_completes_without_a_breakpoint) {
    auto outcome = run_asm_on_core("add r3, r1, r2\nnop\nnop\nnop\nnop\nnop\nnop\nstop\n", comparator_full, efi_none);
    ASSERT_TRUE(outcome);
    EXPECT_FALSE(outcome.value().has_value());
}
