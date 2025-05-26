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

    for(auto &core:specs.cores) {
        for(auto &in:core.inputs) {
            for(int i = 0; i<core.channels; i++) {
                bus_slot s;
                s.address = allocate_slot(in.metadata.io_address);
                s.source.core_name = core.id;
                s.source.type = in.metadata.type;
                s.source.channel = i;
                if(core.channels > 1) {
                    s.source.source_name = in.name + "_" + std::to_string(i);
                } else {
                    s.source.source_name = in.name;
                }
                s.source.endpoint_class = core_iom_input;
                s.source.common_io = in.metadata.is_common_io;
                bus_map.push_back(s);
            }
        }
        for(auto &out:core.outputs) {
            for(int i = 0; i<core.channels; i++) {
                bus_slot s;
                s.address = allocate_slot(out.metadata.io_address);
                s.source.core_name = core.id;
                s.source.channel = i;
                if(core.channels > 1) {
                    s.source.source_name = out.name + "_" + std::to_string(i);
                } else {
                    s.source.source_name = out.name;
                }
                s.source.type = out.metadata.type;
                s.source.endpoint_class = core_iom_output;
                s.source.common_io = out.metadata.is_common_io;
                bus_map.push_back(s);
            }
        }
        for(auto &mem:core.memories) {
            for(int i = 0; i<core.channels; i++) {
                bus_slot s;
                s.address = allocate_slot(mem.metadata.io_address);
                s.source.core_name = core.id;
                s.source.channel = i;
                if(core.channels > 1) {
                    s.source.source_name = mem.name + "_" + std::to_string(i);
                } else {
                    s.source.source_name = mem.name;
                }

                if(std::holds_alternative<std::vector<float>>(mem.value)) {
                    s.source.type = type_float;
                    s.source.initial_value = emulator_backend::float_to_uint32_v(std::get<std::vector<float>>(mem.value));
                } else {
                    s.source.type = type_uint;
                    s.source.initial_value = std::get<std::vector<uint32_t>>(mem.value);
                }
                s.source.endpoint_class = core_iom_memory;
                s.source.common_io = false;
                bus_map.push_back(s);
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

    if(!allocated_addresses.contains(d_a)) {
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
    return ret_val;
}

uint32_t bus_allocator::get_address(const std::string &core, const std::string &input, uint32_t channel) {
    for(auto &slot:bus_map) {
        if(slot.source.core_name == core && slot.source.source_name == input && slot.source.channel == channel) {
            return slot.address;
        }
    }
    throw std::runtime_error("No slot found for core " + core + " input " + input + " channel " + std::to_string(channel));
}

void bus_allocator::clear() {
    bus_map.clear();
    current_index = 1;
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
}
