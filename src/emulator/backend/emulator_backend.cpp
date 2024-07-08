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

#include "emulator/backend/emulator_backend.hpp"




fcore::emulator_backend::emulator_backend(instruction_stream &s, int n_channels, const std::string &core) : efi_backend(core){
    stream = s;

    core_name = core;
    stop_requested = false;
}


void fcore::emulator_backend::run_round(std::shared_ptr<std::vector<uint32_t>> mem) {

    working_memory = std::move(mem);
    for(auto &item:stream){
        run_instruction_by_type(item);
        if(stop_requested) {
            stop_requested = false;
            break;
        }
    }
}

void fcore::emulator_backend::run_instruction_by_type(const std::shared_ptr<ll_instruction_node>& node) {
    switch (node->get_type()) {
        case isa_independent_instruction:
            run_independent_instruction(std::static_pointer_cast<ll_independent_inst_node>(node));
            break;
        case isa_register_instruction:
            run_register_instruction(std::static_pointer_cast<ll_register_instr_node>(node));
            break;
        case isa_conversion_instruction:
            run_conversion_instruction(std::static_pointer_cast<ll_conversion_instr_node>(node));
            break;
        case isa_load_constant_instruction:
            run_load_constant_instruction(std::static_pointer_cast<ll_load_constant_instr_node>(node));
            break;
        case isa_ternary_instruction:
            run_ternary_instruction(std::static_pointer_cast<ll_ternary_instr_node>(node));
            break;
        default:
            break;
    }
}

void fcore::emulator_backend::run_ternary_instruction(const std::shared_ptr<ll_ternary_instr_node> &node) {
    std::string opcode = node->get_opcode();

    uint32_t op_a = node->get_operand_a()->get_bound_reg();
    uint32_t op_b = node->get_operand_b()->get_bound_reg();
    uint32_t op_c = node->get_operand_c()->get_bound_reg();

    auto a = working_memory->at(op_a);
    auto b = working_memory->at(op_b);
    auto c = working_memory->at(op_c);

    uint32_t result;
    uint32_t writeback_address = op_a;

    if(opcode == "csel"){
        result = execute_csel(a, b, c);
    } else {
        throw std::runtime_error("Encountered the following unimplemented operation: " + opcode);
    }

    working_memory->at(writeback_address) = result;
}

void fcore::emulator_backend::run_register_instruction(const std::shared_ptr<ll_register_instr_node>& node) {
    std::string opcode = node->get_opcode();

    uint32_t dest = node->get_destination()->get_bound_reg();
    uint32_t op_a = node->get_operand_a()->get_bound_reg();
    uint32_t op_b = node->get_operand_b()->get_bound_reg();

    auto a = working_memory->at(op_a);
    auto b = working_memory->at(op_b);

    uint32_t result;
    uint32_t writeback_address = dest;

    if(opcode == "add"){
        result = execute_add(a, b);
    } else if (opcode == "sub"){
        result = execute_sub(a, b);
    } else if (opcode == "mul"){
        result = execute_mul(a, b);
    } else if (opcode == "and"){
        result = execute_and(a, b);
    } else if (opcode == "or"){
        result = execute_or(a, b);
    } else if (opcode == "xor"){
        result = execute_xor(a, b);
    } else if (opcode == "satp"){
        result = execute_satp(a, b);
    } else if (opcode == "satn"){
        result  = execute_satn(a, b);
    } else if (opcode == "beq"){
        result = execute_compare_eq(a, b);
    } else if (opcode == "bne"){
        result = execute_compare_ne(a, b);
    } else if (opcode == "bgt"){
        result = execute_compare_gt(a, b);
    } else if (opcode == "ble"){
        result = execute_compare_le(a, b);
    } else if (opcode == "efi"){
        execute_efi(op_a, op_b, dest);
        return;
    } else if (opcode == "bset"){
        result = execute_bset(working_memory->at(op_a), working_memory->at(op_b), working_memory->at(dest));
        writeback_address = op_a;
    } else if (opcode == "bsel"){
        result = execute_bsel(a, b);
    } else {
        throw std::runtime_error("Encountered the following unimplemented operation: " + opcode);
    }

    working_memory->at(writeback_address) = result;
}

void fcore::emulator_backend::run_independent_instruction(const std::shared_ptr<ll_independent_inst_node>& node) {
    std::string opcode = node->get_opcode();
    if(opcode == "nop"){
    } else if (opcode == "stop"){
        stop_requested = true;
    } else {
        throw std::runtime_error("Encountered the following unimplemented operation: " + opcode);
    }
}

void fcore::emulator_backend::run_conversion_instruction(const std::shared_ptr<ll_conversion_instr_node>& node) {
    std::string opcode = node->get_opcode();

    uint32_t src = node->get_source()->get_bound_reg();
    uint32_t dest = node->get_destination()->get_bound_reg();

    uint32_t result;
    if(opcode == "rec"){
        result = execute_rec(working_memory->at(src));
    } else if(opcode == "fti"){
        result = execute_fti(working_memory->at(src));
    } else if(opcode == "itf"){
        result = execute_itf(working_memory->at(src));
    } else if (opcode == "not"){
        result = execute_not(working_memory->at(src));
    } else if(opcode == "abs") {
        result = execute_abs(working_memory->at(src));
    } else if(opcode == "popcnt") {
        result = execute_popcnt(working_memory->at(src));
    } else {
        throw std::runtime_error("Encountered the following unimplemented operation: " + opcode);
    }

    working_memory->at(dest) = result;

}

void fcore::emulator_backend::run_load_constant_instruction(const std::shared_ptr<ll_load_constant_instr_node>& node) {
    uint32_t const_val;
    float raw_const = node->get_constant_f();

    memcpy(&const_val, &raw_const, sizeof(uint32_t));

    uint32_t dest = node->get_destination()->get_bound_reg();

    working_memory->at(dest) = const_val;
}

uint32_t fcore::emulator_backend::execute_add(uint32_t a, uint32_t b) {
    return exec.execute_add(a, b);
}

uint32_t fcore::emulator_backend::execute_sub(uint32_t a, uint32_t b) {
    return exec.execute_sub(a, b);
}

uint32_t fcore::emulator_backend::execute_mul(uint32_t a, uint32_t b) {
    return exec.execute_mul(a, b);
}

uint32_t fcore::emulator_backend::execute_rec(uint32_t a) {
    return exec.execute_rec(a);
}

uint32_t fcore::emulator_backend::execute_fti(uint32_t a) {
    return exec.execute_fti(a);
}


uint32_t fcore::emulator_backend::execute_itf(uint32_t a) {
    return exec.execute_itf(a);
}

uint32_t fcore::emulator_backend::execute_compare_gt(uint32_t a, uint32_t b) {
    bool sign_a = (1<<31) & a;
    bool sign_b = (1<<31) & b;

    bool res;

    if(sign_a & sign_b) {
        res = a < b;
    }else if(sign_a & !sign_b){
        res = false;
    } else if(!sign_a & sign_b){
        res = true;
    } else {
        res = a>b;
    }

    return process_comparison_output(res);
}

uint32_t fcore::emulator_backend::execute_compare_le(uint32_t a, uint32_t b) {
    bool sign_a = (1<<31) & a;
    bool sign_b = (1<<31) & b;

    bool res;
    if(a == b){
        res = true;
    } else if(sign_a & sign_b) {
        res = a>b;
    }else if(sign_a & !sign_b){
        res = true;
    } else if(!sign_a & sign_b){
        res = false;
    }else {
        res = a<=b;
    }
    return process_comparison_output(res);
}

uint32_t fcore::emulator_backend::execute_compare_eq(uint32_t a, uint32_t b) {
    return process_comparison_output(a==b);
}

uint32_t fcore::emulator_backend::execute_compare_ne(uint32_t a, uint32_t b) {
    return process_comparison_output(a!=b);
}

uint32_t fcore::emulator_backend::execute_or(uint32_t a, uint32_t b) {
    return a | b;
}

uint32_t fcore::emulator_backend::execute_and(uint32_t a, uint32_t b) {
    return a & b;
}

uint32_t fcore::emulator_backend::execute_not(uint32_t a) {
    return ~a;
}

uint32_t fcore::emulator_backend::execute_abs(uint32_t a) {
    return a&0x7fffffff;
}

uint32_t fcore::emulator_backend::execute_popcnt(uint32_t a) {
    return std::bitset<32>(a).count();
}

uint32_t fcore::emulator_backend::execute_satp(uint32_t a, uint32_t b) {
    float raw_a = uint32_to_float(a);
    float raw_b = uint32_to_float(b);

    float raw_res;

    if(raw_a>raw_b){
        raw_res = raw_b;
    } else {
        raw_res = raw_a;
    }

    return float_to_uint32(raw_res);
}

uint32_t fcore::emulator_backend::execute_satn(uint32_t a, uint32_t b) {
    float raw_a = uint32_to_float(a);
    float raw_b = uint32_to_float(b);

    float raw_res;
    if(raw_a<raw_b){
        raw_res = raw_b;
    } else {
        raw_res = raw_a;
    }

    return float_to_uint32(raw_res);
}

void fcore::emulator_backend::execute_efi(uint32_t op_a, uint32_t op_b, uint32_t dest) {
    efi_backend.emulate_efi(efi_selector, op_a, op_b, dest, working_memory);
}


uint32_t fcore::emulator_backend::float_to_uint32(float f) {
    uint32_t ret;
    memcpy(&ret, &f, sizeof(f));
       return ret;
}

float fcore::emulator_backend::uint32_to_float(uint32_t u) {
    float ret;
    memcpy(&ret, &u, sizeof(u));
    return ret;
}

uint32_t fcore::emulator_backend::execute_bset(uint32_t a, uint32_t b, uint32_t c) {
    std::bitset<32> bits(a);
    bits[b] = c;
    return bits.to_ulong();
}

uint32_t fcore::emulator_backend::execute_bsel(uint32_t a, uint32_t b) {
    return (a & (1<<b))>>b;
}

uint32_t fcore::emulator_backend::execute_xor(uint32_t a, uint32_t b) {
    return a ^ b;
}


uint32_t fcore::emulator_backend::execute_csel(uint32_t a, uint32_t b, uint32_t c) {
    if(a & 0x1){
        return b;
    } else {
        return c;
    }
}

uint32_t fcore::emulator_backend::process_comparison_output(bool val) {

    if(comparator_type== comparator_full) {
        if(val){
            return 0xffffffff;
        } else {
            return 0;
        }
    } else if(comparator_type==comparator_reducing){
        return val;
    } else if(comparator_type == comparator_none) {
        throw std::runtime_error("The emulator has encountered a comparison instruction on core "+core_name+" which does not have comparators.");
    } else{
        throw std::runtime_error("The emulator has encountered a comparison instruction, however an unknown type was selected in the spec file");
    }
}
