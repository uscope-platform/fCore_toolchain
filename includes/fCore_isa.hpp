// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_HAS_FCORE_ISA_HPP
#define FCORE_HAS_FCORE_ISA_HPP


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

#define OPCODE_WIDTH 5
#define REGISTER_ADDRESS_WIDTH 4

#include <map>

static const int fcore_register_address_width = 6;
static const int fcore_opcode_width = 5;
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
                std::make_pair ("rec", isa_register_instruction),
        };

static std::map <std::string, std::string>  fcore_pseudo_op {
                std::make_pair ("mov", "add"),
        };



#endif //FCORE_HAS_FCORE_ISA_HPP
