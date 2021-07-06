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

//HL PASSES
#include "hl_ast/function_inlining_pass.h"
#include "hl_ast/division_implementation_pass.h"

#include "frontend/variable_map.hpp"
#include "code_elements/hl_ast/hl_ast_node.h"


static pass_manager_base<hl_ast_node> create_hl_pass_manager(std::shared_ptr<variable_map> varmap){
    pass_manager_base<hl_ast_node> manager;
    manager.add_pass(std::make_shared<function_inlining_pass>());
    manager.add_pass(std::make_shared<division_implementation_pass>());
    return manager;
}

#endif //FCORE_HAS_HL_PASSES_HPP
