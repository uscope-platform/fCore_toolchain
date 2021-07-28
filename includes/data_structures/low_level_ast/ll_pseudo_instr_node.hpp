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

#ifndef FCORE_TOOLCHAIN_LL_PSEUDO_INSTR_NODE_HPP
#define FCORE_TOOLCHAIN_LL_PSEUDO_INSTR_NODE_HPP

#include <utility>

#include "data_structures/low_level_ast/ll_instruction_node.hpp"
#include "tools/variable.hpp"

class ll_pseudo_instr_node :public ll_instruction_node {
public:
    ll_pseudo_instr_node(std::string op, std::vector<std::shared_ptr<variable>> args);

    std::vector<std::shared_ptr<variable>> get_arguments() {return arguments;};
    void set_arguments(std::vector<std::shared_ptr<variable>> a) {arguments = std::move(a);};
    int instruction_count() override;

    friend bool operator==(const ll_pseudo_instr_node& lhs, const ll_pseudo_instr_node& rhs);
private:
    std::vector<std::shared_ptr<variable>> arguments;
};


#endif //FCORE_TOOLCHAIN_LL_PSEUDO_INSTR_NODE_HPP
