
add_executable(test_target test.cpp
        Instruction_classes.cpp ../src/frontend/immediate_instruction.cpp
        ../src/frontend/instruction.cpp ../src/frontend/register_operating_instruction.cpp
        ../src/frontend/independent_instruction.cpp ../src/file_parser.cpp
        ../src/frontend/Tree_visitor.cpp ../src/backend/output_writer.cpp ../src/backend/output_writer.hpp
        ../src/frontend/code_element.cpp)

target_link_libraries(test_target fs_parser)
target_link_libraries(fCore_has antlr4)
include(CTest)
include(Catch)
catch_discover_tests(test_target)
file(COPY test_add.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})