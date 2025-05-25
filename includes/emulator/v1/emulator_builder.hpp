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


#ifndef FCORE_TOOLCHAIN_EMULATOR_BUILDER_HPP
#define FCORE_TOOLCHAIN_EMULATOR_BUILDER_HPP

#include <vector>
#include <cstdint>
#include <memory>

#include "data_structures/emulation/v1/specs/emulator_specs.hpp"
#include "data_structures/emulation/v1/emulator_metadata.hpp"
#include "fcore_dis.hpp"
#include "emulator/v1/backend/emulator_backend.hpp"
#include "fcore_cc.hpp"
#include "fcore_has.hpp"


namespace fcore::emulator {

    class emulator_builder {
    public:
        emulator_builder(bool dbg);
        void set_profiler(const std::shared_ptr<instrumentation_core> &prof) {profiler = prof;};
        fcore_program compile_program(
                const emulator::emulator_core& core_spec,
                const std::vector<emulator::emulator_interconnect>& interconnect_spec,
                std::set<io_map_entry> &am
        );



        static std::vector<uint32_t> sanitize_program(const std::vector<uint32_t>&  raw_prog);


        efi_implementation_t get_efi_implementation(const std::string &s);
        comparator_type_t get_comparator_type(const std::string &s);
    private:

        std::pair<fcore_program,std::set<io_map_entry>> compile_program_c(
                std::vector<std::string> &contents,
                std::vector<std::string> &inc,
                std::unordered_map<std::string, core_iom> &map,
                std::string core_name
        );
        std::pair<fcore_program,std::set<io_map_entry>> compile_program_asm(
                std::vector<std::string> &contents,
                std::vector<std::string> &inc,
                std::unordered_map<std::string, core_iom> &map,
                std::string core_name
                );


        std::shared_ptr<instrumentation_core> profiler = std::make_shared<instrumentation_core>();

        std::unordered_map<std::string, core_iom> process_ioms(
                const std::vector<emulator::emulator_interconnect> &input_connections,
                const std::vector<emulator::emulator_interconnect> &output_connections,
                std::vector<emulator::emulator_input_specs> inputs,
                std::vector<emulator::emulator_output_specs> outputs,
                std::vector<emulator::emulator_memory_specs> memory_init_specs,
                const std::set<std::string>& memories
        );
        static constexpr uint16_t code_section_index = 3;
        bool debug_autogen;
    };
}



#endif //FCORE_TOOLCHAIN_EMULATOR_BUILDER_HPP
