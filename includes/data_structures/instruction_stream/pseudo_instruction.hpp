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

#ifndef FCORE_TOOLCHAIN_PSEUDO_INSTRUCTION_HPP
#define FCORE_TOOLCHAIN_PSEUDO_INSTRUCTION_HPP

#include <utility>

#include "data_structures/common/variable.hpp"

namespace fcore{

    class pseudo_instruction {
    public:
        pseudo_instruction(std::string op, std::vector<std::shared_ptr<variable>> args);

        std::vector<std::shared_ptr<variable>> get_arguments() const {return arguments;};
        void set_arguments(std::vector<std::shared_ptr<variable>> a) {arguments = std::move(a);};
        int instruction_count() const;

        uint32_t emit() const{ return 0;};
        void print() const {};
        std::string disassemble() const{return "";};

        friend bool operator==(const pseudo_instruction& lhs, const pseudo_instruction& rhs){
            bool retval = true;

            if(lhs.arguments.empty() && rhs.arguments.empty()){
                retval &= true;
            } else if(lhs.arguments.empty() || rhs.arguments.empty()){
                retval = false;
            } else {
                bool args_equal = true;
                args_equal &= lhs.arguments.size() == rhs.arguments.size();
                for (int i = 0; i < lhs.arguments.size(); i++) {
                    args_equal &= *lhs.arguments[i] == *rhs.arguments[i];
                }
                retval &= args_equal;
            }
            return retval;
        };

        std::string get_opcode(){return opcode;};
    private:
        std::vector<std::shared_ptr<variable>> arguments;
        std::string opcode;
    };
}


#endif //FCORE_TOOLCHAIN_PSEUDO_INSTRUCTION_HPP
