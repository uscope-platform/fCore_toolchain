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
    std::vector<float> reference_1 = {1.0, 1.0, 2.0, 2.0};
    for (size_t i = 0; i < res_1.size(); i++) {
        EXPECT_EQ(res_1[i], reference_1[i]);
    }

    std::vector<float> res_2= res_obj["test_1"]["outputs"]["mem"]["0"][0];
    std::vector<float> reference_2 = {1.0, 2.0, 3.0, 4.0};
    for (size_t i = 0; i < res_2.size(); i++) {
        EXPECT_EQ(res_2[i], reference_2[i]);
    }

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
    std::vector<float> reference_1 = {1.0, 1.0, 3.0, 3.0};
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
    std::vector<float> reference_1 = {1.0, 1.0, 6.0, 6.0};
    for (size_t i = 0; i < res_1.size(); i++) {
        EXPECT_EQ(res_1[i], reference_1[i]);
    }

    std::vector<float> res_2= res_obj["test_1"]["outputs"]["mem"]["0"][0];
    std::vector<float> reference_2 = {1.0, 2.0, 8.0, 14.0};
    for (size_t i = 0; i < res_2.size(); i++) {
        EXPECT_EQ(res_2[i], reference_2[i]);
    }

}