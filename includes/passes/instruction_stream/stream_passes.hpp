//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef STREAM_PASSES_HPP
#define STREAM_PASSES_HPP


#include "passes/instruction_stream/variable_lifetime_mapping.hpp"
#include "passes/instruction_stream/stream_pass_base.hpp"
#include <passes/instruction_stream/uninitialized_variable_detection.hpp>
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
#include "passes/instruction_stream/ternary_deconfliction.hpp"
#include "passes/instruction_stream/stall_insertion.hpp"
#include "passes/instruction_stream/bound_register_assignment.hpp"
#include "passes/instruction_stream/result_deconfliction.hpp"

#endif //STREAM_PASSES_HPP
