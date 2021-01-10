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

#include "fcore_has/frontend/file_parser.h"

#include <utility>


using namespace antlr4;
using namespace fs_parser;

parser::parser(std::istream &stream) {
    variable_map varmap;

    construct_parser(stream, std::make_shared<variable_map>(varmap));
}

parser::parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap) {

    construct_parser(stream, std::move(existing_varmap));
}

void parser::construct_parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap){


    ANTLRInputStream input(stream);
    fs_grammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    fs_grammarParser parser(&tokens);
    ErrorHandling handler;
    parser.addErrorListener(&handler);
    tree::ParseTree *Tree = parser.program();
    Tree_visitor visitor(std::move(existing_varmap));
    tree::ParseTreeWalker::DEFAULT.walk(&visitor, Tree);
    AST = visitor.get_program();

}