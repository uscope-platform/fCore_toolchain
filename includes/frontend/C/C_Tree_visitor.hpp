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
#include <stack>

#include "C_parser/C_grammarBaseListener.h"
#include "C_parser/C_grammarParser.h"
#include "code_elements/variable.hpp"
#include "frontend/variable_map.hpp"

#include "code_elements/hl_ast/hl_function_node.h"
#include "code_elements/hl_ast/hl_identifier_node.h"
#include "code_elements/hl_ast/hl_ast_node.h"


typedef std::unordered_map<std::string, std::shared_ptr<variable>>  varmap_t;

class C_Tree_visitor : public  C_parser::C_grammarBaseListener{
public:
    explicit C_Tree_visitor(std::shared_ptr<variable_map> map);

    void enterFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) override;
    void exitFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) override;

    void exitParameterDeclaration(C_parser::C_grammarParser::ParameterDeclarationContext *ctx) override;

    void exitDeclarationSpecifiers(C_parser::C_grammarParser::DeclarationSpecifiersContext *ctx) override;

private:

    std::shared_ptr<variable_map> varmap;

    std::stack<std::string> declaration_type;
    std::vector<std::shared_ptr<hl_identifier_node>> parameters_list;
    std::vector<std::shared_ptr<hl_function_node>> functions;
    bool in_function_declaration;
};

#endif //FCORE_HAS_ASMTREE_VISITOR_HPP
