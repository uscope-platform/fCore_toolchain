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
#include <chrono>
#include <thread>

#include "../emulator_test_helpers.hpp"
#include "emulator/emulator_dispatcher.hpp"
#include "emulator/v2/backend/live_capture_sink.hpp"
#include "result_helpers.hpp"

using namespace fcore;
using namespace fcore::emulator_v2;

static std::vector<float> block_channel(const live_block &block, uint32_t channel) {
    std::vector<float> ret;
    for(uint32_t i = 0; i < block.n_samples; i++) {
        ret.push_back(emulator_backend::uint32_to_float(block.samples[channel * block.n_samples + i]));
    }
    return ret;
}

TEST(emulator_live_capture, emulator_live_block) {

    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
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
            "content": "void main(){float mem; mem += 1.0; float out = mem*1.0;}",
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
              "is_output": false,
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
        }
      ],
      "interconnect":[],
      "emulation_time": 4,
      "deployment_mode": false
    })");

    auto sink = std::make_shared<live_capture_sink>(2, 4);
    emulator_dispatcher manager;
    ASSERT_TRUE(manager.set_output_sink(sink));
    ASSERT_TRUE(manager.set_specs(specs));
    ASSERT_TRUE(manager.process());
    ASSERT_TRUE(sink->select_output(0, output_selection{"test", "out", 0, 0}));
    ASSERT_TRUE(manager.emulate());

    auto block = sink->take_block();
    ASSERT_TRUE(block.has_value());
    ASSERT_EQ(block->n_channels, 2);
    ASSERT_EQ(block->n_samples, 4);
    ASSERT_EQ(block->sequence, 0);
    ASSERT_EQ(block->sampling_frequency, 1);

    std::vector<float> reference = {1, 2, 3, 4};
    ASSERT_EQ(block_channel(block.value(), 0), reference);

    // the channel without an output is empty
    reference = {0, 0, 0, 0};
    ASSERT_EQ(block_channel(block.value(), 1), reference);
    ASSERT_TRUE(block->channels[0].selected);
    ASSERT_FALSE(block->channels[1].selected);
    ASSERT_EQ(block->channels[0].type, type_float);
    ASSERT_EQ(block->channels[0].width, 32);
    ASSERT_TRUE(block->channels[0].is_signed);

    // a block is taken once
    ASSERT_FALSE(sink->take_block().has_value());
}


TEST(emulator_live_capture, emulator_live_block_not_taken) {

    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
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
            "content": "void main(){float mem; mem += 1.0; float out = mem*1.0;}",
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
              "is_output": false,
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
        }
      ],
      "interconnect":[],
      "emulation_time": 8,
      "deployment_mode": false
    })");

    // two blocks are complete and nobody takes the first one
    auto sink = std::make_shared<live_capture_sink>(1, 4);
    emulator_dispatcher manager;
    ASSERT_TRUE(manager.set_output_sink(sink));
    ASSERT_TRUE(manager.set_specs(specs));
    ASSERT_TRUE(manager.process());
    ASSERT_TRUE(sink->select_output(0, output_selection{"test", "out", 0, 0}));
    ASSERT_TRUE(manager.emulate());

    ASSERT_EQ(sink->dropped_blocks(), 1);
    auto block = sink->take_block();
    ASSERT_TRUE(block.has_value());
    ASSERT_EQ(block->sequence, 1);

    std::vector<float> reference = {5, 6, 7, 8};
    ASSERT_EQ(block_channel(block.value(), 0), reference);
}


TEST(emulator_live_capture, emulator_live_block_taken_while_running) {

    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
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
            "content": "void main(){float mem; mem += 1.0; float out = mem*1.0;}",
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
              "is_output": false,
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
        }
      ],
      "interconnect":[],
      "emulation_time": 8,
      "deployment_mode": false
    })");

    auto sink = std::make_shared<live_capture_sink>(1, 1);
    emulator_dispatcher manager;
    ASSERT_TRUE(manager.set_output_sink(sink));
    ASSERT_TRUE(manager.set_specs(specs));
    ASSERT_TRUE(manager.process());
    ASSERT_TRUE(sink->select_output(0, output_selection{"test", "out", 0, 0}));

    std::vector<float> taken;
    std::thread consumer([&] {
        while(taken.size() < 8) {
            if(!sink->wait_for_block(std::chrono::milliseconds(500))) break;
            if(auto block = sink->take_block()) taken.push_back(block_channel(block.value(), 0)[0]);
        }
    });
    ASSERT_TRUE(manager.emulate());
    consumer.join();

    // a consumer that is slower than the emulation misses blocks, the ones it gets are in order and none is lost twice
    ASSERT_FALSE(taken.empty());
    ASSERT_EQ(taken.back(), 8);
    ASSERT_EQ(taken.size() + sink->dropped_blocks(), 8);
    for(int i = 1; i < taken.size(); i++) {
        ASSERT_LT(taken[i - 1], taken[i]);
    }
}


TEST(emulator_live_capture, emulator_live_two_cores) {

    nlohmann::json specs = nlohmann::json::parse( R"({
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
            "content": "void main(){float mem; mem += 1.0; float out = mem*1.0;}",
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
              "is_output": false,
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
            "content": "void main(){float mem; mem += 1.0; float out = mem*1.0;}",
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
              "is_output": false,
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
      "emulation_time": 3,
      "deployment_mode": false
    })");

    auto sink = std::make_shared<live_capture_sink>(3, 3);
    emulator_dispatcher manager;
    ASSERT_TRUE(manager.set_output_sink(sink));
    ASSERT_TRUE(manager.set_specs(specs));
    ASSERT_TRUE(manager.process());

    // the two cores have an output with the same name, a channel is selected again before the emulation starts
    ASSERT_TRUE(sink->select_output(0, output_selection{"test_producer", "out", 0, 0}));
    ASSERT_TRUE(sink->select_output(1, output_selection{"test_producer_2", "out", 0, 0}));
    ASSERT_TRUE(sink->select_output(2, output_selection{"test_producer", "out", 0, 0}));
    ASSERT_TRUE(sink->select_output(2, output_selection{"test_producer_2", "out", 0, 0}));
    ASSERT_TRUE(sink->unselect_output(0));
    ASSERT_TRUE(sink->select_output(0, output_selection{"test_producer", "out", 0, 0}));
    ASSERT_TRUE(manager.emulate());

    auto block = sink->take_block();
    ASSERT_TRUE(block.has_value());

    std::vector<float> reference = {1, 2, 3};
    ASSERT_EQ(block_channel(block.value(), 0), reference);
    reference = {31, 32, 33};
    ASSERT_EQ(block_channel(block.value(), 1), reference);
    ASSERT_EQ(block_channel(block.value(), 2), reference);
}


TEST(emulator_live_capture, emulator_live_output_selection_errors) {

    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
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
            "content": "void main(){float mem; mem += 1.0; float out = mem*1.0;}",
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
              "is_output": false,
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
        }
      ],
      "interconnect":[],
      "emulation_time": 2,
      "deployment_mode": false
    })");

    auto sink = std::make_shared<live_capture_sink>(2, 2);

    // nothing to select before the emulation is set up
    ASSERT_FALSE(sink->select_output(0, output_selection{"test", "out", 0, 0}));

    emulator_dispatcher manager;
    ASSERT_TRUE(manager.set_output_sink(sink));
    ASSERT_TRUE(manager.set_specs(specs));
    ASSERT_TRUE(manager.process());

    // the output, the core, the channel of the core and the element do not exist
    ASSERT_FALSE(sink->select_output(0, output_selection{"test", "missing", 0, 0}));
    ASSERT_FALSE(sink->select_output(0, output_selection{"missing", "out", 0, 0}));
    ASSERT_FALSE(sink->select_output(0, output_selection{"test", "out", 1, 0}));
    ASSERT_FALSE(sink->select_output(0, output_selection{"test", "out", 0, 1}));

    // the capture has two channels
    ASSERT_FALSE(sink->select_output(2, output_selection{"test", "out", 0, 0}));
    ASSERT_FALSE(sink->unselect_output(2));

    // the specs set again keep the sink
    ASSERT_TRUE(manager.set_specs(specs));
    ASSERT_TRUE(manager.process());
    ASSERT_TRUE(sink->select_output(0, output_selection{"test", "out", 0, 0}));
    ASSERT_TRUE(manager.emulate());
    ASSERT_TRUE(sink->take_block().has_value());
}
