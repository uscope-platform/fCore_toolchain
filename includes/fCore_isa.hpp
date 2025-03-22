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
        return ((1<<(fcore_opcode_width +n_operands*fcore_register_address_width)) + (flag_n-1));
    }

    static std::array<uint32_t,3> get_operands(uint32_t instr){
        std::array<uint32_t,3> result = {};
        result[0] = (instr & operand_mask(1)) >> fcore_opcode_width;
        result[1] = (instr & operand_mask(2)) >> (fcore_opcode_width + fcore_register_address_width);
        result[2] = (instr & operand_mask(3)) >> (fcore_opcode_width + 2*fcore_register_address_width);
        return result;

    }

    static std::array<bool, 2> get_common_io_flags(uint32_t instr){
        std::array<bool,2> result = {};
        result[0] = (instr & flag_mask(1)) >> (fcore_opcode_width + 3*fcore_register_address_width);
        result[1] = (instr & flag_mask(2)) >> (fcore_opcode_width + 3*fcore_register_address_width+1);
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
    }opcode_table_t;


    static std::map <std::string, uint32_t>  fcore_opcodes {
            std::make_pair ("nop", 0u),
            std::make_pair ("add", 1u),
            std::make_pair ("sub", 2u),
            std::make_pair ("mul", 3u),
            std::make_pair ("itf", 4u),
            std::make_pair ("fti", 5u),
            std::make_pair ("ldc", 6u),
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
            std::make_pair ("popcnt", 19u),
            std::make_pair ("abs", 20u),
            std::make_pair ("efi", 21u),
            std::make_pair("bset", 22u),
            std::make_pair("bsel", 25u),
            std::make_pair("xor", 26u),
            std::make_pair("csel", 27u),


    };

    static std::map <uint32_t, std::string>  fcore_opcodes_reverse {
            std::make_pair (fcore_opcodes["nop"], "nop"),
            std::make_pair (fcore_opcodes["add"], "add"),
            std::make_pair (fcore_opcodes["sub"], "sub"),
            std::make_pair (fcore_opcodes["mul"], "mul"),
            std::make_pair (fcore_opcodes["itf"], "itf"),
            std::make_pair (fcore_opcodes["fti"], "fti"),
            std::make_pair (fcore_opcodes["ldc"], "ldc"),
            std::make_pair (fcore_opcodes["bgt"], "bgt"),
            std::make_pair (fcore_opcodes["ble"], "ble"),
            std::make_pair (fcore_opcodes["beq"], "beq"),
            std::make_pair (fcore_opcodes["bne"], "bne"),
            std::make_pair (fcore_opcodes["stop"], "stop"),
            std::make_pair (fcore_opcodes["and"], "and"),
            std::make_pair (fcore_opcodes["or"], "or"),
            std::make_pair (fcore_opcodes["not"], "not"),
            std::make_pair (fcore_opcodes["satp"], "satp"),
            std::make_pair (fcore_opcodes["satn"], "satn"),
            std::make_pair (fcore_opcodes["rec"], "rec"),
            std::make_pair (fcore_opcodes["abs"], "abs"),
            std::make_pair (fcore_opcodes["efi"], "efi"),
            std::make_pair(fcore_opcodes["popcnt"], "popcnt"),
            std::make_pair(fcore_opcodes["bset"], "bset"),
            std::make_pair(fcore_opcodes["bsel"], "bsel"),
            std::make_pair(fcore_opcodes["xor"], "xor"),
            std::make_pair(fcore_opcodes["csel"], "csel")
    };

    static std::map <std::string, isa_instruction_type>  fcore_op_types {
            std::make_pair ("nop", isa_independent_instruction),
            std::make_pair ("add", isa_register_instruction),
            std::make_pair ("sub", isa_register_instruction),
            std::make_pair ("mul", isa_register_instruction),
            std::make_pair ("itf", isa_conversion_instruction),
            std::make_pair ("fti", isa_conversion_instruction),
            std::make_pair ("ldc", isa_load_constant_instruction),
            std::make_pair ("bgt", isa_register_instruction),
            std::make_pair ("ble", isa_register_instruction),
            std::make_pair ("beq", isa_register_instruction),
            std::make_pair ("bne", isa_register_instruction),
            std::make_pair ("stop", isa_independent_instruction),
            std::make_pair ("and", isa_register_instruction),
            std::make_pair ("or", isa_register_instruction),
            std::make_pair("xor", isa_register_instruction),
            std::make_pair ("not", isa_conversion_instruction),
            std::make_pair ("satp", isa_register_instruction),
            std::make_pair ("satn", isa_register_instruction),
            std::make_pair ("rec", isa_conversion_instruction),
            std::make_pair ("abs", isa_conversion_instruction),
            std::make_pair ("efi", isa_register_instruction),
            std::make_pair("popcnt", isa_conversion_instruction),
            std::make_pair("bset",isa_register_instruction),
            std::make_pair("bsel",isa_register_instruction),
            std::make_pair("mov", isa_pseudo_instruction),
            std::make_pair("neg", isa_pseudo_instruction),
            std::make_pair("csel",isa_ternary_instruction)
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

    static std::map <std::string, std::string>  fcore_pseudo_op {
            std::make_pair("mov", "or"),
            std::make_pair("neg", "sub")
    };
}



#endif //FCORE_TOOLCHAIN_FCORE_ISA_HPP
