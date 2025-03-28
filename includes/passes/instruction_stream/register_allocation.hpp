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
#include <unordered_map>

#include "passes/instruction_stream/stream_pass_base.hpp"
#include "data_structures/common/variable.hpp"
#include "tools/variable_map.hpp"
#include "tools/register_map.hpp"
#include "data_structures/common/memory_tracker.hpp"
#include "data_structures/common/io_map_entry.hpp"

namespace fcore{
    class register_allocation : public stream_pass_base{
    public:
        register_allocation(
                std::shared_ptr<variable_map> vmap,
                std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &ebm,
                const std::shared_ptr<std::unordered_map<std::string, std::vector<io_map_entry>>>& all_map
        );
        void setup() override;
        std::optional<instruction_variant> apply_mutable_pass(instruction_variant &element, uint32_t n)  override;
    private:
        void allocate_register(std::shared_ptr<variable> &var, int reg_addr);
        void allocate_array(std::shared_ptr<variable> &var, int reg_addr);

        std::string get_variable_type(std::shared_ptr<variable> &var);
        register_map reg_map;
        std::shared_ptr<variable_map> var_map;
        std::vector<bool> excluded;

        std::unordered_map<std::string, std::pair<int, int>> allocated_contiguous_arrays;
        std::shared_ptr<std::unordered_map<std::string, std::vector<io_map_entry>>> allocation_map;
        std::unordered_map<std::string, int> memory_vars;
    };
}


#endif //FCORE_TOOLCHAIN_REGISTER_ALLOCATION_HPP
