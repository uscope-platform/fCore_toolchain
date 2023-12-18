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

#ifndef FCORE_TOOLCHAIN_EMULATOR_METADATA_HPP
#define FCORE_TOOLCHAIN_EMULATOR_METADATA_HPP


#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include "data_structures/emulation/emulator_input_factory.hpp"


// FORWARD DECLARATIONS
class emulator;

typedef enum {
    type_uint32 = 1,
    type_float = 2,
} emulator_types_t;

typedef struct {
    int reg_n;
    emulator_types_t type;
    std::string name;
} emulator_output_t;

typedef struct{
    unsigned int channel;
    unsigned int address;
} register_spec_t;

typedef struct{
    std::string source;
    std::string destination;
    std::vector<std::pair<register_spec_t, register_spec_t>> connections;
}interconnect_t;



class emulator_metadata {
public:
    emulator_metadata() = default;
    std::unordered_map<std::string, emulator_input> input;
    std::vector<emulator_output_t> output_specs;
    std::unordered_map<unsigned int, std::pair<std::string, std::string>> output_types;
    std::unordered_map<unsigned int, uint32_t> memory_init;
    std::shared_ptr<emulator> emu;
    int active_channels;
    std::string efi_implementation;
    std::string comparator_type;
    bool io_remapping_active;
    std::unordered_map<uint16_t, uint16_t> io_map;
    std::unordered_map<int, std::unordered_map<int, std::vector<uint32_t>>> outputs;
};



typedef  enum {explicit_ordering=1,implicit_ordering=2,no_ordering=0}cores_ordering_t;


#endif //FCORE_TOOLCHAIN_EMULATOR_METADATA_HPP
