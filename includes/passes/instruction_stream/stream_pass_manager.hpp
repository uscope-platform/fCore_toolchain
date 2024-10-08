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
#include "data_structures/instruction_stream/instruction_stream.hpp"
#include "passes/instruction_stream/stream_pass_base.hpp"

#include "passes/instruction_stream/variable_lifetime_mapping.hpp"
#include "passes/instruction_stream/variable_mapping.hpp"
#include "passes/instruction_stream/register_allocation.hpp"
#include "passes/instruction_stream/constant_merging.hpp"
#include "passes/instruction_stream/zero_assignment_removal_pass.hpp"
#include "passes/instruction_stream/bound_register_mapping.hpp"
#include "passes/instruction_stream/io_constant_tracking.hpp"
#include "passes/instruction_stream/ternary_reduction.hpp"
#include "passes/instruction_stream/instruction_counting_pass.hpp"
#include "passes/instruction_stream/virtual_operations_implementation.hpp"
#include "data_structures/common/memory_tracker.hpp"

#include "instrumentation/instrumentation_core.hpp"

namespace fcore{
    class stream_pass_manager {
    public:
        stream_pass_manager(
                std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &bm,
                const std::shared_ptr<std::unordered_map<std::string, std::vector<io_map_entry>>>& all_map,
                std::shared_ptr<instrumentation_core> &prof
        );
        stream_pass_manager(
                std::vector<int> &io_res,
                std::shared_ptr<instrumentation_core> &prof
        );
        void constructs_pass_manager(
                std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &bm,
                const std::shared_ptr<std::unordered_map<std::string, std::vector<io_map_entry>>>& all_map,
                std::shared_ptr<instrumentation_core> &prof
        );

        instruction_stream process_stream(instruction_stream stream);
        instruction_stream apply_pass(instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass);
        void set_enabled_passes(std::vector<bool> ep) {enabled_passes = std::move(ep);};
        std::shared_ptr<struct instruction_count> get_instruction_count() {return ic;};
    private:
        std::vector<std::shared_ptr<stream_pass_base>> passes;
        std::vector<bool> enabled_passes;
        std::shared_ptr<struct instruction_count> ic;
        std::shared_ptr<instrumentation_core> profiler;
    };
}


#endif //FCORE_TOOLCHAIN_STREAM_PASS_MANAGER_HPP
