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

#ifndef EMULATOR_DISPATCHER_HPP
#define EMULATOR_DISPATCHER_HPP

#include <memory>
#include <set>
#include <nlohmann/json.hpp>

#include "errors/result.hpp"
#include <emulator/v2/emulator_manager.hpp>

namespace fcore {

    /// Front of the emulator that selects the implementation from the version field of the specification.
    /// Only the version 2 is implemented, calling anything before set_specs, or after a version 1 specification, fails.
    class emulator_dispatcher {
    public:
        [[nodiscard]] result<void> enable_debug_mode();

        [[nodiscard]] result<void> set_specs(const nlohmann::json &spec_file);
        [[nodiscard]] result<std::set<uint32_t>> get_breakpoints(const std::string &id);
        [[nodiscard]] result<void> process();

        [[nodiscard]] result<std::optional<debug_checkpoint>> emulate();
        [[nodiscard]] result<debug_checkpoint> step_over();
        [[nodiscard]] result<std::optional<debug_checkpoint>> continue_emulation();

        [[nodiscard]] result<void> add_breakpoint(const std::string &s, uint32_t addr);
        [[nodiscard]] result<void> remove_breakpoint(const std::string &s, uint32_t addr);
        [[nodiscard]] result<void> set_multichannel_debug(bool mc);
        [[nodiscard]] result<nlohmann::json> get_results();

        [[nodiscard]] result<void> set_profiler(const std::shared_ptr<instrumentation_core> &prof);
        [[nodiscard]] result<std::map<std::string, disassembled_program>> disassemble();

        [[nodiscard]] result<std::vector<deployed_program>> get_programs();
        [[nodiscard]] result<std::map<std::string, std::vector<memory_init_value>>> get_memory_initializations();

        [[nodiscard]] result<std::vector<deployed_core_inputs>> get_inputs(const std::string &core);

        [[nodiscard]] result<std::vector<deployer_interconnect_slot>> get_interconnect_slots();
        [[nodiscard]] result<deployment_options> get_deployment_options(const std::string &core);

    private:
        /// Succeeds if a version 2 specification was loaded
        [[nodiscard]] result<void> require_v2() const;

        uint32_t version = 0;
        emulator_v2::emulator_manager v2;
    };


}



#endif //EMULATOR_DISPATCHER_HPP
