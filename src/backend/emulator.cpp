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

#include "backend/emulator.hpp"

#include <utility>

emulator::emulator(instruction_stream &s) {
    stream = s;
    memory = std::make_shared<std::vector<uint32_t>>(2<< (fcore_register_address_width-1), 0);
    efi_implementation.set_memory(memory);
    xip_fpo_init2(xil_a, 8, 24);
    xip_fpo_init2(xil_b, 8, 24);
    xip_fpo_init2(xil_res, 8, 24);
    xip_fpo_fix_init2(xil_a_fixed_point, 32, 0);
    stop_requested = false;
}


void emulator::set_inputs(std::vector<std::pair<unsigned int, std::vector<uint32_t>>> &in) {
    inputs = in;
}

void emulator::set_outputs(std::vector<emulator_output_t> &out) {
    output_idx = out;
}


void emulator::run_program() {
    if(!inputs.empty()){
        unsigned int n_rounds = inputs[0].second.size();
        run_program_with_inputs(n_rounds);
    } else {
        run_round();
    }
}

void emulator::run_program_with_inputs(unsigned int rounds) {
    for(unsigned int i = 0; i<rounds; i++){
        for(auto item:inputs){
            memory->at(item.first) = item.second[i];
        }
        run_round();
        for (auto &item:output_idx) {
            outputs[item.reg_n].push_back(memory->at(item.reg_n));
        }
    }
}

void emulator::run_round() {
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

    std::string raw_dest = node->get_destination()->get_name();
    uint32_t dest = std::stoul(raw_dest.substr(1, raw_dest.size()-1));

    std::string raw_op_a = node->get_operand_a()->get_name();
    uint32_t op_a = std::stoul(raw_op_a.substr(1, raw_op_a.size()-1));

    std::string raw_op_b = node->get_operand_b()->get_name();
    uint32_t op_b = std::stoul(raw_op_b.substr(1, raw_op_b.size()-1));

    auto a = memory->at(op_a);
    auto b = memory->at(op_b);

    if(opcode == "add"){
        memory->at(dest) = execute_add(a, b);
    } else if (opcode == "sub"){
        memory->at(dest) = execute_sub(a, b);
    } else if (opcode == "mul"){
        memory->at(dest) = execute_mul(a, b);
    } else if (opcode == "and"){
        memory->at(dest) = execute_and(a, b);
    } else if (opcode == "or"){
        memory->at(dest) = execute_or(a, b);
    } else if (opcode == "xor"){
        memory->at(dest) = execute_xor(a, b);
    } else if (opcode == "satp"){
        memory->at(dest) = execute_satp(a, b);
    } else if (opcode == "satn"){
        memory->at(dest) = execute_satn(a, b);
    } else if (opcode == "beq"){
        memory->at(dest) = execute_compare_eq(a, b);
    } else if (opcode == "bne"){
        memory->at(dest) = execute_compare_ne(a, b);
    } else if (opcode == "bgt"){
        memory->at(dest) = execute_compare_gt(a, b);
    } else if (opcode == "ble"){
        memory->at(dest) = execute_compare_le(a, b);
    } else if (opcode == "efi"){
        execute_efi(op_a, op_b, dest);
    } else if (opcode == "bset"){
        auto res = execute_bset(memory->at(op_a), memory->at(op_b), memory->at(dest));
        memory->at(op_a) = res;
    } else if (opcode == "bsel"){
        memory->at(dest) = execute_bsel(a, b);
    } else {
        throw std::runtime_error("EMULATION ERROR: Encountered the following unimplemented operation: " + opcode);
    }
}

void emulator::run_independent_instruction(const std::shared_ptr<ll_independent_inst_node>& node) {
    std::string opcode = node->get_opcode();
    if(opcode == "nop"){
        int a = 0;
    } else if (opcode == "stop"){
        stop_requested = true;
    } else {
        throw std::runtime_error("EMULATION ERROR: Encountered the following unimplemented operation: " + opcode);
    }
}

void emulator::run_conversion_instruction(const std::shared_ptr<ll_conversion_instr_node>& node) {
    std::string opcode = node->get_opcode();

    std::string raw_dest = node->get_destination()->get_name();
    uint32_t dest = std::stoul(raw_dest.substr(1, raw_dest.size()-1));

    std::string raw_src = node->get_source()->get_name();
    uint32_t src = std::stoul(raw_src.substr(1, raw_src.size()-1));
    if(opcode == "rec"){
        memory->at(dest) = execute_rec(memory->at(src));
    } else if(opcode == "fti"){
        memory->at(dest) = execute_fti(memory->at(src));
    } else if(opcode == "itf"){
        memory->at(dest) = execute_itf(memory->at(src));
    } else if (opcode == "not"){
        memory->at(dest) = execute_not(memory->at(src));
    } else if(opcode == "abs") {
        memory->at(dest) = execute_abs(memory->at(src));
    } else if(opcode == "popcnt") {
        memory->at(dest) = execute_popcnt(memory->at(src));
        int i = 0;
    } else {
            throw std::runtime_error("EMULATION ERROR: Encountered the following unimplemented operation: " + opcode);
    }
}

void emulator::run_load_constant_instruction(const std::shared_ptr<ll_load_constant_instr_node>& node) {
    uint32_t const_val;
    float raw_const = node->get_constant_f();

    memcpy(&const_val, &raw_const, sizeof(uint32_t));

    std::string raw_dest = node->get_destination()->get_name();
    uint32_t dest = std::stoul(raw_dest.substr(1, raw_dest.size()-1));

    memory->at(dest) = const_val;
}

uint32_t emulator::execute_add(uint32_t a, uint32_t b) {
    if(b==0){ // I must be doing something wrong... investigate why these are necessary
        return a;
    } else if(a==0){
        return b;
    }
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    xip_fpo_exc_t exc = xip_fpo_add(xil_res, xil_a, xil_b);
    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the addition of"+ std::to_string(a) + " and " + std::to_string(b));
    }

    auto fv = xip_fpo_get_flt(xil_res);
    return float_to_uint32(fv);
}

uint32_t emulator::execute_sub(uint32_t a, uint32_t b) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    xip_fpo_exc_t exc = xip_fpo_sub(xil_res, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the subtraction of"+ std::to_string(a) + " and " + std::to_string(b));
    }

    return float_to_uint32(xip_fpo_get_flt(xil_res));
}

uint32_t emulator::execute_mul(uint32_t a, uint32_t b) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    xip_fpo_exc_t exc = xip_fpo_mul(xil_res, xil_a, xil_b);
    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the multiplication of"+ std::to_string(a) + " and " + std::to_string(b));
    }

    return float_to_uint32(xip_fpo_get_flt(xil_res));
}

uint32_t emulator::execute_rec(uint32_t a) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));

    xip_fpo_exc_t exc = xip_fpo_rec(xil_res, xil_a);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the calculation of the reciprocal of"+ std::to_string(a));
    }

    return float_to_uint32(xip_fpo_get_flt(xil_res));
}

uint32_t emulator::execute_fti(uint32_t a) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));

    xip_fpo_exc_t exc = xip_fpo_flttofix(xil_a_fixed_point, xil_a);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the conversion of "+ std::to_string(a) + "to integer from float");
    }
    return (uint32_t) xip_fpo_fix_get_si(xil_a_fixed_point);
}


uint32_t emulator::execute_itf(uint32_t a) {
    xip_fpo_fix_set_si(xil_a_fixed_point, (int32_t)a);
    xip_fpo_exc_t exc = xip_fpo_fixtoflt(xil_res, xil_a_fixed_point);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the conversion of "+ std::to_string(a) + "to float from integer");
    }
    auto fv = xip_fpo_get_flt(xil_res);
    return float_to_uint32(fv);
}

uint32_t emulator::execute_compare_gt(uint32_t a, uint32_t b) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    int res_int;
    xip_fpo_exc_t exc = xip_fpo_greater(&res_int, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the comparison of "+ std::to_string(a) + " and " + std::to_string(b) + " (greater than)");
    }

    if(res_int){
        return 0xffffffff;
    } else {
        return 0;
    }
}

uint32_t emulator::execute_compare_le(uint32_t a, uint32_t b) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    int res_int;
    xip_fpo_exc_t exc = xip_fpo_lessequal(&res_int, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the comparison of "+ std::to_string(a) + " and " + std::to_string(b) + " (less than or equal)");
    }
    if(res_int){
        return 0xffffffff;
    } else {
        return 0;
    }
}

uint32_t emulator::execute_compare_eq(uint32_t a, uint32_t b) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    int res_int;
    xip_fpo_exc_t exc = xip_fpo_equal(&res_int, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the comparison of "+ std::to_string(a) + " and " + std::to_string(b) + " (equal)");
    }
    if(res_int){
        return 0xffffffff;
    } else {
        return 0;
    }
}

uint32_t emulator::execute_compare_ne(uint32_t a, uint32_t b) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    int res_int;
    xip_fpo_exc_t exc = xip_fpo_notequal(&res_int, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the comparison of "+ std::to_string(a) + " and " + std::to_string(b) + " (not equal)");
    }

    if(res_int){
        return 0xffffffff;
    } else {
        return 0;
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
    int count;
    for (count = 0; a != 0; count++, a &= a-1);
    return count;
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
    efi_implementation.emulate_efi(efi_selector, op_a, op_b, dest);
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

void emulator::init_memory(std::unordered_map<unsigned int, uint32_t> &mem_init) {
    for(auto &item: mem_init){
        memory->at(item.first) = item.second;
    }
}
