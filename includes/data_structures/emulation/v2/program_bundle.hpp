

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

#ifndef PROGRAM_BUNDLE_V2_HPP
#define PROGRAM_BUNDLE_V2_HPP

#include <string>
#include <vector>
#include <set>
#include <cstdint>

#include "data_structures/common/io_map_entry.hpp"
#include "data_structures/emulation/v2/emulator_metadata.hpp"
#include "specs/emulator_specs.hpp"

namespace fcore::emulator_v2 {

    class program_bundle{
    public:
        std::string name;
        fcore_program program;
        std::set<io_map_entry> io;
        std::vector<emulator_memory_specs> memories;
        std::vector<emulator_input_specs> input;
        uint32_t sampling_frequency;
        uint32_t execution_order;
        uint32_t active_channels;
        uint32_t n_outputs;
        efi_implementation_t efi_selector;
        comparator_type_t comparator_type;
    };
}

#endif //PROGRAM_BUNDLE_V2_HPP
