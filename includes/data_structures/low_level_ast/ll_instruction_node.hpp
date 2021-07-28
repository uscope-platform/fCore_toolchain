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

#ifndef FCORE_TOOLCHAIN_LL_INSTRUCTION_NODE_HPP
#define FCORE_TOOLCHAIN_LL_INSTRUCTION_NODE_HPP

#include <string>
#include <cstdint>
#include <utility>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>

#include "data_structures/low_level_ast/ll_ast_node.hpp"
#include "tools/variable.hpp"
#include "fCore_isa.hpp"


class ll_instruction_node : public ll_ast_node{

public:
    explicit ll_instruction_node(isa_instruction_type t);
    ll_instruction_node(const ll_instruction_node &old_obj);



    virtual uint32_t emit() { return 0;};
    virtual void print() {};
    virtual int instruction_count() { return 0;};

    bool is_terminal() override;

    friend bool operator==(const ll_instruction_node& lhs, const ll_instruction_node& rhs);

    [[nodiscard]] bool is_pseudo() const { return instruction_type == isa_pseudo_instruction;};

    isa_instruction_type get_type();
    std::string get_opcode(){return opcode;};
    virtual std::vector<std::shared_ptr<variable>> get_arguments() {return {};};
    virtual void set_arguments(const std::vector<std::shared_ptr<variable>> &a) {};
protected:

    isa_instruction_type instruction_type;

    std::string opcode;

};



#endif //FCORE_TOOLCHAIN_LL_INSTRUCTION_NODE_HPP
