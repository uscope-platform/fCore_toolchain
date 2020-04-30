//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_IMMEDIATE_INSTRUCTION_H
#define FCORE_HAS_IMMEDIATE_INSTRUCTION_H

#include "instruction.h"
#include <cstdint>
#include <cmath>
#include <iostream>
#include <iomanip>

typedef struct {
    uint16_t opcode : 4;
    uint16_t destination: 4;
    uint16_t immediate : 16;
    uint16_t rsvd : 8;
}imm_instruction_t;


class immediate_instruction : public instruction{

    public:
        immediate_instruction(uint8_t opcode, uint8_t dest, uint16_t immediate);
        void print() override;
        uint32_t emit() override;
    private:
        uint32_t instr;
        imm_instruction_t instr_content{};
};


#endif //FCORE_HAS_IMMEDIATE_INSTRUCTION_H
