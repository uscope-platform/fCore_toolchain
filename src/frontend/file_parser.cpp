
#include "file_parser.h"


using namespace antlr4;
using namespace fs_parser;


std::shared_ptr<code_element> parse(const std::string& filename){
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
    std::shared_ptr<code_element> AST = visitor.get_program();

    return AST;

}

