//   Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#ifndef FCORE_TOOLCHAIN_OUTPUT_SINK_V2_HPP
#define FCORE_TOOLCHAIN_OUTPUT_SINK_V2_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "emulator/v2/bus_allocator.hpp"
#include "emulator/v2/emulation_sequencer.hpp"
#include "emulator/v2/emulator_runner.hpp"
#include "errors/result.hpp"

namespace fcore::emulator_v2 {

    /// Where the outputs of the cores go while the emulation runs. The manager drives it at the same points for every
    /// implementation: the batch one accumulates the whole run to hand it back at the end, the live one only samples
    /// the outputs that are selected.
    class output_sink {
    public:
        virtual ~output_sink() = default;

        virtual void set_runners(const std::shared_ptr<std::map<std::string, emulator_runner>> &r) = 0;
        virtual void process_specs(const std::shared_ptr<bus_allocator> &bus_engine) = 0;
        virtual void set_initial_values(const std::map<std::string, std::map<std::string, std::vector<uint32_t>>> &ivs) = 0;
        virtual void set_simulation_frequency(uint32_t freq) = 0;

        /// Called after a core has run its step, before the interconnect moves its data. Every core gets one call
        /// in every round, whether it ran or not, \p metadata describes all of them. An empty \p core means all.
        [[nodiscard]] virtual result<void> process_outputs(
            const std::vector<core_step_metadata> &metadata,
            const std::string &core
        ) = 0;

        virtual void clear() = 0;
    };
}

#endif //FCORE_TOOLCHAIN_OUTPUT_SINK_V2_HPP
