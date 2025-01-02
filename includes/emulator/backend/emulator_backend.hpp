//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_EMULATOR_H
#define FCORE_TOOLCHAIN_EMULATOR_H

#include <utility>
#include <bitset>
#include <set>
#include <spdlog/spdlog.h>

#include "efi_dispatcher.h"
#include "data_structures/emulation/emulation_program.hpp"
#include "data_structures/emulation/emulator_metadata.hpp"
#include "fCore_isa.hpp"

#if GENERAL_PURPOSE_EMULATION==1
    #include "emulator/backend/gp_executor.hpp"
#else
    #include "emulator/backend/ba_executor.hpp"
#endif


namespace fcore{

    class debug_checkpoint{
    public:
        std::string status;
        std::string core_name;
        uint32_t breakpoint;
        emulation_progress_stat progress;
        std::vector<uint32_t> memory_view;
        bool completed_round;
        std::string next_program;
        std::unordered_map<std::string, uint32_t> inputs;
    };


    bool operator==(const debug_checkpoint& lhs, const debug_checkpoint& rhs);
    std::ostream& operator<<(std::ostream& os, const debug_checkpoint& cp);

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(debug_checkpoint, status, core_name, breakpoint, progress, memory_view, completed_round, next_program, inputs )

    class BreakpointException : public std::runtime_error {
    public:
        BreakpointException(const debug_checkpoint& checkpoint)
                : std::runtime_error("internal exception"), data(checkpoint) {}
            debug_checkpoint data;
    };

    class emulator_backend {
    public:
        emulator_backend() = default;
        void set_program(std::vector<uint32_t> p) {prog.process_raw_program(p);};
        void set_comparator_type(const comparator_type_t &t){comparator_type = t;};
        void setup_memory(std::shared_ptr<std::vector<uint32_t>> channel_mem, const std::shared_ptr<std::vector<uint32_t>> &common_mem);
        void run_round(uint32_t init_point);


        debug_checkpoint step_over();
        void set_efi_selector(const efi_implementation_t sel){ efi_selector = sel;};

        std::set<uint32_t> get_breakpoints() {return breakpoints;};
        void add_breakpoint(uint32_t addr) {breakpoints.insert(addr);};
        void remove_breakpoint(uint32_t addr) {breakpoints.erase(addr);};

        void set_core_name(std::string name) {
            efi_backend.set_core_name(name);
            core_name = std::move(name);
        };

        static uint32_t float_to_uint32(float f);
        static float uint32_to_float(uint32_t u);

        debug_checkpoint produce_checkpoint(bool round_complete);

    private:


        void run_instruction_by_type(const uint32_t& opcode, std::array<uint32_t, 3> operands, std::array<bool, 2> io_flags);

        void run_register_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands, std::array<bool, 2> io_flags);
        void run_ternary_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands);
        void run_independent_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands);
        void run_conversion_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands, std::array<bool, 2> io_flags);
        void run_load_constant_instruction(uint32_t dest, uint32_t val);

        uint32_t execute_add(uint32_t a, uint32_t b);
        uint32_t execute_sub(uint32_t a, uint32_t b);
        uint32_t execute_mul(uint32_t a, uint32_t b);
        uint32_t execute_rec(uint32_t a);
        uint32_t execute_fti(uint32_t a);
        uint32_t execute_itf(uint32_t a);
        static uint32_t execute_not(uint32_t a);
        static uint32_t execute_and(uint32_t a, uint32_t b);
        uint32_t execute_abs(uint32_t a);
        uint32_t execute_popcnt(uint32_t a);
        uint32_t execute_satp(uint32_t a, uint32_t b);
        uint32_t execute_satn(uint32_t a, uint32_t b);
        uint32_t execute_bset(uint32_t a, uint32_t b, uint32_t c);
        uint32_t execute_bsel(uint32_t a, uint32_t b);
        uint32_t execute_csel(uint32_t a, uint32_t b, uint32_t c);
        static uint32_t execute_or(uint32_t a, uint32_t b);
        static uint32_t execute_xor(uint32_t a, uint32_t b);
        uint32_t execute_compare_gt(uint32_t a, uint32_t b);
        uint32_t execute_compare_le(uint32_t a, uint32_t b);
        uint32_t execute_compare_eq(uint32_t a, uint32_t b);
        uint32_t execute_compare_ne(uint32_t a, uint32_t b);
        void execute_efi(uint32_t op_a, uint32_t op_b, uint32_t dest);


        uint32_t process_comparison_output(bool val);

        #if GENERAL_PURPOSE_EMULATION==1
                gp_executor exec;
        #else
                ba_executor exec;
        #endif

         uint32_t current_instruction = 0;

        bool stop_requested = false;

        std::string core_name;
        emulation_program prog;
        efi_implementation_t efi_selector;
        comparator_type_t comparator_type;

        efi_dispatcher efi_backend;


        std::shared_ptr<std::vector<uint32_t>> working_memory;
        std::shared_ptr<std::vector<uint32_t>> common_io;


        std::set<uint32_t> breakpoints;

    };
}


#endif //FCORE_TOOLCHAIN_EMULATOR_H
