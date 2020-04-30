
add_executable(test_target test.cpp
        Instruction_classes.cpp ../src/immediate_instruction.cpp
        ../src/instruction.cpp ../src/register_operating_instruction.cpp
        ../src/independent_instruction.cpp ../src/file_parser.cpp ../src/Tree_visitor.cpp ../src/output_writer.cpp ../src/output_writer.hpp)

target_link_libraries(test_target fs_parser)
target_link_libraries(fCore_has antlr4)
include(CTest)
include(Catch)
catch_discover_tests(test_target)
file(COPY test_add.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})