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

#include "data_structures/instruction_stream/ll_instruction_node.hpp"
#include "data_structures/common/variable.hpp"


namespace fcore{
    class ternary_instruction : public instruction {
    public:
        ternary_instruction(std::string op, std::shared_ptr<variable> op_a, std::shared_ptr<variable> op_b, std::shared_ptr<variable> op_c, std::shared_ptr<variable> dest);
        uint32_t emit() override;
        std::string disassemble() override;
        void print() override;
        int instruction_count() override;

        nlohmann::json dump();

        friend bool operator==(const ternary_instruction& lhs, const ternary_instruction& rhs){
            bool retval = true;

            retval &= *lhs.operand_a == *rhs.operand_a;
            retval &= *lhs.operand_b == *rhs.operand_b;
            retval &= *lhs.operand_c == *rhs.operand_c;
            retval &= *lhs.destination == *rhs.destination;
            retval &= rhs.opcode == lhs.opcode;
            return retval;
        };

        std::shared_ptr<variable> get_operand_a() {return operand_a;};
        std::shared_ptr<variable> get_operand_b() {return operand_b;};
        std::shared_ptr<variable> get_operand_c() {return operand_c;};

        std::shared_ptr<variable> get_destination() {return destination;};
        void set_operand_a(std::shared_ptr<variable> v){ operand_a = std::move(v);};
        void set_destination(std::shared_ptr<variable> v){ destination = std::move(v);};
        std::vector<std::shared_ptr<variable>> get_arguments() override {return {operand_a, operand_b, operand_c, destination};};
        void set_arguments(const std::vector<std::shared_ptr<variable>> &a) override;
    private:
        std::shared_ptr<variable> operand_a;
        std::shared_ptr<variable> operand_b;
        std::shared_ptr<variable> operand_c;
        std::shared_ptr<variable> destination;
    };

}


#endif //FCORE_TOOLCHAIN_TERNARY_INSTRUCTION_HPP
