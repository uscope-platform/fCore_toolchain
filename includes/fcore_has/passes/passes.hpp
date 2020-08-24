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
#include "loop_implementation_pass.hpp"
#include "pseudo_instructions_pass.hpp"
#include "instruction_counting_pass.hpp"
#include "register_allocation_pass.hpp"
#include "variable_lifetime_mapping.hpp"
#include "load_intercalation_pass.hpp"
#include "../frontend/variable_map.hpp"

static pass_manager create_pass_manager(std::shared_ptr<variable_map> varmap){
    pass_manager manager;
    manager.add_pass(std::make_shared<loop_implementation_pass>());
    manager.add_pass(std::make_shared<pseudo_instructions_pass>());
    manager.add_pass(std::make_shared<variable_lifetime_mapping>(varmap));
    manager.add_pass(std::make_shared<load_intercalation_pass>());
    manager.add_pass(std::make_shared<register_allocation_pass>(varmap));//REGISTER ALLOCATION SHOULD ALWAYS BE THE LAST PASS
    std::shared_ptr<pass_base> ic_pass =std::make_shared<instruction_counting_pass>();
    manager.add_pass(ic_pass);
    manager.analysis_passes.insert(std::make_pair ("instruction_counting", ic_pass));
    return manager;
}

#endif //FCORE_HAS_PASSES_HPP
