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

#include "emulator/v2/bus_allocator.hpp"

#include "emulator/v2/backend/emulator_backend.hpp"

namespace fcore::emulator_v2 {

    void bus_allocator::set_emulation_specs(const emulator_specs &specs) {

        sources_map.clear();
        destinations_map.clear();

        for(auto &core:specs.cores) {
            for(auto &in:core.inputs) {
                core_endpoint ep;
                ep.core_name = core.id;
                ep.source_name = in.name;
                ep.channels = core.channels;
                ep.is_vector = in.is_vector;
                ep.vector_size = in.vector_size;
                ep.endpoint_class = core_iom_input;
                ep.metadata = in.metadata;
                if(in.source_type == random_input) random_inputs.insert({core.id, in.name});
                destinations_map[core.id][in.name] = ep;
            }
            for(auto &out:core.outputs) {
                core_endpoint ep;
                ep.core_name = core.id;
                ep.source_name = out.name;
                ep.channels = core.channels;
                ep.is_vector = out.is_vector;
                ep.vector_size = out.vector_size;
                ep.endpoint_class = core_iom_output;
                ep.metadata = out.metadata;
                sources_map[core.id][out.name] = ep;

            }
            for(auto &mem:core.memories) {
                for(int i = 0; i<core.channels; i++) {
                    core_endpoint ep;
                    ep.core_name = core.id;
                    ep.source_name = mem.name;
                    if(std::holds_alternative<std::vector<float>>(mem.value)) {
                        ep.metadata.type = type_float;
                        ep.initial_value = emulator_backend::float_to_uint32_v(std::get<std::vector<float>>(mem.value));
                    } else {
                        ep.metadata.type = type_uint;
                        ep.initial_value = std::get<std::vector<uint32_t>>(mem.value);
                    }
                    ep.endpoint_class = core_iom_memory;
                    ep.metadata.is_common_io = false;
                    ep.is_vector = false;
                    ep.vector_size = 1;
                    ep.channels = core.channels;
                    ep.metadata.io_address = mem.metadata.io_address;
                    ep.metadata = mem.metadata;

                    if(mem.is_input) {
                        destinations_map[core.id][mem.name] = ep;
                    }
                    if(mem.is_output | !mem.is_input) {
                        sources_map[core.id][mem.name] = ep;
                    }
                }
            }
        }


        for(auto &ic:specs.interconnects) {
            auto src_core = ic.source_endpoint.substr(0, ic.source_endpoint.find('.'));\
            auto src_port = ic.source_endpoint.substr(ic.source_endpoint.find('.')+1, ic.source_endpoint.size());
            auto dst_core = ic.destination_endpoint.substr(0, ic.destination_endpoint.find('.'));
            auto dst_port = ic.destination_endpoint.substr(ic.destination_endpoint.find('.')+1, ic.destination_endpoint.size());
            interconnect_descriptor id;
            if(!sources_map.contains(src_core)) {
                throw std::runtime_error("Source core ("+ src_core + ") not found for interconnect: " + ic.source_endpoint + " -> " + ic.destination_endpoint);
            }
            if(!destinations_map.contains(dst_core)) {
                throw std::runtime_error("Destination core ("+ dst_core + ") not found for interconnect: " + ic.source_endpoint + " -> " + ic.destination_endpoint);
            }

            if(!sources_map.at(src_core).contains(src_port)) {
                throw std::runtime_error("Source core " + src_core + " does not have a port named " + src_port);
            }
            if(!destinations_map.at(dst_core).contains(dst_port)) {
                throw std::runtime_error("Destination core " + dst_core + " does not have a port named " + dst_port);
            }

            auto source_descriptor= sources_map.at(src_core).at(src_port);
            auto dest_descriptor= destinations_map.at(dst_core).at(dst_port);
            id.source = {src_core, src_port};
            id.destination = {dst_core, dst_port};
            id.source_shape.size = source_descriptor.vector_size;
            id.destination_shape.size = dest_descriptor.vector_size;
            id.source_metadata = source_descriptor.metadata;

            id.source_shape.channels = source_descriptor.channels;
            id.destination_shape.channels = dest_descriptor.channels;
            id.partial_transfer = false;
            if(ic.source_channel != -1 && ic.destination_channel != -1) {
                id.partial_channels = {ic.source_channel, ic.destination_channel};
                id.partial_transfer = true;
            }
            interconnect_mapping.push_back(id);

        }

        allocate_bus_addresses(interconnect_mapping);
        update_sources(interconnect_mapping);
        allocate_additional_outputs();
        allocate_independent_inputs();
    }

    void bus_allocator::allocate_bus_addresses(std::vector<interconnect_descriptor> &interconnects) {

        for(auto &[core_name, destinations]:destinations_map) {
            for(auto &[port_name, dest]: destinations) {
                for(auto &ic: interconnects) {
                    if(ic.destination.core_name == core_name && ic.destination.port_name== port_name) {
                        if(ic.destination_shape.size > 1 && ic.source_shape.size == 1){ // gather allocation
                            dest.bus_addresses = allocate_bus_address(dest.vector_size, {}, dest.metadata.io_address);
                            ic.source_addresses = {dest.bus_addresses[0]};
                            ic.destination_addresses = dest.bus_addresses;
                        } else if (ic.source_shape.size > 1 && ic.destination_shape.size == 1) { // scatter allocation
                            ic.source_addresses = allocate_bus_address(ic.source_shape.size, {}, dest.metadata.io_address);
                            dest.bus_addresses = {ic.source_addresses[0]};
                            ic.destination_addresses = dest.bus_addresses;
                        } else {
                            dest.bus_addresses = allocate_bus_address(dest.vector_size, {}, dest.metadata.io_address);
                            ic.source_addresses = dest.bus_addresses;
                            ic.destination_addresses = dest.bus_addresses;
                        }

                        global_forbidden_addresses.insert( dest.bus_addresses.begin(),  dest.bus_addresses.end());
                    }
                }
                if(random_inputs.contains({dest.core_name, dest.source_name})) {
                    dest.bus_addresses = allocate_bus_address(dest.vector_size, {}, dest.metadata.io_address);
                    global_forbidden_addresses.insert( dest.bus_addresses.begin(),  dest.bus_addresses.end());
                }
            }
        }
    }

    void bus_allocator::update_sources(std::vector<interconnect_descriptor> &interconnects) {
        for(auto &ic:interconnects) {
            sources_map.at(ic.source.core_name).at(ic.source.port_name).bus_addresses = ic.source_addresses;
            global_forbidden_addresses.insert( ic.source_addresses.begin(),  ic.source_addresses.end());
        }
    }

    void bus_allocator::allocate_additional_outputs() {

        for(auto &[core_name, sources]: sources_map) {
            for(auto &[port_name, src]:sources) {
                if(src.bus_addresses.empty()) {

                    if(is_register(src.source_name)) src.metadata.io_address = {static_cast<uint32_t>(std::stoul(src.source_name.substr(1)))};
                    src.bus_addresses = allocate_bus_address(src.vector_size, {}, src.metadata.io_address);
                    global_forbidden_addresses.insert(src.bus_addresses.begin(), src.bus_addresses.end());
                }
            }
        }
    }

    void bus_allocator::allocate_independent_inputs() {

        for(auto &destinations: destinations_map | std::views::values) {
        std::set<uint32_t> local_allocated_addresses;
            for(auto &dest: destinations | std::views::values) {
                if(dest.bus_addresses.empty()) {

                    if(is_register(dest.source_name)) dest.metadata.io_address = {static_cast<uint32_t>(std::stoul(dest.source_name.substr(1)))};
                    dest.bus_addresses = allocate_bus_address(dest.vector_size, local_allocated_addresses, dest.metadata.io_address);
                    local_allocated_addresses.insert( dest.bus_addresses.begin(),  dest.bus_addresses.end());

                }
            }
        }
    }

    std::vector<uint32_t> bus_allocator::allocate_bus_address(uint32_t vector_size,
        std::set<uint32_t> local_forbidden_addresses, const std::vector<uint32_t> &desired_addresses) const {

        auto  ret = std::vector<uint32_t>(vector_size, 0);
        uint32_t tentative_address = 1;

        std::vector<u_int32_t> desired_array;
        if(desired_addresses.size() == vector_size)
            desired_array = desired_addresses;
        else
            desired_array = std::vector<uint32_t>(vector_size, 0);

        for(int i = 0; i< vector_size; i++) {
            if(
                !global_forbidden_addresses.contains(desired_array[i]) &&
                !local_forbidden_addresses.contains(desired_array[i]) &&
                desired_array[i] != 0
                ) {
                ret[i] = desired_array[i];
                local_forbidden_addresses.insert(desired_array[i]);
            }else {
                while(global_forbidden_addresses.contains(tentative_address) || local_forbidden_addresses.contains(tentative_address)) tentative_address++;
                ret[i] = tentative_address;
                tentative_address++;
            }
        }
        return ret;
    }


    std::unordered_map<std::string, core_iom> bus_allocator::get_dma_io(const std::string &core_name) {

        std::unordered_map<std::string, core_iom> ret_val;
         for(auto &[port_name, endpoint]:sources_map[core_name]) {
            if(ret_val.contains(port_name)) {

            } else {
                core_iom iom;
                iom.address = endpoint.bus_addresses;
                iom.common_io = endpoint.metadata.is_common_io;
                iom.type = endpoint.endpoint_class;
                ret_val[port_name] = iom;
            }
        }

        for(auto &item:destinations_map[core_name] | std::views::values) {
            core_iom iom;
            iom.address = item.bus_addresses;
            iom.common_io = item.metadata.is_common_io;
            iom.type = item.endpoint_class;
            ret_val[item.source_name] = iom;
        }
        return ret_val;
    }

    uint32_t bus_allocator::get_input_address(const std::string &core, const std::string &input, uint32_t array_index) {
        return destinations_map.at(core).at(input).bus_addresses.at(array_index);
    }

    uint32_t bus_allocator::get_output_address(const std::string &core, const std::string &output, uint32_t array_index) {
        return sources_map.at(core).at(output).bus_addresses.at(array_index);
    }

    uint32_t bus_allocator::get_free_address(const std::string &core, const std::string &output, uint32_t array_index) {
        auto addr = allocate_bus_address(1, {}, {0});
        global_forbidden_addresses.insert(addr[0]);
        return addr[0];
    }

     core_endpoint bus_allocator::get_slot_source(const std::string &core, const std::string &slot_name) {
        return sources_map.at(core).at(slot_name);
    }

     std::unordered_map<std::string, std::string> bus_allocator::dump_bus() {
        std::unordered_map<std::string, std::string> ret;
        for(auto &[core, sources]: sources_map) {
            for(auto &[slot_name, ep] : sources) {
                std::string ep_name = core + "." + slot_name;
                std::string addresses = "";
                for(auto addr: ep.bus_addresses) {
                    addresses += std::to_string(addr) + " ";
                }
                ret[ep_name] = addresses;
            }
        }
        return ret;
    }

     std::vector<output_metadata> bus_allocator::get_outputs() {

        std::vector<output_metadata> ret;
        for(auto &[core, sources] : sources_map) {
            for(auto &[port, endpoint]: sources) {
                output_metadata m;
                m.core_name = core;
                m.port_name = port;
                m.vector_size = endpoint.vector_size;
                m.channels = endpoint.channels;
                m.metadata = endpoint.metadata;
                m.addresses = endpoint.bus_addresses;
                ret.push_back(m);
            }
        }
        return ret;
     }


     std::vector<core_endpoint> bus_allocator::get_memories(const std::string &core_name) {
        std::vector<core_endpoint> retval;
        for(auto &[core, sources]:sources_map ) {
            for(auto &endpoint: sources | std::views::values) {
                if(endpoint.endpoint_class == core_iom_memory && core == core_name) {
                    retval.push_back(endpoint);
                }
            }

        }
        return retval;
    }

    std::vector<interconnect_descriptor> bus_allocator::get_interconnects() {
        return interconnect_mapping;
    }
        
    bool bus_allocator::is_register(const std::string &r) {
        if(r.empty() || r[0] != 'r') return false;
        if(r.length() > 3) return false;
        for(int i = 1; i < r.length(); i++) {
            if(!std::isdigit(r[i])) return false;
        }
        return true;
    }
}
