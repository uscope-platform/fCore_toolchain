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
            throw std::runtime_error("Emulator schema version 1 is no longer supported");
        } else if(version == 2) {
            v2.enable_debug_mode();
        } else {
            throw std::runtime_error("Invalid version");
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
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                v2 = emulator_v2::emulator_manager();
                v2.set_specs(spec_file);
                break;
            default:
                throw std::runtime_error("Invalid version");
                break;
        }
    }

    std::set<uint32_t> emulator_dispatcher::get_breakpoints(const std::string &id) {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
            return v2.get_breakpoints(id);
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    void emulator_dispatcher::process() {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                v2.process();
                break;
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    std::optional<debug_checkpoint> emulator_dispatcher::emulate() {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                return v2.emulate();
            default:
                throw std::runtime_error("Invalid version");
        }
        
    }

    debug_checkpoint emulator_dispatcher::step_over() {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
            return v2.step_over();
            default:
                throw std::runtime_error("Invalid version");
        }

    }

    std::optional<debug_checkpoint> emulator_dispatcher::continue_emulation() {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                return v2.continue_emulation();
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    void emulator_dispatcher::add_breakpoint(const std::string &s, uint32_t addr) {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                v2.add_breakpoint(s, addr);
                break;
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    void emulator_dispatcher::remove_breakpoint(const std::string &s, uint32_t addr) {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                v2.remove_breakpoint(s, addr);
                break;
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    void emulator_dispatcher::set_multichannel_debug(bool mc) {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                v2.set_multichannel_debug(mc);
                break;
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    nlohmann::json emulator_dispatcher::get_results() {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                return v2.get_results();
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    void emulator_dispatcher::set_profiler(const std::shared_ptr<instrumentation_core> &prof) {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                v2.set_profiler(prof);
                break;
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    std::map<std::string, disassembled_program> emulator_dispatcher::disassemble() {
        switch(version) {
            case 1:
                throw std::runtime_error("Emulator schema version 1 is no longer supported");
            case 2:
                return v2.disassemble();
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    std::vector<deployed_program> emulator_dispatcher::get_programs() {
        if(version == 1) {
            throw std::runtime_error("Emulator schema version 1 is no longer supported");
        } else if(version == 2) {
            return v2.deploy_programs();

        } else {
            throw std::runtime_error("Invalid version");
        }
    }

    std::map<std::string, std::vector<memory_init_value>>  emulator_dispatcher::get_memory_initializations() {
        std::unordered_map<std::string, std::vector<memory_init_value>> ret;
        if(version == 1) {
            throw std::runtime_error("Emulator schema version 1 is no longer supported");
        } else if(version == 2) {
            return v2.get_memory_init_values();
        } else {
            throw std::runtime_error("Invalid version");
        }
    }

    std::vector<deployed_core_inputs> emulator_dispatcher::get_inputs(const std::string &core) {
        std::vector<deployed_core_inputs> ret;
        if(version == 1) {
            throw std::runtime_error("Emulator schema version 1 is no longer supported");
        } else if(version == 2) {
            return v2.get_inputs(core);
        } else {
            throw std::runtime_error("Invalid version");
        }
    }

    std::vector<deployer_interconnect_slot> emulator_dispatcher::get_interconnect_slots() {
        if(version == 1) {
            throw std::runtime_error("Emulator schema version 1 is no longer supported");
        } else if(version == 2) {
            return v2.get_interconnects();
        } else {
            throw std::runtime_error("Invalid version");
        }
    }

    deployment_options emulator_dispatcher::get_deployment_options(const std::string &core) {
        if(version == 1) {
            throw std::runtime_error("Emulator schema version 1 is no longer supported");
        } else if(version == 2) {
            return v2.get_deployment_options(core);
        } else {
            throw std::runtime_error("Invalid version");
        }
    }

}
