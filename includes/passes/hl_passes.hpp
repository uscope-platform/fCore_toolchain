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

#ifndef FCORE_HAS_HL_PASSES_HPP
#define FCORE_HAS_HL_PASSES_HPP

#include "pass_manager_base.hpp"
#include "passes/high_level/hl_pass_manager.h"
//HL PASSES
#include "passes/high_level/function_inlining_pass.h"
#include "passes/high_level/division_implementation_pass.h"
#include "passes/high_level/function_mapping.h"
#include "passes/high_level/inlined_function_elimination.h"
#include "passes/high_level/normalization_pass.h"
#include "passes/high_level/function_elimination_pass.h"
#include "passes/high_level/hl_variable_mapping.h"

#include "frontend/variable_map.hpp"
#include "ast/high_level/hl_ast_node.h"


static hl_pass_manager create_hl_pass_manager(std::string& entry_point, std::shared_ptr<variable_map> &var_map){
    hl_pass_manager manager;
    std::shared_ptr<function_mapping> mapping_pass = std::make_shared<function_mapping>();
    manager.add_morphing_pass(mapping_pass);

    manager.add_morphing_pass(std::make_shared<division_implementation_pass>());

    auto inlining_pass = std::make_shared<function_inlining_pass>();
    inlining_pass->set_functions_map(mapping_pass->get_map_ref());
    manager.add_morphing_pass(inlining_pass);

    manager.add_morphing_pass(std::make_shared<inlined_function_elimination>(entry_point));


    manager.add_global_pass(std::make_shared<normalization_pass>());
    manager.add_global_pass(std::make_shared<function_elimination_pass>());
    manager.add_global_pass(std::make_shared<hl_variable_mapping>(var_map));
    return manager;
}

#endif //FCORE_HAS_HL_PASSES_HPP
