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
          "program": {"content": "void main(){float test_out[2]; float input_1, input_2; test_out[0] = input_1; test_out[1] = input_2;}",
                      "build_settings": {"io": {"inputs": ["input_1", "input_2"],"outputs": ["test_out"],"memories": []}},"headers": []},
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
          "program": {"content": "void main(){float test_out[2]; float input_1, input_2; test_out[0] = input_1; test_out[1] = input_2;}",
                      "build_settings": {"io": {"inputs": ["input_1", "input_2"],"outputs": ["test_out"],"memories": []}},"headers": []},
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
                    "build_settings": {
                        "io": {
                            "inputs": [
                                "input_1",
                                "input_2"
                            ],
                            "outputs": [
                                "out",
                                "out2"
                            ],
                            "memories": []
                        }
                    },
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
                        "source":{"type": "external"}
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
                    "build_settings": {
                        "io": {
                            "inputs": [
                                "input"
                            ],
                            "outputs": [
                                "out"
                            ],
                            "memories": []
                        }
                    },
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
    e.type = "o";
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
                    "build_settings":{"io":{"inputs":[],"outputs":["out"],"memories":[]}},
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
                        "source":{"type": "external"}
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
                    "build_settings":{"io":{"inputs":["input"],"outputs":["out"],"memories":[]}},
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
    e.type = "o";
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
    e.type = "o";
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








