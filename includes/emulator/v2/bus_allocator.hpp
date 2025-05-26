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


#ifndef BUS_ALLOCATOR_HPP
#define BUS_ALLOCATOR_HPP

#include "data_structures/common/program_metadata.hpp"
#include "data_structures/emulation/v2/specs/emulator_specs.hpp"

namespace fcore::emulator_v2 {

    struct core_endpoint {
        std::string core_name;
        std::string source_name;
        core_iom_type endpoint_class;
        register_data_type type;
        std::vector<uint32_t> initial_value;
        uint32_t channel;
        bool common_io;
    };

    struct bus_slot {

        uint32_t address;
        core_endpoint source;
        std::vector<core_endpoint> destination;
    };


    class bus_allocator {
    public:
        bus_allocator() = default;
        void set_emulation_specs(const emulator_specs &specs);

        uint32_t allocate_slot();
        std::unordered_map<std::string, core_iom> get_dma_io(std::string core_name);
        std::vector<bus_slot> get_bus_map() const {return bus_map;}

        uint32_t get_address(const std::string & core, const std::string & input, uint32_t channel);

        void clear();

        std::vector<bus_slot> get_memories();

    private:
        std::vector<bus_slot> bus_map;

        uint32_t current_index = 1;
    };
}




#endif //BUS_ALLOCATOR_HPP
