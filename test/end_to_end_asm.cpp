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

#include "fcore_has.hpp"
#include "ast/low_level/ll_ast_node.hpp"



static inline uint32_t Reverse32(uint32_t value)
{
    return (((value & 0x000000FFu) << 24u) |
            ((value & 0x0000FF00u) <<  8u) |
            ((value & 0x00FF0000u) >>  8u) |
            ((value & 0xFF000000u) >> 24u));
}

TEST( EndToEndAsm, simple_file ) {
    std::string input_file = "test_add.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};
    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> gold_standard = {0x64107, 0xc8147, 0x185601, 0xc};

    // file parsing and processing

    std::vector<uint32_t> result = uut.get_hexfile(false);
    ASSERT_EQ(result, gold_standard);

    //verilog memfile generation

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
    fread(res,sizeof(uint32_t), program_size, fptr);
    result.clear();
    for(int i = 0; i < program_size; i++){
        result.push_back(Reverse32(res[i]));
    }
    ASSERT_EQ(result, gold_standard);//result == gold_standard);


}

TEST( EndToEndAsm, for_file ) {
    std::string input_file = "test_for.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0x64107, 0xc8147, 0x185101, 0x64107, 0x185101, 0x0000, 0x0000, 0x64107, 0x185101, 0x0000, 0x0000, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST( EndToEndAsm, branch_file ) {
    std::string input_file = "test_branch.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);

     std::vector<uint32_t> gold_standard = {0x64107, 0x185101, 0x1000c1, 0x43088, 0x43089, 0x4308a, 0x4308b, 0xC};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEndAsm, variables_file) {
    std::string input_file = "test_variables.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);
    std::vector<uint32_t> gold_standard = {0x64047, 0xC8087, 0xc8147, 0x185101, 0x1c9041,0x1c9081,0x64047,0x1c9041, 0xA152, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEndAsm, load_constant_file) {
    std::string input_file = "test_ldc.s";

    std::string include_dir;
    std::vector<std::string> include_files = {};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0x64107, 0xc8147, 0x106, 0x4048f5c3, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEndAsm, embeddable_wrapper_pass) {
    std::string input_file = "test_ldc.s";
    int hex_size;
    auto *hex_result = (uint32_t*) malloc(4096*sizeof(uint32_t));

    fCore_has_embeddable_f(input_file.c_str(),hex_result, &hex_size);

    std::vector<uint32_t> result;
    for(int i = 0; i<hex_size;i++){
        result.push_back(hex_result[i]);
    }
    free(hex_result);
    std::vector<uint32_t> gold_standard = {0x64107, 0xc8147, 0x106, 0x4048f5c3, 0xc};
    ASSERT_EQ( result, gold_standard);
}

/*
TEST_CASE( "Embeddable C wrapper fail") {
    std::string input_file = "test_ldc_fail.s";

    std::ifstream ifs(input_file);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()) );

    std::string gold_standard = "mismatched input '<EOF>' expecting {'ldc', 'stop', 'nop', 'add', 'sub', 'mul', 'itf', 'fti', 'ldr', 'ble', 'bgt', 'beq', 'bne', 'mov', 'for(', '#pragma ', 'let', 'const', 'input', 'output'}";
    REQUIRE_THROWS_WITH( fCore_has_embeddable_s(content), gold_standard);
}*/