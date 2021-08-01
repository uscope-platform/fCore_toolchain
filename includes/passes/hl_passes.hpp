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

#ifndef FCORE_TOOLCHAINLCHAIN_HL_PASSES_HPP
#define FCORE_TOOLCHAINLCHAIN_HL_PASSES_HPP

#include "pass_manager_base.hpp"
#include "passes/high_level/hl_pass_manager.hpp"
//HL PASSES
#include "passes/high_level/function_inlining_pass.hpp"
#include "passes/high_level/division_implementation_pass.hpp"
#include "passes/high_level/function_mapping.hpp"
#include "passes/high_level/inlined_function_elimination.hpp"
#include "passes/high_level/normalization_pass.hpp"
#include "passes/high_level/hl_variable_mapping.hpp"
#include "passes/high_level/intrinsics_implementation_pass.hpp"
#include "passes/high_level/dead_variable_elimination.hpp"
#include "passes/high_level/declaration_instantiation_combining_pass.hpp"
#include "passes/high_level/constant_folding_pass.hpp"
#include "passes/high_level/constant_propagation.hpp"
#include "passes/high_level/inline_constant_extraction.hpp"
#include "passes/high_level/conditional_implementation_pass.h"
#include "passes/high_level/loop_unrolling_pass.hpp"
#include "passes/high_level/array_scalarization_pass.hpp"
#include "passes/high_level/code_block_inlining_pass.hpp"
#include "tools/variable_map.hpp"
#include "data_structures/high_level_ast/hl_ast_node.hpp"


static hl_pass_manager create_hl_pass_manager(std::string& entry_point, std::vector<int> order){
    hl_pass_manager manager;
    std::shared_ptr<function_mapping> mapping_pass = std::make_shared<function_mapping>();
    manager.add_morphing_pass(mapping_pass);  // pass #1

    manager.add_morphing_pass(std::make_shared<division_implementation_pass>()); // pass #2
    manager.add_morphing_pass(std::make_shared<intrinsics_implementation_pass>()); // pass #3

    auto inlining_pass = std::make_shared<function_inlining_pass>();
    inlining_pass->set_functions_map(mapping_pass->get_map_ref());
    manager.add_morphing_pass(inlining_pass); // pass #4

    manager.add_morphing_pass(std::make_shared<inlined_function_elimination>(entry_point)); // pass #5
    manager.add_morphing_pass(std::make_shared<code_block_inlining_pass>()); // pass #6

    manager.add_morphing_pass(std::make_shared<conditional_implementation_pass>()); // pass #7
    manager.add_morphing_pass(std::make_shared<loop_unrolling_pass>()); // pass #8
    manager.add_morphing_pass(std::make_shared<array_scalarization_pass>()); // pass #9

    manager.add_morphing_pass(std::make_shared<normalization_pass>());// pass #10
    manager.add_morphing_pass(std::make_shared<declaration_instantiation_combining_pass>());  // pass #11
    manager.add_morphing_pass(std::make_shared<dead_variable_elimination>()); // pass #12

    std::shared_ptr<constant_folding_pass> const_fold = std::make_shared<constant_folding_pass>();
    std::shared_ptr<constant_propagation> const_prop = std::make_shared<constant_propagation>();

    manager.add_morphing_pass_group({const_fold, const_prop}); // group #-1
    manager.add_morphing_pass(std::make_shared<inline_constant_extraction>()); // pass #13


    if(order.empty()){
        manager.set_pass_order({1,2,3,4,5,6,7,8,9,10,11,12,-1, 13});
    } else {
        manager.set_pass_order(order);
    }

    return manager;
}

#endif //FCORE_TOOLCHAINLCHAIN_HL_PASSES_HPP
