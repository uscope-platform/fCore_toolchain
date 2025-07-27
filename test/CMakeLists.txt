set(TEST_SOURCES
        data_model/hl_ast_expression.cpp
        data_model/Instruction_classes.cpp
        passes/instruction_stream_pass.cpp
        passes/type_checking.cpp
        passes/semantic_analysis.cpp
        passes/hl_passes.cpp
        end_to_end_asm.cpp
        testing_main.cpp
        end_to_end_C.cpp
        C_preprocessor.cpp
        C_tree_visitor_testing.cpp
        disassembler_testing.cpp
        hl_pretty_print.cpp
        emulator/full_testing/emulator_manager_interactive.cpp
        emulator/full_testing/emulator_manager_v2.cpp
        emulator/full_testing/emulator_iom.cpp
        emulator/full_testing/emulator_multichannel_tests.cpp
        emulator/emulator_execution.cpp
        emulator/emulator_schema_validation.cpp
        emulator/emulator_runner.cpp
        emulator/bus_deployment_interface.cpp
        tools/length_analysis.cpp
        tools/deep_copy.cpp
        tools/expression_evaluator.cpp
)




add_executable(test_target ${TEST_SOURCES})
target_link_libraries(test_target PUBLIC ${GTEST_LIBRARIES}
        fcore_cc_lib
        fcore_has_lib
        fcore_dis_lib
        fcore_emu_lib
        pthread
        Ip_floating_point_v7_1_bitacc_cmodel
        spdlog::spdlog
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
        )



include(GoogleTest)
gtest_discover_tests(test_target)

# Preprocessor
set(C_PREP_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/c_prep)
file(MAKE_DIRECTORY ${C_PREP_TEST_FILES_DIR})
configure_file(C_files/preprocessor/test_comments.c ${C_PREP_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_pragmas.c ${C_PREP_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_include_fail.c ${C_PREP_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/preprocessor/test_include.c ${C_PREP_TEST_FILES_DIR} COPYONLY)
configure_file(C_files/preprocessor/include_test.h ${C_PREP_TEST_FILES_DIR} COPYONLY)

# DISASSEMBLER TESTING FILES
set(DIS_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/dis)
file(MAKE_DIRECTORY ${DIS_TEST_FILES_DIR})
configure_file(disassembler_files/test_add.hex ${DIS_TEST_FILES_DIR} COPYONLY)
configure_file(disassembler_files/test_error.mem ${DIS_TEST_FILES_DIR} COPYONLY)

# EMULATOR TESTING FILES
set(EMU_TEST_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/emu)
file(MAKE_DIRECTORY ${EMU_TEST_FILES_DIR})

configure_file(emulator_files/test_inputs.csv ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_inputs_spec.json ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_interconnect_spec.json ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_compilation.json ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_compilation_interconnect.json ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/test_compilation_memory.json ${EMU_TEST_FILES_DIR} COPYONLY)

configure_file(emulator_files/exec_format/test_exec_format.json ${EMU_TEST_FILES_DIR} COPYONLY)
configure_file(emulator_files/exec_format/test_exec_format_error.json ${EMU_TEST_FILES_DIR} COPYONLY)



set(EMU_TEST_SCHEMAS_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/emu/schemas)
file(MAKE_DIRECTORY ${EMU_TEST_SCHEMAS_FILES_DIR})
configure_file(schemas/valid_emulator_schema.json ${EMU_TEST_SCHEMAS_FILES_DIR} COPYONLY)
configure_file(schemas/valid_compiler_schema.json ${EMU_TEST_SCHEMAS_FILES_DIR} COPYONLY)
configure_file(schemas/msgpackd_schema.json ${EMU_TEST_SCHEMAS_FILES_DIR} COPYONLY)
configure_file(schemas/msgpackd_schema_fail.json ${EMU_TEST_SCHEMAS_FILES_DIR} COPYONLY)
