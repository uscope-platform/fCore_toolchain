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

TEST(emulator_manager_v2, emulator_executable_format) {

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
                "type": "series",
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
                "type": "series",
                "value": [42.92,-5.8]
              }
            }
          ],
          "outputs": [
            {
              "name": "test_out",
              "is_vector": false,
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              }
            }
          ],
          "memory_init": [],
          "program": {
            "content": "int main() {float input_1;float input_2;float test_out;test_out = input_1 + input_2;}",
            "headers": []
          },
          "order": 1,
          "options": {
            "comparators": "reducing",
            "efi_implementation": "efi_sort"
          },
          "channels": 1,
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

    std::vector<float>  result = std::vector<float>(res_obj["test"]["outputs"]["test_out"]["0"][0]);
    std::vector<float> reference = {58.62, 61.6};
    for(int i = 0; i<result.size(); ++i){
        ASSERT_FLOAT_EQ(result[i], reference[i]);
    }

}

TEST(emulator_manager_v2, emulator_compile_error) {

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
            "value": [42.92,5.8]
          }
        }
      ],
      "outputs": [
        {
          "name":"test_out",
          "is_vector": false,
          "metadata": {
            "type": "float",
            "width": 32,
            "signed": false,
            "common_io": false
          }
        }
      ],
      "memory_init": [],
      "program":{
        "content": "int main() {float a;float b;float c;c = UNDEFINED(a + b);}",
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

    EXPECT_THROW({
        try{
            emulator_dispatcher manager;
            manager.set_specs(specs);
            manager.process();
        }
        catch( const std::runtime_error& e ) {

         EXPECT_STREQ( "CORE test: Function UNDEFINED is not defined", e.what() );
         throw;
        }
    }, std::runtime_error );
}

TEST(emulator_manager_v2, emulator_asm) {


    nlohmann::json specs = nlohmann::json::parse( R"({
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
                        "metadata":{
                            "io_address": 12,
                            "type": "float",
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
                    "efi_implementation": "none"
                },
                "program": {
                    "content": "ldc r42, 12.5000\nldc r3, 3.2000\nadd r3, r42, r12\nstop\n",
                    "type":"asm",
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
        "emulation_time": 1,
        "deployment_mode": false
    })");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();


    auto dbg = manager.get_results().dump(4);
    float res = manager.get_results()["test"]["outputs"]["r12"]["0"][0][0];
    ASSERT_FLOAT_EQ(res, 15.7f);

}

TEST(emulator_manager_v2, emulator_consecutive_runs) {

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
                "memory_init": [{
                        "name": "out",
                        "is_vector": false,
                        "metadata":{
                            "type": "integer",
                            "width": 12,
                            "signed":true
                        },
                        "is_output":true,
                        "is_input": false,
                        "value":0
                    }],
                "channels": 1,
                "options": {
                    "comparators": "reducing",
                    "efi_implementation": "efi_sort"
                },
                "program": {
                    "content": "int main(){float input_1;float input_2;float internal = input_1 + input_2;float out =  internal + out;}",
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
    std::vector<uint32_t> check_vector = {0x426a7ae1, 0x42f070a4};

    std::vector<float> res_f = {0, 0};
    res_f[0] = emulator_backend::uint32_to_float(res[0]);
    res_f[1] = emulator_backend::uint32_to_float(res[1]);


    std::vector<float> check_f = {0, 0};
    check_f[0] = emulator_backend::uint32_to_float(check_vector[0]);
    check_f[1] = emulator_backend::uint32_to_float(check_vector[1]);
    ASSERT_EQ(res, check_vector);

    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    std::vector<uint32_t> res2 = manager.get_results()["test"]["outputs"]["out"]["0"][0];
    check_vector = {0x426a7ae1, 0x42f070a4};

    res_f[0] = emulator_backend::uint32_to_float(res2[0]);
    res_f[1] = emulator_backend::uint32_to_float(res2[1]);

    check_f[0] = emulator_backend::uint32_to_float(check_vector[0]);
    check_f[1] = emulator_backend::uint32_to_float(check_vector[1]);

    ASSERT_EQ(res2, check_vector);


}

TEST(emulator_manager_v2, emulator_compilation) {

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
            "value": [42.92, -5.8]
          }
        }
      ],
      "outputs": [
        {
          "name":"out",
          "is_vector": false,
          "metadata": {
            "type": "integer",
            "width": 15,
            "signed": false,
            "common_io": false
          }
        }
      ],
      "memory_init": [],
      "program":{
        "content": "int main(){float input_1; float input_2; float out; out = fti(input_1 + input_2);}",
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

    std::vector<uint32_t> reference = {59,62};
    std::vector<uint32_t> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
}

TEST(emulator_manager_v2, emulator_compilation_interconnect) {

    nlohmann::json specs = nlohmann::json::parse( R"(
    {
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
              "value": [15.0,67.0]
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
              "value": [42.0,-6.0]
            }
          }
        ],
        "outputs": [
          {
            "name":"out",
            "is_vector": false,
            "metadata": {
              "type": "integer",
              "width": 24,
              "signed": false,
              "common_io": false
            }
          }
        ],
        "memory_init": [],
        "program":{
          "content": "int main(){float input_1; float input_2; float out; out = fti(input_1 + input_2);}",
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
      },
      {
        "id": "test_move",
        "inputs": [
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
                "type":"external"
              }
            }
        ],
        "outputs": [
          {
            "name":"out",
            "is_vector": false,
            "metadata": {
              "type": "integer",
              "width": 15,
              "signed": false,
              "common_io": false
            }
          }
        ],
        "memory_init": [],
        "program":{
          "content": "int main(){float input; float out; float val = itf(input); out = fti(val+1.0);}",
          "headers": []
        },
        "order": 2,
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
        "source": "test.out",
        "destination": "test_move.input"
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
    auto res = manager.get_results();
    auto dbg = res.dump(4);
    std::vector<uint32_t> reference = {57,61};
    std::vector<uint32_t> result = res["test"]["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
    std::vector<uint32_t> reference2 = {58,62};
    std::vector<uint32_t> result2 = res["test_move"]["outputs"]["out"]["0"][0];
    ASSERT_EQ(result2, reference2);
}

TEST(emulator_manager_v2, emulator_interconnect_input_override) {

    nlohmann::json specs = nlohmann::json::parse( R"(
    {
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
              "value": [15.0,67.0]
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
              "value": [42.0,-6.0]
            }
          }
        ],
        "outputs": [
          {
            "name":"out",
            "is_vector": false,
            "metadata": {
              "type": "integer",
              "width": 24,
              "signed": false,
              "common_io": false
            }
          }
        ],
        "memory_init": [],
        "program":{
          "content": "int main(){float input_1; float input_2; float out; out = fti(input_1 + input_2);}",
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
      },
      {
        "id": "test_move",
        "inputs": [
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
                "type":"constant",
                "value": 322.0
              }
            }
        ],
        "outputs": [
          {
            "name":"out",
            "is_vector": false,
            "metadata": {
              "type": "integer",
              "width": 15,
              "signed": false,
              "common_io": false
            }
          }
        ],
        "memory_init": [],
        "program":{
          "content": "int main(){float input; float out; float val = itf(input); out = fti(val+1.0);}",
          "headers": []
        },
        "order": 2,
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
        "source": "test.out",
        "destination": "test_move.input"
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
    auto res = manager.get_results();
    auto dbg = res.dump(4);
    std::vector<uint32_t> reference = {57,61};
    std::vector<uint32_t> result = res["test"]["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
    std::vector<uint32_t> reference2 = {58,62};
    std::vector<uint32_t> result2 = res["test_move"]["outputs"]["out"]["0"][0];
    ASSERT_EQ(result2, reference2);
}

TEST(emulator_manager_v2, emulator_header) {

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
                        "common_io": false
                    },
                    "source": {
                        "type": "constant",
                        "value": [5]
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
                    "source": {
                        "type": "constant",
                        "value": [4]
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
            "channels": 1,
            "options": {
                "comparators": "reducing",
                "efi_implementation": "none"
            },
            "program": {
                "content": "int main(){\n  float input_1;\n  float input_2;\n  float out = add(input_1, input_2);\n}",
                "headers": ["float add(float input_1, float input_2) {return input_1 + input_2;};"]
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
    "emulation_time": 1,
    "deployment_mode": false
})");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    std::vector<float> res = res_obj["test"]["outputs"]["out"]["0"][0];
    auto dbg = res_obj.dump(4);
    ASSERT_FLOAT_EQ(res[0], 9.0);

}

TEST(emulator_manager_v2, emulator_common_io) {


    nlohmann::json specs = nlohmann::json::parse(
    R"({
    "version": 2,
    "cores": [
        {
            "id": "test",
            "order": 1,
            "inputs": [
                {
                    "name": "a",
                    "is_vector": false,
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": true
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
            "outputs": [
                {
                    "name": "c",
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
            "channels": 1,
            "options": {
                "comparators": "reducing",
                "efi_implementation": "none"
            },
            "program": {
                "content": "int main(){float a, b;float c = a + b;}",
                "headers": ["float add(float input_1, float input_2) {return input_1 + input_2;};"]
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
    "emulation_time": 1,
    "deployment_mode": false
})");


    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    std::vector<float> res = res_obj["test"]["outputs"]["c"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 6.0);

}

TEST(emulator_manager_v2, emulator_multiple_common_io) {


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
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    auto dbg = res_obj.dump(4);
    std::vector<float> res_0 = res_obj["test"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res_0[1], 35.2);
    std::vector<float> res_1 = res_obj["test"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res_0[1], 35.2);

}

TEST(emulator_manager_v2, emulation_repeatability) {

    nlohmann::json specs = nlohmann::json::parse(
            R"({
    "version": 2,
    "cores": [
        {
            "id": "producer",
            "order": 1,
            "inputs": [],
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
            "memory_init": [
                {
                    "name": "mem",
                    "vector_size": 1,
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": true
                    },
                    "is_output": false,
                    "is_input": false,
                    "is_vector": false,
                    "value": [
                        0
                    ]
                }
            ],
            "deployment": {
                "rom_address": 0,
                "has_reciprocal": false,
                "control_address": 0
            },
            "channels": 1,
            "program": {
                "content": "void main(){\n  float mem, out;\n\n  mem += 1.0;\n  out = mem*2.0;\n}",
                "headers": []
            },
            "options": {
                "comparators": "reducing",
                "efi_implementation": "efi_trig"
            },
            "sampling_frequency": 1000
        },
        {
            "id": "consumer",
            "order": 2,
            "inputs": [
                {
                    "name": "in",
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": true,
                        "common_io": false
                    },
                    "source": {
                        "type": "external",
                        "value": 0
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
                "content": "void main(){\n  float in, out;\n  out = in*1.5;\n}",
                "headers": []
            },
            "options": {
                "comparators": "reducing",
                "efi_implementation": "efi_trig"
            },
            "sampling_frequency": 1000
        }
    ],
    "interconnect": [
        {
            "source": "producer.out",
            "destination": "consumer.in"
        }
    ],
    "emulation_time": 1,
    "deployment_mode": false
})");

    emulator_dispatcher dispatcher;
    dispatcher.set_specs(specs);
    dispatcher.process();
    dispatcher.emulate();
    auto res_1 = dispatcher.get_results();

    dispatcher.set_specs(specs);
    dispatcher.process();
    dispatcher.emulate();
    auto res_2 = dispatcher.get_results();


    EXPECT_EQ(res_1, res_2);
}