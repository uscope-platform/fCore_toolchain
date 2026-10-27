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

#include "../emulator_test_helpers.hpp"
#include "emulator/live_emulation.hpp"
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

TEST(emulator_live_emulation, emulator_live_run) {

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
      "emulation_time": 1,
      "deployment_mode": false
    })");

    live_emulation emulation(1, 4);
    ASSERT_TRUE(emulation.load(specs));
    ASSERT_TRUE(emulation.select_output(0, output_selection{"test", "out", 0, 0}));
    ASSERT_FALSE(emulation.running());
    ASSERT_TRUE(emulation.start());
    ASSERT_TRUE(emulation.running());

    // the specs ask for one second of a 1 Hz emulation, the live one does not end there
    uint64_t last_block = 0;
    while(last_block < 3) {
        ASSERT_TRUE(emulation.wait_for_block(std::chrono::milliseconds(2000)));
        auto block = emulation.take_block();
        if(!block.has_value()) continue;
        last_block = block->sequence;

        // the counter counts a sample in every round, whatever the blocks that were not taken
        float first = 4 * block->sequence + 1;
        std::vector<float> reference = {first, first + 1, first + 2, first + 3};
        ASSERT_EQ(block_channel(block.value(), 0), reference);
    }

    ASSERT_EQ(emulation.get_sampling_frequency(), 1);
    emulation.stop();
    ASSERT_FALSE(emulation.running());
    ASSERT_FALSE(emulation.get_error().has_value());
}


TEST(emulator_live_emulation, emulator_live_stop_and_start) {

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
      "emulation_time": 1,
      "deployment_mode": false
    })");

    live_emulation emulation(1, 4);
    ASSERT_TRUE(emulation.load(specs));
    ASSERT_TRUE(emulation.select_output(0, output_selection{"test", "out", 0, 0}));
    ASSERT_TRUE(emulation.start());
    ASSERT_TRUE(emulation.wait_for_block(std::chrono::milliseconds(2000)));
    emulation.stop();
    ASSERT_FALSE(emulation.running());

    // nothing is produced while it is stopped
    emulation.take_block();
    ASSERT_FALSE(emulation.wait_for_block(std::chrono::milliseconds(50)));

    // it goes on from where it stopped: the value of a sample says how many rounds went by
    ASSERT_TRUE(emulation.start());
    ASSERT_TRUE(emulation.wait_for_block(std::chrono::milliseconds(2000)));
    emulation.stop();
    auto block = emulation.take_block();
    ASSERT_TRUE(block.has_value());
    float first = 4 * block->sequence + 1;
    std::vector<float> reference = {first, first + 1, first + 2, first + 3};
    ASSERT_EQ(block_channel(block.value(), 0), reference);
}


TEST(emulator_live_emulation, emulator_live_set_input) {

    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
          "inputs": [
            {
              "name": "in_c",
              "is_vector": false,
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": true,
                "common_io": false
              },
              "source": {"type": "constant", "value": [1]}
            }
          ],
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
            "content": "void main(){float in_c; float out = in_c*2.0;}",
            "headers": []
          },
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
        }
      ],
      "interconnect":[],
      "emulation_time": 1,
      "deployment_mode": false
    })");

    live_emulation emulation(1, 4);
    ASSERT_TRUE(emulation.load(specs));
    ASSERT_TRUE(emulation.select_output(0, output_selection{"test", "out", 0, 0}));
    ASSERT_TRUE(emulation.start());
    ASSERT_TRUE(emulation.set_input("test", "in_c", 0, 5.0));

    // the output is twice the input, once the input is set it stays as it was set
    bool changed = false;
    for(int i = 0; i < 1000 && !changed; i++) {
        if(!emulation.wait_for_block(std::chrono::milliseconds(2000))) break;
        auto block = emulation.take_block();
        if(!block.has_value()) continue;
        bool new_value_seen = false;
        for(float sample: block_channel(block.value(), 0)) {
            if(sample == 10.0) new_value_seen = true;
            else ASSERT_EQ(sample, 2.0);
            // the old value is not back after the new one
            if(new_value_seen) ASSERT_EQ(sample, 10.0);
        }
        changed = new_value_seen;
    }
    ASSERT_TRUE(changed);
    emulation.stop();
}


TEST(emulator_live_emulation, emulator_live_set_input_errors) {

    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
          "inputs": [
            {
              "name": "in_c",
              "is_vector": false,
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": true,
                "common_io": false
              },
              "source": {"type": "constant", "value": [1]}
            }
          ],
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
            "content": "void main(){float in_c; float out = in_c*2.0;}",
            "headers": []
          },
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
        }
      ],
      "interconnect":[],
      "emulation_time": 1,
      "deployment_mode": false
    })");

    live_emulation emulation(1, 4);

    // nothing is loaded yet
    ASSERT_FALSE(emulation.set_input("test", "in_c", 0, 5.0));
    ASSERT_TRUE(emulation.load(specs));

    ASSERT_FALSE(emulation.set_input("missing", "in_c", 0, 5.0));
    ASSERT_FALSE(emulation.set_input("test", "missing", 0, 5.0));
    // the core has one channel
    ASSERT_FALSE(emulation.set_input("test", "in_c", 1, 5.0));
    ASSERT_TRUE(emulation.set_input("test", "in_c", 0, 5.0));
}


TEST(emulator_live_emulation, emulator_live_series_start_over) {

    nlohmann::json specs = nlohmann::json::parse( R"({
      "version": 2,
      "cores": [
        {
          "id": "test",
          "inputs": [
            {
              "name": "in_c",
              "is_vector": false,
              "metadata": {
                "type": "float",
                "width": 32,
                "signed": true,
                "common_io": false
              },
              "source": {"type": "series", "value": [1, 2, 3]}
            }
          ],
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
            "content": "void main(){float in_c; float out = in_c*1.0;}",
            "headers": []
          },
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
        }
      ],
      "interconnect":[],
      "emulation_time": 1,
      "deployment_mode": false
    })");

    live_emulation emulation(1, 6);
    ASSERT_TRUE(emulation.load(specs));
    ASSERT_TRUE(emulation.select_output(0, output_selection{"test", "out", 0, 0}));
    // only the constants can be set
    ASSERT_FALSE(emulation.set_input("test", "in_c", 0, 5.0));
    ASSERT_TRUE(emulation.start());

    // the series has three samples and a block six: every block is the series twice
    std::vector<float> reference = {1, 2, 3, 1, 2, 3};
    uint64_t last_block = 0;
    while(last_block < 3) {
        ASSERT_TRUE(emulation.wait_for_block(std::chrono::milliseconds(2000)));
        auto block = emulation.take_block();
        if(!block.has_value()) continue;
        last_block = block->sequence;
        ASSERT_EQ(block_channel(block.value(), 0), reference);
    }
    emulation.stop();
}


TEST(emulator_live_emulation, emulator_live_load_and_start_errors) {

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
      "emulation_time": 1,
      "deployment_mode": false
    })");

    live_emulation emulation(1, 4);

    // there is nothing to run
    ASSERT_FALSE(emulation.start());

    nlohmann::json invalid = specs;
    invalid.erase("version");
    ASSERT_FALSE(emulation.load(invalid));
    ASSERT_FALSE(emulation.start());

    // loading again stops the emulation that is running
    ASSERT_TRUE(emulation.load(specs));
    ASSERT_TRUE(emulation.start());
    ASSERT_TRUE(emulation.load(specs));
    ASSERT_FALSE(emulation.running());

    // the outputs have to be selected again after loading
    ASSERT_TRUE(emulation.start());
    ASSERT_TRUE(emulation.wait_for_block(std::chrono::milliseconds(2000)));
    auto block = emulation.take_block();
    ASSERT_TRUE(block.has_value());
    ASSERT_FALSE(block->channels[0].selected);
    emulation.stop();
}
