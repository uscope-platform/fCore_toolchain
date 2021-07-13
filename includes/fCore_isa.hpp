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

#ifndef FCORE_TOOLCHAIN_FCORE_ISA_HPP
#define FCORE_TOOLCHAIN_FCORE_ISA_HPP

#include "ast/high_level/hl_expression_node.hpp"
#include <map>


typedef enum {
    isa_immediate_instruction = 1,
    isa_independent_instruction = 2,
    isa_register_instruction = 3,
    isa_pseudo_instruction = 4,
    isa_branch_instruction = 5,
    isa_conversion_instruction = 6,
    isa_load_constant_instruction = 7,
    isa_intercalated_constant= 8
}isa_instruction_type;

static const int fcore_register_address_width = 6;
static const int fcore_opcode_width = 6;


static std::map <std::string, uint32_t>  fcore_opcodes {
                std::make_pair ("nop", 0u),
                std::make_pair ("add", 1u),
                std::make_pair ("sub", 2u),
                std::make_pair ("mul", 3u),
                std::make_pair ("itf", 4u),
                std::make_pair ("fti", 5u),
                std::make_pair ("ldc", 6u),
                std::make_pair ("ldr", 7u),
                std::make_pair ("bgt", 8u),
                std::make_pair ("ble", 9u),
                std::make_pair ("beq", 10u),
                std::make_pair ("bne", 11u),
                std::make_pair ("stop", 12u),
                std::make_pair ("and", 13u),
                std::make_pair ("or", 14u),
                std::make_pair ("not", 15u),
                std::make_pair ("satp", 16u),
                std::make_pair ("satn", 17u),
                std::make_pair ("rec", 18u),
        };

static std::map <std::string, isa_instruction_type>  fcore_op_types {
                std::make_pair ("nop", isa_independent_instruction),
                std::make_pair ("add", isa_register_instruction),
                std::make_pair ("sub", isa_register_instruction),
                std::make_pair ("mul", isa_register_instruction),
                std::make_pair ("itf", isa_conversion_instruction),
                std::make_pair ("fti", isa_conversion_instruction),
                std::make_pair ("ldc", isa_immediate_instruction),
                std::make_pair ("ldr", isa_immediate_instruction),
                std::make_pair ("bgt", isa_register_instruction),
                std::make_pair ("ble", isa_register_instruction),
                std::make_pair ("beq", isa_register_instruction),
                std::make_pair ("bne", isa_register_instruction),
                std::make_pair ("stop", isa_independent_instruction),
                std::make_pair ("and", isa_register_instruction),
                std::make_pair ("or", isa_register_instruction),
                std::make_pair ("not", isa_conversion_instruction),
                std::make_pair ("satp", isa_register_instruction),
                std::make_pair ("satn", isa_register_instruction),
                std::make_pair ("rec", isa_conversion_instruction),
        };


static std::map <expression_type_t, bool> fcore_implemented_operations {
    std::make_pair(expr_add, true),
    std::make_pair(expr_sub, true),
    std::make_pair(expr_mult, true),
    std::make_pair(expr_div, false),
    std::make_pair(expr_incr_pre, true),
    std::make_pair(expr_incr_post, true),
    std::make_pair(expr_decr_pre, true),
    std::make_pair(expr_decr_post, true),
    std::make_pair(expr_modulo, false),
    std::make_pair(expr_and_l, false),
    std::make_pair(expr_and_b, true),
    std::make_pair(expr_or_l, false),
    std::make_pair(expr_or_b, true),
    std::make_pair(expr_not_l, false),
    std::make_pair(expr_not_b, true),
    std::make_pair(expr_xor_b, false),
    std::make_pair(expr_lsh, false),
    std::make_pair(expr_rsh, false),
    std::make_pair(expr_eq, true),
    std::make_pair(expr_neq, true),
    std::make_pair(expr_neg, true),
    std::make_pair(expr_lt, true),
    std::make_pair(expr_gt, true),
    std::make_pair(expr_lte, true),
    std::make_pair(expr_gte, true),
    std::make_pair(expr_reciprocal, true),
    std::make_pair(expr_assign, false),
    std::make_pair(expr_call, false),
    std::make_pair(expr_fti, true),
    std::make_pair(expr_itf, true),
    std::make_pair(expr_satp, true),
    std::make_pair(expr_satn, true),
};

static std::map <std::string, std::string>  fcore_pseudo_op {
                std::make_pair ("mov", "add"),
        };



#endif //FCORE_TOOLCHAIN_FCORE_ISA_HPP
