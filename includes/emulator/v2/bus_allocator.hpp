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
        uint32_t channels;
        bool common_io;
    };

    struct bus_slot {

        std::vector<uint32_t> bus_address;
        uint32_t io_address;
        uint32_t n_channels;
        core_endpoint source;
        std::vector<core_endpoint> destination;
    };


    class bus_allocator {
    public:
        bus_allocator() = default;
        void set_emulation_specs(const emulator_specs &specs);

        uint32_t allocate_slot(uint16_t desired_address);
        std::unordered_map<std::string, core_iom> get_dma_io(std::string core_name);
        std::vector<bus_slot> get_bus_map() const {return bus_map;}

        uint32_t get_input_address(const std::string & core, const std::string & input, uint32_t channel);
        uint32_t get_output_address(const std::string & core, const std::string & input, uint32_t channel);
        uint32_t allocate_inputs_address(const std::string & core, const std::string & input);

        core_endpoint get_slot_source(const std::string & core, const std::string & slot_name);

        bus_allocator(const bus_allocator &other) = delete;

        bus_allocator(bus_allocator &&other) noexcept = delete;

        bus_allocator & operator=(const bus_allocator &other) = delete;

        bus_allocator & operator=(bus_allocator &&other) noexcept = delete;

        std::vector<bus_slot> get_memories();
        std::vector<bus_slot> get_interconnects(const std::string &core_name);

    private:
        std::vector<bus_slot> bus_map;
        std::unordered_map<std::string, std::unordered_map<std::string, core_endpoint>> sources_map;
        std::unordered_map<std::string, std::unordered_map<std::string, core_endpoint>> destinations_map;
        std::set<uint32_t> allocated_addresses;
        std::set<uint32_t> desired_addresses;
        std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>> inputs_address_mapping;
        uint32_t current_index = 1;
    };
}




#endif //BUS_ALLOCATOR_HPP
