// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_LL_INTERCALATED_CONST_INSTR_NODE_HPP
#define FCORE_TOOLCHAIN_LL_INTERCALATED_CONST_INSTR_NODE_HPP

#include "data_structures/low_level_ast/low_level_ast.hpp"

class ll_intercalated_const_instr_node : public ll_instruction_node {
public:
    explicit ll_intercalated_const_instr_node(float constant);
    uint32_t emit() override;
    void print() override;
    int instruction_count() override;

    friend bool operator==(const ll_intercalated_const_instr_node& lhs, const ll_intercalated_const_instr_node& rhs);
private:
    float intercalated_constant;
};


#endif //FCORE_TOOLCHAIN_LL_INTERCALATED_CONST_INSTR_NODE_HPP
