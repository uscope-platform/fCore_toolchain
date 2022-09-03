// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <fstream>

#include <gtest/gtest.h>
#include "passes/low_level/ll_pass_manager.hpp"
#include "passes/ll_passes.hpp"
#include "tools/high_level_ast_lowering.hpp"
#include "fcore_cc.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "data_structures/instruction_stream.hpp"


TEST(EndToEndC, minimal_c_end_to_end) {


    std::string input_file = "c_e2e/test_normalization.c";

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(input_file, result_def);
    parser.pre_process({});
    parser.parse();

    std::string ep = "main";
    hl_pass_manager hl_manager = create_hl_pass_manager(ep,{},0);
    hl_manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    high_level_ast_lowering translator;

    translator.set_input_ast(normalized_ast);
    translator.translate();
    std::shared_ptr<ll_ast_node> ll_ast = translator.get_output_ast();

    ll_pass_manager ll_manager = create_ll_pass_manager(0);
    ll_manager.run_morphing_passes(ll_ast);

    binary_generator writer;

    instruction_stream program_stream = instruction_stream_builder::build_stream(ll_ast);

    std::unordered_map<std::string, std::shared_ptr<variable>> iom = parser.get_iom_map();

    stream_pass_manager sman(iom,0);
    program_stream = sman.process_stream(program_stream);

    writer.process_stream(program_stream, false);

    std::vector<uint32_t> result = writer.get_raw_program();

    std::vector<uint32_t> gold_standard = {0x146, 1104150528};
    ASSERT_EQ(result, gold_standard);
}



TEST(EndToEndC, fcore_cc) {


    std::string input_file = "c_e2e/test_normalization.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, false, 0);
    std::vector<uint32_t> result = compiler.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0x146, 1104150528};
    ASSERT_EQ(result, gold_standard);
}


TEST(EndToEndC, end_to_end_intrinsics) {


    std::string input_file = "c_e2e/test_intrinsics_implementation.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,true, 0);
    std::vector<uint32_t> result = compiler.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0x944,0x26,0x42C80000, 0x40950, 0x0953, 0x2f956};
    ASSERT_EQ(result, gold_standard);
}



TEST(EndToEndC, json_writing) {
    std::string input_file = "c_e2e/test_intrinsics_implementation.c";

    std::string test_json = "/tmp/e2e_c_json_test.json";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.write_json(test_json);

    nlohmann::json out;
    std::ifstream check_stream(test_json);

    check_stream >> out;

    std::vector<uint32_t> compile_result = out["compiled_program"];

    std::vector<uint32_t> gold_standard = { 0x944,0x26,0x42C80000, 0x40950, 0x0953, 0x2f956};

    std::filesystem::remove(test_json);

    ASSERT_EQ(gold_standard, compile_result);
}

TEST(EndToEndC, pragma_io) {
    std::string input_file = "c_e2e/test_pragma_io.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x81021, 0x66, 0x40A00000, 0xa1883, 0x66, 0x3e2aaaab, 0x1418a3};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, conditional) {
    std::string input_file = "c_e2e/test_full_conditional.c";


    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,false, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0xE6, 0x40C00000};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_scalarization) {
    std::string input_file = "c_e2e/test_array_scalarization.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x26, 0x40000000, 0x60843, 0x26, 0x40400000, 0x80863, 0x21083, 0x62023, 0x21063};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, loop) {
    std::string input_file = "c_e2e/test_full_loop.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x1e2061, 0xa1881, 0x1e2061, 0xa1881};

   ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, nested_loop) {
    std::string input_file = "c_e2e/test_full_nested_loop.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0xa2061, 0xc2061, 0xa3861, 0xc3861,0xa2061, 0xc2061, 0xa3861, 0xc3861};

     ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_initialization) {
    std::string input_file = "c_e2e/test_array_initialization.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x26, 0x41300000, 0x43823, 0x23843};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, array_initialization_through_function) {
    std::string input_file = "c_e2e/test_array_initialization_through_function.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x246, 0x40400000};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, constant_argument_inlining) {
    std::string input_file = "c_e2e/test_constant_argument_inlining.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x246, 0x40400000};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_io_definition) {
    std::string input_file = "c_e2e/test_array_io_definition.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x63881, 0x103881, 0x123882, 0x143883, 0x161883};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, multidimensional_array_io_definition) {
    std::string input_file = "c_e2e/test_multidim_array_io_definition.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x23881, 0x103881, 0x143882, 0x123881, 0x163882, 0x183883, 0x200883, 0x1a3883, 0x240883};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, iom_initialization){
    std::string input_file = "c_e2e/test_iom_initialization.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x106,0x3F800000,0x126, 0x40000000, 0x146, 0x40400000, 0x166, 0x40800000, 0x286, 0x40400000};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, test_move){
    std::string input_file = "c_e2e/test_move.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x140021};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, test_complex_normalization){
    std::string input_file = "c_e2e/test_complex_normalization.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x66, 0x40A00000, 0x81841, 0x66, 0x41880000, 0xa1823, 0x620a3, 0x141941};

    ASSERT_EQ(gold_standard, result);
}

TEST(InstructionStreamPasses, register_allocation){
    std::string input_file = "c_e2e/test_register_allocation.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x46, 0x41880000, 0x141023};

    ASSERT_EQ(gold_standard, result);
}



TEST(HlPassesTest, functionInliningExpression) {

    std::string input_file = "c_e2e/test_function_inline_expression.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x26, 0x40A00000, 0x40b23, 0x26, 0x3727C5AC, 0x61023, 0x218c1, 0x46, 0xC3160000, 0x21031, 0x46, 0x43160000, 0x21030, 0x40021};

    ASSERT_EQ(gold_standard, result);

}


TEST(HlPassesTest, essential_variable_initialization) {

    std::string input_file = "c_e2e/test_essential_variable_initialization.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0xE6, 0x3F800000, 0xcc8e9, 0xec8e1, 0xa00e1};

    ASSERT_EQ(gold_standard, result);

}



TEST(HlPassesTest, negative_leading_sum) {

    std::string input_file = "c_e2e/test_negative_leading_sum.c";


    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x21002, 0xe1823};

    ASSERT_EQ(gold_standard, result);

}


TEST(HlPassesTest, function_vars_mangling) {

    std::string input_file = "c_e2e/test_function_vars_mangling.c";


    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x66, 4, 0x81843, 0x66, 2, 0xa1823, 0x62881, 0x140861};

    ASSERT_EQ(gold_standard, result);

}


TEST(HlPassesTest, constant_merging) {

    std::string input_file = "c_e2e/test_constant_merging.c";


    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x26, 0x42340000,  0x180943, 0x1a0963};

    ASSERT_EQ(gold_standard, result);

}