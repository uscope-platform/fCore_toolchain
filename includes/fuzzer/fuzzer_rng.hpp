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
#ifndef FCORE_TOOLCHAIN_FUZZER_RNG_HPP
#define FCORE_TOOLCHAIN_FUZZER_RNG_HPP
#include <vector>
#include <cstdint>
#include <random>

class fuzzer_rng {
public:
    fuzzer_rng(std::pair<uint32_t,uint32_t> uniform_bounds, std::pair<float, float> normal_parameters);
    fuzzer_rng(uint32_t seed);
    uint32_t generate_int();
    std::vector<uint32_t> generate_int_vect(uint32_t size);
    float generate_float();
    std::vector<float> generate_float_vect_normal(uint32_t size);
private:
    std::mt19937 rng;

    std::uniform_int_distribution<uint32_t> unif_dist;
    std::normal_distribution<float> normal_dist;
};


#endif //FCORE_TOOLCHAIN_FUZZER_RNG_HPP
