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


TEST(bus_allocation, single_core) {


    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
          "inputs": [
            {
              "name": "input_1",
              "type": "scalar",
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type": "series",
                "value": [15.7,67.4]
              },
              "channel": 0
            },
            {
              "name": "input_2",
              "type": "scalar",
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type": "series",
                "value": [42.92,-5.8]
              },
              "channel": 0
            }
          ],
          "outputs": [
            {
              "name": "test_out",
              "type": "vector",
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

    EXPECT_TRUE(false);
}



TEST(bus_allocation, single_core_multichannel) {

    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
          "inputs": [
            {
              "name": "input_1",
              "type": "scalar",
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type": "series",
                "value": [15.7,67.4]
              },
              "channel": 0
            },
            {
              "name": "input_2",
              "type": "scalar",
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type": "series",
                "value": [42.92,-5.8]
              },
              "channel": 0
            }
          ],
          "outputs": [
            {
              "name": "test_out",
              "type": "vector",
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

    EXPECT_TRUE(false);
}

TEST(bus_allocation, scalar_interconnect) {



    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test_producer",
          "inputs": [
            {
              "name": "input_1",
              "type": "scalar",
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type":"series",
                "value": [15.7,67.4]
              },
              "channel": 0
            },
            {
              "name": "input_2",
              "type": "scalar",
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type":"series",
                "value": [42.92,-5.8]
              },
              "channel": 0
            },
            {
              "name": "input_3",
              "type": "scalar",
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type":"external"
              },
              "channel": 0
            }
          ],
          "order": 1,
          "outputs": [
            {
              "name":"producer_out",
              "type": "scalar",
              "metadata": {
                "type": "integer",
                "width": 32,
                "signed": false,
                "common_io": false
              }
            }
          ],
          "program":{ "content": "void main(){float input_1,input_2; float c = input_1 + input_2; float producer_out = producer_out + c;}","build_settings": {"io": {"inputs": [], "outputs": [],"memories": []}},"headers": []},
          "memory_init": [],
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
              "type": "scalar",
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type":"external"
              },
              "channel": 0
            },
            {
              "name": "input_2c",
              "type": "scalar",
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": false,
                "common_io": false
              },
              "source": {
                "type":"constant",
                "value": 32.1
              },
              "channel": 0
            }
          ],
          "input_data": [],
          "memory_init": [],
          "outputs": [
            {
              "name":"consumer_out",
              "type": "scalar",
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
            "build_settings": {
              "io": {
                "inputs": [
                  "input_1"
                ],
                "outputs": [
                  "consumer_out"
                ],
                "memories": [
                ]
              }
            },
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
        },
        {
          "source": "test_consumer.consumer_out",
          "destination": "test_producer.input_3"
        }
      ],
      "emulation_time": 2,
      "deployment_mode": false
    })");

    EXPECT_TRUE(false);
}