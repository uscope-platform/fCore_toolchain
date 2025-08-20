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

TEST(emulator_iom, emulator_inputs) {

    nlohmann::json specs = nlohmann::json::parse( R"({
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
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        },
                        "source": {
                            "type": "series",
                            "value": [15.7,67.4]
                        }
                    },
                    {
                        "name": "input_2",
                        "is_vector": false,
                        "metadata":{
                            "type": "float",
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        },
                        "source": {
                            "type": "series",
                            "value": [42.92,-5.8]
                        }
                    }
                ],
                "outputs": [
                    {
                        "name": "out",
                        "is_vector": false,
                        "metadata":{
                            "type": "integer",
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        }
                    }
                ],
                "memory_init": [],
                "channels": 1,
                "options": {
                    "comparators": "reducing",
                    "efi_implementation": "efi_sort"
                },
                "program": {
                    "content": "int main(){float input_1;float input_2;float internal = input_1 + input_2;float out =  internal;}",
                    "type":"c",
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

    auto dbg = res_obj.dump(4);

    std::vector<uint32_t> res = res_obj["test"]["outputs"]["out"]["0"][0];
    std::vector<uint32_t> reference = {0x426a7ae1, 0x42766667};
    ASSERT_EQ(res, reference);

}


TEST(emulator_iom, emulator_random_inputs) {

    nlohmann::json specs = nlohmann::json::parse( R"({
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
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        },
                        "source": {
                            "type": "random"
                        }
                    },
                    {
                        "name": "input_2",
                        "is_vector": false,
                        "metadata":{
                            "type": "float",
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        },
                        "source": {
                            "type": "random"
                        }
                    }
                ],
                "outputs": [
                    {
                        "name": "out",
                        "is_vector": false,
                        "metadata":{
                            "type": "integer",
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        }
                    }
                ],
                "memory_init": [],
                "channels": 1,
                "options": {
                    "comparators": "reducing",
                    "efi_implementation": "efi_sort"
                },
                "program": {
                    "content": "int main(){float input_1;float input_2;float out = itf(input_1) + itf(input_2);}",
                    "type":"c",
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

    auto dbg = res_obj.dump(4);

    std::vector<float> res_f;
    for (auto i : res_obj["test"]["outputs"]["out"]["0"][0]) {
        res_f.push_back(emulator_backend::uint32_to_float(i));
    }
    std::vector<float> reference = {-45419, 11592};
    ASSERT_EQ(res_f, reference);

}

TEST(emulator_iom, emulator_outputs) {

    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
          "inputs": [
            {
              "name": "input_1",
              "is_vector": false,
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type":"series",
                "value": [15.7,67.4]
              }
            },
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
                "type":"series",
                "value": [42.92,-5.8]
              }
            }
          ],
          "outputs": [
            {
              "name":"out",
              "is_vector": false,
              "metadata": {
                "type": "float",
                "width": 16,
                "signed": true,
                "common_io": false
              }
            }
          ],
          "program":{
            "content": "void main(){float input_1,input_2; float c = input_1 + input_2; float test_out = test_out + c; float out = test_out*1.0;}",
            "headers": []
          },
          "memory_init": [
            {
              "name": "test_out",
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
          "order": 1,
          "options":{
            "comparators":"reducing",
            "efi_implementation":"efi_sort"
          },
          "channels":1,
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
    auto res = manager.get_results()["test"];

    auto dbg = manager.get_results().dump(4);

    std::vector<float> reference = {58.6199989, 120.220001};
    std::vector<float> test_out = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(test_out, reference);

}

TEST(emulator_iom, emulator_memory) {

    nlohmann::json specs = nlohmann::json::parse( R"({
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
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        },
                        "source": {
                            "type": "series",
                            "value": [15.7,67.4]
                        }
                    },
                    {
                        "name": "input_2",
                        "is_vector": false,
                        "metadata":{
                            "type": "float",
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        },
                        "source": {
                            "type": "series",
                            "value": [42.92,-5.8]
                        }
                    }
                ],
                "outputs": [
                    {
                        "name": "out",
                        "is_vector": false,
                        "metadata":{
                            "type": "integer",
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        }
                    }
                ],
                "memory_init": [
                    {
                        "name": "mem",
                        "is_vector": false,
                        "metadata":{
                            "type": "float",
                            "width": 12,
                            "signed":true
                        },
                        "is_output":true,
                        "is_input": false,
                        "value":2
                    }
                ],
                "channels": 1,
                "options": {
                    "comparators": "reducing",
                    "efi_implementation": "efi_sort"
                },
                "program": {
                    "content": "int main(){float input_1;float input_2;float internal = input_1 + input_2;float mem =  internal + mem; float out=mem*1.0;}",
                    "type":"c",
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

    uint32_t res = manager.get_results()["test"]["outputs"]["out"]["0"][0][1];

    ASSERT_EQ(res, 0x42f470a4);

}


TEST(emulator_iom, emulator_memory_to_memory_inteconnect) {

    nlohmann::json specs = nlohmann::json::parse( R"(
    {
      "version": 2,
      "cores": [
        {
          "id": "test_producer",
          "inputs": [],
          "order": 1,
          "outputs": [
          ],
          "program":{
            "content": "void main(){float mem; mem += 1.2;}",
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
              "is_input": false,
              "value": 0
            }
          ],
          "options":{
            "comparators":"reducing",
            "efi_implementation":"efi_sort"
          },
          "channels":1,
          "sampling_frequency": 1,
          "deployment": {
            "has_reciprocal": false,
            "control_address": 18316525568,
            "rom_address": 17179869184
          }
        },
        {
          "id": "test_consumer",
          "inputs": [],
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
              "is_output": false,
              "is_input": true,
              "value": 0
            }
          ],
          "outputs": [
            {
              "name":"out",
              "is_vector": false,
              "metadata": {
                "type": "integer",
                "width": 32,
                "signed": false,
                "common_io": false
              }
            }
          ],
          "order": 2,
          "program":{
            "content": "void main(){float mem; float out = mem*2.0;}",
            "headers": []
          },
          "options":{
            "comparators":"reducing",
            "efi_implementation":"efi_sort"
          },
          "channels":1,
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
          "destination": "test_consumer.mem"
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
    auto res = manager.get_results()["test_consumer"];

    std::vector<uint32_t> reference = {0x4019999A, 0x4099999A};
    std::vector<uint32_t> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);

}


TEST(emulator_iom, emulator_compilation_memory) {


    nlohmann::json specs = nlohmann::json::parse( R"({
  "version": 2,
  "cores": [
    {
      "id": "test",
      "inputs": [
        {
          "name": "input_1",
          "is_vector": false,
          "metadata": {
            "type": "float",
            "width": 32,
            "signed": false,
            "common_io": false
          },
          "source": {
            "type":"series",
            "value": [15.7,67.4]
          }
        }
      ],
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
      "memory_init": [
        {
            "name": "mem",
            "is_vector": false,
            "metadata":{
                "type": "float",
                "width": 12,
                "signed":true
            },
            "is_output":true,
            "is_input": false,
            "value":0
        }
],
      "program":{
        "content": "int main(){float input_1; float mem; float out; mem = mem + input_1; out = mem;}",
        "headers": []
      },
      "order": 1,
      "options":{
        "comparators":"reducing",
        "efi_implementation":"efi_sort"
      },
      "channels":1,
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
    auto res = manager.get_results()["test"];

    std::vector<uint32_t> reference = {15,83};
    std::vector<uint32_t> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
}


TEST(emulator_iom, emulator_memory_as_output) {

    nlohmann::json specs = nlohmann::json::parse( R"({
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
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        },
                        "source": {
                            "type": "series",
                            "value": [15.7,67.4]
                        }
                    },
                    {
                        "name": "input_2",
                        "is_vector": false,
                        "metadata":{
                            "type": "float",
                            "width": 12,
                            "signed":true,
                            "common_io": false
                        },
                        "source": {
                            "type": "series",
                            "value": [42.92,-5.8]
                        }
                    }
                ],
                "outputs": [],
                "memory_init": [
                    {
                        "name": "mem",
                        "is_vector": false,
                        "metadata":{
                            "type": "float",
                            "width": 12,
                            "signed":true
                        },
                        "is_output":true,
                        "is_input": false,
                        "value":2
                    }
                ],
                "channels": 1,
                "options": {
                    "comparators": "reducing",
                    "efi_implementation": "efi_sort"
                },
                "program": {
                    "content": "int main(){float input_1;float input_2;float internal = input_1 + input_2;float mem =  internal + mem;}",
                    "type":"c",
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

    std::string dbg = manager.get_results().dump(4);

    float res = manager.get_results()["test"]["outputs"]["mem"]["0"][0][0];

    ASSERT_FLOAT_EQ(res, 60.62);
    res = manager.get_results()["test"]["outputs"]["mem"]["0"][0][1];

    ASSERT_FLOAT_EQ(res, 122.22);
}

TEST(emulator_iom, emulator_array_constant_input_float) {

nlohmann::json specs = nlohmann::json::parse(
    R"({
    "version": 2,
        "cores": [
            {
                "order": 1,
                "id": "test",
                "channels":1,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "inputs":[
                {
                  "name": "in",
                  "is_vector": true,
                  "vector_size": 2,
                  "metadata": {
                    "type": "float",
                    "width": 32,
                    "signed": false,
                    "common_io": false
                  },
                  "source": {
                    "type":"constant",
                    "value": [42.92, 15.7]
                  }
                }
                ],
                "outputs":[
                {
                    "name": "out",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    }
                }],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float in[2]; float out = in[0] + in[1];\n}",
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
    auto res = manager.get_results()["test"];

    std::vector<float> reference = {58.62,58.62};
    std::vector<float> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
}

TEST(emulator_iom, emulator_array_file_input_float) {


nlohmann::json specs = nlohmann::json::parse(
    R"({
    "version": 2,
        "cores": [
            {
                "order": 1,
                "id": "test",
                "channels":1,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "inputs":[
                {
                  "name": "in",
                  "is_vector": true,
                  "vector_size": 2,
                  "metadata": {
                    "type": "float",
                    "width": 32,
                    "signed": false,
                    "common_io": false
                  },
                  "source": {
                    "type":"series",
                    "value": [[15.7,67.4], [42.92,-5.8]]
                  }
                }
                ],
                "outputs":[
                {
                    "name": "out",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    }
                }],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float in[2]; float out = in[0] + in[1];\n}",
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
    auto res = manager.get_results()["test"];

    std::vector<float> reference = {58.62,61.6000023};
    std::vector<float> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
}



TEST(emulator_iom, emulator_array_constant_input_int) {

nlohmann::json specs = nlohmann::json::parse(
    R"({
    "version": 2,
        "cores": [
            {
                "order": 1,
                "id": "test",
                "channels":1,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "inputs":[
                {
                  "name": "in",
                  "is_vector": true,
                  "vector_size": 2,
                  "metadata": {
                    "type": "integer",
                    "width": 32,
                    "signed": false,
                    "common_io": false
                  },
                  "source": {
                    "type":"constant",
                    "value": [42, 15]
                  }
                }
                ],
                "outputs":[
                {
                    "name": "out",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    }
                }],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float in[2]; float out = itf(in[0]) + itf(in[1]);\n}",
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
    auto res = manager.get_results()["test"];

    std::vector<float> reference = {57.00,57.00};
    std::vector<float> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
}

TEST(emulator_iom, emulator_array_file_input_int) {


nlohmann::json specs = nlohmann::json::parse(
    R"({
    "version": 2,
        "cores": [
            {
                "order": 1,
                "id": "test",
                "channels":1,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "inputs":[
                {
                  "name": "in",
                  "is_vector": true,
                  "vector_size": 2,
                  "metadata": {
                    "type": "integer",
                    "width": 32,
                    "signed": false,
                    "common_io": false
                  },
                  "source": {
                    "type":"series",
                    "value": [[15,67], [42,-5]]
                  }
                }
                ],
                "outputs":[
                {
                    "name": "out",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    }
                }],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float in[2]; float out = itf(in[0]) + itf(in[1]);\n}",
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
    auto res = manager.get_results()["test"];

    std::vector<float> reference = {57.00,62};
    std::vector<float> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
}



TEST(emulator_iom, emulator_array_output ) {


nlohmann::json specs = nlohmann::json::parse(
    R"({
    "version": 2,
        "cores": [
            {
                "order": 1,
                "id": "test",
                "channels":1,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "inputs":[
                {
                  "name": "in",
                  "is_vector": true,
                  "vector_size": 2,
                  "metadata": {
                    "type": "float",
                    "width": 32,
                    "signed": false,
                    "common_io": false
                  },
                  "source": {
                    "type":"series",
                    "value": [[15.7,67.4], [42.92,-5.8]]
                  }
                }
                ],
                "outputs":[
                {
                    "name": "out",
                    "is_vector": true,
                    "vector_size": 2,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    }
                }],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float in[2]; float out[2]; out[0] = in[0] + in[1]; out[1] = in[0] + 2.0*in[1];\n}",
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
    auto res = manager.get_results()["test"];
    auto dbg = res.dump(4);
    std::vector<float> reference = {58.62,61.6000023};
    std::vector<float> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
    std::vector<float> reference2 = {101.53999, 55.8000031};
    std::vector<float> result2 = res["outputs"]["out"]["0"][1];
    ASSERT_EQ(result2, reference2);
}

TEST(emulator_iom, emulator_same_name_outputs) {

    nlohmann::json specs = nlohmann::json::parse( R"(
{
      "version": 2,
      "cores": [
        {
          "id": "test_producer",
          "inputs": [],
          "order": 1,
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
          "program":{
            "content": "void main(){float mem; mem += 1.2; float out = mem*1.0;}",
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
              "is_input": false,
              "value": 0
            }
          ],
          "options":{
            "comparators":"reducing",
            "efi_implementation":"efi_sort"
          },
          "channels":1,
          "sampling_frequency": 1,
          "deployment": {
            "has_reciprocal": false,
            "control_address": 18316525568,
            "rom_address": 17179869184
          }
        },
        {
          "id": "test_producer_2",
          "inputs": [],
          "order": 2,
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
          "program":{
            "content": "void main(){float mem; mem += 1.2; float out = mem*1.0;}",
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
              "is_input": false,
              "value": 30
            }
          ],
          "options":{
            "comparators":"reducing",
            "efi_implementation":"efi_sort"
          },
          "channels":1,
          "sampling_frequency": 1,
          "deployment": {
            "has_reciprocal": false,
            "control_address": 18316525568,
            "rom_address": 17179869184
          }
        }
      ],
      "interconnect":[],
      "emulation_time": 2,
      "deployment_mode": false
    }
)");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res = manager.get_results();

    std::vector<float> reference = {1.2, 2.4};
    std::vector<float> result = res["test_producer"]["outputs"]["mem"]["0"][0];
    std::vector<float> result2 = res["test_producer"]["outputs"]["out"]["0"][0];
    for(int i = 0; i < reference.size(); i++) {
        ASSERT_FLOAT_EQ(reference[i], result[i]);
        ASSERT_FLOAT_EQ(reference[i], result2[i]);
    }
    reference = {31.2, 32.4};
    result = static_cast<std::vector<float>>(res["test_producer_2"]["outputs"]["mem"]["0"][0]);
    result2 = static_cast<std::vector<float>>(res["test_producer_2"]["outputs"]["out"]["0"][0]);
    for(int i = 0; i < reference.size(); i++) {
        ASSERT_FLOAT_EQ(reference[i], result[i]);
        ASSERT_FLOAT_EQ(reference[i], result2[i]);
    }


}



TEST(emulator_iom, emulator_iom_common_io_csel) {

    nlohmann::json specs = nlohmann::json::parse( R"(
    {
        "version": 2,
        "cores": [
            {
                "id": "test",
                "order": 1,
                "inputs": [
                    {
                        "name": "fault",
                        "metadata": {
                            "type": "integer",
                            "width": 32,
                            "signed": true,
                            "common_io": false
                        },
                        "source": {
                            "type": "series",
                            "value": [
                                [0, 0, 1, 1],
                                [1, 1, 0, 0]
                            ]
                        },
                        "vector_size": 1,
                        "is_vector": false
                    },
                    {
                        "name": "v_in",
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": true,
                            "common_io": true
                        },
                        "source": {
                            "type": "constant",
                            "value": [
                                1000
                            ]
                        },
                        "vector_size": 1,
                        "is_vector": false
                    }
                ],
                "outputs": [
                    {
                        "name": "v_out",
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
                "memory_init": [
                    {
                        "name": "v_cross",
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
                            20,
                            20
                        ]
                    }
                ],
                "deployment": {
                    "rom_address": 0,
                    "has_reciprocal": false,
                    "control_address": 0
                },
                "channels": 2,
                "program": {
                    "content": "void main(){\n  \n    float  v_in, v_out, v_cross, fault; \n    v_out = fault != 0 ? v_cross : v_in;\n  \n}\n",
                    "headers": []
                },
                "options": {
                    "comparators": "reducing",
                    "efi_implementation": "efi_trig"
                },
                "sampling_frequency": 1
            }
        ],
        "interconnect": [],
        "emulation_time": 4,
        "deployment_mode": false
    }
)");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res = manager.get_results();

    std::vector<float> reference = {1000,1000,20,20};
    std::vector<float> result = res["test"]["outputs"]["v_out"]["0"][0];
    for(int i = 0; i < reference.size(); i++) {
        ASSERT_FLOAT_EQ(reference[i], result[i]);
    }

    std::vector<float> reference_2 = {20,20,1000,1000};
    std::vector<float> result_2 = res["test"]["outputs"]["v_out"]["1"][0];
    for(int i = 0; i < reference.size(); i++) {
        ASSERT_FLOAT_EQ(reference_2[i], result_2[i]);
    }
}