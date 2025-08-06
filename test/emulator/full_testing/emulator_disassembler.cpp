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
#include <nlohmann/json.hpp>
#include <fstream>

#include "emulator/emulator_dispatcher.hpp"

using namespace fcore;
using namespace fcore::emulator_v2;


TEST(emulator_disassembler, emulator_disassemble) {


    nlohmann::json specs = nlohmann::json::parse(
    R"({
    "version": 2,
    "cores": [
        {
            "order": 1,
            "id": "test_producer",
            "channels":2,
            "options":{
                "comparators": "full",
                "efi_implementation":"none"
            },
            "sampling_frequency":1,
            "inputs":[
                {
                    "name": "input_1",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "source":{"type": "constant","value": [31.2, 32.7]}
                },
                {
                    "name": "input_2",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "source":{"type": "constant","value": [31.2, 32.7]}
                }
            ],
            "outputs":[
                {
                    "name":"out",
                    "is_vector": false,
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                    }
                }
            ],
            "memory_init":[],
            "program": {
                "content": "int main(){\n  float input_1;\n  float input_2;\n  float out = input_1 + input_2;\n}",
                "headers": []
            },
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
            }
        },
        {
            "order": 2,
            "id": "test_reducer",
            "channels":1,
            "options":{
                "comparators": "full",
                "efi_implementation":"none"
            },
            "sampling_frequency":1,
            "inputs":[
                {
                    "name": "input_data_1",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "source":{"type": "constant","value": [31.2, 32.7]}
                },
                {
                    "name": "input_data_2",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "source":{"type": "constant","value": [31.2, 32.7]}
                }
            ],
            "outputs":[
                {
                    "name":"out",
                    "is_vector": false,
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                    }
                }
            ],
            "memory_init":[],
            "program": {
                "content": "int main(){\n    float input_data_1, input_data_2; \n    float out = input_data_1 * input_data_2;\n}\n",
                "headers": []
            },
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
            }
        }
    ],
    "interconnect": [],
    "emulation_time": 1,
    "deployment_mode": false
})");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    auto execs = manager.get_programs();
    auto res = manager.disassemble();


    std::unordered_map<uint16_t, translation_table_entry> producer_io = {{2,{"out", 3}},{3,{"input_2",1}}, {4,{"input_1",2}}};
    std::unordered_map<uint16_t, translation_table_entry> producer_common_io = {};
    disassembled_program producer_reference = {producer_io,producer_common_io, "add r2, r1, r3\nstop\n"};

    std::unordered_map<uint16_t, translation_table_entry> reducer_io = {{1,{"out",3}},{3,{"input_data_2",2}}, {4,{"input_data_1",1}}};
    std::unordered_map<uint16_t, translation_table_entry> reducer_common_io = {};
    disassembled_program reducer_reference = {reducer_io,reducer_common_io, "mul r1, r2, r3\nstop\n"};


    EXPECT_EQ(res["test_producer"].program, producer_reference.program);
    EXPECT_EQ(res["test_producer"].translation_table, producer_reference.translation_table);
    EXPECT_EQ(res["test_reducer"].program, reducer_reference.program);
    EXPECT_EQ(res["test_reducer"].translation_table, reducer_reference.translation_table);


}


TEST(emulator_disassembler, emulator_disassemble_common_io) {


    nlohmann::json specs = nlohmann::json::parse( R"(
        {
            "version":2,
            "cores": [
                {
                    "id": "test",
                    "order": 1,
                    "inputs": [
                        {
                            "name": "input_1",
                            "is_vector": false,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io":true
                            },
                            "source": {
                                "type": "constant",
                                "value": [
                                    31.2
                                ]
                            }
                        },
                        {
                            "name": "input_2",
                            "is_vector": false,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io":true
                            },
                            "source": {
                                "type": "constant",
                                "value": [
                                    4
                                ]
                            }
                        }
                    ],
                    "outputs": [
                        {
                            "name": "out",
                            "is_vector": false,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io":false
                            }
                        }
                    ],
                    "memory_init": [],
                    "channels": 2,
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "none"
                    },
                    "program": {
                        "content": "int main(){\n  float input_1;\n  float input_2;\n  float out = input_1 + input_2;\n}",
                        "headers": []
                    },
                    "sampling_frequency": 1,
                    "deployment": {
                        "has_reciprocal": false,
                        "control_address": 18316525568,
                        "rom_address": 17179869184
                    }
                }
            ],
            "interconnect": [],
            "emulation_time": 2,
            "deployment_mode": false
        }
    )");



    emulator_dispatcher manager;
    manager.set_specs(specs);
    auto execs = manager.get_programs();
    auto res = manager.disassemble();

    std::unordered_map<uint16_t, translation_table_entry> io = {{1,{"out", 1}}};
    std::unordered_map<uint16_t, translation_table_entry> common_io = {{2, {"input_2",2}}, {3, {"input_1",1}}};
    disassembled_program test_reference = {io,common_io, "add r1c, r2c, r1\nstop\n"};

    EXPECT_EQ(res["test"].program, test_reference.program);
    EXPECT_EQ(res["test"].translation_table, test_reference.translation_table);
    EXPECT_EQ(res["test"].common_io_translation_table, test_reference.common_io_translation_table);


}

