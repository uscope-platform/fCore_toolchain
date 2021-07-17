set(FCORE_LIB_SRCS
        frontend/asm/AsmTree_visitor.cpp
        frontend/asm/asm_language_parser.cpp
        frontend/asm/AsmErrorHandling.cpp
        frontend/C/C_language_parser.cpp
        frontend/C/C_pre_processor.cpp
        frontend/C/C_ErrorHandling.cpp
        frontend/C/C_Tree_visitor.cpp
        frontend/variable_map.cpp
        frontend/define_map.cpp
        frontend/asm/register_map.cpp
        backend/output_generator.cpp
        ast/low_level/ll_instruction_node.cpp
        ast/low_level/ll_loop_node.cpp
        ast/low_level/ll_ast_pragma.cpp
        ast/low_level/ll_ast_node.cpp
        ast/high_level/hl_ast_node.cpp
        ast/high_level/hl_definition_node.cpp
        ast/high_level/hl_function_def_node.cpp
        ast/high_level/hl_expression_node.cpp
        ast/high_level/hl_function_call_node.cpp
        ast/high_level/hl_ast_operand.cpp
        ast/transformations/high_level_ast_lowering.cpp
        ast/define.cpp
        ast/variable.cpp
        passes/low_level/ll_pass_manager.cpp
        passes/low_level/loop_implementation_pass.cpp
        passes/low_level/pseudo_instructions_pass.cpp
        passes/low_level/instruction_counting_pass.cpp#
        passes/low_level/register_allocation_pass.cpp
        passes/low_level/variable_lifetime_mapping.cpp
        passes/low_level/load_intercalation_pass.cpp
        passes/high_level/hl_pass_manager.cpp
        passes/high_level/hl_variable_mapping.cpp
        passes/high_level/function_mapping.cpp
        passes/high_level/inlined_function_elimination.cpp
        passes/high_level/intrinsics_implementation_pass.cpp
        passes/high_level/function_inlining_pass.cpp
        passes/high_level/division_implementation_pass.cpp
        passes/high_level/dead_variable_elimination.cpp
        passes/high_level/declaration_instantiation_combining_pass.cpp
        passes/high_level/normalization_pass.cpp
        fcore_has.cpp
        fcore_cc.cpp
        )

# Regular library for regular use
add_library(fCore_lib_internal ${FCORE_LIB_SRCS} ${C_PARSER_SRCS} ${ASM_PARSER_SRCS})
target_link_libraries(fCore_lib_internal antlr4-runtime)

# Standalone assembler executable
add_executable(fCore_has fcore_has_main.cpp)
target_link_libraries(fCore_has fCore_lib_internal)

# Standalone assembler executable
add_executable(fCore_cc fcore_cc_main.cpp)
target_link_libraries(fCore_cc fCore_lib_internal)

install(TARGETS fCore_has DESTINATION /usr/bin)
install(TARGETS fCore_cc DESTINATION /usr/bin)