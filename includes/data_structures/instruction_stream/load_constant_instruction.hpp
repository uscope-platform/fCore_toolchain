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

#include "data_structures/instruction_stream/ll_instruction_node.hpp"

#include <utility>
namespace fcore{

    class load_constant_instruction: public instruction {
    public:
        load_constant_instruction(std::string op, std::shared_ptr<variable> dest, std::shared_ptr<variable> c);
        uint32_t emit() override;
        void print() override;
        std::string disassemble() override;

        int instruction_count() override;
        float get_constant_f();
        int get_constant_i();
        bool is_float();
        std::shared_ptr<variable> get_constant_variable() {return constant;};
        std::shared_ptr<variable> get_destination() {return destination;};
        void set_destination(std::shared_ptr<variable> v){destination = v;};
        std::vector<std::shared_ptr<variable>> get_arguments() override {return {destination, constant};};
        void set_arguments(const std::vector<std::shared_ptr<variable>> &a) override;

        nlohmann::json dump();

        friend bool operator==(const load_constant_instruction& lhs, const load_constant_instruction& rhs){
            bool retval = true;

            retval &= *lhs.constant == *rhs.constant;
            retval &= *lhs.destination == *rhs.destination;
            retval &= rhs.opcode == lhs.opcode;
            return retval;
        };

        std::string get_opcode(){return opcode;};

    private:
        std::shared_ptr<variable> destination;
        std::shared_ptr<variable> constant;
        std::string opcode;
    };
}


#endif //FCORE_TOOLCHAIN_LOAD_CONSTANT_INSTRUCTION_HPP
