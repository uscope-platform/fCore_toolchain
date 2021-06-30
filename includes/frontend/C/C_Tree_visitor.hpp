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

#ifndef FCORE_HAS_ASMTREE_VISITOR_HPP
#define FCORE_HAS_TREE_VISITOR_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "C_parser/C_grammarBaseListener.h"
#include "C_parser/C_grammarParser.h"
#include "fCore_isa.hpp"
#include "code_elements/ll_ast/ll_instruction.h"
#include "code_elements/ll_ast/ll_loop.hpp"
#include "code_elements/ll_ast/ll_ast_node.hpp"
#include "code_elements/variable.hpp"
#include "frontend/variable_map.hpp"




typedef std::unordered_map<std::string, std::shared_ptr<variable>>  varmap_t;

class C_Tree_visitor : public  C_parser::C_grammarBaseListener{
public:
    explicit C_Tree_visitor(std::shared_ptr<variable_map> map);
    ast_t get_program();

private:
    ast_t program_head{};
    ast_t current_element{};
    std::stack<ast_t> parent_elements;
    std::shared_ptr<variable_map> varmap;

    std::shared_ptr<variable> get_variable(const std::string &variable_name, bool is_const) const;
};

#endif //FCORE_HAS_ASMTREE_VISITOR_HPP
