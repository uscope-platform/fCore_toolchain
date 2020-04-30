
add_library(fs_parser ../antlr4-runtime/antlr4-runtime.h fs_grammarBaseListener.cpp fs_grammarBaseVisitor.cpp fs_grammarLexer.cpp fs_grammarListener.cpp fs_grammarParser.cpp fs_grammarVisitor.cpp)


target_link_libraries(fs_parser antlr4)