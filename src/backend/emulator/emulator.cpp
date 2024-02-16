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

#include "backend/emulator/emulator.hpp"



emulator::emulator(instruction_stream &s, int n_channels,const std::string &core) : efi_implementation(core){
    stream = s;
    for(int i = 0; i<n_channels; i++){
        memory_pool[i] = std::make_shared<std::vector<uint32_t>>(2 << (fcore_register_address_width - 1), 0);
    }
    core_name = core;
    working_memory = memory_pool[0];
    stop_requested = false;
}

void emulator::apply_inputs(uint32_t addr, uint32_t data, unsigned int channel) {
    auto selected_mem = memory_pool[channel];
    selected_mem->at(addr) = data;
}

void emulator::run_round(int channel) {

    working_memory = memory_pool[channel];
    for(auto &item:stream){
        run_instruction_by_type(item);
        if(stop_requested) {
            stop_requested = false;
            break;
        }
    }
}

void emulator::run_instruction_by_type(const std::shared_ptr<ll_instruction_node>& node) {
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
        default:
            break;
    }
}

void emulator::run_register_instruction(const std::shared_ptr<ll_register_instr_node>& node) {
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
        spdlog::critical("Encountered the following unimplemented operation: " + opcode);
        exit(-1);
    }

    working_memory->at(writeback_address) = result;
}

void emulator::run_independent_instruction(const std::shared_ptr<ll_independent_inst_node>& node) {
    std::string opcode = node->get_opcode();
    if(opcode == "nop"){
    } else if (opcode == "stop"){
        stop_requested = true;
    } else {
        spdlog::critical("Encountered the following unimplemented operation: " + opcode);
        exit(-1);
    }
}

void emulator::run_conversion_instruction(const std::shared_ptr<ll_conversion_instr_node>& node) {
    std::string opcode = node->get_opcode();

    uint32_t src = node->get_source()->get_bound_reg();
    uint32_t dest = node->get_destination()->get_bound_reg();

    auto dbg_src = working_memory->at(src);

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
        spdlog::critical("Encountered the following unimplemented operation: " + opcode);
        exit(-1);
    }

    working_memory->at(dest) = result;

}

void emulator::run_load_constant_instruction(const std::shared_ptr<ll_load_constant_instr_node>& node) {
    uint32_t const_val;
    float raw_const = node->get_constant_f();

    memcpy(&const_val, &raw_const, sizeof(uint32_t));

    uint32_t dest = node->get_destination()->get_bound_reg();

    working_memory->at(dest) = const_val;
}

uint32_t emulator::execute_add(uint32_t a, uint32_t b) {
    return exec.execute_add(a, b);
}

uint32_t emulator::execute_sub(uint32_t a, uint32_t b) {
    return exec.execute_sub(a, b);
}

uint32_t emulator::execute_mul(uint32_t a, uint32_t b) {
    return exec.execute_mul(a, b);
}

uint32_t emulator::execute_rec(uint32_t a) {
    return exec.execute_rec(a);
}

uint32_t emulator::execute_fti(uint32_t a) {
    return exec.execute_fti(a);
}


uint32_t emulator::execute_itf(uint32_t a) {
    return exec.execute_itf(a);
}

uint32_t emulator::execute_compare_gt(uint32_t a, uint32_t b) {
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

    if(comparator_type== "full") {
        if(res){
            return 0xffffffff;
        } else {
            return 0;
        }
    } else if(comparator_type=="reducing"){
        return res;
    } else if(comparator_type == "none") {
        throw std::runtime_error("The emulator has encountered a comparison instruction on core "+core_name+" which does not have comparators.");
    } else{
        throw std::runtime_error("The emulator has encountered a comparison instruction, however an unknown type was selected in the spec file");
    }
}

uint32_t emulator::execute_compare_le(uint32_t a, uint32_t b) {
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

    if(comparator_type== "full") {
        if(res){
            return 0xffffffff;
        } else {
            return 0;
        }
    } else if(comparator_type=="reducing"){
        return res;
    } else if(comparator_type == "none") {
        throw std::runtime_error("The emulator has encountered a comparison instruction on core "+core_name+" which does not have comparators.");
    } else{
        throw std::runtime_error("The emulator has encountered a comparison instruction, however an unknown type was selected in the spec file");
    }
}

uint32_t emulator::execute_compare_eq(uint32_t a, uint32_t b) {
    bool res = a==b;
    if(comparator_type== "full") {
        if(res){
            return 0xffffffff;
        } else {
            return 0;
        }
    } else if(comparator_type=="reducing"){
        return res;
    } else if(comparator_type == "none") {
        throw std::runtime_error("The emulator has encountered a comparison instruction on core "+core_name+" which does not have comparators.");
    } else{
        throw std::runtime_error("The emulator has encountered a comparison instruction, however an unknown type was selected in the spec file");
    }
}

uint32_t emulator::execute_compare_ne(uint32_t a, uint32_t b) {
    bool res = a!=b;
    if(comparator_type== "full") {
        if(res){
            return 0xffffffff;
        } else {
            return 0;
        }
    } else if(comparator_type=="reducing"){
        return res;
    } else if(comparator_type == "none") {
        throw std::runtime_error("The emulator has encountered a comparison instruction on core "+core_name+" which does not have comparators.");
    } else{
        throw std::runtime_error("The emulator has encountered a comparison instruction, however an unknown type was selected in the spec file");
    }
}

uint32_t emulator::execute_or(uint32_t a, uint32_t b) {
    return a | b;
}

uint32_t emulator::execute_and(uint32_t a, uint32_t b) {
    return a & b;
}

uint32_t emulator::execute_not(uint32_t a) {
    return ~a;
}

uint32_t emulator::execute_abs(uint32_t a) {
    return a&0x7fffffff;
}

uint32_t emulator::execute_popcnt(uint32_t a) {
    return std::bitset<32>(a).count();
}

uint32_t emulator::execute_satp(uint32_t a, uint32_t b) {
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

uint32_t emulator::execute_satn(uint32_t a, uint32_t b) {
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

void emulator::execute_efi(uint32_t op_a, uint32_t op_b, uint32_t dest) {
    efi_implementation.emulate_efi(efi_selector, op_a, op_b, dest, working_memory);
}


uint32_t emulator::float_to_uint32(float f) {
    uint32_t ret;
    memcpy(&ret, &f, sizeof(f));
       return ret;
}

float emulator::uint32_to_float(uint32_t u) {
    float ret;
    memcpy(&ret, &u, sizeof(u));
    return ret;
}

uint32_t emulator::execute_bset(uint32_t a, uint32_t b, uint32_t c) {
    std::bitset<32> bits(a);
    bits[b] = c;
    return bits.to_ulong();
}

uint32_t emulator::execute_bsel(uint32_t a, uint32_t b) {
    return (a & (1<<b))>>b;
}

uint32_t emulator::execute_xor(uint32_t a, uint32_t b) {
    return a ^ b;
}

void emulator::init_memory(const std::unordered_map<unsigned int, uint32_t> &mem_init) {
    for(auto &item: mem_init){
        for(const auto& reg_file:memory_pool){
            reg_file.second->at(item.first) = item.second;
        }

    }
}

uint32_t emulator::get_output(uint32_t addr, int channel) {
    auto selected_memory = memory_pool[channel];
    return selected_memory->at(addr);
}
