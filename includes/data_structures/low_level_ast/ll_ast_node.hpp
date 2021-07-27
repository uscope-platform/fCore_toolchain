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

#ifndef FCORE_TOOLCHAIN_LL_AST_NODE_HPP
#define FCORE_TOOLCHAIN_LL_AST_NODE_HPP

#include <vector>
#include <cstdint>
#include <memory>
#include <iostream>
#include <utility>

#include "tools/variable.hpp"
#include "data_structures/ast_node_base.hpp"


typedef enum {
    ll_type_instr = 1,
    ll_type_for_block = 4,
    ll_type_program_head = 5,
    ll_type_pragma = 6,
    ll_type_code_block = 7,

} ll_ast_node_type_t;


class ll_ast_node : public ast_node_base<ll_ast_node> {

public:
    ll_ast_node();
    explicit ll_ast_node(ll_ast_node_type_t block_type);

    virtual bool is_terminal();
    static std::shared_ptr<ll_ast_node> deep_copy_element(const std::shared_ptr<ll_ast_node>& element);
    bool compare_content_by_type(const std::shared_ptr<ll_ast_node> &lhs, const std::shared_ptr<ll_ast_node> &rhs);
    ll_ast_node_type_t type;

    friend bool operator==(const ll_ast_node& lhs, const ll_ast_node& rhs);


};





#endif //FCORE_TOOLCHAIN_LL_AST_NODE_HPP
