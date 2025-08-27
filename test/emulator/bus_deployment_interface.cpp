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

#include <fstream>
#include <gtest/gtest.h>

#include "emulator/emulator_dispatcher.hpp"

using namespace fcore;


TEST(bus_deployment_interface, single_core) {


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
          "memory_init": [],
          "program": {"content": "void main(){float test_out[2]; float input_1, input_2; test_out[0] = input_1; test_out[1] = input_2;}","headers": []},
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

    auto slots = manager.get_interconnect_slots();
    std::vector<deployer_interconnect_slot> expected_slots;
    deployer_interconnect_slot e;
    e.source_id = "test";
    e.source_name = "test_out";
    e.type = "o";
    e.source_io_address = 1;
    e.source_channel = 0;
    e.destination_bus_address = 3;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = false;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);


    e.source_id = "test";
    e.source_name = "test_out";
    e.type = "o";
    e.source_io_address = 2;
    e.source_channel = 0;
    e.destination_bus_address = 4;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = false;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);

    EXPECT_EQ(slots, expected_slots);
}



TEST(bus_deployment_interface, single_core_multichannel) {

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
          "memory_init": [],
          "program": {"content": "void main(){float test_out[2]; float input_1, input_2; test_out[0] = input_1; test_out[1] = input_2;}","headers": []},
          "order": 1,
          "options": {
            "comparators": "reducing",
            "efi_implementation": "efi_sort"
          },
          "channels": 2,
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

    auto slots = manager.get_interconnect_slots();
    std::vector<deployer_interconnect_slot> expected_slots;
    deployer_interconnect_slot e;
    e.source_id = "test";
    e.source_name = "test_out";
    e.type = "o";
    e.source_io_address = 1;
    e.source_channel = 0;
    e.destination_bus_address = 3;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = false;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);


    e.source_id = "test";
    e.source_name = "test_out";
    e.type = "o";
    e.source_io_address = 1;
    e.source_channel = 1;
    e.destination_bus_address = 4;
    e.destination_channel = 1;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = false;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);


    e.source_id = "test";
    e.source_name = "test_out";
    e.type = "o";
    e.source_io_address = 2;
    e.source_channel = 0;
    e.destination_bus_address = 5;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = false;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);


    e.source_id = "test";
    e.source_name = "test_out";
    e.type = "o";
    e.source_io_address = 2;
    e.source_channel = 1;
    e.destination_bus_address = 6;
    e.destination_channel = 1;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = false;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);


    EXPECT_EQ(slots, expected_slots);
}

TEST(bus_deployment_interface, scalar_interconnect) {

    nlohmann::json specs = nlohmann::json::parse(R"({
        "version":2,
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
                            "signed": true,
                            "common_io":false
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
                            "common_io":false
                        },
                        "source": {
                            "type": "constant",
                            "value": [
                                32.7
                            ]
                        }
                    }
                ],
                "outputs": [
                    {
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": true,
                            "common_io":false
                        },
                        "is_vector": false,
                        "name": "out"
                    },
                    {
                        "metadata": {
                            "type": "integer",
                            "width": 32,
                            "signed": true,
                            "common_io":false
                        },
                        "is_vector": false,
                        "name": "out2"
                    }
                ],
                "memory_init": [],
                "program": {
                    "content": "int main(){float input_1; float input_2; float out; out = input_1 + input_2 ; out2=fti(out);}",
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
                            "signed": true,
                            "common_io":false
                        },
                        "source":{
                            "type": "external",
                            "value":[0]
                        }
                    }
                ],
                "outputs": [
                    {
                        "is_vector": false,
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": true,
                            "common_io":false
                        },
                        "name": "out"
                    }
                ],
                "memory_init": [],
                "program": {
                    "content": "int main(){float input; float out; float val = itf(input); out = fti(val+1.0);}",
                    "headers": []
                },
                "order": 2,
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
        "interconnect": [
            {
                "source": "test.out2",
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
    auto slots = manager.get_interconnect_slots();


    std::vector<deployer_interconnect_slot> expected_slots;
    deployer_interconnect_slot e;

    e.source_id = "test";
    e.source_name = "out2";
    e.destination_id = "test_move";
    e.destination_name = "input";
    e.type = "c";
    e.source_io_address = 1;
    e.source_channel = 0;
    e.destination_bus_address = 1;
    e.destination_channel = 0;
    e.metadata.type = type_uint;
    e.metadata.width = 32;
    e.metadata.is_signed = true;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);

    e.source_id = "test";
    e.source_name = "out";
    e.destination_id = "";
    e.destination_name = "";
    e.type = "o";
    e.source_io_address = 3;
    e.source_channel = 0;
    e.destination_bus_address = 4;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = true;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);


    e.source_id = "test_move";
    e.source_name = "out";
    e.type = "o";
    e.source_io_address = 2;
    e.source_channel = 0;
    e.destination_bus_address = 5;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = true;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);


    EXPECT_EQ(slots, expected_slots);
}




TEST(bus_deployment_interface, multi_core_random_inputs) {

    nlohmann::json specs = nlohmann::json::parse(R"({
        "version":2,
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
                            "signed": true,
                            "common_io":false
                        },
                        "source": {
                            "type": "random",
                            "value":[0]
                        }
                    },
                    {
                        "name": "input_2",
                        "is_vector": false,
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": true,
                            "common_io":false
                        },
                        "source": {
                            "type": "constant",
                            "value": [
                                32.7
                            ]
                        }
                    }
                ],
                "outputs": [
                    {
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": true,
                            "common_io":false
                        },
                        "is_vector": false,
                        "name": "out"
                    },
                    {
                        "metadata": {
                            "type": "integer",
                            "width": 32,
                            "signed": true,
                            "common_io":false
                        },
                        "is_vector": false,
                        "name": "out2"
                    }
                ],
                "memory_init": [],
                "program": {
                    "content": "int main(){float input_1; float input_2; float out; out = input_1 + input_2 ; out2=fti(out);}",
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
                            "signed": true,
                            "common_io":false
                        },
                        "source":{
                            "type": "random",
                            "value":[0]
                        }
                    }
                ],
                "outputs": [
                    {
                        "is_vector": false,
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": true,
                            "common_io":false
                        },
                        "name": "out"
                    }
                ],
                "memory_init": [],
                "program": {
                    "content": "int main(){float input; float out; float val = itf(input); out = fti(val+1.0);}",
                    "headers": []
                },
                "order": 2,
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
    }
    )");

    emulator_dispatcher manager;
    manager.set_specs(specs);
    manager.process();
    auto inputs_0 = manager.get_inputs("test");
    auto inputs_1 = manager.get_inputs("test_move");

    EXPECT_NE(inputs_0[0].address[0], inputs_1[0].address[0]);
    EXPECT_NE(inputs_0[1].address[0], inputs_1[0].address[0]);
}


TEST(bus_deployment_interface, scatter_interconnect) {

    nlohmann::json specs = nlohmann::json::parse(
            R"({
    "version":2,
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
                        "vector_size": 2,
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": true,
                            "common_io":false
                        }
                    }
                    ],
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
                            "signed": true,
                            "common_io":true
                        },
                        "source":{
                            "type": "external",
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
                            "signed": true,
                            "common_io":false
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
    auto slots = manager.get_interconnect_slots();

    std::vector<deployer_interconnect_slot> expected_slots;
    deployer_interconnect_slot e;

    e.source_id = "test_producer";
    e.source_name = "out";
    e.destination_id = "test_consumer";
    e.destination_name = "input";
    e.type = "c";
    e.source_io_address = 1;
    e.source_channel = 0;
    e.destination_bus_address = 1;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = true;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0, 0};
    expected_slots.push_back(e);

    e.source_id = "test_producer";
    e.source_name = "out";
    e.destination_id = "test_consumer";
    e.destination_name = "input";
    e.type = "c";
    e.source_io_address = 2;
    e.source_channel = 0;
    e.destination_bus_address = 1;
    e.destination_channel = 1;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = true;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0, 0};
    expected_slots.push_back(e);


    e.source_id = "test_consumer";
    e.source_name = "out";
    e.destination_id = "";
    e.destination_name = "";
    e.type = "o";
    e.source_io_address = 3;
    e.source_channel = 0;
    e.destination_bus_address = 4;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = true;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);



    e.source_id = "test_consumer";
    e.source_name = "out";
    e.type = "o";
    e.source_io_address = 3;
    e.source_channel = 1;
    e.destination_bus_address = 5;
    e.destination_channel = 1;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = true;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);


    EXPECT_EQ(slots, expected_slots);
}


TEST(bus_deployment_interface, memory_to_memory_interface) {

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
    auto slots = manager.get_interconnect_slots();

    std::vector<deployer_interconnect_slot> expected_slots;
    deployer_interconnect_slot e;

    e.source_id = "test_producer";
    e.source_name = "mem";
    e.destination_id = "test_consumer";
    e.destination_name = "mem";
    e.type = "c";
    e.source_io_address = 1;
    e.source_channel = 0;
    e.destination_bus_address = 1;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = false;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);


    e.source_id = "test_consumer";
    e.source_name = "out";
    e.destination_id = "";
    e.destination_name = "";
    e.type = "o";
    e.source_io_address = 2;
    e.source_channel = 0;
    e.destination_bus_address = 3;
    e.destination_channel = 0;
    e.metadata.type = type_float;
    e.metadata.width = 32;
    e.metadata.is_signed = false;
    e.metadata.is_common_io = false;
    e.metadata.io_address = {0};
    expected_slots.push_back(e);

    EXPECT_EQ(slots, expected_slots);


    auto inits = manager.get_memory_initializations();
    std::unordered_map<std::string, std::vector<memory_init_value>> expected_inits;
    memory_init_value m;
    m.address = {1};
    m.value = std::vector<float>{0};
    expected_inits["test_producer"] = {m};
    m.address = {1};
    m.value = std::vector<float>{0};
    expected_inits["test_consumer"] = {m};
    EXPECT_EQ(inits, expected_inits);
}
