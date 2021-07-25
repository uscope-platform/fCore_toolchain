set(TEST_SOURCES
        Instruction_classes.cpp
        ll_passes.cpp
        end_to_end_asm.cpp
        testing_main.cpp
        end_to_end_C.cpp
        C_preprocessor.cpp
        C_tree_visitor_testing.cpp
        hl_passes.cpp)


add_executable(test_target ${FCORE_SRCS} ${TEST_SOURCES} ${C_PARSER_SRCS} ${ASM_PARSER_SRCS})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(test_target PUBLIC ${GTEST_LIBRARIES} pthread antlr4-runtime)

# ASM TESTING FILES
configure_file(asm_files/test_add.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_for.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_global.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_variables.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_branch.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(asm_files/test_ldc.s ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#  C TESTING FILES
configure_file(C_files/test_pragma_io.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
    # Preprocessor
configure_file(C_files/preprocessor/test_preproc_comments.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_preproc_pragmas.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_preproc_define.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_preproc_include_fail.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_preproc_include.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/preprocessor/include_test.h ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
    # Tree visitor (ANTLR <-> AST)
configure_file(C_files/tree_visitor/test_unary_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_multiplicative_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_array.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_additive_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_shift_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_equality_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_relational_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_andb_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_orb_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_exorb_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_orl_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_andl_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_assignment_expressions.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_definition.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_function_call.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_return.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_conditional.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/tree_visitor/test_loop_ast.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#OPTIMIZATION PASSES
configure_file(C_files/test_function_inlining.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_normalization.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_intrinsics_implementation.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_division_implementation.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_full_conditional.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_pragma_io.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)