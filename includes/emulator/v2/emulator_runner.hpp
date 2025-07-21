

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

#ifndef FCORE_TOOLCHAIN_EMULATOR_RUNNER_V2_HPP
#define FCORE_TOOLCHAIN_EMULATOR_RUNNER_V2_HPP

#include "data_structures/emulation/v2/program_bundle.hpp"
#include "emulator/v2/backend/emulator_backend.hpp"
#include "emulator/v2/emulation_sequencer.hpp"
#include "emulator/v2/emulator_builder.hpp"

#include <random>

namespace fcore::emulator_v2 {


    class emulator_runner {
    public:

        explicit emulator_runner(program_bundle &prog, const std::shared_ptr<bus_allocator> &bus_engine);

        void add_breakpoint(uint32_t addr) {backend.add_breakpoint(addr);};
        void remove_breakpoint(uint32_t addr) {backend.remove_breakpoint(addr);};
        std::set<uint32_t> get_breakpoints() {return backend.get_breakpoints();};

        void inputs_phase(const core_step_metadata& info, uint32_t  channel);
        void emulation_phase(uint32_t  channel, int init_point);

        void reset_instruction_pointer() {backend.reset_instruction_pointer();};
        debug_checkpoint step_over(uint32_t channel);
        debug_checkpoint get_end_state();

        uint32_t dma_read(uint32_t address, uint32_t channel);
        void dma_write(uint32_t address, uint32_t channel, uint32_t data);

        void set_multichannel_debug(bool mc_debug){ multichannel_debug = mc_debug; };

        std::unordered_map<std::string, uint32_t> get_inputs() {return current_inputs;};

    private:

        std::mt19937 gen;
        std::uniform_int_distribution<> distrib;

        static std::vector<uint32_t> sanitize_program(const std::vector<uint32_t>&  raw_prog);
        static constexpr uint16_t code_section_index = 3;

        program_bundle program;
        std::string core_name;

        std::shared_ptr<std::vector<uint32_t>> common_io_memory;
        std::unordered_map<std::string, uint32_t> current_inputs;
        core_memory_pool_t emulators_memory;
        bool multichannel_debug;

        std::shared_ptr<bus_allocator> bus_engine;
        emulator_backend backend;

    };

} // fcore

#endif //FCORE_TOOLCHAIN_EMULATOR_RUNNER_V2_HPP
