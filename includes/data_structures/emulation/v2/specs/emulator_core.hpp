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

#ifndef FCORE_TOOLCHAIN_EMULATOR_CORE_V2_HPP
#define FCORE_TOOLCHAIN_EMULATOR_CORE_V2_HPP

#include <string>
#include <variant>
#include <cstdint>
#include <set>
#include <emulator/emulator_metadata_common.hpp>

namespace fcore::emulator_v2 {


    typedef enum {
        prog_type_c=0,
        prog_type_asm=1
    } program_data_type;

    struct program_data {
        std::string content;
        program_data_type type;
        std::vector<std::string> headers;
    };


    static std::map<std::string, register_data_type > data_type_map = {
            {"float", type_float},
            {"integer", type_uint}
    };

    typedef enum {
        scalar_endpoint = 0,
        vector_endpoint = 1
    } endpoint_type;

    static std::map<std::string, endpoint_type > endpoint_type_map = {
            {"scalar", scalar_endpoint},
            {"vector", vector_endpoint}
    };


    struct emulator_output_specs {
        std::string name;
        bool is_vector;
        uint32_t vector_size;
        iom_metadata metadata;

    };

    struct emulator_input_specs {
        std::string name;
        iom_metadata metadata;
        source_type_t source_type;
        std::variant<square_wave_parameters, sine_wave_parameters, triangle_wave_parameters> waveform_parameters;
        std::vector<std::variant<std::vector<uint32_t>, std::vector<float>>> data;
        std::vector<uint32_t> channel;
        bool is_vector;
        uint32_t vector_size;
        std::vector<std::string> vector_labels;
    };

    struct emulator_memory_specs {
        std::string name;
        iom_metadata metadata;
        bool is_output;
        bool is_input;
        bool is_vector;
        uint32_t vector_size;
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
        std::vector<emulator_input_specs> inputs;
        std::vector<emulator_memory_specs> memories;

        deployment_options deployment;
    };


} // fcore

#endif //FCORE_TOOLCHAIN_EMULATOR_CORE_V2_HPP
