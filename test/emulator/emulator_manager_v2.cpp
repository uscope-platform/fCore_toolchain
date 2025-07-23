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

#include "emulator_test_helpers.hpp"
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

TEST(emulator_manager_v2, emulator_inputs) {

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


TEST(emulator_manager_v2, emulator_random_inputs) {

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

TEST(emulator_manager_v2, emulator_outputs) {

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

TEST(emulator_manager_v2, emulator_memory) {

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

TEST(emulator_manager_v2, emulator_inteconnect) {

    nlohmann::json specs = nlohmann::json::parse( R"(
    {
      "version": 2,
      "cores": [
        {
          "id": "test_producer",
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
          "order": 1,
          "outputs": [
          ],
          "program":{
            "content": "void main(){float input_1,input_2; float c = input_1 + input_2; float producer_out = producer_out + c;}",
            "headers": []
          },
          "memory_init": [
            {
              "name": "producer_out",
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
                "type":"external"
              }
            }
          ],
          "memory_init": [],
          "outputs": [
            {
              "name":"consumer_out",
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
            "content": "void main(){float input_1; float consumer_out = input_1;}",
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
          "source": "test_producer.producer_out",
          "destination": "test_consumer.input_1"
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

    std::vector<uint32_t> reference = {0x426a7ae1, 0x42f070a4};
    ASSERT_EQ(res["outputs"]["consumer_out"]["0"][0], reference);

}


TEST(emulator_manager_v2, emulator_memory_to_memory_inteconnect) {

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



TEST(emulator_manager_v2, emulator_memory_to_memory_multichannel) {

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
    std::vector<float> reference_3 = {5, 10};
    std::vector<float> result_3 = res["outputs"]["mem"]["1"][0];
    for(int i =0; i<2; i++) {
        ASSERT_FLOAT_EQ(result_3[i], reference_3[i]);
    }
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

TEST(emulator_manager_v2, emulator_compilation_memory) {


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


TEST(emulator_manager_v2, emulator_memory_as_output) {

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

TEST(emulator_manager_v2, emulator_array_constant_input_float) {

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

TEST(emulator_manager_v2, emulator_array_file_input_float) {


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



TEST(emulator_manager_v2, emulator_array_constant_input_int) {

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

TEST(emulator_manager_v2, emulator_array_file_input_int) {


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



TEST(emulator_manager_v2, emulator_array_output) {


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

TEST(emulator_manager_v2, emulator_multichannel) {

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


TEST(emulator_manager_v2, emulator_multichannel_mem_init) {

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

    std::vector<float> res = res_obj["test"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 250.0);
    ASSERT_FLOAT_EQ(res[1], 250.25);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 1250.0);
    ASSERT_FLOAT_EQ(res[1], 1250.25);
}


TEST(emulator_manager_v2, emulator_multichannel_input_file) {


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

TEST(emulator_manager_v2, emulator_multichannel_gather_transfer) {


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
                    "type":"external"
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

TEST(emulator_manager_v2, emulator_multichannel_scatter_transfer) {


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
                        "type":"external"
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


TEST(emulator_manager_v2, emulator_multichannel_vector_transfer) {
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
                        "type":"external"
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

TEST(emulator_manager_v2, emulator_multichannel_2d_vector_transfer) {
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
                        "type":"external"
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

TEST(emulator_manager_v2, emulator_multichannel_input) {
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


TEST(emulator_manager_v2, emulator_disassemble) {


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
    std::unordered_map<std::string, fcore::disassembled_program> expected = {
            {"test_producer", {{{2,3},{3,1}, {4,2}}, "add r2, r1, r3\nstop\n"}},
            {"test_reducer",  {{{1,3},{3,2}, {4,1}}, "mul r1, r2, r3\nstop\n"}}
    };

    EXPECT_EQ(res["test_producer"].program, expected["test_producer"].program);
    EXPECT_EQ(res["test_producer"].translation_table, expected["test_producer"].translation_table);
    EXPECT_EQ(res["test_reducer"].program, expected["test_reducer"].program);
    EXPECT_EQ(res["test_reducer"].translation_table, expected["test_reducer"].translation_table);


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
                        "value": ""
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
