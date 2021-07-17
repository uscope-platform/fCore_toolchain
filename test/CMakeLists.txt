set(TESTED_SOURCES
        ../src/backend/output_generator.cpp
        ../src/ast/low_level/ll_ast_node.cpp
        ../src/ast/low_level/ll_loop_node.cpp
        ../src/ast/low_level/ll_instruction_node.cpp
        ../src/ast/low_level/ll_ast_pragma.cpp
        ../src/ast/high_level/hl_ast_node.cpp
        ../src/ast/high_level/hl_definition_node.cpp
        ../src/ast/high_level/hl_function_def_node.cpp
        ../src/ast/high_level/hl_expression_node.cpp
        ../src/ast/high_level/hl_ast_operand.cpp
        ../src/ast/high_level/hl_function_call_node.cpp
        ../src/ast/transformations/high_level_ast_lowering.cpp
        ../src/ast/variable.cpp
        ../src/ast/define.cpp
        ../src/passes/low_level/ll_pass_manager.cpp
        ../src/passes/low_level/loop_implementation_pass.cpp
        ../src/passes/low_level/pseudo_instructions_pass.cpp
        ../src/passes/low_level/register_allocation_pass.cpp
        ../src/passes/low_level/variable_lifetime_mapping.cpp
        ../src/passes/low_level/load_intercalation_pass.cpp
        ../src/passes/low_level/instruction_counting_pass.cpp
        ../src/passes/high_level/dead_variable_elimination.cpp
        ../src/passes/high_level/hl_variable_mapping.cpp
        ../src/passes/high_level/declaration_instantiation_combining_pass.cpp
        ../src/passes/high_level/hl_pass_manager.cpp
        ../src/passes/high_level/function_inlining_pass.cpp
        ../src/passes/high_level/normalization_pass.cpp
        ../src/passes/high_level/inlined_function_elimination.cpp
        ../src/passes/high_level/function_mapping.cpp
        ../src/passes/high_level/intrinsics_implementation_pass.cpp
        ../src/passes/high_level/division_implementation_pass.cpp
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
        ll_passes.cpp
        end_to_end_asm.cpp
        testing_main.cpp
        end_to_end_C.cpp
        C_preprocessor.cpp
        C_tree_visitor_testing.cpp
        hl_passes.cpp)


add_executable(test_target ${TESTED_SOURCES} ${TEST_SOURCES} ${C_PARSER_SRCS} ${ASM_PARSER_SRCS})

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
configure_file(C_files/test_pragma_io.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
#OPTIMIZATION PASSES
configure_file(C_files/test_function_inlining.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_normalization.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_intrinsics_implementation.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(C_files/test_division_implementation.c ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)