// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_LL_REGISTER_INSTR_NODE_H
#define FCORE_TOOLCHAIN_LL_REGISTER_INSTR_NODE_H

#include <utility>
#include <iostream>

#include "data_structures/common/variable.hpp"
#include "fCore_isa.hpp"

namespace fcore{

    class register_instruction {
    public:
        register_instruction(opcode_table_t op, std::shared_ptr<variable> op_a, std::shared_ptr<variable> op_b, std::shared_ptr<variable> dest);
        std::vector<uint32_t> emit() const;
        std::string disassemble() const;
        void print() const;
        register_instruction(const register_instruction& other) = default;
        register_instruction(register_instruction&& other) noexcept = default;
        register_instruction& operator=(const register_instruction& other) = default;
        register_instruction& operator=(register_instruction&& other) noexcept = default;
        std::string to_string() const;
        int instruction_count() const;

        friend bool operator==(const register_instruction& lhs, const register_instruction& rhs){
            bool retval = true;

            retval &= *lhs.operand_a == *rhs.operand_a;
            retval &= *lhs.operand_b == *rhs.operand_b;
            retval &= *lhs.destination == *rhs.destination;
            retval &= rhs.opcode == lhs.opcode;
            return retval;
        };

        std::shared_ptr<variable> get_operand_a() const {return operand_a;};
        std::shared_ptr<variable> get_operand_b()const {return operand_b;};
        std::shared_ptr<variable> get_destination()const {return destination;};
        void set_destination(std::shared_ptr<variable>d) {destination = std::move(d);};
        std::vector<std::shared_ptr<variable>> get_arguments() const {return {operand_a, operand_b, destination};};
        void set_arguments(const std::vector<std::shared_ptr<variable>> &a);

        opcode_table_t get_opcode()const {return opcode;};

    private:
        std::shared_ptr<variable> operand_a;
        std::shared_ptr<variable> operand_b;
        std::shared_ptr<variable> destination;

        opcode_table_t opcode;
    };
}


#endif //FCORE_TOOLCHAIN_LL_REGISTER_INSTR_NODE_H
