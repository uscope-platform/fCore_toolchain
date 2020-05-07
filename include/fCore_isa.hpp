// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_FCORE_HPP
#define FCORE_HAS_FCORE_HPP

#define FCORE_IMMEDIATE_INSTRUCTION 1
#define FCORE_INDEPENDENT_INSTRUCTION 2
#define FCORE_REGISTER_INSTRUCTION 3

#include <map>

static std::map <std::string, int>  fcore_registers
        {
                std::make_pair ("r1", 1),
                std::make_pair ("r2", 2),
                std::make_pair ("r3", 3),
                std::make_pair ("r4", 4),
                std::make_pair ("r5", 5),
                std::make_pair ("r6", 6),
                std::make_pair ("r7", 7),
                std::make_pair ("r8", 8),
                std::make_pair ("r9", 9),
                std::make_pair ("r10", 10),
                std::make_pair ("r11", 11),
                std::make_pair ("r12", 12),
                std::make_pair ("r13", 13),
                std::make_pair ("r14", 14),
                std::make_pair ("r15", 15)

        };

static std::map <std::string, int>  fcore_opcodes
        {
                std::make_pair ("nop", 0),
                std::make_pair ("add", 1),
                std::make_pair ("sub", 2),
                std::make_pair ("mul", 3),
                std::make_pair ("mac", 4),
                std::make_pair ("shl", 5),
                std::make_pair ("shr", 6),
                std::make_pair ("sal", 7),
                std::make_pair ("sar", 8),
                std::make_pair ("ldr", 9),
                std::make_pair ("stop", 12)

        };

static std::map <std::string, int>  fcore_op_types
        {
                std::make_pair ("nop", FCORE_INDEPENDENT_INSTRUCTION),
                std::make_pair ("add", FCORE_REGISTER_INSTRUCTION),
                std::make_pair ("sub", FCORE_REGISTER_INSTRUCTION),
                std::make_pair ("mul", FCORE_REGISTER_INSTRUCTION),
                std::make_pair ("mac", FCORE_REGISTER_INSTRUCTION),
                std::make_pair ("shl", FCORE_REGISTER_INSTRUCTION),
                std::make_pair ("shr", FCORE_IMMEDIATE_INSTRUCTION),
                std::make_pair ("sal", FCORE_IMMEDIATE_INSTRUCTION),
                std::make_pair ("sar", FCORE_IMMEDIATE_INSTRUCTION),
                std::make_pair ("ldr", FCORE_IMMEDIATE_INSTRUCTION),
                std::make_pair ("stop", FCORE_INDEPENDENT_INSTRUCTION)

        };

static std::map <std::string, std::string>  fcore_pseudo_op
        {
                std::make_pair ("mov", "add"),

        };



#endif //FCORE_HAS_FCORE_HPP
