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

#ifndef FCORE_HAS_DIVISION_IMPLEMENTATION_PASS_HPP
#define FCORE_HAS_DIVISION_IMPLEMENTATION_PASS_HPP

#include "ast/high_level/hl_expression_node.hpp"
#include "ast/high_level/hl_ast_node.hpp"
#include "passes/pass_base.hpp"

class division_implementation_pass :public pass_base<hl_ast_node> {
public:
    division_implementation_pass();
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return LEAF_PASS;};
};




#endif //FCORE_HAS_DIVISION_IMPLEMENTATION_PASS_HPP
