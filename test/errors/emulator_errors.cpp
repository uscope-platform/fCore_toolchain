// Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#include "result_helpers.hpp"
#include "emulator/emulator_dispatcher.hpp"
#include "emulator/v2/emulator_manager.hpp"

using namespace fcore;

namespace {
    /// A single core running a small assembly program
    nlohmann::json load_valid_spec() {
        return nlohmann::json::parse(R"({
            "version": 2,
            "cores": [
                {
                    "id": "test",
                    "order": 1,
                    "inputs": [],
                    "outputs": [
                        {
                            "name": "r12",
                            "is_vector": false,
                            "metadata":{"suggested_address": 12, "type": "float", "width": 12, "signed":true, "common_io": false}
                        }
                    ],
                    "memory_init": [],
                    "channels": 1,
                    "options": {"comparators": "reducing", "efi_implementation": "none"},
                    "program": {
                        "content": "ldc r42, 12.5000\nldc r3, 3.2000\nnop\nadd r3, r42, r12\nnop\nnop\nnop\nnop\nnop\nnop\nstop\n",
                        "type":"asm",
                        "headers": []
                    },
                    "sampling_frequency": 1,
                    "deployment": {"has_reciprocal": false, "control_address": 18316525568, "rom_address": 17179869184}
                }
            ],
            "interconnect": [],
            "emulation_time": 1,
            "deployment_mode": false
        })");
    }
}

TEST(emulator_errors, dispatcher_without_specs_rejects_every_call) {
    emulator_dispatcher dispatcher;

    auto processed = dispatcher.process();
    ASSERT_FALSE(processed);
    EXPECT_EQ(processed.error().code, error_code::invalid_argument);

    EXPECT_FALSE(dispatcher.emulate());
    EXPECT_FALSE(dispatcher.step_over());
    EXPECT_FALSE(dispatcher.get_results());
    EXPECT_FALSE(dispatcher.add_breakpoint("core", 1));
}

TEST(emulator_errors, version_one_specs_are_not_supported) {
    emulator_dispatcher dispatcher;
    auto outcome = dispatcher.set_specs(nlohmann::json{{"version", 1}});
    ASSERT_FALSE(outcome);
    EXPECT_EQ(outcome.error().code, error_code::not_supported);
    EXPECT_EQ(outcome.error().message, "Emulator schema version 1 is no longer supported");
}

TEST(emulator_errors, specs_without_a_valid_version_are_rejected) {
    emulator_dispatcher dispatcher;

    auto missing = dispatcher.set_specs(nlohmann::json{{"cores", nlohmann::json::array()}});
    ASSERT_FALSE(missing);
    EXPECT_EQ(missing.error().code, error_code::spec_error);

    auto unknown = dispatcher.set_specs(nlohmann::json{{"version", 7}});
    ASSERT_FALSE(unknown);
    EXPECT_EQ(unknown.error().code, error_code::spec_error);
}

TEST(emulator_errors, invalid_schema_is_a_schema_error_with_the_violations) {
    auto spec = load_valid_spec();
    spec.erase("cores");

    emulator_dispatcher dispatcher;
    auto outcome = dispatcher.set_specs(spec);
    ASSERT_FALSE(outcome);
    EXPECT_EQ(outcome.error().code, error_code::schema_validation);
    EXPECT_NE(outcome.error().message.find("Missing required property 'cores'"), std::string::npos);
}

TEST(emulator_errors, debugging_an_unknown_core_fails) {
    emulator_v2::emulator_manager manager;
    ASSERT_TRUE(manager.set_specs(load_valid_spec()));
    ASSERT_TRUE(manager.process());

    auto added = manager.add_breakpoint("there_is_no_such_core", 3);
    ASSERT_FALSE(added);
    EXPECT_EQ(added.error().code, error_code::invalid_argument);
    EXPECT_FALSE(manager.remove_breakpoint("there_is_no_such_core", 3));
    EXPECT_FALSE(manager.dump_memory("there_is_no_such_core", 0));
    EXPECT_FALSE(manager.get_inputs("there_is_no_such_core"));
}

TEST(emulator_errors, a_valid_spec_runs_to_completion) {
    emulator_v2::emulator_manager manager;
    ASSERT_TRUE(manager.set_specs(load_valid_spec()));
    ASSERT_TRUE(manager.process());
    auto outcome = manager.emulate();
    ASSERT_TRUE(outcome);
    EXPECT_FALSE(outcome.value().has_value());
    EXPECT_TRUE(manager.get_results());
}
