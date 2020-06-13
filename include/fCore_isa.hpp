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

static std::map <std::string, uint32_t>  fcore_registers
        {
                std::make_pair ("r1", 0u),
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
                std::make_pair ("mac", 4u),
                std::make_pair ("shl", 5u),
                std::make_pair ("shr", 6u),
                std::make_pair ("sar", 8u),
                std::make_pair ("ldr", 9u),
                std::make_pair ("bgt", 10u),
                std::make_pair ("ble", 11u),
                std::make_pair ("beq", 12u),
                std::make_pair ("bne", 13u),
                std::make_pair ("stop", 14u),
                std::make_pair ("addi", 15u),
                std::make_pair ("subi", 16u),
                std::make_pair ("muli", 17u),
                std::make_pair ("maci", 18u),
                std::make_pair ("shli", 19u),
                std::make_pair ("shri", 20u),
                std::make_pair ("sari", 22u),
        };

static std::map <std::string, uint32_t>  fcore_op_types
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
