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

#include "../emulator_test_helpers.hpp"
#include "emulator/emulator_dispatcher.hpp"

using namespace fcore;
using namespace fcore::emulator_v2;

TEST(emulator_multichannel, emulator_partial_memory_to_memory) {

    nlohmann::json specs = nlohmann::json::parse( R"(
    {
      "version": 2,
      "cores": [
        {
          "id": "test_producer",
          "inputs": [
            {
                "name": "in_c",
                "is_vector": false,
                "metadata":{
                    "type": "float",
                    "width": 12,
                    "signed":true,
                    "common_io": false
                },
                "source": {
                    "type": "constant",
                    "value": [5,1]
                }
            }
          ],
          "order": 1,
          "outputs": [
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
          "program":{
            "content": "void main(){float mem; mem += in_c; float out = mem*1.0;}",
            "headers": []
          },
          "memory_init": [
            {
              "name": "mem",
              "is_vector": false,
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "is_output": true,
              "is_input": true,
              "value": 0
            }
          ],
          "options":{
            "comparators":"reducing",
            "efi_implementation":"efi_sort"
          },
          "channels":2,
          "sampling_frequency": 1,
          "deployment": {
            "has_reciprocal": false,
            "control_address": 18316525568,
            "rom_address": 17179869184
          }
        }
      ],
      "interconnect":[
        {
          "source": "test_producer.mem",
          "source_channel":0,
          "destination": "test_producer.mem",
          "destination_channel": 1
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
    auto res = manager.get_results()["test_producer"];

    auto dbg = manager.get_results().dump(4);

    std::vector<float> reference_0 = {5, 10};
    std::vector<float> result_0 = res["outputs"]["out"]["0"][0];
    for(int i =0; i<2; i++) {
        ASSERT_FLOAT_EQ(result_0[i], reference_0[i]);
    }
    std::vector<float> reference_1 = {1, 6};
    std::vector<float> result_1 = res["outputs"]["out"]["1"][0];
    for(int i =0; i<2; i++) {
        ASSERT_FLOAT_EQ(result_1[i], reference_1[i]);
    }

    std::vector<float> reference_2 = {5, 10};
    std::vector<float> result_2 = res["outputs"]["mem"]["0"][0];
    for(int i =0; i<2; i++) {
        ASSERT_FLOAT_EQ(result_2[i], reference_2[i]);
    }
    std::vector<float> reference_3 = {1, 6};
    std::vector<float> result_3 = res["outputs"]["mem"]["1"][0];
    for(int i =0; i<2; i++) {
        ASSERT_FLOAT_EQ(result_3[i], reference_3[i]);
    }
}

TEST(emulator_multichannel, emulator_multichannel) {

    nlohmann::json specs = nlohmann::json::parse(
            R"({
    "version": 2,
    "cores": [
        {
            "id": "test",
            "order": 1,
            "inputs": [
                {
                    "name": "input_1",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io":false
                    },
                    "source": {
                        "type": "constant",
                        "value": [
                            31.2,
                            32.7,
                            62.1,
                            64
                        ]
                    }
                },
                {
                    "name": "input_2",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io":false
                    },
                    "source": {
                        "type": "constant",
                        "value": [
                            4,
                            2,
                            6,
                            12
                        ]
                    }
                }
            ],
            "outputs": [
                {
                    "name": "out",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    }
                }
            ],
            "memory_init": [],
            "channels": 4,
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
})");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    std::vector<float> res = res_obj["test"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 35.2);
    ASSERT_FLOAT_EQ(res[1], 35.2);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 34.7);
    ASSERT_FLOAT_EQ(res[1], 34.7);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["2"][0];
    ASSERT_FLOAT_EQ(res[0], 68.1);
    ASSERT_FLOAT_EQ(res[1], 68.1);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["3"][0];
    ASSERT_FLOAT_EQ(res[0], 76.0);
    ASSERT_FLOAT_EQ(res[1], 76.0);
}

TEST(emulator_multichannel, emulator_multichannel_mem_init) {

    nlohmann::json specs = nlohmann::json::parse(
            R"({
    "version": 2,
    "cores": [
        {
            "id": "test",
            "order": 1,
            "inputs": [],
            "outputs": [
                {
                    "name": "out",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    }
                }
            ],
            "memory_init": [
                {
                    "name": "mem",
                    "vector_size": 1,
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": true
                    },
                    "is_output": true,
                    "is_input": false,
                    "is_vector": false,
                    "value": [
                        100.0,
                        500.0
                    ]
                }
            ],
            "channels": 2,
            "options": {
                "comparators": "reducing",
                "efi_implementation": "none"
            },
            "program": {
                "content": "int main(){\n  float out = mem*2.5;\n mem += 0.1;\n}",
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
})");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();
    auto dbg = res_obj.dump();
    std::vector<float> res = res_obj["test"]["outputs"]["mem"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 100.1);
    ASSERT_FLOAT_EQ(res[1], 100.2);
    res =  static_cast<std::vector<float>>(res_obj["test"]["outputs"]["mem"]["1"][0]);
    ASSERT_FLOAT_EQ(res[0], 500.1);
    ASSERT_FLOAT_EQ(res[1], 500.2);
    res =  static_cast<std::vector<float>>(res_obj["test"]["outputs"]["out"]["0"][0]);
    ASSERT_FLOAT_EQ(res[0], 250.0);
    ASSERT_FLOAT_EQ(res[1], 250.25);
    res = static_cast<std::vector<float>>(res_obj["test"]["outputs"]["out"]["1"][0]);
    ASSERT_FLOAT_EQ(res[0], 1250.0);
    ASSERT_FLOAT_EQ(res[1], 1250.25);
}

TEST(emulator_multichannel, emulator_multichannel_input_file) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
    "version": 2,
    "cores": [
        {
            "order": 1,
            "id": "test",
            "channels":4,
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
                    "source":{
                        "type": "series",
                        "value": [[31.2,31.3], [32.7,32.8], [62.1,62.2], [64.0,64.1]]
                    }
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
                    "source":{
                        "type": "constant",
                        "value": [4.0, 2.0, 6.0, 12.0]
                    }
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
                "content": "int main(){float input_1;float input_2;float out = input_1 + input_2;}",
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
    "emulation_time": 2,
    "deployment_mode": false
}
)");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();


    std::vector<float> res = res_obj["test"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 35.2);
    ASSERT_FLOAT_EQ(res[1], 35.3);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 34.7);
    ASSERT_FLOAT_EQ(res[1], 34.8);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["2"][0];
    ASSERT_FLOAT_EQ(res[0], 68.1);
    ASSERT_FLOAT_EQ(res[1], 68.2);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["3"][0];
    ASSERT_FLOAT_EQ(res[0], 76.0);
    ASSERT_FLOAT_EQ(res[1], 76.1);
}

TEST(emulator_multichannel, emulator_multichannel_gather_transfer) {


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
                  "name": "input_data",
                  "is_vector": true,
                  "vector_size": 2,
                  "metadata": {
                    "type": "float",
                    "width": 32,
                    "signed": false,
                    "common_io": false
                  },
                  "source": {
                    "type":"external",
                    "value":[0]
                  }
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
                "content": "int main(){\n    float input_data[2];\n    float out = input_data[0] + input_data[1];\n}\n",
                "headers": []
            },
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
            }
        }
    ],
    "interconnect": [
        {
          "source": "test_producer.out",
          "destination": "test_reducer.input_data"
        }
    ],
    "emulation_time": 1,
    "deployment_mode": false
})");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();
    auto dbg = res_obj.dump(4);
    std::vector<float> res = res_obj["test_producer"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 62.4);
    res = (std::vector<float>) res_obj["test_producer"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 65.4);
    res = (std::vector<float>) res_obj["test_reducer"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 127.8);
}

TEST(emulator_multichannel, emulator_multichannel_scatter_transfer) {


    nlohmann::json specs = nlohmann::json::parse(
    R"({
    "version": 2,
        "cores": [
            {
                "order": 1,
                "id": "test_producer",
                "channels":1,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "inputs":[],
                "outputs":[
                    {
                        "name":"out",
                        "is_vector": true,
                        "vector_size":2,
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": false,
                            "common_io": false
                        }
                    }],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float out[2] = {15.6, 17.2};\n}",
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
                "id": "test_consumer",
                "channels":2,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "inputs":[
                    {
                      "name": "input",
                      "is_vector": false,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"external",
                        "value":[0]
                      }
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
                    "content": "int main(){\n  float input;float out = input*3.5;\n}",
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            }
        ],
        "interconnect": [
            {
              "source": "test_producer.out",
              "destination": "test_consumer.input"
            }
        ],
        "emulation_time": 1,
    "deployment_mode": false
    })");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    auto res = (std::vector<float>) res_obj["test_consumer"]["outputs"]["out"]["0"][0];

    ASSERT_FLOAT_EQ(res[0], 54.6);
    res = (std::vector<float>) res_obj["test_consumer"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 60.2);
}

TEST(emulator_multichannel, emulator_multichannel_vector_transfer) {
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
                "id": "test_consumer",
                "channels":2,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "inputs":[
                    {
                      "name": "input",
                      "is_vector": false,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"external",
                        "value":[0]
                      }
                    }],
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
                    "content": "int main(){\n  float input;float out = input*3.5;\n}",
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            }
        ],
        "interconnect": [
            {
              "source": "test_producer.out",
              "destination": "test_consumer.input"
            }
        ],
        "emulation_time": 1,
    "deployment_mode": false
    })");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    auto res = (std::vector<float>) res_obj["test_consumer"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 218.4);
    res = (std::vector<float>) res_obj["test_consumer"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 228.9);

}

TEST(emulator_multichannel, emulator_multichannel_2d_vector_transfer) {
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
                "inputs":[],
                "outputs":[
                    {
                        "name":"out",
                        "is_vector": true,
                        "vector_size": 2,
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": false,
                            "common_io": false
                        }
                    }],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float out[2] = {15.6, 17.2};\n}",
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
                "id": "test_consumer",
                "channels":2,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "inputs":[
                    {
                      "name": "input",
                      "is_vector": true,
                      "vector_size":2,
                      "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false,
                        "common_io": false
                      },
                      "source": {
                        "type":"external",
                        "value":[0]
                      }
                    }],
                "outputs":[
                    {
                        "name":"consumer_out",
                        "is_vector": true,
                        "vector_size": 2,
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
                    "content": "int main(){\n  float input[2]; \n  float consumer_out[2]; \n  consumer_out[0] = input[0]*3.5; \n  consumer_out[1] = input[1]*3.5;\n}",
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            }
        ],
        "interconnect": [
            {
              "source": "test_producer.out",
              "destination": "test_consumer.input"
            }
        ],
        "emulation_time": 2,
    "deployment_mode": false
    })");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();


    std::vector<float> res = res_obj["test_consumer"]["outputs"]["consumer_out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 54.6);
    ASSERT_FLOAT_EQ(res[1], 54.6);
    std::vector<float> res2 = (std::vector<float>) res_obj["test_consumer"]["outputs"]["consumer_out"]["0"][1];
    ASSERT_FLOAT_EQ(res2[0], 60.2);
    ASSERT_FLOAT_EQ(res2[1], 60.2);
    std::vector<float> res3 = (std::vector<float>) res_obj["test_consumer"]["outputs"]["consumer_out"]["1"][0];
    ASSERT_FLOAT_EQ(res3[0], 54.6);
    ASSERT_FLOAT_EQ(res3[1], 54.6);
    std::vector<float> res4 = (std::vector<float>) res_obj["test_consumer"]["outputs"]["consumer_out"]["1"][1];
    ASSERT_FLOAT_EQ(res4[0], 60.2);
    ASSERT_FLOAT_EQ(res4[1], 60.2);
}

TEST(emulator_multichannel, emulator_multichannel_input) {
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
                        "name": "a",
                        "is_vector": false,
                        "metadata":{
                            "type": "float",
                            "width": 24,
                            "signed":false,
                            "common_io": false
                        },
                        "source": {
                            "type": "constant",
                            "value": [5]
                        }
                    },
                    {
                        "name": "b",
                        "is_vector": false,
                        "metadata":{
                            "type": "float",
                            "width": 24,
                            "signed":false,
                            "common_io": false
                        },
                        "source": {
                            "type": "constant",
                            "value": [1]
                        }
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
                    "content": "int main(){\n  float a,b,out; out = a + b;\n}",
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
        "emulation_time": 2,
    "deployment_mode": false
    })");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();


    std::vector<float> res = res_obj["test_producer"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 6);
    ASSERT_FLOAT_EQ(res[1], 6);
    std::vector<float> res2 = (std::vector<float>) res_obj["test_producer"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res2[0], 6);
    ASSERT_FLOAT_EQ(res2[1], 6);
}
