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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.06/07/2021.
//

#ifndef FCORE_TOOLCHAIN_LL_PASS_MANAGER_HPP
#define FCORE_TOOLCHAIN_LL_PASS_MANAGER_HPP

#include "passes/pass_manager_base.hpp"
#include "ast/low_level/ll_ast_node.hpp"
#include "passes/pass_base.hpp"

class ll_pass_manager : public pass_manager_base<ll_ast_node> {
public:
    void run_morphing_pass( std::shared_ptr<ll_ast_node> subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass) override;
    std::vector<std::shared_ptr<ll_ast_node>> process_nodes(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass);
    std::shared_ptr<ll_ast_node> process_leaves(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass);

};


#endif //FCORE_TOOLCHAIN_LL_PASS_MANAGER_HPP
