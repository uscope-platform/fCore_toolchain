

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

#include "emulator/v2/emulator_runner.hpp"

namespace fcore::emulator_v2 {


    emulator_runner::emulator_runner(program_bundle &prog, const std::shared_ptr<bus_allocator> &engine) : distrib(0, 65536) {
        gen.seed(542);
        core_name = prog.name;
        multichannel_debug = false;
        bus_engine = engine;
        backend.set_core_name(core_name);
        program = prog;
        backend.set_program(sanitize_program(prog.program.binary));
        backend.set_efi_selector(prog.efi_selector);
        backend.set_comparator_type(prog.comparator_type);

        common_io_memory = std::make_shared<std::vector<uint32_t>>(32, 0); // TODO: make the number of common io cells a parameter

        for(int i = 0; i<prog.active_channels; i++){
            emulators_memory[i] = std::make_shared<std::vector<uint32_t>>(2 << (fcore_register_address_width - 1), 0);
        }


        for(auto &init_val: bus_engine->get_memories(core_name)){
            for(int i = 0; i< prog.active_channels; i++){
                if(init_val.initial_value.size()== prog.active_channels) {
                    auto res = dma_write(init_val.bus_addresses[0], i, init_val.initial_value[i]);
                    if(!res) throw std::runtime_error("Unable to initialize memory (" +core_name + "." + init_val.source_name + "[" + std::to_string(i) + "])");
                } else {
                    auto res = dma_write(init_val.bus_addresses[0], i, init_val.initial_value[0]);
                    if(!res) throw std::runtime_error("Unable to initialize memory (" +core_name + "." + init_val.source_name);
                }

            }
        }


        for(auto &ic : bus_engine->get_interconnects()) {
            if(prog.name==ic.destination.core_name) {
                for(auto &i:program.input) {
                    if(i.name == ic.destination.port_name) {
                        input_override[prog.name].insert(i.name);
                    }
                }
            }
        }

    }

    std::vector<uint32_t> emulator_runner::sanitize_program(const std::vector<uint32_t> &raw_prog) {
        std::vector<uint32_t> program;
        int section = 0;

        for(auto &instr:raw_prog){
            if(section == code_section_index){
                program.push_back(instr);
            }
            if(instr == fcore_opcodes["stop"]){
                section++;
            }
        }
        return program;
    }

    void emulator_runner::emulation_phase(uint32_t channel, int init_point) {
        auto mem = emulators_memory[channel];
        backend.set_debugging(multichannel_debug || channel == 0);
        backend.setup_memory(mem, common_io_memory);
        backend.run_round(init_point);
    }

    debug_checkpoint emulator_runner::step_over(uint32_t channel) {
        auto mem = emulators_memory[channel];
        backend.set_debugging(multichannel_debug || channel == 0);
        backend.setup_memory(mem, common_io_memory);
        return backend.step_over();
    }


    void emulator_runner::inputs_phase(const core_step_metadata &info, uint32_t channel) {


        if(info.running){
            for(auto &in:program.input){
                if(input_override[info.id].contains(in.name)) continue;
                std::vector<uint32_t> input_val;
                if(in.source_type == external_input) continue;
                if(in.source_type == random_input) {
                    for(int i = 0; i< in.vector_size; i++) {
                        auto in_i = distrib(gen);
                        float in_norm = quant_norm[in_i];
                        int32_t norm_in = in_norm*(2<<15);
                        input_val = {static_cast<uint32_t>(norm_in)};
                    }
                } else if(in.metadata.type==type_float){
                    if(in.source_type == constant_input){
                        if(in.is_vector) {
                            for(int i = 0; i< in.vector_size; i++) {
                                float value = std::get<std::vector<float>>(in.data[i])[channel];
                                input_val.push_back(emulator_backend::float_to_uint32(value));
                            }
                        } else {
                            float value = std::get<std::vector<float>>(in.data[0])[0];
                            if(in.data.size() != 1){
                                value = std::get<std::vector<float>>(in.data[channel])[0];
                            }
                            input_val = {emulator_backend::float_to_uint32(value)};
                        }

                    } else  {
                        if(in.data.size() <= channel) {
                            throw std::runtime_error(" The series input for channel " + std::to_string(channel) + " was not found");
                        }
                        if(in.is_vector) {
                            for(auto &i:in.data) {
                                input_val.push_back(emulator_backend::float_to_uint32(std::get<std::vector<float>>(i)[info.step_n]));
                            }
                        } else {
                            std::vector<float> in_vect = std::get<std::vector<float>>(in.data[channel]);
                            input_val = {emulator_backend::float_to_uint32(in_vect[info.step_n])};
                        }
                    }
                } else {
                    if(in.is_vector) {
                        for(int i = 0; i< in.vector_size; i++) {
                            std::vector<uint32_t> in_vect = std::get<std::vector<uint32_t>>(in.data[i]);
                            if(in.source_type == constant_input){
                                input_val.push_back(in_vect[0]);
                            } else  {
                                input_val.push_back(in_vect[info.step_n]);
                            }
                        }
                    } else {
                        std::vector<uint32_t> in_vect = std::get<std::vector<uint32_t>>(in.data[channel]);
                        if(in.source_type == constant_input){
                            input_val = {in_vect[0]};
                        } else  {
                            input_val = {in_vect[info.step_n]};
                        }
                    }

                }
                current_inputs[in.name] = input_val[0];
                for(int i = 0; i< in.vector_size; i++) {
                    auto addr = bus_engine->get_input_address(info.id,in.name, i);
                    if(in.metadata.type==type_float) {
                        spdlog::trace("Applying input {}f to register ({},{}) of core {}", emulator_backend::uint32_to_float(input_val[i]), addr, channel, core_name);
                    } else {
                        spdlog::trace("Applying input {} to register ({},{}) of core {}", input_val[i], addr, channel, core_name);
                    }

                    auto res = dma_write(addr, channel, input_val[i]);
                    if(!res) throw std::runtime_error("Unable to apply input (" +in.name + "[" + std::to_string(i) + "])");
                }
            }
        }
    }

    std::optional<uint32_t>  emulator_runner::dma_read(uint32_t address, uint32_t channel) {

        uint32_t core_reg = 0;
        bool is_common;

        if(auto core_addr = io_map_entry::get_io_map_entry_by_io_addr(program.io, address)){
            core_reg = core_addr->core_addr;
            is_common = core_addr->common_io;
        } else {
            return {};
        }

        if(emulators_memory.size()< channel+1){
            throw std::runtime_error("Attempted read from unavailable channel: " + std::to_string(channel) + " of core: " + core_name);
        }
        if(is_common){
            return common_io_memory->at(core_reg);
        } else {
            return  emulators_memory[channel]->at(core_reg);
        }

    }

    bool emulator_runner::dma_write(uint32_t address, uint32_t channel, uint32_t data) {

        uint32_t core_reg = 0;
        bool is_common;

        if(auto core_addr = io_map_entry::get_io_map_entry_by_io_addr(program.io, address)){
            core_reg = core_addr->core_addr;
            is_common = core_addr->common_io;
        } else {
            return false;

        }
        if(emulators_memory.size()< channel+1){
            throw std::runtime_error("Attempted write to unavailable channel: " + std::to_string(channel) + " of core: " + core_name);
        }
        if(core_reg != 0) {
            if (is_common) {
                common_io_memory->at(core_reg) = data;
            } else {
                emulators_memory[channel]->at(core_reg) = data;
            }
        }
        return true;
    }

    debug_checkpoint emulator_runner::get_end_state() {
        auto ret = backend.produce_checkpoint(true);
        ret.breakpoint = 0;
        return ret;
    }

} // fcore