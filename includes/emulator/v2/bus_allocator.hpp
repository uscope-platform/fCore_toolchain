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

#include <unordered_set>
#include <string>

#include "data_structures/common/program_metadata.hpp"
#include "data_structures/emulation/v2/specs/emulator_specs.hpp"

namespace fcore::emulator_v2 {

    struct core_endpoint {
        std::string core_name;
        std::string source_name;
        core_iom_type endpoint_class;
        register_data_type type;
        bool is_vector;
        uint32_t vector_size;
        std::vector<uint32_t> initial_value;
        uint32_t channels;
        bool common_io;
        std::vector<uint32_t> bus_addresses;
        std::vector<uint32_t> desired_address;
    };


    struct endpoint_descriptor {
        std::string core_name;
        std::string port_name;

        friend bool operator==(const endpoint_descriptor &lhs, const endpoint_descriptor &rhs) {
            return std::tie(lhs.core_name, lhs.port_name) == std::tie(rhs.core_name, rhs.port_name);
        }

        friend bool operator!=(const endpoint_descriptor &lhs, const endpoint_descriptor &rhs) {
            return !(lhs == rhs);
        }
    };

    struct interconnect_descriptor {
        endpoint_descriptor source;
        endpoint_descriptor destination;
        std::vector<uint32_t> source_addresses;
        std::vector<uint32_t> destination_addresses;
        uint32_t source_vector_size;
        uint32_t dest_vector_size;
        uint32_t source_channels;
        uint32_t dest_channels;
        bool source_is_vector() const {
            return source_vector_size > 1;
        }
        bool destination_is_vector() const {
            return  dest_vector_size > 1;
        }
        bool source_is_multichannel() const {
            return source_channels > 1;
        }
        bool destination_is_multichannel() const {
            return dest_channels > 1;
        }
        friend bool operator==(const interconnect_descriptor &lhs, const interconnect_descriptor &rhs) {
            return std::tie(lhs.source,lhs.source_addresses,lhs.destination_addresses, lhs.destination) == std::tie(rhs.source,rhs.source_addresses,rhs.destination_addresses, rhs.destination);
        }

        friend bool operator!=(const interconnect_descriptor &lhs, const interconnect_descriptor &rhs) {
            return !(lhs == rhs);
        }
    };

    struct allocation {
        endpoint_descriptor endpoint;
        std::vector<uint32_t> addresses;
    };

    struct output_metadata {
        std::string core_name;
        std::string port_name;
        uint32_t vector_size;
        uint32_t channels;
    };


    class bus_allocator {
    public:
        bus_allocator() = default;
        void set_emulation_specs(const emulator_specs &specs);
        std::vector<allocation> allocate_bus_addresses(std::vector<interconnect_descriptor> &interconnects);
        void update_sources(std::vector<interconnect_descriptor> &interconnects);
        void allocate_additional_outputs(std::vector<allocation> &current_allocations);
        void allocate_independent_inputs(const std::vector<allocation> &current_allocations);
        std::vector<uint32_t> allocate_bus_address(uint32_t vector_size, std::set<uint32_t> local_forbidden_addresses,
            const std::vector<uint32_t> &desired_addresses
        ) const;

        std::unordered_map<std::string, core_iom> get_dma_io(const std::string &core_name);

        uint32_t get_input_address(const std::string & core, const std::string & input, uint32_t array_index);
        uint32_t get_output_address(const std::string & core, const std::string & input, uint32_t array_index);

        core_endpoint get_slot_source(const std::string & core, const std::string & slot_name);

        std::vector<output_metadata> get_outputs();

        bus_allocator(const bus_allocator &other) = delete;
        bus_allocator(bus_allocator &&other) noexcept = delete;
        bus_allocator & operator=(const bus_allocator &other) = delete;
        bus_allocator & operator=(bus_allocator &&other) noexcept = delete;

        std::vector<core_endpoint> get_memories(const std::string &core_name);
        std::vector<interconnect_descriptor> get_interconnects(const std::string &core_name);
    private:
        std::vector<interconnect_descriptor> interconnect_mapping;

        std::set<uint32_t> global_forbidden_addresses;

        std::unordered_map<std::string, std::unordered_map<std::string, core_endpoint>> sources_map;
        std::unordered_map<std::string, std::unordered_map<std::string, core_endpoint>> destinations_map;

        std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>> bus_allocations;

        std::set<uint32_t> allocated_addresses;
        std::set<uint32_t> desired_addresses;

        uint32_t current_index = 1;
    };

}



#endif //BUS_ALLOCATOR_HPP