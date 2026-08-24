//  Copyright 2026 University of Nottingham
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
#include "fuzzer/fuzzer_rng.hpp"


fuzzer_rng::fuzzer_rng(uint32_t seed, std::pair<float, float> normal_parameters) :
    rng(seed),
    normal_dist(normal_parameters.first, normal_parameters.second) {

}


uint32_t fuzzer_rng::generate_int(std::pair<uint32_t, uint32_t> bounds) {
    auto dist = std::uniform_int_distribution(bounds.first, bounds.second);
    return dist(rng);
}


float fuzzer_rng::generate_float() {
    return normal_dist(rng);
}

std::vector<float> fuzzer_rng::generate_float_vect_normal(uint32_t size){
    std::vector<float> vec;
    vec.reserve(size);
    for (uint32_t i = 0; i < size; ++i) {
        vec.push_back(generate_float());
    }
    return vec;
}
