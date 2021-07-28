set(FCORE_SRCS_I
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/asm/AsmTree_visitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/asm/asm_language_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/asm/AsmErrorHandling.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/C/C_language_parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/C/C_pre_processor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/C/C_ErrorHandling.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/C/C_Tree_visitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/frontend/asm/register_map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/backend/output_generator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_instruction_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_loop_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_ast_pragma.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/low_level_ast/ll_ast_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_ast_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_definition_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_function_def_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_ast_loop_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_ast_conditional_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_expression_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_function_call_node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/high_level_ast/hl_ast_operand.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data_structures/instruction_stream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/high_level_ast_lowering.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/instruction_stream_builder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/expression_evaluator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/define.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/variable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/variable_map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tools/define_map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/ll_pass_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/loop_implementation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/pseudo_instructions_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/instruction_counting_pass.cpp#
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/register_allocation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/variable_lifetime_mapping.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/low_level/load_intercalation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/constant_folding_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/constant_propagation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/hl_pass_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/hl_variable_mapping.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/function_mapping.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/inlined_function_elimination.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/inline_constant_extraction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/intrinsics_implementation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/function_inlining_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/division_implementation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/dead_variable_elimination.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/declaration_instantiation_combining_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/conditional_implementation_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/loop_unrolling_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/passes/high_level/normalization_pass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fcore_has.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fcore_cc.cpp
        )

set(FCORE_SRCS ${FCORE_SRCS_I} PARENT_SCOPE)


# Standalone assembler executable
add_executable(fCore_has ${FCORE_SRCS_I} ${C_PARSER_SRCS} ${ASM_PARSER_SRCS} fcore_has_main.cpp)
target_link_libraries(fCore_has PUBLIC antlr4-runtime)

# Standalone assembler executable
add_executable(fCore_cc ${FCORE_SRCS_I} ${C_PARSER_SRCS} ${ASM_PARSER_SRCS} fcore_cc_main.cpp)
target_link_libraries(fCore_cc PUBLIC antlr4-runtime)

install(TARGETS fCore_has DESTINATION /usr/bin)
install(TARGETS fCore_cc DESTINATION /usr/bin)