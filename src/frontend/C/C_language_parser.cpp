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

#include "frontend/C/C_language_parser.h"

using namespace antlr4;

C_language_parser::C_language_parser(std::istream &stream) {
    variable_map varmap;

    construct_parser(stream, std::make_shared<variable_map>(varmap));
}

C_language_parser::C_language_parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap) {

    construct_parser(stream, std::move(existing_varmap));
}

void C_language_parser::construct_parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap){

    pre_processor(stream, existing_varmap);

    ANTLRInputStream input(stream);

    C_parser::C_grammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    C_parser::C_grammarParser parser(&tokens);
    C_ErrorHandling handler;
    parser.addErrorListener(&handler);
    tree::ParseTree *Tree = parser.compilationUnit();
    C_Tree_visitor visitor(std::move(existing_varmap));
    tree::ParseTreeWalker::DEFAULT.walk(&visitor, Tree);
    AST = visitor.get_program();

}

void C_language_parser::pre_processor(std::istream &stream, const std::shared_ptr<variable_map>& existing_varmap) {
    std::string line;
    std::ostringstream decommented_file;

    std::regex multiline_comment_start("^\\/\\*");
    std::regex multiline_comment_end("^\\*\\/");
    std::regex line_comment("^\\*\\/");
    while (std::getline(stream,line)){

        decommented_file << line + "/n";
    }

}