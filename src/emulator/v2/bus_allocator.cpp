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

#include "emulator/v1/backend/emulator_backend.hpp"
#include "emulator/v2/backend/emulator_backend.hpp"

namespace fcore::emulator_v2 {

void bus_allocator::set_emulation_specs(const emulator_specs &specs) {

    inputs_address_mapping.clear();
    bus_map.clear();
    sources_map.clear();
    destinations_map.clear();
    allocated_addresses.clear();
    desired_addresses.clear();
    current_index = 1;

    for(auto &core:specs.cores) {
        for(auto &in:core.inputs) {
            for(int i = 0; i<core.channels; i++) {
                core_endpoint ep;
                ep.core_name = core.id;
                ep.type = in.metadata.type;
                ep.channel = i;
                if(core.channels > 1) {
                    ep.source_name = in.name + "_" + std::to_string(i);
                } else {
                    ep.source_name = in.name;
                }
                ep.endpoint_class = core_iom_input;
                ep.common_io = in.metadata.is_common_io;
                destinations_map[core.id][in.name] = ep;
            }
        }
        for(auto &out:core.outputs) {
            for(int i = 0; i<core.channels; i++) {
                core_endpoint ep;
                ep.core_name = core.id;
                ep.channel = i;
                if(core.channels > 1) {
                    ep.source_name = out.name + "_" + std::to_string(i);
                } else {
                    ep.source_name = out.name;
                }
                ep.type = out.metadata.type;
                ep.endpoint_class = core_iom_output;
                ep.common_io = out.metadata.is_common_io;
                sources_map[core.id][out.name] = ep;

                bus_slot s;
                s.address = allocate_slot(out.metadata.io_address);
                s.source = ep;
                bus_map.push_back(s);
            }
        }
        for(auto &mem:core.memories) {
            for(int i = 0; i<core.channels; i++) {
                core_endpoint ep;
                ep.core_name = core.id;

                ep.channel = i;
                if(core.channels > 1) {
                    ep.source_name = mem.name + "_" + std::to_string(i);
                } else {
                    ep.source_name = mem.name;
                }

                if(std::holds_alternative<std::vector<float>>(mem.value)) {
                    ep.type = type_float;
                    ep.initial_value = emulator_backend::float_to_uint32_v(std::get<std::vector<float>>(mem.value));
                } else {
                    ep.type = type_uint;
                    ep.initial_value = std::get<std::vector<uint32_t>>(mem.value);
                }
                ep.endpoint_class = core_iom_memory;
                ep.common_io = false;
                sources_map[core.id][mem.name] = ep;

                bus_slot s;
                s.address = allocate_slot(mem.metadata.io_address);
                s.source = ep;
                bus_map.push_back(s);
            }
        }
    }

    for(auto &ic:specs.interconnects) {
        auto src_core = ic.source_endpoint.substr(0, ic.source_endpoint.find('.'));\
        auto src_port = ic.source_endpoint.substr(ic.source_endpoint.find('.')+1, ic.source_endpoint.size());
        auto dst_core = ic.destination_endpoint.substr(0, ic.destination_endpoint.find('.'));\
        auto dst_port = ic.destination_endpoint.substr(ic.destination_endpoint.find('.')+1, ic.destination_endpoint.size());


        auto destination = destinations_map[dst_core][dst_port];

        for(auto &slot:bus_map) {
            if(slot.source.core_name == src_core && slot.source.source_name == src_port) {
                inputs_address_mapping[dst_core][dst_port] = slot.address;
                slot.destination.push_back(destination);
            }
        }

    }
}

uint32_t bus_allocator::allocate_slot(uint16_t d_a) {
    if(allocated_addresses.contains(d_a) && !desired_addresses.contains(d_a)) {
        for(auto &slot:bus_map) {
            if(slot.address == d_a) {
                allocated_addresses.insert(current_index);
                slot.address = current_index;
                allocated_addresses.erase(d_a);
            }
        }
    }

    if(!allocated_addresses.contains(d_a) && d_a != 0) {
        allocated_addresses.insert(d_a);
        desired_addresses.insert(d_a);
        return d_a;
    } else if(d_a != 0) {
        throw std::runtime_error("Conflict between two signals for desired address " + std::to_string(d_a));
    }
    while(allocated_addresses.contains(current_index)) current_index++;
    auto address = current_index;
    allocated_addresses.insert(address);
    current_index++;
    return address;
}

std::unordered_map<std::string, core_iom> bus_allocator::get_dma_io(std::string core_name) {

    std::unordered_map<std::string, core_iom> ret_val;
    for(auto &item:bus_map) {
        if(item.source.core_name == core_name) {
            if(ret_val.contains(item.source.source_name)) {

            } else {
                core_iom iom;
                iom.address = {item.address};
                iom.common_io = item.source.common_io;
                iom.type = item.source.endpoint_class;
                ret_val[item.source.source_name] = iom;
            }

        }
    }

    for(auto &item:destinations_map[core_name] | std::views::values) {
        core_iom iom;
        iom.address = {get_inputs_address(core_name, item.source_name, item.channel) };
        iom.common_io = item.common_io;
        iom.type = item.endpoint_class;
        ret_val[item.source_name] = iom;
    }
    return ret_val;
}

uint32_t bus_allocator::get_bus_address(const std::string &core, const std::string &input, uint32_t channel) {
    return inputs_address_mapping[core][input];
}

uint32_t bus_allocator::get_inputs_address(const std::string &core, const std::string &input, uint32_t channel) {
    uint32_t tentative_address = 1;
    if(inputs_address_mapping.contains(core)) {
        if(inputs_address_mapping[core].contains(input)) {
            return inputs_address_mapping[core][input];
        }
    }
    std::set<uint32_t> used_input_addresses;
    for(auto &val : inputs_address_mapping[core] | std::views::values) {
        used_input_addresses.insert(val);
    }
    while(allocated_addresses.contains(tentative_address) || used_input_addresses.contains(tentative_address)) tentative_address++;
    inputs_address_mapping[core][ input] = tentative_address;
    used_input_addresses.insert(tentative_address);
    return tentative_address;
}


std::vector<bus_slot> bus_allocator::get_memories() {
    std::vector<bus_slot> retval;
    for(auto &slot:bus_map) {
        if(slot.source.endpoint_class == core_iom_memory) {
            retval.push_back(slot);
        }
    }
    return retval;
}

std::vector<bus_slot> bus_allocator::get_interconnects(const std::string &core_name) {
    std::vector<bus_slot> retval;
    for(auto &slot:bus_map) {
        if(slot.source.core_name == core_name) {
            retval.push_back(slot);
        }
    }
    return retval;
}
}
