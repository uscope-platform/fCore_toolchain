//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_INSTRUCTION_H
#define FCORE_HAS_INSTRUCTION_H

#include <iostream>
#include <iomanip>
#include <cstdint>

#define IMMEDIATE_INSTRUCTION 1
#define INDEPENDENT_INSTRUCTION 2
#define REGISTER_INSTRUCTION 3

typedef struct {
    uint16_t opcode : 4;
    uint16_t destination: 4;
    uint16_t immediate : 16;
    uint16_t rsvd : 8;
}imm_instruction_t;

typedef struct {
    uint16_t opcode : 4;
    uint16_t op_a : 4;
    uint16_t op_b : 4;
    uint16_t dest : 4;
}reg_instruction_t;

class instruction{

    public:
        instruction();
        instruction(uint8_t opcode,uint8_t dest, uint16_t immediate);
        explicit instruction(uint8_t opcode);
        instruction(uint8_t opcode, uint8_t op_a, uint8_t op_b, uint8_t dest);
        uint32_t emit();
        void print();
        bool is_terminal() { return true;};
    private:
        void print_immediate();
        void print_independent();
        void print_register();
        int type;
        imm_instruction_t immediate_instr;
        reg_instruction_t register_instr;
        uint32_t instr;
};


#endif //FCORE_HAS_INSTRUCTION_H
