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
#include <nlohmann/json.hpp>
#include <string>

#include "data_structures/common/program_metadata.hpp"
#include "data_structures/emulation/v2/specs/emulator_specs.hpp"

namespace fcore::emulator_v2 {

    struct core_endpoint {
        std::string core_name;
        std::string source_name;
        core_iom_type endpoint_class;
        bool is_vector;
        uint32_t vector_size;
        std::vector<uint32_t> initial_value;
        uint32_t channels;
        std::vector<uint32_t> bus_addresses;
        iom_metadata metadata;
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

    struct endpoint_shape {
        uint16_t size;
        uint16_t channels;
    };

    struct interconnect_descriptor {
        endpoint_descriptor source;
        endpoint_descriptor destination;
        std::vector<uint32_t> source_addresses;
        std::vector<uint32_t> destination_addresses;
        endpoint_shape source_shape;
        endpoint_shape destination_shape;
        bool partial_transfer;
        std::pair<uint8_t, uint8_t> partial_channels;
        iom_metadata source_metadata;

        dma_channel_type get_type() const {
            if(partial_transfer) {
                return dma_link_partial;
            }
            if(source_shape.size == 1 && destination_shape.size == 1 ) {
                if(source_shape.channels == 1 && destination_shape.channels == 1) {
                    return dma_link_scalar;
                }
                return dma_link_vector;
            }
            if(source_shape.size  == 1 && destination_shape.size  > 1 ) {
                return dma_link_gather;
            }
            if(source_shape.size  >1 && destination_shape.size  == 1) {
                return dma_link_scatter;
            }
            return  dma_link_2d_vector;
        };

        friend bool operator==(const interconnect_descriptor &lhs, const interconnect_descriptor &rhs) {
            return std::tie(lhs.source,lhs.source_addresses,lhs.destination_addresses, lhs.destination) == std::tie(rhs.source,rhs.source_addresses,rhs.destination_addresses, rhs.destination);
        }

        friend bool operator!=(const interconnect_descriptor &lhs, const interconnect_descriptor &rhs) {
            return !(lhs == rhs);
        }
    };

    struct output_metadata {
        std::string core_name;
        std::string port_name;
        uint32_t vector_size;
        uint32_t channels;
        std::vector<uint32_t> addresses;
        iom_metadata metadata;
    };


    class bus_allocator {
    public:
        bus_allocator() = default;
        void set_emulation_specs(const emulator_specs &specs);
        void allocate_bus_addresses(std::vector<interconnect_descriptor> &interconnects);
        void update_sources(std::vector<interconnect_descriptor> &interconnects);
        void allocate_additional_outputs();
        void allocate_independent_inputs();
        std::vector<uint32_t> allocate_bus_address(uint32_t vector_size, std::set<uint32_t> local_forbidden_addresses,
            const std::vector<uint32_t> &desired_addresses
        ) const;

        std::unordered_map<std::string, core_iom> get_dma_io(const std::string &core_name);

        uint32_t get_input_address(const std::string & core, const std::string & input, uint32_t array_index);
        uint32_t get_output_address(const std::string & core, const std::string & output, uint32_t array_index);
        uint32_t get_free_address(const std::string & core, const std::string & output, uint32_t array_index);

        core_endpoint get_slot_source(const std::string & core, const std::string & slot_name);

        std::unordered_map<std::string, std::string> dump_bus();

        std::vector<output_metadata> get_outputs();

        bus_allocator(const bus_allocator &other) = delete;
        bus_allocator(bus_allocator &&other) noexcept = delete;
        bus_allocator & operator=(const bus_allocator &other) = delete;
        bus_allocator & operator=(bus_allocator &&other) noexcept = delete;

        std::vector<core_endpoint> get_memories(const std::string &core_name);
        std::vector<interconnect_descriptor> get_interconnects();

        void add_source(const std::string &c,const std::string &io,  core_endpoint &ep) {sources_map[c][io] = ep;}
        void add_destination(const std::string &c,const std::string &io, core_endpoint &ep) {destinations_map[c][io] = ep;}

    private:

        bool is_register(const std::string &r);
        std::vector<interconnect_descriptor> interconnect_mapping;

        std::set<uint32_t> global_forbidden_addresses;

        std::unordered_map<std::string, std::unordered_map<std::string, core_endpoint>> sources_map;
        std::unordered_map<std::string, std::unordered_map<std::string, core_endpoint>> destinations_map;

        std::set<std::pair<std::string, std::string>> waveform_inputs;

    };

}



#endif //BUS_ALLOCATOR_HPP