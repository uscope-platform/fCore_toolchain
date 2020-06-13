
#include "file_parser.h"


using namespace antlr4;
using namespace fs_parser;

parser::parser(const std::string &filename) {
    varmap_t varmap;
    construct_parser(filename, varmap);
}

parser::parser(const std::string &filename, varmap_t &existing_varmap) {
    construct_parser(filename, existing_varmap);
}

void parser::construct_parser(const std::string &filename, varmap_t &existing_varmap){
    std::ifstream stream;
    stream.open(filename);

    ANTLRInputStream input(stream);
    fs_grammarLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    fs_grammarParser parser(&tokens);

    tree::ParseTree *Tree = parser.program();
    Tree_visitor visitor;
    visitor.set_varmap(existing_varmap);
    tree::ParseTreeWalker::DEFAULT.walk(&visitor, Tree);
    AST = visitor.get_program();
    var_map = visitor.get_varmap();
}

