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

#ifndef FCORE_TOOLCHAIN_FCORE_ISA_HPP
#define FCORE_TOOLCHAIN_FCORE_ISA_HPP

#include "data_structures/high_level_ast/ast_expression.hpp"

#include <map>

namespace fcore{

    typedef enum {
        isa_independent_instruction = 2,
        isa_register_instruction = 3,
        isa_pseudo_instruction = 4,
        isa_conversion_instruction = 6,
        isa_load_constant_instruction = 7,
        isa_intercalated_constant= 8,
        isa_ternary_instruction = 9,
    }isa_instruction_type;

    constexpr std::string_view isa_instr_type_to_string(isa_instruction_type t){
        switch (t) {
            case isa_register_instruction: return "isa_register_instruction";
            case isa_independent_instruction: return "isa_independent_instruction";
            case isa_pseudo_instruction: return "isa_pseudo_instruction";
            case isa_conversion_instruction: return "isa_conversion_instruction";
            case isa_load_constant_instruction: return "isa_load_constant_instruction";
            case isa_intercalated_constant: return "isa_intercalated_constant";
            case isa_ternary_instruction: return  "isa_ternary_instruction";
            default: return "unknown_isa_instr_type";
        }
    }

    constexpr int fcore_register_address_width = 6;
    constexpr int fcore_opcode_width = 5;

    constexpr int fcore_n_common_io_registers = 32;
    constexpr  int fcore_max_binary_size = 4096;
    constexpr int n_operands = 3;

    static uint32_t get_opcode(uint32_t instr) {
        return instr & (1<<fcore_opcode_width)-1;
    }

    static uint32_t operand_mask(uint8_t operand_position){
        return (
                ((1<<(fcore_opcode_width +     operand_position*fcore_register_address_width))-1) -
                ((1<<(fcore_opcode_width + (operand_position-1)*fcore_register_address_width))-1)
        );
    }
    static uint32_t flag_mask(uint8_t flag_n){
        return 1<<(fcore_opcode_width +n_operands*fcore_register_address_width + flag_n-1);
    }

    static std::array<uint32_t,3> get_operands(uint32_t instr){
        std::array<uint32_t,3> result = {};
        result[0] = (instr & operand_mask(1)) >> fcore_opcode_width;
        result[1] = (instr & operand_mask(2)) >> (fcore_opcode_width + fcore_register_address_width);
        result[2] = (instr & operand_mask(3)) >> (fcore_opcode_width + 2*fcore_register_address_width);
        return result;

    }

    static std::array<bool, 3> get_common_io_flags(uint32_t instr){
        std::array<bool,3> result = {};
        result[0] = (instr & flag_mask(1)) >> (fcore_opcode_width + 3*fcore_register_address_width);
        result[1] = (instr & flag_mask(2)) >> (fcore_opcode_width + 3*fcore_register_address_width+1);
        result[2] = (instr & flag_mask(3)) >> (fcore_opcode_width + 3*fcore_register_address_width+2);
        return result;
    }
    typedef enum {
        opcode_nop = 0,
        opcode_add = 1,
        opcode_sub = 2,
        opcode_mul = 3,
        opcode_itf = 4,
        opcode_fti = 5,
        opcode_ldc = 6,
        opcode_bgt = 8,
        opcode_ble = 9,
        opcode_beq = 10,
        opcode_bne = 11,
        opcode_stop = 12,
        opcode_and = 13,
        opcode_or = 14,
        opcode_not = 15,
        opcode_satp = 16,
        opcode_satn = 17,
        opcode_rec = 18,
        opcode_popcnt = 19,
        opcode_abs = 20,
        opcode_efi = 21,
        opcode_bset = 22,
        opcode_bsel = 25,
        opcode_xor = 26,
        opcode_csel =27,
        opcode_mov =100,
        opcode_neg=101
    }opcode_table_t;


     static std::map<opcode_table_t, uint8_t> fcore_execution_latencies {
         {opcode_nop, 0},
         {opcode_add, 6},
         {opcode_sub, 6},
         {opcode_mul, 6},
         {opcode_itf, 4},
         {opcode_fti, 4},
         {opcode_ldc, 1},
         {opcode_bgt, 1},
         {opcode_ble, 1},
         {opcode_beq, 1},
         {opcode_bne, 1},
         {opcode_stop, 0},
         {opcode_and, 2},
         {opcode_or, 2},
         {opcode_not, 2},
        {opcode_satp, 3},
        {opcode_satn, 3},
        {opcode_rec, 9},
        {opcode_popcnt, 3},
        {opcode_abs, 2},
        {opcode_efi, 0},
        {opcode_bset, 2},
        {opcode_bsel, 2},
        {opcode_xor, 2},
        {opcode_csel, 2}
    };


    static std::map <opcode_table_t, uint32_t>  fcore_opcodes {
            std::make_pair (opcode_nop, 0u),
            std::make_pair (opcode_add, 1u),
            std::make_pair (opcode_sub, 2u),
            std::make_pair (opcode_mul, 3u),
            std::make_pair (opcode_itf, 4u),
            std::make_pair (opcode_fti, 5u),
            std::make_pair (opcode_ldc, 6u),
            std::make_pair (opcode_bgt, 8u),
            std::make_pair (opcode_ble, 9u),
            std::make_pair (opcode_beq, 10u),
            std::make_pair (opcode_bne, 11u),
            std::make_pair (opcode_stop, 12u),
            std::make_pair (opcode_and, 13u),
            std::make_pair (opcode_or, 14u),
            std::make_pair (opcode_not, 15u),
            std::make_pair (opcode_satp, 16u),
            std::make_pair (opcode_satn, 17u),
            std::make_pair (opcode_rec, 18u),
            std::make_pair (opcode_popcnt, 19u),
            std::make_pair (opcode_abs, 20u),
            std::make_pair (opcode_efi, 21u),
            std::make_pair(opcode_bset, 22u),
            std::make_pair(opcode_bsel, 25u),
            std::make_pair(opcode_xor, 26u),
            std::make_pair(opcode_csel, 27u),
    };


    static std::map <uint32_t, opcode_table_t>  fcore_opcodes_reverse {
        std::make_pair ( 0u, opcode_nop),
        std::make_pair (1u,opcode_add),
        std::make_pair (2u, opcode_sub),
        std::make_pair (3u, opcode_mul),
        std::make_pair (4u, opcode_itf),
        std::make_pair (5u, opcode_fti),
        std::make_pair (6u, opcode_ldc),
        std::make_pair (8u, opcode_bgt),
        std::make_pair (9u, opcode_ble),
        std::make_pair (10u, opcode_beq),
        std::make_pair (11u, opcode_bne),
        std::make_pair (12u, opcode_stop),
        std::make_pair (13u, opcode_and),
        std::make_pair (14u,opcode_or),
        std::make_pair (15u, opcode_not),
        std::make_pair (16u,opcode_satp),
        std::make_pair (17u, opcode_satn),
        std::make_pair (18u, opcode_rec),
        std::make_pair (19u, opcode_popcnt),
        std::make_pair (20u, opcode_abs),
        std::make_pair (21u, opcode_efi),
        std::make_pair(22u, opcode_bset),
        std::make_pair(25u, opcode_bsel),
        std::make_pair(26u,opcode_xor),
        std::make_pair(27u, opcode_csel),
};


    static std::map <uint32_t, std::string>  fcore_string_map {
            std::make_pair (fcore_opcodes[opcode_nop], "nop"),
            std::make_pair (fcore_opcodes[opcode_add], "add"),
            std::make_pair (fcore_opcodes[opcode_sub], "sub"),
            std::make_pair (fcore_opcodes[opcode_mul], "mul"),
            std::make_pair (fcore_opcodes[opcode_itf], "itf"),
            std::make_pair (fcore_opcodes[opcode_fti], "fti"),
            std::make_pair (fcore_opcodes[opcode_ldc], "ldc"),
            std::make_pair (fcore_opcodes[opcode_bgt], "bgt"),
            std::make_pair (fcore_opcodes[opcode_ble], "ble"),
            std::make_pair (fcore_opcodes[opcode_beq], "beq"),
            std::make_pair (fcore_opcodes[opcode_bne], "bne"),
            std::make_pair (fcore_opcodes[opcode_stop], "stop"),
            std::make_pair (fcore_opcodes[opcode_and], "and"),
            std::make_pair (fcore_opcodes[opcode_or], "or"),
            std::make_pair (fcore_opcodes[opcode_not], "not"),
            std::make_pair (fcore_opcodes[opcode_satp], "satp"),
            std::make_pair (fcore_opcodes[opcode_satn], "satn"),
            std::make_pair (fcore_opcodes[opcode_rec], "rec"),
            std::make_pair (fcore_opcodes[opcode_abs], "abs"),
            std::make_pair (fcore_opcodes[opcode_efi], "efi"),
            std::make_pair(fcore_opcodes[opcode_popcnt], "popcnt"),
            std::make_pair(fcore_opcodes[opcode_bset], "bset"),
            std::make_pair(fcore_opcodes[opcode_bsel], "bsel"),
            std::make_pair(fcore_opcodes[opcode_xor], "xor"),
            std::make_pair(fcore_opcodes[opcode_csel], "csel")
    };

    static std::map <std::string, opcode_table_t>  fcore_opcode_string_reverse {
        std::make_pair ("nop", opcode_nop),
        std::make_pair ("add", opcode_add),
        std::make_pair ("sub", opcode_sub),
        std::make_pair ("mul", opcode_mul),
        std::make_pair ("itf", opcode_itf),
        std::make_pair ("fti", opcode_fti),
        std::make_pair ("ldc", opcode_ldc),
        std::make_pair ("bgt", opcode_bgt),
        std::make_pair ("ble", opcode_ble),
        std::make_pair ("beq", opcode_beq),
        std::make_pair ("bne", opcode_bne),
        std::make_pair ("stop", opcode_stop),
        std::make_pair ("and", opcode_and),
        std::make_pair ("or", opcode_or),
        std::make_pair ("not", opcode_not),
        std::make_pair ("satp", opcode_satp),
        std::make_pair ("satn", opcode_satn),
        std::make_pair ("rec", opcode_rec),
        std::make_pair ("abs", opcode_abs),
        std::make_pair ("efi", opcode_efi),
        std::make_pair("popcnt", opcode_popcnt),
        std::make_pair("bset", opcode_bset),
        std::make_pair("bsel", opcode_bsel),
        std::make_pair("xor", opcode_xor),
        std::make_pair("mov", opcode_mov),
        std::make_pair("neg", opcode_neg),
        std::make_pair("csel", opcode_csel)
};

    static std::map <opcode_table_t, isa_instruction_type>  fcore_op_types {
            std::make_pair (opcode_nop, isa_independent_instruction),
            std::make_pair (opcode_add, isa_register_instruction),
            std::make_pair (opcode_sub, isa_register_instruction),
            std::make_pair (opcode_mul, isa_register_instruction),
            std::make_pair (opcode_itf, isa_conversion_instruction),
            std::make_pair (opcode_fti, isa_conversion_instruction),
            std::make_pair (opcode_ldc, isa_load_constant_instruction),
            std::make_pair (opcode_bgt, isa_register_instruction),
            std::make_pair (opcode_ble, isa_register_instruction),
            std::make_pair (opcode_beq, isa_register_instruction),
            std::make_pair (opcode_bne, isa_register_instruction),
            std::make_pair (opcode_stop, isa_independent_instruction),
            std::make_pair (opcode_and, isa_register_instruction),
            std::make_pair (opcode_or, isa_register_instruction),
            std::make_pair(opcode_xor, isa_register_instruction),
            std::make_pair (opcode_not, isa_conversion_instruction),
            std::make_pair (opcode_satp, isa_register_instruction),
            std::make_pair (opcode_satn, isa_register_instruction),
            std::make_pair (opcode_rec, isa_conversion_instruction),
            std::make_pair (opcode_abs, isa_conversion_instruction),
            std::make_pair (opcode_efi, isa_register_instruction),
            std::make_pair(opcode_popcnt, isa_conversion_instruction),
            std::make_pair(opcode_bset,isa_register_instruction),
            std::make_pair(opcode_bsel,isa_register_instruction),
            std::make_pair(opcode_mov, isa_pseudo_instruction),
            std::make_pair(opcode_neg, isa_pseudo_instruction),
            std::make_pair(opcode_csel,isa_ternary_instruction)
    };


    static std::map fcore_implemented_operations {
            std::make_pair(ast_expression::ADD, true),
            std::make_pair(ast_expression::SUB, true),
            std::make_pair(ast_expression::MULT, true),
            std::make_pair(ast_expression::DIV, false),
            std::make_pair(ast_expression::PRE_INCR, true),
            std::make_pair(ast_expression::POST_INCR, true),
            std::make_pair(ast_expression::PRE_DECR, true),
            std::make_pair(ast_expression::POST_DECR, true),
            std::make_pair(ast_expression::MODULO, false),
            std::make_pair(ast_expression::AND_L, false),
            std::make_pair(ast_expression::AND_B, true),
            std::make_pair(ast_expression::OR_L, false),
            std::make_pair(ast_expression::OR_B, true),
            std::make_pair(ast_expression::NOT_L, false),
            std::make_pair(ast_expression::NOT_B, true),
            std::make_pair(ast_expression::XOR_B, true),
            std::make_pair(ast_expression::LSH, false),
            std::make_pair(ast_expression::RSH, false),
            std::make_pair(ast_expression::EQ, true),
            std::make_pair(ast_expression::NEQ, true),
            std::make_pair(ast_expression::NEG, true),
            std::make_pair(ast_expression::LT, true),
            std::make_pair(ast_expression::GT, true),
            std::make_pair(ast_expression::LTE, true),
            std::make_pair(ast_expression::GTE, true),
            std::make_pair(ast_expression::RECIPROCAL, true),
            std::make_pair(ast_expression::ASSIGN, false),
            std::make_pair(ast_expression::CALL, false),
            std::make_pair(ast_expression::FTI, true),
            std::make_pair(ast_expression::ITF, true),
            std::make_pair(ast_expression::SATP, true),
            std::make_pair(ast_expression::SATN, true),
            std::make_pair(ast_expression::POPCNT, true),
            std::make_pair(ast_expression::EFI, true),
            std::make_pair(ast_expression::ABS, true),
            std::make_pair(ast_expression::BSET, true),
            std::make_pair(ast_expression::BSEL, true),
            std::make_pair(ast_expression::NOP, true),
            std::make_pair(ast_expression::CSEL, true)
    };

    static std::map <opcode_table_t, opcode_table_t>  fcore_pseudo_op {
            std::make_pair(opcode_mov, opcode_or),
            std::make_pair(opcode_neg, opcode_sub)
    };
}



#endif //FCORE_TOOLCHAIN_FCORE_ISA_HPP
