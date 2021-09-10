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

#include "frontend/C/C_language_parser.hpp"

#include <utility>



using namespace antlr4;

C_language_parser::C_language_parser(){
    dmap = std::make_shared<define_map>();
}

C_language_parser::C_language_parser(std::string &path, std::shared_ptr<define_map> &existing_defmap) {
    dmap = existing_defmap;
    preproc = std::make_unique<C_pre_processor>(path,dmap);

}


void C_language_parser::pre_process(const std::vector<std::string> &abs_includes) {
    preproc->set_absolute_includes(abs_includes);
    preproc->process_file();
    preproc->substitute_defines();
    preprocessed_content = preproc->get_preprocessed_file();
    visitor.set_iom_map( preproc->get_iom_map());
}

void C_language_parser::parse() {

    std::istringstream ss(preprocessed_content);
    ANTLRInputStream input(ss);

    C_parser::C_grammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    C_parser::C_grammarParser parser(&tokens);
    C_ErrorHandling handler;
    parser.addErrorListener(&handler);
    tree::ParseTree *Tree = parser.compilationUnit();
    tree::ParseTreeWalker::DEFAULT.walk(&visitor, Tree);
    AST = visitor.get_ast();
}
