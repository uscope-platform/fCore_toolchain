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

#ifndef FCORE_TOOLCHAIN_LL_PASSES_HPP
#define FCORE_TOOLCHAIN_LL_PASSES_HPP

#include "pass_manager_base.hpp"
// LL passes
#include "passes/low_level/loop_implementation_pass.hpp"
#include "passes/low_level/pseudo_instructions_pass.hpp"
#include "passes/low_level/instruction_counting_pass.hpp"
#include "passes/low_level/register_allocation_pass.hpp"
#include "passes/low_level/variable_lifetime_mapping.hpp"
#include "passes/low_level/load_intercalation_pass.hpp"

#include "tools/variable_map.hpp"
#include "ast/low_level/ll_ast_node.hpp"
#include "passes/low_level/ll_pass_manager.hpp"
#include "passes/pass_base.hpp"

static ll_pass_manager create_ll_pass_manager(std::shared_ptr<variable_map> varmap){
    ll_pass_manager manager;
    manager.add_morphing_pass(std::make_shared<loop_implementation_pass>());
    manager.add_morphing_pass(std::make_shared<pseudo_instructions_pass>());
    manager.add_morphing_pass(std::make_shared<variable_lifetime_mapping>(varmap));
    manager.add_morphing_pass(std::make_shared<load_intercalation_pass>());
    manager.add_morphing_pass(std::make_shared<register_allocation_pass>(varmap));//REGISTER ALLOCATION SHOULD ALWAYS BE THE LAST PASS
    std::shared_ptr<pass_base<ll_ast_node>> ic_pass =std::make_shared<instruction_counting_pass>();
    manager.add_morphing_pass(ic_pass);
    manager.set_pass_order({1,2,3,4,5,6});
    manager.analysis_passes.insert(std::make_pair ("instruction_counting", ic_pass));
    return manager;
}

#endif //FCORE_TOOLCHAIN_LL_PASSES_HPP
