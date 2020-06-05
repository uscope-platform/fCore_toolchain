// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_FCORE_ISA_HPP
#define FCORE_HAS_FCORE_ISA_HPP

#define IMMEDIATE_INSTRUCTION 1
#define INDEPENDENT_INSTRUCTION 2
#define REGISTER_INSTRUCTION 3
#define PSEUDO_INSTRUCTION 4
#define GENERATED_INSTRUCTION 5
#define BRANCH_INSTRUCTION 6
#define ALU_IMMEDIATE_INSTRUCTION 7
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
                std::make_pair ("sar", 8),
                std::make_pair ("ldr", 9),
                std::make_pair ("bgt", 10),
                std::make_pair ("ble", 11),
                std::make_pair ("beq", 12),
                std::make_pair ("bne", 13),
                std::make_pair ("stop", 14),
                std::make_pair ("addi", 15),
                std::make_pair ("subi", 16),
                std::make_pair ("muli", 17),
                std::make_pair ("maci", 18),
                std::make_pair ("shli", 19),
                std::make_pair ("shri", 20),
                std::make_pair ("sari", 22),
        };

static std::map <std::string, int>  fcore_op_types
        {
                std::make_pair ("nop", INDEPENDENT_INSTRUCTION),
                std::make_pair ("add", REGISTER_INSTRUCTION),
                std::make_pair ("sub", REGISTER_INSTRUCTION),
                std::make_pair ("mul", REGISTER_INSTRUCTION),
                std::make_pair ("mac", REGISTER_INSTRUCTION),
                std::make_pair ("shl", REGISTER_INSTRUCTION),
                std::make_pair ("shr", REGISTER_INSTRUCTION),
                std::make_pair ("sar", REGISTER_INSTRUCTION),
                std::make_pair ("ldr", IMMEDIATE_INSTRUCTION),
                std::make_pair ("bgt", BRANCH_INSTRUCTION),
                std::make_pair ("ble", BRANCH_INSTRUCTION),
                std::make_pair ("beq", BRANCH_INSTRUCTION),
                std::make_pair ("bne", BRANCH_INSTRUCTION),
                std::make_pair ("stop", INDEPENDENT_INSTRUCTION),
                std::make_pair ("addi", ALU_IMMEDIATE_INSTRUCTION),
                std::make_pair ("subi", ALU_IMMEDIATE_INSTRUCTION),
                std::make_pair ("muli", ALU_IMMEDIATE_INSTRUCTION),
                std::make_pair ("maci", ALU_IMMEDIATE_INSTRUCTION),
                std::make_pair ("shli", ALU_IMMEDIATE_INSTRUCTION),
                std::make_pair ("shri", ALU_IMMEDIATE_INSTRUCTION),
                std::make_pair ("sari", ALU_IMMEDIATE_INSTRUCTION),

        };

static std::map <std::string, std::string>  fcore_pseudo_op
        {
                std::make_pair ("mov", "add"),

        };



#endif //FCORE_HAS_FCORE_ISA_HPP
