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
    stream_pass_manager(std::unordered_map<std::string, std::shared_ptr<variable>> &iom);
    instruction_stream process_stream(instruction_stream stream);
    instruction_stream apply_pass(const instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass);
private:
    std::vector<std::shared_ptr<stream_pass_base>> passes;
    std::unordered_map<std::string, std::shared_ptr<variable>> iom_map;
};


#endif //FCORE_TOOLCHAIN_STREAM_PASS_MANAGER_HPP
