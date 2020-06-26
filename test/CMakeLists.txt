
add_executable(test_target test.cpp
        Instruction_classes.cpp ../src/code_elements/instruction.cpp ../src/frontend/file_parser.cpp
        ../src/frontend/Tree_visitor.cpp ../src/backend/output_writer.cpp ../src/backend/output_writer.hpp
        ../src/code_elements/code_element.cpp ../src/passes/pass_manager.cpp ../src/passes/pass_manager.hpp
        ../src/passes/loop_implementation_pass.cpp ../src/code_elements/for_loop.cpp
        ../src/code_elements/variable.cpp ../src/code_elements/variable.hpp
        ../src/passes/pseudo_instructions_pass.cpp passes.cpp end_to_end.cpp
        ../src/passes/register_allocation_pass.cpp ../src/passes/register_allocation_pass.hpp
        ../src/passes/variable_lifetime_mapping.cpp ../src/passes/variable_lifetime_mapping.hpp
        ../src/passes/load_intercalation_pass.cpp ../src/passes/load_intercalation_pass.hpp
        ../src/passes/instruction_counting_pass.cpp ../src/frontend/variable_map.cpp
        ../src/frontend/variable_map.hpp ../src/frontend/register_map.cpp ../src/frontend/register_map.hpp)

target_link_libraries(test_target fs_parser)
include(CTest)
include(Catch)
catch_discover_tests(test_target)

file(COPY asm_files/test_add.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_for.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_global.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_variables.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_branch.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_ldc.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/register_defs.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
