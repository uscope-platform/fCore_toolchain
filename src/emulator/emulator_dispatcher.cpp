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
                v1.set_specs(spec_file);
                break;
            case 2:
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
            return v1.get_breakpoints(id);
            case 2:
            return v2.get_breakpoints(id);
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    void emulator_dispatcher::process() {
        switch(version) {
            case 1:
                v1.process();
                break;
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
            return v1.emulate();
            case 2:
                return v2.emulate();
            default:
                throw std::runtime_error("Invalid version");
        }
        
    }

    debug_checkpoint emulator_dispatcher::step_over() {
        switch(version) {
            case 1:
            return v1.step_over();
            case 2:
            return v2.step_over();
            default:
                throw std::runtime_error("Invalid version");
        }

    }

    std::optional<debug_checkpoint> emulator_dispatcher::continue_emulation() {
        switch(version) {
            case 1:
            return v1.continue_emulation();
            case 2:
            return v2.continue_emulation();
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    void emulator_dispatcher::add_breakpoint(const std::string &s, uint32_t addr) {
        switch(version) {
            case 1:
                v1.add_breakpoint(s, addr);
                break;
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
                v1.remove_breakpoint(s, addr);
                break;
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
                v1.set_multichannel_debug(mc);
                break;
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
                return v1.get_results();
            case 2:
                return v2.get_results();
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    void emulator_dispatcher::set_profiler(const std::shared_ptr<instrumentation_core> &prof) {
        switch(version) {
            case 1:
                v1.set_profiler(prof);
                break;
            case 2:
                v2.set_profiler(prof);
                break;
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    std::unordered_map<std::string, disassembled_program> emulator_dispatcher::disassemble() {
        switch(version) {
            case 1:
                return v1.disassemble();
            case 2:
                return v2.disassemble();
            default:
                throw std::runtime_error("Invalid version");
        }
    }

    std::vector<deployed_program> emulator_dispatcher::get_programs() {
        if(version == 1) {
            auto bundles = v1.get_programs();
            std::vector<deployed_program> ret;
            for(int i = 0; i<bundles.size(); i++) {
                deployed_program dp;
                dp.index = i;
                dp.sampling_frequency = bundles[i].sampling_frequency;
                dp.name = bundles[i].name;
                dp.program = bundles[i].program;
                ret.push_back(dp);
            }
            return ret;
        } else if(version == 2) {
            auto bundles = v2.get_programs();
            std::vector<deployed_program> ret;
            for(int i = 0; i<bundles.size(); i++) {
                deployed_program dp;
                dp.index = i;
                dp.sampling_frequency = bundles[i].sampling_frequency;
                dp.name = bundles[i].name;
                dp.program = bundles[i].program;
                ret.push_back(dp);
            }
            return ret;
        } else {
            throw std::runtime_error("Invalid version");
        }
    }

    std::unordered_map<std::string, uint32_t> emulator_dispatcher::get_sampling_frequencies() {
        std::unordered_map<std::string, uint32_t> ret;
        if(version == 1) {
            auto bundles = v1.get_programs();
            for(auto &bundle:bundles) {
                ret.insert({bundle.name, bundle.sampling_frequency});
            }
            return ret;
        } else if(version == 2) {
            auto bundles = v2.get_programs();
            for(auto &bundle:bundles) {
                ret.insert({bundle.name, bundle.sampling_frequency});
            }
            return ret;
        } else {
            throw std::runtime_error("Invalid version");
        }
    }

    std::unordered_map<std::string, std::vector<memory_init_value>>  emulator_dispatcher::get_memory_initializations() {
        std::unordered_map<std::string, std::vector<memory_init_value>> ret;
        if(version == 1) {
            auto bundles = v1.get_programs();
            for(auto &bundle:bundles) {
                for(auto mem_init: bundle.memories) {
                    memory_init_value val;
                    val.address = mem_init.address;
                    val.value = mem_init.value;
                    ret[bundle.name].push_back(val);
                }
            }
            return ret;
        } else if(version == 2) {
            auto bundles = v2.get_programs();
            for(auto &bundle:bundles) {
                for(auto mem_init: bundle.memories) {
                    memory_init_value val;
                    val.address = {0};
                    val.value = mem_init.value;
                    ret[bundle.name].push_back(val);
                }
            }
            return ret;
        } else {
            throw std::runtime_error("Invalid version");
        }
    }
}
