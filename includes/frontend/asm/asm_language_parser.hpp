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

#ifndef FCORE_TOOLCHAIN_ASM_LANGUAGE_PARSER_HPP
#define FCORE_TOOLCHAIN_ASM_LANGUAGE_PARSER_HPP

#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include "ast/low_level/ll_ast_node.hpp"
#include "AsmTree_visitor.hpp"
#include "ast/low_level/ll_ast_node.hpp"
#include "AsmErrorHandling.hpp"

#include "antlr4-runtime.h"
#include "asm_parser/asm_grammarLexer.h"
#include "asm_parser/asm_grammarParser.h"

class asm_language_parser{
    public:
    explicit asm_language_parser(std::istream &stream);
    asm_language_parser(std::istream &stream, std::shared_ptr<variable_map> new_varmap);
    void construct_parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap);

    unsigned int n_inputs() const {return n_inputs_;};
    unsigned int n_outputs() const {return n_outputs_;};
    unsigned int n_variables() const {return n_variables_;};

    std::shared_ptr<ll_ast_node> AST;
    varmap_t var_map;

    std::string error;


    private:

    unsigned int n_inputs_ = 0;
    unsigned int n_outputs_ = 0;
    unsigned int n_variables_ = 0;
};


#endif //FCORE_TOOLCHAIN_ASM_LANGUAGE_PARSER_HPP
