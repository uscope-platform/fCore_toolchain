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

#ifndef FCORE_TOOLCHAIN_STREAM_PASS_MANAGER_HPP
#define FCORE_TOOLCHAIN_STREAM_PASS_MANAGER_HPP

#include <utility>

#include "passes/instruction_stream/variable_lifetime_mapping.hpp"
#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "data_structures/instruction_stream.hpp"
#include "passes/instruction_stream/stream_pass_base.hpp"

#include "passes/instruction_stream/variable_lifetime_mapping.hpp"
#include "passes/instruction_stream/variable_mapping.hpp"
#include "passes/instruction_stream/register_allocation.hpp"

class stream_pass_manager {
public:
    stream_pass_manager();
    instruction_stream process_stream(instruction_stream stream);
    instruction_stream apply_pass(const instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass);
private:
    std::vector<std::shared_ptr<stream_pass_base>> passes;
};


#endif //FCORE_TOOLCHAIN_STREAM_PASS_MANAGER_HPP
