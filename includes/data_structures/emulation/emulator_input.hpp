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

#ifndef FCORE_TOOLCHAIN_EMULATOR_INPUT_HPP
#define FCORE_TOOLCHAIN_EMULATOR_INPUT_HPP

#include <utility>
#include <vector>
#include <string>
#include <cstdint>
#include <spdlog/spdlog.h>

typedef enum {emulator_in_type_constant = 0, emulator_in_type_vector = 1} emulator_input_type;

class emulator_input {
public:
    emulator_input() = default;
    void set_target_address(uint32_t a) {target_address = a;};
    uint32_t get_address() const{return target_address;};
    void set_target_channel(uint32_t c) {target_channel = c;};
    uint32_t get_channel() const{return target_channel;};
    void set_data(std::vector<uint32_t> d);
    void set_data(uint32_t d);
    uint32_t get_data(uint32_t i);
    std::vector<uint32_t> get_data() const { return data;};
    void set_type(std::string s){type = std::move(s);};
    void set_name(std::string n){name = std::move(n);};
    std::string get_name()const{ return name;};
    std::string get_type() const {return type;};
private:
    uint32_t target_address;
    std::vector<uint32_t> data;
    uint32_t target_channel;
    std::string name;
    emulator_input_type input_source = emulator_in_type_constant;
    std::string type;
};


#endif //FCORE_TOOLCHAIN_EMULATOR_INPUT_HPP
