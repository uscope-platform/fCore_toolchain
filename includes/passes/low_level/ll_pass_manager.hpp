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
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.06/07/2021.
//

#ifndef FCORE_HAS_LL_PASS_MANAGER_HPP
#define FCORE_HAS_LL_PASS_MANAGER_HPP

#include "passes/pass_manager_base.hpp"
#include "ast/low_level/ll_ast_node.hpp"
#include "passes/pass_base.hpp"

class ll_pass_manager : public pass_manager_base<ll_ast_node> {
public:
    std::shared_ptr<ll_ast_node> run_morphing_pass(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass) override;
    std::vector<std::shared_ptr<ll_ast_node>> process_nodes(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass);
    std::shared_ptr<ll_ast_node> process_leaves(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base<ll_ast_node>>& pass);

};


#endif //FCORE_HAS_LL_PASS_MANAGER_HPP
