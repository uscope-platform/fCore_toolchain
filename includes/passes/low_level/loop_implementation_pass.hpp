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

#ifndef FCORE_TOOLCHAIN_LOOP_IMPLEMENTATION_PASS_HPP
#define FCORE_TOOLCHAIN_LOOP_IMPLEMENTATION_PASS_HPP

#include <memory>
#include "ast/low_level/ll_ast_node.hpp"
#include "ast/low_level/ll_loop_node.hpp"
#include "ast/low_level/ll_ast_pragma.hpp"
#include "passes/pass_base.hpp"

class loop_implementation_pass : public pass_base<ll_ast_node> {

public:
    loop_implementation_pass();
    std::vector<std::shared_ptr<ll_ast_node>>process_node(std::shared_ptr<ll_ast_node> element) override;
    int get_pass_type() override { return NODE_PASS;};
};


#endif //FCORE_TOOLCHAIN_LOOP_IMPLEMENTATION_PASS_HPP
