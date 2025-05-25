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
#include <fstream>
#include "data_structures/emulation/v1/specs/emulator_specs.hpp"
#include "frontend/schema_validators/schema_validator_base.h"

using namespace fcore::emulator;
using namespace fcore;

TEST(emulator_schema, validation_success) {
    std::ifstream ifs("emu/schemas/valid_emulator_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(emulator_input);
    EXPECT_NO_THROW(validator.validate(spec));
}

TEST(emulator_schema, validation_fail_no_cores) {
    std::ifstream ifs("emu/schemas/valid_emulator_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(emulator_input);
    spec.erase("cores");
    testing::internal::CaptureStderr();
    EXPECT_THROW(validator.validate(spec), std::invalid_argument);

    auto message = testing::internal::GetCapturedStderr();
    std::string correct_message = "Error #1\n  context: <root>\n  desc:    Missing required property 'cores'.\n";
    EXPECT_EQ(message, correct_message);
}

TEST(emulator_schema, validation_fail_no_program) {
    std::ifstream ifs("emu/schemas/valid_emulator_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(emulator_input);
    spec["cores"][0].erase("program");
    testing::internal::CaptureStderr();
    EXPECT_THROW(validator.validate(spec), std::invalid_argument);

    auto message = testing::internal::GetCapturedStderr();
    std::string correct_message = "Error #1\n  context: <root>[cores][0]\n  desc:    Missing required property 'program'.\nError #2\n  context: <root>[cores]\n  desc:    Failed to validate item #0 in array.\nError #3\n  context: <root>\n  desc:    Failed to validate against schema associated with property name 'cores'.\n";
    EXPECT_EQ(message, correct_message);
}


TEST(compiler_schema, validation_success) {
    std::ifstream ifs("emu/schemas/valid_compiler_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(compiler_input);
    EXPECT_NO_THROW(validator.validate(spec));

}


TEST(compiler_schema, validation_fail_no_input) {
    std::ifstream ifs("emu/schemas/valid_compiler_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(compiler_input);
    spec.erase("input_file");
    testing::internal::CaptureStderr();
    EXPECT_THROW(validator.validate(spec), std::invalid_argument);

    auto message = testing::internal::GetCapturedStderr();
    std::string correct_message = "Error #1\n  context: <root>\n  desc:    Missing required property 'input_file'.\n";
    EXPECT_EQ(message, correct_message);
}

TEST(compiler_schema, validation_success_ints_as_floats) {
    std::ifstream ifs("emu/schemas/msgpackd_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(emulator_input);
    EXPECT_NO_THROW(validator.validate(spec));

}

TEST(compiler_schema, validation_fail_ints_as_floats) {
    std::ifstream ifs("emu/schemas/msgpackd_schema_fail.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(emulator_input);

    EXPECT_NO_THROW(validator.validate(spec));

    try{
        fcore::emulator::emulator_specs s;
        s.set_specs(spec);
        EXPECT_TRUE(false);
    } catch (std::runtime_error &e){
        std::string message = e.what();
        std::string correct_message = "Both rom and control addresses for core test should be integer like numbers";
        EXPECT_EQ(message, correct_message);
    }


}

