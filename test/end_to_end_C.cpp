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


TEST(EndToEndC, fcore_cc) {

    std::string input_file = "c_e2e/test_normalization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result = compiler.get_executable();

    std::vector<uint32_t> gold_standard = {0x20003,0x30001, 0x1000a, 0x26, 1104150528, 0xc};
    ASSERT_EQ(result, gold_standard);
}

TEST(EndToEndC, end_to_end_intrinsics) {


    std::string input_file = "c_e2e/test_intrinsics_implementation.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result = compiler.get_executable();

    std::vector<uint32_t> gold_standard = {0x20003,0x70001,0x1000A,0x1024,0x46,0x42C80000, 0x61030, 0x1033, 0x2f836, 0xc};
    ASSERT_EQ(result, gold_standard);
}

TEST(EndToEndC, exceptionHandling) {
    std::string input_file = "c_e2e/test_exception.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cells":{"type": "input","address":59},
                    "v_arms":{"type": "output","address":[60,61]}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::string result = compiler.get_errors();

    ASSERT_EQ(result, "Strings are not supported by the fCore toolchain");
}

TEST(EndToEndC, json_writing) {
    std::string input_file = "c_e2e/test_intrinsics_implementation.c";

    std::string test_json = "/tmp/e2e_c_json_test.json";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    compiler.write_json(test_json);

    nlohmann::json out;
    std::ifstream check_stream(test_json);

    check_stream >> out;

    std::vector<uint32_t> compile_result = out["compiled_program"];

    std::vector<uint32_t> gold_standard = {0x20003,0x70001,0x1000A,0x1024,0x46,0x42C80000, 0x61030, 0x1033, 0x2f836, 0xc};

    std::filesystem::remove(test_json);

    ASSERT_EQ(gold_standard, compile_result);
}

TEST(EndToEndC, iom) {
    std::string input_file = "c_e2e/test_pragma_io.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "memory","address":1},
                    "b":{"type": "input","address":2},
                    "c":{"type": "memory","address":4},
                    "test":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003,0x80004, 0x3000A, 0x3f0004, 0x10002, 0x3e0001, 0x7e0fc1, 0x26, 0x40A00000, 0x40fe3, 0x26, 0x3e2aaaab, 0x60843, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, conditional) {
    std::string input_file = "c_e2e/test_full_conditional.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test":{"type": "output","address":7}
                }})"
    );

    fcore_cc compiler(input_file, includes,true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xE6, 0x40C00000, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, loop) {
    std::string input_file = "c_e2e/test_full_loop.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "h":{"type": "input","address":1},
                    "a":{"type": "input","address":2},
                    "j":{"type": "output","address":15}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x1e18e1, 0x163861, 0x1e2101, 0x184081, 0xc};

   ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, nested_loop) {
    std::string input_file = "c_e2e/test_full_nested_loop.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "h":{"type": "input","address":1},
                    "a":{"type": "input","address":2},
                    "j":{"type": "output","address":15}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x162861, 0x163061,0x182881,  0x183081, 0xc};

     ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_initialization) {
    std::string input_file = "c_e2e/test_array_initialization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":7}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x86, 0x40000000,0x26, 0x41300000, 0x43823, 0xa3843, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, array_initialization_through_function) {
    std::string input_file = "c_e2e/test_array_initialization_through_function.c";

    std::vector<std::string> includes;


    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":18}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x246, 0x40400000, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, constant_argument_inlining) {
    std::string input_file = "c_e2e/test_constant_argument_inlining.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":18}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x246, 0x40400000, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_io_definition) {
    std::string input_file = "c_e2e/test_array_io_definition.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":[4,7]},
                    "b":{"type": "output","address":3},
                    "c":{"type": "output","address":[8,9]},
                    "d":{"type": "memory","address":[10,11]}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x63881, 0x103881, 0x123882, 0x143883, 0x161883, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, multidimensional_array_io_definition) {
    std::string input_file = "c_e2e/test_multidim_array_io_definition.c";

    std::vector<std::string> includes;


    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":[4,7]},
                    "c":{"type": "output","address":[8,9,10,11]},
                    "d":{"type": "memory","address":[12,13,16,18]}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x23881, 0x103881, 0x143882, 0x123881, 0x163882, 0x183883, 0x200883, 0x1a3883, 0x240883, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, iom_initialization){
    std::string input_file = "c_e2e/test_iom_initialization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":[8,9,10,11]},
                    "b":{"type": "output","address":20}
                }})"
    );
    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x106,0x3F800000,0x126, 0x40000000, 0x146, 0x40400000, 0x166, 0x40800000, 0x286, 0x40800000, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, test_move){
    std::string input_file = "c_e2e/test_move.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":1},
                    "test":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x140021, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, test_complex_normalization){
    std::string input_file = "c_e2e/test_complex_normalization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":1},
                    "b":{"type": "input","address":2},
                    "test":{"type": "memory","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x66, 0x40A00000, 0x81841, 0x66, 0x41880000, 0xa1823, 0x620a3, 0x141941, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, register_allocation){
    std::string input_file = "c_e2e/test_register_allocation.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":1},
                    "test":{"type": "memory","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x46, 0x41880000, 0x141023, 0xc};

    ASSERT_EQ(gold_standard, result);
}



TEST(EndToEndC, functionInliningExpression) {

    std::string input_file = "c_e2e/test_function_inline_expression.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test_in":{"type": "input","address":25},
                    "integ":{"type": "memory","address":6}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x26, 0x40A00000, 0x40b23, 0x26, 0x3727C5AC, 0x61023, 0x218c1, 0x46, 0xC3160000, 0x21031, 0x46, 0x43160000, 0x21030, 0x40021, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, essential_variable_initialization) {

    std::string input_file = "c_e2e/test_essential_variable_initialization.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test_in":{"type": "input","address":25},
                    "test_out":{"type": "output","address":5},
                    "test_var":{"type": "output","address":7},
                    "factor_1":{"type": "output","address":6}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x26, 0x3F800000, 0xcc829, 0xec821, 0xa00e1, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, test_constant_propagation) {

    std::string input_file = "c_e2e/test_constant_propagation.c";

    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    std::vector<uint32_t> result =  compiler.get_raw_code();


    std::vector<uint32_t> gold_standard = {0x226,0x3F800000, 0x222a21, 0x242a41, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, negative_leading_sum) {

    std::string input_file = "c_e2e/test_negative_leading_sum.c";

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":2},
                    "b":{"type": "input","address":3},
                    "c":{"type": "output","address":7}
                }})"
            );
    std::vector<std::string> includes;

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x21002, 0xe1823, 0xc};

    ASSERT_EQ(gold_standard, result);
}


TEST(EndToEndC, function_vars_mangling) {

    std::string input_file = "c_e2e/test_function_vars_mangling.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "b":{"type": "input","address":2},
                    "a":{"type": "input","address":1},
                    "c":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x66, 4, 0x81843, 0x66, 2, 0xa1823, 0x62881, 0x140861, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, constant_merging) {

    std::string input_file = "c_e2e/test_constant_merging.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":[10,11]},
                    "b":{"type": "output","address":[12,13]}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x26, 0x42340000,  0x180943, 0x1a0963, 0xc};

    ASSERT_EQ(gold_standard, result);

}



TEST(EndToEndC, zero_assignment_removal) {

    std::string input_file = "c_e2e/test_zero_assignment_removal.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":10},
                    "b":{"type": "output","address":12}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x180141, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, loop_index_expression) {

    std::string input_file = "c_e2e/test_loop_index_expression.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cells":{"type": "input","address":[40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59]},
                    "v_arms":{"type": "output","address":[60,61]}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x786, 0, 0x7a6, 0x0, 0x7b97a1, 0x7b9fa1, 0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, loop_index_expression_multidim) {

    std::string input_file = "c_e2e/test_loop_index_expression_multidim.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cells":{"type": "input","address":[40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59]},
                    "v_arms":{"type": "output","address":[60,61]}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x786, 0, 0x7a6, 0x0, 0x7b8fa1, 0x7bafa1, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, contiguos_array_allocation) {

    std::string input_file = "c_e2e/test_contiguous_array_allocation.c";


    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "out_1":{"type": "output","address":2},
                    "out_2":{"type": "output","address":6}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xe5875, 0x26, 0x4,0x408e1, 0x26,0x2,0xc0901,0xc};

    ASSERT_EQ(gold_standard, result);

}


TEST(EndToEndC, efi_load_elimination) {

    std::string input_file = "c_e2e/test_efi_load_elimination.c";

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "theta":{"type": "input","address":1},
                    "s_th":{"type": "output","address":15},
                    "c_th":{"type": "output","address":17}
                }})"
    );

    fcore_cc compiler(input_file, includes, true, 0);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x60021,  0x46, 0x0, 0x1e1055, 0x86,0x38000074,0x1e7883, 0x46, 0x1, 0x221055,0xc};

    ASSERT_EQ(gold_standard, result);

}