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

program_bundle prepare_test_bundle(){

    program_bundle b;
    b.name = "test_prog";
    b.program.binary = {0x20004, 0xc, 0x20000, 0x10001, 0x3000a, 0xc, 0xc, 0x60841, 0xc};
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
    auto bundle = prepare_test_bundle();

    auto emulators_memory  = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
    auto common_memory  = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();

    emulator_runner uut(bundle);

    core_step_metadata m;
    m.id = "test_prog";
    m.running = true;
    m.order = 0;
    m.step_n = 0;
    uut.inputs_phase(m, 0);
    uut.emulation_phase(0);
    auto result = uut.dma_read(10, 0);
    ASSERT_EQ(result, 0x40733333);
}


TEST(Emulator_runner, run_simple_emulator_inputs) {
    auto bundle = prepare_test_bundle();

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
    uut.emulation_phase(0);
    auto result = uut.dma_read(10, 0);
    ASSERT_EQ(result, 0x40733333);
}