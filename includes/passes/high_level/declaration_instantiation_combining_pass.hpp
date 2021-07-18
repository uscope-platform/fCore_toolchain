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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.05/07/2021.
//


#ifndef FCORE_TOOLCHAIN_DECLARATION_INSTANTIATION_COMBINING_PASS_HPP
#define FCORE_TOOLCHAIN_DECLARATION_INSTANTIATION_COMBINING_PASS_HPP

#include "passes/pass_base.hpp"
#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "ast/high_level/hl_expression_node.hpp"

class declaration_instantiation_combining_pass : public pass_base<hl_ast_node> {
public:
    declaration_instantiation_combining_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};
};


#endif //FCORE_TOOLCHAIN_DECLARATION_INSTANTIATION_COMBINING_PASS_HPP
