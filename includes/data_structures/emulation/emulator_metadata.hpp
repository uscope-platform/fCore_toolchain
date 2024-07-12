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

#ifndef FCORE_TOOLCHAIN_EMULATOR_METADATA_HPP
#define FCORE_TOOLCHAIN_EMULATOR_METADATA_HPP


#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <set>
#include "data_structures/common/io_map_entry.hpp"

namespace fcore{

// FORWARD DECLARATIONS
    class emulator_backend;

    typedef std::unordered_map<uint32_t , std::shared_ptr<std::vector<uint32_t>>> core_memory_pool_t;

    typedef struct{
        unsigned int channel;
        unsigned int address;
    } register_spec_t;

    typedef struct{
        std::string source;
        std::string destination;
        std::vector<std::pair<register_spec_t, register_spec_t>> connections;
    }interconnect_t;

    typedef enum {
        efi_none = 0,
        efi_trig = 1,
        efi_sort = 2,
    } efi_implementation_t;

    typedef enum {
        comparator_none = 0,
        comparator_reducing= 1,
        comparator_full = 2
    } comparator_type_t;



}

#endif //FCORE_TOOLCHAIN_EMULATOR_METADATA_HPP
