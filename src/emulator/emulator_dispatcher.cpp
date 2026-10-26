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

#include "emulator/emulator_dispatcher.hpp"
namespace fcore {
    result<void> emulator_dispatcher::require_v2() const {
        if(version == 2) return {};
        if(version == 1) return fail(error_code::not_supported, "Emulator schema version 1 is no longer supported");
        return fail(error_code::invalid_argument, "No emulator specification was loaded");
    }

    result<void> emulator_dispatcher::enable_debug_mode() {
        if(auto supported = require_v2(); !supported) return supported;
        v2.enable_debug_mode();
        return {};
    }

    result<void> emulator_dispatcher::set_specs(const nlohmann::json &spec_file) {
        if(!spec_file.contains("version")) {
            return fail(error_code::spec_error, "Invalid spec file, missing version field");
        }
        if(spec_file["version"] != 1 && spec_file["version"] != 2) {
            return fail(error_code::spec_error, "Invalid spec file, version field must be 1 or 2");
        }
        version = spec_file["version"];
        if(auto supported = require_v2(); !supported) return supported;

        v2 = emulator_v2::emulator_manager();
        return v2.set_specs(spec_file);
    }

    result<std::set<uint32_t>> emulator_dispatcher::get_breakpoints(const std::string &id) {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.get_breakpoints(id);
    }

    result<void> emulator_dispatcher::process() {
        if(auto supported = require_v2(); !supported) return supported;
        return v2.process();
    }

    result<std::optional<debug_checkpoint>> emulator_dispatcher::emulate() {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.emulate();
    }

    result<debug_checkpoint> emulator_dispatcher::step_over() {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.step_over();
    }

    result<std::optional<debug_checkpoint>> emulator_dispatcher::continue_emulation() {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.continue_emulation();
    }

    result<void> emulator_dispatcher::add_breakpoint(const std::string &s, uint32_t addr) {
        if(auto supported = require_v2(); !supported) return supported;
        return v2.add_breakpoint(s, addr);
    }

    result<void> emulator_dispatcher::remove_breakpoint(const std::string &s, uint32_t addr) {
        if(auto supported = require_v2(); !supported) return supported;
        return v2.remove_breakpoint(s, addr);
    }

    result<void> emulator_dispatcher::set_multichannel_debug(bool mc) {
        if(auto supported = require_v2(); !supported) return supported;
        v2.set_multichannel_debug(mc);
        return {};
    }

    result<nlohmann::json> emulator_dispatcher::get_results() {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.get_results();
    }

    result<void> emulator_dispatcher::set_profiler(const std::shared_ptr<instrumentation_core> &prof) {
        if(auto supported = require_v2(); !supported) return supported;
        v2.set_profiler(prof);
        return {};
    }

    result<std::map<std::string, disassembled_program>> emulator_dispatcher::disassemble() {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.disassemble();
    }

    result<std::vector<deployed_program>> emulator_dispatcher::get_programs() {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.deploy_programs();
    }

    result<std::map<std::string, std::vector<memory_init_value>>> emulator_dispatcher::get_memory_initializations() {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.get_memory_init_values();
    }

    result<std::vector<deployed_core_inputs>> emulator_dispatcher::get_inputs(const std::string &core) {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.get_inputs(core);
    }

    result<std::vector<deployer_interconnect_slot>> emulator_dispatcher::get_interconnect_slots() {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.get_interconnects();
    }

    result<deployment_options> emulator_dispatcher::get_deployment_options(const std::string &core) {
        if(auto supported = require_v2(); !supported) return fail(std::move(supported).error());
        return v2.get_deployment_options(core);
    }

}
