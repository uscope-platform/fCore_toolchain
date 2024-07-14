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
#include "frontend/schema_validators/schema_validator_base.h"

std::string s_f = SCHEMAS_FOLDER;

TEST(emulator_schema, validation_success) {
    std::ifstream ifs("emu/schemas/valid_emulator_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    fcore::schema_validator_base validator(s_f+ "/emulator_spec_schema.json");
    EXPECT_NO_THROW(validator.validate(spec));
}

TEST(emulator_schema, validation_fail_no_cores) {
    std::ifstream ifs("emu/schemas/valid_emulator_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    fcore::schema_validator_base validator(s_f  + "/emulator_spec_schema.json");
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
    fcore::schema_validator_base validator(s_f  + "/emulator_spec_schema.json");
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
    fcore::schema_validator_base validator(s_f  + "/compiler_spec_schema.json");
    EXPECT_NO_THROW(validator.validate(spec));

}


TEST(compiler_schema, validation_fail_no_input) {
    std::ifstream ifs("emu/schemas/valid_compiler_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    fcore::schema_validator_base validator(s_f  + "/compiler_spec_schema.json");
    spec.erase("input_file");
    testing::internal::CaptureStderr();
    EXPECT_THROW(validator.validate(spec), std::invalid_argument);

    auto message = testing::internal::GetCapturedStderr();
    std::string correct_message = "Error #1\n  context: <root>\n  desc:    Missing required property 'input_file'.\n";
    EXPECT_EQ(message, correct_message);
}
