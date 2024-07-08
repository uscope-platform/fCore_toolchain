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
#include "data_structures/emulation/emulator_input_factory.hpp"

namespace fcore{

// FORWARD DECLARATIONS
    class emulator_backend;

    typedef std::unordered_map<uint32_t , std::shared_ptr<std::vector<uint32_t>>> core_memory_pool_t;

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


    class emulator_metadata {
    public:
        emulator_metadata() = default;
        std::unordered_map<std::string, emulator_input> input;
        std::unordered_map<uint32_t, uint32_t> memory_init;
        std::shared_ptr<emulator_backend> emu;
        uint32_t execution_order;
        int active_channels;
        std::set<io_map_entry> io_map_set;
        efi_implementation_t efi_selector;
        comparator_type_t comparator_type;
    };



    typedef  enum {explicit_ordering=1,implicit_ordering=2,no_ordering=0}cores_ordering_t;

}

#endif //FCORE_TOOLCHAIN_EMULATOR_METADATA_HPP
