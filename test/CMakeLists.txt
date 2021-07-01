set(TESTED_SOURCES
        ../src/backend/output_generator.cpp
        ../src/code_elements/ll_ast/ll_ast_node.cpp
        ../src/code_elements/ll_ast/ll_loop.cpp
        ../src/code_elements/ll_ast/ll_instruction.cpp
        ../src/code_elements/hl_ast/hl_ast_node.cpp
        ../src/code_elements/hl_ast/hl_identifier_node.cpp
        ../src/code_elements/hl_ast/hl_function_node.cpp
        ../src/code_elements/hl_ast/hl_expression_node.cpp
        ../src/code_elements/hl_ast/hl_ast_operand.cpp
        ../src/code_elements/variable.cpp
        ../src/code_elements/define.cpp
        ../src/passes/pass_manager.cpp
        ../src/passes/loop_implementation_pass.cpp
        ../src/passes/pseudo_instructions_pass.cpp
        ../src/passes/register_allocation_pass.cpp
        ../src/passes/variable_lifetime_mapping.cpp
        ../src/passes/load_intercalation_pass.cpp
        ../src/passes/instruction_counting_pass.cpp
        ../src/frontend/variable_map.cpp
        ../src/frontend/define_map.cpp
        ../src/frontend/asm/register_map.cpp
        ../src/frontend/asm/AsmErrorHandling.cpp
        ../src/frontend/asm/asm_language_parser.cpp
        ../src/frontend/asm/AsmTree_visitor.cpp
        ../src/frontend/C/C_language_parser.cpp
        ../src/frontend/C/C_ErrorHandling.cpp
        ../src/frontend/C/C_Tree_visitor.cpp
        ../src/frontend/C/C_pre_processor.cpp
        ../src/fcore_has.cpp
        ../src/fcore_cc.cpp
        )


set(TEST_SOURCES
        Instruction_classes.cpp
        passes.cpp
        end_to_end_asm.cpp
        testing_main.cpp
        end_to_end_C.cpp
        C_preprocessor.cpp
        C_tree_visitor.cpp
        )


add_executable(test_target ${TESTED_SOURCES} ${TEST_SOURCES})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(test_target ${GTEST_LIBRARIES} pthread asm_parser_lib)
target_link_libraries(test_target ${GTEST_LIBRARIES} pthread c_parser)

# ASM TESTING FILES
configure_file(asm_files/test_add.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_for.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_global.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_variables.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_branch.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_ldc.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/register_defs.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#  C TESTING FILES
configure_file(C_files/test_main_add.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_preproc_comments.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_preproc_pragmas.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_preproc_define.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_preproc_include_fail.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_preproc_include.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_unary_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/include_test.h ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)