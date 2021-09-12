// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

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
    hl_pass_manager hl_manager = create_hl_pass_manager(ep,{});
    hl_manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    high_level_ast_lowering translator;

    translator.set_input_ast(normalized_ast);
    translator.translate();
    std::shared_ptr<ll_ast_node> ll_ast = translator.get_output_ast();

    ll_pass_manager ll_manager = create_ll_pass_manager();
    ll_manager.run_morphing_passes(ll_ast);

    binary_generator writer;

    instruction_stream program_stream = instruction_stream_builder::build_stream(ll_ast);

    std::unordered_map<std::string, std::shared_ptr<variable>> iom = parser.get_iom_map();

    stream_pass_manager sman(iom);
    program_stream = sman.process_stream(program_stream);

    writer.process_stream(program_stream, false);

    std::vector<uint32_t> result = writer.get_raw_program();

    std::vector<uint32_t> gold_standard = {0x146, 1104150528};
    ASSERT_EQ(result, gold_standard);
}



TEST(EndToEndC, fcore_cc) {


    std::string input_file = "c_e2e/test_normalization.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, false);
    std::vector<uint32_t> result = compiler.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0x146, 1104150528};
    ASSERT_EQ(result, gold_standard);
}


TEST(EndToEndC, end_to_end_intrinsics) {


    std::string input_file = "c_e2e/test_intrinsics_implementation.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,true);
    std::vector<uint32_t> result = compiler.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0x944,0x26,0x42C80000, 0x40950};
    ASSERT_EQ(result, gold_standard);
}



TEST(EndToEndC, json_writing) {
    std::string input_file = "c_e2e/test_intrinsics_implementation.c";

    std::string test_json = "/tmp/e2e_c_json_test.json";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,false);
    compiler.write_json(test_json);

    nlohmann::json out;
    std::ifstream check_stream(test_json);

    check_stream >> out;

    std::vector<uint32_t> compile_result = out["compiled_program"];

    std::vector<uint32_t> gold_standard = { 0x944,0x26,0x42C80000, 0x40950};

    std::filesystem::remove(test_json);

    ASSERT_EQ(gold_standard, compile_result);
}

TEST(EndToEndC, pragma_io) {
    std::string input_file = "c_e2e/test_pragma_io.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,false);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x81021, 0x26, 0x40A00000, 0x40883, 0x26, 0x3e2aaaab, 0x140843};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, conditional) {
    std::string input_file = "c_e2e/test_full_conditional.c";


    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,false);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0xE6, 0x40C00000};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_scalarization) {
    std::string input_file = "c_e2e/test_array_scalarization.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,true);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x26, 0x40000000, 0x60843, 0x26, 0x40400000, 0x80863, 0x21083, 0x62023, 0x21063};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, loop) {
    std::string input_file = "c_e2e/test_full_loop.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes,false);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x1e1021, 0x60841, 0x1e1021, 0x60841};

   ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, nested_loop) {
    std::string input_file = "c_e2e/test_full_nested_loop.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x61021, 0x81021, 0x62821, 0x62821, 0xc1021,0x81021, 0xc2821, 0x62821};

     ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_initialization) {
    std::string input_file = "c_e2e/test_array_initialization.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x26, 0x41b00000, 0x46, 0x40400000, 0x61023};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, array_initialization_through_function) {
    std::string input_file = "c_e2e/test_array_initialization_through_function.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x246, 0x40400000};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, constant_argument_inlining) {
    std::string input_file = "c_e2e/test_constant_argument_inlining.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x246, 0x40400000};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_io_definition) {
    std::string input_file = "c_e2e/test_array_io_definition.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x63881, 0x103881, 0x123882, 0x143883, 0x161883};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, multidimensional_array_io_definition) {
    std::string input_file = "c_e2e/test_multidim_array_io_definition.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true);
    std::vector<uint32_t> result =  compiler.get_hexfile(false);


    std::vector<uint32_t> gold_standard = {0x23881, 0x103881, 0x143882, 0x123881, 0x163882, 0x183883, 0x200883, 0x1a3883, 0x240883};

    ASSERT_EQ(gold_standard, result);
}