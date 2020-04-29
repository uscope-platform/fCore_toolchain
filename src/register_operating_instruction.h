//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_REGISTER_OPERATING_INSTRUCTION_H
#define FCORE_HAS_REGISTER_OPERATING_INSTRUCTION_H

#include "instruction.h"
#include <cstdint>
#include <iostream>
#include <iomanip>

typedef struct {
    uint16_t opcode : 4;
    uint16_t op_a : 4;
    uint16_t op_b : 4;
    uint16_t dest : 4;
}reg_instruction_t;

class register_operating_instruction : public instruction {

public:
    register_operating_instruction(uint8_t opcode, uint8_t op_a, uint8_t op_b, uint8_t dest);
    void print() override;
    uint32_t emit() override;
private:
    uint32_t instr{};
    reg_instruction_t instr_content{};
};

#endif //FCORE_HAS_REGISTER_OPERATING_INSTRUCTION_H
