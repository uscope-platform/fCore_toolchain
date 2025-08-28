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
#include "data_structures/emulation/v2/specs/emulator_specs.hpp"
#include "frontend/schema_validators/schema_validator_base.h"

using namespace fcore::emulator_v2;
using namespace fcore;

TEST(emulator_schema, validation_success) {
    std::ifstream ifs("emu/schemas/valid_emulator_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(emulator_input, 2);
    EXPECT_NO_THROW(validator.validate(spec));
}

TEST(emulator_schema, validation_fail_no_cores) {
    std::ifstream ifs("emu/schemas/valid_emulator_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(emulator_input,2);
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
    schema_validator_base validator(emulator_input,2);
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
    schema_validator_base validator(compiler_input,2);
    EXPECT_NO_THROW(validator.validate(spec));

}


TEST(compiler_schema, validation_fail_no_input) {
    std::ifstream ifs("emu/schemas/valid_compiler_schema.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(compiler_input,2);
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
    schema_validator_base validator(emulator_input,2);
    EXPECT_NO_THROW(validator.validate(spec));

}

TEST(compiler_schema, validation_fail_ints_as_floats) {
    std::ifstream ifs("emu/schemas/msgpackd_schema_fail.json");
    nlohmann::json spec = nlohmann::json::parse(ifs);
    schema_validator_base validator(emulator_input,2);

    EXPECT_NO_THROW(validator.validate(spec));

    try{
        emulator_specs s;
        s.parse(spec);
        EXPECT_TRUE(false);
    } catch (std::runtime_error &e){
        std::string message = e.what();
        std::string correct_message = "Both rom and control addresses for core test should be integer like numbers";
        EXPECT_EQ(message, correct_message);
    }
}


TEST(emulator_schema, waveform_square_success) {
        nlohmann::json specs = nlohmann::json::parse(
                R"({
        "version": 2,
        "cores": [
            {
                "id": "producer",
                "order": 1,
                "inputs": [
                    {
                      "name": "input_2",
                      "is_vector": false,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"waveform",
                        "shape":"square",
                        "von": 21.1,
                        "voff": 21.1,
                        "tdelay": 21.1,
                        "period": 21.1,
                        "ton": 21.1
                      }
                    }
                ],
                "outputs": [],
                "memory_init": [],
                "deployment": {"rom_address": 0,"has_reciprocal": false,"control_address": 0},
                "channels": 1,
                "program": {"content": "void main(){\n  float mem, out;\n\n  mem += 1.0;\n  out = mem*2.0;\n}","headers": []},
                "options": {"comparators": "reducing","efi_implementation": "efi_trig"},
                "sampling_frequency": 1000
            }
        ],
        "interconnect": [],
        "emulation_time": 1,
        "deployment_mode": false
    })");
    schema_validator_base validator(emulator_input, 2);
    EXPECT_NO_THROW(validator.validate(specs));
}


TEST(emulator_schema, waveform_missing_shape_fail) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
        "version": 2,
        "cores": [
            {
                "id": "producer",
                "order": 1,
                "inputs": [
                    {
                      "name": "input_2",
                      "is_vector": false,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"waveform",
                        "von": 21.1,
                        "voff": 21.1,
                        "tdelay": 21.1,
                        "period": 21.1,
                        "ton": 21.1
                      }
                    }
                ],
                "outputs": [],
                "memory_init": [],
                "deployment": {"rom_address": 0,"has_reciprocal": false,"control_address": 0},
                "channels": 1,
                "program": {"content": "void main(){\n  float mem, out;\n\n  mem += 1.0;\n  out = mem*2.0;\n}","headers": []},
                "options": {"comparators": "reducing","efi_implementation": "efi_trig"},
                "sampling_frequency": 1000
            }
        ],
        "interconnect": [],
        "emulation_time": 1,
        "deployment_mode": false
    })");
    schema_validator_base validator(emulator_input,2);
    testing::internal::CaptureStderr();
    EXPECT_THROW(validator.validate(specs), std::invalid_argument);

    auto message = testing::internal::GetCapturedStderr();
    std::string correct_message = "Error #1\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Missing required property 'shape'.\nError #2\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Failed to validate against a conditional schema set by if-then-else constraints.\nError #3\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Failed to validate against child schema #2.\nError #4\n  context: <root>[cores][0][inputs][0]\n  desc:    Failed to validate against schema associated with property name 'source'.\nError #5\n  context: <root>[cores][0][inputs]\n  desc:    Failed to validate item #0 in array.\nError #6\n  context: <root>[cores][0]\n  desc:    Failed to validate against schema associated with property name 'inputs'.\nError #7\n  context: <root>[cores]\n  desc:    Failed to validate item #0 in array.\nError #8\n  context: <root>\n  desc:    Failed to validate against schema associated with property name 'cores'.\n";
    EXPECT_EQ(message, correct_message);
}


TEST(emulator_schema, waveform_missing_square_parameter_fail) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
        "version": 2,
        "cores": [
            {
                "id": "producer",
                "order": 1,
                "inputs": [
                    {
                      "name": "input_2",
                      "is_vector": false,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"waveform",
                        "shape":"square",
                        "voff": 21.1,
                        "tdelay": 21.1,
                        "period": 21.1,
                        "ton": 21.1
                      }
                    }
                ],
                "outputs": [],
                "memory_init": [],
                "deployment": {"rom_address": 0,"has_reciprocal": false,"control_address": 0},
                "channels": 1,
                "program": {"content": "void main(){\n  float mem, out;\n\n  mem += 1.0;\n  out = mem*2.0;\n}","headers": []},
                "options": {"comparators": "reducing","efi_implementation": "efi_trig"},
                "sampling_frequency": 1000
            }
        ],
        "interconnect": [],
        "emulation_time": 1,
        "deployment_mode": false
    })");
    schema_validator_base validator(emulator_input,2);
    testing::internal::CaptureStderr();
    EXPECT_THROW(validator.validate(specs), std::invalid_argument);

    auto message = testing::internal::GetCapturedStderr();
    std::string correct_message = "Error #1\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Missing required property 'von'.\nError #2\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Failed to validate against a conditional schema set by if-then-else constraints.\nError #3\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Failed to validate against child schema #3.\nError #4\n  context: <root>[cores][0][inputs][0]\n  desc:    Failed to validate against schema associated with property name 'source'.\nError #5\n  context: <root>[cores][0][inputs]\n  desc:    Failed to validate item #0 in array.\nError #6\n  context: <root>[cores][0]\n  desc:    Failed to validate against schema associated with property name 'inputs'.\nError #7\n  context: <root>[cores]\n  desc:    Failed to validate item #0 in array.\nError #8\n  context: <root>\n  desc:    Failed to validate against schema associated with property name 'cores'.\n";
    EXPECT_EQ(message, correct_message);
}


TEST(emulator_schema, waveform_sine) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
        "version": 2,
        "cores": [
            {
                "id": "producer",
                "order": 1,
                "inputs": [
                    {
                      "name": "input_2",
                      "is_vector": false,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"waveform",
                        "shape":"sine",
                        "dc_offset": 21.1,
                        "amplitude": 21.1,
                        "frequency": 21.1,
                        "phase": 21.1
                      }
                    }
                ],
                "outputs": [],
                "memory_init": [],
                "deployment": {"rom_address": 0,"has_reciprocal": false,"control_address": 0},
                "channels": 1,
                "program": {"content": "void main(){\n  float mem, out;\n\n  mem += 1.0;\n  out = mem*2.0;\n}","headers": []},
                "options": {"comparators": "reducing","efi_implementation": "efi_trig"},
                "sampling_frequency": 1000
            }
        ],
        "interconnect": [],
        "emulation_time": 1,
        "deployment_mode": false
    })");
    schema_validator_base validator(emulator_input, 2);
    EXPECT_NO_THROW(validator.validate(specs));
}


TEST(emulator_schema, waveform_sine_missing_parameter_fail) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
        "version": 2,
        "cores": [
            {
                "id": "producer",
                "order": 1,
                "inputs": [
                    {
                      "name": "input_2",
                      "is_vector": false,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"waveform",
                        "shape":"sine",
                        "amplitude": 21.1,
                        "frequency": 21.1,
                        "phase": 21.1
                      }
                    }
                ],
                "outputs": [],
                "memory_init": [],
                "deployment": {"rom_address": 0,"has_reciprocal": false,"control_address": 0},
                "channels": 1,
                "program": {"content": "void main(){\n  float mem, out;\n\n  mem += 1.0;\n  out = mem*2.0;\n}","headers": []},
                "options": {"comparators": "reducing","efi_implementation": "efi_trig"},
                "sampling_frequency": 1000
            }
        ],
        "interconnect": [],
        "emulation_time": 1,
        "deployment_mode": false
    })");
    schema_validator_base validator(emulator_input,2);
    testing::internal::CaptureStderr();
    EXPECT_THROW(validator.validate(specs), std::invalid_argument);

    auto message = testing::internal::GetCapturedStderr();
    std::string correct_message = "Error #1\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Missing required property 'dc_offset'.\nError #2\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Failed to validate against a conditional schema set by if-then-else constraints.\nError #3\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Failed to validate against child schema #5.\nError #4\n  context: <root>[cores][0][inputs][0]\n  desc:    Failed to validate against schema associated with property name 'source'.\nError #5\n  context: <root>[cores][0][inputs]\n  desc:    Failed to validate item #0 in array.\nError #6\n  context: <root>[cores][0]\n  desc:    Failed to validate against schema associated with property name 'inputs'.\nError #7\n  context: <root>[cores]\n  desc:    Failed to validate item #0 in array.\nError #8\n  context: <root>\n  desc:    Failed to validate against schema associated with property name 'cores'.\n";
    EXPECT_EQ(message, correct_message);
}


TEST(emulator_schema, waveform_triangle) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
        "version": 2,
        "cores": [
            {
                "id": "producer",
                "order": 1,
                "inputs": [
                    {
                      "name": "input_2",
                      "is_vector": false,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"waveform",
                        "shape":"triangle",
                        "dc_offset": 21.1,
                        "amplitude": 21.1,
                        "frequency": 21.1,
                        "phase": 21.1,
                        "duty": 0.3
                      }
                    }
                ],
                "outputs": [],
                "memory_init": [],
                "deployment": {"rom_address": 0,"has_reciprocal": false,"control_address": 0},
                "channels": 1,
                "program": {"content": "void main(){\n  float mem, out;\n\n  mem += 1.0;\n  out = mem*2.0;\n}","headers": []},
                "options": {"comparators": "reducing","efi_implementation": "efi_trig"},
                "sampling_frequency": 1000
            }
        ],
        "interconnect": [],
        "emulation_time": 1,
        "deployment_mode": false
    })");
    schema_validator_base validator(emulator_input, 2);
    EXPECT_NO_THROW(validator.validate(specs));
}


TEST(emulator_schema, waveform_triangle_missing_parameter_fail) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
        "version": 2,
        "cores": [
            {
                "id": "producer",
                "order": 1,
                "inputs": [
                    {
                      "name": "input_2",
                      "is_vector": false,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"waveform",
                        "shape":"triangle",
                        "dc_offset": 21.1,
                        "amplitude": 21.1,
                        "frequency": 21.1,
                        "phase": 21.1
                      }
                    }
                ],
                "outputs": [],
                "memory_init": [],
                "deployment": {"rom_address": 0,"has_reciprocal": false,"control_address": 0},
                "channels": 1,
                "program": {"content": "void main(){\n  float mem, out;\n\n  mem += 1.0;\n  out = mem*2.0;\n}","headers": []},
                "options": {"comparators": "reducing","efi_implementation": "efi_trig"},
                "sampling_frequency": 1000
            }
        ],
        "interconnect": [],
        "emulation_time": 1,
        "deployment_mode": false
    })");
    schema_validator_base validator(emulator_input,2);
    testing::internal::CaptureStderr();
    EXPECT_THROW(validator.validate(specs), std::invalid_argument);

    auto message = testing::internal::GetCapturedStderr();
    std::string correct_message = "Error #1\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Missing required property 'duty'.\nError #2\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Failed to validate against a conditional schema set by if-then-else constraints.\nError #3\n  context: <root>[cores][0][inputs][0][source]\n  desc:    Failed to validate against child schema #4.\nError #4\n  context: <root>[cores][0][inputs][0]\n  desc:    Failed to validate against schema associated with property name 'source'.\nError #5\n  context: <root>[cores][0][inputs]\n  desc:    Failed to validate item #0 in array.\nError #6\n  context: <root>[cores][0]\n  desc:    Failed to validate against schema associated with property name 'inputs'.\nError #7\n  context: <root>[cores]\n  desc:    Failed to validate item #0 in array.\nError #8\n  context: <root>\n  desc:    Failed to validate against schema associated with property name 'cores'.\n";
    EXPECT_EQ(message, correct_message);
}