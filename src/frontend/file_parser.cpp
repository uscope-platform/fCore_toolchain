
#include "file_parser.h"

#include <utility>


using namespace antlr4;
using namespace fs_parser;

parser::parser(const std::string &filename) {
    variable_map varmap;

    std::ifstream stream;
    stream.open(filename);
    construct_parser(stream, std::make_shared<variable_map>(varmap));
}
parser::parser(const std::string &filename, std::shared_ptr<variable_map> existing_varmap) {
    std::ifstream stream;
    stream.open(filename);

    construct_parser(stream, std::move(existing_varmap));
}

void parser::construct_parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap){


    ANTLRInputStream input(stream);
    fs_grammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    fs_grammarParser parser(&tokens);

    tree::ParseTree *Tree = parser.program();
    Tree_visitor visitor(std::move(existing_varmap));
    tree::ParseTreeWalker::DEFAULT.walk(&visitor, Tree);
    AST = visitor.get_program();
}

