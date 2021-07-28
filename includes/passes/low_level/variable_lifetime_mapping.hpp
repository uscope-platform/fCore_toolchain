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

#ifndef FCORE_TOOLCHAIN_VARIABLE_LIFETIME_MAPPING_HPP
#define FCORE_TOOLCHAIN_VARIABLE_LIFETIME_MAPPING_HPP

#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "tools/variable_map.hpp"
#include "passes/pass_base.hpp"

#include <utility>

class variable_lifetime_mapping: public pass_base<ll_ast_node> {
public:
    explicit variable_lifetime_mapping(std::shared_ptr<variable_map> var_map);
    std::shared_ptr<ll_ast_node> process_leaf(std::shared_ptr<ll_ast_node> element) override ;
    int get_pass_type() override { return LEAF_PASS;};
private:
    int variable_detection_ctr;
    std::shared_ptr<variable_map> vmap;
};



#endif //FCORE_TOOLCHAIN_VARIABLE_LIFETIME_MAPPING_HPP
