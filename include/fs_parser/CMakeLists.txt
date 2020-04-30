
add_library(fs_parser fs_grammarBaseListener.cpp fs_grammarBaseVisitor.cpp fs_grammarLexer.cpp fs_grammarListener.cpp fs_grammarParser.cpp fs_grammarVisitor.cpp)
target_include_directories(fs_parser PRIVATE /usr/include/antlr4-runtime)
target_include_directories(fs_parser PUBLIC /usr/local/include/antlr4-runtime)