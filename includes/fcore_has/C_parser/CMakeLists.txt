set(C_PARSER_LIB_SRCS /
        C_grammarBaseListener.cpp /
        C_grammarBaseVisitor.cpp /
        C_grammarLexer.cpp /
        C_grammarListener.cpp /
        C_grammarParser.cpp /
        C_grammarVisitor.cpp)

add_library(c_parser SHARED ${C_PARSER_LIB_SRCS})
target_link_libraries(c_parser antlr4-runtime)

add_library(c_perser_s STATIC ${C_PARSER_LIB_SRCS})
set_property(TARGET c_perser_s PROPERTY POSITION_INDEPENDENT_CODE 1)



