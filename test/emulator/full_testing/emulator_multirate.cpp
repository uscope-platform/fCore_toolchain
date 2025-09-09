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

TEST(emulator_multirate, emulator_simple_multirate) {

    nlohmann::json specs = nlohmann::json::parse( R"(
        {
            "version": 2,
            "cores": [
                {
                    "id": "test_0",
                    "order": 1,
                    "inputs": [],
                    "outputs": [],
                    "memory_init": [
                        {
                            "name": "mem",
                            "is_vector": false,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": false
                            },
                            "is_output": true,
                            "is_input": false,
                            "value": 0
                        }
                    ],
                    "channels": 1,
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_sort"
                    },
                    "program": {
                        "content": "int main(){float mem; mem += 1.0;}",
                        "type": "c",
                        "headers": []
                    },
                    "sampling_frequency": 1,
                    "deployment": {
                        "has_reciprocal": false,
                        "control_address": 18316525568,
                        "rom_address": 17179869184
                    }
                },
                {
                    "id": "test_1",
                    "order": 2,
                    "inputs": [],
                    "outputs": [],
                    "memory_init": [
                        {
                            "name": "mem",
                            "is_vector": false,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": false
                            },
                            "is_output": true,
                            "is_input": false,
                            "value": 0
                        }
                    ],
                    "channels": 1,
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_sort"
                    },
                    "program": {
                        "content": "int main(){float mem; mem += 1.0;}",
                        "type": "c",
                        "headers": []
                    },
                    "sampling_frequency": 2,
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
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    auto dbg = res_obj.dump(4);

    std::vector<float> res_1 = res_obj["test_0"]["outputs"]["mem"]["0"][0];
    std::vector<float> reference_1 = {0.0, 1.0, 1.0, 2.0};
    for (size_t i = 0; i < res_1.size(); i++) {
        EXPECT_EQ(res_1[i], reference_1[i]);
    }

    std::vector<float> res_2= res_obj["test_1"]["outputs"]["mem"]["0"][0];
    std::vector<float> reference_2 = {1.0, 2.0, 3.0, 4.0};
    for (size_t i = 0; i < res_2.size(); i++) {
        EXPECT_EQ(res_2[i], reference_2[i]);
    }

    std::vector<double> tb = res_obj["timebase"];
    std::vector<double> tb_ref = {0, 0.5, 1, 1.5};
    ASSERT_EQ(tb.size(), 4);
    ASSERT_EQ(tb, tb_ref);
}


TEST(emulator_multirate, emulator_input_multirate) {

    nlohmann::json specs = nlohmann::json::parse( R"(
        {
            "version": 2,
            "cores": [
                {
                    "id": "test_0",
                    "order": 1,
                    "inputs": [
                        {
                            "name": "in",
                            "is_vector": false,
                            "metadata":{
                                "type": "float",
                                "width": 12,
                                "signed":true,
                                "common_io": false
                            },
                            "source": {
                                "type": "series",
                                "value": [1, 1000, 2, 2000]
                            }
                        }
                    ],
                    "outputs": [],
                    "memory_init": [
                        {
                            "name": "mem",
                            "is_vector": false,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": false
                            },
                            "is_output": true,
                            "is_input": false,
                            "value": 0
                        }
                    ],
                    "channels": 1,
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_sort"
                    },
                    "program": {
                        "content": "int main(){float mem; mem += in;}",
                        "type": "c",
                        "headers": []
                    },
                    "sampling_frequency": 1,
                    "deployment": {
                        "has_reciprocal": false,
                        "control_address": 18316525568,
                        "rom_address": 17179869184
                    }
                },
                {
                    "id": "test_1",
                    "order": 2,
                    "inputs": [
                        {
                            "name": "in",
                            "is_vector": false,
                            "metadata":{
                                "type": "float",
                                "width": 12,
                                "signed":true,
                                "common_io": false
                            },
                            "source": {
                                "type": "series",
                                "value": [1, 1, 2, 2]
                            }
                        }
                    ],
                    "outputs": [],
                    "memory_init": [
                        {
                            "name": "mem",
                            "is_vector": false,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": false
                            },
                            "is_output": true,
                            "is_input": false,
                            "value": 0
                        }
                    ],
                    "channels": 1,
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_sort"
                    },
                    "program": {
                        "content": "int main(){float mem; mem += in;}",
                        "type": "c",
                        "headers": []
                    },
                    "sampling_frequency": 2,
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
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    auto dbg = res_obj.dump(4);

    std::vector<float> res_1 = res_obj["test_0"]["outputs"]["mem"]["0"][0];
    std::vector<float> reference_1 = {0.0, 1000.0, 1000.0, 3000.0};
    for (size_t i = 0; i < res_1.size(); i++) {
        EXPECT_EQ(res_1[i], reference_1[i]);
    }

    std::vector<float> res_2= res_obj["test_1"]["outputs"]["mem"]["0"][0];
    std::vector<float> reference_2 = {1.0, 2.0, 4.0, 6.0};
    for (size_t i = 0; i < res_2.size(); i++) {
        EXPECT_EQ(res_2[i], reference_2[i]);
    }

}


TEST(emulator_multirate, emulator_interconnect_multirate) {

    nlohmann::json specs = nlohmann::json::parse( R"(
        {
            "version": 2,
            "cores": [
                {
                    "id": "test_0",
                    "order": 1,
                    "inputs": [
                        {
                            "name": "in",
                            "is_vector": false,
                            "metadata":{
                                "type": "float",
                                "width": 12,
                                "signed":true,
                                "common_io": false
                            },
                            "source": {
                                "type": "series",
                                "value": [1, 1, 5, 5]
                            }
                        }
                    ],
                    "outputs": [],
                    "memory_init": [
                        {
                            "name": "mem",
                            "is_vector": false,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": false
                            },
                            "is_output": true,
                            "is_input": false,
                            "value": 0
                        }
                    ],
                    "channels": 1,
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_sort"
                    },
                    "program": {
                        "content": "int main(){float mem; mem += in;}",
                        "type": "c",
                        "headers": []
                    },
                    "sampling_frequency": 1,
                    "deployment": {
                        "has_reciprocal": false,
                        "control_address": 18316525568,
                        "rom_address": 17179869184
                    }
                },
                {
                    "id": "test_1",
                    "order": 2,
                    "inputs": [
                        {
                            "name": "in",
                            "is_vector": false,
                            "metadata":{
                                "type": "float",
                                "width": 12,
                                "signed":true,
                                "common_io": false
                            },
                            "source": {
                                "type": "series",
                                "value": [1, 1, 2, 2]
                            }
                        }
                    ],
                    "outputs": [],
                    "memory_init": [
                        {
                            "name": "mem",
                            "is_vector": false,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": false
                            },
                            "is_output": true,
                            "is_input": false,
                            "value": 0
                        }
                    ],
                    "channels": 1,
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_sort"
                    },
                    "program": {
                        "content": "int main(){float mem; mem += in;}",
                        "type": "c",
                        "headers": []
                    },
                    "sampling_frequency": 2,
                    "deployment": {
                        "has_reciprocal": false,
                        "control_address": 18316525568,
                        "rom_address": 17179869184
                    }
                }
            ],
            "interconnect": [
                {
                    "source": "test_0.mem",
                    "destination":"test_1.in"
                }
            ],
            "emulation_time": 2,
            "deployment_mode": false
        }
    )");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    auto dbg = res_obj.dump(4);

    std::vector<float> res_1 = res_obj["test_0"]["outputs"]["mem"]["0"][0];
    std::vector<float> reference_1 = {1.0, 1.0, 1.0, 6.0};
    for (size_t i = 0; i < res_1.size(); i++) {
        EXPECT_EQ(res_1[i], reference_1[i]);
    }

    std::vector<float> res_2= res_obj["test_1"]["outputs"]["mem"]["0"][0];
    std::vector<float> reference_2 = {1.0, 2.0, 3.0,9.0};
    for (size_t i = 0; i < res_2.size(); i++) {
        EXPECT_EQ(res_2[i], reference_2[i]);
    }

}


TEST(emulator_multirate, multirate_interconnect_initializaiton) {

    nlohmann::json specs = nlohmann::json::parse( R"(
        {
            "version": 2,
            "cores": [
                {
                    "id": "fast_core",
                    "order": 2,
                    "inputs": [
                        {
                            "name": "input",
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io": false
                            },
                            "source": {
                                "type": "external",
                                "value": [
                                    40
                                ]
                            },
                            "vector_size": 1,
                            "is_vector": false
                        }
                    ],
                    "outputs": [
                        {
                            "name": "out",
                            "is_vector": false,
                            "vector_size": 1,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io": false
                            }
                        }
                    ],
                    "memory_init": [],
                    "deployment": {
                        "rom_address": 0,
                        "has_reciprocal": false,
                        "control_address": 0
                    },
                    "channels": 1,
                    "program": {
                        "content": "void main(){\n\n    //inputs\n    float random_in;\n    float gain;\n\n    float out = input + 20.4;\n\n      \n}\n",
                        "headers": []
                    },
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_trig"
                    },
                    "sampling_frequency": 100
                },
                {
                    "id": "slow_core",
                    "order": 1,
                    "inputs": [
                        {
                            "name": "input",
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io": false
                            },
                            "source": {
                                "type": "constant",
                                "value": [
                                    50
                                ]
                            },
                            "vector_size": 1,
                            "is_vector": false
                        }
                    ],
                    "outputs": [
                        {
                            "name": "out",
                            "is_vector": false,
                            "vector_size": 1,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io": false
                            }
                        }
                    ],
                    "memory_init": [],
                    "deployment": {
                        "rom_address": 0,
                        "has_reciprocal": false,
                        "control_address": 0
                    },
                    "channels": 1,
                    "program": {
                        "content": "void main(){\n\n    //inputs\n    float random_in;\n    float gain;\n\n    float out = input + 20.4;\n\n      \n}\n",
                        "headers": []
                    },
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_trig"
                    },
                    "sampling_frequency": 50
                }
            ],
            "interconnect": [
                {
                    "source": "slow_core.out",
                    "source_channel": -1,
                    "destination": "fast_core.input",
                    "destination_channel": -1
                }
            ],
            "emulation_time": 0.025,
            "deployment_mode": false
        }
    )");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    auto dbg = res_obj.dump(4);

    std::vector<float> res_1 = res_obj["fast_core"]["outputs"]["out"]["0"][0];
    std::vector<float> reference_1 = {60.4, 90.8, 90.8};
    for (size_t i = 0; i < res_1.size(); i++) {
        EXPECT_EQ(res_1[i], reference_1[i]);
    }

    std::vector<float> res_2= res_obj["slow_core"]["outputs"]["out"]["0"][0];
    std::vector<float> reference_2 = {40.0, 70.4, 70.4};
    for (size_t i = 0; i < res_2.size(); i++) {
        EXPECT_EQ(res_2[i], reference_2[i]);
    }

}

TEST(emulator_multirate, multirate_multichannel_interconnect_initializaiton) {

    nlohmann::json specs = nlohmann::json::parse( R"(
        {
            "version": 2,
            "cores": [
                {
                    "id": "fast_core",
                    "order": 2,
                    "inputs": [
                        {
                            "name": "input",
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io": false
                            },
                            "source": {
                                "type": "external",
                                "value": [
                                    32,
                                    64
                                ]
                            },
                            "vector_size": 1,
                            "is_vector": false
                        }
                    ],
                    "outputs": [
                        {
                            "name": "out",
                            "is_vector": false,
                            "vector_size": 1,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io": false
                            }
                        }
                    ],
                    "memory_init": [],
                    "deployment": {
                        "rom_address": 0,
                        "has_reciprocal": false,
                        "control_address": 0
                    },
                    "channels": 2,
                    "program": {
                        "content": "void main(){\n\n    //inputs\n    float random_in;\n    float gain;\n\n    float out = input + 20.4;\n\n      \n}\n",
                        "headers": []
                    },
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_trig"
                    },
                    "sampling_frequency": 100
                },
                {
                    "id": "slow_core",
                    "order": 1,
                    "inputs": [
                        {
                            "name": "input",
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io": false
                            },
                            "source": {
                                "type": "constant",
                                "value": [
                                    50
                                ]
                            },
                            "vector_size": 1,
                            "is_vector": false
                        }
                    ],
                    "outputs": [
                        {
                            "name": "out",
                            "is_vector": false,
                            "vector_size": 1,
                            "metadata": {
                                "type": "float",
                                "width": 32,
                                "signed": true,
                                "common_io": false
                            }
                        }
                    ],
                    "memory_init": [],
                    "deployment": {
                        "rom_address": 0,
                        "has_reciprocal": false,
                        "control_address": 0
                    },
                    "channels": 2,
                    "program": {
                        "content": "void main(){\n\n    //inputs\n    float random_in;\n    float gain;\n\n    float out = input + 20.4;\n\n      \n}\n",
                        "headers": []
                    },
                    "options": {
                        "comparators": "reducing",
                        "efi_implementation": "efi_trig"
                    },
                    "sampling_frequency": 50
                }
            ],
            "interconnect": [
                {
                    "source": "slow_core.out",
                    "source_channel": -1,
                    "destination": "fast_core.input",
                    "destination_channel": -1
                }
            ],
            "emulation_time": 0.025,
            "deployment_mode": false
        }
    )");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    auto dbg = res_obj.dump(4);

    std::vector<float> res_1 = res_obj["fast_core"]["outputs"]["out"]["0"][0];
    std::vector<float> reference_1 = {52.4, 90.8, 90.8};
    for (size_t i = 0; i < res_1.size(); i++) {
        EXPECT_EQ(res_1[i], reference_1[i]);
    }

    res_1 = static_cast<std::vector<float>>(res_obj["fast_core"]["outputs"]["out"]["1"][0]);
    reference_1 = {84.4, 90.8, 90.8};
    for (size_t i = 0; i < res_1.size(); i++) {
        EXPECT_EQ(res_1[i], reference_1[i]);
    }

    std::vector<float> res_2= res_obj["slow_core"]["outputs"]["out"]["0"][0];
    std::vector<float> reference_2 = {32.0, 70.4, 70.4};
    for (size_t i = 0; i < res_2.size(); i++) {
        EXPECT_EQ(res_2[i], reference_2[i]);
    }

    res_2 = static_cast<std::vector<float>>(res_obj["slow_core"]["outputs"]["out"]["1"][0]);
    reference_2 = {64.0, 70.4, 70.4};
    for (size_t i = 0; i < res_2.size(); i++) {
        EXPECT_EQ(res_2[i], reference_2[i]);
    }
}

