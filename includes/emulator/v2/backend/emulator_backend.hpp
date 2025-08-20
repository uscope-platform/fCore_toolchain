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

#ifndef FCORE_TOOLCHAIN_EMULATOR_V2_H
#define FCORE_TOOLCHAIN_EMULATOR_V2_H

#include <utility>
#include <bitset>
#include <set>
#include <spdlog/spdlog.h>

#include "efi_dispatcher.h"
#include "data_structures/emulation/v2/emulation_program.hpp"
#include "data_structures/emulation/v2/emulator_metadata.hpp"
#include "fCore_isa.hpp"

#if GENERAL_PURPOSE_EMULATION==1
    #include "emulator/v2/backend/gp_executor.hpp"
#else
    #include "emulator/v2/backend/ba_executor.hpp"
#endif

#include "emulator/emulator_metadata_common.hpp"

namespace fcore::emulator_v2{


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
        void run_round(int init_point);

        void reset_instruction_pointer() {current_instruction =0;};

        debug_checkpoint step_over();
        void set_efi_selector(const efi_implementation_t sel){ efi_selector = sel;};

        std::set<uint32_t> get_breakpoints() {return breakpoints;};
        void add_breakpoint(uint32_t addr) {breakpoints.insert(addr);};
        void remove_breakpoint(uint32_t addr) {breakpoints.erase(addr);};

        void set_core_name(std::string name) {
            efi_backend.set_core_name(name);
            core_name = std::move(name);
        };

        void set_debugging(bool value) {debugging_enabled = value;};

        static std::vector<uint32_t> float_to_uint32_v(const std::vector<float> &f);

        static uint32_t float_to_uint32(float f);
        static float uint32_to_float(uint32_t u);

        debug_checkpoint produce_checkpoint(bool round_complete);

    private:


        void run_instruction_by_type(const uint32_t& opcode, std::array<uint32_t, 3> operands, std::array<bool, 3> io_flags);

        void run_register_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands, std::array<bool, 3> io_flags);
        void run_ternary_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands, std::array<bool, 3> io_flags);
        void run_independent_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands);
        void run_conversion_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands, std::array<bool, 3> io_flags);
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

         int current_instruction = -1;

        bool stop_requested = false;
        bool debugging_enabled = true;

        std::string core_name;
        emulation_program prog;
        efi_implementation_t efi_selector;
        comparator_type_t comparator_type;

        efi_dispatcher efi_backend;


        std::shared_ptr<std::vector<uint32_t>> working_memory;
        std::shared_ptr<std::vector<uint32_t>> common_io;


        std::set<uint32_t> breakpoints;

    };

    inline std::vector<uint32_t> emulator_backend::float_to_uint32_v(const std::vector<float> &f) {
        std::vector<uint32_t> res;
            for(auto &x:f) {
                res.push_back(float_to_uint32(x));
            }
        return res;
    }
}


#endif //FCORE_TOOLCHAIN_EMULATOR_V2_H
