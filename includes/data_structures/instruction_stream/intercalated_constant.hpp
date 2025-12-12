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

#ifndef FCORE_TOOLCHAIN_INTERCALATED_CONSTANT_HPP
#define FCORE_TOOLCHAIN_INTERCALATED_CONSTANT_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include "data_structures/common/variable.hpp"
#include "fCore_isa.hpp"

namespace fcore{
    class intercalated_constant {
    public:
        explicit intercalated_constant(float constant);
        explicit intercalated_constant(uint32_t constant);
        uint32_t emit() const;
        intercalated_constant(const intercalated_constant& other) = default;
        intercalated_constant(intercalated_constant&& other) noexcept = default;
        intercalated_constant& operator=(const intercalated_constant& other) = default;
        intercalated_constant& operator=(intercalated_constant&& other) noexcept = default;
        void print() const;
        std::string to_string() const;
        std::string disassemble() const;
        int instruction_count() const;

        friend bool operator==(const intercalated_constant& lhs, const intercalated_constant& rhs){
            {
                bool retval = true;

                retval &= lhs.float_const == rhs.float_const;
                retval &= rhs.opcode == lhs.opcode;
                return retval;
            }
        };

        void set_arguments(const std::vector<std::shared_ptr<variable>> &) {};
        std::vector<std::shared_ptr<variable>> get_arguments() const {return {};};


        opcode_table_t get_opcode(){return opcode;};

    private:
        float float_const;
        uint32_t int_const;
        bool is_float;
        opcode_table_t opcode;
    };
}


#endif //FCORE_TOOLCHAIN_INTERCALATED_CONSTANT_HPP
