
add_executable(test test.cpp catch.hpp
        Instruction_classes.cpp ../src/immediate_instruction.cpp
        ../src/instruction.cpp ../src/register_operating_instruction.cpp
        ../src/independent_instruction.cpp ../src/file_parser.cpp ../src/AST_visitor.cpp)

target_include_directories(test PUBLIC /usr/include/antlr4-runtime)
target_link_libraries(test fs_parser)
target_link_libraries(test antlr4-runtime)
