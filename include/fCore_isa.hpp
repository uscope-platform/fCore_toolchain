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

#define IMMEDIATE_INSTRUCTION 1
#define INDEPENDENT_INSTRUCTION 2
#define REGISTER_INSTRUCTION 3
#define PSEUDO_INSTRUCTION 4
#define BRANCH_INSTRUCTION 5
#define CONVERSION_INSTRUCTION 6
#define LOAD_CONSTANT_INSTRUCTION 7
#define INTERCALATED_CONSTANT 8
#include <map>

static std::map <std::string, uint32_t>  fcore_registers
        {
                std::make_pair ("r0", 0u),
                std::make_pair ("r1", 1u),
                std::make_pair ("r2", 2u),
                std::make_pair ("r3", 3u),
                std::make_pair ("r4", 4u),
                std::make_pair ("r5", 5u),
                std::make_pair ("r6", 6u),
                std::make_pair ("r7", 7u),
                std::make_pair ("r8", 8u),
                std::make_pair ("r9", 9u),
                std::make_pair ("r10", 10u),
                std::make_pair ("r11", 11u),
                std::make_pair ("r12", 12u),
                std::make_pair ("r13", 13u),
                std::make_pair ("r14", 14u),
                std::make_pair ("r15", 15u)

        };

static std::map <std::string, uint32_t>  fcore_opcodes
        {
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
                std::make_pair ("stop", 12u)
        };

static std::map <std::string, uint32_t>  fcore_op_types
        {
                std::make_pair ("nop", INDEPENDENT_INSTRUCTION),
                std::make_pair ("add", REGISTER_INSTRUCTION),
                std::make_pair ("sub", REGISTER_INSTRUCTION),
                std::make_pair ("mul", REGISTER_INSTRUCTION),
                std::make_pair ("itf", CONVERSION_INSTRUCTION),
                std::make_pair ("fti", CONVERSION_INSTRUCTION),
                std::make_pair ("ldc", IMMEDIATE_INSTRUCTION),
                std::make_pair ("ldr", IMMEDIATE_INSTRUCTION),
                std::make_pair ("bgt", BRANCH_INSTRUCTION),
                std::make_pair ("ble", BRANCH_INSTRUCTION),
                std::make_pair ("beq", BRANCH_INSTRUCTION),
                std::make_pair ("bne", BRANCH_INSTRUCTION),
                std::make_pair ("stop", INDEPENDENT_INSTRUCTION),
        };

static std::map <std::string, std::string>  fcore_pseudo_op
        {
                std::make_pair ("mov", "add"),
        };



#endif //FCORE_HAS_FCORE_ISA_HPP
