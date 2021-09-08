// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_EMULATOR_H
#define FCORE_TOOLCHAIN_EMULATOR_H

#include <utility>

#include "data_structures/instruction_stream.hpp"
#include "floating_point_v7_1_bitacc_cmodel.h"
#include "fCore_isa.hpp"
class emulator {
public:
    explicit emulator(instruction_stream &s);

    void set_inputs(std::unordered_map<uint32_t, uint32_t>);
    void run_program();
    std::vector<uint32_t> get_memory() { return memory;};
private:

    void run_instruction_by_type(const std::shared_ptr<ll_instruction_node>& node);

    void run_register_instruction(const std::shared_ptr<ll_register_instr_node>& node);
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
    uint32_t execute_satp(uint32_t a, uint32_t b);
    uint32_t execute_satn(uint32_t a, uint32_t b);
    static uint32_t execute_or(uint32_t a, uint32_t b);
    uint32_t execute_compare_gt(uint32_t a, uint32_t b);
    uint32_t execute_compare_le(uint32_t a, uint32_t b);
    uint32_t execute_compare_eq(uint32_t a, uint32_t b);
    uint32_t execute_compare_ne(uint32_t a, uint32_t b);

    xip_fpo_t xil_a, xil_b, xil_res;
    xip_fpo_fix_t xil_a_fixed_point;
    instruction_stream stream;

    std::vector<uint32_t> memory;
};


#endif //FCORE_TOOLCHAIN_EMULATOR_H
