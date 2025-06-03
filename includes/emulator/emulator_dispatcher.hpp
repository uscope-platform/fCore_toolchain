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

#include <emulator/v1/emulator_manager.hpp>
#include <emulator/v2/emulator_manager.hpp>

namespace fcore {


    struct memory_init_value {
        std::vector<uint32_t>  address;
        std::variant<std::vector<float>, std::vector<uint32_t>> value;
    };


    struct deployed_core_inputs {
        std::string name;
        iom_metadata metadata;
        source_type_t source_type;
        std::vector<std::variant<std::vector<uint32_t>, std::vector<float>>> data;
        std::vector<uint32_t> address;
        std::vector<uint32_t> channel;
    };

    struct deployed_program {
        std::string name;
        uint16_t index;
        uint32_t sampling_frequency;
        uint32_t order;
        fcore_program program;
        std::vector<deployed_core_inputs> inputs;
    };



    class emulator_dispatcher {
    public:
        void enable_debug_mode();

        void set_specs(const nlohmann::json &spec_file);
        std::set<uint32_t> get_breakpoints(const std::string &id);
        void process();

        std::optional<debug_checkpoint> emulate();
        debug_checkpoint step_over();
        std::optional<debug_checkpoint> continue_emulation();

        void add_breakpoint(const std::string &s, uint32_t addr);
        void remove_breakpoint(const std::string &s, uint32_t addr);
        void set_multichannel_debug(bool mc);
        nlohmann::json get_results();

        void set_profiler(const std::shared_ptr<instrumentation_core> &prof);
        std::unordered_map<std::string, disassembled_program>  disassemble();

        std::vector<deployed_program> get_programs();
        std::unordered_map<std::string, std::vector<memory_init_value>> get_memory_initializations();

        std::vector<deployed_core_inputs> get_inputs(const std::string &core);

        std::vector<deployer_interconnect_slot> get_interconnect_slots();
        uint64_t get_rom_address(const std::string &core);
        uint64_t get_control_address(const std::string &core);

    private:
        uint32_t version = 0;
        emulator::emulator_manager v1;
        emulator_v2::emulator_manager v2;
    };


}



#endif //EMULATOR_DISPATCHER_HPP
