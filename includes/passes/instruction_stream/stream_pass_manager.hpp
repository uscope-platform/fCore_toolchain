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

#include "passes/instruction_stream/stream_pass_base.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"
#include "data_structures/common/memory_tracker.hpp"
#include "instrumentation/instrumentation_core.hpp"
#include "data_structures/common/io_map_entry.hpp"

#include "passes/instruction_stream/stream_passes.hpp"

namespace fcore{


    class stream_pass_manager {
    public:

        enum mode {
            high_level_language,
            asm_language
        };

        stream_pass_manager(
                std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &bm,
                const std::shared_ptr<std::unordered_map<std::string, std::vector<io_map_entry>>>& all_map,
                std::shared_ptr<instrumentation_core> &prof,
                mode m
        );
        stream_pass_manager(
                std::vector<int> &io_res,
                std::shared_ptr<instrumentation_core> &prof,
                mode m
        );
        void constructs_pass_manager(
                std::shared_ptr<std::unordered_map<std::string, memory_range_t>> &bm,
                const std::shared_ptr<std::unordered_map<std::string, std::vector<io_map_entry>>>& all_map,
                std::shared_ptr<instrumentation_core> &prof,
                mode m
        );

        instruction_stream process_stream(instruction_stream stream);
        instruction_stream apply_pass(instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass);
        std::shared_ptr<instruction_count> get_instruction_count() {return ic;};
    private:
        mode optimizer_mode;
        std::vector<std::shared_ptr<stream_pass_base>> passes;
        std::shared_ptr<instruction_count> ic;
        std::shared_ptr<instrumentation_core> profiler;
    };
}


#endif //FCORE_TOOLCHAIN_STREAM_PASS_MANAGER_HPP
