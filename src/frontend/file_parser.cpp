
#include "file_parser.h"


using namespace antlr4;
using namespace fs_parser;

parser::parser(const std::string &filename) {
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
    AST = visitor.get_program();
    var_map = visitor.get_varmap();

}
