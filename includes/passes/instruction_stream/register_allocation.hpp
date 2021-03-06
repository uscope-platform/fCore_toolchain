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

#ifndef FCORE_TOOLCHAIN_REGISTER_ALLOCATION_HPP
#define FCORE_TOOLCHAIN_REGISTER_ALLOCATION_HPP

#include <utility>


#include "passes/instruction_stream/stream_pass_base.hpp"
#include "tools/variable.hpp"
#include "tools/variable_map.hpp"
#include "tools/register_map.hpp"


class register_allocation : public stream_pass_base{
public:
    register_allocation(std::shared_ptr<variable_map> vmap, std::unordered_map<std::string, std::shared_ptr<variable>> &iom);
    std::shared_ptr<ll_instruction_node> apply_pass(std::shared_ptr<ll_instruction_node> element) override;
private:
    std::shared_ptr<variable_map> var_map;
    std::unordered_map<std::string, std::shared_ptr<variable>> iom_map;
    std::unordered_map<std::string, std::shared_ptr<variable>> register_mapping;
    register_map reg_map;
    std::vector<bool> used;
};


#endif //FCORE_TOOLCHAIN_REGISTER_ALLOCATION_HPP
