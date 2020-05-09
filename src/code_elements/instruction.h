//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_INSTRUCTION_H
#define FCORE_HAS_INSTRUCTION_H

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include "../../include/fCore_isa.hpp"



typedef struct {
    uint16_t opcode;
    uint16_t destination;
    uint16_t immediate;
    uint16_t rsvd;
}imm_instruction_t;

typedef struct {
    std::string opcode;
    uint16_t arg_1;
    uint16_t arg_2;
    uint16_t arg_3;
}pseudo_instruction_t;

typedef struct {
    uint16_t opcode;
    uint16_t op_a;
    uint16_t op_b;
    uint16_t dest;
}reg_instruction_t;

typedef struct {
    uint16_t opcode;
    uint16_t op_a;
    uint16_t op_b;
    uint16_t offset;
}branch_instruction_t;

class instruction{

    public:
        instruction();
        instruction(int inst_type, std::vector<uint16_t> opcode);
        instruction(int inst_type, uint32_t complete_instr);
        instruction(int inst_type, std::string opcode, std::vector<uint16_t> operands);

        [[nodiscard]] uint32_t emit() const;
        void print();
        void specialize_pseudo();
        bool is_pseudo() { return type == PSEUDO_INSTRUCTION;};

    pseudo_instruction_t pseudo_instr;
    private:
        void print_immediate() const;
        void print_independent() const;
        void print_register() const;
        void print_branch() const;

        void form_indep_inst(uint8_t opcode);
        void form_reg_inst(uint8_t opcode, uint8_t op_a, uint8_t op_b, uint8_t dest);
        void form_imm_inst(uint8_t opcode,uint8_t dest, uint16_t immediate);
        void form_branch_inst(uint8_t opcode, uint8_t op_a, uint8_t op_b, uint16_t offset);

        int type;
        imm_instruction_t immediate_instr;
        reg_instruction_t register_instr;
        branch_instruction_t branch_instr;

        uint32_t instr;

    void print_generated() const;
};


#endif //FCORE_HAS_INSTRUCTION_H
