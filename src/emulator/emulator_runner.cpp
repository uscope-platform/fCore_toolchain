

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

#include "emulator/emulator_runner.hpp"

namespace fcore {


    emulator_runner::emulator_runner(program_bundle &prog) {
        backend.set_core_name(core_name);
        program = prog;
        backend.set_program(sanitize_program(prog.program.binary));
        backend.set_efi_selector(prog.efi_selector);
        backend.set_comparator_type(prog.comparator_type);
        core_name = prog.name;
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

    void emulator_runner::emulation_phase(uint32_t channel) {
        backend.run_round(emulators_memory->at(core_name)[channel], common_io_memory->at(core_name));
    }

    void emulator_runner::inputs_phase(const core_step_metadata &info, uint32_t channel) {
        if(info.running){
            for(auto &in:program.input){
                uint32_t core_reg = 0;
                auto io_addr = in.address[0];

                bool is_common;
                if(auto core_addr = io_map_entry::get_io_map_entry_by_io_addr(program.io, io_addr)){
                    core_reg = core_addr->core_addr;
                    is_common = core_addr->common_io;
                } else {
                    throw std::runtime_error("unable to find input address in the core io map during input phase");
                }
                if(in.source_type == emulator::external_input) continue;

                if(core_reg != 0){
                    uint32_t input_val;
                    if(in.metadata.type==emulator::type_float){

                        if(in.source_type == emulator::constant_input){
                            float value = std::get<std::vector<float>>(in.data[0])[0];
                            if(in.data.size() != 1){
                                value = std::get<std::vector<float>>(in.data[channel])[0];
                            }
                            input_val = emulator_backend::float_to_uint32(value);

                        } else  {
                            std::vector<float> in_vect = std::get<std::vector<float>>(in.data[channel]);
                            input_val = emulator_backend::float_to_uint32(in_vect[info.step_n]);
                        }
                    } else {

                        std::vector<uint32_t> in_vect = std::get<std::vector<uint32_t>>(in.data[channel]);
                        if(in.source_type == emulator::constant_input){
                            input_val = in_vect[0];
                        } else  {
                            input_val = in_vect[info.step_n];
                        }
                    }
                    if(is_common){
                        common_io_memory->at(core_name)->at(core_reg) = input_val;
                    } else {
                        uint32_t sel_ch = channel;
                        if(in.source_type != emulator::constant_input || in.channel.size()!=1){
                            sel_ch = in.channel[channel];
                        }
                        emulators_memory->at(core_name)[sel_ch]->at(core_reg) = input_val;
                    }
                }
            }
        }
    }

} // fcore