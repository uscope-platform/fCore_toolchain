

//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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

#include "data_structures/emulation/emulator_output.hpp"

fcore::emulator_output::emulator_output(const std::string& i, uint32_t size) {
    if(size == 1){
        id = {i};
        data.emplace_back();
    } else {
        for(int n = 0; n<size; n++){
            id.push_back(i + std::to_string(n));
            data.emplace_back();
        }
    }
    vector_size = size;
}

void fcore::emulator_output::add_data_point(const std::vector<uint32_t>& dp) {
    if(dp.size()!=vector_size){
        auto message = "Wrong dimension for output data point";
        spdlog::critical(message);
        throw std::runtime_error(message);
    }
    for(int n = 0; n<vector_size; n++){
        data[n].push_back(dp[n]);
    }
}

void fcore::emulator_output::add_data_point(uint32_t dp) {
    if(vector_size!=1){
        auto message = "Attempted to add a single value to an output vector";
        spdlog::critical(message);
        throw std::runtime_error(message);
    }
    data[0].push_back(dp);
}

void fcore::emulator_output::repeat_last_data_point() {
    for(int n = 0; n<vector_size; n++){
        data[n].push_back(data[n].back());
    }
}

std::vector<std::vector<float>> fcore::emulator_output::get_float_data() {
    std::vector<std::vector<float>> ret_val;

    for(const auto &vect:data){
        std::vector<float> ds;
        for(const auto &item:vect){
            ds.push_back(emulator::uint32_to_float(item));
        }
        ret_val.push_back(ds);
    }
    return ret_val;
}
