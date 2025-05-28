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
    void emulator_dispatcher::enable_debug_mode() {
        if(version == 1) {
            v1.enable_debug_mode();
        } else {
            v2.enable_debug_mode();
        }
    }

    void emulator_dispatcher::set_specs(const nlohmann::json &spec_file) {
        if(!spec_file.contains("version")) {
            throw std::runtime_error("Invalid spec file, missing version field");
        }
        if(spec_file["version"] != 1 && spec_file["version"] != 2) {
            throw std::runtime_error("Invalid spec file, version field must be 1 or 2");
        }
        version = spec_file["version"];
        if(version == 1) {
            v1.set_specs(spec_file);
        } else {
            v2.set_specs(spec_file);
        }
    }

    std::set<uint32_t> emulator_dispatcher::get_breakpoints(const std::string &id) {
        if(version == 1) {
            return v1.get_breakpoints(id);
        } else {
            return v2.get_breakpoints(id);
        }
    }

    void emulator_dispatcher::process() {
        if(version == 1) {
            v1.process();
        } else {
            v2.process();
        }
    }

    std::optional<debug_checkpoint> emulator_dispatcher::emulate() {
        if(version == 1) {
            return v1.emulate();
        } else {
            return v2.emulate();
        }
    }

    debug_checkpoint emulator_dispatcher::step_over() {
        if(version == 1) {
            return v1.step_over();
        } else {
            return v2.step_over();
        }
    }

    std::optional<debug_checkpoint> emulator_dispatcher::continue_emulation() {
        if(version == 1) {
            return v1.continue_emulation();
        } else {
            return v2.continue_emulation();
        }
    }

    void emulator_dispatcher::add_breakpoint(const std::string &s, uint32_t addr) {
        if(version == 1) {
            v1.add_breakpoint(s, addr);
        } else {
            v2.add_breakpoint(s, addr);
        }
    }

    void emulator_dispatcher::remove_breakpoint(const std::string &s, uint32_t addr) {
        if(version == 1) {
            v1.remove_breakpoint(s, addr);
        } else {
            v2.remove_breakpoint(s, addr);
        }
    }

    void emulator_dispatcher::set_multichannel_debug(bool mc) {
        if(version  == 1) {
            v1.set_multichannel_debug(mc);
        } else {
            v2.set_multichannel_debug(mc);
        }
    }

    nlohmann::json emulator_dispatcher::get_results() {
        if(version == 1) {
            return v1.get_results();
        } else {
            return v2.get_results();
        }
    }

    void emulator_dispatcher::set_profiler(const std::shared_ptr<instrumentation_core> &prof) {
        if(version == 1) {
            v1.set_profiler(prof);
        } else {
            v2.set_profiler(prof);
        }
    }

    std::unordered_map<std::string, disassembled_program> emulator_dispatcher::disassemble() {
        if(version == 1) {
            return v1.disassemble();
        } else {
            return v2.disassemble();
        }
    }
}
