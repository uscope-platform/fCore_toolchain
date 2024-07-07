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
#include <spdlog/spdlog.h>

#include "efi_dispatcher.h"
#include "data_structures/instruction_stream.hpp"
#include "data_structures/emulation/emulator_metadata.hpp"
#include "fCore_isa.hpp"

#if GENERAL_PURPOSE_EMULATION==1
    #include "emulator/backend/gp_executor.hpp"
#else
    #include "emulator/backend/ba_executor.hpp"
#endif


namespace fcore{
    class emulator_backend {
    public:
        emulator_backend(instruction_stream &s, int n_channels, const std::string &core);

        void set_comparator_type(const comparator_type_t &t){comparator_type = t;};
        void run_round(std::shared_ptr<std::vector<uint32_t>> mem);
        void set_efi_selector(const efi_implementation_t sel){ efi_selector = sel;};

        std::string get_name() {return core_name;};

        static uint32_t float_to_uint32(float f);
        static float uint32_to_float(uint32_t u);
    private:
        void run_instruction_by_type(const std::shared_ptr<ll_instruction_node>& node);

        void run_register_instruction(const std::shared_ptr<ll_register_instr_node>& node);
        void run_ternary_instruction(const std::shared_ptr<ll_ternary_instr_node>& node);
        void run_independent_instruction(const std::shared_ptr<ll_independent_inst_node>& node);
        void run_conversion_instruction(const std::shared_ptr<ll_conversion_instr_node>& node);
        void run_load_constant_instruction(const std::shared_ptr<ll_load_constant_instr_node>& node);

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

        bool stop_requested;

        instruction_stream stream;
        efi_implementation_t efi_selector;
        comparator_type_t comparator_type;

        efi_dispatcher efi_backend;

        std::string core_name;

        std::shared_ptr<std::vector<uint32_t>> working_memory;
    };
}


#endif //FCORE_TOOLCHAIN_EMULATOR_H
