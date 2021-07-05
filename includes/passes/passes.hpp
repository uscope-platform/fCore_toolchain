// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_HAS_PASSES_HPP
#define FCORE_HAS_PASSES_HPP

#include "pass_manager.hpp"
// LL passes
#include "ll_ast/loop_implementation_pass.hpp"
#include "ll_ast/pseudo_instructions_pass.hpp"
#include "ll_ast/instruction_counting_pass.hpp"
#include "ll_ast/register_allocation_pass.hpp"
#include "ll_ast/variable_lifetime_mapping.hpp"
#include "ll_ast/load_intercalation_pass.hpp"
//HL PASSES
#include "hl_ast/function_inlining_pass.h"

#include "frontend/variable_map.hpp"
#include "code_elements/ll_ast/ll_ast_node.hpp"
#include "code_elements/hl_ast/hl_ast_node.h"

static pass_manager<ll_ast_node> create_ll_pass_manager(std::shared_ptr<variable_map> varmap){
    pass_manager<ll_ast_node> manager;
    manager.add_pass(std::make_shared<loop_implementation_pass>());
    manager.add_pass(std::make_shared<pseudo_instructions_pass>());
    manager.add_pass(std::make_shared<variable_lifetime_mapping>(varmap));
    manager.add_pass(std::make_shared<load_intercalation_pass>());
    manager.add_pass(std::make_shared<register_allocation_pass>(varmap));//REGISTER ALLOCATION SHOULD ALWAYS BE THE LAST PASS
    std::shared_ptr<pass_base<ll_ast_node>> ic_pass =std::make_shared<instruction_counting_pass>();
    manager.add_pass(ic_pass);
    manager.analysis_passes.insert(std::make_pair ("instruction_counting", ic_pass));
    return manager;
}


static pass_manager<hl_ast_node> create_hl_pass_manager(std::shared_ptr<variable_map> varmap){
    pass_manager<hl_ast_node> manager;
    manager.add_pass(std::make_shared<function_inlining_pass>());

    return manager;
}

#endif //FCORE_HAS_PASSES_HPP
