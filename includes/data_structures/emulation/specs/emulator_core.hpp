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

#ifndef FCORE_TOOLCHAIN_EMULATOR_CORE_HPP
#define FCORE_TOOLCHAIN_EMULATOR_CORE_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <variant>
#include <cstdint>
#include <set>

namespace fcore::emulator {

    struct core_io {
        std::set<std::string> inputs;
        std::set<std::string> outputs;
        std::set<std::string> memories;
    };

    struct program_data {
        std::string content;
        core_io io;
        std::vector<std::string> headers;
    };

    typedef enum {
        type_float=0,
        type_uint=1
    } register_data_type;

    static std::unordered_map<std::string, register_data_type > data_type_map = {
            {"float", type_float},
            {"integer", type_uint}
    };

    typedef enum {
        scalar_endpoint = 0,
        vector_endpoint = 1
    } endpoint_type;

    static std::unordered_map<std::string, endpoint_type > endpoint_type_map = {
            {"scalar", scalar_endpoint},
            {"vector", vector_endpoint}
    };

    typedef enum {
        constant_input = 0,
        time_series_input = 1
    } input_type;

    static std::unordered_map<std::string, input_type > input_type_map = {
            {"constant", constant_input},
            {"file", time_series_input}
    };

    struct emulator_output_specs {
        std::string name;
        register_data_type data_type;
        endpoint_type type;
        std::vector<uint32_t> address;
    };

    struct emulator_input_specs {
        std::string name;
        endpoint_type type;
        register_data_type data_type;
        input_type source_type;
        std::vector<std::variant<std::vector<uint32_t>, std::vector<float>>> data;
        std::vector<uint32_t> address;
        std::vector<uint32_t> channel;
    };

    struct emulator_memory_specs {
        std::string name;
        register_data_type data_type;
        bool is_output;
        std::vector<uint32_t> address;
        std::variant<std::vector<float>, std::vector<uint32_t>> value;
    };

    struct emulator_core {
        std::string id;
        uint16_t channels;
        uint16_t order;
        uint32_t sampling_frequency;
        std::map<std::string, std::string> options;
        program_data program;

        std::vector<emulator_output_specs> outputs;
        std::unordered_map<std::string, emulator_input_specs> inputs;
        std::vector<emulator_memory_specs> memories;
    };


} // fcore

#endif //FCORE_TOOLCHAIN_EMULATOR_CORE_HPP
