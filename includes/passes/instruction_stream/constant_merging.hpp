// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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
//

#ifndef FCORE_TOOLCHAIN_CONSTANT_MERGING_H
#define FCORE_TOOLCHAIN_CONSTANT_MERGING_H

#include "stream_pass_base.hpp"

#include <unordered_map>
#include <set>
#include <utility>

namespace fcore{
    class constant_merging : public stream_pass_base {
    public:
        constant_merging(std::shared_ptr<std::map<std::string, std::pair<int,int>>> lam);
        std::optional<instruction_variant> apply_pass(const instruction_variant &element, uint32_t n) override;

    private:
        std::set<std::string> processed_constants;
        std::map<float, std::shared_ptr<variable>> float_const_map;
        std::map<uint32_t, std::shared_ptr<variable>> int_const_map;
        std::map<std::string, std::shared_ptr<variable>> reassignments_map;
        void map_exclusions(const instruction_variant &element);
        instruction_variant merge_register_inst(register_instruction& instr);
        instruction_variant merge_ternary_inst(ternary_instruction& instr);
        instruction_variant merge_conv_instr(conversion_instruction& instr);
        std::optional<instruction_variant> merge_load_const_instr(load_constant_instruction& instr);
        std::optional<instruction_variant> merge_interc_const(intercalated_constant& instr);
        std::shared_ptr<variable> get_merged_constant(std::shared_ptr<variable> v);
        bool is_last_io_assignment(const std::shared_ptr<variable> &dest);
        bool delete_intercalated_const;
        int idx;
        std::shared_ptr<std::map<std::string, std::pair<int,int>>> assignments_map;
    };
}


#endif //FCORE_TOOLCHAIN_CONSTANT_MERGING_H
