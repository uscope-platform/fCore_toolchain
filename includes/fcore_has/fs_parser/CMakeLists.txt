set(FCORE_PARSER_LIB_SRCS fs_grammarBaseListener.cpp fs_grammarBaseVisitor.cpp fs_grammarLexer.cpp fs_grammarListener.cpp fs_grammarParser.cpp fs_grammarVisitor.cpp)
add_library(fs_parser ${FCORE_PARSER_LIB_SRCS})
target_link_libraries(fs_parser antlr4-runtime)

add_library(fcparser STATIC ${FCORE_PARSER_LIB_SRCS})
set_property(TARGET fcparser PROPERTY POSITION_INDEPENDENT_CODE 1)



