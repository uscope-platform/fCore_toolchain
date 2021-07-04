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

#ifndef FCORE_HAS_VARIABLE_LIFETIME_MAPPING_HPP
#define FCORE_HAS_VARIABLE_LIFETIME_MAPPING_HPP


#include "code_elements/ll_ast/ll_ast_node.hpp"
#include "frontend/variable_map.hpp"
#include "pass_manager.hpp"

#include <utility>

class variable_lifetime_mapping: public pass_base {
public:
    explicit variable_lifetime_mapping(std::shared_ptr<variable_map> var_map);
    ast_t process_leaf(ast_t element) override ;
    int get_pass_type() override { return LEAF_PASS;};
private:
    int variable_detection_ctr;
    std::shared_ptr<variable_map> vmap;
};



#endif //FCORE_HAS_VARIABLE_LIFETIME_MAPPING_HPP