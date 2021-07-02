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

#include <utility>



using namespace antlr4;

C_language_parser::C_language_parser(){
    vmap = std::make_shared<variable_map>();
    dmap = std::make_shared<define_map>();
}

C_language_parser::C_language_parser(std::istream &stream, std::shared_ptr<variable_map> &existing_varmap, std::shared_ptr<define_map> &existing_defmap) {
    vmap = existing_varmap;
    dmap = existing_defmap;
    preproc = std::make_unique<C_pre_processor>(stream, vmap,dmap);

}


void C_language_parser::pre_process(const std::vector<std::string> &abs_includes, const std::vector<std::string> &rel_includes) {
    preproc->set_absolute_includes(abs_includes);
    preproc->set_relative_includes(rel_includes);
    preproc->process_file();
    preprocessed_content = preproc->get_preprocessed_file();
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

}
