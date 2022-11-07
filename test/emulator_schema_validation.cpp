//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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
// limitations under the License.05/07/2021.

#include <gtest/gtest.h>
#include <fstream>
#include <frontend/emulator_schema_validator.h>

TEST(emulator_schema, validation_success) {
    std::ifstream ifs("emu/schemas/valid_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    emulator_schema_validator validator;
    EXPECT_NO_THROW(validator.validate(spec));

}

TEST(emulator_schema, validation_fail_no_cores) {
    std::ifstream ifs("emu/schemas/valid_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    emulator_schema_validator validator;
    spec.erase("cores");
    testing::internal::CaptureStdout();
    EXPECT_THROW(validator.validate(spec), std::invalid_argument);

    auto raw_message = testing::internal::GetCapturedStdout();
    std::string error = raw_message.substr(raw_message.find("[critical]"));
    std::string correct_message = "[critical] emulator specification file error:\n\tError location: /\n\tError message: required property 'cores' not found in object\n";
    EXPECT_EQ(error, correct_message);
}

TEST(emulator_schema, validation_fail_no_program) {
    std::ifstream ifs("emu/schemas/valid_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    emulator_schema_validator validator;
    spec["cores"][0].erase("program");
    testing::internal::CaptureStdout();
    EXPECT_THROW(validator.validate(spec), std::invalid_argument);

    auto raw_message = testing::internal::GetCapturedStdout();
    std::string error = raw_message.substr(raw_message.find("[critical]"), raw_message.length()-1);

    std::string correct_message = "[critical] emulator specification file error:\n\tError location: /cores/0\n\tError message: required property 'program' not found in object\n";
    EXPECT_EQ(error, correct_message);
}