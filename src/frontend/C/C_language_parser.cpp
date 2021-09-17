// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
