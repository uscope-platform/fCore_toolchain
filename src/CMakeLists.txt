
add_executable(fCore_has main.cpp instruction.cpp instruction.h
        immediate_instruction.cpp immediate_instruction.h register_operating_instruction.cpp
        register_operating_instruction.h AST_visitor.cpp AST_visitor.hpp ../include/fCore_isa.hpp
        independent_instruction.cpp independent_instruction.hpp file_parser.cpp file_parser.h)

target_include_directories(fCore_has PUBLIC /usr/include/antlr4-runtime)
target_link_libraries(fCore_has fs_parser)
target_link_libraries(fCore_has antlr4-runtime)