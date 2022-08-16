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

emulator::emulator(instruction_stream &s) :memory(2<< (fcore_register_address_width-1), 0) {
    stream = s;

    xip_fpo_init2(xil_a, 8, 24);
    xip_fpo_init2(xil_b, 8, 24);
    xip_fpo_init2(xil_res, 8, 24);
    xip_fpo_fix_init2(xil_a_fixed_point, 32, 0);
    stop_requested = false;
}


void emulator::set_inputs(std::vector<std::pair<unsigned int, std::vector<uint32_t>>> &in) {
    inputs = in;
}

void emulator::set_outputs(std::vector<int> &out) {
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
            memory[item.first] = item.second[i];
        }
        run_round();
        for (auto &item:output_idx) {
            outputs[item].push_back(memory[item]);
        }
    }
}

void emulator::run_round() {
    float *dbg = (float*)memory.data();
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

    if(opcode == "add"){
        memory[dest] = execute_add(memory[op_a], memory[op_b]);
    } else if (opcode == "sub"){
        memory[dest] = execute_sub(memory[op_a], memory[op_b]);
    } else if (opcode == "mul"){
        memory[dest] = execute_mul(memory[op_a], memory[op_b]);
    } else if (opcode == "and"){
        memory[dest] = execute_and(memory[op_a], memory[op_b]);
    } else if (opcode == "or"){
        memory[dest] = execute_or(memory[op_a], memory[op_b]);
    } else if (opcode == "satp"){
        memory[dest] = execute_satp(memory[op_a], memory[op_b]);
    } else if (opcode == "satn"){
        memory[dest] = execute_satn(memory[op_a], memory[op_b]);
    } else if (opcode == "beq"){
        memory[dest] = execute_compare_eq(memory[op_a], memory[op_b]);
    } else if (opcode == "bne"){
        memory[dest] = execute_compare_ne(memory[op_a], memory[op_b]);
    } else if (opcode == "bgt"){
        memory[dest] = execute_compare_gt(memory[op_a], memory[op_b]);
    } else if (opcode == "ble"){
        memory[dest] = execute_compare_le(memory[op_a], memory[op_b]);
    } else if (opcode == "efi"){
        execute_efi(op_a, op_b, dest);
    } else if (opcode == "bset"){
        memory[dest] = execute_bset(memory[op_a], memory[op_b]);
    } else if (opcode == "bclr"){
        memory[dest] = execute_bclr(memory[op_a], memory[op_b]);
    } else if (opcode == "binv"){
        memory[dest] = execute_binv(memory[op_a], memory[op_b]);
    } else {
        throw std::runtime_error("EMULATION ERROR: Encountered the following unimplemented operation: " + opcode);
    }
}

void emulator::run_independent_instruction(const std::shared_ptr<ll_independent_inst_node>& node) {
    std::string opcode = node->get_opcode();
    if(opcode == "nop"){
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
        memory[dest] = execute_rec(memory[src]);
    } else if(opcode == "fti"){
        memory[dest] = execute_fti(memory[src]);
    } else if(opcode == "itf"){
        memory[dest] = execute_itf(memory[src]);
    } else if (opcode == "not"){
        memory[dest] = execute_not(memory[src]);
    } else if(opcode == "abs") {
        memory[dest] = execute_abs(memory[src]);
    } else if(opcode == "popcnt") {
        memory[dest] = execute_popcnt(memory[src]);
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

    memory[dest] = const_val;
}

uint32_t emulator::execute_add(uint32_t a, uint32_t b) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    xip_fpo_exc_t exc = xip_fpo_add(xil_res, xil_a, xil_b);
    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the addition of"+ std::to_string(a) + " and " + std::to_string(b));
    }

    return float_to_uint32(xip_fpo_get_flt(xil_res));
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
    return xip_fpo_fix_get_ui(xil_a_fixed_point);
}


uint32_t emulator::execute_itf(uint32_t a) {
    xip_fpo_fix_set_ui(xil_a_fixed_point, a);
    xip_fpo_exc_t exc = xip_fpo_fixtoflt(xil_res, xil_a_fixed_point);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the conversion of "+ std::to_string(a) + "to float from integer");
    }

    return float_to_uint32(xip_fpo_get_flt(xil_res));
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



class cell {
public:
    cell(double v, int s, bool o);
    bool operator <(const cell &b) const;
    double voltage;
    float idx;  // Does not participate in comparisons
    bool order;
};


cell::cell(double v, int s, bool o) {
    voltage = v;
    idx = s;
    order = o;
}

bool cell::operator<(const cell &b) const {
    if(order)
        return voltage > b.voltage;
    else
        return b.voltage > voltage;
}

void emulator::execute_efi(uint32_t op_a, uint32_t op_b, uint32_t dest) {
    std::vector<float> in;
    for(int i = 0; i<op_b; i++){
        in.push_back(uint32_to_float(memory[op_a+i]));
    }
    std::vector<uint32_t> out = efi_sort(in);
    for (int i = 0; i < out.size(); ++i) {
        memory[dest+i] = out[i];
    }
}

std::vector<uint32_t> emulator::efi_sort(std::vector<float> &in) {
    bool descending_order  = in[0] == 1.0;
    std::vector<cell> cells;
    std::vector<uint32_t> idx;
    idx.reserve(in.size());
    cells.reserve(in.size());

    for (int i = 1; i < in.size(); i++) {
        cells.emplace_back(in[i], i, descending_order);
    }

    std::sort(cells.begin(), cells.end());


    for(auto &item:cells){
        idx.push_back((uint32_t)(item.idx));
    }
    return idx;
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

uint32_t emulator::execute_bset(uint32_t a, uint32_t b) {
    return  a | (1<<b);
}

uint32_t emulator::execute_bclr(uint32_t a, uint32_t b) {
    return  a & ~(1<<b);
}

uint32_t emulator::execute_binv(uint32_t a, uint32_t b) {
    return  a ^ (1<<b);
}
