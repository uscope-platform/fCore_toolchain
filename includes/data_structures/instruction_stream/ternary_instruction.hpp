//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_TERNARY_INSTRUCTION_HPP
#define FCORE_TOOLCHAIN_TERNARY_INSTRUCTION_HPP

#include <utility>
#include <iostream>

#include "data_structures/common/variable.hpp"
#include "fCore_isa.hpp"


namespace fcore{
    class ternary_instruction {
    public:
        ternary_instruction(opcode_table_t op, std::shared_ptr<variable> op_a, std::shared_ptr<variable> op_b, std::shared_ptr<variable> op_c, std::shared_ptr<variable> dest);
        std::vector<uint32_t> emit() const;
        std::string disassemble() const;
        ternary_instruction(const ternary_instruction& other) = default;
        ternary_instruction(ternary_instruction&& other) noexcept = default;
        ternary_instruction& operator=(const ternary_instruction& other) = default;
        ternary_instruction& operator=(ternary_instruction&& other) noexcept = default;
        void print() const;
        std::string to_string() const;
        int instruction_count() const;

        friend bool operator==(const ternary_instruction& lhs, const ternary_instruction& rhs){
            bool retval = true;

            retval &= *lhs.operand_a == *rhs.operand_a;
            retval &= *lhs.operand_b == *rhs.operand_b;
            retval &= *lhs.operand_c == *rhs.operand_c;
            retval &= *lhs.destination == *rhs.destination;
            retval &= rhs.opcode == lhs.opcode;
            return retval;
        };

        std::shared_ptr<variable> get_operand_a() const {return operand_a;};
        std::shared_ptr<variable> get_operand_b() const {return operand_b;};
        std::shared_ptr<variable> get_operand_c() const {return operand_c;};

        std::shared_ptr<variable> get_destination() const {return destination;};
        void set_operand_a(std::shared_ptr<variable> v){ operand_a = std::move(v);};
        void set_destination(std::shared_ptr<variable> v){ destination = std::move(v);};
        std::vector<std::shared_ptr<variable>> get_arguments() const {return {operand_a, operand_b, operand_c, destination};};
        void set_arguments(const std::vector<std::shared_ptr<variable>> &a);

         opcode_table_t get_opcode() const {return opcode;};

    private:
        std::shared_ptr<variable> operand_a;
        std::shared_ptr<variable> operand_b;
        std::shared_ptr<variable> operand_c;
        std::shared_ptr<variable> destination;

        opcode_table_t opcode;
    };

}


#endif //FCORE_TOOLCHAIN_TERNARY_INSTRUCTION_HPP
