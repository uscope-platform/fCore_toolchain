//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_EMULATOR_METADATA_V2_HPP
#define FCORE_TOOLCHAIN_EMULATOR_METADATA_V2_HPP


#include <vector>
#include <cstdint>
#include <unordered_map>
#include <memory>

#include "data_structures/common/program_metadata.hpp"

namespace fcore::emulator_v2 {

// FORWARD DECLARATIONS
    class emulator_backend;

    typedef std::unordered_map<uint32_t , std::vector<uint32_t>> core_memory_pool_t;

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

#endif //FCORE_TOOLCHAIN_EMULATOR_METADATA_V2_HPP
