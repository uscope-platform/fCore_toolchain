//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_INSTRUCTION_H
#define FCORE_HAS_INSTRUCTION_H

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <memory>
#include "../../include/fCore_isa.hpp"
#include "variable.hpp"

typedef struct {
    std::string opcode;
    std::vector<std::shared_ptr<variable>> arguments;
} instruction_t;


class instruction{

    public:
        instruction();
        instruction(int inst_type,std::string opcode, std::vector<std::shared_ptr<variable>> arguments);

        [[nodiscard]] uint32_t emit() const;
        [[nodiscard]] int instruction_count() const;
        void print();
        [[nodiscard]] bool is_pseudo() const { return type == PSEUDO_INSTRUCTION;};
        [[nodiscard]] const instruction_t &getStringInstr() const;
        void setStringInstr(const instruction_t &stringInstr);

private:
        [[nodiscard]] uint32_t emit_branch() const;
        [[nodiscard]] uint32_t emit_immediate() const;
        [[nodiscard]] uint32_t emit_independent() const;
        [[nodiscard]] uint32_t emit_register() const;
        [[nodiscard]] uint32_t emit_alu_immediate() const;
        void print_immediate() const;
        void print_independent() const;
        void print_register() const;
        void print_branch() const;
        void print_alu_immediate() const;

        int type;
        instruction_t string_instr;
        uint32_t instr;


};


#endif //FCORE_HAS_INSTRUCTION_H
