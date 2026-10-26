

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
        // set_active_channels overrides it, it used to be left uninitialized when that was not called
        active_channels = prog.active_channels;
        bus_engine = engine;
        backend.set_core_name(core_name);
        program = prog;
        backend.set_program(sanitize_program(prog.program.binary));
        backend.set_efi_selector(prog.efi_selector);
        backend.set_comparator_type(prog.comparator_type);

        common_io_memory = std::vector<uint32_t>(32, 0); // TODO: make the number of common io cells a parameter

        for(int i = 0; i<prog.active_channels; i++){
            emulators_memory[i] = std::vector<uint32_t>(2 << (fcore_register_address_width - 1), 0);
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

    result<emulator_runner> emulator_runner::create(program_bundle &prog, const std::shared_ptr<bus_allocator> &engine) {
        emulator_runner runner(prog, engine);
        if(auto initialized = runner.initialize_memories(); !initialized) return fail(std::move(initialized).error());
        return runner;
    }

    result<void> emulator_runner::initialize_memories() {
        for(auto &init_val: bus_engine->get_memories(core_name)){
            for(int i = 0; i< program.active_channels; i++){
                auto initial_value = init_val.initial_value.size()== program.active_channels ? init_val.initial_value[i] : init_val.initial_value[0];
                if(auto res = dma_write(init_val.bus_addresses[0], i, initial_value); !res){
                    return fail(std::move(res).error().with_context(
                        "initializing the memory " + core_name + "." + init_val.source_name + "[" + std::to_string(i) + "]"));
                }
            }
        }
        return {};
    }

    void emulator_runner::add_waveform(const std::string &in,
        std::variant<square_wave_parameters, sine_wave_parameters, triangle_wave_parameters> p) {
        waveforms_generator.add_waveform(in, p, program.active_channels);
    }

    std::vector<uint32_t> emulator_runner::sanitize_program(const std::vector<uint32_t> &raw_prog) {
        std::vector<uint32_t> program;
        int section = 0;

        for(auto &instr:raw_prog){
            if(section == code_section_index){
                program.push_back(instr);
            }
            if(instr == fcore_opcodes[opcode_stop]){
                section++;
            }
        }
        return program;
    }

    result<round_outcome_t> emulator_runner::emulation_phase(uint32_t channel, int init_point) {
        backend.set_debugging(multichannel_debug || channel == 0);
        backend.setup_memory(emulators_memory[channel], common_io_memory, active_channels);
        return backend.run_round(init_point);
    }

    result<debug_checkpoint> emulator_runner::step_over(uint32_t channel) {
        backend.set_debugging(multichannel_debug || channel == 0);
        backend.setup_memory(emulators_memory[channel], common_io_memory, active_channels);
        return backend.step_over();
    }


    result<void> emulator_runner::inputs_phase(const core_step_metadata &info, uint32_t channel) {


        if(info.running){
            for(auto &in:program.input){
                if(input_override[info.id].contains(in.name)) continue;
                std::vector<uint32_t> input_val;
                if(in.source_type == external_input) continue;
                if(in.source_type == waveform_input) {
                    auto val = waveforms_generator.get_value(in.name, channel);
                    input_val = {emulator_backend::float_to_uint32(val)};
                } else if(in.source_type == random_input) {
                    for(int i = 0; i< in.vector_size; i++) {
                        auto in_i = distrib(gen);
                        input_val = {emulator_backend::float_to_uint32(quant_norm[in_i])};
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
                            return fail(error_code::spec_error, "The series input for channel " + std::to_string(channel) + " was not found");
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

                    if(auto res = dma_write(addr, channel, input_val[i]); !res){
                        return fail(std::move(res).error().with_context("applying the input " + in.name + "[" + std::to_string(i) + "]"));
                    }
                }
            }
        }
        return {};
    }

    result<uint32_t> emulator_runner::dma_read(uint32_t address, uint32_t channel) {

        const auto core_addr = io_map_entry::get_io_map_entry_by_io_addr(program.io, address);
        if(!core_addr){
            return fail(error_code::emulation_error, "The io address " + std::to_string(address) + " is not mapped on core: " + core_name);
        }

        if(emulators_memory.size()< channel+1){
            return fail(error_code::emulation_error, "Attempted read from unavailable channel: " + std::to_string(channel) + " of core: " + core_name);
        }
        if(core_addr->common_io){
            return common_io_memory[core_addr->core_addr];
        } else {
            return emulators_memory[channel][core_addr->core_addr];
        }

    }

    result<void> emulator_runner::dma_write(uint32_t address, uint32_t channel, uint32_t data) {

        const auto core_addr = io_map_entry::get_io_map_entry_by_io_addr(program.io, address);
        if(!core_addr){
            return fail(error_code::emulation_error, "The io address " + std::to_string(address) + " is not mapped on core: " + core_name);
        }
        if(emulators_memory.size()< channel+1){
            return fail(error_code::emulation_error, "Attempted write to unavailable channel: " + std::to_string(channel) + " of core: " + core_name);
        }
        if(core_addr->core_addr != 0) {
            if (core_addr->common_io) {
                common_io_memory[core_addr->core_addr] = data;
            } else {
                emulators_memory[channel][core_addr->core_addr] = data;
            }
        }
        return {};
    }

    debug_checkpoint emulator_runner::get_end_state() {
        auto ret = backend.produce_checkpoint(true);
        ret.breakpoint = 0;
        return ret;
    }

} // fcore