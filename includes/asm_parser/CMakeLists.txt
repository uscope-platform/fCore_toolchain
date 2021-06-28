set(FCORE_PARSER_LIB_SRCS
        asm_grammarBaseListener.cpp
        asm_grammarBaseVisitor.cpp
        asm_grammarLexer.cpp
        asm_grammarListener.cpp
        asm_grammarParser.cpp
        asm_grammarVisitor.cpp
        )

add_library(asm_parser_lib ${FCORE_PARSER_LIB_SRCS})
target_link_libraries(asm_parser_lib antlr4-runtime)

add_library(asm_parser_libs STATIC ${FCORE_PARSER_LIB_SRCS})
set_property(TARGET asm_parser_libs PROPERTY POSITION_INDEPENDENT_CODE 1)



