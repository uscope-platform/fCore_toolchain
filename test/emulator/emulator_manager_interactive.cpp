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
#include <nlohmann/json.hpp>
#include <fstream>

#include "emulator_test_helpers.hpp"
#include "emulator/emulator_dispatcher.hpp"

using namespace fcore;
using namespace fcore::emulator_v2;

nlohmann::json prepare_asm_spec(std::vector<std::string> pv, uint32_t n_steps, std::vector<uint32_t> output_regs, uint32_t n_channels){

    nlohmann::json spec;
    spec["version"] = 2;
    spec["cores"] = std::vector<nlohmann::json>();
    spec["emulation_time"] = n_steps;

    for(int i = 0; i< pv.size(); i++){
        auto cs = nlohmann::json();

        cs["order"] = i+1;
        cs["id"] = "test_" + std::to_string(i);

        cs["program"] = nlohmann::json();
        cs["program"]["headers"] = std::vector<std::string>();
        cs["program"]["content"] = pv[i];
        cs["channels"] = n_channels;
        cs["options"] = nlohmann::json();
        cs["options"]["comparators"] = "full";
        cs["options"]["efi_implementation"] = "none";
        cs["sampling_frequency"] =1;
        cs["deployment"] = nlohmann::json();
        cs["deployment"]["control_address"] = 18316525568;
        cs["deployment"]["rom_address"] = 17179869184;
        cs["deployment"]["has_reciprocal"] = false;
        cs["input_data"] = std::vector<nlohmann::json>();
        cs["inputs"]= std::vector<nlohmann::json>();

        cs["program"]["type"] = "asm";
        cs["program"]["build_settings"] = nlohmann::json();
        cs["program"]["build_settings"]["io"] = nlohmann::json();

        cs["program"]["build_settings"]["io"]["inputs"] = std::vector<std::string>();
        cs["program"]["build_settings"]["io"]["outputs"] = std::vector<std::string>();
        cs["program"]["build_settings"]["io"]["memories"] = std::vector<std::string>();
        cs["program"]["build_settings"]["io"]["memories"].push_back("out");



        cs["outputs"]= std::vector<nlohmann::json>();

        for(auto &j:output_regs){
            auto out = nlohmann::json();
            out["name"] = "r" + std::to_string(j);
            out["metadata"]["type"] = "float";
            out["metadata"]["width"] = 32;
            out["metadata"]["signed"] = true;
            out["metadata"]["common_io"] = false;
            out["vector_size"] = 1;
            out["is_vector"] = false;
            cs["outputs"].push_back(out);
        }

        cs["memory_init"]= std::vector<nlohmann::json>();

        spec["cores"].push_back(cs);
    }


    spec["interconnect"] = std::vector<nlohmann::json>();
    spec["deployment_mode"] = false;
    return spec;
}


TEST(emulator_manager_interactive, uninterrupted_run) {

    std::string program = R"(
        ldc r42, 12.5000
        ldc r3, 3.2000
        add r3, r42, r12
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42}, 1);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.emulate();
    auto dbg = manager.get_results().dump(4);
    float res = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, 15.7f);

}



TEST(emulator_manager_interactive, breakpoint) {

    std::string program = R"(
        ldc r42, 12.5000
        ldc r3, 3.2000
        add r3, r42, r12
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42}, 1);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 2);
    auto breakpoint = manager.emulate();
    EXPECT_TRUE(breakpoint.has_value());

    auto result = breakpoint.value();


    fcore::debug_checkpoint expected;
    expected.status = "in_progress";
    expected.core_name = "test_0";
    expected.next_program = "test_0";
    expected.breakpoint = 2;
    expected.completed_round = false;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x0;
    expected.memory_view[42] = 0x41480000;
    expected.progress.current = 1;
    expected.progress.channel = 0;
    expected.progress.total_steps = 1;
    expected.progress.period = 1;
    EXPECT_EQ(expected, result);
}




TEST(emulator_manager_interactive, continue_emulation) {

    std::string program = R"(
        ldc r42, 12.5000
        ldc r3, 3.2000
        add r3, r42, r12
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42}, 1);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 2);
    auto bp_1 = manager.emulate();
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 2);
    auto breakpoint = manager.continue_emulation();
    EXPECT_TRUE(breakpoint.has_value());
    auto result = breakpoint.value();


    debug_checkpoint expected;
    expected.status = "complete";
    expected.core_name = "test_0";
    expected.breakpoint = 0;
    expected.next_program = "";
    expected.completed_round = true;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.period = 1;
    expected.progress.channel = 0;
    expected.progress.total_steps = 1;
    expected.progress.current = 2;

    EXPECT_EQ(expected, result);
}

TEST(emulator_manager_interactive, step_over) {

    std::string program = R"(
        ldc r42, 12.5000
        ldc r3, 3.2000
        add r3, r42, r12
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42}, 1);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 2);
    auto bp_1 = manager.emulate();
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 2);
    auto breakpoint = manager.step_over();

    debug_checkpoint expected;
    expected.status = "in_progress";
    expected.core_name = "test_0";
    expected.next_program = "test_0";
    expected.breakpoint = 3;
    expected.completed_round = false;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.channel =0;
    expected.progress.total_steps = 1;
    expected.progress.period = 1;
    expected.progress.current =1;

    EXPECT_EQ(expected, breakpoint);

}



TEST(emulator_manager_interactive, step_over_round_end) {

    std::string program = R"(
        ldc r42, 12.5000
        ldc r3, 3.2000
        add r3, r42, r12
        stop
    )";
    uint32_t n_steps = 2;

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42}, 1);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 3);
    auto bp_1 = manager.emulate();
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 3);
    auto breakpoint = manager.step_over();

    debug_checkpoint expected;
    expected.status = "in_progress";
    expected.core_name = "test_0";
    expected.next_program = "test_0";
    expected.breakpoint = 0;
    expected.completed_round = true;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.current = 2;
    expected.progress.channel = 0;
    expected.progress.total_steps = 2;
    expected.progress.period = 1;

    EXPECT_EQ(expected, breakpoint);

};


TEST(emulator_manager_interactive, two_programs_continue) {

    std::string program_a = R"(
        ldc r42, 12.5000
        ldc r3, 3.2000
        add r3, r42, r12
        stop
    )";

    std::string program_b = R"(
        ldc r45, 1.5000
        ldc r4, 332.2000
        sub r45, r4, r14
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program_a, program_b}, n_steps, {12, 42}, 1);
    spec["cores"][1]["outputs"][0]["name"] = "r14";

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 3);
    auto bp_1 = manager.emulate();
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 3);
    manager.remove_breakpoint("test_0", 3);
    auto breakpoint = manager.continue_emulation();

    debug_checkpoint expected;
    expected.status = "complete";
    expected.core_name = "test_0";
    expected.next_program = "";
    expected.breakpoint = 0;
    expected.completed_round = true;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.current = 2;
    expected.progress.channel = 0;
    expected.progress.total_steps = 1;
    expected.progress.period = 1;

    EXPECT_EQ(expected, breakpoint);
    auto dbg = manager.get_results().dump(4);
    auto results = manager.get_results();

    float res = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, 15.7f);

     res = manager.get_results()["test_1"]["outputs"]["r14"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, -330.7f);
};



TEST(emulator_manager_interactive, second_program_breakpoint) {

    std::string program_a = R"(
        ldc r42, 12.5000
        ldc r3, 3.2000
        add r3, r42, r12
        stop
    )";

    std::string program_b = R"(
        ldc r43, 1.5000
        ldc r4, 332.2000
        sub r43, r4, r13
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program_a, program_b}, n_steps, {12, 42}, 1);
    spec["cores"][1]["outputs"][0]["name"] = "r13";

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_1", 3);
    auto bp_1 = manager.emulate();
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().core_name, "test_1");
    EXPECT_EQ(bp_1.value().breakpoint, 3);
    manager.remove_breakpoint("test_1", 3);
    auto breakpoint = manager.continue_emulation();

    debug_checkpoint expected;
    expected.status = "complete";
    expected.core_name = "test_0";
    expected.next_program = "";
    expected.breakpoint = 0;
    expected.completed_round = true;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.current = 2;
    expected.progress.channel = 0;
    expected.progress.total_steps = 1;
    expected.progress.period = 1;

    EXPECT_EQ(expected, breakpoint);
    auto dbg = manager.get_results().dump(4);
    auto results = manager.get_results();

    float res = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, 15.7f);

    res = manager.get_results()["test_1"]["outputs"]["r13"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, -330.7f);
};

TEST(emulator_manager_interactive, two_programs_step_over) {

    std::string program_a = R"(
        ldc r42, 12.5000
        ldc r3, 3.2000
        add r3, r42, r12
        stop
    )";

    std::string program_b = R"(
        ldc r43, 1.5000
        ldc r4, 332.2000
        sub r43, r4, r13
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program_a, program_b}, n_steps, {12, 42}, 1);
    spec["cores"][1]["outputs"][0]["name"] = "r13";

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 3);
    auto bp_1 = manager.emulate();
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 3);
    manager.remove_breakpoint("test_0", 3);
    manager.step_over();
    auto breakpoint = manager.continue_emulation();


    debug_checkpoint expected;
    expected.status = "complete";
    expected.core_name = "test_0";
    expected.next_program = "";
    expected.breakpoint = 0;
    expected.completed_round = true;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.current = 2;
    expected.progress.channel = 0;
    expected.progress.total_steps = 1;
    expected.progress.period = 1;

    EXPECT_EQ(expected, breakpoint);
    auto dbg = manager.get_results().dump(4);
    auto results = manager.get_results();

    float res = results["test_0"]["outputs"]["r12"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, 15.7f);

    auto dbg_1 =  results["test_1"]["outputs"]["r13"].dump(2);
    res = results["test_1"]["outputs"]["r13"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, -330.7f);
};



TEST(emulator_manager_interactive, first_core_correct_restart) {

    std::string program_a = R"(
        ldc r42, 12.5000
        add r12, r42, r12
        stop
    )";

    std::string program_b = R"(
        ldc r43, 1.5000
        stop
    )";
    uint32_t n_steps = 2;

    auto spec = prepare_asm_spec({program_a, program_b}, n_steps, {12, 42}, 1);

    spec["cores"][1]["outputs"][0]["name"] = "r43";
    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 2);
    auto bp = manager.emulate();
    EXPECT_TRUE(bp.has_value());
    EXPECT_EQ(bp.value().breakpoint, 2);
    manager.remove_breakpoint("test_0", 2);

    manager.step_over();
    manager.step_over();
    manager.step_over();
    manager.step_over();
    manager.step_over();
    manager.continue_emulation();
    auto results = manager.get_results().dump(4);

    float res = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0][1];
    EXPECT_FLOAT_EQ(res, 25.f);
};


TEST(emulator_manager_interactive, continue_emulation_multichannel) {

    std::string program = R"(
        ldc r42, 12.5000
        add r12, r42, r12
        stop
    )";
    uint32_t n_steps = 2;

    auto spec = prepare_asm_spec({program}, n_steps, {12}, 2);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 2);
    auto bp_1 = manager.emulate();
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 2);
    manager.remove_breakpoint("test_0", 2);
    auto breakpoint = manager.continue_emulation();
    auto results = manager.get_results();
    auto test = results.dump(4);

    std::vector<float> expected =  {12.5, 25.00};
    std::vector<float> res_1 = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0];
    std::vector<float> res_2 = manager.get_results()["test_0"]["outputs"]["r12"]["1"][0];

    EXPECT_EQ(res_1, expected);
    EXPECT_EQ(res_2, expected);
}

TEST(emulator_manager_interactive, multichannel_cross_channel_stepover) {

    std::string program = R"(
        ldc r42, 12.5000
        add r12, r42, r12
        stop
    )";
    uint32_t n_steps = 2;

    auto spec = prepare_asm_spec({program}, n_steps, {12}, 2);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 2);
    auto bp_1 = manager.emulate();
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 2);
    manager.remove_breakpoint("test_0", 2);
    manager.step_over();
    auto breakpoint = manager.continue_emulation();
    auto results = manager.get_results();
    auto test = results.dump(4);

    std::vector<float> expected =  {12.5, 25.00};
    std::vector<float> res_0 = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0];
    std::vector<float> res_1 = manager.get_results()["test_0"]["outputs"]["r12"]["1"][0];

    EXPECT_EQ(res_0, expected);
    EXPECT_EQ(res_1, expected);
}

TEST(emulator_manager_interactive, multichannel_stepover_restart) {

    std::string program = R"(
        ldc r42, 12.5000
        add r12, r42, r12
        stop
    )";
    uint32_t n_steps = 2;

    auto spec = prepare_asm_spec({program}, n_steps, {12}, 2);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 1);
    auto bp_1 = manager.emulate();
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 1);
    manager.remove_breakpoint("test_0", 1);
    manager.step_over();
    auto breakpoint = manager.continue_emulation();
    auto results = manager.get_results();
    auto test = results.dump(4);

    std::vector<float> expected =  {12.5, 25.00};
    std::vector<float> res_0 = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0];
    std::vector<float> res_1 = manager.get_results()["test_0"]["outputs"]["r12"]["1"][0];

    EXPECT_EQ(res_0, expected);
    EXPECT_EQ(res_1, expected);
}



TEST(emulator_manager_interactive, multichannel_breakpoint) {

    std::string program = R"(
        ldc r42, 12.5000
        add r12, r42, r12
        stop
    )";
    uint32_t n_steps = 2;

    auto spec = prepare_asm_spec({program}, n_steps, {12}, 2);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.set_multichannel_debug(true);
    manager.process();
    manager.add_breakpoint("test_0", 1);
    auto bp = manager.emulate();
    EXPECT_TRUE(bp.has_value());
    EXPECT_EQ(bp.value().breakpoint, 1);
    EXPECT_EQ(bp.value().progress.channel, 0);
    EXPECT_EQ(bp.value().progress.current, 1);


    bp = manager.continue_emulation();
    EXPECT_EQ(bp.value().breakpoint, 1);
    EXPECT_EQ(bp.value().progress.channel, 1);
    EXPECT_EQ(bp.value().progress.current, 1);
    EXPECT_FALSE(bp.value().completed_round);
    manager.remove_breakpoint("test_0", 1);
    bp = manager.continue_emulation();
    EXPECT_TRUE(bp.value().completed_round);
    auto results = manager.get_results();

    std::vector<float> expected =  {12.5, 25.00};
    std::vector<float> res_0 = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0];
    std::vector<float> res_1 = manager.get_results()["test_0"]["outputs"]["r12"]["1"][0];

    EXPECT_EQ(res_0, expected);
    EXPECT_EQ(res_1, expected);
}


TEST(emulator_manager_interactive, disable_multichannel_debug) {

    std::string program = R"(
        ldc r42, 12.5000
        add r12, r42, r12
        stop
    )";
    uint32_t n_steps = 2;

    auto spec = prepare_asm_spec({program}, n_steps, {12}, 2);

    emulator_dispatcher manager;
    manager.set_specs(spec);
    manager.set_multichannel_debug(false);
    manager.process();
    manager.add_breakpoint("test_0", 1);
    auto bp = manager.emulate();
    EXPECT_TRUE(bp.has_value());
    EXPECT_EQ(bp.value().breakpoint, 1);
    EXPECT_EQ(bp.value().progress.channel, 0);
    EXPECT_EQ(bp.value().progress.current, 1);


    bp = manager.continue_emulation();

    EXPECT_EQ(bp.value().breakpoint, 1);
    EXPECT_EQ(bp.value().progress.channel, 0);
    EXPECT_EQ(bp.value().progress.current, 2);

    bp = manager.continue_emulation();
    EXPECT_TRUE(bp.value().completed_round);
    auto results = manager.get_results();

    std::vector<float> expected =  {12.5, 25.00};
    std::vector<float> res_0 = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0];
    std::vector<float> res_1 = manager.get_results()["test_0"]["outputs"]["r12"]["1"][0];

    EXPECT_EQ(res_0, expected);
    EXPECT_EQ(res_1, expected);
}