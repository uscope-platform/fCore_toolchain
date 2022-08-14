// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_EMULATOR_H
#define FCORE_TOOLCHAIN_EMULATOR_H

#include <utility>

#include "data_structures/instruction_stream.hpp"
#include "floating_point_v7_1_bitacc_cmodel.h"
#include "fCore_isa.hpp"
class emulator {
public:
    explicit emulator(instruction_stream &s);

    void set_inputs(std::vector<std::pair<unsigned int, std::vector<float>>> &in);
    void set_outputs(std::vector<int> &out);
    void run_program();
    void run_program_with_inputs(unsigned int rounds);
    void run_round();
    std::vector<uint32_t> get_memory() { return memory;};
    std::unordered_map<int, std::vector<float>> get_outputs() { return outputs;};
private:

    std::vector<uint32_t> efi_sort(std::vector<float> &in);

    static uint32_t float_to_uint32(float f);
    static float uint32_to_float(uint32_t u);
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
    void execute_efi(uint32_t op_a, uint32_t op_b, uint32_t dest);
    xip_fpo_t xil_a, xil_b, xil_res;
    xip_fpo_fix_t xil_a_fixed_point;
    instruction_stream stream;

    bool stop_requested;

    std::vector<uint32_t> memory;
    std::vector<int> output_idx;
    std::unordered_map<int, std::vector<float>> outputs{};
    std::vector<std::pair<unsigned int, std::vector<float>>> inputs;
};


#endif //FCORE_TOOLCHAIN_EMULATOR_H
