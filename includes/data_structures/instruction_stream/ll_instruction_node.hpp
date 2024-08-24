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

#ifndef FCORE_TOOLCHAIN_LL_INSTRUCTION_NODE_HPP
#define FCORE_TOOLCHAIN_LL_INSTRUCTION_NODE_HPP

#include <string>
#include <cstdint>
#include <utility>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>

#include "data_structures/common/variable.hpp"
#include "fCore_isa.hpp"

namespace fcore{
    class instruction {

    public:
        explicit instruction(isa_instruction_type t);
        instruction(const instruction &old_obj);

        bool is_stop();


        virtual uint32_t emit() { return 0;};
        virtual void print() {};
        virtual std::string disassemble() {return "";};
        virtual int instruction_count() { return 0;};

        bool is_terminal();

        friend bool operator==(const instruction& lhs, const instruction& rhs){
            bool retval = true;

            retval &= lhs.opcode == rhs.opcode;
            return retval;
        };
        static bool compare_content_by_type(const std::shared_ptr<instruction> &lhs, const std::shared_ptr<instruction> &rhs);
        [[nodiscard]] bool is_pseudo() const { return instruction_type == isa_pseudo_instruction;};

        isa_instruction_type get_type();
        std::string get_opcode(){return opcode;};
        virtual std::vector<std::shared_ptr<variable>> get_arguments() {return {};};
        virtual void set_arguments(const std::vector<std::shared_ptr<variable>> &) {};

        nlohmann::json dump();
        static nlohmann::json dump_instruction_by_type(const std::shared_ptr<instruction> &node);

    protected:

        isa_instruction_type instruction_type;

        std::string opcode;


    };
}



#endif //FCORE_TOOLCHAIN_LL_INSTRUCTION_NODE_HPP
