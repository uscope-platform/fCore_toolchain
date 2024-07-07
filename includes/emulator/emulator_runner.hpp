

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

#ifndef FCORE_TOOLCHAIN_EMULATOR_RUNNER_HPP
#define FCORE_TOOLCHAIN_EMULATOR_RUNNER_HPP

#include "emulator/emulation_sequencer.hpp"
#include "emulator/backend/emulation_outputs_manager.hpp"
#include "emulator/backend/multirate_io_repeater.hpp"

namespace fcore {

    class emulator_runner {
    public:
    private:
        void inputs_phase(const core_step_metadata& info);
        void execution_phase(const core_step_metadata& info);
        void interconnects_phase(const core_step_metadata& info, std::unordered_map<std::string, bool> enabled_cores);


        multirate_io_repeater output_repeater;
        emulation_sequencer sequencer;
        emulation_outputs_manager outputs_manager;
    };

} // fcore

#endif //FCORE_TOOLCHAIN_EMULATOR_RUNNER_HPP
