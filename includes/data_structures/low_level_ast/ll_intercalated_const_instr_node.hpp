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

#ifndef FCORE_TOOLCHAIN_LL_INTERCALATED_CONST_INSTR_NODE_HPP
#define FCORE_TOOLCHAIN_LL_INTERCALATED_CONST_INSTR_NODE_HPP

#include "data_structures/low_level_ast/low_level_ast.hpp"
namespace fcore{
    class ll_intercalated_const_instr_node : public ll_instruction_node {
    public:
        explicit ll_intercalated_const_instr_node(float constant);
        explicit ll_intercalated_const_instr_node(uint32_t constant);
        uint32_t emit() override;
        void print() override;
        int instruction_count() override;

        friend bool operator==(const ll_intercalated_const_instr_node& lhs, const ll_intercalated_const_instr_node& rhs){
            {
                bool retval = true;

                retval &= lhs.float_const == rhs.float_const;
                retval &= rhs.opcode == lhs.opcode;
                return retval;
            }
        };

        nlohmann::json dump();

    private:
        float float_const;
        uint32_t int_const;
        bool is_float;
    };
}


#endif //FCORE_TOOLCHAIN_LL_INTERCALATED_CONST_INSTR_NODE_HPP
