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

#include "backend/emulator.hpp"

emulator::emulator(instruction_stream &s) :memory(2<< (fcore_register_address_width-1), 0) {
    stream = s;

    xip_fpo_init2(xil_a, 8, 24);
    xip_fpo_init2(xil_b, 8, 24);
    xip_fpo_init2(xil_res, 8, 24);
    xip_fpo_fix_init2(xil_a_fixed_point, 32, 0);

}


void emulator::set_inputs(std::unordered_map<uint32_t, uint32_t>) {
    throw std::logic_error("Inputs emulation is not implemented yet!!");
}

void emulator::run_program() {
    for(auto &item:stream){
        run_instruction_by_type(item);
    }
    int i = 0;
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
    }
}

void emulator::run_independent_instruction(const std::shared_ptr<ll_independent_inst_node>& node) {

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
    float raw_a, raw_b;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    memcpy(&raw_b, &b, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);
    xip_fpo_set_flt(xil_b, raw_b);

    xip_fpo_exc_t exc = xip_fpo_add(xil_res, xil_a, xil_b);
    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the addition of"+ std::to_string(a) + " and " + std::to_string(b));
    }
    float raw_res = xip_fpo_get_flt(xil_res);
    memcpy(&res, &raw_res, sizeof(uint32_t));
    return res;
}

uint32_t emulator::execute_sub(uint32_t a, uint32_t b) {
    float raw_a, raw_b;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    memcpy(&raw_b, &b, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);
    xip_fpo_set_flt(xil_b, raw_b);

    xip_fpo_exc_t exc = xip_fpo_sub(xil_res, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the subtraction of"+ std::to_string(a) + " and " + std::to_string(b));
    }

    float raw_res = xip_fpo_get_flt(xil_res);
    memcpy(&res, &raw_res, sizeof(uint32_t));
    return res;
}

uint32_t emulator::execute_mul(uint32_t a, uint32_t b) {
    float raw_a, raw_b;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    memcpy(&raw_b, &b, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);
    xip_fpo_set_flt(xil_b, raw_b);

    xip_fpo_exc_t exc = xip_fpo_mul(xil_res, xil_a, xil_b);
    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the multiplication of"+ std::to_string(a) + " and " + std::to_string(b));
    }

    float raw_res = xip_fpo_get_flt(xil_res);
    memcpy(&res, &raw_res, sizeof(uint32_t));
    return res;
}

uint32_t emulator::execute_rec(uint32_t a) {
    float raw_a;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);

    xip_fpo_exc_t exc = xip_fpo_rec(xil_res, xil_a);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the calculation of the reciprocal of"+ std::to_string(a));
    }

    float raw_res = xip_fpo_get_flt(xil_res);
    memcpy(&res, &raw_res, sizeof(uint32_t));
    return res;
}

uint32_t emulator::execute_fti(uint32_t a) {
    float raw_a;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);

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

    uint32_t res;
    float raw_res = xip_fpo_get_flt(xil_res);
    memcpy(&res, &raw_res, sizeof(uint32_t));
    return res;
}

uint32_t emulator::execute_compare_gt(uint32_t a, uint32_t b) {
    float raw_a, raw_b;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    memcpy(&raw_b, &b, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);
    xip_fpo_set_flt(xil_b, raw_b);

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
    float raw_a, raw_b;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    memcpy(&raw_b, &b, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);
    xip_fpo_set_flt(xil_b, raw_b);

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
    float raw_a, raw_b;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    memcpy(&raw_b, &b, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);
    xip_fpo_set_flt(xil_b, raw_b);

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
    float raw_a, raw_b;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    memcpy(&raw_b, &b, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);
    xip_fpo_set_flt(xil_b, raw_b);

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

uint32_t emulator::execute_satp(uint32_t a, uint32_t b) {
    float raw_a, raw_b;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    memcpy(&raw_b, &b, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);
    xip_fpo_set_flt(xil_b, raw_b);
    float raw_res;

    if(raw_a>raw_b){
        raw_res = raw_b;
    } else {
        raw_res = raw_a;
    }

    memcpy(&res, &raw_res, sizeof(uint32_t));
    return res;
}

uint32_t emulator::execute_satn(uint32_t a, uint32_t b) {
    float raw_a, raw_b;
    uint32_t res;
    memcpy(&raw_a, &a, sizeof(uint32_t));
    memcpy(&raw_b, &b, sizeof(uint32_t));
    xip_fpo_set_flt(xil_a, raw_a);
    xip_fpo_set_flt(xil_b, raw_b);
    float raw_res;
    if(raw_a<raw_b){
        raw_res = raw_b;
    } else {
        raw_res = raw_a;
    }

    memcpy(&res, &raw_res, sizeof(uint32_t));
    return res;
}
