set(FCORE_COMMON_SRCS_I
        frontend/binary_loader.cpp
        backend/binary_generator.cpp
        data_structures/executable.cpp
        data_structures/instruction_stream/register_instruction.cpp
        data_structures/instruction_stream/conversion_instruction.cpp
        data_structures/instruction_stream/independent_instruction.cpp
        data_structures/instruction_stream/intercalated_constant.cpp
        data_structures/instruction_stream/load_constant_instruction.cpp
        data_structures/instruction_stream/pseudo_instruction.cpp
        data_structures/instruction_stream/instruction_variant.cpp
        data_structures/instruction_stream/ternary_instruction.cpp
        data_structures/instruction_stream.cpp
        data_structures/common/memory_tracker.cpp
        tools/define.cpp
        tools/register_map.cpp
        data_structures/common/variable.cpp
        tools/variable_map.cpp
        tools/define_map.cpp
        tools/array_linearizer.cpp
        passes/instruction_stream/instruction_counting_pass.cpp
        passes/instruction_stream/io_constant_tracking.cpp
        passes/instruction_stream/stream_pass_manager.cpp
        passes/instruction_stream/variable_lifetime_mapping.cpp
        passes/instruction_stream/variable_mapping.cpp
        passes/instruction_stream/register_allocation.cpp
        passes/instruction_stream/constant_merging.cpp
        passes/instruction_stream/zero_assignment_removal_pass.cpp
        passes/instruction_stream/bound_register_mapping.cpp
        passes/instruction_stream/ternary_reduction.cpp
        passes/instruction_stream/uninitialized_variable_detection.cpp
        passes/instruction_stream/virtual_operations_implementation.cpp
        instrumentation/instrumentation_core.cpp
        data_structures/high_level_ast/ast_code_block.cpp
        passes/high_level/infrastructure/hl_acting_visitor.cpp
        passes/high_level/infrastructure/hl_observing_visitor.cpp
        passes/instruction_stream/ternary_deconfliction.cpp
)


set(FCORE_CC_SRCS
        frontend/C/C_language_parser.cpp
        frontend/C/C_pre_processor.cpp
        frontend/C/C_ErrorHandling.cpp
        frontend/C/C_Tree_visitor.cpp
        data_structures/high_level_ast/ast_node.cpp
        data_structures/high_level_ast/variant/hl_ast_node_variant.cpp
        data_structures/high_level_ast/ast_definition.cpp
        data_structures/high_level_ast/ast_function_def.cpp
        data_structures/high_level_ast/ast_loop.cpp
        data_structures/high_level_ast/ast_conditional.cpp
        data_structures/high_level_ast/ast_expression.cpp
        data_structures/high_level_ast/ast_call.cpp
        data_structures/high_level_ast/ast_operand.cpp
        data_structures/high_level_ast/ast_struct.cpp
        data_structures/constants_tracker.cpp
        passes/high_level/optimizations/dead_load_elimination.cpp
        passes/high_level/optimizations/constant_propagation.cpp
        passes/high_level/infrastructure/hl_pass_manager.cpp
        passes/high_level/optimizations/visitor_passes/inlined_function_elimination.cpp
        passes/high_level/optimizations/visitor_passes/array_initialization_substitution.cpp
        passes/high_level/optimizations/visitor_passes/operating_assignment_implementation_pass.cpp
        passes/high_level/optimizations/visitor_passes/intrinsics_implementation_pass.cpp
        passes/high_level/optimizations/visitor_passes/division_implementation_pass.cpp
        passes/high_level/optimizations/visitor_passes/ternary_expression_extraction.cpp
        passes/high_level/optimizations/visitor_passes/dead_variable_elimination.cpp
        passes/high_level/optimizations/visitor_passes/array_index_lowering.cpp
        passes/high_level/optimizations/visitor_passes/constant_folding_pass.cpp
        passes/high_level/optimizations/visitor_passes/comparison_flipping.cpp
        passes/high_level/optimizations/visitor_passes/constant_commutation.cpp
        passes/high_level/optimizations/inline_constant_extraction.cpp
        passes/high_level/optimizations/fuction_mangling_pass.cpp
        passes/high_level/optimizations/function_inlining_pass.cpp
        passes/high_level/optimizations/code_block_inlining_pass.cpp
        passes/high_level/optimizations/conditional_implementation_pass.cpp
        passes/high_level/optimizations/loop_unrolling_pass.cpp
        passes/high_level/optimizations/normalization_pass.cpp
        passes/high_level/optimizations/contiguous_array_identification.cpp
        passes/high_level/optimizations/visitor_passes/destructuring_pass.cpp
        passes/high_level/semantic_analysis/assignments.cpp
        passes/high_level/semantic_analysis/undefined_variables.cpp
        passes/high_level/semantic_analysis/function_calls.cpp
        passes/high_level/semantic_analysis/mixed_type_operations.cpp
        passes/high_level/semantic_analysis/type_propagation.cpp
        fcore_cc.cpp
        tools/high_level_ast_lowering.cpp
        tools/expression_evaluator.cpp
        frontend/schema_validators/schema_validator_base.cpp
)


set(FCORE_AS_SRCS
        frontend/asm/AsmTree_visitor.cpp
        frontend/asm/asm_language_parser.cpp
        frontend/asm/AsmErrorHandling.cpp
        fcore_has.cpp
        )


set(FCORE_DIS_SRCS
        backend/assembly_generator.cpp
        fcore_dis.cpp
        )

set(FCORE_EMU_SRCS
        frontend/schema_validators/schema_validator_base.cpp
        data_structures/emulation/v1/hil_bus_map.cpp
        data_structures/emulation/v1/emulator_output.cpp
        data_structures/emulation/v1/specs/emulator_specs.cpp
        data_structures/emulation/v1/emulation_program.cpp
        data_structures/emulation/v2/hil_bus_map.cpp
        data_structures/emulation/v2/emulator_output.cpp
        data_structures/emulation/v2/specs/emulator_specs.cpp
        data_structures/emulation/v2/emulation_program.cpp
        emulator/v1/backend/emulator_backend.cpp
        emulator/v1/backend/emulation_outputs_manager.cpp
        emulator/v1/backend/efi_dispatcher.cpp
        emulator/v1/emulator_builder.cpp
        emulator/v1/emulation_sequencer.cpp
        emulator/v1/emulator_manager.cpp
        emulator/v1/emulator_runner.cpp
        emulator/v1/backend/multirate_io_repeater.cpp
        emulator/v1/interconnect_manager.cpp
        emulator/v2/backend/emulator_backend.cpp
        emulator/v2/backend/emulation_outputs_manager.cpp
        emulator/v2/backend/efi_dispatcher.cpp
        emulator/v2/emulator_builder.cpp
        emulator/v2/emulation_sequencer.cpp
        emulator/v2/emulator_manager.cpp
        emulator/v2/emulator_runner.cpp
        emulator/v2/bus_allocator.cpp
        emulator/v2/backend/multirate_io_repeater.cpp
        emulator/v2/interconnect_manager.cpp
        emulator/emulator_dispatcher.cpp
        )



set(FCORE_SRCS ${FCORE_COMMON_SRCS_I} ${FCORE_CC_SRCS} ${FCORE_AS_SRCS} ${FCORE_DIS_SRCS} ${FCORE_EMU_SRCS} PARENT_SCOPE)

add_library(common_srcs ${FCORE_COMMON_SRCS_I})

target_link_libraries(common_srcs PUBLIC
        nlohmann_json::nlohmann_json
        ValiJSON::valijson
)

add_library(fcore_has_lib ${FCORE_AS_SRCS} ${ASM_PARSER_SRCS})
target_link_libraries(fcore_has_lib PUBLIC
        common_srcs
        antlr4_static
        spdlog::spdlog
)


add_executable(fCore_has fcore_has_main.cpp)
target_link_libraries(fCore_has PRIVATE
        fcore_has_lib
        CLI11::CLI11
        )

add_library(fcore_cc_lib ${FCORE_CC_SRCS} ${C_PARSER_SRCS})
target_link_libraries(fcore_cc_lib PUBLIC
        common_srcs
        antlr4_static
        GTest::gtest
        spdlog::spdlog
)

add_executable(fCore_cc fcore_cc_main.cpp)
target_link_libraries(fCore_cc PRIVATE common_srcs
        fcore_cc_lib
        CLI11::CLI11
        )

add_library(fcore_dis_lib ${FCORE_DIS_SRCS})
target_link_libraries(fcore_dis_lib PUBLIC
        common_srcs
)

add_executable(fCore_dis ${FCORE_DIS_SRCS} fcore_dis_main.cpp)
target_link_libraries(fCore_dis PRIVATE
        fcore_dis_lib
        CLI11::CLI11
        spdlog::spdlog
        )


add_executable(fCore_emu fcore_emu_main.cpp)


add_library(fcore_emu_lib_gp ${FCORE_EMU_SRCS}
        emulator/v1/backend/gp_executor.cpp
        emulator/v2/backend/gp_executor.cpp
)
target_compile_definitions(fcore_emu_lib_gp PUBLIC GENERAL_PURPOSE_EMULATION=1)
target_link_libraries(fcore_emu_lib_gp PUBLIC
        fcore_dis_lib
        fcore_cc_lib
        fcore_has_lib
)

add_executable(fCore_emu_gp fcore_emu_main.cpp)
target_link_libraries(fCore_emu_gp
        fcore_emu_lib_gp
        spdlog::spdlog
        CLI11::CLI11
)

if(${INCLUDE_EMULATOR})

    add_library(fcore_emu_lib ${FCORE_EMU_SRCS}
            emulator/v1/backend/ba_executor.cpp
            emulator/v2/backend/ba_executor.cpp
    )
    target_compile_definitions(fcore_emu_lib PUBLIC GENERAL_PURPOSE_EMULATION=0)


    target_link_libraries(fcore_emu_lib PUBLIC
            Ip_floating_point_v7_1_bitacc_cmodel
    )
    install(FILES ../third_party/fp_ip_cmodel/lib/libIp_floating_point_v7_1_bitacc_cmodel.so
            DESTINATION ${CMAKE_INSTALL_LIBDIR})
else ()
    add_library(fcore_emu_lib ${FCORE_EMU_SRCS} emulator/v1/backend/gp_executor.cpp)
    target_compile_definitions(fcore_emu_lib PUBLIC GENERAL_PURPOSE_EMULATION=1)

endif(${INCLUDE_EMULATOR})

target_link_libraries(fcore_emu_lib PUBLIC
        fcore_dis_lib
        fcore_cc_lib
        fcore_has_lib
)

target_link_libraries(fCore_emu
        fcore_emu_lib
        spdlog::spdlog
        CLI11::CLI11
)

add_custom_target(toolchain)
add_dependencies(toolchain fCore_has fCore_cc fCore_dis fCore_emu)


install(TARGETS fCore_has DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS fCore_cc DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS fCore_dis DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS fCore_emu DESTINATION ${CMAKE_INSTALL_BINDIR})
