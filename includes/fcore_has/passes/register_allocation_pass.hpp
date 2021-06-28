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

#ifndef FCORE_HAS_REGISTER_ALLOCATION_PASS_HPP
#define FCORE_HAS_REGISTER_ALLOCATION_PASS_HPP

#include <memory>
#include <unordered_map>
#include "fcore_has/frontend/asm/variable_map.hpp"
#include "fcore_has/frontend/asm/register_map.hpp"
#include "fcore_has/code_elements/code_element.hpp"
#include "pass_manager.hpp"
#include "fcore_has/fCore_isa.hpp"


class register_allocation_pass: public pass_base {
    public:
        explicit register_allocation_pass(std::shared_ptr<variable_map> varmap);
        ast_t process_leaf(ast_t element) override ;
        int get_pass_type() override { return LEAF_PASS;};
private:
    bool used[16] = {false};
    std::unordered_map<std::shared_ptr<variable>, std::shared_ptr<variable>> register_mapping;
    register_map reg_map;
    std::shared_ptr<variable_map> var_map;
};


#endif //FCORE_HAS_REGISTER_ALLOCATION_PASS_HPP
