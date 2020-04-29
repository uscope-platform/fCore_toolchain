//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_INDEPENDENT_INSTRUCTION_HPP
#define FCORE_HAS_INDEPENDENT_INSTRUCTION_HPP

#include "instruction.h"
#include <cstdint>
#include <cmath>
#include <iostream>
#include <iomanip>

class independent_instruction: public instruction{

public:
    explicit independent_instruction(uint8_t opcode);
    void print() override;
    uint32_t emit() override;
private:
    uint32_t instr{};
};


#endif //FCORE_HAS_INDEPENDENT_INSTRUCTION_HPP