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

#include "frontend/asm/asm_language_parser.hpp"



using namespace antlr4;

namespace fcore{

    result<void> asm_language_parser::parse(std::istream &stream){

        ANTLRInputStream input(stream);
        asm_parser::asm_grammarLexer lexer(&input);
        CommonTokenStream tokens(&lexer);

        tokens.fill();
        asm_parser::asm_grammarParser parser(&tokens);
        syntax_error_collector handler;
        parser.addErrorListener(&handler);
        tree::ParseTree *Tree = parser.program();
        if(auto syntax = handler.status(); !syntax) return syntax;

        AsmTree_visitor visitor(existing_varmap);
        tree::ParseTreeWalker::DEFAULT.walk(&visitor, Tree);
        program = visitor.get_program();
        return {};
    }
}
