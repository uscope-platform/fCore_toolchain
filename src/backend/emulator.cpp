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

emulator::emulator(instruction_stream &s) {
    stream = std::move(s);

    xip_fpo_init2(xil_a, 8, 24);
    xip_fpo_init2(xil_b, 8, 24);
    xip_fpo_init2(xil_res, 8, 24);
    xip_fpo_fix_init2(xil_a_fixed_point, 32, 0);

    memory.reserve(2<< fcore_register_address_width);
    std::fill(memory.begin(), memory.end(), 0);

}


void emulator::set_inputs(std::unordered_map<uint32_t, uint32_t>) {
    throw std::logic_error("Inputs emulation is not implemented yet!!");
}

void emulator::run_program() {
    for(auto &item:stream){
        run_instruction_by_type(item);
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

}

void emulator::run_independent_instruction(const std::shared_ptr<ll_independent_inst_node>& node) {

}

void emulator::run_conversion_instruction(const std::shared_ptr<ll_conversion_instr_node>& node) {

}

void emulator::run_load_constant_instruction(const std::shared_ptr<ll_load_constant_instr_node>& node) {

}

uint32_t emulator::execute_add(uint32_t a, uint32_t b) {
    xip_fpo_set_ui(xil_a, a);
    xip_fpo_set_ui(xil_b, b);
    xip_fpo_exc_t exc = xip_fpo_add(xil_res, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the addition of"+ std::to_string(a) + " and " + std::to_string(b));
    }
    return xip_fpo_get_ui(xil_res);
}

uint32_t emulator::execute_sub(uint32_t a, uint32_t b) {
    xip_fpo_set_ui(xil_a, a);
    xip_fpo_set_ui(xil_b, b);
    xip_fpo_exc_t exc = xip_fpo_sub(xil_res, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the subtraction of"+ std::to_string(a) + " and " + std::to_string(b));
    }
    return xip_fpo_get_ui(xil_res);
}

uint32_t emulator::execute_mul(uint32_t a, uint32_t b) {
    xip_fpo_set_ui(xil_a, a);
    xip_fpo_set_ui(xil_b, b);
    xip_fpo_exc_t exc = xip_fpo_mul(xil_res, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the multiplication of"+ std::to_string(a) + " and " + std::to_string(b));
    }
    return xip_fpo_get_ui(xil_res);
}

uint32_t emulator::execute_rec(uint32_t a) {
    xip_fpo_set_ui(xil_a, a);
    xip_fpo_exc_t exc = xip_fpo_rec(xil_res, xil_a);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the calculation of the reciprocal of"+ std::to_string(a));
    }
    return xip_fpo_get_ui(xil_res);
}

uint32_t emulator::execute_fti(uint32_t a) {
    xip_fpo_set_ui(xil_a, a);
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

    return xip_fpo_get_ui(xil_res);
}

uint32_t emulator::execute_compare_gt(uint32_t a, uint32_t b) {
    xip_fpo_set_ui(xil_a, a);
    xip_fpo_set_ui(xil_b, b);

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
    xip_fpo_set_ui(xil_a, a);
    xip_fpo_set_ui(xil_b, b);

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
    xip_fpo_set_ui(xil_a, a);
    xip_fpo_set_ui(xil_b, b);

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
    xip_fpo_set_ui(xil_a, a);
    xip_fpo_set_ui(xil_b, b);

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
