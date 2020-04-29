#include "antlr4-runtime.h"
#include "instruction.h"
#include "AST_visitor.hpp"
#include "../include/fs_parser/fs_grammarParser.h"
#include "../include/fs_parser/fs_grammarLexer.h"

#include "file_parser.h"

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

    tree::ParseTree *AST = parser.code();
    AST_visitor visitor;
    tree::ParseTreeWalker::DEFAULT.walk(&visitor, AST);
    std::vector<std::shared_ptr<instruction>> obj_program = visitor.get_program();

    std::vector<uint32_t> program;

    for (auto & it : obj_program){
        it->print();
        program.push_back(it->emit());
    }

    return program;
}

