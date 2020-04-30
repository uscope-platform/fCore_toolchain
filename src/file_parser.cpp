#include "antlr4-runtime.h"
#include "../include/fs_parser/fs_grammarParser.h"
#include "../include/fs_parser/fs_grammarLexer.h"

#include "file_parser.h"
#include "Tree_visitor.hpp"
#include "code_element.hpp"
#include <string>
#include <vector>

using namespace antlr4;
using namespace fs_parser;


std::vector<uint32_t>  parse(const std::string& filename){
    std::ifstream stream;
    stream.open(filename);

    ANTLRInputStream input(stream);
    fs_grammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    fs_grammarParser parser(&tokens);

    tree::ParseTree *Tree = parser.program();
    Tree_visitor visitor;
    tree::ParseTreeWalker::DEFAULT.walk(&visitor, Tree);
    std::shared_ptr<code_element> obj_program = visitor.get_program();

    std::vector<uint32_t> program;

    for (auto & it : obj_program){
        it->print();
        program.push_back(it->emit());
    }

    return program;
}

