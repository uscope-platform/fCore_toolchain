set(FCORE_PARSER_LIB_SRCS asm_grammarBaseListener.cpp asm_grammarBaseVisitor.cpp asm_grammarLexer.cpp asm_grammarListener.cpp asm_grammarParser.cpp asm_grammarVisitor.cpp)
add_library(fs_parser ${FCORE_PARSER_LIB_SRCS})
target_link_libraries(fs_parser antlr4-runtime)

add_library(fcparser STATIC ${FCORE_PARSER_LIB_SRCS})
set_property(TARGET fcparser PROPERTY POSITION_INDEPENDENT_CODE 1)



