
add_executable(test_target test.cpp
        Instruction_classes.cpp ../src/immediate_instruction.cpp
        ../src/instruction.cpp ../src/register_operating_instruction.cpp
        ../src/independent_instruction.cpp ../src/file_parser.cpp ../src/AST_visitor.cpp)

target_include_directories(test_target PUBLIC /usr/include/antlr4-runtime)
target_include_directories(test_target PUBLIC /usr/local/include/antlr4-runtime)
target_link_libraries(test_target fs_parser)
target_link_libraries(test_target antlr4-runtime)
include(CTest)
include(Catch)
catch_discover_tests(test_target)