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
        code_elements/ll_ast/ll_instruction.cpp
        code_elements/ll_ast/ll_ast_node.cpp
        code_elements/ll_ast/ll_loop.cpp
        code_elements/hl_ast/hl_ast_node.cpp
        code_elements/hl_ast/hl_definition_node.cpp
        code_elements/hl_ast/hl_function_def_node.cpp
        code_elements/hl_ast/hl_expression_node.cpp
        code_elements/hl_ast/hl_function_call_node.cpp
        code_elements/hl_ast/hl_ast_operand.cpp
        code_elements/define.cpp
        code_elements/variable.cpp
        passes/pass_manager.cpp
        passes/loop_implementation_pass.cpp
        passes/pseudo_instructions_pass.cpp
        passes/instruction_counting_pass.cpp
        passes/register_allocation_pass.cpp
        passes/variable_lifetime_mapping.cpp
        passes/load_intercalation_pass.cpp
        fcore_has.cpp
        fcore_cc.cpp
        )

# Regular library for regular use
add_library(fCore_lib_internal ${FCORE_LIB_SRCS})
target_link_libraries(fCore_lib_internal asm_parser_lib)
target_link_libraries(fCore_lib_internal c_parser)

# Static library for use with uscope server
add_library(fCore_lib_internal_s SHARED ${FCORE_LIB_SRCS})
target_link_libraries(fCore_lib_internal_s asm_parser_libs)
set_property(TARGET fCore_lib_internal_s PROPERTY POSITION_INDEPENDENT_CODE 1)

# Python module
if(NOT ${PY_MODULE_EXCLUDE})
    add_definitions(-DPYTHON_MODULE)
    pybind11_add_module(fCore_has_py  ${FCORE_LIB_SRCS})
    target_link_libraries(fCore_has_py PRIVATE asm_parser_libs)
    target_link_libraries(fCore_has_py PRIVATE antlr4-runtime)
endif(NOT ${PY_MODULE_EXCLUDE})

# Standalone assembler executable
add_executable(fCore_has fcore_has_main.cpp)
target_link_libraries(fCore_has fCore_lib_internal)

# Standalone assembler executable
add_executable(fCore_cc fcore_cc_main.cpp)
target_link_libraries(fCore_cc fCore_lib_internal)

# Install
install(TARGETS fCore_lib_internal_s
        LIBRARY DESTINATION /usr/local/lib/fcore_has)

install(DIRECTORY ../includes # source directory
        DESTINATION /usr/local/include # target directory
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
        )
