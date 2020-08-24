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

#ifndef FCORE_HAS_INSTRUCTION_H
#define FCORE_HAS_INSTRUCTION_H

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <memory>
#include <bitset>
#include <cstring>
#include "fcore_has/fCore_isa.hpp"
#include "variable.hpp"

typedef struct {
    std::string opcode;
    std::vector<std::shared_ptr<variable>> arguments;
    float intercalated_constant;
} instruction_t;


class instruction{

    public:
        instruction() = default;
        instruction(int inst_type,std::string opcode, std::vector<std::shared_ptr<variable>> arguments);
        instruction(int inst_type, float constant);
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
        [[nodiscard]] uint32_t emit_conversion() const;
        [[nodiscard]] uint32_t emit_load_const() const;
        [[nodiscard]] uint32_t emit_intercalated_const() const;
        void print_immediate() const;
        void print_independent() const;
        void print_register() const;
        void print_branch() const;
        void print_conversion() const;
        void print_load_const() const;
        int type;
        instruction_t string_instr;


};


#endif //FCORE_HAS_INSTRUCTION_H
