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

#ifndef FCORE_TOOLCHAIN_LL_INDEPENDENT_INST_NODE_HPP
#define FCORE_TOOLCHAIN_LL_INDEPENDENT_INST_NODE_HPP

#include <utility>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>

#include "data_structures/common/variable.hpp"
#include "fCore_isa.hpp"

namespace fcore{
    class independent_instruction {
    public:
        explicit independent_instruction(std::string opcode);
        uint32_t emit() const;
        std::string disassemble() const;
        void print() const;
        int instruction_count() const;

        void set_arguments(const std::vector<std::shared_ptr<variable>> &) {};
        std::vector<std::shared_ptr<variable>> get_arguments() const {return {};};

        friend bool operator==(const independent_instruction& lhs, const independent_instruction& rhs){
            return rhs.opcode == lhs.opcode;
        };

        std::string get_opcode(){return opcode;};

    private:

        std::string opcode;
    };
}



#endif //FCORE_TOOLCHAIN_LL_INDEPENDENT_INST_NODE_HPP
