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

#include <string>
#include <variant>
#include <cstdint>
#include <set>
#include "emulator/emulator_metadata_common.hpp"

namespace fcore::emulator {


    typedef enum {
        prog_type_c=0,
        prog_type_asm=1
    } program_data_type;

    struct core_io {
        std::set<std::string> inputs;
        std::set<std::string> outputs;
        std::set<std::string> memories;
    };

    struct program_data {
        std::string content;
        program_data_type type;
        core_io io;
        std::vector<std::string> headers;
    };

    struct iom_metadata {
        register_data_type type;
        uint16_t width;
        bool is_signed;
    };

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


    struct emulator_output_specs {
        std::string name;
        register_data_type output_type;
        iom_metadata metadata;
        std::vector<uint32_t> address;
    };

    struct emulator_input_specs {
        std::string name;
        iom_metadata metadata;
        source_type_t source_type;
        std::vector<std::variant<std::vector<uint32_t>, std::vector<float>>> data;
        std::vector<uint32_t> address;
        std::vector<uint32_t> channel;
        std::vector<std::string> vector_labels;
    };

    struct emulator_memory_specs {
        std::string name;
        iom_metadata metadata;
        bool is_output;
        std::vector<uint32_t> address;
        std::variant<std::vector<float>, std::vector<uint32_t>> value;
    };

    struct deployment_options {
        uint64_t rom_address;
        uint64_t control_address;
        bool has_reciprocal;
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

#endif //FCORE_TOOLCHAIN_EMULATOR_CORE_HPP
