
add_executable(test_target test.cpp
        Instruction_classes.cpp ../src/code_elements/instruction.cpp ../src/frontend/file_parser.cpp
        ../src/frontend/Tree_visitor.cpp ../src/backend/output_writer.cpp ../src/backend/output_writer.hpp
        ../src/code_elements/code_element.cpp ../src/passes/pass_manager.cpp ../src/passes/pass_manager.hpp
        ../src/passes/loop_implementation_pass.cpp ../src/code_elements/for_loop.cpp passes.cpp end_to_end.cpp)

target_link_libraries(test_target fs_parser)
include(CTest)
include(Catch)
catch_discover_tests(test_target)

file(COPY test_add.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY test_for.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})