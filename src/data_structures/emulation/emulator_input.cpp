//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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
// limitations under the License.05/07/2021.

#include "data_structures/emulation/emulator_input.hpp"

#include <utility>

void emulator_input::set_data(std::vector<uint32_t> d) {
    data = std::move(d);
    input_source = emulator_in_type_vector;
}


void emulator_input::set_data(uint32_t d) {
    data = std::vector<uint32_t>();
    data.push_back(d);
    input_source = emulator_in_type_constant;
}


uint32_t emulator_input::get_data(uint32_t i) {
    if(input_source == emulator_in_type_constant){
        return data[0];
    } else{
        if(i>=data.size()){
            spdlog::critical("Input overflow, attempted to access: "+ name+ " at index: " + std::to_string(i));
            exit(-1);
        }
        return data[i];
    }
}