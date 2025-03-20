//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAINLCHAIN_HL_PASSES_HPP
#define FCORE_TOOLCHAINLCHAIN_HL_PASSES_HPP

#include "passes/high_level/infrastructure/hl_pass_manager.hpp"
//HL PASSES
#include "passes/high_level/optimizations/function_inlining_pass.hpp"
#include "passes/high_level/optimizations/visitor_passes/division_implementation_pass.hpp"
#include "passes/high_level/optimizations/inlined_function_elimination.hpp"
#include "passes/high_level/optimizations/normalization_pass.hpp"
#include "passes/high_level/optimizations/visitor_passes/intrinsics_implementation_pass.hpp"
#include "passes/high_level/optimizations/visitor_passes/comparison_flipping.hpp"
#include "passes/high_level/optimizations/visitor_passes/dead_variable_elimination.hpp"
#include "passes/high_level/optimizations/visitor_passes/constant_folding_pass.hpp"
#include "passes/high_level/optimizations/constant_propagation.hpp"
#include "passes/high_level/optimizations/inline_constant_extraction.hpp"
#include "passes/high_level/optimizations/conditional_implementation_pass.h"
#include "passes/high_level/optimizations/loop_unrolling_pass.hpp"
#include "passes/high_level/optimizations/code_block_inlining_pass.hpp"
#include "passes/high_level/optimizations/visitor_passes/operating_assignment_implementation_pass.hpp"
#include "passes/high_level/optimizations/dead_load_elimination.hpp"
#include "passes/high_level/optimizations/visitor_passes/array_index_lowering.hpp"
#include "passes/high_level/optimizations/fuction_mangling_pass.hpp"
#include "passes/high_level/optimizations/contiguous_array_identification.hpp"
#include "passes/high_level/optimizations/visitor_passes/array_initialization_substitution.h"
#include "passes/high_level/optimizations/visitor_passes/ternary_expression_extraction.hpp"
#include "passes/high_level/optimizations/visitor_passes/destructuring_pass.hpp"


namespace fcore{
    static hl_pass_manager create_hl_pass_manager(
            std::string& entry_point
    ){
        hl_pass_manager manager;

        manager.add_optimization_pass("Division Implementation", std::make_shared<division_implementation_pass>()); // pass #1
        manager.add_optimization_pass("Intrinsics Implementation", std::make_shared<intrinsics_implementation_pass>()); // pass #2
        manager.add_optimization_pass("Comparison flipping pass", std::make_shared<comparison_flipping>()); // pass #2

        manager.add_optimization_pass("Operating Assignment Implementation", std::make_shared<operating_assignment_implementation_pass>()); // pass #3
        manager.add_optimization_pass("Function Mangling", std::make_shared<fuction_mangling_pass>()); // pass #4

        manager.add_optimization_pass_group("Function Inlining", {std::make_shared<function_inlining_pass>(),  std::make_shared<code_block_inlining_pass>()}); // group #-1
        manager.add_optimization_pass("Inlined Function Elimination", std::make_shared<inlined_function_elimination>(entry_point)); // pass #6
        manager.add_optimization_pass("Code Block Expansion",std::make_shared<code_block_inlining_pass>()); // pass #7

        manager.add_optimization_pass_group("Destructuring", {std::make_shared<destructuring_pass>()});

        manager.add_optimization_pass("Loop Unrolling", std::make_shared<loop_unrolling_pass>()); // pass #8
        manager.add_optimization_pass("Array Initialization", std::make_shared<array_initialization_substitution>()); // pass #9
        manager.add_optimization_pass("Conditional Implementation", std::make_shared<conditional_implementation_pass>()); // pass #10
        manager.add_optimization_pass("Normalization", std::make_shared<normalization_pass>()); // pass #11

        manager.add_optimization_pass("Contiguous Array Identification", std::make_shared<contiguous_array_identification>()); // pass #12
        manager.add_optimization_pass("Dead Variable elimination", std::make_shared<dead_variable_elimination>());  // pass #13

        auto const_fold = std::make_shared<constant_folding_pass>();
        auto const_prop = std::make_shared<constant_propagation>();
        manager.add_optimization_pass_group("Constants optimization", {const_fold, const_prop}); // group #-1

        manager.add_optimization_pass("Inline Constant Extraction", std::make_shared<inline_constant_extraction>()); // pass #14
        manager.add_optimization_pass("Array Flattening", std::make_shared<array_index_lowering>()); // pass #15
        manager.add_optimization_pass("Dead Load elimination", std::make_shared<dead_load_elimination>()); // pass #16
        manager.add_optimization_pass("Ternary Expression extraction", std::make_shared<ternary_expression_extraction>());
        return manager;
    }
}




#endif //FCORE_TOOLCHAINLCHAIN_HL_PASSES_HPP
