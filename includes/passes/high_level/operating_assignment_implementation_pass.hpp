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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.08/07/2021.
//

#ifndef FCORE_TOOLCHAIN_OPERATING_ASSIGNMENT_IMPLEMENTATION_PASS_H
#define FCORE_TOOLCHAIN_OPERATING_ASSIGNMENT_IMPLEMENTATION_PASS_H

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/pass_base.hpp"

class operating_assignment_implementation_pass : public pass_base<hl_ast_node> {
public:
    operating_assignment_implementation_pass();
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return LEAF_PASS;};
private:
    static std::shared_ptr<hl_expression_node> create_top_expression(assignment_type_t a);
};


#endif //FCORE_TOOLCHAIN_OPERATING_ASSIGNMENT_IMPLEMENTATION_PASS_H
