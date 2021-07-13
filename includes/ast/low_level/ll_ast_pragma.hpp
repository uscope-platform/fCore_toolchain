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

#ifndef FCORE_TOOLCHAIN_LL_AST_PRAGMA_HPP
#define FCORE_TOOLCHAIN_LL_AST_PRAGMA_HPP

#include <string>

#include "ll_ast_node.hpp"

class ll_ast_pragma :public ll_ast_node{
public:
    ll_ast_pragma();
    explicit ll_ast_pragma(std::string directive);
    std::string get_directive();
    bool is_terminal() override;
    friend bool operator==(const ll_ast_pragma& lhs, const ll_ast_pragma& rhs);
    void print();
private:
    std::string directive;
};


#endif //FCORE_TOOLCHAIN_LL_AST_PRAGMA_HPP
