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

#ifndef FCORE_TOOLCHAIN_REGISTER_ALLOCATION_HPP
#define FCORE_TOOLCHAIN_REGISTER_ALLOCATION_HPP

#include <utility>


#include "passes/instruction_stream/stream_pass_base.hpp"
#include "tools/variable.hpp"
#include "tools/variable_map.hpp"
#include "frontend/asm/register_map.hpp"


class register_allocation : public stream_pass_base{
public:
    explicit register_allocation(std::shared_ptr<variable_map> vmap);
    std::shared_ptr<ll_instruction_node> apply_pass(std::shared_ptr<ll_instruction_node> element) override;
private:
    std::shared_ptr<variable_map> var_map;
    std::unordered_map<std::string, std::shared_ptr<variable>> register_mapping;
    register_map reg_map;
    std::vector<bool> used;
};


#endif //FCORE_TOOLCHAIN_REGISTER_ALLOCATION_HPP
