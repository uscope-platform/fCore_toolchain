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
#include <gtest/gtest.h>
#include <filesystem>

#include "fcore_has.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"

using namespace fcore;

static inline uint32_t Reverse32(uint32_t value)
{
    return (((value & 0x000000FFu) << 24u) |
            ((value & 0x0000FF00u) <<  8u) |
            ((value & 0x00FF0000u) >>  8u) |
            ((value & 0xFF000000u) >> 24u));
}

TEST( EndToEndAsm, simple_file ) {
    std::string input_file = "asm/test_add.s";

    std::ifstream stream(input_file);
    fcore_has uut(stream, false);

    std::vector<uint32_t> gold_standard = {0x60001, 0xc,0xc, 0xc, 0x86, 0x42c80000, 0xa6, 0x43480000, 0xc2b01, 0xc};

    // file parsing and processing

    std::vector<uint32_t> result = uut.get_executable();
    ASSERT_EQ(result, gold_standard);

    //verilog memfile generationc
    uut.write_verilog_memfile(input_file+".mem");

    std::ifstream infile(input_file+".mem");
    std::string a;
    result.clear();
    while (infile >> a)
    {
        result.push_back(std::stoi(a, nullptr, 16));
    }
    ASSERT_EQ(result, gold_standard);

    // hex file generation

    uut.write_hexfile(input_file+".hex");

    std::string filename = input_file+".hex";
    FILE *fptr = fopen(filename.c_str(),"rb");

    uint32_t program_size = uut.get_program_size();
    uint32_t res[1000];
    ssize_t ret = fread(res,sizeof(uint32_t), program_size, fptr);
    if(ret ==0){
        std::cout << "OH SNAP! this should not have happened";
        exit(1);
    }
    result.clear();
    for(int i = 0; i < program_size; i++){
        result.push_back(Reverse32(res[i]));
    }
    ASSERT_EQ(result, gold_standard);//result == gold_standard);


}

TEST( EndToEndAsm, compare_file ) {
    std::string input_file = "asm/compare_file.s";

    std::ifstream stream(input_file);
    fcore_has uut(stream, false);

    std::vector<uint32_t> result = uut.get_executable();

    std::vector<uint32_t> gold_standard = {0x90001,0xc, 0xc,0xc, 0x86, 0x42c80000, 0xc2881, 0x8006E, 0x21848, 0x21849, 0x2184a, 0x2184b, 0xC};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEndAsm, variables_file) {
    std::string input_file = "asm/test_variables.s";

    std::ifstream stream(input_file);
    fcore_has uut(stream, false);

    std::vector<uint32_t> result = uut.get_executable();
    std::vector<uint32_t> gold_standard = {0xe0001,0xc, 0xc,0xc,0x26,0x42c80000, 0x46, 0x43480000, 0xA6, 0x43480000, 0xc2881, 0xe4821,0xe4841,0x26,0x42c80000,0xe4821, 0x50b2, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEndAsm, load_constant_file) {
    std::string input_file = "asm/test_ldc.s";


    std::ifstream stream(input_file);
    fcore_has uut(stream, false);

    std::vector<uint32_t> result = uut.get_executable();

    std::vector<uint32_t> gold_standard = {0x70001,0xc, 0xc, 0xc,0x86, 0x42c80000, 0xa6, 0x43480000, 0x86, 0x4048f5c3, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEndAsm, embeddable_wrapper_pass) {
    std::string input_file = "asm/test_ldc.s";
    int hex_size;
    auto *hex_result = (uint32_t*) malloc(4096*sizeof(uint32_t));

    fCore_has_embeddable_f(input_file.c_str(),hex_result, &hex_size, false);

    std::vector<uint32_t> result;
    for(int i = 0; i<hex_size;i++){
        result.push_back(hex_result[i]);
    }
    free(hex_result);
    std::vector<uint32_t> gold_standard = {0x70001, 0xc, 0xc, 0xc,0x86, 0x42c80000, 0xa6, 0x43480000, 0x86, 0x4048f5c3, 0xc};
    ASSERT_EQ( result, gold_standard);
}


TEST(EndToEndAsm, load_integer_constant) {
    std::string input_file = "asm/test_ldc_int.s";

    std::ifstream stream(input_file);
    fcore_has uut(stream, true);

    std::vector<uint32_t> result = uut.get_executable();

    std::vector<uint32_t> gold_standard = {0x30001,  0xc, 0xc,0xc,0x86, 0x64, 0xc};
    ASSERT_EQ( result, gold_standard);
}


TEST(EndToEndAsm, json_writing) {
    std::string input_file = "asm/test_ldc.s";

    std::string test_json = "/tmp/e2e_asm_json_test.json";

    std::ifstream stream(input_file);
    fcore_has uut(stream, false);

    uut.write_json(test_json);

    nlohmann::json out;
    std::ifstream check_stream(test_json);

    check_stream >> out;

    std::vector<uint32_t> compile_result = out["compiled_program"];

    std::vector<uint32_t> gold_standard = {0x70001, 0xc, 0xc, 0xc,0x86, 0x42c80000, 0xa6, 0x43480000, 0x86, 0x4048f5c3, 0xc};

    std::filesystem::remove(test_json);

    ASSERT_EQ(gold_standard, compile_result);
}


TEST(EndToEndAsm, conditional_select) {
    std::string input_string = "ldc r4, 100\n"
                             "ldc r5, 200\n"
                             "ldc r1, 1\n"
                             "csel r1, r5, r4\n"
                             "stop";

    std::istringstream stream(input_string);
    fcore_has uut(stream, true);

    std::vector<uint32_t> result = uut.get_executable();

    std::vector<uint32_t> gold_standard = {0x80001, 0xc, 0xc,0xc,0x86, 0x64, 0xa6, 0xc8, 0x26, 1, 0x8283b, 0xc};
    ASSERT_EQ( result, gold_standard);
}


