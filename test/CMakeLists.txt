set(TESTED_SOURCES
        ../src/code_elements/instruction.cpp
        ../src/frontend/asm/file_parser.cpp
        ../src/frontend/asm/Tree_visitor.cpp
        ../src/backend/output_generator.cpp
        ../src/code_elements/code_element.cpp
        ../src/passes/pass_manager.cpp
        ../src/passes/loop_implementation_pass.cpp
        ../src/code_elements/for_loop.cpp
        ../src/code_elements/variable.cpp
        ../src/passes/pseudo_instructions_pass.cpp
        ../src/passes/register_allocation_pass.cpp
        ../src/passes/variable_lifetime_mapping.cpp
        ../src/passes/load_intercalation_pass.cpp
        ../src/passes/instruction_counting_pass.cpp
        ../src/frontend/variable_map.cpp
        ../src/frontend/asm/register_map.cpp
        ../src/fcore_has.cpp
        ../src/frontend/asm/ErrorHandling.cpp
        )


set(TEST_SOURCES
        Instruction_classes.cpp
        passes.cpp
        end_to_end.cpp
        )

add_executable(test_target ${TESTED_SOURCES} ${TEST_SOURCES})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(test_target ${GTEST_LIBRARIES} pthread asm_parser_lib)


configure_file(asm_files/test_add.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_for.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_global.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_variables.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_branch.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_ldc.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/register_defs.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)



