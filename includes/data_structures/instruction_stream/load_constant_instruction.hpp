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

#ifndef FCORE_TOOLCHAIN_LOAD_CONSTANT_INSTRUCTION_HPP
#define FCORE_TOOLCHAIN_LOAD_CONSTANT_INSTRUCTION_HPP

#include <iostream>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>

#include "data_structures/common/variable.hpp"
#include "fCore_isa.hpp"

namespace fcore{

    class load_constant_instruction {
    public:
        load_constant_instruction(opcode_table_t op, std::shared_ptr<variable> dest, std::shared_ptr<variable> c);
        std::vector<uint32_t> emit() const;
        void print() const;
        load_constant_instruction(const load_constant_instruction& other) = default;
        load_constant_instruction(load_constant_instruction&& other) noexcept = default;
        load_constant_instruction& operator=(const load_constant_instruction& other) = default;
        load_constant_instruction& operator=(load_constant_instruction&& other) noexcept = default;
        std::string to_string() const;
        std::string disassemble() const;

        int instruction_count() const;
        float get_constant_f();
        int get_constant_i();
        bool is_float();
        std::shared_ptr<variable> get_constant_variable() {return constant;};
        std::shared_ptr<variable> get_destination() const {return destination;};
        void set_destination(std::shared_ptr<variable> v){destination = v;};
        std::vector<std::shared_ptr<variable>> get_arguments() const {return {destination, constant};};
        void set_arguments(const std::vector<std::shared_ptr<variable>> &a);

        friend bool operator==(const load_constant_instruction& lhs, const load_constant_instruction& rhs){
            bool retval = true;

            retval &= *lhs.constant == *rhs.constant;
            retval &= *lhs.destination == *rhs.destination;
            retval &= rhs.opcode == lhs.opcode;
            return retval;
        };

        opcode_table_t get_opcode(){return opcode;};

    private:
        std::shared_ptr<variable> destination;
        std::shared_ptr<variable> constant;
        opcode_table_t opcode;
    };
}


#endif //FCORE_TOOLCHAIN_LOAD_CONSTANT_INSTRUCTION_HPP
