
find_package(Catch2 REQUIRED PATH)

add_executable(test_target test.cpp
        Instruction_classes.cpp ../src/code_elements/instruction.cpp ../src/frontend/file_parser.cpp
        ../src/frontend/Tree_visitor.cpp ../src/backend/output_generator.cpp ../includes/fcore_has/backend/output_generator.hpp
        ../src/code_elements/code_element.cpp ../src/passes/pass_manager.cpp ../includes/fcore_has/passes/pass_manager.hpp
        ../src/passes/loop_implementation_pass.cpp ../src/code_elements/for_loop.cpp
        ../src/code_elements/variable.cpp ../includes/fcore_has/code_elements/variable.hpp
        ../src/passes/pseudo_instructions_pass.cpp passes.cpp end_to_end.cpp
        ../src/passes/register_allocation_pass.cpp ../includes/fcore_has/passes/register_allocation_pass.hpp
        ../src/passes/variable_lifetime_mapping.cpp ../includes/fcore_has/passes/variable_lifetime_mapping.hpp
        ../src/passes/load_intercalation_pass.cpp ../includes/fcore_has/passes/load_intercalation_pass.hpp
        ../src/passes/instruction_counting_pass.cpp ../src/frontend/variable_map.cpp
        ../includes/fcore_has/frontend/variable_map.hpp ../src/frontend/register_map.cpp ../includes/fcore_has/frontend/register_map.hpp
        ../src/fcore_has.cpp ../includes/fcore_has/fcore_has.hpp
        ../src/frontend/ErrorHandling.cpp ../includes/fcore_has/frontend/ErrorHandling.hpp)

target_link_libraries(test_target Catch2::Catch2)
target_link_libraries(test_target fs_parser)



file(COPY asm_files/test_add.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_for.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_global.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_variables.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_branch.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/test_ldc.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY asm_files/register_defs.s DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
