

//  Copyright  2026 University of Nottingham
//  Author: Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#ifndef FCORE_TOOLCHAIN_FUZZER_METADATA_HPP
#define FCORE_TOOLCHAIN_FUZZER_METADATA_HPP

#include <cstdint>
#include <vector>
#include <map>
#include <string>

struct fuzzer_config {
    uint8_t min_inputs = 1;
    uint8_t max_inputs = 5;
    uint8_t active_regs = 5;
    uint8_t min_program_size = 3;
    uint16_t max_program_size = 150;
    uint32_t rng_seed;
    std::pair<float, float> rng_float_params;
};

struct fuzzing_package {
    std::vector<uint32_t> binary;
    std::map<uint32_t, float> inputs;
    std::string reference;
};

#endif //FCORE_TOOLCHAIN_FUZZER_METADATA_HPP
