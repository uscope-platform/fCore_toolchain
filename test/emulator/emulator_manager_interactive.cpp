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
#include "emulator/emulator_manager.hpp"

using namespace fcore;


nlohmann::json prepare_asm_spec(std::vector<std::string> pv, uint32_t n_steps, std::vector<uint32_t> output_regs){

    nlohmann::json spec;
    spec["cores"] = std::vector<nlohmann::json>();
    spec["emulation_time"] = n_steps;

    for(int i = 0; i< pv.size(); i++){
        auto cs = nlohmann::json();

        cs["order"] = i+1;
        cs["id"] = "test_" + std::to_string(i);

        cs["program"] = nlohmann::json();
        cs["program"]["headers"] = std::vector<std::string>();
        cs["program"]["content"] = pv[i];
        cs["channels"] = 1;
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
            out["metadata"]["width"] = j;
            out["metadata"]["signed"] = true;
            out["reg_n"] = std::vector<uint32_t>();
            out["reg_n"].push_back(j);
            out["type"] = "float";
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

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42});

    emulator_manager manager;
    manager.set_specs(spec);
    manager.process();
    manager.emulate(true);
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

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42});

    emulator_manager manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 2);
    auto breakpoint = manager.emulate(true);
    EXPECT_TRUE(breakpoint.has_value());

    auto result = breakpoint.value();


    debug_checkpoint expected;
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

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42});

    emulator_manager manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 2);
    auto bp_1 = manager.emulate(true);
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 2);
    auto breakpoint = manager.continue_emulation();
    EXPECT_TRUE(breakpoint.has_value());
    auto result = breakpoint.value();


    debug_checkpoint expected;
    expected.status = "complete";
    expected.core_name = "test_0";
    expected.breakpoint = 3;
    expected.next_program = "";
    expected.completed_round = true;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.period = 1;
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

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42});

    emulator_manager manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 2);
    auto bp_1 = manager.emulate(true);
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

    auto spec = prepare_asm_spec({program}, n_steps, {12, 42});

    emulator_manager manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 3);
    auto bp_1 = manager.emulate(true);
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
        ldc r42, 1.5000
        ldc r3, 332.2000
        sub r42, r3, r12
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program_a, program_b}, n_steps, {12, 42});

    emulator_manager manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 3);
    auto bp_1 = manager.emulate(true);
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 3);
    manager.remove_breakpoint("test_0", 3);
    auto breakpoint = manager.continue_emulation();

    debug_checkpoint expected;
    expected.status = "complete";
    expected.core_name = "test_0";
    expected.next_program = "";
    expected.breakpoint = 4;
    expected.completed_round = true;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.current = 2;
    expected.progress.total_steps = 1;
    expected.progress.period = 1;

    EXPECT_EQ(expected, breakpoint);
    auto dbg = manager.get_results().dump(4);
    auto results = manager.get_results();

    float res = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, 15.7f);

     res = manager.get_results()["test_1"]["outputs"]["r12"]["0"][0][0];
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
        ldc r42, 1.5000
        ldc r3, 332.2000
        sub r42, r3, r12
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program_a, program_b}, n_steps, {12, 42});

    emulator_manager manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_1", 3);
    auto bp_1 = manager.emulate(true);
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().core_name, "test_1");
    EXPECT_EQ(bp_1.value().breakpoint, 3);
    manager.remove_breakpoint("test_1", 3);
    auto breakpoint = manager.continue_emulation();

    debug_checkpoint expected;
    expected.status = "complete";
    expected.core_name = "test_0";
    expected.next_program = "";
    expected.breakpoint = 4;
    expected.completed_round = true;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.current = 3;
    expected.progress.total_steps = 1;
    expected.progress.period = 1;

    EXPECT_EQ(expected, breakpoint);
    auto dbg = manager.get_results().dump(4);
    auto results = manager.get_results();

    float res = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, 15.7f);

    res = manager.get_results()["test_1"]["outputs"]["r12"]["0"][0][0];
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
        ldc r42, 1.5000
        ldc r3, 332.2000
        sub r42, r3, r12
        stop
    )";
    uint32_t n_steps = 1;

    auto spec = prepare_asm_spec({program_a, program_b}, n_steps, {12, 42});

    emulator_manager manager;
    manager.set_specs(spec);
    manager.process();
    manager.add_breakpoint("test_0", 3);
    auto bp_1 = manager.emulate(true);
    EXPECT_TRUE(bp_1.has_value());
    EXPECT_EQ(bp_1.value().breakpoint, 3);
    manager.remove_breakpoint("test_0", 3);
    manager.step_over();
    auto breakpoint = manager.continue_emulation();


    debug_checkpoint expected;
    expected.status = "complete";
    expected.core_name = "test_0";
    expected.next_program = "";
    expected.breakpoint = 4;
    expected.completed_round = true;
    expected.memory_view.resize(64, 0);
    expected.memory_view[3] = 0x404ccccd;
    expected.memory_view[12] = 0x417b3333;
    expected.memory_view[42] = 0x41480000;
    expected.progress.current = 2;
    expected.progress.total_steps = 1;
    expected.progress.period = 1;

    EXPECT_EQ(expected, breakpoint);
    auto dbg = manager.get_results().dump(4);
    auto results = manager.get_results();

    float res = manager.get_results()["test_0"]["outputs"]["r12"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, 15.7f);

    res = manager.get_results()["test_1"]["outputs"]["r12"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, -330.7f);
};


