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
#include "passes/hl_ast/hl_pass_manager.h"
//HL PASSES
#include "passes/hl_ast/function_inlining_pass.h"
#include "passes/hl_ast/division_implementation_pass.h"
#include "passes/hl_ast/function_mapping.h"
#include "passes/hl_ast/inlined_function_elimination.h"

#include "frontend/variable_map.hpp"
#include "code_elements/hl_ast/hl_ast_node.h"


static hl_pass_manager create_hl_pass_manager(std::string& entry_point){
    hl_pass_manager manager;
    std::shared_ptr<function_mapping> mapping_pass = std::make_shared<function_mapping>();
    manager.add_pass(mapping_pass);

    manager.add_pass(std::make_shared<division_implementation_pass>());

    auto inlining_pass = std::make_shared<function_inlining_pass>();
    inlining_pass->set_functions_map(mapping_pass->get_map_ref());
    manager.add_pass(inlining_pass);

    manager.add_pass(std::make_shared<inlined_function_elimination>(entry_point));


    return manager;
}

#endif //FCORE_HAS_HL_PASSES_HPP
